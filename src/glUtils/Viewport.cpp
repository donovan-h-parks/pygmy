//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../glUtils/Viewport.hpp"
#include "../glUtils/ErrorGL.hpp"

#include <Image/ImageIO.hpp>

using namespace glUtils;
using std::wstring;

Viewport::Viewport(wxWindow *parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size, long style, const wxString& name): 
		wxGLCanvas(parent, id, NULL, pos, size, style, name), m_bDisabled(false)
{
	m_contextGL = new wxGLContext(this);

	Viewport::ConnectEvents();
}

Viewport::~Viewport()
{
	delete m_contextGL;

	Viewport::DisconnectEvents();
}


void Viewport::ConnectEvents()
{
	this->Connect( wxEVT_ERASE_BACKGROUND, wxEraseEventHandler( Viewport::OnEraseBackground ) );
	this->Connect( wxEVT_PAINT, wxPaintEventHandler( Viewport::OnPaint ) );
}

void Viewport::DisconnectEvents()
{
	this->Disconnect( wxEVT_ERASE_BACKGROUND, wxEraseEventHandler( Viewport::OnEraseBackground ) );
	this->Disconnect( wxEVT_PAINT, wxPaintEventHandler( Viewport::OnPaint ) );
}

void Viewport::OnPaint(wxPaintEvent& event)
{
	if(!m_bDisabled)
	{
		// Must be called within an OnPaint() event.
		wxPaintDC(this);	

		RenderScene();
	}
}

void Viewport::Render()
{
	if(!m_bDisabled)
	{
		// Must be called when painting to a window outside of an OnPaint() event.
		wxClientDC(this);

		RenderScene();
	}
}

void Viewport::OnEraseBackground(wxEraseEvent &WXUNUSED(event))
{
	// keep empty to reduce flicker
} 

void Viewport::SaveImage(const wstring& filename)
{
	m_contextGL->SetCurrent(*this);
	glUtils::ErrorGL::Check();

	int dotPos = filename.rfind(_T("."));
	wstring extension = filename.substr(dotPos+1);
	boost::to_lower(extension);

	if(extension == _T("bmp") || extension == _T("ppm") || extension == _T("png"))
	{
		SaveRasterImage(filename, extension);
	}
	else
	{
		wxMessageBox(_T("Unknown graphics format."), _T("ERROR"),wxOK | wxICON_ERROR, 0);
		return;
	}

	glUtils::ErrorGL::Check();
}

void Viewport::SaveRasterImage(const wstring& filename, const wstring& extension)
{
	glReadBuffer(GL_BACK); // designate buffer to read

	int vp[4];
	glGetIntegerv(GL_VIEWPORT, vp);
	int width=vp[2];
	int height=vp[3];

	unsigned char* buffer = NULL;

	if(extension == _T("png"))
	{
		// OpenGL assumes (0,0) is the lower, left. This image formats assume 
		// (0,0) is the upper, left so we must "flip" the image.
		unsigned char* buffer = new unsigned char[width*height*4];
		glReadPixels(0,0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

		unsigned char* buffer_flip = new unsigned char[width*height*4];
		for (int y = 0; y < height; y++) 
		{
			for (int x = 0; x < width; x++) 
			{
				buffer_flip[(y*width+x)*4] = buffer[((height-1-y)*width+x)*4];
				buffer_flip[(y*width+x)*4+1] = buffer[((height-1-y)*width+x)*4+1];
				buffer_flip[(y*width+x)*4+2] = buffer[((height-1-y)*width+x)*4+2];
				buffer_flip[(y*width+x)*4+3] = 255;
			}
		}

		std::string str(filename.begin(), filename.end());
		Image::RGBA::PNG::Write(str, buffer_flip, width, height);		
		delete[] buffer_flip;
	}
	else if(extension == _T("ppm"))
	{
				// OpenGL assumes (0,0) is the lower, left. This image formats assume 
		// (0,0) is the upper, left so we must "flip" the image.
		unsigned char* buffer = new unsigned char[width*height*4];
		glReadPixels(0,0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

		unsigned char* buffer_flip = new unsigned char[width*height*3];
		for (int y = 0; y < height; y++) 
		{
			for (int x = 0; x < width; x++) 
			{
				buffer_flip[(y*width+x)*3] = buffer[((height-1-y)*width+x)*4];
				buffer_flip[(y*width+x)*3+1] = buffer[((height-1-y)*width+x)*4+1];
				buffer_flip[(y*width+x)*3+2] = buffer[((height-1-y)*width+x)*4+2];
			}
		}

		std::string str(filename.begin(), filename.end());
		Image::RGB::PPM::Write(str, buffer_flip, width, height);	
		delete[] buffer_flip;
	}

	if(buffer != NULL)
		delete[] buffer; 
}