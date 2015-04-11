//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _PYGMY_APP_
#define _PYGMY_APP_

#include <wx/cmdline.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

/**
 * @brief Entry point for wxWidget application.
 */
class PygmyApp : public wxApp
{
public:
	/**
	* @brief Perform required initialization before starting the application.
	*/
	virtual bool OnInit();
	void OnInitCmdLine(wxCmdLineParser& parser);
    virtual bool OnCmdLineParsed(wxCmdLineParser& parser);

	/**
	* @brief Catch any exceptions occuring in the main message loop.
	*/
  virtual bool OnExceptionInMainLoop();

	/**
	* @brief this function is called in case of a crash 
	*				 (e.g. dereferencing null pointer, division by 0, ...)
	*/
  virtual void OnFatalException();

	/**
	* @brief Perform any necessary clean up before application terminates.
	*/
	virtual int OnExit();

private:
	wxString m_treeFilename;
};

static const wxCmdLineEntryDesc gCmdLineDesc [] =
{
	{ wxCMD_LINE_PARAM,  NULL, NULL, "input tree", wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL },

	{ wxCMD_LINE_NONE }
};


#endif
