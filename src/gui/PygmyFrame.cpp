//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../gui/PygmyFrame.hpp"
#include "../gui/TaxaSelectionDlg.hpp"

#include "../core/State.hpp"
#include "../core/App.hpp"
#include "../core/ViewportMain.hpp"
#include "../core/ViewportOverview.hpp"
#include "../core/VisualTree.hpp"
#include "../core/MetadataIO.hpp"
#include "../core/MetadataInfo.hpp"
#include "../core/VisualColourMap.hpp"
#include "../core/TextSearch.hpp"
#include "../core/NewickIO.hpp"
#include "../core/OptimizeLeafOrder.hpp"

#include "../glUtils/Font.hpp"

#include "../utils/StringTools.hpp"
#include "../utils/ColourMapManager.hpp"
#include "../utils/ColourMap.hpp"
#include "../utils/ColourMapDiscrete.hpp"
#include "../utils/ColourMapContinuous.hpp"

using namespace pygmy;
using namespace utils;
using namespace std;

PygmyFrame::PygmyFrame(wxWindow* parent): PygmyLayout(parent),
		m_viewport(new ViewportMain((wxPanel*)m_pnlViewport, ID_PANEL_VIEWPORT, wxPoint(0,0), m_pnlViewport->GetSize())),
		m_overview(new ViewportOverview((wxPanel*)m_pnlOverview, ID_PANEL_OVERVIEW, wxPoint(0,0), m_pnlOverview->GetSize())),
		m_textSearch(new TextSearch()), m_colourMapManager(new utils::ColourMapManager())
{
	const int SEARCH_TEXT_PANEL_WIDTH = 200;
	const int OVERVIEW_PANEL_WIDTH = 100;
	const int SETTINGS_PANEL_WIDTH = 200;
	const int COLOUR_MAP_PANEL_HEIGHT = 30;

	// setup sizers so main viewport and overview canvas automatically expand
	wxBoxSizer* sizerViewport = new wxBoxSizer( wxVERTICAL );
	sizerViewport->Add(m_viewport, 1, wxEXPAND);
	m_pnlViewport->SetSizer(sizerViewport);

	wxBoxSizer* sizerOverview = new wxBoxSizer( wxVERTICAL );
	sizerOverview->Add(m_overview, 1, wxEXPAND);
	m_pnlOverview->SetSizer(sizerOverview);

	// initialize the text search filter
	m_textSearch->DataFilter()->SetColour(Colour(0.8f, 0.9f, 0.9f, 1.0f));
	m_overview->SearchFilter(m_textSearch->DataFilter());

	// link main viewport and overview canvas
	m_viewport->OverviewViewport(m_overview);
	m_overview->MainViewport(m_viewport);

	// set the default position of each splitter sash		
	m_splitterViewportTools->Unsplit();									// start with text search window hidden
	m_searchTextPanelWidth = SEARCH_TEXT_PANEL_WIDTH;		// default size of the text search window when it is first shown
	
	m_settingsSplitter->Unsplit(m_pnlSettings);
	m_settingsPanelWidth = SETTINGS_PANEL_WIDTH;

	m_colourMapPanelHeight = COLOUR_MAP_PANEL_HEIGHT;
	m_toolBar->ToggleTool(ID_TB_COLOUR_MAP_PANEL, true);

	m_overviewPanelWidth = OVERVIEW_PANEL_WIDTH;
	m_toolBar->ToggleTool(ID_TB_VIEW_OVERVIEW_WINDOW, true);

	// initialize status bar
	int n = m_statusBar->GetFieldsCount();
	int* widths = new int[n];
	widths[0] = 150;
	for(int i = 1; i < n; ++i)
		widths[i] = -1;	// variable width field
	m_statusBar->SetStatusWidths(n, widths);
	delete[] widths;

	SetDefaultValues();

	// load all colour maps
	m_colourMapManager->LoadColourMaps(App::Inst().GetExeDir() + _T("colourMaps"));

	m_cboSearchType->SetValue(_T("contains"));

	// attach viewport mouse events to local functions
	m_viewport->SignalMouseLeftClick(boost::bind(&PygmyFrame::SigViewportMouseLeftClick, this, _1));
	m_viewport->SignalMouseRightClick(boost::bind(&PygmyFrame::SigViewportMouseRightClick, this, _1));
}


PygmyFrame::~PygmyFrame()
{
	
}

void PygmyFrame::SetDefaultValues()
{
	// *** Tree Appearance
	m_spinLineWeight->SetValue(State::Inst().GetLineWidth());
	m_chkOptimizeLeafOrder->SetValue(State::Inst().GetOptimizeLeafNodeOrdering());

	// *** Leaf Labels
	std::wstring fontFile = State::Inst().GetFontFile();
	fontFile = fontFile.substr(fontFile.find('/')+1, fontFile.find('.')-fontFile.find('/')-1);
	m_choiceLeafFont->SetStringSelection(fontFile);
	
	m_spinLeafFontSize->SetValue(State::Inst().GetTreeFontSize());

	Colour colour = State::Inst().GetTreeFontColour();
	m_colourLeafFont->SetColour(wxColour(colour.GetRedInt(), colour.GetGreenInt(), colour.GetBlueInt()));

	m_chkAppendMetadata->SetValue(State::Inst().GetShowMetadataLabels());
	m_chkShowLeafLabels->SetValue(State::Inst().GetShowLeafLabels());

	// *** Overview Appearance
	m_spinOverviewLineWeight->SetValue(State::Inst().GetOverviewLineWidth());	
	m_chkColourOverviewTree->SetValue(State::Inst().GetColourOverviewTree());
	m_chkShowPositionOverlay->SetValue(State::Inst().GetOverviewPositionOverlay());

	// *** Colour Map Visualization
	m_spinColourMapWidth->SetValue(State::Inst().GetColourMapWidth());
	m_chkShowColourMap->SetValue(State::Inst().GetShowColourMapVis());
	m_chkShowColourMapTicks->SetValue(State::Inst().GetShowColourMapTickMarks());

	colour = State::Inst().GetDefaultTreeColour();
	ColourMap::SetDefaultColour(colour);
	m_defaultTreeColour->SetColour(wxColour(colour.GetRedInt(), colour.GetGreenInt(), colour.GetBlueInt()));

	colour = State::Inst().GetColourMissingData();
	m_colourMissingData->SetColour(wxColour(colour.GetRedInt(), colour.GetGreenInt(), colour.GetBlueInt()));
	m_chkIgnoreLeafNodes->SetValue(State::Inst().GetIgnoreMissingData());


	// *** Colour Map Labels
	colour = State::Inst().GetColourMapFontColour();
	m_colourMapLabelColour->SetColour(wxColour(colour.GetRedInt(), colour.GetGreenInt(), colour.GetBlueInt()));
	m_spinColourMapLabelSize->SetValue(State::Inst().GetColourMapFontSize());
	m_spinColourMapLabelPrecision->SetValue(State::Inst().GetColourMapFontPrecision());
	m_spinColourMapNumberOfLabels->SetValue(State::Inst().GetColourMapValuesToDisplay());
	m_chkScientific->SetValue(State::Inst().GetColourMapFontScientific());


	//*** Internal Node Labels
	colour = State::Inst().GetInternalNodeFontColour();
	m_internalNodeLabelColour->SetColour(wxColour(colour.GetRedInt(), colour.GetGreenInt(), colour.GetBlueInt()));
	m_cboInternalNodeLabelsField->SetValue(State::Inst().GetInternalNodeField());
	m_cboInternalLabelPos->SetValue(State::Inst().GetInternalLabelPos());
	m_spinInternalNodeLabelSize->SetValue(State::Inst().GetInternalNodeFontSize());
	m_spinInternalNodeLabelPrecision->SetValue(State::Inst().GetInternalNodeFontPrecision());
	m_chkInternalNodeLabelScientificNotation->SetValue(State::Inst().GetInternalNodeFontScientific());
	m_chkShowInternalLabels->SetValue(State::Inst().GetShowInternalLabels());

	
	// *** Mouse Settings
	m_sliderScrollSensitivity->SetValue(State::Inst().GetScrollSensitivity());
	m_sliderTranslationSensitibity->SetValue(State::Inst().GetTranslationSensitivity()*10);
	m_sliderZoomSensitivity->SetValue(State::Inst().GetZoomSensitivity()*1000);
}

void PygmyFrame::OnFileExit(wxCommandEvent& event)
{
	Close(true);
}

void PygmyFrame::OnHelpAbout( wxCommandEvent& event )
{
	wxAboutDialogInfo info;
	info.SetName(_T("Pygmy"));
	info.SetVersion(_T("0.02 - Beta"));
	info.SetCopyright(_T("Copyright (c) 2009, Donovan Parks (donovan.parks@gmail.com)"));
	info.SetDescription(_T("Relating phylogenies to environmental variables."));
	info.AddDeveloper(_T("Donovan Parks"));
	info.SetIcon(wxIcon(_T("images/Tree.ico"), wxBITMAP_TYPE_ICO));
	info.SetLicence(_T("The contents of this file are licensed under the ") 
										_T("Attribution-ShareAlike Creative Commons License: ")
										_T("http://creativecommons.org/licenses/by-sa/3.0/"));
	info.SetWebSite(_T("http://dparks.wikidot.com/"));
	info.AddArtist(_T("Tree icon designed by: Fasticon.com"));
	info.AddArtist(_T("Select toolbar icons designed by: famfamfam.com"));

	::wxAboutBox(info);
}

void PygmyFrame::OnFileOpenTree(wxCommandEvent& event)
{
	// *** Prompt user for file they wish to open
	wxFileDialog* openDlg = new wxFileDialog(this, _T("Open file..."), _T(""), _T(""), _T("*.*"), 
														wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_CHANGE_DIR);

	wxString wildcards = _T("Newick file (*.tre)|*.tre|All files (*.*)|*.*");
 	openDlg->SetWildcard(wildcards);

  if(openDlg->ShowModal() != wxID_OK)
  {
		openDlg->Destroy();
		return;
  }

  wstring path = openDlg->GetDirectory();
  wstring filename = openDlg->GetFilename();

	openDlg->Destroy();

	OpenTree(filename);
}

void PygmyFrame::OpenTree(const wstring& filename)
{
	// *** Read in tree
	Tree<NodePhylo>::Ptr tree(new Tree<NodePhylo>());
	NewickIO newickIO;
	bool bRead = newickIO.Read(tree, filename);
	
	if(!bRead)
	{
		wxMessageBox(_T("Failed to read tree from file."), _T("Failed to read file"), wxOK | wxICON_INFORMATION);
		return;
	}

	// *** Update GUI to reflect properties of graph
	std::wstring statusText =	_T("Nodes = ") + utils::StringTools::ToString(tree->GetNumberOfNodes()) + _T(", ")
														_T("Leaves = ") + utils::StringTools::ToString(tree->GetNumberOfLeaves()) + _T(", ")
														_T("Height = ") + utils::StringTools::ToString(tree->GetRootNode()->GetHeight());

	m_statusBar->SetStatusText(statusText, 1);

	// *** Initialize text search object
	std::vector<NodePhylo*> leafNodes = tree->GetLeaves();
	m_textSearch->Clear();
	foreach(NodePhylo* leaf, leafNodes)
	{
		m_textSearch->Add(leaf->GetName(), leaf->GetId());
	}

	SearchText(_T(""), _T("starts with"));	// fill search list box with all words

	//*** Set new tree
	m_visualTree.reset(new VisualTree(tree));

	//*** Assign existing colour map and metadata to new tree
	if(m_visualColourMap)
	{
		m_visualTree->SetMetadataInfo(m_metadataInfo);
		m_visualTree->SetVisualColourMap(m_visualColourMap);
		m_viewport->SetColourMap(m_visualColourMap);
	}
	
	// *** Inform viewport and overview canvas of the new tree
	if(m_cboBranchStyle->GetStringSelection() == "Cladogram")
		m_visualTree->SetBranchStyle(VisualTree::CLADOGRAM_BRANCHES);
	else if(m_cboBranchStyle->GetStringSelection() == "Equal")
		m_visualTree->SetBranchStyle(VisualTree::EQUAL_BRANCHES);
	else if(m_cboBranchStyle->GetStringSelection() == "Phylogram")
		m_visualTree->SetBranchStyle(VisualTree::PHYLOGRAM_BRANCHES);

	m_visualTree->SetSearchFilter(m_textSearch->DataFilter());

	m_visualTree->Layout();

	m_overview->SetTree(m_visualTree);
	m_viewport->SetTree(m_visualTree);	

	App::Inst().SetTitle(filename);
}

void PygmyFrame::OnFileOpenMetadata( wxCommandEvent& event )
{
	if(!m_visualTree)
	{
		utils::Log::Inst().Warning(_T("A tree must be present before metadata can be loaded."));
		return;
	}

	// *** Prompt user for file they wish to open
	wxFileDialog* openDlg = new wxFileDialog(this, _T("Open file..."), _T(""), _T(""), _T("*.*"), 
														wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_CHANGE_DIR);

	wxString wildcards = _T("Metadata (*.csv)|*.csv|All files (*.*)|*.*");
 	openDlg->SetWildcard(wildcards);

  if(openDlg->ShowModal() != wxID_OK)
  {
		openDlg->Destroy();
		return;
  }

  wstring path = openDlg->GetDirectory();
  wstring filename = openDlg->GetFilename();

	openDlg->Destroy();

	// *** Read in metadata
	m_metadataInfo.reset(new MetadataInfo());
	MetadataIO::Read(filename, m_visualTree, m_metadataInfo);
	m_visualTree->SetMetadataInfo(m_metadataInfo);

	// *** Assign visual colour map
	m_visualColourMap.reset(new VisualColourMap());	
	m_visualColourMap->SetMetadataInfo(m_metadataInfo);
	m_visualTree->SetVisualColourMap(m_visualColourMap);
	m_viewport->SetColourMap(m_visualColourMap);

	// *** Populate colour map panel widets
	std::vector<std::wstring> fields = m_metadataInfo->GetFields();

	m_cboField->Freeze();
	m_cboField->Clear();
	foreach(const std::wstring& field, fields)
	{
		m_cboField->Append(field);
	}
	m_cboField->Thaw();

	m_cboField->SetSelection(0);
	OnChangeField(wxCommandEvent());
}

void PygmyFrame::PopulateSearchList(std::vector<std::wstring>& words)
{
	m_lstSearch->Clear();

	std::vector<std::wstring>::iterator it;
	m_lstSearch->Freeze();
	for(it = words.begin(); it != words.end(); ++it)
	{
		m_lstSearch->Append(*it);
	}
	m_lstSearch->Thaw();

	m_lstSearch->Refresh(false);

	m_viewport->Render();
	m_overview->Redraw(true);
}

void PygmyFrame::SearchText(const std::wstring& str, const std::wstring& searchType)
{
	std::vector<std::wstring>& filtered = m_textSearch->FilterData(str, searchType);
	PopulateSearchList(filtered);
}

void PygmyFrame::OnSearchText( wxCommandEvent& event )
{
	wxString str = m_txtSearch->GetValue();
	SearchText(str.wc_str(), m_cboSearchType->GetValue().wc_str());
}

void PygmyFrame::OnChangeSearchType( wxCommandEvent& event )
{
	wxString str = m_txtSearch->GetValue();
	SearchText(str.wc_str(), m_cboSearchType->GetValue().wc_str());
}

void PygmyFrame::OnSearchClick( wxCommandEvent& event )
{
	std::wstring selection = m_lstSearch->GetStringSelection();

	uint id;
	if(m_textSearch->Data(selection, id))
	{
		m_viewport->CenterNode(id);
	}
}

void PygmyFrame::OnFileSaveOverview( wxCommandEvent& event )
{
	wxFileDialog saveDlg(this, _T("Save image file..."), _T(""), _T(""),_T("*.*"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT | wxFD_CHANGE_DIR);
	wxString wildcards = _T("Portable Network Graphics (*.png)|*.png|Portable Pixel Map (*.ppm)|*.ppm");
 	saveDlg.SetWildcard(wildcards);

  if(saveDlg.ShowModal() != wxID_OK)
  {
      return;
  }

  wstring path = saveDlg.GetDirectory();
  wstring filename = saveDlg.GetFilename();

	m_overview->SaveImage(path + _T("\\") + filename);
}

void PygmyFrame::OnFileSaveImage( wxCommandEvent& event )
{
	wxFileDialog saveDlg(this, _T("Save image file..."), _T(""), _T(""),_T("*.*"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT | wxFD_CHANGE_DIR);
	wxString wildcards = _T("Portable Network Graphics (*.png)|*.png|Portable Pixel Map (*.ppm)|*.ppm");
 	saveDlg.SetWildcard(wildcards);

  if(saveDlg.ShowModal() != wxID_OK)
  {
      return;
  }

  wstring path = saveDlg.GetDirectory();
  wstring filename = saveDlg.GetFilename();

	m_viewport->SaveImage(path + _T("\\") + filename);
}

void PygmyFrame::OnFileExportTree( wxCommandEvent& event )
{
	wxFileDialog saveDlg(this, _T("Export tree to file..."), _T(""), _T(""),_T("*.*"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT | wxFD_CHANGE_DIR);
	wxString wildcards = _T("Newick file (*.tre)|*.tre|All files (*.*)|*.*");
 	saveDlg.SetWildcard(wildcards);

  if(saveDlg.ShowModal() != wxID_OK)
  {
      return;
  }

  wstring path = saveDlg.GetDirectory();
  wstring filename = saveDlg.GetFilename();

	if(m_visualTree)
	{
		utils::Tree<NodePhylo>::Ptr tree = m_visualTree->GetTree();
		
		NewickIO newickIO;
		newickIO.Write(tree, path + _T("\\") + filename);
	}
}

void PygmyFrame::OnFileExportSubtree( wxCommandEvent& event )
{
	wxFileDialog saveDlg(this, _T("Export subtree to file..."), _T(""), _T(""),_T("*.*"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT | wxFD_CHANGE_DIR);
	wxString wildcards = _T("Newick file (*.tre)|*.tre|All files (*.*)|*.*");
 	saveDlg.SetWildcard(wildcards);

  if(saveDlg.ShowModal() != wxID_OK)
  {
      return;
  }

  wstring path = saveDlg.GetDirectory();
  wstring filename = saveDlg.GetFilename();

	if(m_visualTree)
	{
		utils::Tree<NodePhylo>::Ptr subtree = m_visualTree->GetSelectedSubtree();
		
		NewickIO newickIO;
		newickIO.Write(subtree, path + _T("\\") + filename);
	}
}

void PygmyFrame::OnBranchStyleChanged( wxCommandEvent& event )
{
	if(m_cboBranchStyle->GetStringSelection() == "Cladogram")
		m_visualTree->SetBranchStyle(VisualTree::CLADOGRAM_BRANCHES);
	else if(m_cboBranchStyle->GetStringSelection() == "Equal")
		m_visualTree->SetBranchStyle(VisualTree::EQUAL_BRANCHES);
	else if(m_cboBranchStyle->GetStringSelection() == "Phylogram")
		m_visualTree->SetBranchStyle(VisualTree::PHYLOGRAM_BRANCHES);

	m_visualTree->LayoutBranchStyle();
	m_viewport->Redraw(true);
}

void PygmyFrame::ViewSearchTextPanel()
{
	if(m_splitterViewportTools->IsSplit())
	{
		m_searchTextPanelWidth = m_pnlSearchText->GetSize().x;
		m_splitterViewportTools->Unsplit();
	}
	else
	{
		// Split the window to show the search window (Hack: the -8 factor is needed... why?)
		m_splitterViewportTools->SplitVertically(m_pnlViewports, m_pnlSearchText, -m_searchTextPanelWidth-8);
	}
}

void PygmyFrame::OnViewSearchTextTb( wxCommandEvent& event )
{
	ViewSearchTextPanel();

	m_menuBar->Check(ID_MNU_VIEW_SEARCH, m_toolBar->GetToolState(ID_TB_VIEW_SEARCH));
}

void PygmyFrame::OnViewSearchTextMnu( wxCommandEvent& event )
{
	ViewSearchTextPanel();

	m_toolBar->ToggleTool(ID_TB_VIEW_SEARCH, m_menuBar->IsChecked(ID_MNU_VIEW_SEARCH));
}

void PygmyFrame::ViewSettingsPanel()
{
	if(m_settingsSplitter->IsSplit())
	{
		m_settingsPanelWidth = m_pnlSettings->GetSize().x;
		m_settingsSplitter->Unsplit(m_pnlSettings);
	}
	else
	{
		// Split the window to show the search window (Hack: the -8 factor is needed... why?)
		m_settingsSplitter->SplitVertically(m_pnlSettings, m_pnlMain, m_settingsPanelWidth);
	}
}

void PygmyFrame::OnViewSettingsTb( wxCommandEvent& event )
{
	ViewSettingsPanel();

	m_menuBar->Check(ID_MNU_VIEW_SETTINGS, m_toolBar->GetToolState(ID_TB_VIEW_SETTINGS));
}

void PygmyFrame::OnViewSettingsMnu( wxCommandEvent& event )
{
	ViewSettingsPanel();

	m_toolBar->ToggleTool(ID_TB_VIEW_SETTINGS, m_menuBar->IsChecked(ID_MNU_VIEW_SETTINGS));
}

void PygmyFrame::ViewOverviewPanel()
{
	if(m_splitterOverview->IsSplit())
	{
		m_overview->SetDisabled(true);
		m_overviewPanelWidth = m_pnlOverview->GetSize().x;
		m_splitterOverview->Unsplit(m_pnlOverview);
	}
	else
	{
		// Split the window to show the overview window
		m_splitterOverview->SplitVertically(m_pnlOverview, m_pnlViewport, m_overviewPanelWidth);
		m_overview->SetDisabled(false);
		m_overview->Redraw(true);
	}
}

void PygmyFrame::OnViewOverviewWindowMnu(wxCommandEvent& event)
{
	ViewOverviewPanel();

	m_toolBar->ToggleTool(ID_TB_VIEW_OVERVIEW_WINDOW, m_menuBar->IsChecked(ID_MNU_VIEW_OVERVIEW_WINDOW));
}


void PygmyFrame::OnViewOverviewWindowTb(wxCommandEvent& event)
{
	ViewOverviewPanel();

	m_menuBar->Check(ID_MNU_VIEW_OVERVIEW_WINDOW, m_toolBar->GetToolState(ID_TB_VIEW_OVERVIEW_WINDOW));
}

void PygmyFrame::ViewColourMapPanel()
{
	if(m_splitterColourMap->IsSplit())
	{
		m_colourMapPanelHeight = m_pnlColourMap->GetSize().y;
		m_splitterColourMap->Unsplit(m_pnlColourMap);
	}
	else
	{
		// Split the window to show the colour map panel
		m_splitterColourMap->SplitHorizontally(m_panelTop, m_pnlColourMap, -m_colourMapPanelHeight);
	}
}

void PygmyFrame::OnViewColourMapMnu( wxCommandEvent& event )
{
	ViewColourMapPanel();

	m_toolBar->ToggleTool(ID_TB_COLOUR_MAP_PANEL, m_menuBar->IsChecked(ID_MNU_COLOUR_MAP_PANEL));
}

void PygmyFrame::OnViewColourMapTb( wxCommandEvent& event )
{
	ViewColourMapPanel();

	m_menuBar->Check(ID_MNU_COLOUR_MAP_PANEL, m_toolBar->GetToolState(ID_TB_COLOUR_MAP_PANEL));
}

void PygmyFrame::OnLeafFontTypeface( wxCommandEvent& event )
{
	std::wstring fontFile = m_choiceLeafFont->GetStringSelection();
	State::Inst().SetFontFile(_T("fonts/") + fontFile + _T(".ttf"));
	State::Inst().GetFont()->SetTypeface(pygmy::App::Inst().GetExeDir() + _T("fonts/") + fontFile + _T(".ttf"));

	m_viewport->ModifiedFont();
}

void PygmyFrame::OnLeafFontSize( wxSpinEvent& event )
{
	State::Inst().SetTreeFontSize(m_spinLeafFontSize->GetValue());
	
	m_viewport->ModifiedFont();
}

void PygmyFrame::OnLeafFontColour( wxColourPickerEvent& event )
{
	State::Inst().SetTreeFontColour(Colour(m_colourLeafFont->GetColour()));

	m_viewport->Render();
}

void PygmyFrame::OnLineWidth( wxSpinEvent& event )
{
	State::Inst().SetLineWidth(m_spinLineWeight->GetValue());

	m_viewport->Render();
}

void PygmyFrame::OnOverviewLineWidth( wxSpinEvent& event )
{
	State::Inst().SetOverviewLineWidth(m_spinOverviewLineWeight->GetValue());

	m_overview->Redraw(true);
}

void PygmyFrame::OnScrollSensitivity( wxScrollEvent& event )
{
	State::Inst().SetScrollSensitivity(m_sliderScrollSensitivity->GetValue());
}

void PygmyFrame::OnTranslationSensitivity( wxScrollEvent& event )
{
	State::Inst().SetTranslationSensitivity(float(m_sliderTranslationSensitibity->GetValue()) / 10);
}

void PygmyFrame::OnZoomSensitivity( wxScrollEvent& event )
{
	State::Inst().SetZoomSensitivity(float(m_sliderZoomSensitivity->GetValue()) / 1000);
}

void PygmyFrame::OnChangeField( wxCommandEvent& event )
{
	if(!m_visualTree)
		return;

	State::Inst().SetMetadataField(m_cboField->GetValue().wc_str());

	FieldInfo fieldInfo = m_visualTree->GetMetadataInfo()->GetInfo(m_cboField->GetValue().wc_str());	

	if(fieldInfo.dataType == FieldInfo::CATEGORICAL)
	{
		m_cboTreatDataAs->SetValue(_T("Categorical"));
	}
	else if(fieldInfo.dataType == FieldInfo::NUMERICAL && fieldInfo.values.size() <= FieldInfo::MAX_DISCRETE_VALUES)
	{
		m_cboTreatDataAs->SetValue(_T("Discrete"));
	}
	else
	{
		m_cboTreatDataAs->SetValue(_T("Continuous"));
	}

	if(State::Inst().GetShowMetadataLabels())
		m_visualTree->LabelBoundingBoxes();

	m_statusBar->SetStatusText(_T("Unique field values = ") + utils::StringTools::ToString(fieldInfo.values.size()), 2);

	OnTreatDataAs(wxCommandEvent());
}

void PygmyFrame::OnTreatDataAs( wxCommandEvent& event )
{
	if(!m_visualTree)
		return;

	m_cboColourMap->Enable(true);

	// get all colour maps of the specified type
	std::vector<std::wstring> maps;
	if(m_cboTreatDataAs->GetStringSelection() == _T("Categorical"))
		maps = m_colourMapManager->GetCategoricalMaps();
	else if(m_cboTreatDataAs->GetStringSelection() == _T("Continuous"))
		maps = m_colourMapManager->GetContinuousMaps();
	else if(m_cboTreatDataAs->GetStringSelection() == _T("Discrete"))
		maps = m_colourMapManager->GetDiscreteMaps();

	// list those colour maps with enough entries to cover all unique values 
	m_cboColourMap->Clear();

	std::wstring field(m_cboField->GetValue().wc_str());
	FieldInfo fieldInfo = m_metadataInfo->GetInfo(field);

	foreach(const std::wstring& map, maps)
	{
		if(fieldInfo.dataType == FieldInfo::CATEGORICAL)
		{
			if(m_cboTreatDataAs->GetStringSelection() == _T("Continuous")
					|| m_colourMapManager->GetColourMap(map)->GetSize() >= fieldInfo.values.size())
			{
				m_cboColourMap->Append(map);
			}
		}
		else
		{
			if(m_cboTreatDataAs->GetStringSelection() != _T("Categorical")
					|| m_colourMapManager->GetColourMap(map)->GetSize() >= fieldInfo.values.size())
			{
				m_cboColourMap->Append(map);
			}
		}
	}

	if(m_cboColourMap->GetCount() == 0)
		m_cboColourMap->Enable(false);

	// set last selected colour map of the selected type
	if(m_cboTreatDataAs->GetStringSelection() == _T("Categorical"))
		m_cboColourMap->SetValue(m_colourMapManager->GetLastSelectedCategorical());
	else if(m_cboTreatDataAs->GetStringSelection() == _T("Continuous"))
		m_cboColourMap->SetValue(m_colourMapManager->GetLastSelectedContinuous());
	else if(m_cboTreatDataAs->GetStringSelection() == _T("Discrete"))
		m_cboColourMap->SetValue(m_colourMapManager->GetLastSelectedDiscrete());

	OnChangeColourMap(wxCommandEvent());
}

void PygmyFrame::OnChangeColourMap( wxCommandEvent& event )
{
	if(!m_visualTree)
		return;

	std::wstring colourMapName = m_cboColourMap->GetStringSelection().wc_str();
	if(!colourMapName.empty())
	{
		m_colourMapManager->SetLastSelected(colourMapName);
	}
	else
	{
		if(m_cboColourMap->GetCount() > 0)
			m_cboColourMap->Select(0);
	}

	ModifyColourMap();

	if(State::Inst().GetOptimizeLeafNodeOrdering())
	{
		std::wstring field(m_cboField->GetValue().wc_str());

		uint numCrossings = 0;
		OptimizeLeafOrder::OptimizeLeafNodeOrdering(m_visualTree->GetTree(), m_metadataInfo, field, numCrossings, true);

		m_statusBar->SetStatusText(_T("Number of crossings: ") + utils::StringTools::ToString(numCrossings), 3);

		m_visualTree->Layout();
	}
	
	m_viewport->Refresh(false);
}

void PygmyFrame::OnAppendMetadata( wxCommandEvent& event )
{
	State::Inst().SetShowMetadataLabels(m_chkAppendMetadata->GetValue());

	if(m_visualTree)
	{
		m_visualTree->LabelBoundingBoxes();
		m_viewport->Refresh(false);
	}
}

void PygmyFrame::OnShowLeafLabels( wxCommandEvent& event )
{
	State::Inst().SetShowLeafLabels(m_chkShowLeafLabels->GetValue());

	if(m_visualTree)
	{
		m_visualTree->LabelBoundingBoxes();
		m_viewport->Refresh(false);
	}
}

void PygmyFrame::OnColourOverviewTree( wxCommandEvent& event )
{
	State::Inst().SetColourOverviewTree(m_chkColourOverviewTree->GetValue());

	if(m_overview)
		m_overview->Redraw(true);
}

void PygmyFrame::OnShowPositionOverlay( wxCommandEvent& event )
{
	State::Inst().SetOverviewPositionOverlay(m_chkShowPositionOverlay->GetValue());

	if(m_overview)
		m_overview->Redraw(true);
}

void PygmyFrame::OnColourMapWidth( wxSpinEvent& event )
{
	State::Inst().SetColourMapWidth(m_spinColourMapWidth->GetValue());

	if(m_visualColourMap)
		m_viewport->Refresh(false);
}

void PygmyFrame::OnShowColourMap( wxCommandEvent& event )
{
	State::Inst().SetShowColourMapVis(m_chkShowColourMap->GetValue());

	if(m_visualColourMap)
		m_viewport->Refresh(false);
}

void PygmyFrame::OnShowColourMapTicks( wxCommandEvent& event )
{
	State::Inst().SetShowColourMapTickMarks(m_chkShowColourMapTicks->GetValue());

	if(m_visualColourMap)
		m_viewport->Refresh(false);
}

void PygmyFrame::OnMissingDataColour( wxColourPickerEvent& event )
{
	State::Inst().SetColourMissingData(Colour(m_colourMissingData->GetColour()));

	if(m_visualColourMap)
	{
		ModifyColourMap();
		m_viewport->Refresh(false);
	}
}

void PygmyFrame::OnDefaultTreeColour( wxColourPickerEvent& event )
{
	State::Inst().SetDefaultTreeColour(Colour(m_defaultTreeColour->GetColour()));

	if(m_visualColourMap)
	{
		ModifyColourMap();
		m_viewport->Refresh(false);
	}
}

void PygmyFrame::OnIgnoreLeafNodes( wxCommandEvent& event )
{
	State::Inst().SetIgnoreMissingData(m_chkIgnoreLeafNodes->GetValue());

	if(m_visualColourMap)
	{
		ModifyColourMap();
		m_viewport->Refresh(false);
	}
}

void PygmyFrame::ModifyColourMap()
{
	std::wstring field(m_cboField->GetValue().wc_str());

	std::wstring colorMapStr = m_cboColourMap->GetStringSelection().wc_str();

	ColourMapPtr colourMap;
	if(!colorMapStr.empty())
	{
		colourMap = m_colourMapManager->GetColourMap(colorMapStr);

		// assign names to a discrete or categorical colour map
		FieldInfo fieldInfo = m_metadataInfo->GetInfo(field);
		if(colourMap->GetType() == ColourMap::DISCRETE || colourMap->GetType() == ColourMap::CATEGORICAL)
		{
			ColourMapDiscretePtr discreteMap = boost::dynamic_pointer_cast<ColourMapDiscrete>(colourMap);

			int index = 0;
			foreach(const std::wstring& value, fieldInfo.values)
			{
				discreteMap->SetColour(value, discreteMap->GetColour(index));
				index++;
			}
		}
	}
	else
	{
		// create 'fake' colour map where all entries are black
		ColourMapContinuousPtr continuousMap(new ColourMapContinuous());
		continuousMap->SetType(ColourMap::CONTINUOUS);
		continuousMap->SetColour(ColourMap::GetDefaultColour(), 0);
		continuousMap->SetColour(ColourMap::GetDefaultColour(), 1);

		colourMap = continuousMap;
	}

	if(m_visualColourMap)
		m_visualColourMap->SetColourMap(colourMap);

	// propagate colours up tree
	m_visualTree->PropagateColours(field, colourMap);

	// propagate colour up overview tree
	if(State::Inst().GetColourOverviewTree())
		m_overview->Redraw(true);
}

void PygmyFrame::OnColourMapLabelColour( wxColourPickerEvent& event )
{
	State::Inst().SetColourMapFontColour(Colour(m_colourMapLabelColour->GetColour()));

	if(m_visualColourMap)
		m_viewport->Refresh(false);
}

void PygmyFrame::OnColourMapLabelSize( wxSpinEvent& event )
{
	State::Inst().SetColourMapFontSize(m_spinColourMapLabelSize->GetValue());

	if(m_visualColourMap)
		m_viewport->Refresh(false);
}

void PygmyFrame::OnColourMapLabelPrecision( wxSpinEvent& event )
{
	State::Inst().SetColourMapFontPrecision(m_spinColourMapLabelPrecision->GetValue());

	if(m_visualColourMap)
		m_viewport->Refresh(false);
}

void PygmyFrame::OnScientificNotation( wxCommandEvent& event )
{
	State::Inst().SetColourMapFontScientific(m_chkScientific->GetValue());

	if(m_visualColourMap)
		m_viewport->Refresh(false);
}

void PygmyFrame::OnColourMapNumberOfLabels( wxSpinEvent& event )
{
	State::Inst().SetColourMapValuesToDisplay(m_spinColourMapNumberOfLabels->GetValue());

	if(m_visualColourMap)
		m_viewport->Refresh(false);
}

void PygmyFrame::OnOptimizeLeafNodeOrdering( wxCommandEvent& event )
{
	State::Inst().SetOptimizeLeafNodeOrdering(m_chkOptimizeLeafOrder->GetValue());

	if(m_visualTree)
	{
		std::wstring field(m_cboField->GetValue().wc_str());

		uint numCrossings = 0;
		OptimizeLeafOrder::OptimizeLeafNodeOrdering(m_visualTree->GetTree(), m_metadataInfo, field, numCrossings, true);

		m_statusBar->SetStatusText(_T("Number of crossings: ") + utils::StringTools::ToString(numCrossings), 3);

		m_visualTree->Layout();
		m_viewport->Refresh(false);
	}
}

void PygmyFrame::OnInternalNodeField( wxCommandEvent& event )
{
	State::Inst().SetInternalNodeField(m_cboInternalNodeLabelsField->GetValue().wc_str());

	if(m_visualTree)
		m_viewport->Refresh(false);
}

void PygmyFrame::OnInternalNodeColour( wxColourPickerEvent& event )
{
	State::Inst().SetInternalNodeFontColour(Colour(m_internalNodeLabelColour->GetColour()));

	if(m_visualTree)
		m_viewport->Refresh(false);
}

void PygmyFrame::OnInternalNodeSize( wxSpinEvent& event )
{
	State::Inst().SetInternalNodeFontSize(m_spinInternalNodeLabelSize->GetValue());

	if(m_visualTree)
		m_viewport->Refresh(false);
}

void PygmyFrame::OnInternalNodePrecision( wxSpinEvent& event )
{
	State::Inst().SetInternalNodeFontPrecision(m_spinInternalNodeLabelPrecision->GetValue());

	if(m_visualTree)
		m_viewport->Refresh(false);
}

void PygmyFrame::OnInternalNodeScientific( wxCommandEvent& event )
{
	State::Inst().SetInternalNodeFontScientific(m_chkInternalNodeLabelScientificNotation->GetValue());

	if(m_visualTree)
		m_viewport->Refresh(false);
}

void PygmyFrame::OnInternalLabelPos( wxCommandEvent& event )
{
	State::Inst().SetInternalLabelPos(m_cboInternalLabelPos->GetValue().wc_str());

	if(m_visualTree)
		m_viewport->Refresh(false);
}

void PygmyFrame::OnInternalNodeShow( wxCommandEvent& event )
{
	State::Inst().SetShowInternalLabels(m_chkShowInternalLabels->GetValue());

	if(m_visualTree)
		m_viewport->Refresh(false);
}

void PygmyFrame::OnCollapseNode( wxCommandEvent& event )
{
	long value = wxGetNumberFromUser(_T("Collapse nodes with support less than the specified value.\n"),
																		_T("Minimum required support:"),
																		_T("Collapse weakly supported nodes"),
																		70, 0, 100, App::Inst().GetMainFrame());

	if(value != -1 && m_visualTree)
	{
		// collapse all nodes with a bootstrap value less than the specified value
		m_visualTree->CollapseNodes(value);
		m_viewport->Refresh(false);
	}
}

void PygmyFrame::OnProjectTree( wxCommandEvent& event )
{
	TaxaSelectionDlg* dlg = new TaxaSelectionDlg(App::Inst().GetMainFrame(), m_visualTree, m_viewport);
	dlg->ShowModal();
	dlg->Destroy();	
}

void PygmyFrame::OnRestoreTree( wxCommandEvent& event )
{
	int answer = wxMessageBox(_T("Restore original tree?"), _T("Restore original tree"),
                              wxYES_NO | wxCANCEL, App::Inst().GetMainFrame());


	if(answer == wxYES && m_visualTree)
	{
		m_visualTree->RestoreTree();
		m_viewport->Redraw(true);
	}
}

void PygmyFrame::OnRerootTree( wxCommandEvent& event )
{
	if(m_visualTree)
		m_visualTree->Reroot();

	m_viewport->Redraw(true);
}

void PygmyFrame::OnCollapseExandSubtree( wxCommandEvent& event )
{

}

void PygmyFrame::SigViewportMouseLeftClick(wxMouseEvent& event)
{
	Point mousePos(event.GetPosition().x, m_viewport->GetHeight()-event.GetPosition().y);

	bool bSelected = false;

	if(m_visualTree)
	{
		bSelected = m_visualTree->MouseLeftDown(mousePos);
	}

	m_viewport->Refresh(false);
		
	event.Skip();	// note: needs to be called so window will get focus (see wxWidgets documentation)

}

void PygmyFrame::SigViewportMouseRightClick(wxMouseEvent& event)
{

}

void PygmyFrame::OnCharFromKeyboard( wxKeyEvent& event )
{
	event.Skip();
}

void PygmyFrame::OnAnalysisParsimony( wxCommandEvent& event )
{
	if(m_visualTree)
	{
		uint score = m_visualTree->Parsimony();
		m_cboInternalNodeLabelsField->SetValue(State::Inst().GetInternalNodeField());

		FieldInfo fieldInfo = m_visualTree->GetMetadataInfo()->GetInfo(m_cboField->GetValue().wc_str());	
		uint minTransitions = fieldInfo.values.size() - 1;

		wxString message = "Parsimony score = " + utils::StringTools::ToString(score) + "\n\n";
		message += "Consistency index = " + utils::StringTools::ToString(minTransitions / float(score), 3);
		
		wxMessageBox(message, _T("Parsimony Analysis Info"), wxOK | wxICON_INFORMATION);
	}
	else
	{
		wxMessageBox(_T("Please load a tree before performing a parsimony analysis."), _T("Warning"), wxOK | wxICON_INFORMATION);
	}
}