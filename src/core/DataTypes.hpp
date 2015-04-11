//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _DATA_TYPES_
#define _DATA_TYPES_

// basic data types
typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned long ulong;

// smart pointers to classes
namespace pygmy
{
	class Filter;
	typedef boost::shared_ptr<Filter> FilterPtr;

	class TextSearch;
	typedef boost::shared_ptr<TextSearch> TextSearchPtr;

	class MetadataInfo;
	typedef boost::shared_ptr<MetadataInfo> MetadataInfoPtr;

	class ViewportOverview;
	typedef ViewportOverview* ViewportOverviewPtr;

	class ViewportTree;
	typedef ViewportTree* ViewportTreePtr;

	class ViewportMain;
	typedef ViewportMain* ViewportMainPtr;

	class VisualColourMap;
	typedef boost::shared_ptr<VisualColourMap> VisualColourMapPtr;

	class VisualObject;
	typedef boost::shared_ptr<VisualObject> VisualObjectPtr;

	class VisualTree;
	typedef boost::shared_ptr<VisualTree> VisualTreePtr;
}

namespace glUtils
{
	class Viewport;
	typedef Viewport* ViewportPtr;	// smart pointer are not used here since wxWidgets objects
																	// handle deallocation internally	

	class ViewportOrtho;
	typedef ViewportOrtho* ViewportOrthoPtr;	// smart pointer are not used here since wxWidgets objects
																						// handle deallocation internally	
	class Font;
	typedef boost::shared_ptr<Font> FontPtr;
}

namespace utils
{
	class Colour;
	typedef boost::shared_ptr<Colour> ColourPtr;
	
	class ColourMap;
	typedef boost::shared_ptr<ColourMap> ColourMapPtr;

	class ColourMapContinuous;
	typedef boost::shared_ptr<ColourMapContinuous> ColourMapContinuousPtr;

	class ColourMapDiscrete;
	typedef boost::shared_ptr<ColourMapDiscrete> ColourMapDiscretePtr;

	class ColourMapManager;
	typedef boost::shared_ptr<ColourMapManager> ColourMapManagerPtr;

	class ParsimonyCalculator;
	typedef boost::shared_ptr<ParsimonyCalculator> ParsimonyCalculatorPtr;

}

#endif
