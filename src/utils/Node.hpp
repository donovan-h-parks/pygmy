//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _NODE_H_
#define _NODE_H_

#include "../core/Precompiled.hpp"

namespace utils
{

/**
 * @brief Nodes used in trees.
 */
class Node
{
public:
	enum NODE_FLAGS { NO_DISTANCE = INT_MIN };
	typedef uint NodeId;
    
public:  
	/**
	 * @brief Constructor.
	 * @param id Unique id identifying node.
	 */
	Node(NodeId id) : m_id(id), m_name(_T("")), m_parent(NULL), m_distanceToParent(NO_DISTANCE) {}

	/**
	 * @brief Constructor.
	 * @param id Unique id identifying node.
	 * @param name Name of node.
	 */
	Node(NodeId id,  const std::wstring & name) : m_id(id), m_name(name), m_parent(NULL), m_distanceToParent(NO_DISTANCE) {}

	/** Destructor. */
	virtual ~Node() {}

	/**
   * @brief Copy constructor.
   * 
   * @param node The node to copy.
   */
  Node(const Node & node);

  /**
   * @brief Assignation operator.
   *
   * @param node the node to copy.
   * @return A reference toward this node.
   */
  Node & operator=(const Node & node);

public:          
	/** Get id associated with this node. */
	virtual NodeId GetId() const  { return m_id; }
	/**
	 * @brief Set node's id.
	 * @param id New identity tag.
	 */
	virtual void SetId(NodeId id) { m_id = id; }

	/** Get id of all children. */
	virtual std::vector<NodeId> GetChildrenIds() const;
	  
	/** Get the name associated to this node. */
	virtual const std::wstring& GetName() const	{	return m_name; }
	    
	/**
	 * @brief Set name of node.
	 * @param name Name to give node.
	 */
	virtual void SetName(const std::wstring& name)	{	m_name = name; }

	/** Get the distance to the parent node.	 */     
	virtual float GetDistanceToParent() const { return m_distanceToParent; }
	    
	/**
	 * @brief Set the distance to the parent node.
	 * @param distance Distance to parent node.
	 */
	virtual void SetDistanceToParent(float distance) { m_distanceToParent = distance; }
	  
	/** Get parent of this node. */     
	virtual Node* GetParent() const  { return m_parent; }

	/** Get id of parent node. */
	virtual unsigned int GetParentId() const  { return m_parent->GetId(); }
	    
	/**
	 * @brief Set the parent node.
	 * @param node Parent node.
	 */
	virtual void SetParent(Node* parent) { m_parent = parent; }
	    
	/** Remove the parent node. */
	virtual Node* RemoveParent() { Node* p = m_parent; m_parent = NULL; return p; }
	    
	/** Indicate if this node is the root node.	 */
	virtual bool IsRoot() const { return m_parent == NULL; }

	/** Get number of child nodes. */	     
	virtual unsigned int GetNumberOfChildren() const { return m_children.size(); }
    
	/** 
	 * @brief Get specified child node. 
	 * @param pos Indicates child that should be returned.
	 * @return Child at specified index position.
	 */
	virtual Node* GetChild(unsigned int pos) const;
	    
	/** 
	 * @brief Add child node at specified index position. 
	 * @param pos Position to add child.
	 * @param node Child node to add.
	 */
	virtual void AddChild(unsigned int pos, Node* node);

	/** 
	 * @brief Add child node.
	 * @param node Child node to add.
	 */
	virtual void AddChild(Node* node);
    
	/** 
	 * @brief Remove child node.
	 * @param pos Specifies which child to remove.
	 */
	virtual void RemoveChild(unsigned int pos);

	/** 
	 * @brief Remove child node.
	 * @param node Node to be removed.
	 */
	virtual void RemoveChild(Node* node);

	/** Remove all child nodes. */
	virtual void RemoveChildren();
	    
	/**
	 * @brief Get position of specified child node.
	 * @param child Child node to determine position of.
	 * @return Position of child node.
	 */
	virtual unsigned int GetChildPosition(Node* child) const;

	/** Get all neighbouring nodes (i.e., nodes that are children of this nodes parent). */
	// Note: this function is purposely not virual. Derived classes must implement there own
	// version of this class. if they wish to allow users to return a vector that is not of type Node*.
	std::vector<Node*> GetNeighbors() const;

	/** Get all child nodes. */
	// Note: this function is purposely not virual. Derived classes must implement there own
	// version of this class. if they wish to allow users to return a vector that is not of type Node*.
	std::vector<Node*> GetChildren() const { return m_children; }
	    
	/** Check if node is a leaf node. */
	virtual bool IsLeaf() const  { return m_children.empty(); }

	/** 
	 * @brief Swap the position of the two indicated children.
	 * @brief pos1 Position of first child.
	 * @brief pos2 Position of second child.
	 */
	virtual void Swap(unsigned int pos1, unsigned int pos2);
	
	/** Set index of leaf node. */
	void SetLeafOrderIndex(uint index) { m_leafNodeIndex = index; }

	/** Get leaf node index. */
	uint GetLeafOrderIndex() { return m_leafNodeIndex; }

	/** Get the distance to the root node.	 */     
	float GetDistanceToRoot() const { return m_distanceToRoot; }
	    
	/**
	 * @brief Set the distance to the root node.
	 * @param distance Distance to root node.
	 */
	void SetDistanceToRoot(float distance) { m_distanceToRoot = distance; }

	/** Get height of node (i.e., length of longest path to a leaf node). */
	int GetHeight() const { return m_height; }

	/** Set height of node (i.e., length of longest path to a leaf node). */
	void SetHeight(int height) { m_height = height; }

	/** Get depth of node (i.e., length of path to root). */
	int GetDepth() const { return m_depth; }

	/** Set depth of node (i.e., length of path to root). */
	void SetDepth(int depth) { m_depth = depth; }

protected:
	/** Unique id identifying node. */
  NodeId m_id;

	/** Name of node. */
  std::wstring m_name;

	/** Children of node. */
  std::vector<Node*> m_children;

	/** Parent of node. */
	Node* m_parent;

	/** Distance to parent of this node. */
  float m_distanceToParent;  

	/** Distance to the root node. */
	float m_distanceToRoot;

	/** Height of node (i.e., length of longest path to a leaf node). */
	int m_height;

	/** Depth of node (i.e., length of path to root). */
	int m_depth;

	/** Index of leaf node amongst all leaf nodes. */
	uint m_leafNodeIndex;
};

} 

#endif

