//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _NODE_PHYLO_H_
#define _NODE_PHYLO_H_

#include "../core/Precompiled.hpp"

#include "../utils/Node.hpp"
#include "../utils/Point.hpp"
#include "../utils/Colour.hpp"

namespace pygmy
{

/**
 * @brief Nodes used for phylogenetic trees.
 */
	class NodePhylo : public utils::Node
{   
public:  
	/**
	 * @brief Constructor.
	 * @param id Unique id identifying node.
	 */
	NodePhylo(NodeId id): utils::Node(id), m_bootstrap(NO_DISTANCE), m_pos(utils::Point()), 
												m_colour(utils::Colour(0,0,0)), m_bProcessed(false), m_bMissingData(false),
												m_crossings(0), m_baryCenter(0), m_layoutPos(0), m_bSelected(false) {}

	/**
	 * @brief Constructor.
	 * @param id Unique id identifying node.
	 * @param name Name of node.
	 */
	NodePhylo(NodeId id,  const std::wstring & name): Node(id, name), m_bootstrap(NO_DISTANCE), m_pos(utils::Point()),
												m_colour(utils::Colour(0,0,0)), m_bProcessed(false), m_bMissingData(false),
												m_crossings(0), m_baryCenter(0), m_layoutPos(0), m_bSelected(false) {}

	/** Destructor. */
	virtual ~NodePhylo() {}

	/**
   * @brief Copy constructor.
   * 
   * @param node The node to copy.
   */
  NodePhylo(const NodePhylo& node): Node(node), m_bootstrap(node.GetBootstrapToParent()),
		m_pos(node.GetPosition()), m_interval(node.GetInterval()), m_colour(node.GetColour()),
		m_bProcessed(node.IsProcessed()), m_bMissingData(node.IsMissingData()),
		m_baryCenter(node.GetBaryCenter()), m_layoutPos(node.GetLayoutPos()), m_crossings(node.GetNumCrossings()),
		m_bSelected(node.IsSelected())
	{
		m_metadata = node.GetMetadata();
	}


  /**
   * @brief Assignation operator.
   *
   * @param node the node to copy.
   * @return A reference toward this node.
   */
  NodePhylo & operator=(const NodePhylo & node)
	{
		Node::operator=(node);

		m_bootstrap = node.GetBootstrapToParent();

		return * this;
	}

	/** 
	 * @brief Get specified child node. 
	 * @param pos Indicates child that should be returned.
	 * @return Child at specified index position.
	 */
	virtual NodePhylo* GetChild(unsigned int pos) const { return (NodePhylo*)Node::GetChild(pos); }

	/** Get parent of this node. */     
	virtual NodePhylo* GetParent() const  { return (NodePhylo*)Node::GetParent(); }

	/** Remove the parent node. */
	virtual NodePhylo* RemoveParent() { return (NodePhylo*)Node::RemoveParent(); }

	/** Get all neighbouring nodes (i.e., nodes that are children of this nodes parent). */
	std::vector<NodePhylo*> GetNeighbors() const
	{
		std::vector<NodePhylo*> neighbors;

		NodePhylo* parent = GetParent();

		for(unsigned int i = 0; i < parent->GetNumberOfChildren(); i++) 
		{
			if(parent->GetChild(i) != this)
				neighbors.push_back(parent->GetChild(i));
		}

		return neighbors;
	}

	/** Get all child nodes. */
	// Note: this function is purposely not virual. Derived classes must implement there own
	// version of this class. if they wish to allow users to return a vector that is not of type NodeGeoTree*.
	std::vector<NodePhylo*> GetChildren() const
	{ 
		std::vector<NodePhylo*> children;

		for(unsigned int i = 0; i < GetNumberOfChildren(); ++i)
		{
			children.push_back((NodePhylo*)GetChild(i));
		}

		return children; 
	}

	/** 
	 * @brief Set child node.
	 * @param index Index of child node to set.
	 * @param childNode Child node to set.
	 */
	virtual void SetChild(uint index, NodePhylo* childNode) { m_children.at(index) = childNode; }


	/** Get the bootstap value between this node and its parent node.	 */     
	virtual float GetBootstrapToParent() const { return m_bootstrap; }
	    
	/**
	 * @brief Set the bootstap value between this node and its parent node.
	 * @param bootstrap Bootstrap value to parent node.
	 */
	virtual void SetBootstrapToParent(float bootstrap) { m_bootstrap = bootstrap; }

	/** Set position of node. */
	void SetPosition(const utils::Point& pos) { m_pos = pos; }

	/** Set x-position of node. */
	void SetXPos(float xPos) { m_pos.x = xPos; }

	/** Get x-position of node. */
	float GetXPos() const { return m_pos.x; }

	/** Set y-position of node. */
	void SetYPos(float yPos) { m_pos.y = yPos; }

	/** Get y-position of node. */
	float GetYPos() const { return m_pos.y; }

	/** Get position of node. */
	const utils::Point& GetPosition() const { return m_pos; }

	/** Set interval of node. */
	void SetInterval(const utils::Interval& interval) { m_interval = interval; }

	/** Get interval of node. */
	const utils::Interval& GetInterval() const { return m_interval; }

	/** Set colour of node. */
	void SetColour(const utils::Colour& colour) { m_colour = colour; }

	/** Get colour of node. */
	const utils::Colour& GetColour() const { return m_colour; }

	/** Set metadata for node. */
	void SetMetadata(const std::map<std::wstring, std::wstring>& metadata) { m_metadata = metadata; }

	/** Get metadata for node. */
	std::map<std::wstring, std::wstring> GetMetadata() const { return m_metadata; }

	/** 
	 * @brief Get data for specified field. 
	 * @param field Field to get data for. 
	 * @return Data associated with the provided field.
	 */
	const std::wstring& GetData(const std::wstring& field) { return m_metadata[field]; }

	/** Set processed flag. */
	void SetProcessed(bool state) { m_bProcessed = state; }

	/** Get processed flag. */
	bool IsProcessed() const { return m_bProcessed; }

	/** Set missing data. */
	void SetMissingData(bool state) { m_bMissingData = state; }

	/** Get missing data. */
	bool IsMissingData() const { return m_bMissingData; }

		/** Set barycenter for this node. */
	void SetBaryCenter(double value) { m_baryCenter = value; }

	/** Get barycenter for this node. */
	double GetBaryCenter() const { return m_baryCenter; }

	/** Set desired position of node along a layout primative. */
	void SetLayoutPos(uint pos) { m_layoutPos = pos; }

	/** Get desired position of node along a layout primative. */
	uint GetLayoutPos() const { return m_layoutPos; }

	/** Set number of crossings below this node. */
	void SetNumCrossings(uint crossings) { m_crossings = crossings; }

	/** Get number of crossings below this node. */
	uint GetNumCrossings() const { return m_crossings; }

	/** Set flag indicating if node is selected or not. */
	virtual void SetSelected(bool state) { m_bSelected = state; }

	/** Determine if node is currently selected. */
	virtual bool IsSelected() const { return m_bSelected; }

protected:
	/** Bootstrap value for node. */
	float m_bootstrap;

	/** Position of node. */
	utils::Point m_pos;

	/** Vertical region spanned by the leaves of this node. */
	utils::Interval m_interval;

	/** Colour of node. */
	utils::Colour m_colour;

	/** Metadata associated with node. */
	std::map<std::wstring, std::wstring> m_metadata;

	/** Processed flag useful for many algorithms. */
	bool m_bProcessed;

	/** Flag indicating if it has missing data for the currently set field. */
	bool m_bMissingData;

	/** Barycentre of node. Used for heuristic graph layout. */
	double m_baryCenter;

	/** Position of node along a layout primative. */
	uint m_layoutPos;

	/** Number of crossings in subtree defined by this node. */
	uint m_crossings;

	/** Flag indicating if node is currently selected. */
	bool m_bSelected;
};

} 

#endif

