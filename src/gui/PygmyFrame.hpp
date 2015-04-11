//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _PYGMY_FRAME_HPP_
#define _PYGMY_FRAME_HPP_

#include "../core/Precompiled.hpp"

#include "../core/NodePhylo.hpp"

#include "../gui/PygmyLayout.h"

#include "../utils/Tree.hpp"

namespace pygmy
{

/**
 * @brief Handles all events and GUI processing from main form.
 */
class PygmyFrame : public PygmyLayout
{
public:
	enum STATUS_POS { SP_TOOLTIP = 0, SP_LEFT_TREE = 1, SP_RIGHT_TREE = 2 };

public:
	/**
	 * @brief Constructor.
	 * @param parent Parent for this frame
	 */
	PygmyFrame( wxWindow* parent = (wxFrame *)NULL );

	/** Destructor */
	~PygmyFrame();

	/** Change colour map event handler. */
	void OnChangeColourMap( wxCommandEvent& event );

	/** Open tree. */
	void OpenTree(const std::wstring& filename);
	
private:
	/** Set default value of all controls. */
	void SetDefaultValues();

	/**
	 * @brief Populate the list box with all (filtered) words.
	 * @param words Words to place in list box.
	 */
	void PopulateSearchList(std::vector<std::wstring>& words);

	/**
	 * @brief Search for taxa using the specified search type
	 *				and show results both in the tree overviews and the search list box.
	 * @param str String to search for.
	 * @param searchType Type of search to perform (i.e., starts with, contains, ends with, matches)
	 */
	void SearchText(const std::wstring& str, const std::wstring& searchType);

	/** File->Open Tree... event handler. */
	void OnFileOpenTree( wxCommandEvent& event );


	/** File->Open Metadata... event handler. */
	void OnFileOpenMetadata( wxCommandEvent& event );

	/** File->Exit event handler. */
	void OnFileExit( wxCommandEvent& event );

	/** File->Save viewport as image... event handler. */
	void OnFileSaveImage( wxCommandEvent& event );

	/** File->Save overview tree as image... event handler. */
	void OnFileSaveOverview( wxCommandEvent& event );

	/** File->Export tree... event handler. */
	void OnFileExportTree( wxCommandEvent& event );

	/** File->Export subtree... event handler. */
	void OnFileExportSubtree( wxCommandEvent& event );

	/** Help->About event handler. */
	void OnHelpAbout( wxCommandEvent& event );

	/** Desired branch style has changed. **/
	void OnBranchStyleChanged( wxCommandEvent& event );

	/** Show/hide search text panel. */
	void ViewSearchTextPanel();

	/** View->Search Leaf Nodes panel event handler. */
	void OnViewSearchTextMnu( wxCommandEvent& event );

	/** Search Leaf Nodes panel toolbar event handler. */
	void OnViewSearchTextTb( wxCommandEvent& event );

	/**Show\hide overview panel. */
	void ViewOverviewPanel();

	/** View->Overview panel event handler. */
	void OnViewOverviewWindowMnu( wxCommandEvent& event );

	/** Show\hide overview window toolbar event handler. */
	void OnViewOverviewWindowTb( wxCommandEvent& event );

	/** Show/hide settings panel. */
	void ViewSettingsPanel();

	/** View->Settings panel event handler. */
	void OnViewSettingsMnu( wxCommandEvent& event );

	/** Settings Window toolbar event handler. */
	void OnViewSettingsTb( wxCommandEvent& event );

	/** show/hide colour map panel. */
	void ViewColourMapPanel();

	/** View->Colour map panel event handler. */
	void OnViewColourMapMnu( wxCommandEvent& event );

	/** Colour map panel toolbar event handler. */
	void OnViewColourMapTb( wxCommandEvent& event );

	/** Handle the erase event for the main form which is generated
	 		whenever a window's background needs to be repainted. */
	void OnEraseBackground( wxEraseEvent& event ){ /* prevent flicker */ }

	/** Handle the erase event for the viewport panel which is generated
			whenever a window's background needs to be repainted. */
	void OnViewportEraseBackground( wxEraseEvent& event ){ /* prevent flicker */ }

	/** Event occurs when text is entered into the text search box. */
	void OnSearchText( wxCommandEvent& event );

	/** Event occurs when an item if the search list box is selected. */
	void OnSearchClick( wxCommandEvent& event );

		/** Style->Font Size event handler. */
	void OnFontSize( wxCommandEvent& event );

	/** Change leaf font typeface event handler. */
	void OnLeafFontTypeface( wxCommandEvent& event );

	/** Change leaf font size event handler. */
	void OnLeafFontSize( wxSpinEvent& event );

	/** Change leaf font colour event handler. */
	void OnLeafFontColour( wxColourPickerEvent& event );

	/** Change line width event handler. */
	void OnLineWidth( wxSpinEvent& event );

	/** Change overview line width event handler. */
	void OnOverviewLineWidth( wxSpinEvent& event );

	/** Change sensitivity of scroll wheel. */
	void OnScrollSensitivity( wxScrollEvent& event );

	/** Change sensitivity of left-click translation. */
	void OnTranslationSensitivity( wxScrollEvent& event );

	/** Change sensitivity of right-click zooming. */
	void OnZoomSensitivity( wxScrollEvent& event );

	/** Change field type event handler. */
	void OnChangeField( wxCommandEvent& event );

	/** Change how data should be treated event handler. */
	void OnTreatDataAs( wxCommandEvent& event );

	/** Show/hide metadata label event handler. */
	void OnAppendMetadata( wxCommandEvent& event );

	/** Show/hide leaf labels event handler. */
	void OnShowLeafLabels( wxCommandEvent& event );

	/** Change colour overview tree flag event handler. */
	void OnColourOverviewTree( wxCommandEvent& event );

	/** Change flag indicating if overview position overlay should be rendered. */
	void OnShowPositionOverlay( wxCommandEvent& event );

	/** Change colour map width event handler. */
	void OnColourMapWidth( wxSpinEvent& event );

	/** Change visibility of colour map event handler. */
	void OnShowColourMap( wxCommandEvent& event );

	/** Change visibility of colour map tick marks event handler. */
	void OnShowColourMapTicks( wxCommandEvent& event );

	/** Change colour of missing data event handler. */
	void OnMissingDataColour( wxColourPickerEvent& event );

	/** Change default tree colour event handler. */
	void OnDefaultTreeColour( wxColourPickerEvent& event );

	/** Change flag indicating if leaf nodes should be ignored when propagating colours. */
	void OnIgnoreLeafNodes( wxCommandEvent& event );

	/** Change colour of colour map labels event handler. */
	void OnColourMapLabelColour( wxColourPickerEvent& event );

	/** Change size of colour map labels event handler. */
	void OnColourMapLabelSize( wxSpinEvent& event );

	/** Change precision of colour map labels event handler. */
	void OnColourMapLabelPrecision( wxSpinEvent& event );

	/** Change whether colour map labels are displayed in fixed or scientific notation. */
	void OnScientificNotation( wxCommandEvent& event );

	/** Change number of labels to display on continuous colour map. */
	void OnColourMapNumberOfLabels( wxSpinEvent& event );

	/** Change whether ordering of leaf nodes is optimized or not. */
	void OnOptimizeLeafNodeOrdering( wxCommandEvent& event );

	/** Change field of internal node labels. */
	void OnInternalNodeField( wxCommandEvent& event );

	/** Change colour of internal node labels. */
	void OnInternalNodeColour( wxColourPickerEvent& event );

	/** Change size of internal node labels. */
	void OnInternalNodeSize( wxSpinEvent& event );

	/** Change precision of internal node labels. */
	void OnInternalNodePrecision( wxSpinEvent& event );

	/** Change notation of internal node labels. */
	void OnInternalNodeScientific( wxCommandEvent& event );

	/** Change position of internal labels. */
	void OnInternalLabelPos( wxCommandEvent& event );

	/** Change visibility of internal node labels. */
	void OnInternalNodeShow( wxCommandEvent& event );

	/** Collapse nodes with poor bootstrap support. */
	void OnCollapseNode( wxCommandEvent& event );

	/** Project tree onto a subset of taxa. */
	void OnProjectTree( wxCommandEvent& event );

	/** Restore originally loaded tree. */
	void OnRestoreTree( wxCommandEvent& event );

	/** Reroot tree. */
	void OnRerootTree( wxCommandEvent& event );

	/** Collapse/exand subtree to/from a triangle. */
	void OnCollapseExandSubtree( wxCommandEvent& event );

	/** Change search type. */
	void OnChangeSearchType( wxCommandEvent& event );

	/** Perform parsimony analysis on tree. */
	void OnAnalysisParsimony( wxCommandEvent& event );

	/** Configure colour map. */
	void ModifyColourMap();

	/** Handle mouse left click events from viewport. */
	virtual void SigViewportMouseLeftClick(wxMouseEvent& event);

	/** Handle mouse right click events from viewport. */
	virtual void SigViewportMouseRightClick(wxMouseEvent& event);
	
	/** Handle keyboard event. */
	virtual void OnCharFromKeyboard( wxKeyEvent& event );

private:
	/** Tree to display in viewports. */
	VisualTreePtr m_visualTree;

	/** Main canvas which supports OpenGL orthographic rendering linked to an overview tree. */
	ViewportMainPtr m_viewport;

	/** OpenGL canvas for rendering an overview tree. */
	ViewportOverviewPtr m_overview;

	/** Performs text search on leaf node labels of tree. */
	TextSearchPtr m_textSearch;

	/** Metadata info. */
	MetadataInfoPtr m_metadataInfo;

	/** Colour map visualization. */
	VisualColourMapPtr m_visualColourMap;

	/** Colour map manager. */
	utils::ColourMapManagerPtr m_colourMapManager;

	/** Width of search text window. */
	int m_searchTextPanelWidth;

	/** Width of overview window. */
	int m_overviewPanelWidth;

	/** Width of settings window. */
	int m_settingsPanelWidth;

	/** Height of colour map panel. */
	int m_colourMapPanelHeight;
};

}

#endif 
