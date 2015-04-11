//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../core/App.hpp"

using namespace pygmy;

App& App::Inst()
{
	static App app;
	return app;
}

std::wstring App::GetExeDir()
{
	wxStandardPaths standardPaths;
  wxString exeDir;
	#ifdef WIN32
		exeDir = standardPaths.GetExecutablePath();
	  exeDir = exeDir.SubString(0, exeDir.find_last_of('\\'));
  #else
    // Mac version
    exeDir = standardPaths.GetExecutablePath();
    exeDir = exeDir.SubString(0, exeDir.length()-13);
    exeDir = exeDir + _T("Resources/");
  #endif

	return std::wstring(exeDir);
}