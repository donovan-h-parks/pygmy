//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../glUtils/Font.hpp"
#include "../glUtils/ErrorGL.hpp"

using namespace glUtils;
using namespace utils;

Font::Font(const std::wstring& fontFile): m_fontFile(fontFile)
		
{
	glDisable(GL_LINE_SMOOTH);

	std::string str(fontFile.begin(), fontFile.end());
	m_font = new FTTextureFont(str.c_str());

	// check if font opened correctly
	utils::Error::Assert(!m_font->Error());

	m_font->CharMap(ft_encoding_unicode);
	m_font->UseDisplayList(true);
}

Font::~Font()
{
	if(m_font != NULL)
	{
		//delete m_font;
		m_font = NULL;
	}
}

void Font::SetTypeface(const std::wstring& fontFile)
{
	std::string str(fontFile.begin(), fontFile.end());
	m_font = new FTTextureFont(str.c_str());

	// check if font opened correctly
	utils::Error::Assert(!m_font->Error());

	m_font->CharMap(ft_encoding_unicode);
	m_font->UseDisplayList(true);
}

void Font::Render(const std::wstring& text, uint x, uint y)
{
	glUtils::ErrorGL::Check();
	m_font->Render(text.c_str(), -1, FTPoint(x, y), FTPoint(), FTGL::RENDER_FRONT);
	glUtils::ErrorGL::Check();
}

void Font::SetSize(uint size)
{
	bool rtn = m_font->FaceSize(size);
	utils::Error::Assert(rtn);
}

BBox Font::GetBoundingBox(const std::wstring& text) 
{ 
	glUtils::ErrorGL::Check();
	FTBBox bbox = m_font->BBox(text.c_str()); 
	glUtils::ErrorGL::Check();

	return BBox(bbox.Lower().Xf(), bbox.Lower().Yf(), 
								bbox.Upper().Xf(), bbox.Upper().Yf());
}


