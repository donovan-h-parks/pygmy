//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../core/App.hpp"
#include "../core/OptimizeLeafOrder.hpp"
#include "../core/NodePhylo.hpp"
#include "../core/MetadataInfo.hpp"

#include "../utils/TreeTools.hpp"
#include "../utils/StringTools.hpp"

using namespace pygmy;
using namespace utils;

typedef struct sIDENTICAL_VALUE_SET
{
	sIDENTICAL_VALUE_SET(uint _index, uint _layoutPos): index(_index), layoutPos(_layoutPos) {}

	uint index;
	uint layoutPos;
} IdenticalValueSet;

bool IdenticalSetPredicate(IdenticalValueSet elem1, IdenticalValueSet elem2)
{
	 return elem1.layoutPos < elem2.layoutPos;
}

bool IdenticalSetVectorPredicate(std::vector<IdenticalValueSet> elem1, std::vector<IdenticalValueSet> elem2)
{
	 return elem1.at(0).layoutPos < elem2.at(0).layoutPos;
}

void OptimizeLeafOrder::OptimizeLeafNodeOrdering(Tree<NodePhylo>::Ptr tree, MetadataInfoPtr metadataInfo, const std::wstring& field, 
																											uint& numCrossings, bool bOptimize)
{
	numCrossings = 0;

	FieldInfo fieldInfo = metadataInfo->GetInfo(field);

	// assign layout position of each leaf node along colour map
	std::vector<NodePhylo*> leafNodes = tree->GetLeaves();
	foreach(NodePhylo* leafNode, leafNodes)
	{
		leafNode->SetNumCrossings(0);

		std::wstring value = leafNode->GetData(field);
		if(!metadataInfo->IsMissingData(value))
		{
			// find position in unique values
			uint pos = 0;
			foreach(const std::wstring& v, fieldInfo.values)
			{
				if(value == v)
					leafNode->SetLayoutPos(pos);
				pos++;
			}
		}
		else
		{
			// ignore leaf nodes with missing data
			leafNode->SetLayoutPos(NOT_SET);
		}
	}

	// find optimal ordering of leaf nodes in tree
	BranchAndBoundTreeOpt(tree->GetRootNode(), numCrossings, bOptimize);
}

void OptimizeLeafOrder::BranchAndBoundTreeOpt(NodePhylo* node, uint& numCrossings, bool bOptimize)
{
	if(!node->IsLeaf())
	{
		uint numChildren = node->GetNumberOfChildren();

		// optimize ordering of subtrees first
		std::vector<uint> permutationVec;
		for(uint i = 0; i < numChildren; ++i)
		{
			BranchAndBoundTreeOpt(node->GetChild(i), numCrossings, bOptimize);
			permutationVec.push_back(i);
		}

		// Get number of crossings in subtrees below this node
		std::vector<NodePhylo*> childNode = node->GetChildren();
		uint childrenCrossings = 0;
		foreach(NodePhylo* child, childNode)
		{
			childrenCrossings += child->GetNumCrossings();
		}


		// Get ordering of leaf nodes determine by barycenter heuristic
		// Complexity barycenter heuristic: O(|E|)
		std::vector<uint> baryCenterOrdering;
		BaryCenterOrdering(node, baryCenterOrdering);				

		// Get crossing count for the barycenter heuristic		
		// Complexity: O(|E|log(|Vsmall|))
		for(uint i = 0; i < numChildren; ++i)
		{
			node->SetChild(i, childNode.at(baryCenterOrdering.at(i)));
		}
		uint baryCenterBound = CountCrossingsByInversionNumber(node);

		if(!bOptimize)
		{
			node->SetNumCrossings(childrenCrossings+baryCenterBound);
			return;
		}

		// It has been shown that if there is an ordering of points that results in zero crossings,
		// that both the median and barycenter heuristics will find this ordering.
		// see: Graph Drawing: Algorithms for the Visualization of Graphs
		//				by Battista, Eades, Tamassia, Tollis
		uint bound = baryCenterBound;
		if(baryCenterBound == 0)
		{
			node->SetNumCrossings(childrenCrossings);
			return;
		}
		else
		{
			// Create count matrix
			// Complexity: O(|Vsmall|^2) 
			std::vector< std::vector<uint> > countMatrix;
			CreateCountMatrix(node, countMatrix);

			// Get order of children now that they are in the order specified by the barycenter heuristic.
			// It is likely that lower bound will be found more quickly starting from this ordering than
			// the default one.
			childNode = node->GetChildren();	

			// Determine best order of leaf nodes by performing a branch and bound search
			// over the entire permutation tree as represented by a permutation vector.
			std::vector<uint> optOrder = permutationVec;

			// perform branch and bound on the permutation tree in a depth first search manner
			// Complexity: O(?)
			do
			{		
				uint crossingsForPermutation = 0;

				// evaluate current permutation
				// Complexity (worst case): O(|Vsmall|^2)
				for(uint i = 1; i < numChildren; ++i)
				{
					// determine number of crossings for the potentially partial permutation						
					for(uint j = 0; j < i; ++j)
					{
						crossingsForPermutation += countMatrix[permutationVec.at(j)][permutationVec.at(i)];
						if(crossingsForPermutation >= bound)
							break;
					}
			
					if(i < numChildren-1 && crossingsForPermutation >= bound)
					{
						// No need to explore the rest of the permutation below the current node
						// in the permutation tree. This portion of the tree can be skipped by
						// setting the elements in the permutation vector beyond this node in
						// descending order. This works because std::next_permutation() goes through
						// permutations in a specific order. Namely, it always generates the
						// "lexicographically next greater permutation of the elements".
						//
						// Note: this could be done in O(|Vsmall|) time using a radix sort,
						// however in practice for the size of problem considered here
						// the std::sort will be faster. Notice, that this step only every
						// occurs once per permutation.
						std::sort(permutationVec.begin()+i+1, permutationVec.end(), std::greater<int>());
						break;
					}
				}
				
				if(crossingsForPermutation < bound)
				{
					bound = crossingsForPermutation;
					optOrder = permutationVec;
				}
			} while(next_permutation(permutationVec.begin(), permutationVec.end()));

			// Set node to the optimal order
			if(bound < baryCenterBound)
			{
				// if the bary center bound is optimal than the children 
				// have already been put in the correct order
				node->RemoveChildren();
				for(uint i = 0; i < numChildren; ++i)
				{
					node->AddChild(childNode.at(optOrder.at(i)));
				}
			}
		}

		// tabulate total number of crossings for tree
		numCrossings += bound;

		node->SetNumCrossings(childrenCrossings + bound);
	}
}

typedef struct sCROSS_SORTER
{
	sCROSS_SORTER(uint _southIndex, uint _northIndex): southIndex(_southIndex), northIndex(_northIndex) {}

	uint southIndex;
	uint northIndex;
} CrossSorter;

// Predicate used to sort items in NodeSorter.
bool CrossSorterPredicate(CrossSorter elem1, CrossSorter elem2)
{
	 return elem1.southIndex < elem2.southIndex;
}

uint OptimizeLeafOrder::CountCrossingsByInversionNumber(NodePhylo* node, uint maxCrossings)
{
	// Determine lexicographical order of nodes on the north line as read from left to right
	// across the south line. The implementation here takes O(|E|log(|E|)) where E is the 
	// number of edges. It can be done in O(|E|) time by using radix sort. Although radix
	// sort is better theoretically (and in practice for large |E|) I have decided to use
	// std::sort for simplicity and since |E| is fairly small for the cases we are interested in.
	std::vector<NodePhylo*> children = node->GetChildren();
	std::vector<CrossSorter> crossSeq;
	for(uint i = 0; i < children.size(); ++i)
	{
		if(children.at(i)->IsLeaf())
		{
			uint pos = children.at(i)->GetLayoutPos();
			if(pos != NOT_SET)
			{
				CrossSorter crossSorter(pos, i);
				crossSeq.push_back(crossSorter);
			}
		}
		else
		{
			std::vector<NodePhylo*> grandChildren = TreeTools<NodePhylo>::GetLeaves(children.at(i));

			foreach(NodePhylo* node, grandChildren)
			{			
				uint pos = node->GetLayoutPos();
				if(pos != NOT_SET)
				{
					CrossSorter crossSorter(pos, i);
					crossSeq.push_back(crossSorter);
				}
			}
		}
	}

	std::sort(crossSeq.begin(), crossSeq.end(), CrossSorterPredicate);

	// Count crossings using accumulator tree
	// See: "Simple and efficient bilayer cross counting" by Barth, W., Junger, M., and Mutzel, P.
	// This takes O(|E|log(|V_small|), where E is the number of edges and V_small is the smaller
	// cardinality node set. In our case, E is the number of leaf nodes in the subtree rooted at 
	// the specified node and V_small is the number of children of this node. Intuitively, the 
	// runtime is O(|E|log(|V_small|)) since for each edge all positions in a balance search tree
	// from the leaf node of this edge to the root must be updated. The height of the balanced
	// search tree is log(|V_small|) so there is log(|V_small|) work for each edge.
	uint firstIndex = 1;
	while(firstIndex < children.size())
		firstIndex *= 2;

	uint treeSize = 2*firstIndex - 1;		// number of nodes in tree	
	firstIndex -= 1;										// index of leftmost leaf
	uint* tree = new uint[treeSize];
	for(uint t = 0; t < treeSize; ++t)
		tree[t] = 0;

	uint crossCount = 0;
	for(uint k = 0; k < crossSeq.size(); ++k)
	{
		uint index = crossSeq.at(k).northIndex + firstIndex;
		tree[index]++;
		while(index > 0)
		{
			if(index%2)
			{
				crossCount += tree[index+1];
				if(crossCount > maxCrossings)
					return crossCount;
			}

			index = (index-1) / 2;
			tree[index]++;
		}
	}

	delete[] tree;

	return crossCount;
}

void OptimizeLeafOrder::CreateCountMatrix(NodePhylo* node, std::vector< std::vector<uint> >& countMatrix)
{
	std::vector<NodePhylo*> childNodes = node->GetChildren();
	countMatrix.resize(childNodes.size());
	for(uint i = 0; i < childNodes.size(); ++i)
	{
		countMatrix.at(i).resize(childNodes.size());
	}

	// count crossings between all pairs of children 
	for(uint i = 0; i < childNodes.size(); ++i)
	{
		for(uint j = 0; j < childNodes.size(); ++j)
		{
			if(i != j)
			{
				NodePhylo tempNode(0);
				tempNode.AddChild(childNodes[i]);
				tempNode.AddChild(childNodes[j]);
				countMatrix[i][j] = CountCrossingsByInversionNumber(&tempNode);
			}
			else 
			{
				countMatrix[i][j] = 0;
			}
		}
	}

	// reset all children to point to the parent node since they will be modified above
	for(uint i = 0; i < childNodes.size(); ++i)
	{
		childNodes.at(i)->SetParent(node);
	}
}

uint OptimizeLeafOrder::CanonicalLowerBound(const std::vector< std::vector<uint> >& countMatrix)
{
	uint lowerBound = 0;
	for(uint i = 0; i < countMatrix.size()-1; ++i)
	{
		for(uint j = i+1; j < countMatrix.size(); ++j)
		{
			uint c_ij = countMatrix[i][j];
			uint c_ji = countMatrix[j][i];

			if(c_ij <= c_ji)
			{
				lowerBound += c_ij;
			}
			else
			{
				lowerBound += c_ji;
			}
		}
	}

	return lowerBound;
}

typedef struct sHEURISTIC_SORTER
{
	sHEURISTIC_SORTER(double _heuristicValue, uint _index, uint _degree): heuristicValue(_heuristicValue), index(_index), degree(_degree) {}

	double heuristicValue;
	uint index;
	uint degree;
} HeuristicSorter;

// Predicate used to sort items in NodeSorter.
bool HeuristicSorterPredicate(HeuristicSorter elem1, HeuristicSorter elem2)
{
	if(elem1.heuristicValue < elem2.heuristicValue)
	 return true;
	else if(elem1.heuristicValue > elem2.heuristicValue)
	 return false;
	else
	{
		// if one of the elements has odd degree and the other even, than the
		// odd degree vertex should be placed on the left. If both have the
		// same degree than the order is arbitrary.
		// see: Graph Drawing: Algorithms for the Visualization of Graphs
		//				by Battista, Eades, Tamassia, Tollis
		if(elem1.degree % 2 == 1)
			return true;

		// Note: Weird way to write the above relationship so the it is a strictly weak ordering
		// as required by STL
		//if( ( elem1.degree % 2 ) >= ( elem2.degree % 2 ) ) 
    //    return true; 
	}
		
		return false;
}

void OptimizeLeafOrder::BaryCenterOrdering(NodePhylo* node, std::vector<uint>& baryCenterOrdering)
{
	// Calculate the barycenter (average) for each subtree. This heuristic finds an O(sqrt(n))
	// -approximation solution or a (d−1)-approximation solution, where d is the maximum degree of 
	// nodes in the free side.

	// This algorithm assumes the barycenter of all children node (except leaf nodes) has already been
	// calculated. In this way, the barycenter can more efficently be calculated.
	std::vector<NodePhylo*> childNodes = node->GetChildren();
	std::vector<HeuristicSorter> baryCenters;
	for(uint i = 0; i < childNodes.size(); ++i)
	{
		NodePhylo* curNode = childNodes.at(i);

		if(curNode->IsLeaf())
		{
			baryCenters.push_back(HeuristicSorter(curNode->GetLayoutPos(), i, 0));
		}
		else
		{
			std::vector<NodePhylo*> childChildNodes = curNode->GetChildren();

			uint baryCenter = 0;
			uint divisor = 0;
			foreach(NodePhylo* node, childChildNodes)
			{
				if(node->IsLeaf())
				{
					uint pos = node->GetLayoutPos();
					if(pos != NOT_SET)
					{
						baryCenter += pos;
						divisor++;
					}
				}
				else
				{
					uint pos = node->GetBaryCenter();
					if(pos != NOT_SET)
					{
						baryCenter += node->GetBaryCenter()*node->GetNumberOfChildren();
						divisor += node->GetNumberOfChildren();
					}
				}
			}

			if(divisor != 0)
			{
				baryCenter /= divisor;
			}
			else
			{
				// the placement of nodes where none of the leaves are attached to geographic locations does not matter
				// so just place it at the end and mark the internal node as being unset
				baryCenter = NOT_SET;
			}

			baryCenters.push_back(HeuristicSorter(baryCenter, i, childNodes.at(i)->GetNumberOfChildren()));
			curNode->SetBaryCenter(baryCenter);
		}		
	}
	std::sort(baryCenters.begin(), baryCenters.end(), HeuristicSorterPredicate);

	for(uint i = 0; i < baryCenters.size(); ++i)
	{
		baryCenterOrdering.push_back(baryCenters.at(i).index);
	}
}

void OptimizeLeafOrder::MedianOrdering(NodePhylo* node, std::vector<uint>& medianOrdering)
{
	// Calculate the median for each subtree. This heuristic finds an 3-approximation solution,
	// but in NodePhylo is often worse than the bartcenter heuristic.
	std::vector<NodePhylo*> childNodes = node->GetChildren();
	std::vector<HeuristicSorter> medians;
	for(uint i = 0; i < childNodes.size(); ++i)
	{
		std::vector<NodePhylo*> leafNodes = TreeTools<NodePhylo>::GetLeaves(node->GetChild(i));
		std::vector<uint> leafPos;
		for(uint j = 0; j < leafNodes.size(); ++j)
		{
			uint pos = leafNodes.at(j)->GetLayoutPos();
			if(pos != NOT_SET)
			{
				leafPos.push_back(pos);
			}
		}

		std::sort(leafPos.begin(), leafPos.end());
		uint median = leafPos.at(leafPos.size()/2);
		medians.push_back(HeuristicSorter(median, i, childNodes.at(i)->GetNumberOfChildren()));
	}
	std::sort(medians.begin(), medians.end(), HeuristicSorterPredicate);

	for(uint i = 0; i < medians.size(); ++i)
	{
		medianOrdering.push_back(medians.at(i).index);
	}
}

double OptimizeLeafOrder::SignificanceTest(Tree<NodePhylo>::Ptr tree, NodePhylo* node, uint iterations, std::map<uint, uint>& pdf)
{
	/*
	wxProgressDialog* progressDlg = new wxProgressDialog("Performing Significance Test", "Iteration: 0", iterations, App::Inst().GetMainFrame());

	// get order of leaf nodes
	std::vector<uint> leafOrder;
	std::vector<NodePhylo*> leafNodes = TreeTools<NodePhylo>::GetLeaves(node);
	std::vector<NodePhylo*> activeLeafNodes;
	foreach(NodePhylo* leaf, leafNodes)
	{
		//if(leaf->GetActive())
		{
			leafOrder.push_back(leaf->GetLayoutPos());
			activeLeafNodes.push_back(leaf);
		}
	}

	// get number of crossings for original association of leaf nodes to geographical locations
	uint origNumCrossings = 0;
	OptimizeLeafNodeOrdering(tree, node, origNumCrossings, true);

	// Create probability density function by holding the tree topology and order 
	// of geographical locations along the layout line constant. Only the association 
	// of leaf nodes to geographical location is randomized.
	std::vector<uint> rndPermutation = leafOrder;
	for(uint i = 0; i < iterations; ++i)
	{
		// randomly permute association between leaf node and geographical location
		RandomPermutation(rndPermutation);
		for(uint j = 0; j < activeLeafNodes.size(); ++j)
		{
			activeLeafNodes.at(j)->SetLayoutPos(rndPermutation.at(j));
		}

		uint numCrossings = 0;
		OptimizeLeafNodeOrdering(tree, node, numCrossings, true);

		std::map<uint, uint>::iterator iter;
		iter = pdf.find(numCrossings);
		if(iter == pdf.end())
		{
			pdf[numCrossings] = 1;
		}
		else
		{
			iter->second++;
		}

		if(!progressDlg->Update(i, "Iteration: " + utils::StringTools::ToString(i)))
		{
			progressDlg->Destroy();
			return 1.0f;
		}
	}

	// determine p-value for original association of leaf nodes to geographical locations
	std::map<uint, uint>::iterator iter;
	uint pValueCount = 0;
	for(iter = pdf.begin(); iter != pdf.end(); ++iter)
	{
		if(iter->first <= origNumCrossings)
			pValueCount += iter->second;
	}
	double pValue = (pValueCount + 1.0) / (iterations + 1.0);		// the +1 is to account for the original model (permutation)
	
	// restore original order and statistics for tree
	for(uint i = 0; i < activeLeafNodes.size(); ++i)
	{
		activeLeafNodes.at(i)->SetLayoutPos(leafOrder.at(i));
	}

	uint numCrossings = 0;
	OptimizeLeafNodeOrdering(tree, node, numCrossings, true);

	progressDlg->Destroy();

	return pValue;
	*/
	return 0;
}

void OptimizeLeafOrder::RandomPermutation(std::vector<uint>& leafOrder)
{
	// randomly permute order of leaf nodes
	// see: http://www.algoblog.com/2007/06/04/permutation/
	for(uint i = 1; i < leafOrder.size(); ++i)
	{
		uint j = rand() % (i+1);
		uint temp = leafOrder.at(i);
		leafOrder.at(i) = leafOrder.at(j);
		leafOrder.at(j) = temp;
	}
}
