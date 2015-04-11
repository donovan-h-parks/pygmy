//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _TAXA_SELECTION_DLG_
#define _TAXA_SELECTION_DLG_

#include "../core/Precompiled.hpp"

#include "../gui/TaxaSelectionLayout.h"

namespace pygmy
{

/**
 * @brief Handles adding/removing taxa within a tree.
 */
class TaxaSelectionDlg : public TaxaSelectionLayout
{
public:
	/**
	 * @brief Constructor.
	 * @param parent Parent for this frame
	 * @param visualTree Visual tree to select taxa from.
	 * @param viewport OpenGL viewport containing the visual tree.
	 */
	TaxaSelectionDlg(wxWindow* parent, VisualTreePtr visualTree, ViewportMainPtr viewport);

	/** Destructor */
	~TaxaSelectionDlg();

private:
	/** Initialize controls. */
	void Init();

	/** Apply all parameter values. */
	void Apply();

	/** Field combobox value has changed. */
	void OnFieldChange( wxCommandEvent& event );

	/** Get all field values for a given field in sorted order. */
	void GetSortedFieldValues(const std::wstring& field, bool bActive, std::vector<std::wstring>& fieldValues);

	/** Add sequences to active set. */
	void OnAdd( wxCommandEvent& event );

	/** Remove sequences from active set. */
	void OnRemove( wxCommandEvent& event );

	/** OK button event handler. */
	void OnOK( wxCommandEvent& event ){ Apply(); EndModal(wxID_OK); }

	/** Apply button event handler. */
	void OnApply( wxCommandEvent& event ){ Apply(); }

	/** Cancel button event handler. */
	void OnCancel( wxCommandEvent& event ){ EndModal(wxID_CANCEL); }

protected:
	/** Visual tree to select taxa from. */
	VisualTreePtr m_visualTree;

	/** Viewport containing the visual tree. */
	ViewportMainPtr m_viewport;

	/** Save last selected field. */
	static std::wstring m_lastSelectedField;
};

}

#endif 
