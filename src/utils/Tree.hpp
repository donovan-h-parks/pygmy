//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// Based on code by: Julien Dutheil and Celine Scornavacca (Bio++ project)
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _TREE_
#define _TREE_

#include "../core/Precompiled.hpp"

#include "../utils/TreeTools.hpp"
#include "../utils/Log.hpp"

#include <ostream>

namespace utils
{

/**
 * @brief Build a new tree. The nodes of the tree can be any class derived from Node.
 *
 * Code example:
 * @code
 * @endcode
 *
 * @see Node
 */
template<class N> class Tree
{
public:
	/** Allows convenient syntax for creating smart pointers of this class. */
	typedef boost::shared_ptr< Tree<N> > Ptr;	

public:	
	/** Constructor. */
	Tree(): m_root(NULL), m_name(_T("")), m_numLeaves(0), m_numNodes(0), m_lengthOfTree(0) {}

	/**
	 * @brief Constructor
	 * @param root Root of tree.
	 */
	Tree(N* root): m_root(root), m_name(_T("")), m_numLeaves(0), m_numNodes(0), m_lengthOfTree(0) {}

	/** Copy constructor. */
	Tree(const Tree<N>& t);

	/** Assignment operator. */
	Tree<N>& operator=(const Tree<N>& t);

	/** Destructor. */
	~Tree();

	/** Clone tree. */
	typename Tree::Ptr Clone() const { return Tree::Ptr(new Tree<N>(*this)); }

public:
	/** Get name of tree. */
	std::wstring GetName() const  { return m_name; }

	/**
	 * @brief Set name of tree.
	 * @param name Desired name of tree.
	 */		
	void SetName(const std::wstring & name) { m_name = name; }

	/** 
	 * @brief Set root node of tree.
	 * @param root Desired root node.
	 */
	void SetRootNode(N* root) { m_root = root; }

	/** Get root node. */
	N* GetRootNode() const { return m_root; }

	/** Get id of root node. */
	unsigned int GetRootId() const { return m_root->GetId(); }

	/** Get node with the given id. */	
	N* GetNode(unsigned int id) const; 

	/** Get node with the given name. */
	N* GetNode(const std::wstring& name) const;

	/** Get number of leaf nodes in tree. */
	unsigned int GetNumberOfLeaves() const { return m_numLeaves; }

	/** Get all leaf nodes in tree. */
	std::vector<N*> GetLeaves() const { return TreeTools<N>::GetLeaves(m_root); }

	/** Get id of all leaf nodes. */
	std::vector<unsigned int> GetLeafIds() const { return TreeTools<N>::GetLeafIds(m_root); }

	/** Get name of all leaf nodes in depth first order. */
	std::vector<std::wstring> GetLeafNames() const { return TreeTools<N>::GetLeafNames(m_root); }

	/** Get number of nodes in tree. */
	unsigned int GetNumberOfNodes() const { return m_numNodes; }

	/** Get all nodes in tree. */
	std::vector<N*> GetNodes() const { return TreeTools<N>::GetNodes(m_root); }

	/** Get id of all nodes. */
	std::vector<unsigned int> GetNodesId() const { return TreeTools<N>::GetNodesId(m_root); }

	/** Get length of all branches. */
	std::vector<float> GetBranchLengths() const { return TreeTools<N>::GetBranchLengths(m_root); }

	/** Get distance to furthest leaf node. */
	float GetDistToFurthestLeafNode(const N* node) const { return TreeTools<N>::GetDistToFurthestLeafNode(node); }

	/** 
	 * @brief Indicate if tree has a node with a given id.
	 * @param nodeId Id to check.
	 * @return True if tree has a node with the given id.
	 */
	bool HasNode(unsigned int nodeId) const { return TreeTools<N>::HasNodeWithId(m_root, nodeId); }
		
	/** 
	 * @brief Reset node ids so they are all unique values.
	 * @param nodeId Id of node of interest.
	 * @param dist Distance to parent node.
	 */
	void ResetNodeIds();
	
	/** Indicate if tree is multifurcating. */
	bool IsMultifurcating() const;
	
	/** Get total length of all branches in tree. */
	float GetTotalLength() const;

	/** 
	 * @brief Set all branches to the specified length.
	 * @param length Desired length.
	 */
	void SetBranchLengths(float length);

	/**
	 * @brief Scale tree distances by a constant factor.
	 * @param factor Amount to scale tree distances by.
	 */
	void ScaleTree(float factor);

	/**
	 * @brief Collapse all nodes with a bootstrap value less than the specified value. 
	 * @param support Collapse all nodes with support less than this value.
	 */
	void CollapseNodes(float support);

	/** 
	 * @brief Project tree onto a set of leaf nodes.
	 * @param names Names of leaf nodes to project tree onto.
	 * Note: names will contain a list of all the names not found in the tree after function returns.
	 */
	void ProjectTree(std::vector<std::wstring>& names);

	/** 
	 * @brief Set a new root for the tree.
	 * @param node The new root will be placed half way along the branch leading from this node to its parent.
	 */
	void Reroot(N* node);

	/**
	 * @brief Calculate commonly needs statistics for tree.
	 **/
	void CalculateStatistics();

	/** Get distance from root to furthest leaf node. */
	float GetLengthOfTree() const { return m_lengthOfTree; }
 
protected:		
	void DestroySubtree(N* node);

	void CalculatePostOrderStatistics(N* node);

protected:
	N* m_root;
	std::wstring m_name;

	uint m_numLeaves;
	uint m_numNodes;

	float m_lengthOfTree;
};

// --- Function implementations -----------------------------------------------

template <class N>
Tree<N>::Tree(const Tree<N>& t)
{
	m_name = t.m_name;
	m_numLeaves = t.GetNumberOfLeaves();
	m_numNodes = t.GetNumberOfNodes();
	m_lengthOfTree = t.GetLengthOfTree();

	//Perform a hard copy of the nodes:
	m_root = TreeTools<N>::CloneSubtree(t.GetRootNode());
}

template <class N>
Tree<N>& Tree<N>::operator=(const Tree<N>& t)
{
	// Free memory allocated to LHS tree
	if(m_root) 
	{ 
		DestroySubtree(m_root); 
		delete m_root; 
	}

	// Perform hard copy of nodes on RHS
  m_root = TreeTools<N>::CloneSubtree(t.GetRootNode());
  m_name = t.m_name;

	m_numLeaves = t.GetNumberOfLeaves();
	m_numNodes = t.GetNumberOfNodes();
	m_lengthOfTree = t.GetLengthOfTree();

	return *this;
}

template <class N>
Tree<N>::~Tree()
{
	if(m_root)
	{
		DestroySubtree(m_root);
		delete m_root;
	}
}
	
template <class N>
void Tree<N>::DestroySubtree(N* node)
{
	for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
	{
		N* child = node->GetChild(i);
		DestroySubtree(child);

		delete child;
	}
}

template <class N>
N* Tree<N>::GetNode(unsigned int id) const
{
	std::vector<N*> nodes = TreeTools<N>::SearchNodeWithId(m_root, id);

	if(nodes.size() > 1)
	{
		return NULL;
	}
	else if(nodes.size() == 0)
	{
		return NULL;
	}

	return nodes[0];
}

template <class N>
N* Tree<N>::GetNode(const std::wstring& name) const
{
	std::vector<N*> nodes = TreeTools<N>::SearchNodeWithName(m_root, name);

	if(nodes.size() > 1)
	{
		std::wstring warning = _T("Node::GetNode(): multiple nodes have id = "); 
		utils::Log::Inst().Warning(warning + name);
		return NULL;
	}
	else if(nodes.size() == 0)
	{
		//std::wstring warning = "Node::GetNode(): no node with id = "; 
		//error::Log::Inst().Warning(warning + name);
		return NULL;
	}

	return nodes[0];
}

template <class N>
void Tree<N>::ResetNodeIds()
{
	std::vector<N*> nodes = GetNodes();
	for(unsigned int i = 0; i < nodes.size(); i++)
  {
    nodes[i]->SetId(i);
  }
}

template <class N>
bool Tree<N>::IsMultifurcating() const
{
	bool b = false;
	for(unsigned int i = 0; i < m_root->GetNumberOfChildren(); i++)
  {
		b = b || TreeTools<N>::IsMultifurcating(m_root->GetChild(i));
	}
	return b;
}

template <class N>
float Tree<N>::GetTotalLength() const
{
	float length = 0;
	for(unsigned int i = 0; i < m_root->GetNumberOfChildren(); i++)
  {
    length += TreeTools<N>::GetTotalLength(m_root->GetChild(i));
  }
  return length;
}

template <class N>
void Tree<N>::SetBranchLengths(float length)
{
	for(unsigned int i = 0; i < m_root->GetNumberOfChildren(); i++)
  {
    TreeTools<N>::SetBranchLengths(m_root->GetChild(i), length);
  }
}

template <class N>
void Tree<N>::ScaleTree(float factor)
{
	for(unsigned int i = 0; i < m_root->GetNumberOfChildren(); i++)
  {
	  TreeTools<N>::ScaleTree(m_root->GetChild(i), factor);
  }
}

template <class N>
void Tree<N>::CollapseNodes(float support)
{
	std::queue<N*> queue;
	std::vector<N*> children = GetRootNode()->GetChildren();
	foreach(N* child, children)
	{
		queue.push(child);
	}

	while(!queue.empty())
	{
		N* curNode = queue.front();

		// check support of current node
		if(curNode->GetBootstrapToParent() < support)
		{
			// collapse this node by assigning all of its children to
			// the parent of this node
			std::vector<N*> children = curNode->GetChildren();
			foreach(N* child, children)
			{
				curNode->GetParent()->AddChild(child);
				child->SetParent(curNode->GetParent());

				if(child->GetDistanceToParent() != Node::NO_DISTANCE)
				{
					// keep track of branch lengths
					child->SetDistanceToParent(child->GetDistanceToParent() 
																										+ curNode->GetDistanceToParent()); 
				}

				if(!child->IsLeaf())
					queue.push(child);
			}

			curNode->GetParent()->RemoveChild(curNode);
		}
		else
		{
			// add children to the queue
			std::vector<N*> children = curNode->GetChildren();
			foreach(N* child, children)
			{
				if(!child->IsLeaf())
					queue.push(child);
			}
		}

		// Remove current parent node
		queue.pop();
	}	
}

template <class N>
void Tree<N>::ProjectTree(std::vector<std::wstring>& names)
{
	// mark all internal node as unprocessed so we can distinguish them for 
	// true leaf nodes
	std::vector<N*> nodes = GetNodes();
	foreach(N* node, nodes)
	{
		node->SetProcessed(!node->IsLeaf());
	}

	// Remove all leaf nodes not in projection set.

	// 1. Create dictionary mapping names to leaf nodes.
	std::vector<N*> leafNodes = GetLeaves();
	std::map<std::wstring, N*> namesToNodes;
	foreach(N* leaf, leafNodes)
	{
		namesToNodes.insert(std::pair<std::wstring, N*>(leaf->GetName(), leaf));
	}

	// 2. Remove all nodes contained in the projection set.
	std::map<std::wstring, N*>::iterator it;
	foreach(const std::wstring& name, names)
	{
		it = namesToNodes.find(name);
		if(it != namesToNodes.end())
			namesToNodes.erase(it);
	}

	// 3. Delete all remaining nodes in the dictionary.
	for(it = namesToNodes.begin(); it != namesToNodes.end(); ++it)
	{
		N* deadNode = it->second;
		deadNode->GetParent()->RemoveChild(deadNode);
	}

	// collapse any internal nodes that have less than 2 children. This is 
	// done in a breadth first manner from the leaf nodes to the root node.
	std::vector<N*> curNodes = GetLeaves();
	std::set<N*> nextNodes;
	while(!curNodes.empty())
	{
		nextNodes.clear();
		foreach(N* node, curNodes)
		{
			if(!node->IsRoot())
				nextNodes.insert(node->GetParent());

			if(node->IsProcessed() && node->GetNumberOfChildren() == 0)
			{
				if(node->IsRoot())
				{
					// we have a root with no children so just leave it as the sole node in the tree
				}
				else
				{
					// remove this node from the tree
					node->GetParent()->RemoveChild(node);
					nextNodes.erase(node);
				}
			}
			else if(node->IsProcessed() && node->GetNumberOfChildren() == 1)
			{		
				if(node->IsRoot())
				{
					// the root is degenerate so we must make its sole child the new root
					node->GetChild(0)->SetParent(NULL);
					node->GetChild(0)->SetDistanceToParent(Node::NO_DISTANCE);
					SetRootNode(node->GetChild(0));
					nextNodes.erase(node);
					delete node;
				}
				else
				{
					// remove node from tree after assigning its sole child to its parent
					node->GetParent()->AddChild(node->GetChild(0));	
					
					if(node->GetChild(0)->GetDistanceToParent() != Node::NO_DISTANCE)
					{
						// keep track of branch lengths
						node->GetChild(0)->SetDistanceToParent(node->GetChild(0)->GetDistanceToParent() 
																											+ node->GetDistanceToParent()); 
					}

					node->GetParent()->RemoveChild(node);
					nextNodes.erase(node);
				}
			}	
		}

		curNodes.assign(nextNodes.begin(), nextNodes.end());
	}
}

template <class N>
void Tree<N>::Reroot(N* node)
{
	if(node->IsRoot())
		return;

	N* newRoot = new N(m_root->GetId());

	// create new root and add selected subtree as a child
	N* parentNode = node->GetParent();
	newRoot->AddChild(node);
	if(node->GetDistanceToParent() != Node::NO_DISTANCE)
		node->SetDistanceToParent(node->GetDistanceToParent()*0.5);

	N* prevNode;
	if(!parentNode->IsRoot())
	{
		// add parent of selected subtree as a child to new root
		N* curNode = parentNode->GetParent();		
		newRoot->AddChild(parentNode);
		parentNode->RemoveChild(node);
		parentNode->SetDistanceToParent(node->GetDistanceToParent());

		float prevBootstrap = parentNode->GetBootstrapToParent();
		parentNode->SetBootstrapToParent(node->GetBootstrapToParent());

		// reorganize tree from selected node to the previous root
		prevNode = parentNode;
		while(!curNode->IsRoot())
		{
			N* parentNode = curNode->GetParent();
			prevNode->AddChild(curNode);
			curNode->RemoveChild(prevNode);
			curNode->SetDistanceToParent(prevNode->GetDistanceToParent());
			float tempBootstrap = curNode->GetBootstrapToParent();
			curNode->SetBootstrapToParent(prevBootstrap);
			prevBootstrap = tempBootstrap;

			prevNode = curNode;
			curNode = parentNode;
		}

		// add children of previous root to newly rooted tree
		for(uint i = 0; i < m_root->GetNumberOfChildren(); ++i)
		{
			N* child = m_root->GetChild(i);
			if(child != prevNode)
			{
				prevNode->AddChild(child);

				if(child->GetDistanceToParent() != Node::NO_DISTANCE && prevNode->GetDistanceToParent() != Node::NO_DISTANCE)
					child->SetDistanceToParent(child->GetDistanceToParent() + prevNode->GetDistanceToParent());
				else
					child->SetDistanceToParent(Node::NO_DISTANCE);
			}
		}
	}
	else
	{
		for(uint i = 0; i < m_root->GetNumberOfChildren(); ++i)
		{
			N* child = m_root->GetChild(i);
			if(child != node)
			{
				newRoot->AddChild(child);

				if(child->GetDistanceToParent() != Node::NO_DISTANCE && node->GetDistanceToParent() != Node::NO_DISTANCE)
					child->SetDistanceToParent(child->GetDistanceToParent() + node->GetDistanceToParent());
				else
					child->SetDistanceToParent(Node::NO_DISTANCE);
			}
		}
	}

	delete m_root;

	std::vector<N*> children = newRoot->GetChildren();
	foreach(N* child, children)
	{
		if(!child->IsLeaf())
			child->SetBootstrapToParent(node->GetBootstrapToParent());
	}

	m_root = newRoot;
}

template <class N>
void Tree<N>::CalculateStatistics()
{
	m_root->SetDepth(0);
	m_root->SetDistanceToRoot(0.0f);

	// perform depth first traversal to calculate:
	//  1. depth of all nodes
	//  2. distance from each node to the root
	//  3. number of nodes in tree
	//  4. number of leaf nodes in tree
	//  5. length of tree (furthest distance from root to a leaf node)
	std::stack<N*> stack;
	for(uint i = 0; i < m_root->GetNumberOfChildren(); ++i)
		stack.push(m_root->GetChild(i));

	m_numNodes = 1;	// remember to count the root node
	m_numLeaves = 0;
	while(!stack.empty())
	{
		N* curNode = stack.top();
		stack.pop();

		m_numNodes++;

		for(uint i = 0; i < curNode->GetNumberOfChildren(); ++i)
			stack.push(curNode->GetChild(i));

		curNode->SetDepth(curNode->GetParent()->GetDepth() + 1);
		curNode->SetDistanceToRoot(curNode->GetParent()->GetDistanceToRoot() + curNode->GetDistanceToParent());

		if(curNode->IsLeaf())
		{
			m_numLeaves++;

			if(curNode->GetDistanceToRoot() > m_lengthOfTree)
				m_lengthOfTree = curNode->GetDistanceToRoot();
		}
	}

	// perform post-order traversal to calculate:
	//  1. height of all nodes
	CalculatePostOrderStatistics(m_root);
}

template <class N>
void Tree<N>::CalculatePostOrderStatistics(N* node)
{
	if(node->IsLeaf())
	{
		node->SetHeight(0);		
		return;
	}

	node->SetHeight(0);
	for(uint i = 0; i < node->GetNumberOfChildren(); ++i)
	{
		N* child = node->GetChild(i);

		CalculatePostOrderStatistics(child);

		if(child->GetHeight() >= node->GetHeight())
			node->SetHeight(child->GetHeight() + 1);
	}	
}


} 

#endif	
