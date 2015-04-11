//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "NewickIO.hpp"

#include "../utils/Log.hpp"
#include "../utils/StringTools.hpp"

using namespace pygmy;
using namespace utils;
using namespace std;

bool NewickIO::Read(Tree<NodePhylo>::Ptr tree, const wstring& filename)
{
	// Set name of tree to the filename
	wstring file = utils::StringTools::ReplaceChar(filename, _T('\\'), _T('/'));
	wstring::size_type slashPos = file.rfind(_T('/'));
	wstring::size_type dotPos = file.rfind(_T('.'));
	if(dotPos > slashPos)
		tree->SetName(file.substr(slashPos+1, dotPos-slashPos-1));
	else
		tree->SetName(_T(""));

	// Parse Newick file
	wifstream input(file.c_str(), std::ios::in);
	bool bLoaded = Read(tree, input);
	input.close();

	if(bLoaded)
		tree->CalculateStatistics();

	return bLoaded;
}

bool NewickIO::Read(Tree<NodePhylo>::Ptr tree, wistream & in)
{	
	// Checking the existence of specified input stream
	if(!in)
		return false;
	
	// We concatenate all line in file till we reach the ending semi colon:
	wstring temp, newickStr;

	// Read entire input stream
	while (!in.eof())
  {
		getline(in, temp, _T('\n'));  // Copy current line in temporary string
    wstring::size_type index = temp.find(_T(";"));
		if(index != string::npos)
    {
			newickStr += temp.substr(0, index + 1);
			break;
		}
    else newickStr += temp;
	}

	newickStr = utils::StringTools::RemoveSubstrings(newickStr, _T('['), _T(']'));

	return ParseNewickString(tree, newickStr);
}

void NewickIO::ParseNodeInfo(NodePhylo* node, wstring& nodeInfo, bool bLeafNode)
{
	wstring length;
	wstring name;
	wstring supportValue;

	// check if this element has length
	int colon = nodeInfo.find_last_of(':');
  if(colon != -1)
  {
		length = StringTools::RemoveSurroundingWhiteSpaces(nodeInfo.substr(colon + 1));
		nodeInfo = StringTools::RemoveSurroundingWhiteSpaces(nodeInfo.substr(0, colon));
  }

	// check for name and/or support value
	int lastP = nodeInfo.find_last_of('\'');
	int firstP = nodeInfo.find_first_of('\'');
	if(firstP != -1)
	{
		name = nodeInfo.substr(firstP+1, lastP-firstP-1);
		StringTools::ReplaceChar(name, '_', ' ');
		supportValue = StringTools::RemoveSurroundingWhiteSpaces(nodeInfo.substr(lastP+1));
	}
	else
	{
		int spacePos = nodeInfo.find_first_of(' ');
		if(spacePos != -1)
		{
			// parse the name and support value
			name = nodeInfo.substr(0, spacePos-1);	
			StringTools::ReplaceChar(name, '_', ' ');
			supportValue = StringTools::RemoveSurroundingWhiteSpaces(nodeInfo.substr(spacePos+1));
		}
		else
		{
			// The remaining description is either a name of support value depending 
			// on whether this is a leaf or internal node.
			if(bLeafNode)
			{
				name = StringTools::RemoveSurroundingWhiteSpaces(nodeInfo);
				StringTools::ReplaceChar(name, '_', ' ');
			}
			else
				supportValue = StringTools::RemoveSurroundingWhiteSpaces(nodeInfo);
		}
	}	

	if(!name.empty())
		node->SetName(name);

	if(!length.empty())
		node->SetDistanceToParent(StringTools::ToDouble(length));

	if(!supportValue.empty())
		node->SetBootstrapToParent(StringTools::ToInt(supportValue));
}

bool NewickIO::ParseNewickString(Tree<NodePhylo>::Ptr tree, const wstring& newickStr)
{
	// create root node
	uint processedElement = 0;
	NodePhylo* root(new NodePhylo(processedElement++));
	tree->SetRootNode(root);
	root->SetDistanceToParent(0.0f);

	int lastP  = newickStr.find_last_of(')');
	int firstP = newickStr.find_first_of('(');
  int semi = newickStr.find_last_of(';');

	wstring content = newickStr.substr(firstP + 1, lastP - firstP);
  wstring rootElements = newickStr.substr(lastP + 1, semi - lastP - 1);
  
	ParseNodeInfo(root, rootElements, false);

	// parse newick string
	std::stack<NodePhylo*> nodeStack;
	nodeStack.push(root);
	wstring nodeInfo;
	NodePhylo* activeNode = NULL;
	for(uint i = 0; i < content.size(); ++i)
	{
		char ch = content.at(i);

		if(ch == '(')
		{
			// create a new internal node which will be the child 
			// of the node on the top of the stack
			NodePhylo* node(new NodePhylo(processedElement++));
			nodeStack.top()->AddChild(node);
			nodeStack.push(node);
		}
		else if(ch == ')')
		{
			if(activeNode)
			{
				// if there is a currently active node, then we are
				// processing an internal node
				ParseNodeInfo(activeNode, nodeInfo, false);
			}
			else
			{
				// if there is no currently active node, then we
				// must create a new leaf node
				NodePhylo* node(new NodePhylo(processedElement++));
				nodeStack.top()->AddChild(node);

				ParseNodeInfo(node, nodeInfo, true);				
			}

			// we are finished processing all children of the node
			// on the top of the stack
			activeNode = nodeStack.top();
			nodeStack.pop();

			nodeInfo = _T("");
		}
		else if(ch == ',')
		{
			if(activeNode)
			{
				// if there is a currently active node, then we are
				// processing an internal node
				ParseNodeInfo(activeNode, nodeInfo, false);
				activeNode = NULL;
				nodeInfo = _T("");
			}
			else
			{
				// if there is no currently active node, then we
				// must create a new leaf node
				NodePhylo* node(new NodePhylo(processedElement++));
				nodeStack.top()->AddChild(node);

				ParseNodeInfo(node, nodeInfo, true);
				nodeInfo = _T("");
			}
		}
		else
		{
			// character is indicate the properties of a node
			nodeInfo += ch;
		}
	}

	if(!nodeStack.empty())
	{
		//Log::Inst().Error("Failed to parse Newick string. There does not appear to be an even number of opening and closing parentheses.");
		return false;
	}
	
	return true; 
}

void NewickIO::Write(Tree<NodePhylo>::Ptr tree, wostream& out) const
{
	// Checking the existence of specified file, and possibility to open it in write mode
	assert(out != NULL);

	out << "(";

	NodePhylo* root = tree->GetRootNode();
	
  if(tree->GetNumberOfLeaves() == 0)
  {
    out << "'" << root->GetName().c_str() << "'";

		float dist = root->GetDistanceToParent();
		if(dist != NodePhylo::NO_DISTANCE)
			out << " " << dist;
  }
  else
  {
		WriteNodes(tree, out, root);
  }
	out << ")";
	
	// Output the name of the root if it has one
	if(!utils::StringTools::IsEmpty(root->GetName()))
		out << "'" << root->GetName().c_str() << "'";
	
	out << ";" << endl;
}

void NewickIO::WriteNodes(Tree<NodePhylo>::Ptr tree, wostream& out, NodePhylo* parent) const
{
	vector<unsigned int> childrenId = parent->GetChildrenIds();
	assert(childrenId.size() > 0);

	WriteElements(tree, out, parent, parent->GetChild(0));
	for(uint i = 1; i < childrenId.size(); i++)
	{
		out << ",";
		WriteElements(tree, out, parent, parent->GetChild(i));
	}
}

void NewickIO::WriteElements(Tree<NodePhylo>::Ptr tree, wostream& out, NodePhylo* parent, NodePhylo* child) const
{	
  if(child->GetNumberOfChildren() != 0)
  {
    out << "(";
		WriteNodes(tree, out, child); 
    out << ")";
  }

	if(!utils::StringTools::IsEmpty(child->GetName()))
		out << "'" << child->GetName().c_str() << "'";
	
	if(child->GetBootstrapToParent() != NodePhylo::NO_DISTANCE)
		out << " " << ((NodePhylo*)child)->GetBootstrapToParent();

	if(child->GetDistanceToParent() != NodePhylo::NO_DISTANCE)
		out << ":" << child->GetDistanceToParent();
}



