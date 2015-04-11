//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _ERROR_GL_
#define _ERROR_GL_

#include "../core/Precompiled.hpp"

namespace glUtils
{

/**
 * @brief OpenGL error checking routines.
 */
class ErrorGL
{
public:
	/**
	 * @brief Assert that a boolean expression is true.
	 * @return True if an error has occured.
	 */
	static void Check()
	{
		#ifndef NDEBUG
			static const int MAX_STRING_LEN = 4096;

			GLenum errCode = glGetError();
			const GLubyte *errString = gluErrorString(errCode);
			
			char strBuffer[MAX_STRING_LEN];
			sprintf(strBuffer, "(OpenGL Error) %s", errString);
			
			utils::Error::Assert(errCode == GL_NO_ERROR);
		#endif
	}

	/** Clear all OpenGL errors. */
	static void Clear()
	{
		GLenum errCode;
		do
		{
			errCode = glGetError();
		} while(errCode != GL_NO_ERROR);
	}

};

}

#endif
