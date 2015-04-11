//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _APP_H_
#define _APP_H_

#include "../core/DataTypes.hpp"

namespace pygmy
{

/**
 * @class App
 * @brief Singleton class for holding project specific settings and widely access system level objects.
 */
class App
{
public:
	/** Destructor */
	~App() { }

	/** Get the one and only instance of the settings class. */
	static App& Inst();

	/** Set main frame of application. */
	void SetMainFrame(wxFrame* frame) { m_mainFrame = frame; }

	/** Get main frame of application. */
	wxFrame* GetMainFrame() { return m_mainFrame; }

	/** Set title of main frame. */
	void SetTitle(const std::wstring& title) { m_mainFrame->SetTitle(_T("Pygmy - ") + title); }

	/** Get directory containing program executable. */
	std::wstring GetExeDir();

protected:
	/** Private singleton constructor (must instantiate this class through Inst()). */
	App(): m_mainFrame(NULL) {}

	/** Private copy constructor (must instantiate this class through Inst()). */
  App(const App&);

	/** Private assignment constructor (must instantiate this class through Inst()). */
  App& operator= (const App&);

private:
	/** Main frame of application. */
	wxFrame* m_mainFrame;
};

}

#endif