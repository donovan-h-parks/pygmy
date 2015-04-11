///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 17 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "../core/Precompiled.hpp"

#include "PygmyLayout.h"

#include "../../bin/images/fileopen.xpm"
#include "../../bin/images/find.xpm"
#include "../../bin/images/metadata.xpm"
#include "../../bin/images/overview_tree.xpm"

///////////////////////////////////////////////////////////////////////////

PygmyLayout::PygmyLayout( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 600,400 ), wxDefaultSize );
	
	wxBoxSizer* m_mainVertSizer;
	m_mainVertSizer = new wxBoxSizer( wxVERTICAL );
	
	m_staticline = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	m_mainVertSizer->Add( m_staticline, 0, wxEXPAND | wxALL, 0 );
	
	m_splitterColourMap = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_splitterColourMap->SetSashGravity( 1 );
	m_splitterColourMap->Connect( wxEVT_IDLE, wxIdleEventHandler( PygmyLayout::m_splitterColourMapOnIdle ), NULL, this );
	m_splitterColourMap->SetMinimumPaneSize( 30 );
	
	m_panelTop = new wxPanel( m_splitterColourMap, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* m_mainHorSizer;
	m_mainHorSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_settingsSplitter = new wxSplitterWindow( m_panelTop, ID_SETTINGS_SPLITTER, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE|wxSP_NOBORDER );
	m_settingsSplitter->Connect( wxEVT_IDLE, wxIdleEventHandler( PygmyLayout::m_settingsSplitterOnIdle ), NULL, this );
	m_settingsSplitter->SetMinimumPaneSize( 200 );
	
	m_pnlSettings = new wxPanel( m_settingsSplitter, ID_PANEL_SETTINGS, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* m_sizerSettings;
	m_sizerSettings = new wxBoxSizer( wxVERTICAL );
	
	m_choiceBook = new wxChoicebook( m_pnlSettings, ID_SETTINGS_CHOICE_BOOK, wxDefaultPosition, wxDefaultSize, wxCHB_TOP );
	m_pnlTreeAppearance = new wxPanel( m_choiceBook, ID_PANEL_TREE_APPEARANCE, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* m_sizerTreeAppearance;
	m_sizerTreeAppearance = new wxBoxSizer( wxVERTICAL );
	
	m_staticLine = new wxStaticLine( m_pnlTreeAppearance, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	m_sizerTreeAppearance->Add( m_staticLine, 0, wxEXPAND, 1 );
	
	wxFlexGridSizer* m_sizeTreeAppearanceOptions;
	m_sizeTreeAppearanceOptions = new wxFlexGridSizer( 2, 2, 0, 0 );
	m_sizeTreeAppearanceOptions->SetFlexibleDirection( wxBOTH );
	m_sizeTreeAppearanceOptions->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_lblBranchStyle = new wxStaticText( m_pnlTreeAppearance, wxID_ANY, wxT("Branch style:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblBranchStyle->Wrap( -1 );
	m_sizeTreeAppearanceOptions->Add( m_lblBranchStyle, 0, wxALL, 5 );
	
	wxString m_cboBranchStyleChoices[] = { wxT("Cladogram"), wxT("Equal"), wxT("Phylogram") };
	int m_cboBranchStyleNChoices = sizeof( m_cboBranchStyleChoices ) / sizeof( wxString );
	m_cboBranchStyle = new wxChoice( m_pnlTreeAppearance, ID_CBO_BRANCH_STYLE, wxDefaultPosition, wxDefaultSize, m_cboBranchStyleNChoices, m_cboBranchStyleChoices, 0 );
	m_cboBranchStyle->SetSelection( 0 );
	m_sizeTreeAppearanceOptions->Add( m_cboBranchStyle, 0, wxALL|wxEXPAND, 5 );
	
	m_lblLineWidth = new wxStaticText( m_pnlTreeAppearance, wxID_ANY, wxT("Line weight:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblLineWidth->Wrap( -1 );
	m_sizeTreeAppearanceOptions->Add( m_lblLineWidth, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinLineWeight = new wxSpinCtrl( m_pnlTreeAppearance, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 25, 1 );
	m_sizeTreeAppearanceOptions->Add( m_spinLineWeight, 0, wxALL, 5 );
	
	m_sizerTreeAppearance->Add( m_sizeTreeAppearanceOptions, 0, wxEXPAND, 5 );
	
	wxBoxSizer* m_sizerLineWidth1;
	m_sizerLineWidth1 = new wxBoxSizer( wxHORIZONTAL );
	
	m_chkOptimizeLeafOrder = new wxCheckBox( m_pnlTreeAppearance, wxID_ANY, wxT("Optimize leaf node ordering"), wxDefaultPosition, wxDefaultSize, 0 );
	m_sizerLineWidth1->Add( m_chkOptimizeLeafOrder, 0, wxALL, 5 );
	
	m_sizerTreeAppearance->Add( m_sizerLineWidth1, 0, wxEXPAND, 5 );
	
	m_pnlTreeAppearance->SetSizer( m_sizerTreeAppearance );
	m_pnlTreeAppearance->Layout();
	m_sizerTreeAppearance->Fit( m_pnlTreeAppearance );
	m_choiceBook->AddPage( m_pnlTreeAppearance, wxT("Tree Appearance"), true );
	m_pnlOverviewAppearance = new wxPanel( m_choiceBook, ID_PANEL_OVERVIEW_APPEARANCE, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* m_sizerOverview;
	m_sizerOverview = new wxBoxSizer( wxVERTICAL );
	
	m_staticLine11 = new wxStaticLine( m_pnlOverviewAppearance, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	m_sizerOverview->Add( m_staticLine11, 0, wxEXPAND | wxALL, 1 );
	
	wxBoxSizer* m_sizerOverviewLineWidth;
	m_sizerOverviewLineWidth = new wxBoxSizer( wxHORIZONTAL );
	
	m_lblOverviewLineWidth = new wxStaticText( m_pnlOverviewAppearance, wxID_ANY, wxT("Line weight:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblOverviewLineWidth->Wrap( -1 );
	m_sizerOverviewLineWidth->Add( m_lblOverviewLineWidth, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinOverviewLineWeight = new wxSpinCtrl( m_pnlOverviewAppearance, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 25, 1 );
	m_sizerOverviewLineWidth->Add( m_spinOverviewLineWeight, 0, wxALL, 5 );
	
	m_sizerOverview->Add( m_sizerOverviewLineWidth, 0, wxEXPAND, 5 );
	
	wxBoxSizer* m_sizerOverviewOptions;
	m_sizerOverviewOptions = new wxBoxSizer( wxVERTICAL );
	
	m_chkColourOverviewTree = new wxCheckBox( m_pnlOverviewAppearance, wxID_ANY, wxT("Colour overview tree"), wxDefaultPosition, wxDefaultSize, 0 );
	m_sizerOverviewOptions->Add( m_chkColourOverviewTree, 0, wxALL, 5 );
	
	m_chkShowPositionOverlay = new wxCheckBox( m_pnlOverviewAppearance, wxID_ANY, wxT("Show position overlay"), wxDefaultPosition, wxDefaultSize, 0 );
	m_sizerOverviewOptions->Add( m_chkShowPositionOverlay, 0, wxALL, 5 );
	
	m_sizerOverview->Add( m_sizerOverviewOptions, 0, wxEXPAND, 5 );
	
	m_pnlOverviewAppearance->SetSizer( m_sizerOverview );
	m_pnlOverviewAppearance->Layout();
	m_sizerOverview->Fit( m_pnlOverviewAppearance );
	m_choiceBook->AddPage( m_pnlOverviewAppearance, wxT("Overview Appearance"), false );
	m_pnlColourMapVisualization = new wxPanel( m_choiceBook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* m_sizerColourMapVisualization;
	m_sizerColourMapVisualization = new wxBoxSizer( wxVERTICAL );
	
	m_staticLine111 = new wxStaticLine( m_pnlColourMapVisualization, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	m_sizerColourMapVisualization->Add( m_staticLine111, 0, wxEXPAND | wxALL, 1 );
	
	wxStaticBoxSizer* m_sizerColourMapGeneral;
	m_sizerColourMapGeneral = new wxStaticBoxSizer( new wxStaticBox( m_pnlColourMapVisualization, wxID_ANY, wxT("General Properties") ), wxVERTICAL );
	
	wxBoxSizer* m_sizerColourMapWidth;
	m_sizerColourMapWidth = new wxBoxSizer( wxHORIZONTAL );
	
	m_lblColourMapWidth = new wxStaticText( m_pnlColourMapVisualization, wxID_ANY, wxT("Width:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblColourMapWidth->Wrap( -1 );
	m_sizerColourMapWidth->Add( m_lblColourMapWidth, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinColourMapWidth = new wxSpinCtrl( m_pnlColourMapVisualization, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 50, 12 );
	m_sizerColourMapWidth->Add( m_spinColourMapWidth, 0, wxALL, 5 );
	
	m_sizerColourMapGeneral->Add( m_sizerColourMapWidth, 0, wxEXPAND, 5 );
	
	wxBoxSizer* m_sizerUnassignedColour;
	m_sizerUnassignedColour = new wxBoxSizer( wxHORIZONTAL );
	
	m_lblUnassignedValueColour = new wxStaticText( m_pnlColourMapVisualization, wxID_ANY, wxT("Default colour:"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_lblUnassignedValueColour->Wrap( -1 );
	m_sizerUnassignedColour->Add( m_lblUnassignedValueColour, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_defaultTreeColour = new wxColourPickerCtrl( m_pnlColourMapVisualization, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	m_sizerUnassignedColour->Add( m_defaultTreeColour, 0, wxALL, 5 );
	
	m_sizerColourMapGeneral->Add( m_sizerUnassignedColour, 0, wxEXPAND, 5 );
	
	wxBoxSizer* m_sizerShowColourMap;
	m_sizerShowColourMap = new wxBoxSizer( wxHORIZONTAL );
	
	m_chkShowColourMap = new wxCheckBox( m_pnlColourMapVisualization, wxID_ANY, wxT("Show colour map"), wxDefaultPosition, wxDefaultSize, 0 );
	m_sizerShowColourMap->Add( m_chkShowColourMap, 0, wxALL, 5 );
	
	m_sizerColourMapGeneral->Add( m_sizerShowColourMap, 0, wxEXPAND, 5 );
	
	wxBoxSizer* m_sizerShowColourMapTicks;
	m_sizerShowColourMapTicks = new wxBoxSizer( wxHORIZONTAL );
	
	m_chkShowColourMapTicks = new wxCheckBox( m_pnlColourMapVisualization, wxID_ANY, wxT("Show value tick marks"), wxDefaultPosition, wxDefaultSize, 0 );
	m_sizerShowColourMapTicks->Add( m_chkShowColourMapTicks, 0, wxALL, 5 );
	
	m_sizerColourMapGeneral->Add( m_sizerShowColourMapTicks, 0, wxEXPAND, 5 );
	
	m_sizerColourMapVisualization->Add( m_sizerColourMapGeneral, 0, wxEXPAND|wxTOP|wxBOTTOM, 5 );
	
	wxStaticBoxSizer* m_sizerMissingData;
	m_sizerMissingData = new wxStaticBoxSizer( new wxStaticBox( m_pnlColourMapVisualization, wxID_ANY, wxT("Missing Data") ), wxVERTICAL );
	
	wxBoxSizer* m_sizerMissingDataColor;
	m_sizerMissingDataColor = new wxBoxSizer( wxHORIZONTAL );
	
	m_lblMissingData = new wxStaticText( m_pnlColourMapVisualization, wxID_ANY, wxT("Colour:"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_lblMissingData->Wrap( -1 );
	m_sizerMissingDataColor->Add( m_lblMissingData, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_colourMissingData = new wxColourPickerCtrl( m_pnlColourMapVisualization, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	m_sizerMissingDataColor->Add( m_colourMissingData, 0, wxALL, 5 );
	
	m_sizerMissingData->Add( m_sizerMissingDataColor, 1, wxEXPAND, 5 );
	
	wxBoxSizer* m_sizerMissingDataRule;
	m_sizerMissingDataRule = new wxBoxSizer( wxHORIZONTAL );
	
	m_chkIgnoreLeafNodes = new wxCheckBox( m_pnlColourMapVisualization, wxID_ANY, wxT("Ignore leaf nodes"), wxDefaultPosition, wxDefaultSize, 0 );
	m_sizerMissingDataRule->Add( m_chkIgnoreLeafNodes, 0, wxALL, 5 );
	
	m_sizerMissingData->Add( m_sizerMissingDataRule, 0, wxEXPAND, 5 );
	
	m_sizerColourMapVisualization->Add( m_sizerMissingData, 0, wxEXPAND|wxTOP|wxBOTTOM, 5 );
	
	m_pnlColourMapVisualization->SetSizer( m_sizerColourMapVisualization );
	m_pnlColourMapVisualization->Layout();
	m_sizerColourMapVisualization->Fit( m_pnlColourMapVisualization );
	m_choiceBook->AddPage( m_pnlColourMapVisualization, wxT("Colour Map Visualization"), false );
	m_pnlColourMapLabels = new wxPanel( m_choiceBook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* m_sizerColourMapLabelsMain;
	m_sizerColourMapLabelsMain = new wxBoxSizer( wxVERTICAL );
	
	m_staticLine1111 = new wxStaticLine( m_pnlColourMapLabels, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	m_sizerColourMapLabelsMain->Add( m_staticLine1111, 0, wxEXPAND | wxALL, 1 );
	
	wxStaticBoxSizer* m_sizerColourMapLabels;
	m_sizerColourMapLabels = new wxStaticBoxSizer( new wxStaticBox( m_pnlColourMapLabels, wxID_ANY, wxT("Labels") ), wxVERTICAL );
	
	wxBoxSizer* m_sizerColourMapLabelColour;
	m_sizerColourMapLabelColour = new wxBoxSizer( wxHORIZONTAL );
	
	m_lblColourMapLabelColour = new wxStaticText( m_pnlColourMapLabels, wxID_ANY, wxT("Colour:"), wxDefaultPosition, wxSize( 45,-1 ), 0 );
	m_lblColourMapLabelColour->Wrap( -1 );
	m_sizerColourMapLabelColour->Add( m_lblColourMapLabelColour, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_colourMapLabelColour = new wxColourPickerCtrl( m_pnlColourMapLabels, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	m_sizerColourMapLabelColour->Add( m_colourMapLabelColour, 0, wxALL, 5 );
	
	m_sizerColourMapLabels->Add( m_sizerColourMapLabelColour, 1, wxEXPAND, 5 );
	
	wxBoxSizer* m_sizerColourMapLabelSize;
	m_sizerColourMapLabelSize = new wxBoxSizer( wxHORIZONTAL );
	
	m_lblColourMapLabelSize = new wxStaticText( m_pnlColourMapLabels, wxID_ANY, wxT("Size:"), wxDefaultPosition, wxSize( 45,-1 ), 0 );
	m_lblColourMapLabelSize->Wrap( -1 );
	m_sizerColourMapLabelSize->Add( m_lblColourMapLabelSize, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinColourMapLabelSize = new wxSpinCtrl( m_pnlColourMapLabels, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 8, 32, 12 );
	m_sizerColourMapLabelSize->Add( m_spinColourMapLabelSize, 0, wxALL, 5 );
	
	m_sizerColourMapLabels->Add( m_sizerColourMapLabelSize, 0, wxEXPAND, 5 );
	
	wxBoxSizer* m_sizerColourMapLabelDecimalPlaces;
	m_sizerColourMapLabelDecimalPlaces = new wxBoxSizer( wxHORIZONTAL );
	
	m_lblColourMapLabelPrecision = new wxStaticText( m_pnlColourMapLabels, wxID_ANY, wxT("Precision:"), wxDefaultPosition, wxSize( 45,-1 ), 0 );
	m_lblColourMapLabelPrecision->Wrap( -1 );
	m_sizerColourMapLabelDecimalPlaces->Add( m_lblColourMapLabelPrecision, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_spinColourMapLabelPrecision = new wxSpinCtrl( m_pnlColourMapLabels, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 8, 2 );
	m_sizerColourMapLabelDecimalPlaces->Add( m_spinColourMapLabelPrecision, 0, wxALL, 5 );
	
	m_sizerColourMapLabels->Add( m_sizerColourMapLabelDecimalPlaces, 1, wxEXPAND|wxTOP, 5 );
	
	wxBoxSizer* m_sizerColourMapLabelNotation;
	m_sizerColourMapLabelNotation = new wxBoxSizer( wxHORIZONTAL );
	
	
	m_sizerColourMapLabelNotation->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_chkScientific = new wxCheckBox( m_pnlColourMapLabels, wxID_ANY, wxT("Scientific notation"), wxDefaultPosition, wxDefaultSize, 0 );
	m_sizerColourMapLabelNotation->Add( m_chkScientific, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_sizerColourMapLabels->Add( m_sizerColourMapLabelNotation, 0, wxEXPAND|wxBOTTOM, 5 );
	
	m_sizerColourMapLabelsMain->Add( m_sizerColourMapLabels, 0, wxEXPAND|wxTOP|wxBOTTOM, 5 );
	
	wxStaticBoxSizer* m_sizerColourMapContinuous;
	m_sizerColourMapContinuous = new wxStaticBoxSizer( new wxStaticBox( m_pnlColourMapLabels, wxID_ANY, wxT("Continuous Colour Map") ), wxVERTICAL );
	
	wxBoxSizer* m_sizerColourMapNumberOfLabels;
	m_sizerColourMapNumberOfLabels = new wxBoxSizer( wxHORIZONTAL );
	
	m_lblColourMapNumberOfLabels = new wxStaticText( m_pnlColourMapLabels, wxID_ANY, wxT("Number of labels:"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_lblColourMapNumberOfLabels->Wrap( -1 );
	m_sizerColourMapNumberOfLabels->Add( m_lblColourMapNumberOfLabels, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinColourMapNumberOfLabels = new wxSpinCtrl( m_pnlColourMapLabels, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 2, 20, 2 );
	m_sizerColourMapNumberOfLabels->Add( m_spinColourMapNumberOfLabels, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_sizerColourMapContinuous->Add( m_sizerColourMapNumberOfLabels, 1, wxEXPAND, 5 );
	
	m_sizerColourMapLabelsMain->Add( m_sizerColourMapContinuous, 0, wxEXPAND, 5 );
	
	m_pnlColourMapLabels->SetSizer( m_sizerColourMapLabelsMain );
	m_pnlColourMapLabels->Layout();
	m_sizerColourMapLabelsMain->Fit( m_pnlColourMapLabels );
	m_choiceBook->AddPage( m_pnlColourMapLabels, wxT("Colour Map Labels"), false );
	m_pnlLeafLabels = new wxPanel( m_choiceBook, ID_PANEL_LEAF_LABELS, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* m_sizerLeafLabels;
	m_sizerLeafLabels = new wxBoxSizer( wxVERTICAL );
	
	m_staticLine1 = new wxStaticLine( m_pnlLeafLabels, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	m_sizerLeafLabels->Add( m_staticLine1, 0, wxEXPAND, 1 );
	
	wxStaticBoxSizer* m_sizerFont;
	m_sizerFont = new wxStaticBoxSizer( new wxStaticBox( m_pnlLeafLabels, wxID_ANY, wxT("Font") ), wxVERTICAL );
	
	wxBoxSizer* m_sizerFontTypeface;
	m_sizerFontTypeface = new wxBoxSizer( wxHORIZONTAL );
	
	m_lblFont = new wxStaticText( m_pnlLeafLabels, wxID_ANY, wxT("Typeface:"), wxDefaultPosition, wxSize( 50,-1 ), 0 );
	m_lblFont->Wrap( -1 );
	m_sizerFontTypeface->Add( m_lblFont, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceLeafFontChoices[] = { wxT("Arial"), wxT("Andale"), wxT("Courier"), wxT("Georgia"), wxT("Impact"), wxT("Times"), wxT("Trebuchet"), wxT("Verdana") };
	int m_choiceLeafFontNChoices = sizeof( m_choiceLeafFontChoices ) / sizeof( wxString );
	m_choiceLeafFont = new wxChoice( m_pnlLeafLabels, ID_CHOICE_FONT, wxDefaultPosition, wxDefaultSize, m_choiceLeafFontNChoices, m_choiceLeafFontChoices, 0 );
	m_choiceLeafFont->SetSelection( 2 );
	m_sizerFontTypeface->Add( m_choiceLeafFont, 0, wxALL, 5 );
	
	m_sizerFont->Add( m_sizerFontTypeface, 0, wxEXPAND, 5 );
	
	wxBoxSizer* m_sizerFontSize;
	m_sizerFontSize = new wxBoxSizer( wxHORIZONTAL );
	
	m_lblFontSize = new wxStaticText( m_pnlLeafLabels, wxID_ANY, wxT("Size:"), wxDefaultPosition, wxSize( 50,-1 ), 0 );
	m_lblFontSize->Wrap( -1 );
	m_sizerFontSize->Add( m_lblFontSize, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinLeafFontSize = new wxSpinCtrl( m_pnlLeafLabels, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 70,-1 ), wxSP_ARROW_KEYS, 8, 32, 12 );
	m_sizerFontSize->Add( m_spinLeafFontSize, 0, wxALL, 5 );
	
	m_sizerFont->Add( m_sizerFontSize, 0, wxEXPAND, 5 );
	
	wxBoxSizer* m_sizerFontColour;
	m_sizerFontColour = new wxBoxSizer( wxHORIZONTAL );
	
	m_lblFontColour = new wxStaticText( m_pnlLeafLabels, wxID_ANY, wxT("Colour:"), wxDefaultPosition, wxSize( 50,-1 ), 0 );
	m_lblFontColour->Wrap( -1 );
	m_sizerFontColour->Add( m_lblFontColour, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_colourLeafFont = new wxColourPickerCtrl( m_pnlLeafLabels, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	m_sizerFontColour->Add( m_colourLeafFont, 0, wxALL, 5 );
	
	m_sizerFont->Add( m_sizerFontColour, 0, wxEXPAND, 5 );
	
	m_sizerLeafLabels->Add( m_sizerFont, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer231;
	bSizer231 = new wxBoxSizer( wxHORIZONTAL );
	
	m_chkAppendMetadata = new wxCheckBox( m_pnlLeafLabels, wxID_ANY, wxT("Append metadata to label"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer231->Add( m_chkAppendMetadata, 0, wxALL, 5 );
	
	
	bSizer231->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_sizerLeafLabels->Add( bSizer231, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer2311;
	bSizer2311 = new wxBoxSizer( wxHORIZONTAL );
	
	m_chkShowLeafLabels = new wxCheckBox( m_pnlLeafLabels, wxID_ANY, wxT("Show labels"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2311->Add( m_chkShowLeafLabels, 0, wxALL, 5 );
	
	
	bSizer2311->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_sizerLeafLabels->Add( bSizer2311, 0, wxEXPAND, 5 );
	
	m_pnlLeafLabels->SetSizer( m_sizerLeafLabels );
	m_pnlLeafLabels->Layout();
	m_sizerLeafLabels->Fit( m_pnlLeafLabels );
	m_choiceBook->AddPage( m_pnlLeafLabels, wxT("Leaf Labels"), false );
	m_pnlInternalNodeLabels = new wxPanel( m_choiceBook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* m_sizerInternalNodeLabelsMain;
	m_sizerInternalNodeLabelsMain = new wxBoxSizer( wxVERTICAL );
	
	m_staticLine11111 = new wxStaticLine( m_pnlInternalNodeLabels, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	m_sizerInternalNodeLabelsMain->Add( m_staticLine11111, 0, wxEXPAND | wxALL, 1 );
	
	wxStaticBoxSizer* m_sizerInternalNodeLabels;
	m_sizerInternalNodeLabels = new wxStaticBoxSizer( new wxStaticBox( m_pnlInternalNodeLabels, wxID_ANY, wxT("Labels") ), wxVERTICAL );
	
	wxBoxSizer* m_sizerInternalNodeLabelsField;
	m_sizerInternalNodeLabelsField = new wxBoxSizer( wxHORIZONTAL );
	
	m_lblInternalNodeLabelsField = new wxStaticText( m_pnlInternalNodeLabels, wxID_ANY, wxT("Field:"), wxDefaultPosition, wxSize( 45,-1 ), 0 );
	m_lblInternalNodeLabelsField->Wrap( -1 );
	m_sizerInternalNodeLabelsField->Add( m_lblInternalNodeLabelsField, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_cboInternalNodeLabelsField = new wxComboBox( m_pnlInternalNodeLabels, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY|wxCB_SORT );
	m_cboInternalNodeLabelsField->Append( wxT("Bootstrap") );
	m_cboInternalNodeLabelsField->Append( wxT("Height") );
	m_cboInternalNodeLabelsField->Append( wxT("Distance") );
	m_cboInternalNodeLabelsField->Append( wxT("Name") );
	m_cboInternalNodeLabelsField->Append( wxT("Number of Leaves") );
	m_cboInternalNodeLabelsField->Append( wxT("Parsimony Data") );
	m_sizerInternalNodeLabelsField->Add( m_cboInternalNodeLabelsField, 0, wxALL, 5 );
	
	m_sizerInternalNodeLabels->Add( m_sizerInternalNodeLabelsField, 1, wxEXPAND, 5 );
	
	wxBoxSizer* m_sizerInternalLabelPos;
	m_sizerInternalLabelPos = new wxBoxSizer( wxHORIZONTAL );
	
	m_lblInternalLabelPos = new wxStaticText( m_pnlInternalNodeLabels, wxID_ANY, wxT("Position:"), wxDefaultPosition, wxSize( 45,-1 ), 0 );
	m_lblInternalLabelPos->Wrap( -1 );
	m_sizerInternalLabelPos->Add( m_lblInternalLabelPos, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_cboInternalLabelPos = new wxComboBox( m_pnlInternalNodeLabels, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY|wxCB_SORT );
	m_cboInternalLabelPos->Append( wxT("Right") );
	m_cboInternalLabelPos->Append( wxT("Above Left") );
	m_sizerInternalLabelPos->Add( m_cboInternalLabelPos, 0, wxALL, 5 );
	
	m_sizerInternalNodeLabels->Add( m_sizerInternalLabelPos, 1, wxEXPAND, 5 );
	
	wxBoxSizer* m_sizerInternalNodeLabelsColour;
	m_sizerInternalNodeLabelsColour = new wxBoxSizer( wxHORIZONTAL );
	
	m_lblInternalNodeLabelsColour = new wxStaticText( m_pnlInternalNodeLabels, wxID_ANY, wxT("Colour:"), wxDefaultPosition, wxSize( 45,-1 ), 0 );
	m_lblInternalNodeLabelsColour->Wrap( -1 );
	m_sizerInternalNodeLabelsColour->Add( m_lblInternalNodeLabelsColour, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_internalNodeLabelColour = new wxColourPickerCtrl( m_pnlInternalNodeLabels, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	m_sizerInternalNodeLabelsColour->Add( m_internalNodeLabelColour, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_sizerInternalNodeLabels->Add( m_sizerInternalNodeLabelsColour, 1, wxEXPAND, 5 );
	
	wxBoxSizer* m_sizerInternalNodeLabelSize;
	m_sizerInternalNodeLabelSize = new wxBoxSizer( wxHORIZONTAL );
	
	m_lblInternalNodeLabelSize = new wxStaticText( m_pnlInternalNodeLabels, wxID_ANY, wxT("Size:"), wxDefaultPosition, wxSize( 45,-1 ), 0 );
	m_lblInternalNodeLabelSize->Wrap( -1 );
	m_sizerInternalNodeLabelSize->Add( m_lblInternalNodeLabelSize, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinInternalNodeLabelSize = new wxSpinCtrl( m_pnlInternalNodeLabels, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 8, 32, 12 );
	m_sizerInternalNodeLabelSize->Add( m_spinInternalNodeLabelSize, 0, wxALL, 5 );
	
	m_sizerInternalNodeLabels->Add( m_sizerInternalNodeLabelSize, 0, wxEXPAND, 5 );
	
	wxBoxSizer* m_sizerInternalNodeLabelPrecision;
	m_sizerInternalNodeLabelPrecision = new wxBoxSizer( wxHORIZONTAL );
	
	m_lblInternalNodeLabelPrecision = new wxStaticText( m_pnlInternalNodeLabels, wxID_ANY, wxT("Precision:"), wxDefaultPosition, wxSize( 45,-1 ), 0 );
	m_lblInternalNodeLabelPrecision->Wrap( -1 );
	m_sizerInternalNodeLabelPrecision->Add( m_lblInternalNodeLabelPrecision, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_spinInternalNodeLabelPrecision = new wxSpinCtrl( m_pnlInternalNodeLabels, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 8, 2 );
	m_sizerInternalNodeLabelPrecision->Add( m_spinInternalNodeLabelPrecision, 0, wxALL, 5 );
	
	m_sizerInternalNodeLabels->Add( m_sizerInternalNodeLabelPrecision, 1, wxEXPAND|wxTOP, 5 );
	
	wxBoxSizer* m_sizerInternalNodeLabelScientificNotation;
	m_sizerInternalNodeLabelScientificNotation = new wxBoxSizer( wxHORIZONTAL );
	
	
	m_sizerInternalNodeLabelScientificNotation->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_chkInternalNodeLabelScientificNotation = new wxCheckBox( m_pnlInternalNodeLabels, wxID_ANY, wxT("Scientific notation"), wxDefaultPosition, wxDefaultSize, 0 );
	m_sizerInternalNodeLabelScientificNotation->Add( m_chkInternalNodeLabelScientificNotation, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_sizerInternalNodeLabels->Add( m_sizerInternalNodeLabelScientificNotation, 0, wxEXPAND|wxBOTTOM, 5 );
	
	m_sizerInternalNodeLabelsMain->Add( m_sizerInternalNodeLabels, 0, wxEXPAND|wxTOP|wxBOTTOM, 5 );
	
	m_chkShowInternalLabels = new wxCheckBox( m_pnlInternalNodeLabels, wxID_ANY, wxT("Show internal labels"), wxDefaultPosition, wxDefaultSize, 0 );
	m_sizerInternalNodeLabelsMain->Add( m_chkShowInternalLabels, 0, wxALL, 5 );
	
	m_pnlInternalNodeLabels->SetSizer( m_sizerInternalNodeLabelsMain );
	m_pnlInternalNodeLabels->Layout();
	m_sizerInternalNodeLabelsMain->Fit( m_pnlInternalNodeLabels );
	m_choiceBook->AddPage( m_pnlInternalNodeLabels, wxT("Internal Node Labels"), false );
	m_pnlMouseSettings = new wxPanel( m_choiceBook, ID_PANEL_MOUSE_SETTINGS, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* m_sizerMouseSettings;
	m_sizerMouseSettings = new wxBoxSizer( wxVERTICAL );
	
	m_staticLine2 = new wxStaticLine( m_pnlMouseSettings, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	m_sizerMouseSettings->Add( m_staticLine2, 0, wxEXPAND, 1 );
	
	wxBoxSizer* m_sizerScrollSensitivity;
	m_sizerScrollSensitivity = new wxBoxSizer( wxVERTICAL );
	
	m_lblScrollSensitibity = new wxStaticText( m_pnlMouseSettings, wxID_ANY, wxT("Scroll sensitivity:"), wxDefaultPosition, wxSize( 110,-1 ), 0 );
	m_lblScrollSensitibity->Wrap( -1 );
	m_sizerScrollSensitivity->Add( m_lblScrollSensitibity, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_sliderScrollSensitivity = new wxSlider( m_pnlMouseSettings, wxID_ANY, 30, 1, 200, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	m_sizerScrollSensitivity->Add( m_sliderScrollSensitivity, 0, wxALL|wxEXPAND, 5 );
	
	m_sizerMouseSettings->Add( m_sizerScrollSensitivity, 0, wxEXPAND, 5 );
	
	wxBoxSizer* m_sizerTranslationSensitivity;
	m_sizerTranslationSensitivity = new wxBoxSizer( wxVERTICAL );
	
	m_lblTranslationSensitivity = new wxStaticText( m_pnlMouseSettings, wxID_ANY, wxT("Translation sensitivity:"), wxDefaultPosition, wxSize( 110,-1 ), 0 );
	m_lblTranslationSensitivity->Wrap( -1 );
	m_sizerTranslationSensitivity->Add( m_lblTranslationSensitivity, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_sliderTranslationSensitibity = new wxSlider( m_pnlMouseSettings, wxID_ANY, 30, 1, 200, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	m_sizerTranslationSensitivity->Add( m_sliderTranslationSensitibity, 0, wxALL|wxEXPAND, 5 );
	
	m_sizerMouseSettings->Add( m_sizerTranslationSensitivity, 0, wxEXPAND, 5 );
	
	wxBoxSizer* m_sizerZoomSensitivity;
	m_sizerZoomSensitivity = new wxBoxSizer( wxVERTICAL );
	
	m_lblZoomSensitivity = new wxStaticText( m_pnlMouseSettings, wxID_ANY, wxT("Zoom sensitivity:"), wxDefaultPosition, wxSize( 110,-1 ), 0 );
	m_lblZoomSensitivity->Wrap( -1 );
	m_sizerZoomSensitivity->Add( m_lblZoomSensitivity, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_sliderZoomSensitivity = new wxSlider( m_pnlMouseSettings, wxID_ANY, 10, 1, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	m_sizerZoomSensitivity->Add( m_sliderZoomSensitivity, 0, wxALL|wxEXPAND, 5 );
	
	m_sizerMouseSettings->Add( m_sizerZoomSensitivity, 0, wxEXPAND, 5 );
	
	m_pnlMouseSettings->SetSizer( m_sizerMouseSettings );
	m_pnlMouseSettings->Layout();
	m_sizerMouseSettings->Fit( m_pnlMouseSettings );
	m_choiceBook->AddPage( m_pnlMouseSettings, wxT("Mouse Settings"), false );
	m_sizerSettings->Add( m_choiceBook, 1, wxEXPAND | wxALL, 5 );
	
	m_pnlSettings->SetSizer( m_sizerSettings );
	m_pnlSettings->Layout();
	m_sizerSettings->Fit( m_pnlSettings );
	m_pnlMain = new wxPanel( m_settingsSplitter, ID_PANEL_MAIN, wxDefaultPosition, wxDefaultSize, 0 );
	wxBoxSizer* m_mainSizer;
	m_mainSizer = new wxBoxSizer( wxVERTICAL );
	
	m_splitterViewportTools = new wxSplitterWindow( m_pnlMain, ID_SPLITTER_VIEWPORT_TOOLS, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE|wxSP_NOBORDER|wxNO_BORDER );
	m_splitterViewportTools->SetSashGravity( 1 );
	m_splitterViewportTools->Connect( wxEVT_IDLE, wxIdleEventHandler( PygmyLayout::m_splitterViewportToolsOnIdle ), NULL, this );
	m_splitterViewportTools->SetMinimumPaneSize( 50 );
	
	m_pnlViewports = new wxPanel( m_splitterViewportTools, ID_PANEL_VIEWPORTS, wxDefaultPosition, wxSize( -1,-1 ), wxNO_BORDER );
	wxBoxSizer* m_sizerViewports;
	m_sizerViewports = new wxBoxSizer( wxVERTICAL );
	
	m_splitterOverview = new wxSplitterWindow( m_pnlViewports, ID_SPLITTER_LEFT, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_LIVE_UPDATE|wxSP_NOBORDER|wxNO_BORDER );
	m_splitterOverview->Connect( wxEVT_IDLE, wxIdleEventHandler( PygmyLayout::m_splitterOverviewOnIdle ), NULL, this );
	m_splitterOverview->SetMinimumPaneSize( 50 );
	
	m_pnlOverview = new wxPanel( m_splitterOverview, ID_PANEL_OVERVIEW, wxDefaultPosition, wxSize( -1,-1 ), wxNO_BORDER );
	m_pnlViewport = new wxPanel( m_splitterOverview, ID_PANEL_VIEWPORT, wxDefaultPosition, wxSize( -1,-1 ), wxNO_BORDER|wxWANTS_CHARS );
	m_splitterOverview->SplitVertically( m_pnlOverview, m_pnlViewport, 100 );
	m_sizerViewports->Add( m_splitterOverview, 1, wxEXPAND, 0 );
	
	m_pnlViewports->SetSizer( m_sizerViewports );
	m_pnlViewports->Layout();
	m_sizerViewports->Fit( m_pnlViewports );
	m_pnlSearchText = new wxPanel( m_splitterViewportTools, ID_PANEL_TOOLS, wxDefaultPosition, wxSize( -1,-1 ), wxNO_BORDER|wxTAB_TRAVERSAL );
	wxBoxSizer* m_sizerToolsHor;
	m_sizerToolsHor = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticLineTextSeach = new wxStaticLine( m_pnlSearchText, ID_STATIC_LINE_TEXT_SEARCH, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL|wxSIMPLE_BORDER );
	m_sizerToolsHor->Add( m_staticLineTextSeach, 0, wxEXPAND | wxALL, 0 );
	
	wxBoxSizer* m_sizerTools;
	m_sizerTools = new wxBoxSizer( wxVERTICAL );
	
	m_lstSearch = new wxListBox( m_pnlSearchText, ID_SEARCH_LIST, wxDefaultPosition, wxSize( -1,-1 ), 0, NULL, wxLB_NEEDED_SB|wxLB_SINGLE|wxLB_SORT ); 
	m_sizerTools->Add( m_lstSearch, 1, wxALL|wxEXPAND, 2 );
	
	m_cboSearchType = new wxComboBox( m_pnlSearchText, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	m_cboSearchType->Append( wxT("contains") );
	m_cboSearchType->Append( wxT("starts with") );
	m_cboSearchType->Append( wxT("ends with") );
	m_cboSearchType->Append( wxT("matches") );
	m_sizerTools->Add( m_cboSearchType, 0, wxEXPAND|wxALL, 2 );
	
	m_txtSearch = new wxTextCtrl( m_pnlSearchText, ID_TEXT_SEARCH, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_sizerTools->Add( m_txtSearch, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 2 );
	
	m_sizerToolsHor->Add( m_sizerTools, 1, wxEXPAND, 5 );
	
	m_pnlSearchText->SetSizer( m_sizerToolsHor );
	m_pnlSearchText->Layout();
	m_sizerToolsHor->Fit( m_pnlSearchText );
	m_splitterViewportTools->SplitVertically( m_pnlViewports, m_pnlSearchText, 154 );
	m_mainSizer->Add( m_splitterViewportTools, 1, wxEXPAND, 0 );
	
	m_pnlMain->SetSizer( m_mainSizer );
	m_pnlMain->Layout();
	m_mainSizer->Fit( m_pnlMain );
	m_settingsSplitter->SplitVertically( m_pnlSettings, m_pnlMain, 242 );
	m_mainHorSizer->Add( m_settingsSplitter, 1, wxEXPAND, 5 );
	
	m_panelTop->SetSizer( m_mainHorSizer );
	m_panelTop->Layout();
	m_mainHorSizer->Fit( m_panelTop );
	m_pnlColourMap = new wxPanel( m_splitterColourMap, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer( wxVERTICAL );
	
	m_staticline7 = new wxStaticLine( m_pnlColourMap, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer23->Add( m_staticline7, 0, wxEXPAND | wxALL, 0 );
	
	wxBoxSizer* m_mainSizerColourMap;
	m_mainSizerColourMap = new wxBoxSizer( wxHORIZONTAL );
	
	
	m_mainSizerColourMap->Add( 0, 0, 1, 0, 5 );
	
	wxBoxSizer* m_sizerField;
	m_sizerField = new wxBoxSizer( wxHORIZONTAL );
	
	m_lblField = new wxStaticText( m_pnlColourMap, wxID_ANY, wxT("Field:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblField->Wrap( -1 );
	m_sizerField->Add( m_lblField, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_cboField = new wxComboBox( m_pnlColourMap, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_DROPDOWN|wxCB_READONLY|wxCB_SORT ); 
	m_sizerField->Add( m_cboField, 1, wxALL, 5 );
	
	m_mainSizerColourMap->Add( m_sizerField, 0, 0, 5 );
	
	wxBoxSizer* m_sizerDataType;
	m_sizerDataType = new wxBoxSizer( wxHORIZONTAL );
	
	m_lblDataType = new wxStaticText( m_pnlColourMap, wxID_ANY, wxT("Treat data as:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblDataType->Wrap( -1 );
	m_sizerDataType->Add( m_lblDataType, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_cboTreatDataAs = new wxComboBox( m_pnlColourMap, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_DROPDOWN|wxCB_READONLY|wxCB_SORT );
	m_cboTreatDataAs->Append( wxT("Categorical") );
	m_cboTreatDataAs->Append( wxT("Continuous") );
	m_cboTreatDataAs->Append( wxT("Discrete") );
	m_sizerDataType->Add( m_cboTreatDataAs, 1, wxALL, 5 );
	
	m_mainSizerColourMap->Add( m_sizerDataType, 0, 0, 5 );
	
	wxBoxSizer* m_sizerColourMap;
	m_sizerColourMap = new wxBoxSizer( wxHORIZONTAL );
	
	m_lblColourMap = new wxStaticText( m_pnlColourMap, wxID_ANY, wxT("Colour map:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblColourMap->Wrap( -1 );
	m_sizerColourMap->Add( m_lblColourMap, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_cboColourMap = new wxComboBox( m_pnlColourMap, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_DROPDOWN|wxCB_READONLY|wxCB_SORT ); 
	m_sizerColourMap->Add( m_cboColourMap, 1, wxALL, 5 );
	
	m_mainSizerColourMap->Add( m_sizerColourMap, 0, 0, 5 );
	
	bSizer23->Add( m_mainSizerColourMap, 1, wxEXPAND, 5 );
	
	m_pnlColourMap->SetSizer( bSizer23 );
	m_pnlColourMap->Layout();
	bSizer23->Fit( m_pnlColourMap );
	m_splitterColourMap->SplitHorizontally( m_panelTop, m_pnlColourMap, 10000 );
	m_mainVertSizer->Add( m_splitterColourMap, 1, wxEXPAND, 5 );
	
	this->SetSizer( m_mainVertSizer );
	this->Layout();
	m_menuBar = new wxMenuBar( 0 );
	m_mnuFile = new wxMenu();
	wxMenuItem* m_mnuFileOpenTree;
	m_mnuFileOpenTree = new wxMenuItem( m_mnuFile, ID_FILE_OPEN_LEFT, wxString( wxT("Open &tree...") ) + wxT('\t') + wxT("Ctrl+T"), wxT("Load tree file"), wxITEM_NORMAL );
	m_mnuFile->Append( m_mnuFileOpenTree );
	
	wxMenuItem* m_mnuFileOpenMetadata;
	m_mnuFileOpenMetadata = new wxMenuItem( m_mnuFile, ID_FILE_OPEN_METADATA, wxString( wxT("Open metadata...") ) + wxT('\t') + wxT("Ctrl+M"), wxT("Load metadata file"), wxITEM_NORMAL );
	m_mnuFile->Append( m_mnuFileOpenMetadata );
	
	wxMenuItem* m_separator1;
	m_separator1 = m_mnuFile->AppendSeparator();
	
	wxMenuItem* m_mnuFileExportTree;
	m_mnuFileExportTree = new wxMenuItem( m_mnuFile, ID_FILE_EXPORT_TREE, wxString( wxT("Export tree...") ) + wxT('\t') + wxT("Ctrl+E"), wxT("Save current tree to file"), wxITEM_NORMAL );
	m_mnuFile->Append( m_mnuFileExportTree );
	
	wxMenuItem* m_mnuFileExportSubtree;
	m_mnuFileExportSubtree = new wxMenuItem( m_mnuFile, ID_FILE_EXPORT_SUBTREE, wxString( wxT("Export subtree...") ) , wxT("Save selected subtree to file"), wxITEM_NORMAL );
	m_mnuFile->Append( m_mnuFileExportSubtree );
	
	wxMenuItem* m_separator2;
	m_separator2 = m_mnuFile->AppendSeparator();
	
	wxMenuItem* m_mnuFileSaveImage;
	m_mnuFileSaveImage = new wxMenuItem( m_mnuFile, ID_FILE_SAVE_IMAGE, wxString( wxT("Save viewport as image...") ) , wxT("Create image from viewport"), wxITEM_NORMAL );
	m_mnuFile->Append( m_mnuFileSaveImage );
	
	wxMenuItem* m_mnuFileSaveOverview;
	m_mnuFileSaveOverview = new wxMenuItem( m_mnuFile, ID_FILE_SAVE_OVERFILE, wxString( wxT("Save overview tree as image...") ) , wxT("Create image from overview viewport"), wxITEM_NORMAL );
	m_mnuFile->Append( m_mnuFileSaveOverview );
	
	wxMenuItem* m_separator3;
	m_separator3 = m_mnuFile->AppendSeparator();
	
	wxMenuItem* m_mnuFileExit;
	m_mnuFileExit = new wxMenuItem( m_mnuFile, ID_FILE_EXIT, wxString( wxT("E&xit") ) , wxT("Quit program"), wxITEM_NORMAL );
	m_mnuFile->Append( m_mnuFileExit );
	
	m_menuBar->Append( m_mnuFile, wxT("&File") ); 
	
	m_mnuView = new wxMenu();
	wxMenuItem* m_mnuViewOverview;
	m_mnuViewOverview = new wxMenuItem( m_mnuView, ID_MNU_VIEW_OVERVIEW_WINDOW, wxString( wxT("Overview panel") ) + wxT('\t') + wxT("Ctrl+Shift+O"), wxT("Show/hide overview panel"), wxITEM_CHECK );
	m_mnuView->Append( m_mnuViewOverview );
	m_mnuViewOverview->Check( true );
	
	wxMenuItem* m_separator4;
	m_separator4 = m_mnuView->AppendSeparator();
	
	wxMenuItem* m_mnuViewColourMap;
	m_mnuViewColourMap = new wxMenuItem( m_mnuView, ID_MNU_COLOUR_MAP_PANEL, wxString( wxT("Colour map panel") ) + wxT('\t') + wxT("Ctrl+Shift+C"), wxT("Show/hide colour map panel"), wxITEM_CHECK );
	m_mnuView->Append( m_mnuViewColourMap );
	m_mnuViewColourMap->Check( true );
	
	wxMenuItem* m_separator5;
	m_separator5 = m_mnuView->AppendSeparator();
	
	wxMenuItem* m_mnuViewSearch;
	m_mnuViewSearch = new wxMenuItem( m_mnuView, ID_MNU_VIEW_SEARCH, wxString( wxT("Search panel") ) + wxT('\t') + wxT("Ctrl+Shift+F"), wxT("Show/hide search panel"), wxITEM_CHECK );
	m_mnuView->Append( m_mnuViewSearch );
	
	wxMenuItem* m_separator6;
	m_separator6 = m_mnuView->AppendSeparator();
	
	wxMenuItem* m_mnuViewSettings;
	m_mnuViewSettings = new wxMenuItem( m_mnuView, ID_MNU_VIEW_SETTINGS, wxString( wxT("Settings panel") ) + wxT('\t') + wxT("Ctrl+Shift+S"), wxT("Show/hide settings panel"), wxITEM_CHECK );
	m_mnuView->Append( m_mnuViewSettings );
	
	m_menuBar->Append( m_mnuView, wxT("&View") ); 
	
	m_mnuManipulate = new wxMenu();
	wxMenuItem* m_mnuManipulateCollapse;
	m_mnuManipulateCollapse = new wxMenuItem( m_mnuManipulate, ID_MNU_TREE_COLLAPSE, wxString( wxT("Collapse weakly supported bipartitions") ) + wxT('\t') + wxT("Ctrl+C"), wxT("Collapse nodes based on bootstrap support"), wxITEM_NORMAL );
	m_mnuManipulate->Append( m_mnuManipulateCollapse );
	
	wxMenuItem* m_mnuManipulateProject;
	m_mnuManipulateProject = new wxMenuItem( m_mnuManipulate, ID_MNU_TREE_PROJECT, wxString( wxT("Project tree") ) + wxT('\t') + wxT("Ctrl+P"), wxT("Project tree onto a specified set of leaf nodes"), wxITEM_NORMAL );
	m_mnuManipulate->Append( m_mnuManipulateProject );
	
	wxMenuItem* m_mnuManipulateRestoreTree;
	m_mnuManipulateRestoreTree = new wxMenuItem( m_mnuManipulate, ID_MNU_TREE_RESTORE, wxString( wxT("Restore original tree") ) + wxT('\t') + wxT("Ctrl+O"), wxT("Restor original tree"), wxITEM_NORMAL );
	m_mnuManipulate->Append( m_mnuManipulateRestoreTree );
	
	wxMenuItem* m_separator8;
	m_separator8 = m_mnuManipulate->AppendSeparator();
	
	wxMenuItem* m_mnuManipulateReroot;
	m_mnuManipulateReroot = new wxMenuItem( m_mnuManipulate, ID_MNU_TREE_REROOT, wxString( wxT("Reroot tree") ) + wxT('\t') + wxT("Ctrl+R"), wxT("Reroot tree on specified branch"), wxITEM_NORMAL );
	m_mnuManipulate->Append( m_mnuManipulateReroot );
	
	wxMenuItem* m_mnuManipulateCollapseExandSubtree;
	m_mnuManipulateCollapseExandSubtree = new wxMenuItem( m_mnuManipulate, wxID_ANY, wxString( wxT("Collapse/expand subtree") ) , wxT("Collapse/expand a subtree to/from a triangle"), wxITEM_NORMAL );
	m_mnuManipulate->Append( m_mnuManipulateCollapseExandSubtree );
	
	m_menuBar->Append( m_mnuManipulate, wxT("&Manipulate") ); 
	
	m_mnuAnalysis = new wxMenu();
	wxMenuItem* m_mnuAnalysisParsimony;
	m_mnuAnalysisParsimony = new wxMenuItem( m_mnuAnalysis, ID_MNU_ANALYSIS_PARSIMONY, wxString( wxT("Parsimony analysis") ) , wxEmptyString, wxITEM_NORMAL );
	m_mnuAnalysis->Append( m_mnuAnalysisParsimony );
	
	m_menuBar->Append( m_mnuAnalysis, wxT("Analysis") ); 
	
	m_mnuHelp = new wxMenu();
	wxMenuItem* m_mnuHelpAbout;
	m_mnuHelpAbout = new wxMenuItem( m_mnuHelp, ID_HELP_ABOUT, wxString( wxT("&About...") ) , wxEmptyString, wxITEM_NORMAL );
	m_mnuHelp->Append( m_mnuHelpAbout );
	
	m_menuBar->Append( m_mnuHelp, wxT("&Help") ); 
	
	this->SetMenuBar( m_menuBar );
	
	m_statusBar = this->CreateStatusBar( 4, wxST_SIZEGRIP, ID_STATUS_BAR );
	m_toolBar = this->CreateToolBar( wxTB_FLAT|wxTB_HORIZONTAL, wxID_ANY );
	m_toolBar->SetToolBitmapSize( wxSize( 16,16 ) );
	m_toolBar->AddTool( ID_TB_OPEN_TREE, wxT("Open tree"), wxBitmap( fileopen_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Open tree file"), wxT("Open tree file") ); 
	m_toolBar->AddTool( ID_OPEN_METADATA, wxT("Open metadata"), wxBitmap( metadata_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Load metadata file"), wxT("Load metadata file") ); 
	m_toolBar->AddSeparator(); 
	m_toolBar->AddTool( ID_TB_VIEW_OVERVIEW_WINDOW, wxT("tool"), wxBitmap( overview_tree_xpm ), wxNullBitmap, wxITEM_CHECK, wxT("Show/hide overview panel"), wxT("Show/hide overview panel") ); 
	m_toolBar->AddTool( ID_TB_COLOUR_MAP_PANEL, wxT("tool"), wxBitmap(pygmy::App::Inst().GetExeDir() +  wxT("images/colour_map.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_CHECK, wxT("Show/hide colour map panel"), wxT("Show/hide colour map panel") ); 
	m_toolBar->AddTool( ID_TB_VIEW_SEARCH, wxT("tool"), wxBitmap( find_xpm ), wxNullBitmap, wxITEM_CHECK, wxT("Find leaf node"), wxT("Find leaf node") ); 
	m_toolBar->AddTool( ID_TB_VIEW_SETTINGS, wxT("tool"), wxBitmap(pygmy::App::Inst().GetExeDir() +  wxT("images/settings.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_CHECK, wxT("Show/hide settings panel"), wxT("Show/hide settings panel") ); 
	m_toolBar->AddSeparator(); 
	m_toolBar->AddTool( ID_TB_HELP_ABOUT, wxT("tool"), wxBitmap(pygmy::App::Inst().GetExeDir() +  wxT("images/about.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString ); 
	m_toolBar->Realize();
	
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CHAR, wxKeyEventHandler( PygmyLayout::OnCharFromKeyboard ) );
	this->Connect( wxEVT_ERASE_BACKGROUND, wxEraseEventHandler( PygmyLayout::OnEraseBackground ) );
	m_cboBranchStyle->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PygmyLayout::OnBranchStyleChanged ), NULL, this );
	m_spinLineWeight->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PygmyLayout::OnLineWidth ), NULL, this );
	m_chkOptimizeLeafOrder->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PygmyLayout::OnOptimizeLeafNodeOrdering ), NULL, this );
	m_spinOverviewLineWeight->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PygmyLayout::OnOverviewLineWidth ), NULL, this );
	m_chkColourOverviewTree->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PygmyLayout::OnColourOverviewTree ), NULL, this );
	m_chkShowPositionOverlay->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PygmyLayout::OnShowPositionOverlay ), NULL, this );
	m_spinColourMapWidth->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PygmyLayout::OnColourMapWidth ), NULL, this );
	m_defaultTreeColour->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( PygmyLayout::OnDefaultTreeColour ), NULL, this );
	m_chkShowColourMap->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PygmyLayout::OnShowColourMap ), NULL, this );
	m_chkShowColourMapTicks->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PygmyLayout::OnShowColourMapTicks ), NULL, this );
	m_colourMissingData->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( PygmyLayout::OnMissingDataColour ), NULL, this );
	m_chkIgnoreLeafNodes->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PygmyLayout::OnIgnoreLeafNodes ), NULL, this );
	m_colourMapLabelColour->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( PygmyLayout::OnColourMapLabelColour ), NULL, this );
	m_spinColourMapLabelSize->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PygmyLayout::OnColourMapLabelSize ), NULL, this );
	m_spinColourMapLabelPrecision->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PygmyLayout::OnColourMapLabelPrecision ), NULL, this );
	m_chkScientific->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PygmyLayout::OnScientificNotation ), NULL, this );
	m_spinColourMapNumberOfLabels->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PygmyLayout::OnColourMapNumberOfLabels ), NULL, this );
	m_choiceLeafFont->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PygmyLayout::OnLeafFontTypeface ), NULL, this );
	m_spinLeafFontSize->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PygmyLayout::OnLeafFontSize ), NULL, this );
	m_colourLeafFont->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( PygmyLayout::OnLeafFontColour ), NULL, this );
	m_chkAppendMetadata->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PygmyLayout::OnAppendMetadata ), NULL, this );
	m_chkShowLeafLabels->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PygmyLayout::OnShowLeafLabels ), NULL, this );
	m_cboInternalNodeLabelsField->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( PygmyLayout::OnInternalNodeField ), NULL, this );
	m_cboInternalLabelPos->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( PygmyLayout::OnInternalLabelPos ), NULL, this );
	m_internalNodeLabelColour->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( PygmyLayout::OnInternalNodeColour ), NULL, this );
	m_spinInternalNodeLabelSize->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PygmyLayout::OnInternalNodeSize ), NULL, this );
	m_spinInternalNodeLabelPrecision->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PygmyLayout::OnInternalNodePrecision ), NULL, this );
	m_chkInternalNodeLabelScientificNotation->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PygmyLayout::OnInternalNodeScientific ), NULL, this );
	m_chkShowInternalLabels->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PygmyLayout::OnInternalNodeShow ), NULL, this );
	m_sliderScrollSensitivity->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( PygmyLayout::OnScrollSensitivity ), NULL, this );
	m_sliderScrollSensitivity->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( PygmyLayout::OnScrollSensitivity ), NULL, this );
	m_sliderScrollSensitivity->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( PygmyLayout::OnScrollSensitivity ), NULL, this );
	m_sliderScrollSensitivity->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( PygmyLayout::OnScrollSensitivity ), NULL, this );
	m_sliderScrollSensitivity->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( PygmyLayout::OnScrollSensitivity ), NULL, this );
	m_sliderScrollSensitivity->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( PygmyLayout::OnScrollSensitivity ), NULL, this );
	m_sliderScrollSensitivity->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( PygmyLayout::OnScrollSensitivity ), NULL, this );
	m_sliderScrollSensitivity->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( PygmyLayout::OnScrollSensitivity ), NULL, this );
	m_sliderScrollSensitivity->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( PygmyLayout::OnScrollSensitivity ), NULL, this );
	m_sliderTranslationSensitibity->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( PygmyLayout::OnTranslationSensitivity ), NULL, this );
	m_sliderTranslationSensitibity->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( PygmyLayout::OnTranslationSensitivity ), NULL, this );
	m_sliderTranslationSensitibity->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( PygmyLayout::OnTranslationSensitivity ), NULL, this );
	m_sliderTranslationSensitibity->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( PygmyLayout::OnTranslationSensitivity ), NULL, this );
	m_sliderTranslationSensitibity->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( PygmyLayout::OnTranslationSensitivity ), NULL, this );
	m_sliderTranslationSensitibity->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( PygmyLayout::OnTranslationSensitivity ), NULL, this );
	m_sliderTranslationSensitibity->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( PygmyLayout::OnTranslationSensitivity ), NULL, this );
	m_sliderTranslationSensitibity->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( PygmyLayout::OnTranslationSensitivity ), NULL, this );
	m_sliderTranslationSensitibity->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( PygmyLayout::OnTranslationSensitivity ), NULL, this );
	m_sliderZoomSensitivity->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( PygmyLayout::OnZoomSensitivity ), NULL, this );
	m_sliderZoomSensitivity->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( PygmyLayout::OnZoomSensitivity ), NULL, this );
	m_sliderZoomSensitivity->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( PygmyLayout::OnZoomSensitivity ), NULL, this );
	m_sliderZoomSensitivity->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( PygmyLayout::OnZoomSensitivity ), NULL, this );
	m_sliderZoomSensitivity->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( PygmyLayout::OnZoomSensitivity ), NULL, this );
	m_sliderZoomSensitivity->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( PygmyLayout::OnZoomSensitivity ), NULL, this );
	m_sliderZoomSensitivity->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( PygmyLayout::OnZoomSensitivity ), NULL, this );
	m_sliderZoomSensitivity->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( PygmyLayout::OnZoomSensitivity ), NULL, this );
	m_sliderZoomSensitivity->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( PygmyLayout::OnZoomSensitivity ), NULL, this );
	m_lstSearch->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( PygmyLayout::OnSearchClick ), NULL, this );
	m_cboSearchType->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( PygmyLayout::OnChangeSearchType ), NULL, this );
	m_txtSearch->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( PygmyLayout::OnSearchText ), NULL, this );
	m_cboField->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( PygmyLayout::OnChangeField ), NULL, this );
	m_cboTreatDataAs->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( PygmyLayout::OnTreatDataAs ), NULL, this );
	m_cboColourMap->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( PygmyLayout::OnChangeColourMap ), NULL, this );
	this->Connect( m_mnuFileOpenTree->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnFileOpenTree ) );
	this->Connect( m_mnuFileOpenMetadata->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnFileOpenMetadata ) );
	this->Connect( m_mnuFileExportTree->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnFileExportTree ) );
	this->Connect( m_mnuFileExportSubtree->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnFileExportSubtree ) );
	this->Connect( m_mnuFileSaveImage->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnFileSaveImage ) );
	this->Connect( m_mnuFileSaveOverview->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnFileSaveOverview ) );
	this->Connect( m_mnuFileExit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnFileExit ) );
	this->Connect( m_mnuViewOverview->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnViewOverviewWindowMnu ) );
	this->Connect( m_mnuViewColourMap->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnViewColourMapMnu ) );
	this->Connect( m_mnuViewSearch->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnViewSearchTextMnu ) );
	this->Connect( m_mnuViewSettings->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnViewSettingsMnu ) );
	this->Connect( m_mnuManipulateCollapse->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnCollapseNode ) );
	this->Connect( m_mnuManipulateProject->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnProjectTree ) );
	this->Connect( m_mnuManipulateRestoreTree->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnRestoreTree ) );
	this->Connect( m_mnuManipulateReroot->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnRerootTree ) );
	this->Connect( m_mnuManipulateCollapseExandSubtree->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnCollapseExandSubtree ) );
	this->Connect( m_mnuAnalysisParsimony->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnAnalysisParsimony ) );
	this->Connect( m_mnuHelpAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnHelpAbout ) );
	this->Connect( ID_TB_OPEN_TREE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( PygmyLayout::OnFileOpenTree ) );
	this->Connect( ID_OPEN_METADATA, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( PygmyLayout::OnFileOpenMetadata ) );
	this->Connect( ID_TB_VIEW_OVERVIEW_WINDOW, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( PygmyLayout::OnViewOverviewWindowTb ) );
	this->Connect( ID_TB_COLOUR_MAP_PANEL, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( PygmyLayout::OnViewColourMapTb ) );
	this->Connect( ID_TB_VIEW_SEARCH, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( PygmyLayout::OnViewSearchTextTb ) );
	this->Connect( ID_TB_VIEW_SETTINGS, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( PygmyLayout::OnViewSettingsTb ) );
	this->Connect( ID_TB_HELP_ABOUT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( PygmyLayout::OnHelpAbout ) );
}

PygmyLayout::~PygmyLayout()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CHAR, wxKeyEventHandler( PygmyLayout::OnCharFromKeyboard ) );
	this->Disconnect( wxEVT_ERASE_BACKGROUND, wxEraseEventHandler( PygmyLayout::OnEraseBackground ) );
	m_cboBranchStyle->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PygmyLayout::OnBranchStyleChanged ), NULL, this );
	m_spinLineWeight->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PygmyLayout::OnLineWidth ), NULL, this );
	m_chkOptimizeLeafOrder->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PygmyLayout::OnOptimizeLeafNodeOrdering ), NULL, this );
	m_spinOverviewLineWeight->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PygmyLayout::OnOverviewLineWidth ), NULL, this );
	m_chkColourOverviewTree->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PygmyLayout::OnColourOverviewTree ), NULL, this );
	m_chkShowPositionOverlay->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PygmyLayout::OnShowPositionOverlay ), NULL, this );
	m_spinColourMapWidth->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PygmyLayout::OnColourMapWidth ), NULL, this );
	m_defaultTreeColour->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( PygmyLayout::OnDefaultTreeColour ), NULL, this );
	m_chkShowColourMap->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PygmyLayout::OnShowColourMap ), NULL, this );
	m_chkShowColourMapTicks->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PygmyLayout::OnShowColourMapTicks ), NULL, this );
	m_colourMissingData->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( PygmyLayout::OnMissingDataColour ), NULL, this );
	m_chkIgnoreLeafNodes->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PygmyLayout::OnIgnoreLeafNodes ), NULL, this );
	m_colourMapLabelColour->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( PygmyLayout::OnColourMapLabelColour ), NULL, this );
	m_spinColourMapLabelSize->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PygmyLayout::OnColourMapLabelSize ), NULL, this );
	m_spinColourMapLabelPrecision->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PygmyLayout::OnColourMapLabelPrecision ), NULL, this );
	m_chkScientific->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PygmyLayout::OnScientificNotation ), NULL, this );
	m_spinColourMapNumberOfLabels->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PygmyLayout::OnColourMapNumberOfLabels ), NULL, this );
	m_choiceLeafFont->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PygmyLayout::OnLeafFontTypeface ), NULL, this );
	m_spinLeafFontSize->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PygmyLayout::OnLeafFontSize ), NULL, this );
	m_colourLeafFont->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( PygmyLayout::OnLeafFontColour ), NULL, this );
	m_chkAppendMetadata->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PygmyLayout::OnAppendMetadata ), NULL, this );
	m_chkShowLeafLabels->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PygmyLayout::OnShowLeafLabels ), NULL, this );
	m_cboInternalNodeLabelsField->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( PygmyLayout::OnInternalNodeField ), NULL, this );
	m_cboInternalLabelPos->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( PygmyLayout::OnInternalLabelPos ), NULL, this );
	m_internalNodeLabelColour->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( PygmyLayout::OnInternalNodeColour ), NULL, this );
	m_spinInternalNodeLabelSize->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PygmyLayout::OnInternalNodeSize ), NULL, this );
	m_spinInternalNodeLabelPrecision->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PygmyLayout::OnInternalNodePrecision ), NULL, this );
	m_chkInternalNodeLabelScientificNotation->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PygmyLayout::OnInternalNodeScientific ), NULL, this );
	m_chkShowInternalLabels->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PygmyLayout::OnInternalNodeShow ), NULL, this );
	m_sliderScrollSensitivity->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( PygmyLayout::OnScrollSensitivity ), NULL, this );
	m_sliderScrollSensitivity->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( PygmyLayout::OnScrollSensitivity ), NULL, this );
	m_sliderScrollSensitivity->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( PygmyLayout::OnScrollSensitivity ), NULL, this );
	m_sliderScrollSensitivity->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( PygmyLayout::OnScrollSensitivity ), NULL, this );
	m_sliderScrollSensitivity->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( PygmyLayout::OnScrollSensitivity ), NULL, this );
	m_sliderScrollSensitivity->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( PygmyLayout::OnScrollSensitivity ), NULL, this );
	m_sliderScrollSensitivity->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( PygmyLayout::OnScrollSensitivity ), NULL, this );
	m_sliderScrollSensitivity->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( PygmyLayout::OnScrollSensitivity ), NULL, this );
	m_sliderScrollSensitivity->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( PygmyLayout::OnScrollSensitivity ), NULL, this );
	m_sliderTranslationSensitibity->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( PygmyLayout::OnTranslationSensitivity ), NULL, this );
	m_sliderTranslationSensitibity->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( PygmyLayout::OnTranslationSensitivity ), NULL, this );
	m_sliderTranslationSensitibity->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( PygmyLayout::OnTranslationSensitivity ), NULL, this );
	m_sliderTranslationSensitibity->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( PygmyLayout::OnTranslationSensitivity ), NULL, this );
	m_sliderTranslationSensitibity->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( PygmyLayout::OnTranslationSensitivity ), NULL, this );
	m_sliderTranslationSensitibity->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( PygmyLayout::OnTranslationSensitivity ), NULL, this );
	m_sliderTranslationSensitibity->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( PygmyLayout::OnTranslationSensitivity ), NULL, this );
	m_sliderTranslationSensitibity->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( PygmyLayout::OnTranslationSensitivity ), NULL, this );
	m_sliderTranslationSensitibity->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( PygmyLayout::OnTranslationSensitivity ), NULL, this );
	m_sliderZoomSensitivity->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( PygmyLayout::OnZoomSensitivity ), NULL, this );
	m_sliderZoomSensitivity->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( PygmyLayout::OnZoomSensitivity ), NULL, this );
	m_sliderZoomSensitivity->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( PygmyLayout::OnZoomSensitivity ), NULL, this );
	m_sliderZoomSensitivity->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( PygmyLayout::OnZoomSensitivity ), NULL, this );
	m_sliderZoomSensitivity->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( PygmyLayout::OnZoomSensitivity ), NULL, this );
	m_sliderZoomSensitivity->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( PygmyLayout::OnZoomSensitivity ), NULL, this );
	m_sliderZoomSensitivity->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( PygmyLayout::OnZoomSensitivity ), NULL, this );
	m_sliderZoomSensitivity->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( PygmyLayout::OnZoomSensitivity ), NULL, this );
	m_sliderZoomSensitivity->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( PygmyLayout::OnZoomSensitivity ), NULL, this );
	m_lstSearch->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( PygmyLayout::OnSearchClick ), NULL, this );
	m_cboSearchType->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( PygmyLayout::OnChangeSearchType ), NULL, this );
	m_txtSearch->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( PygmyLayout::OnSearchText ), NULL, this );
	m_cboField->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( PygmyLayout::OnChangeField ), NULL, this );
	m_cboTreatDataAs->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( PygmyLayout::OnTreatDataAs ), NULL, this );
	m_cboColourMap->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( PygmyLayout::OnChangeColourMap ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnFileOpenTree ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnFileOpenMetadata ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnFileExportTree ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnFileExportSubtree ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnFileSaveImage ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnFileSaveOverview ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnFileExit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnViewOverviewWindowMnu ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnViewColourMapMnu ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnViewSearchTextMnu ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnViewSettingsMnu ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnCollapseNode ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnProjectTree ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnRestoreTree ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnRerootTree ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnCollapseExandSubtree ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnAnalysisParsimony ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( PygmyLayout::OnHelpAbout ) );
	this->Disconnect( ID_TB_OPEN_TREE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( PygmyLayout::OnFileOpenTree ) );
	this->Disconnect( ID_OPEN_METADATA, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( PygmyLayout::OnFileOpenMetadata ) );
	this->Disconnect( ID_TB_VIEW_OVERVIEW_WINDOW, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( PygmyLayout::OnViewOverviewWindowTb ) );
	this->Disconnect( ID_TB_COLOUR_MAP_PANEL, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( PygmyLayout::OnViewColourMapTb ) );
	this->Disconnect( ID_TB_VIEW_SEARCH, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( PygmyLayout::OnViewSearchTextTb ) );
	this->Disconnect( ID_TB_VIEW_SETTINGS, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( PygmyLayout::OnViewSettingsTb ) );
	this->Disconnect( ID_TB_HELP_ABOUT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( PygmyLayout::OnHelpAbout ) );
	
}
