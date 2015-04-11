//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _GENGIS_SHAPE_MAP_
#define _GENGIS_SHAPE_MAP_

#include "../core/Precompiled.hpp"

#include "../core/VisualMarker.hpp"

namespace GenGIS
{

/**
 * @class ShapeMap
 * @brief Stores a set of shapes that can be access by name.
 */
class ShapeMap
{
public:
	/** Constructor. */
	ShapeMap(const std::wstring& name = _T("<no name>")): m_name(name), m_bCustom(false) {}

	/** Constructor. */
	ShapeMap(ShapeMapPtr shapeMap);

	/** Destructor. */
	virtual ~ShapeMap() {}

	/** 
	 * @brief Assign shape to a given name. 
	 * @param name Name to associate with this shape.
	 * @param shape Desired shape.
	 */
	void SetShape(const std::wstring& name, VisualMarker::MARKER_SHAPE shape);

	/** Get shape assigned to a given name. */
	bool GetShape(std::wstring name, VisualMarker::MARKER_SHAPE& shape) const;

	/** Get number of specified name to shape associations. */
	uint GetShapeToNameMapSize() { return m_shapeNames.size(); }

	/** Set name of colour map. */
	void SetName(const std::wstring& name) { m_name = name; }
  
	/** Get name of colour map. */
	const std::wstring& GetName() const { return m_name; }

	/** Clear names associated with shapes. */
	void ClearNames() { m_shapeNames.clear(); }
  
	/** 
	 * @brief Copy shape map. 
	 * @param shapeMap Shape map to copy shapes from.
	 */
	virtual void CopyShapeMap(ShapeMapPtr shapeMap);

	/** Set shape map as being custom or predefined. */
	void SetCustom(bool custom);

	/** Get map which associates names with shape indices. */
	std::map<std::wstring, VisualMarker::MARKER_SHAPE> GetNameToShapeMap() { return m_shapeNames; }

	/** Convert a string to its corresponding shape. */
	VisualMarker::MARKER_SHAPE ToShape(std::wstring str);

	/** Convert a shape to its corresponding string. */
	std::wstring ToStringW(VisualMarker::MARKER_SHAPE shape);

	/** Get the size of the shape map. */
	uint GetSize() const { return m_shapeMap.size(); }

	/** Get shape from shape map by index. */
	const VisualMarker::MARKER_SHAPE GetShape(uint index) const;

	/** Get all available shapes. */
	const std::vector<VisualMarker::MARKER_SHAPE>& GetShapeMap() const { return m_shapeMap; }

	/** Add shape. */
	void AddShape(VisualMarker::MARKER_SHAPE shape) { m_shapeMap.push_back(shape); }
	
protected:
	/** Shape map. */
	std::vector<VisualMarker::MARKER_SHAPE> m_shapeMap;

	/** Name associated with each shape index. */
	std::map<std::wstring, VisualMarker::MARKER_SHAPE> m_shapeNames;

	/** Name of shape map. */
	std::wstring m_name;

	/** Flag indicating if shape map is custom. */
	bool m_bCustom;
};

}

#endif
