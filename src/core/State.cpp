//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../core/State.hpp"
#include "../glUtils/Font.hpp"

using namespace pygmy;
using namespace utils;

State::State()
{
	
}

State& State::Inst()
{
	static State state;	
	return state;
}

void State::Load(const std::wstring& filename)
{
	m_settingsFile = filename;

	try
	{
		std::string str(m_settingsFile.begin(), m_settingsFile.end());
		m_doc.LoadFile(str);


		ticpp::Element* pRoot = m_doc.FirstChildElement();

		ticpp::Element* elem = pRoot->FirstChildElement("Font");

		std::string fontFile;
		elem->GetAttribute("file", &fontFile);
		m_fontFile = std::wstring(fontFile.begin(), fontFile.end());
		elem->GetAttribute("size", &m_treeFontSize);

		float red, green, blue;
		elem->GetAttribute("red", &red);
		elem->GetAttribute("green", &green);
		elem->GetAttribute("blue", &blue);

		m_treeFontColour = Colour(red, green, blue);

		elem = pRoot->FirstChildElement("Labels");
		elem->GetAttribute("showLeafLabels", &m_bShowLeafLabels);
		elem->GetAttribute("showMetadataLabels", &m_bShowMetadataLabels);

		elem = pRoot->FirstChildElement("Zoom");
		elem->GetAttribute("default", &m_zoomDefault);
		elem->GetAttribute("max", &m_zoomMax);

		elem = pRoot->FirstChildElement("Layout");
		elem->GetAttribute("borderX", &m_border.x);
		elem->GetAttribute("borderY", &m_border.y);
		elem->GetAttribute("labelOffset", &m_labelOffset);
		elem->GetAttribute("distanceOffsetX", &m_distanceOffsetX);
		elem->GetAttribute("distanceOffsetY", &m_distanceOffsetY);

		elem = pRoot->FirstChildElement("Tree");
		elem->GetAttribute("lineWidth", &m_lineWidth);
		elem->GetAttribute("optimizeLeafOrdering", &m_bOptimizeLeafNodes);

		elem = pRoot->FirstChildElement("InternalLabels");
		elem->GetAttribute("showLabels", &m_bShowInternalLabels);

		std::string internalLabelField;
		elem->GetAttribute("field", &internalLabelField);
		m_internalLabelField = std::wstring(internalLabelField.begin(), internalLabelField.end());

		std::string internalLabelPos;
		elem->GetAttribute("position", &internalLabelPos);
		m_internalLabelPos = std::wstring(internalLabelPos.begin(), internalLabelPos.end());

		elem->GetAttribute("fontSize", &m_internalLabelSize);
		elem->GetAttribute("fontPrecision", &m_internalLabelPrecision);
		elem->GetAttribute("scientific", &m_bInternalLabelScientific);
		elem->GetAttribute("red", &red);
		elem->GetAttribute("green", &green);
		elem->GetAttribute("blue", &blue);

		m_internalLabelColour = Colour(red, green, blue);

		elem = pRoot->FirstChildElement("Overview");
		elem->GetAttribute("lineWidth", &m_overviewLineWidth);
		elem->GetAttribute("colourTree", &m_bColourOverviewTree);
		elem->GetAttribute("showPositionOverlay", &m_bOverviewPosOverlay);

		elem = pRoot->FirstChildElement("ColourMapVis");
		elem->GetAttribute("width", &m_colourMapWidth);
		elem->GetAttribute("show", &m_bShowColourMapVis);
		elem->GetAttribute("showTickMarks", &m_bShowColourMapTickMarks);
		elem->GetAttribute("ignoreLeafNodes", &m_bIgnoreLeafNodes);

		elem = pRoot->FirstChildElement("ColourMapLabel");
		elem->GetAttribute("fontSize", &m_colourMapFontSize);
		elem->GetAttribute("fontPrecision", &m_colourMapFontPrecision);
		elem->GetAttribute("scientific", &m_bColourMapScientific);
		elem->GetAttribute("valuesToShow", &m_colourMapLegendValuesToShow);
		elem->GetAttribute("red", &red);
		elem->GetAttribute("green", &green);
		elem->GetAttribute("blue", &blue);

		m_colourMapFontColour = Colour(red, green, blue);

		elem = pRoot->FirstChildElement("MissingDataColour");
		elem->GetAttribute("red", &red);
		elem->GetAttribute("green", &green);
		elem->GetAttribute("blue", &blue);

		m_missingDataColour = Colour(red, green, blue);

		elem = pRoot->FirstChildElement("DefaultTreeColour");
		elem->GetAttribute("red", &red);
		elem->GetAttribute("green", &green);
		elem->GetAttribute("blue", &blue);

		m_defaultTreeColour = Colour(red, green, blue);

		elem = pRoot->FirstChildElement("Mouse");
		elem->GetAttribute("scrollSensitivity", &m_scrollSensitivity);
		elem->GetAttribute("translationSensitivity", &m_translationSensitivity);
		elem->GetAttribute("zoomSensitivity", &m_zoomSensitivity);		

		m_font.reset(new glUtils::Font(pygmy::App::Inst().GetExeDir() + GetFontFile()));
	}
	catch(...)
	{
		
	}
}

void State::Save(const std::wstring& filename)
{ 
	ticpp::Element* pRoot = m_doc.FirstChildElement();

	ticpp::Element* elem = pRoot->FirstChildElement("Font");

	std::string fontFile(m_fontFile.begin(), m_fontFile.end());
	elem->SetAttribute("file", fontFile);
	elem->SetAttribute("size", m_treeFontSize);

	elem->SetAttribute("red", m_treeFontColour.GetRed());
	elem->SetAttribute("green", m_treeFontColour.GetGreen());
	elem->SetAttribute("blue", m_treeFontColour.GetBlue());

	elem = pRoot->FirstChildElement("Labels");
	elem->SetAttribute("showLeafLabels", m_bShowLeafLabels);
	elem->SetAttribute("showMetadataLabels", m_bShowMetadataLabels);

	elem = pRoot->FirstChildElement("Zoom");
	elem->SetAttribute("default", m_zoomDefault);
	elem->SetAttribute("max", m_zoomMax);

	elem = pRoot->FirstChildElement("Layout");
	elem->SetAttribute("borderX", m_border.x);
	elem->SetAttribute("borderY", m_border.y);
	elem->SetAttribute("labelOffset", m_labelOffset);
	elem->SetAttribute("distanceOffsetX", m_distanceOffsetX);
	elem->SetAttribute("distanceOffsetY", m_distanceOffsetY);

	elem = pRoot->FirstChildElement("Tree");
	elem->SetAttribute("lineWidth", m_lineWidth);
	elem->SetAttribute("optimizeLeafOrdering", m_bOptimizeLeafNodes);

	elem = pRoot->FirstChildElement("InternalLabels");
	elem->SetAttribute("showLabels", m_bShowInternalLabels);

	std::string internalLabelField(m_internalLabelField.begin(), m_internalLabelField.end());
	elem->SetAttribute("field", internalLabelField);

	std::string internalLabelPos(m_internalLabelPos.begin(), m_internalLabelPos.end());
	elem->SetAttribute("position", internalLabelPos);
	elem->SetAttribute("fontSize", m_internalLabelSize);
	elem->SetAttribute("fontPrecision", m_internalLabelPrecision);
	elem->SetAttribute("scientific", m_bInternalLabelScientific);
	elem->SetAttribute("red", m_internalLabelColour.GetRed());
	elem->SetAttribute("green", m_internalLabelColour.GetGreen());
	elem->SetAttribute("blue", m_internalLabelColour.GetBlue());

	elem = pRoot->FirstChildElement("Overview");
	elem->SetAttribute("lineWidth", m_overviewLineWidth);
	elem->SetAttribute("colourTree", m_bColourOverviewTree);
	elem->SetAttribute("showPositionOverlay", m_bOverviewPosOverlay);

	elem = pRoot->FirstChildElement("ColourMapVis");
	elem->SetAttribute("width", m_colourMapWidth);
	elem->SetAttribute("show", m_bShowColourMapVis);
	elem->SetAttribute("showTickMarks", m_bShowColourMapTickMarks);
	elem->SetAttribute("ignoreLeafNodes", m_bIgnoreLeafNodes);

	elem = pRoot->FirstChildElement("ColourMapLabel");
	elem->SetAttribute("red", m_colourMapFontColour.GetRed());
	elem->SetAttribute("green", m_colourMapFontColour.GetGreen());
	elem->SetAttribute("blue", m_colourMapFontColour.GetBlue());
	elem->SetAttribute("fontSize", m_colourMapFontSize);
	elem->SetAttribute("fontPrecision", m_colourMapFontPrecision);
	elem->SetAttribute("scientific", m_bColourMapScientific);
	elem->SetAttribute("valuesToShow", m_colourMapLegendValuesToShow);

	elem = pRoot->FirstChildElement("MissingDataColour");
	elem->SetAttribute("red", m_missingDataColour.GetRed());
	elem->SetAttribute("green", m_missingDataColour.GetGreen());
	elem->SetAttribute("blue", m_missingDataColour.GetBlue());

	elem = pRoot->FirstChildElement("DefaultTreeColour");
	elem->SetAttribute("red", m_defaultTreeColour.GetRed());
	elem->SetAttribute("green", m_defaultTreeColour.GetGreen());
	elem->SetAttribute("blue", m_defaultTreeColour.GetBlue());

	elem = pRoot->FirstChildElement("Mouse");
	elem->SetAttribute("scrollSensitivity", m_scrollSensitivity);
	elem->SetAttribute("translationSensitivity", m_translationSensitivity);
	elem->SetAttribute("zoomSensitivity", m_zoomSensitivity);		
	
	std::string str(filename.begin(), filename.end());
	m_doc.SaveFile(str); 
}
