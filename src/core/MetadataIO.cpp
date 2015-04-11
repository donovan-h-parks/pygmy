//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../core/MetadataIO.hpp"

#include "../core/App.hpp"
#include "../core/VisualTree.hpp"
#include "../core/MetadataInfo.hpp"
#include "../core/NodePhylo.hpp"

#include "../utils/Log.hpp"
#include "../utils/StringTools.hpp"

using namespace boost;
using namespace std;
using namespace utils;
using namespace pygmy;

bool MetadataIO::Read(const std::wstring& filename, VisualTreePtr visualTree, MetadataInfoPtr metadataInfo) 
{
	const int ROWS_TO_SHOW_PROGRESS_DLG = 2000;

	// clear any previously loaded metadata
	metadataInfo->Clear();

	// open file containing metadata
	wifstream infile(filename.c_str());
	if(!infile.is_open()) 
	{
		utils::Log::Inst().Warning(_T("(Warning) Failed to open metadata file."));	
		return false;
	}

	// read in column names
	wstring columnHeaders;
	getline(infile, columnHeaders);

	// tokenize columns
	tokenizer< escaped_list_separator<wchar_t>, wstring::const_iterator, wstring > columnTokens(columnHeaders);
	tokenizer< escaped_list_separator<wchar_t>, wstring::const_iterator, wstring >::iterator colIter;   

	// parse all rows
	wstring line;
	vector<wstring> rows;
	while(getline(infile, line))
		rows.push_back(line);

	wxProgressDialog* progressDlg = NULL;
	if(rows.size() > ROWS_TO_SHOW_PROGRESS_DLG)
	{
		progressDlg = new wxProgressDialog(_T("Loading file"), _T("Loading ") + filename + _T("..."),
																														rows.size()-1, App::Inst().GetMainFrame(), 
																														wxPD_APP_MODAL | wxPD_CAN_ABORT | wxPD_SMOOTH |
																														wxPD_ELAPSED_TIME | wxPD_AUTO_HIDE);
	}
	else
	{
		::wxBeginBusyCursor();
	}

	uint rowNum = 0;
	vector<wstring>::const_iterator it;
	for(it = rows.begin(); it != rows.end(); ++it)
	{
		if(progressDlg && rowNum % 25 == 0)
			progressDlg->Update(rowNum);		

		rowNum++;

		tokenizer< escaped_list_separator<wchar_t>, wstring::const_iterator, wstring > dataTokens(*it);
		tokenizer< escaped_list_separator<wchar_t>, wstring::const_iterator, wstring >::iterator dataIter = dataTokens.begin();                

		wstring id = _T("");

		std::map<std::wstring, std::wstring> metadata;
		for(colIter = columnTokens.begin(); colIter != columnTokens.end(); ++colIter)
		{
			std::wstring columnHeader = *colIter;
			std::wstring columnValue = *dataIter;
			metadata.insert(pair<wstring, wstring>(columnHeader, columnValue));

			// determine which column we are looking at (this allows user to put columns in any order)
			if(utils::StringTools::ToLower(*colIter) == _T("sequence id"))
			{
				id = *dataIter;
			}

			// move to next column
			dataIter++;
		}

		// check for required data
		if(id == _T(""))
		{
			if(progressDlg)
				progressDlg->Destroy();

			utils::Log::Inst().Warning(_T("(Warning) Missing 'Sequence Id' field."));
			return false;
		}
		
		// associate metadata with leaf node
		NodePhylo* nodeOriginal = visualTree->GetOriginalTree()->GetNode(id);
		NodePhylo* nodeActive = visualTree->GetTree()->GetNode(id);
		if(nodeOriginal)
		{
			// failure to find a node with a given id is not necessarily an error
			// since the metadata file may simple span more sites/leaves than the
			// tree currently being considered
			nodeOriginal->SetMetadata(metadata);

			if(nodeActive)
				nodeActive->SetMetadata(metadata);

			metadataInfo->AddMetadata(metadata);
		}
	}

	// closing the file stream.
	infile.close();

	if(progressDlg)
		progressDlg->Destroy();
	else
		::wxEndBusyCursor();

	return true;
}

