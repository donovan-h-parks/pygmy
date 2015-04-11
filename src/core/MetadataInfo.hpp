//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _METADATA_INFO_HPP_
#define _METADATA_INFO_HPP_

#include "../core/Precompiled.hpp"

#include "../core/NodePhylo.hpp"

#include "../utils/Tree.hpp"

#include <cfloat>

namespace pygmy
{

/**
 * @class FieldInfo
 * @brief Information calculated for each metadata field.
 */
typedef struct sFIELD_INFO
{
	/** Types of data. */
	enum DATA_TYPE { NUMERICAL, CATEGORICAL };

	/** Number of unique values until a field is considered continuous. */
	static const int MAX_DISCRETE_VALUES = 8;

	/** Value used to indicate the min or max value if not applicable. */
	static const float NA;

	/** Default constructor. */
	sFIELD_INFO()
		: minValue(0), maxValue(0), dataType(NUMERICAL) {}

	/** Constructor. */
	sFIELD_INFO(float _minValue, float _maxValue, DATA_TYPE _dataType, const std::set<std::wstring>& _values)
		: minValue(_minValue), maxValue(_maxValue), dataType(_dataType), values(_values) {}

	/** Get string corresponding to data type. */
	std::wstring GetDataTypeStr()
	{
		if(dataType == CATEGORICAL)
			return _T("Categorical");
		else if(dataType == NUMERICAL)
			return _T("Numerical");

		return _T("");
	}

	/** Minimum value of field. */
  float minValue;

	/** Maximum value of field. */
  float maxValue;

	/** Type of data in field. */
	DATA_TYPE dataType;

	/** Values for this field. */
	std::set<std::wstring> values;
} FieldInfo;

/**
 * @class Metadata
 * @brief Holds all metadata fields and summary information about these fields.
 */
class MetadataInfo 
{
public:
	/** Constructor. */
	MetadataInfo() {}

	/** Destructor. */
	~MetadataInfo( void ) {}

	/** Get summary information for given field. */
	FieldInfo GetInfo(const std::wstring& field) { return m_metadataInfo[field]; }

	/** Add new metadata. */
	void AddMetadata(const std::map<std::wstring, std::wstring>& metadata);

	/** Set metadata to reflect data in the leaf nodes of a tree. */
	void SetMetadata(utils::Tree<NodePhylo>::Ptr tree);

	/** Clear metadata. */
	void Clear() { m_metadataInfo.clear(); }

	/** Get all fields. */
	std::vector<std::wstring> GetFields();

	/** Check if data is missing. */
	static bool IsMissingData(const std::wstring& value);

private:
	std::map<std::wstring, FieldInfo> m_metadataInfo;
};

}

#endif
