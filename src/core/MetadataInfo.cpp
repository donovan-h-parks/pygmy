//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../core/MetadataInfo.hpp"
#include "../core/NodePhylo.hpp"

#include "../utils/StringTools.hpp"
#include "../utils/Tree.hpp"

using namespace utils;
using namespace pygmy;

const float FieldInfo::NA = -FLT_MAX;

std::vector<std::wstring> MetadataInfo::GetFields()
{
	std::vector<std::wstring> fields;

	typedef std::pair<std::wstring, FieldInfo> pair_t;
	foreach(pair_t data, m_metadataInfo)
	{	
		fields.push_back(data.first);
	}

	return fields;
}

void MetadataInfo::AddMetadata(const std::map<std::wstring, std::wstring>& metadata)
{
	typedef std::pair<std::wstring, std::wstring> pair_t;
	foreach(pair_t data, metadata)
	{
		std::map<std::wstring, FieldInfo>::iterator it = m_metadataInfo.find(data.first);
		if(it == m_metadataInfo.end())
		{
			std::set<std::wstring> values;
			if(!IsMissingData(data.second)) 
			{
				values.insert(data.second);

				// add new field
				if(utils::StringTools::IsDecimalNumber(data.second))
				{
					float value = utils::StringTools::ToFloat(data.second);
					m_metadataInfo[data.first] = FieldInfo(value, value, FieldInfo::NUMERICAL, values); 
				}
				else
				{
					m_metadataInfo[data.first] = FieldInfo(FieldInfo::NA, FieldInfo::NA, FieldInfo::CATEGORICAL, values); 
				}
			}
		}
		else
		{
			// update field info
			FieldInfo& fieldInfo = it->second;
			if(!IsMissingData(data.second)) 
			{
				fieldInfo.values.insert(data.second);

				if(utils::StringTools::IsDecimalNumber(data.second))
				{
					float value = utils::StringTools::ToFloat(data.second);

					if(value < fieldInfo.minValue)
							fieldInfo.minValue = value;
					if(value > fieldInfo.maxValue)
						fieldInfo.maxValue = value;

					fieldInfo.dataType = FieldInfo::NUMERICAL;
				}
				else
				{
					fieldInfo.dataType = FieldInfo::CATEGORICAL;				
				}
			}
		}
	}
}

void MetadataInfo::SetMetadata(utils::Tree<NodePhylo>::Ptr tree)
{
	Clear();

	std::vector< NodePhylo* > leaves = tree->GetLeaves();
	foreach(NodePhylo* leaf, leaves)
	{
		AddMetadata(leaf->GetMetadata());
	}
}

bool MetadataInfo::IsMissingData(const std::wstring& value)
{
	return value.empty() || value == _T("N/A") || value == _T("-") || value == _T("NULL");
}