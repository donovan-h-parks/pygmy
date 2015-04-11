//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _VIEWPORT_TREE_OVERVIEW_H_
#define _VIEWPORT_TREE_OVERVIEW_H_

#include "../core/Precompiled.hpp"

#include "../core/VisualTree.hpp"
#include "../core/NodePhylo.hpp"

#include "../glUtils/ViewportOrtho.hpp"

#include "../utils/Tree.hpp"

namespace pygmy
{

/**
 * @brief Viewport to display a tree with an associated overview window.
 */
class ViewportMain : public glUtils::ViewportOrtho
{
public:
	/** Constructor. */
	ViewportMain(wxWindow *parent, const wxWindowID id = -1, 
							const wxPoint& pos = wxDefaultPosition,
							const wxSize& size = wxDefaultSize, 
							long style = wxFULL_REPAINT_ON_RESIZE, 
							const wxString& name = _T("ViewportMain"));

	/** Destructor. */
	virtual ~ViewportMain() {}

	/** 
	 * @brief Reconstruct display lists. 
	 * @param bRender True if OpenGL scene should be re-rendered.
	 */
	virtual void Redraw(bool bRender);

	/**
	 * @brief Set phylogenetic tree to be displayed.
	 *
	 * @param visualTree Tree to display.
	 */
	virtual void SetTree(VisualTreePtr visualTree);

	/**
	 * @brief Set colour map to be displayed.
	 *
	 * @param visualColourMap Colour map to display.
	 */
	virtual void SetColourMap(VisualColourMapPtr visualColourMap);

	/**
	 * @brief Get phylogenetic tree being displayed.
	 */
	virtual VisualTreePtr GetTree() { return m_visualTree; }

	/**
	 * @brief Set branch style for tree.
	 */
	void SetBranchStyle(VisualTree::BRANCH_STYLE branchStyle); 

	/**
	 * @brief Ensure specified node is within the viewport. If it is 
	 *				currently outside the viewport, adjust the viewport so
	 *				it is centered of the Y position of this node.
	 * @param id Id of node of interest.
	 */
	virtual void CenterNode(uint id);

	/** Set translation to a given fraction of the tree. */
	virtual void TranslationFraction(float frac);

	/** Fraction of tree covered by the translation. */
	virtual float TranslationFraction();

	/** Indicate that the font size or style has been modified and that any values
			dependent on the font should be recalculated. */
	virtual void ModifiedFont();

	/**
	 * @brief Set overview viewport associated with this viewport. 
	 * @param overview Overview viewport of interest.
	 */
	void OverviewViewport(ViewportOverviewPtr overview) { m_overview = overview; }

protected:
	/** 
	 * @brief Render the OpenGL scene. Called by Render() and OnPaint() which 
	 *				set up the appropriate device context. 
	 */
	virtual void RenderScene();
	
	/** Set min/max values for zooming. */
	virtual void ZoomExtents();

	/** Set min/max values for translation. */
	virtual void TranslationExtents();

	// ** Window size has changed, so adjust the tree viewport size. */
	virtual void AdjustViewport();

	/** Called whenever zoom level has changed. */
	virtual void ZoomChanged();

	/** Called whenever translation changes. */
	virtual void TranslationChanged() {}

	// ** Translate viewport due to left mouse dragging. */
	virtual void TranslateView(int dx, int dy);

	// ** Scale viewport due to right mouse dragging. */
	virtual void ScaleView(int dx, int dy);

	// ** Change zoom. */
	virtual void SetZoom(float zoom);

	// ** Set default zoom level due to right mouse button double click. */
	virtual void SetDefaultZoom();

	// ** Translate viewport due to scroll wheel. */
	virtual void TranslateViewWheel(int dWheel);

protected:
	/** Tree to be displayed in viewport. */
	VisualTreePtr m_visualTree; 

	/** Colour map to be displayed in viewport. */
	VisualColourMapPtr m_visualColourMap;

	/** Overview associated with this viewport. */
	ViewportOverviewPtr m_overview;
};

}

#endif

