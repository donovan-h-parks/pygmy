//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _METADATA_IO_
#define _METADATA_IO_

#include "../core/Precompiled.hpp"

namespace pygmy
{

/*!
	\class MetadataIO
	\brief Read metadata from file.
*/

class MetadataIO
{
public:
	/**
	 * @brief Load metadata from file.
	 * @param filename Filename of data.
	 * @param tree Tree metadata is to be associated with.
	 * @param metadataInfo Classes which summarize information about each metadata field.
	 */
	static bool Read(const std::wstring& filename, VisualTreePtr visualTree, MetadataInfoPtr metadataInfo);
};

}


#endif
