///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 16 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __TaxaSelectionLayout__
#define __TaxaSelectionLayout__

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/combobox.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/listbox.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

namespace pygmy
{
	///////////////////////////////////////////////////////////////////////////////
	/// Class TaxaSelectionLayout
	///////////////////////////////////////////////////////////////////////////////
	class TaxaSelectionLayout : public wxDialog 
	{
		private:
		
		protected:
			enum
			{
				ID_BTN_OK = 1000,
				ID_BTN_CANCEL,
			};
			
			wxStaticText* m_lblField;
			wxComboBox* m_cboFields;
			wxStaticLine* m_staticline1;
			wxStaticText* m_lblAllValues;
			wxListBox* m_lstInactiveValues;
			
			wxButton* m_btnAdd;
			wxButton* m_btnRemove;
			
			wxStaticText* m_lblActiveValues;
			wxListBox* m_lstActiveValues;
			
			wxButton* m_btnOK;
			wxButton* m_btnApply;
			wxButton* m_btnCancel;
			
			// Virtual event handlers, overide them in your derived class
			virtual void OnFieldChange( wxCommandEvent& event ){ event.Skip(); }
			virtual void OnAdd( wxCommandEvent& event ){ event.Skip(); }
			virtual void OnRemove( wxCommandEvent& event ){ event.Skip(); }
			virtual void OnOK( wxCommandEvent& event ){ event.Skip(); }
			virtual void OnApply( wxCommandEvent& event ){ event.Skip(); }
			virtual void OnCancel( wxCommandEvent& event ){ event.Skip(); }
			
		
		public:
			TaxaSelectionLayout( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _T("Project Tree onto Active Taxa"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
			~TaxaSelectionLayout();
		
	};
	
} // namespace pygmy

#endif //__TaxaSelectionLayout__
