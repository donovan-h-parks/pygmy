//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _GEO_TREE_VIEW_HPP_
#define _GEO_TREE_VIEW_HPP_

#include "../core/Precompiled.hpp"

#include "../core/NodePhylo.hpp"
#include "../core/VisualObject.hpp"
#include "../core/VisualMarker.hpp"
#include "../core/VisualRect.hpp"

#include "../utils/Colour.hpp"
#include "../utils/Tree.hpp"

namespace pygmy 
{

/** Visual properties of tree nodes. */
typedef struct sVISUAL_NODE
{
	/** Constructor. */
	sVISUAL_NODE(VisualMarker _visualMarker, NodePhylo* _node): visualMarker(_visualMarker), node(_node) {}

	/** Visual properties of node. */
	VisualMarker visualMarker;

	/** Node. */
	NodePhylo* node;
} VisualNode;

/** Visual properties of tree branch. */
typedef struct sVISUAL_BRANCH
{
	/** Constructor. */
	sVISUAL_BRANCH(VisualRect _visualBranch, NodePhylo* _node): visualBranch(_visualBranch), node(_node) {}

	/** Visual properties of branch. */
	VisualRect visualBranch;

	/** Node branch leads to. */
	NodePhylo* node;
} VisualBranch;

/**
 * @brief Class for visualizing a tree.
 */
class VisualTree: public VisualObject
{
public:
	enum BRANCH_STYLE { PHYLOGRAM_BRANCHES, CLADOGRAM_BRANCHES, EQUAL_BRANCHES };

public:
	/** 
	 * @brief Constructor. 
	 * @param tree Tree to visualize.
	 */
	VisualTree(utils::Tree<NodePhylo>::Ptr tree);

	/** Destructor. */
	virtual ~VisualTree() {}

	/** 
	 * @brief Render portion of tree visible within the viewport.
	 * @param width Width of viewport.
	 * @param height Height of viewport.
	 * @param translation Translation of tree in viewport.
	 * @param zoom Zoom level of tree in viewport.
	 */
	void Render(int width, int height, float translation, float zoom);

	/**
	 * @brieft Layout tree.
	 */
	void Layout() { LayoutBranchStyle(); LayoutY(); }

	/**
	 * @brief Layout tree with a given branch style.
	 */
	void LayoutBranchStyle();

	/**
	 * @brief Layout y-position of nodes.
	 */
	void LayoutY();

	/** Set visual colour map. */
	void SetVisualColourMap(VisualColourMapPtr visualColourMap) { m_visualColourMap = visualColourMap; }

	/**
	 * @brief Layout tree.
	 * @param field Field to base colours on.
	 * @param colourMap Colour map to associate with tree. 
	 */
	void PropagateColours(const std::wstring& field, utils::ColourMapPtr colourMap);

	/**
	 * @brief Calculate dimensions of tree.
	 * @param width Current width of viewport tree is being displayed in.
	 * @param height Current height of viewport tree is being displayed in.
	 * @param zoom Current zoom level of viewport tree is being displayed in.
	 */
	void CalculateTreeDimensions(uint width, uint height, float zoom);

	/**
	 * @brief Filter node labels based on a text search.
	 * @param filter Filter object containing all items filtered by the search.
	 */
	virtual void SetSearchFilter(FilterPtr filter) { m_searchFilter = filter; }

	/** Set metadata info object. */
	void SetMetadataInfo(MetadataInfoPtr metadataInfo) { m_metadataInfo = metadataInfo; }

	/** Get metadata info object. */
	MetadataInfoPtr GetMetadataInfo() { return m_metadataInfo; }

	/** 
	 * @brief Get fraction of tree height visible in the viewport. 
	 * @param frac Fraction visible.
	 */
	virtual float GetViewportHeightFraction() { return m_viewportHeightFrac; }

	/** 
	 * @brief Project tree onto a set of leaf nodes.
	 * @param names Names of leaf nodes to project tree onto.
	 * Note: names will contain a list of all the names not found in the tree after function returns.
	 */
	void ProjectTree(std::vector<std::wstring>& names);

	/**
	 * @brief Collapse all nodes with a bootstrap value less than the specified value. 
	 * @param support Collapse all nodes with support less than this value.
	 */
	void CollapseNodes(float support);

	/**
	 * @brief Reroot a tree to the user selected branch.
	 */
	void Reroot();

	/** 
	 * @brief Restore original tree.
	 */
	void RestoreTree();

	/**
	 * @brief Get current tree.
	 */
	utils::Tree<NodePhylo>::Ptr GetTree() { return m_tree; }

	/**
	 * @brief Get selected subtree.
	 */
	utils::Tree<NodePhylo>::Ptr GetSelectedSubtree();

	/**
	 * @brief Get original tree.
	 */
	utils::Tree<NodePhylo>::Ptr GetOriginalTree() { return m_originalTree; }

	/** 
	 * @brief Calculate grid positions of all nodes in tree for a given branch style. 
	 * @param layout Desired layout style.
	 */
	void SetBranchStyle(BRANCH_STYLE branchLayout) { m_branchStyle = branchLayout; }

	/** Get current branch style. */
	BRANCH_STYLE GetBranchStyle() { return m_branchStyle; }

	/** Calculate bounding boxes for all leaf node labels. */
	void LabelBoundingBoxes();

	/** Get height of tree when labels just touch each other (in pixels). */
	float GetTreeHeight() { return m_treeHeight; }

	/** Get width of tree such that leaf node labels fit within viewport (in pixels). */
	float GetTreeWidth() { return m_treeWidth; } 

	/** Get width of the widest label (in pixels). */
	float GetWidestLabel() { return m_widestLabel; }

	/** Get height of the highest label (in pixels). */
	float GetHighestLabel() { return m_highestLabel; }

	/** Perform parsimony analysis. */
	uint Parsimony();

	/** 
	 * @brief Process mouse left button down events. 
	 * @param mousePt Screen position of mouse.
	 * @return True if visual tree is processing the event, else false.
	 */
	bool MouseLeftDown(const utils::Point& mousePt);

protected:
	/**
	 * @brief Propogate colours assigned to leaf nodes up tree.
	 * @param bMixColour Flag indicating if the colour of a parent node should be a mixture of the
	 *									 colours of its children or set to a default value if all children are not the
	 *									 same colour.
	 */
	void PropagateLeafNodeColours(bool bMixColour);

	/** Render tree. */
	virtual void RenderTree(float translation, float zoom);

	/** Render highlights for text search. */ 
	virtual void RenderTextSearch(float translation, float zoom);

	/** Render leaf node labels. */
	virtual void RenderLeafNodeLabels(float translation, float zoom);

	/** Render labels on internal nodes. */
	virtual void RenderInternalLabels(float translation, float zoom);

	/** Render the active node (i.e., node under the cursor). */
	virtual void RenderActiveNode(float translation, float zoom);

	void LayoutY(NodePhylo* node, uint& yLeafPosition);

protected:
	/** Active geographic tree model. May be subject to modification (e.g., projection onto a set of leaf nodes). */
	utils::Tree<NodePhylo>::Ptr m_tree;

	/** Original tree model. */
	utils::Tree<NodePhylo>::Ptr m_originalTree;

	/** Object indicating metadata associated with tree. */
	MetadataInfoPtr m_metadataInfo;

	/** Visual colour map. */
	VisualColourMapPtr m_visualColourMap;

	/** Current branch style of tree. */
	BRANCH_STYLE m_branchStyle;

	/** List of all branches within the viewport. */
	std::vector<VisualBranch> m_visibleBranches;

	/** List of all nodes currently within the viewport. */
	std::vector<VisualNode> m_visibleNodes;

	/** List of all leaf nodes currently within the viewport. */
	std::vector<NodePhylo*> m_visibleLeafNodes;

	/** Node currently under cursor. */
	VisualNode m_activeNode;
	
	/** Height of tree such when labels just touch each other (in pixels). */
	float m_treeHeight;

	/** Width of tree such that leaf node labels fit within viewport (in pixels). */
	float m_treeWidth;

	/** Bounding boxes for all leaf node labels. */
	std::map<utils::Node::NodeId, utils::BBox> m_bboxMap;

	/** Width of the widest label (in pixels). */
	float m_widestLabel;

	/** Height of the highest label (in pixels). */
	float m_highestLabel;

	/** Space between tree and colour map. */
	float m_colourMapSpacing;

	/** Filter for text search. */
	FilterPtr m_searchFilter;

	/** Fraction of a tree's height visible in the viewport. */
	float m_viewportHeightFrac;
	
	/** Calculate parsimony score and internal entries. */
	utils::ParsimonyCalculatorPtr m_parsimonyCalculator;
};

}

#endif
