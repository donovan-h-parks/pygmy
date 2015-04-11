//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../utils/ShapeMapManager.hpp"
#include "../utils/ShapeMap.hpp"
#include "../utils/Log.hpp"

using namespace GenGIS;

ShapeMapPtr ShapeMapManager::GetDefaultShapeMap()
{
	ShapeMapConstIter it = m_shapeMaps.find(_T("Standard"));
	if(it == m_shapeMaps.end())
	{
		error::Log::Inst().Error("ShapeMapManager::GetDefaultShapeMap: default shape map is missing.");
		return m_shapeMaps.begin()->second;
	}

	return it->second;
}

ShapeMapPtr ShapeMapManager::GetShapeMap(const std::wstring& name)
{
	ShapeMapConstIter it = m_shapeMaps.find(name);
	if(it == m_shapeMaps.end())
	{
		error::Log::Inst().Error("ShapeMapManager::GetShapeMap: unrecognized shape map name.");
		return m_shapeMaps.begin()->second;
	}

	return it->second;
}

void ShapeMapManager::BuildShapeMaps()
{
	ShapeMapPtr standardShapeMap = BuildStandardShapeMap();
	m_shapeMaps[_T("Standard")] = standardShapeMap;
}

ShapeMapPtr ShapeMapManager::BuildStandardShapeMap()
{
	ShapeMapPtr shapeMap(new ShapeMap(_T("Standard")));

	// set all possible shapes supported by shape map
	shapeMap->AddShape(VisualMarker::CIRCLE);
	shapeMap->AddShape(VisualMarker::SQUARE);
	shapeMap->AddShape(VisualMarker::TRIANGLE);
	shapeMap->AddShape(VisualMarker::PLUS_SIGN);
	shapeMap->AddShape(VisualMarker::DIAMOND);
	shapeMap->AddShape(VisualMarker::INVERTED_TRIANGLE);
	shapeMap->AddShape(VisualMarker::STAR);
	shapeMap->AddShape(VisualMarker::HEXAGON);

	return shapeMap;
}
