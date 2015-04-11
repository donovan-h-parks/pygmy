///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 17 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __PygmyLayout__
#define __PygmyLayout__

#include <wx/statline.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/spinctrl.h>
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/clrpicker.h>
#include <wx/statbox.h>
#include <wx/combobox.h>
#include <wx/slider.h>
#include <wx/choicebk.h>
#include <wx/splitter.h>
#include <wx/listbox.h>
#include <wx/textctrl.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/toolbar.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class PygmyLayout
///////////////////////////////////////////////////////////////////////////////
class PygmyLayout : public wxFrame 
{
	private:
	
	protected:
		enum
		{
			ID_MAIN_FRAME = 1000,
			ID_SETTINGS_SPLITTER,
			ID_PANEL_SETTINGS,
			ID_SETTINGS_CHOICE_BOOK,
			ID_PANEL_TREE_APPEARANCE,
			ID_CBO_BRANCH_STYLE,
			ID_PANEL_OVERVIEW_APPEARANCE,
			ID_PANEL_LEAF_LABELS,
			ID_CHOICE_FONT,
			ID_PANEL_MOUSE_SETTINGS,
			ID_PANEL_MAIN,
			ID_SPLITTER_VIEWPORT_TOOLS,
			ID_PANEL_VIEWPORTS,
			ID_SPLITTER_LEFT,
			ID_PANEL_OVERVIEW,
			ID_PANEL_VIEWPORT,
			ID_PANEL_TOOLS,
			ID_STATIC_LINE_TEXT_SEARCH,
			ID_SEARCH_LIST,
			ID_TEXT_SEARCH,
			ID_MENUBAR,
			ID_FILE_OPEN_LEFT,
			ID_FILE_OPEN_METADATA,
			ID_FILE_EXPORT_TREE,
			ID_FILE_EXPORT_SUBTREE,
			ID_FILE_SAVE_IMAGE,
			ID_FILE_SAVE_OVERFILE,
			ID_FILE_EXIT,
			ID_MNU_VIEW_OVERVIEW_WINDOW,
			ID_MNU_COLOUR_MAP_PANEL,
			ID_MNU_VIEW_SEARCH,
			ID_MNU_VIEW_SETTINGS,
			ID_MNU_TREE_COLLAPSE,
			ID_MNU_TREE_PROJECT,
			ID_MNU_TREE_RESTORE,
			ID_MNU_TREE_REROOT,
			ID_MNU_ANALYSIS_PARSIMONY,
			ID_HELP_ABOUT,
			ID_STATUS_BAR,
			ID_TB_OPEN_TREE,
			ID_OPEN_METADATA,
			ID_TB_VIEW_OVERVIEW_WINDOW,
			ID_TB_COLOUR_MAP_PANEL,
			ID_TB_VIEW_SEARCH,
			ID_TB_VIEW_SETTINGS,
			ID_TB_HELP_ABOUT,
		};
		
		wxStaticLine* m_staticline;
		wxSplitterWindow* m_splitterColourMap;
		wxPanel* m_panelTop;
		wxSplitterWindow* m_settingsSplitter;
		wxPanel* m_pnlSettings;
		wxChoicebook* m_choiceBook;
		wxPanel* m_pnlTreeAppearance;
		wxStaticLine* m_staticLine;
		wxStaticText* m_lblBranchStyle;
		wxChoice* m_cboBranchStyle;
		wxStaticText* m_lblLineWidth;
		wxSpinCtrl* m_spinLineWeight;
		wxCheckBox* m_chkOptimizeLeafOrder;
		wxPanel* m_pnlOverviewAppearance;
		wxStaticLine* m_staticLine11;
		wxStaticText* m_lblOverviewLineWidth;
		wxSpinCtrl* m_spinOverviewLineWeight;
		wxCheckBox* m_chkColourOverviewTree;
		wxCheckBox* m_chkShowPositionOverlay;
		wxPanel* m_pnlColourMapVisualization;
		wxStaticLine* m_staticLine111;
		wxStaticText* m_lblColourMapWidth;
		wxSpinCtrl* m_spinColourMapWidth;
		wxStaticText* m_lblUnassignedValueColour;
		wxColourPickerCtrl* m_defaultTreeColour;
		wxCheckBox* m_chkShowColourMap;
		wxCheckBox* m_chkShowColourMapTicks;
		wxStaticText* m_lblMissingData;
		wxColourPickerCtrl* m_colourMissingData;
		wxCheckBox* m_chkIgnoreLeafNodes;
		wxPanel* m_pnlColourMapLabels;
		wxStaticLine* m_staticLine1111;
		wxStaticText* m_lblColourMapLabelColour;
		wxColourPickerCtrl* m_colourMapLabelColour;
		wxStaticText* m_lblColourMapLabelSize;
		wxSpinCtrl* m_spinColourMapLabelSize;
		wxStaticText* m_lblColourMapLabelPrecision;
		wxSpinCtrl* m_spinColourMapLabelPrecision;
		
		wxCheckBox* m_chkScientific;
		wxStaticText* m_lblColourMapNumberOfLabels;
		wxSpinCtrl* m_spinColourMapNumberOfLabels;
		wxPanel* m_pnlLeafLabels;
		wxStaticLine* m_staticLine1;
		wxStaticText* m_lblFont;
		wxChoice* m_choiceLeafFont;
		wxStaticText* m_lblFontSize;
		wxSpinCtrl* m_spinLeafFontSize;
		wxStaticText* m_lblFontColour;
		wxColourPickerCtrl* m_colourLeafFont;
		wxCheckBox* m_chkAppendMetadata;
		
		wxCheckBox* m_chkShowLeafLabels;
		
		wxPanel* m_pnlInternalNodeLabels;
		wxStaticLine* m_staticLine11111;
		wxStaticText* m_lblInternalNodeLabelsField;
		wxComboBox* m_cboInternalNodeLabelsField;
		wxStaticText* m_lblInternalLabelPos;
		wxComboBox* m_cboInternalLabelPos;
		wxStaticText* m_lblInternalNodeLabelsColour;
		wxColourPickerCtrl* m_internalNodeLabelColour;
		wxStaticText* m_lblInternalNodeLabelSize;
		wxSpinCtrl* m_spinInternalNodeLabelSize;
		wxStaticText* m_lblInternalNodeLabelPrecision;
		wxSpinCtrl* m_spinInternalNodeLabelPrecision;
		
		wxCheckBox* m_chkInternalNodeLabelScientificNotation;
		wxCheckBox* m_chkShowInternalLabels;
		wxPanel* m_pnlMouseSettings;
		wxStaticLine* m_staticLine2;
		wxStaticText* m_lblScrollSensitibity;
		wxSlider* m_sliderScrollSensitivity;
		wxStaticText* m_lblTranslationSensitivity;
		wxSlider* m_sliderTranslationSensitibity;
		wxStaticText* m_lblZoomSensitivity;
		wxSlider* m_sliderZoomSensitivity;
		wxPanel* m_pnlMain;
		wxSplitterWindow* m_splitterViewportTools;
		wxPanel* m_pnlViewports;
		wxSplitterWindow* m_splitterOverview;
		wxPanel* m_pnlOverview;
		wxPanel* m_pnlViewport;
		wxPanel* m_pnlSearchText;
		wxStaticLine* m_staticLineTextSeach;
		wxListBox* m_lstSearch;
		wxComboBox* m_cboSearchType;
		wxTextCtrl* m_txtSearch;
		wxPanel* m_pnlColourMap;
		wxStaticLine* m_staticline7;
		
		wxStaticText* m_lblField;
		wxComboBox* m_cboField;
		wxStaticText* m_lblDataType;
		wxComboBox* m_cboTreatDataAs;
		wxStaticText* m_lblColourMap;
		wxComboBox* m_cboColourMap;
		wxMenuBar* m_menuBar;
		wxMenu* m_mnuFile;
		wxMenu* m_mnuView;
		wxMenu* m_mnuManipulate;
		wxMenu* m_mnuAnalysis;
		wxMenu* m_mnuHelp;
		wxStatusBar* m_statusBar;
		wxToolBar* m_toolBar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCharFromKeyboard( wxKeyEvent& event ) { event.Skip(); }
		virtual void OnEraseBackground( wxEraseEvent& event ) { event.Skip(); }
		virtual void OnBranchStyleChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLineWidth( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnOptimizeLeafNodeOrdering( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOverviewLineWidth( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnColourOverviewTree( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnShowPositionOverlay( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnColourMapWidth( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnDefaultTreeColour( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnShowColourMap( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnShowColourMapTicks( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMissingDataColour( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnIgnoreLeafNodes( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnColourMapLabelColour( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnColourMapLabelSize( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnColourMapLabelPrecision( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnScientificNotation( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnColourMapNumberOfLabels( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnLeafFontTypeface( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLeafFontSize( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnLeafFontColour( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnAppendMetadata( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnShowLeafLabels( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnInternalNodeField( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnInternalLabelPos( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnInternalNodeColour( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnInternalNodeSize( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnInternalNodePrecision( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnInternalNodeScientific( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnInternalNodeShow( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnScrollSensitivity( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnTranslationSensitivity( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnZoomSensitivity( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnSearchClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChangeSearchType( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSearchText( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChangeField( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTreatDataAs( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChangeColourMap( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFileOpenTree( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFileOpenMetadata( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFileExportTree( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFileExportSubtree( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFileSaveImage( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFileSaveOverview( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFileExit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewOverviewWindowMnu( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewColourMapMnu( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewSearchTextMnu( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewSettingsMnu( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCollapseNode( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnProjectTree( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRestoreTree( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRerootTree( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCollapseExandSubtree( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAnalysisParsimony( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnHelpAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewOverviewWindowTb( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewColourMapTb( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewSearchTextTb( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewSettingsTb( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		PygmyLayout( wxWindow* parent, wxWindowID id = ID_MAIN_FRAME, const wxString& title = wxT("Pygmy"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL|wxWANTS_CHARS );
		~PygmyLayout();
		
		void m_splitterColourMapOnIdle( wxIdleEvent& )
		{
			m_splitterColourMap->SetSashPosition( 10000 );
			m_splitterColourMap->Disconnect( wxEVT_IDLE, wxIdleEventHandler( PygmyLayout::m_splitterColourMapOnIdle ), NULL, this );
		}
		
		void m_settingsSplitterOnIdle( wxIdleEvent& )
		{
			m_settingsSplitter->SetSashPosition( 242 );
			m_settingsSplitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( PygmyLayout::m_settingsSplitterOnIdle ), NULL, this );
		}
		
		void m_splitterViewportToolsOnIdle( wxIdleEvent& )
		{
			m_splitterViewportTools->SetSashPosition( 154 );
			m_splitterViewportTools->Disconnect( wxEVT_IDLE, wxIdleEventHandler( PygmyLayout::m_splitterViewportToolsOnIdle ), NULL, this );
		}
		
		void m_splitterOverviewOnIdle( wxIdleEvent& )
		{
			m_splitterOverview->SetSashPosition( 100 );
			m_splitterOverview->Disconnect( wxEVT_IDLE, wxIdleEventHandler( PygmyLayout::m_splitterOverviewOnIdle ), NULL, this );
		}
	
};

#endif //__PygmyLayout__
