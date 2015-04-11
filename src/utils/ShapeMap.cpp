//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../utils/ShapeMap.hpp"
#include "../utils/Log.hpp"
#include "../utils/StringTools.hpp"

using namespace GenGIS;

ShapeMap::ShapeMap(ShapeMapPtr shapeMap)
{
	CopyShapeMap(shapeMap);
}

void ShapeMap::CopyShapeMap(ShapeMapPtr shapeMap)
{
	m_name = shapeMap->GetName();

	m_shapeMap.clear();
	for(uint i = 0; i < shapeMap->GetSize(); ++i)
		m_shapeMap.push_back(shapeMap->GetShape(i));

	m_shapeMap = shapeMap->GetShapeMap();
	m_shapeNames = shapeMap->GetNameToShapeMap();
}

void ShapeMap::SetShape(const std::wstring& name, VisualMarker::MARKER_SHAPE shape) 
{ 
	std::map<std::wstring, VisualMarker::MARKER_SHAPE>::iterator it = m_shapeNames.find(name);
	if(it != m_shapeNames.end())
	{
		it->second = shape;
	}
	else
	{
		m_shapeNames[name] = shape;
	}
}

bool ShapeMap::GetShape(std::wstring name, VisualMarker::MARKER_SHAPE& shape) const 
{ 
	std::map<std::wstring, VisualMarker::MARKER_SHAPE>::const_iterator it = m_shapeNames.find(name);
	if(it == m_shapeNames.end())
	{
		shape = m_shapeMap.at(0);
		return false;
	}

	shape = it->second;
	return true;
}

const VisualMarker::MARKER_SHAPE ShapeMap::GetShape(uint index) const
{ 
	if(index < m_shapeMap.size())
	{
		return m_shapeMap.at(index);
	}

	return VisualMarker::CIRCLE;
}

void ShapeMap::SetCustom(bool custom) 
{ 
	m_bCustom = custom;

	if(m_bCustom)
		m_name = _T("Custom");
}

VisualMarker::MARKER_SHAPE ShapeMap::ToShape(std::wstring str)
{
	if(str == _T("Circle"))
		return VisualMarker::CIRCLE;
	else if(str == _T("Square"))
		return VisualMarker::SQUARE;
	else if(str == _T("Triangle"))
		return VisualMarker::TRIANGLE;
	else if(str == _T("Star"))
		return VisualMarker::STAR;
	else if(str == _T("Plus sign"))
		return VisualMarker::PLUS_SIGN;
	else if(str == _T("Hexagon"))
		return VisualMarker::HEXAGON;
	else if(str == _T("Diamond"))
		return VisualMarker::DIAMOND;
	else if(str == _T("Inverted triangle"))
		return VisualMarker::INVERTED_TRIANGLE;

	assert(false);
	error::Log::Inst().Error("ShapeMap::ToShape(): unrecognized shape string.");
	return VisualMarker::CIRCLE;
}

std::wstring ShapeMap::ToStringW(VisualMarker::MARKER_SHAPE shape)
{
	if(shape == VisualMarker::CIRCLE)
		return _T("Circle");
	else if(shape == VisualMarker::SQUARE)
		return _T("Square");
	else if(shape == VisualMarker::TRIANGLE)
		return _T("Triangle");
	else if(shape == VisualMarker::STAR)
		return _T("Star");
	else if(shape == VisualMarker::PLUS_SIGN)
		return _T("Plus sign");
	else if(shape == VisualMarker::HEXAGON)
		return _T("Hexagon");
	else if(shape == VisualMarker::DIAMOND)
		return _T("Diamond");
	else if(shape == VisualMarker::INVERTED_TRIANGLE)
		return _T("Inverted triangle");

	assert(false);
	error::Log::Inst().Error("ShapeMap::ToStringW(): unrecognized shape.");
	return _T("Circle");
}
