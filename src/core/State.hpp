//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _STATE_H_
#define _STATE_H_

#include <string>
#include <ticpp/ticpp.h>

#include "../utils/Point.hpp"

#include "../utils/Colour.hpp"

namespace pygmy
{

/**
 * @brief Singleton class for holding current application state.
 */
class State
{
public:
	/** Destructor */
	~State() {}

	/** Get the one and only instance of the state class. */
	static State& Inst();

	/** OpenGL font to use for rendering text in application. */
	const glUtils::FontPtr GetFont() const { return m_font; }

	/** TrueType font to use in application (i.e., times.ttf, arial.ttf) */
	void SetFontFile(const std::wstring& fontFile) { m_fontFile = fontFile; }

	/** TrueType font to use in application (i.e., times.ttf, arial.ttf) (read-only) */
	const std::wstring& GetFontFile() const { return m_fontFile; }

	/** Set size of tree font. */
	void SetTreeFontSize(uint size) { m_treeFontSize = size; }

	/** Get size of tree font. */
	uint GetTreeFontSize() const { return m_treeFontSize; }

	/** Set colour of tree font. */
	void SetTreeFontColour(const utils::Colour& colour) { m_treeFontColour = colour; }

	/** Get colour of tree font. */
	const utils::Colour& GetTreeFontColour() const { return m_treeFontColour; }

	/** Set size of colour map font. */
	void SetColourMapFontSize(uint size) { m_colourMapFontSize = size; }

	/** Get size of colour map font. */
	uint GetColourMapFontSize() const { return m_colourMapFontSize; }

	/** Set colour of colour map font. */
	void SetColourMapFontColour(const utils::Colour& colour) { m_colourMapFontColour = colour; }

	/** Get colour of colour map font. */
	const utils::Colour& GetColourMapFontColour() const { return m_colourMapFontColour; }

	/** Get colour map font precision. */
	uint GetColourMapFontPrecision() const { return m_colourMapFontPrecision; }

	/** Set colour map font precision. */
	void SetColourMapFontPrecision(uint precision) { m_colourMapFontPrecision = precision; }

	/** Get number of values to display on continous colour map. */
	uint GetColourMapValuesToDisplay() { return m_colourMapLegendValuesToShow; }

	/** Set number of values to display on continous colour map. */
	void SetColourMapValuesToDisplay(uint values) { m_colourMapLegendValuesToShow = values; }

	/** Get flag indicating if values should be written in scientific notation. */
	bool GetColourMapFontScientific() { return m_bColourMapScientific; }

	/** Set flag indicating if values should be written in scientific notation. */
	void SetColourMapFontScientific(bool state) { m_bColourMapScientific = state; }

	/** Set width of lines. */
	void SetLineWidth(float width) { m_lineWidth = width; }

	/** Get width of lines. */
	const float& GetLineWidth() const { return m_lineWidth; }

	/** Set width of overview tree lines. */
	void SetOverviewLineWidth(float width) { m_overviewLineWidth = width; }

	/** Get width of overview treelines. */
	const float& GetOverviewLineWidth() const { return m_overviewLineWidth; }

	/** Default zoom level. */
	void SetZoomDefault(float zoomDefault) { m_zoomDefault = zoomDefault; }

	/** Default zoom level. */
	const float& GetZoomDefault() const { return m_zoomDefault; }

	/** Maximum zoom level. */
	void SetZoomMax(float zoomMax) { m_zoomMax = zoomMax; }

	/** Maximum zoom level. */
	const float& GetZoomMax() const { return m_zoomMax; }

	/** Set size of border (in pixels). */
	void SetBorderSize(utils::Point& borderSize) { m_border = borderSize; }

	/** Get size of border (in pixels). */
	const utils::Point& GetBorderSize() const { return m_border; }

	/** Set width of colour map visualization. */
	void SetColourMapWidth(float width) { m_colourMapWidth = width; }

	/** Get width of colour map visualization. */
	float GetColourMapWidth() { return m_colourMapWidth; }

	/** Set flag indicating if colour map visualization should be shown. */
	void SetShowColourMapVis(bool state) { m_bShowColourMapVis = state; }

	/** Get flag indicating if colour map visualization should be shown. */
	bool GetShowColourMapVis() { return m_bShowColourMapVis; }

	/** Set flag indicating if colour map tick marks should be shown. */
	void SetShowColourMapTickMarks(bool state) { m_bShowColourMapTickMarks = state; }

	/** Get flag indicating if colour map tick marks should be shown. */
	bool GetShowColourMapTickMarks() { return m_bShowColourMapTickMarks; }

	/** Leaf node label offset (in pixels). */
	void SetLabelOffset(uint offset) { m_labelOffset = offset; }

	/** Leaf node label offset (in pixels). */
	const uint& GetLabelOffset() const { return m_labelOffset; }

	/** Distance label offset along y-axis (in pixels). */
	void SetDistanceOffsetY(uint offset) { m_distanceOffsetY = offset; }

	/** Distance label offset along y-axis  (in pixels). */
	const uint& GetDistanceOffsetY() const { return m_distanceOffsetY; }

	/** Distance label offset along x-axis (in pixels). */
	void SetDistanceOffsetX(uint offset) { m_distanceOffsetX = offset; }

	/** Distance label offset along x-axis  (in pixels). */
	uint GetDistanceOffsetX() const { return m_distanceOffsetX; }

	/** Flag indicating if labels should be shown on internal nodes. */
	void SetShowInternalLabels(bool state) { m_bShowInternalLabels = state; }

	/** Flag indicating if labels should be shown on internal nodes. */
	bool GetShowInternalLabels() const { return m_bShowInternalLabels; }

	/** Set field of internal nodes to display. */
	void SetInternalNodeField(const std::wstring& field) { m_internalLabelField = field; }

	/** Get field of internal nodes to display. */
	std::wstring GetInternalNodeField() const { return m_internalLabelField; }

	/** Set size of internal node font. */
	void SetInternalNodeFontSize(uint size) { m_internalLabelSize = size; }

	/** Get size of internal node font. */
	uint GetInternalNodeFontSize() const { return m_internalLabelSize; }

	/** Set colour of internal node font. */
	void SetInternalNodeFontColour(const utils::Colour& colour) { m_internalLabelColour = colour; }

	/** Get colour of internal node font. */
	const utils::Colour& GetInternalNodeFontColour() const { return m_internalLabelColour; }

	/** Set precision of internal node font. */
	void SetInternalNodeFontPrecision(uint precision) { m_internalLabelPrecision = precision; }

	/** Get precision of internal node font. */
	uint GetInternalNodeFontPrecision() const { return m_internalLabelPrecision; }

	/** Set flag indicating if internal node values should be written in scientific notation. */
	void SetInternalNodeFontScientific(bool state) { m_bInternalLabelScientific = state; }

	/** Get flag indicating if internal node values should be written in scientific notation. */
	bool GetInternalNodeFontScientific() { return m_bInternalLabelScientific; }

	/** Set desired position of internal labels. */
	void SetInternalLabelPos(const std::wstring& pos) { m_internalLabelPos = pos; }

	/** Get desired position of internal labels. */
	std::wstring GetInternalLabelPos() const { return m_internalLabelPos; }

	/** Sensitivity of scroll wheel translation. */
	void SetScrollSensitivity(float sensitivity) { m_scrollSensitivity = sensitivity; }

	/** Sensitivity of scroll wheel translation. */
	const float& GetScrollSensitivity() const { return m_scrollSensitivity; }

	/** Sensitivity of mouse dragging for translation. */
	void SetTranslationSensitivity(float sensitivity) { m_translationSensitivity = sensitivity; }

	/** Sensitivity of mouse dragging for translation. */
	const float& GetTranslationSensitivity() const { return m_translationSensitivity; }

	/** Sensitivity of mouse dragging for zoom. */
	void SetZoomSensitivity(float sensitivity) { m_zoomSensitivity = sensitivity; }

	/** Sensitivity of mouse dragging for zoom. */
	const float& GetZoomSensitivity() const { return m_zoomSensitivity; }

	/** Set show leaf labels flag. */
	void SetShowLeafLabels(bool state) { m_bShowLeafLabels = state; }

	/** Get flag indicating if leaf labels should be shown. */
	bool GetShowLeafLabels() { return m_bShowLeafLabels; }

	/** Set flag indicating if metadata label should be shown. */
	void SetShowMetadataLabels(bool state) { m_bShowMetadataLabels = state; }

	/** Get flag indicating if metadata labels should be shown. */
	bool GetShowMetadataLabels() { return m_bShowMetadataLabels; }

	/** Set metadata field. */
	void SetMetadataField(const std::wstring& field) { m_metadataField = field; }

	/** Get metadata field. */
	const std::wstring& GetMetadataField() { return m_metadataField; }
	
	/** Set flag indicating if overview tree should be rendered in colour. */
	void SetColourOverviewTree(bool state) { m_bColourOverviewTree = state; }

	/** Get flag indicating if overview tree should be rendered in colour. */
	bool GetColourOverviewTree() { return m_bColourOverviewTree; }

	/** Set flag indicating if the overview position overlay should be rendered. */
	void SetOverviewPositionOverlay(bool state) { m_bOverviewPosOverlay = state; }

	/** Get flag indicating if the overview position overlay should be rendered. */
	bool GetOverviewPositionOverlay() { return m_bOverviewPosOverlay; }

	/** Set colour of missing data. */
	void SetColourMissingData(utils::Colour colour) { m_missingDataColour = colour; }

	/** Get colour of missing data. */
	utils::Colour GetColourMissingData() { return m_missingDataColour; }

	/** Set default colour for tree. */
	void SetDefaultTreeColour(utils::Colour colour) { m_defaultTreeColour = colour; }

	/** Get default colour for tree. */
	utils::Colour GetDefaultTreeColour() { return m_defaultTreeColour; }

	/** Set flag indicating if leaf nodes with missing data should be ignored. */
	void SetIgnoreMissingData(bool state) { m_bIgnoreLeafNodes = state; }

	/** Get flag indicating if leaf nodes with missing data should be ignored. */
	bool GetIgnoreMissingData() { return m_bIgnoreLeafNodes; }

	/** Set flag indicating if ordering of leaf nodes should be optimized. */
	void SetOptimizeLeafNodeOrdering(bool state) { m_bOptimizeLeafNodes = state; }

	/** Get flag indicating if ordering of leaf nodes should be optimized. */
	bool GetOptimizeLeafNodeOrdering() { return m_bOptimizeLeafNodes; }

	/**
	 * @brief Load project settings from file.
	 * @param filename XML file containing project settings.
	 */
	void Load(const std::wstring& filename);

	/** Save settings. */
	void Save(const std::wstring& filename);

protected:
	/** Private singleton constructor (must instantiate  this class through Inst()). */
  State();

	/** Private copy constructor (must instantiate  this class through Inst()). */
  State(const State&);

	/** Private assignment constructor (must instantiate  this class through Inst()). */
  State& operator= (const State&);

private:
	/** TinyXML++ document reader. */
	ticpp::Document m_doc;
	
	/** Name of file holding project settings. */
	std::wstring m_settingsFile;

	/** Font to use in project. */
	std::wstring m_fontFile;

	/** Pointer to font class used to render TrueType fonts on an OpenGL canvas. */
	glUtils::FontPtr m_font;

	/** Size of tree font. */
	uint m_treeFontSize;

	/** Colour of tree font. */
	utils::Colour m_treeFontColour;

	/** Size of colour map font. */
	uint m_colourMapFontSize;

	/** Colour of colour map font. */
	utils::Colour m_colourMapFontColour;

	/** Precision of colour map font. */
	uint m_colourMapFontPrecision;

	/** Number of values to display on continuous colour map. */
	uint m_colourMapLegendValuesToShow;

	/** Flag indicating if values should be written in scientific notation. */
	bool m_bColourMapScientific;

	/** Width of lines. */
	float m_lineWidth;

	/** Width of overview tree lines. */
	float m_overviewLineWidth;

	/** Default zoom. */
	float m_zoomDefault;

	/** Maximum zoom. */
	float m_zoomMax;

	/** Size of border. */
	utils::Point m_border;

	/** Width of colour map visualization. */
	float m_colourMapWidth;

	/** Flag indicating if colour map visualization should be shown. */
	bool m_bShowColourMapVis;

	/** Flag indicating if colour map tick marks should be shown. */
	bool m_bShowColourMapTickMarks;

	/** Leaf node label offset. */
	uint m_labelOffset;

	/** Distance label offset. */
	uint m_distanceOffsetX, m_distanceOffsetY;

	/** Flag indicating if labels should be shown on internal nodes. */
	bool m_bShowInternalLabels;

	/** Field of internal nodes to display. */
	std::wstring m_internalLabelField;

	/** Size of internal node font. */
	uint m_internalLabelSize;

	/** Colour of internal node font. */
	utils::Colour m_internalLabelColour;

	/** Precision of internal node font. */
	uint m_internalLabelPrecision;

	/** Flag indicating if internal node values should be written in scientific notation. */
	bool m_bInternalLabelScientific;

	/** Get desired position of internal labels. */
	std::wstring m_internalLabelPos; 

	/** Sensitivity of scroll wheel. */
	float m_scrollSensitivity;

	/** Sensitivity of scroll wheel. */
	float m_translationSensitivity;

	/** Sensitivity of scroll wheel. */
	float m_zoomSensitivity;

	/** Flag indicating if leaf labels should be shown. */
	bool m_bShowLeafLabels;

	/** Flag indicating if metadata labels should be shown. */
	bool m_bShowMetadataLabels;

	/** Metadata field. */
	std::wstring m_metadataField; 

	/** Flag indicating if overview tree should be rendered in colour. */
	bool m_bColourOverviewTree;

	/** Flag indicating if the overview position overlay should be rendered. */
	bool m_bOverviewPosOverlay;

	/** Colour of missing data. */
	utils::Colour m_missingDataColour;

	/** Default tree colour. */
	utils::Colour m_defaultTreeColour;

	/** Flag indicating if leaf nodes with missing data should be ignored. */
	bool m_bIgnoreLeafNodes;

	/** Flag indicating if ordering of leaf nodes should be optimized. */
	bool m_bOptimizeLeafNodes;
};

}

#endif