//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _COLOR_
#define _COLOR_

#include "../core/Precompiled.hpp"

namespace utils
{

/**
 * @class Colour
 * @brief Specify an RGBA colour.
 */
class Colour 
{
public:
	/** Constructor. */
  Colour();

	/** 
	 * @brief Constructor. Specify colour components between 0 and 255. 
	 * @param r,g,b Colour channels (0 to 255).
	 * @param alpha Alpha channel (0 to 255).
	 */
	Colour( int r, int g, int b, int alpha = 255 );

	/** 
	 * @brief Constructor. Specify colour components between 0 and 1. 
	 * @param r,g,b Colour channels (0 to 1).
	 * @param alpha Alpha channel (0 to 1).
	 */
  Colour( float r, float g, float b, float alpha = 1.0f );

	/** 
	 * @brief Constructor. Specify colour components between 0 and 1. 
	 * @param colour wxWidgets colour object.
	 */
  Colour( const wxColour& colour );

	/** Destructor. */
  ~Colour( void );

	/** Set red colour channel (0 to 1). */
  void SetRed( float r );	

	/** Set red colour channel (0 to 255). */
  void SetRed( int r );	

	/** Set blue colour channel (0 to 1). */
  void SetBlue( float b );	

	/** Set blue colour channel (0 to 255). */
  void SetBlue( int b );	

	/** Set green colour channel (0 to 1). */
  void SetGreen( float g );			

	/** Set green colour channel (0 to 255). */
  void SetGreen( int g );		

	/** Set red colour channel (0 to 1). */
  void SetAlpha( float a );		

	/** Get red colour channel (0 to 1). */
  float GetRed() const;  

	/** Get green colour channel (0 to 1). */
  float GetGreen() const; 

	/** Get blue colour channel (0 to 1). */
  float GetBlue() const;  

	/** Get alpha colour channel (0 to 1). */
  float GetAlpha() const;

	/** Get red colour channel (0 to 255). */
	int GetRedInt() const;

	/** Get green colour channel (0 to 255). */
  int GetGreenInt() const;

	/** Get blue colour channel (0 to 255). */
  int GetBlueInt() const;

	/** Get alpha channel (0 to 255). */
  int GetAlphaInt() const;

	/** Get OpenGL colour. */
	void SetColourOpenGL() const { glColor4f(m_red, m_green, m_blue, m_alpha); }


	/** Create a random colour with alpha = 1. */
  void SetRndColour();				

	/** 
	 * @brief Create a random colour with a specific alpha channel value. 
	 * @param alpha Value of alpha channel.
	 */
  void SetRndColour( float alpha );

	/** Set RGB values (0 to 1). */
  void SetRGB( float r, float g, float b );

	/** Set RGB values (0 to 255). */
  void SetRGB( int r, int g, int b );

	/** Set RGBA values (0 to 1). */
  void SetRGBA( float r, float g, float b, float alpha );

	/** Equality operator. */
	bool operator==(const Colour &other) const;

	/** Inequality operator. */
	bool operator!=(const Colour &other) const;

	/** Interpolate colour. */
	static Colour Interpolate(const Colour& colour1, const Colour& colour2, float curValue, float startValue, float endValue); 

	/** Interpolate colour. */
	static Colour Interpolate(ColourPtr colour1, ColourPtr colour2, float curValue, float startValue, float endValue); 

private:
	/** Red colour channel. */
  float m_red;
	
	/** Blue colour channel. */
	float m_blue;
	
	/** Green colour channel. */
	float m_green;
	
	/** Alpha channel. */
	float m_alpha;
};

}

#endif
