//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../core/VisualColourMap.hpp"

#include "../core/State.hpp"
#include "../core/MetadataInfo.hpp"

#include "../glUtils/ErrorGL.hpp"
#include "../glUtils/Font.hpp"

#include "../utils/ColourMap.hpp"
#include "../utils/ColourMapDiscrete.hpp"
#include "../utils/ColourMapContinuous.hpp"

#include "../utils/StringTools.hpp"
#include "../utils/AlphaNumericSorter.hpp"

using namespace pygmy;
using namespace utils;

void VisualColourMap::Render(int width, int height)
{
	glUtils::ErrorGL::Check();

	if(!State::Inst().GetShowColourMapVis())
	{
		m_width = 0;
		return;
	}

	if(m_colourMap->GetType() == ColourMap::DISCRETE || m_colourMap->GetType() == ColourMap::CATEGORICAL)
	{
		ColourMapDiscretePtr discreteMap = boost::dynamic_pointer_cast<ColourMapDiscrete>(m_colourMap);

		RenderDiscreteMap(discreteMap, width, height);
	}
	else if(m_colourMap->GetType() == ColourMap::CONTINUOUS)
	{
		ColourMapContinuousPtr continuousMap = boost::dynamic_pointer_cast<ColourMapContinuous>(m_colourMap);
		
		RenderContinuousMap(continuousMap, width, height);
	}

	glUtils::ErrorGL::Check();
}

void VisualColourMap::RenderDiscreteMap(ColourMapDiscretePtr colourMap, int width, int height)
{
	glUtils::ErrorGL::Check();

	Point border = State::Inst().GetBorderSize();

	State::Inst().GetFont()->SetSize(State::Inst().GetColourMapFontSize());

	// *** Render labels
	Colour colour = State::Inst().GetColourMapFontColour();
	glColor3f(colour.GetRed(), colour.GetGreen(), colour.GetBlue());
	FieldInfo fieldInfo = m_metadataInfo->GetInfo(State::Inst().GetMetadataField());

	// determine number of colour bins
	uint bins = fieldInfo.values.size();
	if(colourMap->GetSize() < bins)
		bins = colourMap->GetSize();

	float labelWidthMax = 0;
	bool bDiscreteValues = false;
	if(fieldInfo.dataType == FieldInfo::CATEGORICAL || fieldInfo.values.size() <= colourMap->GetSize())
	{
		bDiscreteValues = true;

		// find widest label		
		std::vector< std::wstring > values;
		foreach(std::wstring value, fieldInfo.values)
		{
			value = utils::StringTools::FormatNumberStr(value, 
																									State::Inst().GetColourMapFontPrecision(), 
																									State::Inst().GetColourMapFontScientific());
			values.push_back(value);

			BBox bbox = State::Inst().GetFont()->GetBoundingBox(value);
			if(bbox.Width() > labelWidthMax)
					labelWidthMax = bbox.Width();
		}

		utils::AlphaNumericSorter::Sort(values);

		// render labels
		float dy = (height - border.y*2) / bins;
		float y = border.y + dy*0.5;
		foreach(std::wstring value, values)
		{
			BBox bbox = State::Inst().GetFont()->GetBoundingBox(value);
			State::Inst().GetFont()->Render(value, width-border.x-labelWidthMax, int(y - bbox.Height()*0.5 + 0.5));

			y += dy;
		}
	}
	else
	{
		// Label division between each bin:

		// find widest label	
		float dValue = (fieldInfo.maxValue - fieldInfo.minValue) / bins;
		float value = fieldInfo.minValue;
		std::vector< std::wstring > values;
		for(uint i = 0; i < bins+1; ++i)
		{
			std::wstring valueStr = utils::StringTools::ToString(value, 
																								State::Inst().GetColourMapFontPrecision(), 
																								State::Inst().GetColourMapFontScientific());
			values.push_back(valueStr);

			BBox bbox = State::Inst().GetFont()->GetBoundingBox(valueStr);
			if(bbox.Width() > labelWidthMax)
				labelWidthMax = bbox.Width();

			value += dValue;
		}
			
		// render labels
		float dy = (height - border.y*2) / bins;
		float y = border.y;
		for(uint i = 0; i < bins+1; ++i)
		{
			BBox bbox = State::Inst().GetFont()->GetBoundingBox(values.at(i));
			State::Inst().GetFont()->Render(values.at(i), width-border.x-labelWidthMax, int(y - bbox.Height()*0.5 + 0.5));

			value += dValue;
			y += dy;
		}
	}

	// *** Render colour map bar
	m_width = State::Inst().GetColourMapWidth() + labelWidthMax + m_fontOffset;
	uint x = width - border.x - m_width;
	float y = border.y;

	float dy = (height - border.y*2) / bins;
	uint dx = State::Inst().GetColourMapWidth();

	for(uint i = 0; i < bins; ++i)
	{
		// Note: the y value is purposely incremented in this manner to ensure that rounding errors
		// do not cause the different colour map segments to have a 1 pixel gap between them.
		colourMap->GetColour(i).SetColourOpenGL();
		glBegin(GL_QUADS);
			glVertex2i(x + dx, int(y));
			glVertex2i(x, int(y));

			y += dy;	
			glVertex2i(x, int(y));
			glVertex2i(x + dx, int(y));
		glEnd();			
	}

	if(State::Inst().GetShowColourMapTickMarks() && !bDiscreteValues)
		RenderUniqueValueMarks(width, height);

	glUtils::ErrorGL::Check();
}

void VisualColourMap:: RenderContinuousMap(ColourMapContinuousPtr colourMap, int width, int height)
{
	glUtils::ErrorGL::Check();

	Point border = State::Inst().GetBorderSize();
	State::Inst().GetFont()->SetSize(State::Inst().GetColourMapFontSize());

	// *** Render labels
	Colour colour = State::Inst().GetColourMapFontColour();
	glColor3f(colour.GetRed(), colour.GetGreen(), colour.GetBlue());

	FieldInfo fieldInfo = m_metadataInfo->GetInfo(State::Inst().GetMetadataField());
	float labelWidthMax = 0;
	if(fieldInfo.dataType == FieldInfo::NUMERICAL)
	{
		// find widest label
		uint valuesToDisplay = State::Inst().GetColourMapValuesToDisplay();
		float stepSize = (fieldInfo.maxValue - fieldInfo.minValue) / (valuesToDisplay-1);
		float value = fieldInfo.minValue;
		for(uint i = 0; i < valuesToDisplay; ++i)
		{			
			std::wstring valueStr = utils::StringTools::ToString(value, 
																								State::Inst().GetColourMapFontPrecision(), 
																								State::Inst().GetColourMapFontScientific());

			BBox bbox = State::Inst().GetFont()->GetBoundingBox(valueStr);
			if(bbox.Width() > labelWidthMax)
				labelWidthMax = bbox.Width();

			value += stepSize;
		}

		// render labels
		value = fieldInfo.minValue;
		float y = border.y;
		float dy = (height - border.y*2) / (valuesToDisplay-1);
		for(uint i = 0; i < valuesToDisplay; ++i)
		{	
			std::wstring valueStr = utils::StringTools::ToString(value, 
																								State::Inst().GetColourMapFontPrecision(), 
																								State::Inst().GetColourMapFontScientific());

			if(utils::StringTools::IsIntegerNumber(valueStr))
			{
				valueStr = valueStr.substr(0, valueStr.find(_T(".")));
			}

			BBox bbox = State::Inst().GetFont()->GetBoundingBox(valueStr);
			State::Inst().GetFont()->Render(valueStr, width-border.x-labelWidthMax, int(y - bbox.Height()*0.5 + 0.5));

			value += stepSize;
			y += dy;
		}	
	}
	else
	{
		// find widest label
		foreach(std::wstring value, fieldInfo.values)
		{
			value = utils::StringTools::FormatNumberStr(value, 
																								State::Inst().GetColourMapFontPrecision(), 
																								State::Inst().GetColourMapFontScientific());
			BBox bbox = State::Inst().GetFont()->GetBoundingBox(value);
			if(bbox.Width() > labelWidthMax)
					labelWidthMax = bbox.Width();
		}

		// render labels
		float dy = (height - border.y*2) / (fieldInfo.values.size()-1);
		float y = border.y;
		foreach(std::wstring value, fieldInfo.values)
		{
			value = utils::StringTools::FormatNumberStr(value, 
																								State::Inst().GetColourMapFontPrecision(), 
																								State::Inst().GetColourMapFontScientific());
			BBox bbox = State::Inst().GetFont()->GetBoundingBox(value);
			State::Inst().GetFont()->Render(value, width-border.x-labelWidthMax, int(y - bbox.Height()*0.5 + 0.5));

			y += dy;
		}
	}

	// *** Render colour map
	m_width = State::Inst().GetColourMapWidth() + labelWidthMax + m_fontOffset;
	uint x = width - border.x - m_width;
	float y = border.y;

	uint colours = colourMap->GetSize();
	float dy = (height - border.y*2) / (colours-1);
	uint dx = State::Inst().GetColourMapWidth();

	for(uint i = 0; i < colours-1; ++i)
	{
		// Note: the y value is purposely incremented in this manner to ensure that rounding errors
		// do not cause the different colour map segments to have a 1 pixel gap between them.
		glBegin(GL_QUADS);
			colourMap->GetColour(i).SetColourOpenGL();
			glVertex2i(x + dx, int(y));
			glVertex2i(x, int(y));

			y += dy;
			colourMap->GetColour(i+1).SetColourOpenGL();
			glVertex2i(x, int(y));
			glVertex2i(x + dx, int(y));
		glEnd();	
	}

	if(State::Inst().GetShowColourMapTickMarks() && fieldInfo.dataType == FieldInfo::NUMERICAL)
		RenderUniqueValueMarks(width, height);

	glUtils::ErrorGL::Check();
}

void VisualColourMap::RenderUniqueValueMarks(int width, int height)
{
	Point border = State::Inst().GetBorderSize();
	FieldInfo fieldInfo = m_metadataInfo->GetInfo(State::Inst().GetMetadataField());

	foreach(const std::wstring& valueStr, fieldInfo.values)
	{
		float value = utils::StringTools::ToFloat(valueStr);
		float pos = (value - fieldInfo.minValue) / (fieldInfo.maxValue - fieldInfo.minValue);
		
		int colourMapWidth = State::Inst().GetColourMapWidth();
		int markerHeight = int((height - border.y*2)*pos + border.y + 0.5);
		int markerXstart = int(width - border.x - m_width + colourMapWidth*0.25);
		int markerXend = int(markerXstart + colourMapWidth*0.5);

		glDisable(GL_LINE_SMOOTH);

		glLineWidth(1.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
			glVertex2i(markerXstart, markerHeight);
			glVertex2i(markerXend, markerHeight);
		glEnd();

		glEnable(GL_LINE_SMOOTH);
	}
}