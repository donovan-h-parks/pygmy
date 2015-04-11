//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../gui/TaxaSelectionDlg.hpp"

#include "../core/App.hpp"
#include "../core/VisualTree.hpp"
#include "../core/ViewportMain.hpp"
#include "../core/MetadataInfo.hpp"

#include "../utils/StringTools.hpp"
#include "../utils/AlphaNumericSorter.hpp"

using namespace pygmy;

std::wstring TaxaSelectionDlg::m_lastSelectedField = _T("");

TaxaSelectionDlg::TaxaSelectionDlg(wxWindow* parent, VisualTreePtr visualTree, ViewportMainPtr viewport)
	: TaxaSelectionLayout(parent), m_visualTree(visualTree), m_viewport(viewport)
{
	if(visualTree)
	{
		Init();
		Fit();
	}
}

TaxaSelectionDlg::~TaxaSelectionDlg()
{

}

void TaxaSelectionDlg::Init()
{
	// populate combo box with all metadata fields 
	MetadataInfoPtr metadata = m_visualTree->GetMetadataInfo();

	if(metadata)
	{
		std::vector< std::wstring > fields = metadata->GetFields();
		foreach(const std::wstring& field, fields)
		{
			m_cboFields->Append(field);
		}
	}
	else
	{
		m_cboFields->Append(_T("Sequence Id"));
	}

	if(m_cboFields->FindString(m_lastSelectedField) != wxNOT_FOUND)
	{
		m_cboFields->SetValue(m_lastSelectedField);
	}
	else
	{
		m_cboFields->SetValue(m_cboFields->GetString(0));
	}

	// Set field values
	wxCommandEvent dummy;
	OnFieldChange(dummy);
}

void TaxaSelectionDlg::OnFieldChange( wxCommandEvent& event ) 
{ 
	m_lastSelectedField = m_cboFields->GetValue();

	m_lstInactiveValues->Clear();
	m_lstActiveValues->Clear();

	std::vector<std::wstring> activeFieldValues;
	GetSortedFieldValues(m_cboFields->GetValue().wc_str(), true, activeFieldValues);

	std::vector<std::wstring> inactiveFieldValues;
	GetSortedFieldValues(m_cboFields->GetValue().wc_str(), false, inactiveFieldValues);

	// populate inactive and active list boxes
	for(uint i = 0; i < activeFieldValues.size(); ++i)
	{
		if(!MetadataInfo::IsMissingData(activeFieldValues.at(i).c_str()))
			m_lstActiveValues->Append(activeFieldValues.at(i).c_str());
	}

	for(uint i = 0; i < inactiveFieldValues.size(); ++i)
	{
		if(!MetadataInfo::IsMissingData(inactiveFieldValues.at(i).c_str()))
			m_lstInactiveValues->Append(inactiveFieldValues.at(i).c_str());
	}
}

void TaxaSelectionDlg::GetSortedFieldValues(const std::wstring& field, bool bActive, std::vector<std::wstring>& fieldValues)
{
	MetadataInfoPtr metadata = m_visualTree->GetMetadataInfo();

	// get all unique field values within the given field
	std::vector<NodePhylo*> leaves = m_visualTree->GetTree()->GetLeaves();
	std::set< std::wstring > activeFieldValues;
	foreach(NodePhylo* leaf, leaves)
	{
		if(metadata)
			activeFieldValues.insert(leaf->GetData(field));
		else
			activeFieldValues.insert(leaf->GetName());
	}

	fieldValues.clear();
	if(bActive)
	{
		fieldValues = std::vector<std::wstring>(activeFieldValues.begin(), activeFieldValues.end());
	}
	else
	{
		// get inactive set
		std::set<std::wstring> allFieldValues;
		if(metadata)
		{
			FieldInfo fieldInfo = metadata->GetInfo(field);
			allFieldValues = fieldInfo.values;
		}
		else
		{
			std::vector<NodePhylo*> leaves = m_visualTree->GetOriginalTree()->GetLeaves();
			foreach(NodePhylo* leaf, leaves)
				allFieldValues.insert(leaf->GetName());
		}

		foreach(const std::wstring& fieldValue, activeFieldValues)
		{
			allFieldValues.erase(fieldValue);
		}

		fieldValues = std::vector<std::wstring>(allFieldValues.begin(), allFieldValues.end());
	}

	utils::AlphaNumericSorter::Sort(fieldValues);
}

void TaxaSelectionDlg::OnAdd( wxCommandEvent& event )
{
	wxArrayInt selections;
	m_lstInactiveValues->GetSelections(selections);

	wxArrayString selectionStr;
	for(uint i = 0; i < selections.Count(); ++i)
	{
		selectionStr.Add(m_lstInactiveValues->GetString(selections[i]));		
	}

	m_lstActiveValues->Append(selectionStr);

	for(uint i = 0; i < selectionStr.Count(); ++i)
	{
		m_lstInactiveValues->Delete(m_lstInactiveValues->FindString(selectionStr[i]));
	}
}

void TaxaSelectionDlg::OnRemove( wxCommandEvent& event )
{
	wxArrayInt selections;
	m_lstActiveValues->GetSelections(selections);

	wxArrayString selectionStr;
	for(uint i = 0; i < selections.Count(); ++i)
	{
		selectionStr.Add(m_lstActiveValues->GetString(selections[i]));		
	}

	m_lstInactiveValues->Append(selectionStr);

	for(uint i = 0; i < selectionStr.Count(); ++i)
	{
		m_lstActiveValues->Delete(m_lstActiveValues->FindString(selectionStr[i]));
	}
}

void TaxaSelectionDlg::Apply() 
{ 
	if(!m_visualTree)
		return;

	::wxBeginBusyCursor();

	std::vector< std::wstring > activeTaxa;
	std::vector<NodePhylo*> leaves = m_visualTree->GetTree()->GetLeaves();

	// get all active taxa
	foreach(NodePhylo* leaf, leaves)
	{
		for(uint i = 0; i < m_lstActiveValues->GetCount(); ++i)
		{
			std::wstring test = leaf->GetData(m_lastSelectedField);
			if(leaf->GetData(m_lastSelectedField) == m_lstActiveValues->GetString(i).wc_str())
			{
				activeTaxa.push_back(leaf->GetName());
				break;
			}
		}
	}

	m_visualTree->ProjectTree(activeTaxa);

	MetadataInfoPtr metadata = m_visualTree->GetMetadataInfo();
	metadata->SetMetadata(m_visualTree->GetTree());

	m_viewport->SetTree(m_visualTree);

	::wxEndBusyCursor();
}