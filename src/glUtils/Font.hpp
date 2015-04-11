//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _OPENGL_FONT_
#define _OPENGL_FONT_

#include "../utils/Common.hpp"

#include <FTGL/ftgl.h>

namespace glUtils
{

/**
 * @brief Render TrueType fonts on OpenGL canvas.
 */
class Font
{
public:
	/**
	 * @brief Build a new font.
	 * @param fontFile TrueType font file (e.g., times.ttf, arial.ttf).
	 */
	Font(const std::wstring& fontFile);

	/** Destructor. */
	~Font();

	/**
	 * @brief Change the font typeface.
	 * @param fontFile TrueType font file (e.g., times.ttf, arial.ttf).
	 */
	void SetTypeface(const std::wstring& fontFile);

	/**
	 * @brief Render text to current OpenGL canvas.
	 * @param text Text to render.
	 * @param x,y Location to render bottom, left corner of text.
	 */
	void Render(const std::wstring& text, uint x, uint y);

	/**
	 * @brief Set size of font.
	 * @param size Desired size of font.
	 * @throw Exception If font can not be set to specified size.
	 */
	void SetSize(uint size);

	/**
	 * @brief Get size of font.
	 * @return Size of font.
	 */
	uint GetSize() {	return m_font->FaceSize(); }

	/**
	 * @brief Get descender amount for font.
	 * @return Descender of font.
	 */
	float GetDescender() { return m_font->Descender(); }

	/**
	 * @brief Get ascender amount for font.
	 * @return Ascender of font.
	 */
	float GetAscender() { return m_font->Ascender(); }

	/**
	 * @brief Get bounding box of a string.
	 * @param text Text to determine bounding box of.
	 * @return Bounding box.
	 */
	utils::BBox GetBoundingBox(const std::wstring& text);

	/**
	 * @brief Type of font (e.g., Times.ttf, Arial.ttf).
	 * @return TrueType filename.
	 */
	const std::wstring& GetFontFile() { return m_fontFile; }

private:
	/** TTF font file. */
	std::wstring m_fontFile;

	/** Smart pointer to a FTFont. */
	FTTextureFont* m_font;
};

}

#endif
