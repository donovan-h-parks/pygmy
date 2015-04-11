//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _NEWICK_IO_
#define _NEWICK_IO_

#include "../core/Precompiled.hpp"

#include "../core/NodePhylo.hpp"

#include "../utils/Tree.hpp"

namespace pygmy
{

/**
 * @brief Read/write data in Newick format.
 *
 * Branch lengths and bootstrap value are supported:
 *
 * ex:
 * <code>
 * ((Human:0.1,Gorilla:0.1):0.4,(Mouse:0.2,Rat:0.2):0.3);
 * </code>
 *
 * Code example:
 * @code
 * #include <NewickIO.hpp>
 * #include <Tree.hpp>
 * 
 * NewickIO newickIO;
 * Tree<NodePhylo>::Ptr tree(new Tree<NodePhylo>());
 * newickIO.Read(tree, "E:/PhD/Development/Projects/Data/Trees/Newick_test1.tre");
 * @endcode
 */
class NewickIO
{
public:
	/** Function signature for LoadingProgress event. */
	typedef boost::signal<bool (int progress, const std::wstring& msg, bool* skip)> OnLoadingProgress;

public:		
	/** Constructor. */
	NewickIO() {}

	/**
	 * @brief Read a phylogenetic tree from a file.
	 *
	 * @param tree Tree to populate from file.
	 * @param filename The file path.
	 * @return True if tree loaded successfully, false loading was cancelled.
	 */
	bool Read(utils::Tree<NodePhylo>::Ptr tree, const std::wstring& filename);

	/**
	 * @brief Read a phylogenetic tree from a stream.
	 *
	 * @param tree Tree to populate from file.
	 * @param in The input stream.
	 * @return True if tree loaded successfully, false loading was cancelled.
	 */
	bool Read(utils::Tree<NodePhylo>::Ptr tree, std::wistream& in);


	/**
	 * @brief Parse a string in Newick format and convert it to a tree.
	 *
	 * @param tree Tree to populate from file.
	 * @param newickStr Newick string to parse.
	 * @return True if tree loaded successfully, false loading was cancelled.
	 */
	bool ParseNewickString(utils::Tree<NodePhylo>::Ptr tree, const std::wstring& newickStr);

	/**
	 * @brief Write a phylogenetic tree to a stream.
	 *
	 * @param tree Tree to write out to file.
	 * @param out The output stream.
	 * @throw IOException If output stream is invalid
	 */
	void Write(utils::Tree<NodePhylo>::Ptr tree, std::wostream & out) const; 

  /**
   * @brief Write a phylogenetic tree to a file.
   *
	 * @param tree Tree to write out to file.
   * @param filename The file path.
   * @param overwrite Tell if existing file should be overwritten or appended to.
	 * @throw IOException If file can not be opened.
   */
	void Write(utils::Tree<NodePhylo>::Ptr tree, const std::wstring & filename, bool overwrite = true) const
	{
		std::wofstream output(filename.c_str(), overwrite ? (std::ios::out) : (std::ios::out|std::ios::app));
		Write(tree, output); 
		output.close();
	}

protected:
	 /**
		* @brief Parse Newick string information about a node.
		*
		* @param node Node to associate information with.
		* @param nodeInfo Node data obtained from Newick string.
		* @return bLeafNode Flag indicating if node represents a leaf node (true) or internal node (false).
		*/
	void ParseNodeInfo(NodePhylo* node, std::wstring& nodeInfo, bool bLeafNode);
  
		/**
     * @brief Write elements of a node to file in Newick format.
     *
		 * @param tree Tree to write out to file.
     * @param out The output stream.
		 * @param parentID Index of parent node.
		 * @param childID Node structure of the child node.
     */
		void WriteElements(utils::Tree<NodePhylo>::Ptr tree, std::wostream& out, NodePhylo* parent, NodePhylo* child) const;

		/**
     * @brief Write each node to file in Newick format.
     *
		 * @param tree Tree to write out to file.
     * @param out The output stream.
		 * @param parentID Index of parent node.
     */
		void WriteNodes(utils::Tree<NodePhylo>::Ptr tree, std::wostream& out, NodePhylo* parent) const;
};

} 

#endif

