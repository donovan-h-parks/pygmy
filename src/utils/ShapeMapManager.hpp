//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _GENGIS_SHAPE_MAP_MANAGER_
#define _GENGIS_SHAPE_MAP_MANAGER_

namespace GenGIS
{

/**
 * @class ShapeMapManager
 * @brief Allow access to all shape maps supported by GenGIS.
 */
class ShapeMapManager
{
public:
	typedef std::map<std::wstring, ShapeMapPtr>::const_iterator ShapeMapConstIter;
	typedef std::pair<std::wstring, ShapeMapPtr> ShapeMapPair;

public:
	/** Constructor. */
	ShapeMapManager() { BuildShapeMaps(); }

	/** Destructor. */
	virtual ~ShapeMapManager() {}

	/** Get shape map with the provided name. */
	ShapeMapPtr GetShapeMap(const std::wstring& name);

	/** Get default shape map. */
	ShapeMapPtr GetDefaultShapeMap();

	/** Get shape maps. */
	const std::map<std::wstring, ShapeMapPtr>& GetShapeMaps() const { return m_shapeMaps; }
	
protected:
	/** Build all shape maps. */
	void BuildShapeMaps();

	/** Build standard shape map. */
	ShapeMapPtr BuildStandardShapeMap();

protected:
	/** All supported shape maps. */
	std::map<std::wstring, ShapeMapPtr> m_shapeMaps;
};

}

#endif
