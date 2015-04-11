//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../glUtils/ContextGL.hpp"
#include "../glUtils/ErrorGL.hpp"

using namespace glUtils;

ContextGL::ContextGL(wxGLCanvas *canvas): wxGLContext(canvas)
{
	//glUtils::ErrorGL::Check();
	//SetCurrent(*canvas);
	//glUtils::ErrorGL::Check();
}