//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../core/VisualMarker.hpp"
#include "../core/App.hpp"

#include "../glUtils/ErrorGL.hpp"
#include "../utils/StringTools.hpp"

using namespace pygmy;
using namespace utils;

VisualMarker::VisualMarker()
	: m_position(Point(0,0)), m_shape(CIRCLE), m_colour(Colour(0,0,0)), m_size(6), m_selectionStyle(OUTLINE)
{

}

VisualMarker::VisualMarker(Colour colour, float size, MARKER_SHAPE shape, SELECTION_STYLE style, const Point& position)
		: m_colour(colour), m_size(size), m_shape(shape), m_position(position), m_selectionStyle(style)
{

}

void VisualMarker::Render()
{
	if(!m_bVisible)
		return;

	glUtils::ErrorGL::Check();

	glPushMatrix();	

		glTranslated(m_position.x, m_position.y, 0.0f);

		if(!m_bSelected)
		{
			glColor4f(m_colour.GetRed(), m_colour.GetGreen(), m_colour.GetBlue(), m_colour.GetAlpha());
			RenderMarker(m_size, m_shape);
		}
		else if(m_selectionStyle == OUTLINE)
		{
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
			RenderMarker(m_size+2, m_shape);

			glColor4f(m_colour.GetRed(), m_colour.GetGreen(), m_colour.GetBlue(), m_colour.GetAlpha());
			RenderMarker(m_size, m_shape);
		}
		else if(m_selectionStyle == FILL)
		{
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
			RenderMarker(m_size, m_shape);
		}
		else if(m_selectionStyle == FILL_AND_EXPAND)
		{
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
			RenderMarker(m_size+2, m_shape);
		}

	glPopMatrix();

	glUtils::ErrorGL::Check();
}

void VisualMarker::RenderMarker(float size, MARKER_SHAPE shape)
{
	if(shape == CIRCLE)
	{
		glPointSize(size);
		glBegin(GL_POINTS);
			glVertex2f( 0, 0);
		glEnd();
	}
	else if(shape == SQUARE)
	{
		glBegin(GL_QUADS);
			glVertex2f( -size, -size);
			glVertex2f( size, -size);
			glVertex2f( size, size);
			glVertex2f( -size, size);
		glEnd();
	}
	else if(shape == TRIANGLE)
	{		
		glBegin(GL_TRIANGLES);
			glVertex2f( 0.0f, -size);
			glVertex2f( -size, size);
			glVertex2f( size, size);
		glEnd();
	}
	else if(shape == STAR)
	{
		glBegin(GL_QUADS);
			glVertex2f( -size/5, -size);
			glVertex2f( size/5, -size);
			glVertex2f( size/5, size);
			glVertex2f( -size/5, size);
		glEnd();

		glBegin(GL_QUADS);
			glVertex2f( -size, -size/5);
			glVertex2f( size, -size/5);
			glVertex2f( size, size/5);
			glVertex2f( -size, size/5);
		glEnd();

		float threeForths = 3.0f / 4.0f;
		glBegin(GL_QUADS);
			glVertex2f( -size, -threeForths*size);
			glVertex2f( -threeForths*size, -size);
			glVertex2f( size, threeForths*size);
			glVertex2f( threeForths*size, size);
		glEnd();

		glBegin(GL_QUADS);
			glVertex2f( threeForths*size, -size);
			glVertex2f( size, -threeForths*size);
			glVertex2f( -threeForths*size, size);
			glVertex2f( -size, threeForths*size);
		glEnd();
	}
	else if(shape == PLUS_SIGN)
	{
		glBegin(GL_QUADS);
			glVertex2f( -size/3, -size);
			glVertex2f( size/3, -size);
			glVertex2f( size/3, size);
			glVertex2f( -size/3, size);
		glEnd();

		glBegin(GL_QUADS);
			glVertex2f( -size, -size/3);
			glVertex2f( size, -size/3);
			glVertex2f( size, size/3);
			glVertex2f( -size, size/3);
		glEnd();
	}
	else if(shape == HEXAGON)
	{
		glBegin(GL_QUADS);
			glVertex2f( -size/2, -size);
			glVertex2f( size/2, -size);
			glVertex2f( size/2, size);
			glVertex2f( -size/2, size);
		glEnd();

		glBegin(GL_QUADS);
			glVertex2f( -size, -size/2);
			glVertex2f( size, -size/2);
			glVertex2f( size, size/2);
			glVertex2f( -size, size/2);
		glEnd();

		glBegin(GL_QUADS);
			glVertex2f( -size, size/2);
			glVertex2f( -size/2, size);
			glVertex2f( size, -size/2);
			glVertex2f( size/2, -size);
		glEnd();

		glBegin(GL_QUADS);
			glVertex2f( size/2, size);
			glVertex2f( size, size/2);
			glVertex2f( -size/2, -size);
			glVertex2f( -size, -size/2);
		glEnd();
	}
	else if(shape == INVERTED_TRIANGLE)
	{
		glBegin(GL_TRIANGLES);
			glVertex2f( 0.0f, size);
			glVertex2f( -size, -size);
			glVertex2f( size, -size);
		glEnd();
	}
	else if(shape == DIAMOND)
	{
		glBegin(GL_QUADS);
			glVertex2f( 0.0f, size);
			glVertex2f( size, 0.0f);
			glVertex2f( 0.0f, -size);
			glVertex2f( -size, 0.0f);
		glEnd();
	}
}

bool VisualMarker::MouseLeftDown(const utils::Point& mousePt)
{
	if(!m_bVisible)
		return false;

	return (mousePt.x > m_position.x - m_size && mousePt.x < m_position.x + m_size
					&& mousePt.y > m_position.y - m_size && mousePt.y < m_position.y + m_size);
}