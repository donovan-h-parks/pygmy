//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../utils/ColourMapManager.hpp"
#include "../utils/ColourMap.hpp"
#include "../utils/ColourMapContinuous.hpp"
#include "../utils/ColourMapDiscrete.hpp"

#include "../utils/Log.hpp"

using namespace utils;

const std::wstring& ColourMapManager::GetLastSelectedCategorical() 
{ 
	if(m_lastCategoricalMap.empty())
		m_lastCategoricalMap = _T("Ware [9]");

	return m_lastCategoricalMap; 
}

const std::wstring& ColourMapManager::GetLastSelectedContinuous() 
{ 
	if(m_lastContinuousMap.empty())
		m_lastContinuousMap = _T("Spectral");

	return m_lastContinuousMap; 
}

const std::wstring& ColourMapManager::GetLastSelectedDiscrete() 
{ 
	if(m_lastDiscreteMap.empty())
		m_lastDiscreteMap = _T("Diverging Spectral [8]");

	return m_lastDiscreteMap; 
}

void ColourMapManager::SetLastSelected(const std::wstring mapName)
{
	std::map<std::wstring, ColourMapPtr>::const_iterator it;
	it = m_colourMaps.find(mapName);
	if(it == m_colourMaps.end())
	{
		utils::Log::Inst().Error(_T("(Error) ColourMapManager::SetLastSelected: Failed to locate colour map with specified name."));
	}

	if(it->second->GetType() == ColourMap::CATEGORICAL)
		m_lastCategoricalMap = mapName;
	else if(it->second->GetType() == ColourMap::CONTINUOUS)
		m_lastContinuousMap = mapName;
	else if(it->second->GetType() == ColourMap::DISCRETE)
		m_lastDiscreteMap = mapName;
}

ColourMapPtr ColourMapManager::GetDefaultDiscreteMap()
{
	ColourMapConstIter it = m_colourMaps.find(_T("Diverging Spectral [8]"));
	if(it == m_colourMaps.end())
	{
		utils::Log::Inst().Error(_T("ColourMapManager::GetDefaultDiscreteMap: default discrete map is missing."));
		return m_colourMaps.begin()->second;
	}

	return it->second;
}

ColourMapPtr ColourMapManager::GetDefaultContinuousMap()
{
	ColourMapConstIter it = m_colourMaps.find(_T("Spectral"));
	if(it == m_colourMaps.end())
	{
		utils::Log::Inst().Error(_T("ColourMapManager::GetDefaultContinuousMap: default continuous map is missing."));
		return m_colourMaps.begin()->second;
	}

	return it->second;
}

ColourMapPtr ColourMapManager::GetDefaultCategoricalMap()
{
	ColourMapConstIter it = m_colourMaps.find(_T("Ware [9]"));
	if(it == m_colourMaps.end())
	{
		utils::Log::Inst().Error(_T("ColourMapManager::GetDefaultCategoricalColour: default categorical map is missing."));
		return m_colourMaps.begin()->second;
	}

	return it->second;
}

ColourMapPtr ColourMapManager::GetColourMap(const std::wstring& name)
{
	ColourMapConstIter it = m_colourMaps.find(name);
	if(it == m_colourMaps.end())
	{
		utils::Log::Inst().Error(_T("ColourMapManager::GetColourMap: unrecognized colour map name."));
		return m_colourMaps.begin()->second;
	}

	return it->second;
}

bool ColourMapManager::LoadColourMaps(const std::wstring& colorMapPath)
{
	using namespace boost::filesystem; 
	
	// check if colour map directory exists
	wpath colorMapDir(colorMapPath);
	if(!exists(colorMapDir)) 
	{
		utils::Log::Inst().Error(_T("ColourMapManager::LoadColourMaps(): failed to open colour map directory."));
		return false;
	}

	// iterate over all files in colour map directory
	wdirectory_iterator end_itr; 
	ColourMapPtr tempColourMap(new ColourMap());
	bool bSuccess;
  for(wdirectory_iterator itr(colorMapDir); itr != end_itr; ++itr)
  {
		if (!is_directory(itr->status()))
		{
			std::wstring filename = itr->path().file_string();
			ColourMap::TYPE type = tempColourMap->ReadType(filename);
			ColourMapPtr colourMap;
			if(type == ColourMap::CONTINUOUS)
			{
				colourMap.reset(new ColourMapContinuous());
				bSuccess = colourMap->Load(filename);
			}
			else if(type == ColourMap::DISCRETE || type == ColourMap::CATEGORICAL)
			{
				colourMap.reset(new ColourMapDiscrete());
				bSuccess = colourMap->Load(filename);
			}
			else
			{
				utils::Log::Inst().Error(_T("ColourMapManager::LoadColourMaps(): invalid colour map found in colour map directory."));
				return false;
			}


			if(bSuccess)
			{
				m_colourMaps[colourMap->GetName()] = colourMap;
			}
			else
			{
				utils::Log::Inst().Error(_T("ColourMapManager::LoadColourMaps(): failed to parse colour map found in colour map directory."));
				return false;
			}
		}
  }

	return true;
}

std::vector<std::wstring> ColourMapManager::GetCategoricalMaps() const
{
	std::vector<std::wstring> maps;

	typedef std::pair<std::wstring, ColourMapPtr> pair_t;
	foreach(pair_t map, m_colourMaps)
	{
		if(map.second->GetType() == ColourMap::CATEGORICAL)
			maps.push_back(map.first);
	}

	return maps;
}

std::vector<std::wstring> ColourMapManager::GetContinuousMaps() const
{
	std::vector<std::wstring> maps;

	typedef std::pair<std::wstring, ColourMapPtr> pair_t;
	foreach(pair_t map, m_colourMaps)
	{
		if(map.second->GetType() == ColourMap::CONTINUOUS)
			maps.push_back(map.first);
	}

	return maps;
}

std::vector<std::wstring> ColourMapManager::GetDiscreteMaps() const
{
	std::vector<std::wstring> maps;

	typedef std::pair<std::wstring, ColourMapPtr> pair_t;
	foreach(pair_t map, m_colourMaps)
	{
		if(map.second->GetType() == ColourMap::DISCRETE)
			maps.push_back(map.first);
	}

	return maps;
}