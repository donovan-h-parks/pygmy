//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../core/PygmyApp.hpp"
#include "../core/App.hpp"
#include "../core/State.hpp"

#include "../gui/PygmyFrame.hpp"

#include "../utils/Log.hpp"

IMPLEMENT_APP(PygmyApp)

bool PygmyApp::OnInit()
{
	if (!wxApp::OnInit())
        return false;

	try
	{
		utils::Log::Inst().Write(_T("Program Started."));

		wxImage::AddHandler(new wxPNGHandler);
		wxImage::AddHandler(new wxICOHandler);

		pygmy::State::Inst().Load(pygmy::App::Inst().GetExeDir() + _T("data/settings.xml"));

		pygmy::PygmyFrame* frame = new pygmy::PygmyFrame();
		SetTopWindow(frame);
		pygmy::App::Inst().SetMainFrame(frame);

		if(!m_treeFilename.IsEmpty())
		{
			std::wstring filename = m_treeFilename;
			frame->OpenTree(filename);
		}
		
		wxIcon icon(pygmy::App::Inst().GetExeDir() + _T("images/Tree.ico"), wxBITMAP_TYPE_ICO);
		frame->SetIcon(icon);
		
		frame->Show();
	}
	catch(...)
	{
		wxMessageBox(_T("Unknown exception"), _T("Unknown Fatal Exception"), wxOK | wxICON_ERROR);
	}

 return true;
}

bool PygmyApp::OnExceptionInMainLoop()
{
	wxMessageBox(_T("Program has crashed in main message loop."), _T("Message Loop Error"), wxOK | wxICON_ERROR);
	return false;
}

void PygmyApp::OnFatalException()
{
	wxMessageBox(_T("Program has crashed with a fatal exception."), _T("Fatal Error"), wxOK | wxICON_ERROR);
}
 
int PygmyApp::OnExit()
{
	pygmy::State::Inst().Save(pygmy::App::Inst().GetExeDir() + _T("data/settings.xml"));
	return 0;
}

void PygmyApp::OnInitCmdLine(wxCmdLineParser& parser)
{
    parser.SetDesc(gCmdLineDesc); 
    parser.SetSwitchChars (wxT("-"));
}

 
bool PygmyApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
	if(parser.GetParamCount() == 1)
		m_treeFilename = parser.GetParam(0);
 
    return true;
}