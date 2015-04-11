//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _CONTEXT_GL_HPP
#define _CONTEXT_GL_HPP

#include "../core/Precompiled.hpp"

namespace glUtils
{

class ContextGL: public wxGLContext
{
public:
	ContextGL(wxGLCanvas* canvas);
};

}

#endif