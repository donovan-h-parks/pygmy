//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"
#include "../utils/Colour.hpp"
#include "assert.h"

using namespace utils;

Colour::Colour( float r, float g, float b, float alpha ) 
{
  assert( ( alpha >= 0 && alpha <= 1.0 ) && ( r >= 0 && r <= 1.0 )
          && ( g >= 0 && g <= 1.0 ) && ( b >= 0 && b <= 1.0 ) );
  m_red = r;
  m_green = g;
  m_blue = b;
  m_alpha = alpha;
}

Colour::Colour( int r, int g, int b, int alpha ) 
{
  assert( ( alpha >= 0 && alpha <= 255 ) && ( r >= 0 && r <= 255 ) && ( g >= 0 && g <= 255 ) && ( b >= 0 && b <= 255 ) );
  m_red = r / 255.0f;
  m_green = g / 255.0f;
  m_blue = b / 255.0f;
  m_alpha = alpha / 255.0f;
}

Colour::Colour( const wxColour& colour )
{
	m_red = colour.Red() / 255.0f;
  m_green = colour.Green()  / 255.0f;
  m_blue = colour.Blue()  / 255.0f;
	m_alpha = colour.Alpha()  / 255.0f;
}

Colour::Colour() 
{
  //white
  m_red = 1.0f;
  m_green = 1.0f;
  m_blue = 1.0f;
  m_alpha = 1.0f;
}

Colour::~Colour( void ) 
{

}

bool Colour::operator==(const Colour &other) const 
{
	return (this->GetRed() == other.GetRed()) && (this->GetGreen() == other.GetGreen())  
						&& (this->GetBlue() == other.GetBlue()) && (this->GetAlpha() == other.GetAlpha()); 
}

bool Colour::operator!=(const Colour &other) const 
{
  return !(*this == other);
}

void Colour::SetAlpha( float a ) 
{
  assert( a >= 0 && a <= 1.0 );
  m_alpha = a;
}

//access functions
float Colour::GetRed() const
{
	return m_red;
}

float Colour::GetGreen() const
{
    return m_green;
}

float Colour::GetBlue() const
{
	return m_blue;
}

float Colour::GetAlpha() const
{
	return m_alpha;
}

void Colour::SetRndColour(float alpha) 
{
	assert( alpha >= 0 && alpha <= 1.0 );
	m_alpha = alpha;

	//create random r,g,b values
	m_red = ( float )rand() / RAND_MAX;
	m_green = ( float )rand() / RAND_MAX;
	m_blue = ( float )rand() / RAND_MAX;
}

void Colour::SetRndColour() 
{
	m_red = ( float )rand() / RAND_MAX;
	m_green = ( float )rand() / RAND_MAX;
	m_blue = ( float )rand() / RAND_MAX;
	m_alpha = ( float )rand() / RAND_MAX;
}

/**** HC Mod follows */

void Colour::SetRGBA( float r, float g, float b, float a ) 
{
	m_red = r;
	m_green = g;
	m_blue = b;
	m_alpha = a;
}

void Colour::SetRGB( float r, float g, float b ) 
{
	m_red = r;
	m_green = g;
	m_blue = b;
	m_alpha = 1.0;
}

void Colour::SetRGB( int r, int g, int b ) 
{
	m_red = r / 255.0f;
	m_green = g / 255.0f;
	m_blue = b / 255.0f;
	m_alpha = 1.0f;
}

int Colour::GetRedInt() const
{
	return (int)(m_red * 255);
}

int Colour::GetGreenInt() const
{
	return (int)(m_green * 255);
}

int Colour::GetBlueInt() const
{
	return (int)(m_blue * 255);
}

int Colour::GetAlphaInt() const
{
	return (int)(m_alpha * 255);
}

Colour Colour::Interpolate(const Colour& colour1, const Colour& colour2, float curValue, float startValue, float endValue)
{
	float offset = curValue - startValue;
	float range = endValue - startValue;
	float delta = offset / range;

	return Colour(
		colour1.GetRed() + delta * ( colour2.GetRed() - colour1.GetRed() ), 
		colour1.GetGreen() + delta * ( colour2.GetGreen() - colour1.GetGreen() ),
		colour1.GetBlue() + delta * ( colour2.GetBlue() - colour1.GetBlue() ) ,
		colour1.GetAlpha() + delta * ( colour2.GetAlpha() - colour1.GetAlpha() ) );
}

Colour Colour::Interpolate(ColourPtr colour1, ColourPtr colour2, float curValue, float startValue, float endValue)
{
	float offset = curValue - startValue;
	float range = endValue - startValue;
	float delta = offset / range;

	return Colour(
		colour1->GetRed() + delta * ( colour2->GetRed() - colour1->GetRed() ), 
		colour1->GetGreen() + delta * ( colour2->GetGreen() - colour1->GetGreen() ),
		colour1->GetBlue() + delta * ( colour2->GetBlue() - colour1->GetBlue() ) ,
		colour1->GetAlpha() + delta * ( colour2->GetAlpha() - colour1->GetAlpha() ) );
}
