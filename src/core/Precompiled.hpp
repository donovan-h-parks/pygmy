//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _PRECOMPILED_
#define _PRECOMPILED_

// Generally only 3rd party header files should be included in this file. That is, header files that will
// almost never be changed. If a project header is added to this file, the entire project will need to be
// recompiled whenever this file changes. There are cases where this is reasonable (i.e., header files specifying
// common typedef's or constants that must be included in almost every file anyways).

// STL includes
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <utility>

// C/C++ includes
#include <string>
#include <limits>
#include <fstream>
#include <iostream>
#include <cfloat>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <exception>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>

// Boost includes
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/scoped_array.hpp>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/signals.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/archive/iterators/mb_from_wchar.hpp>
#include <boost/archive/iterators/wchar_from_mb.hpp>
#include <boost/filesystem.hpp>
#include <boost/dynamic_bitset.hpp>

// OpenGL includes
#if defined(_WIN32)
	#define NOMINMAX
	#include <windows.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#else
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#endif

// wxWidgets includes
#include <wx/wx.h>
#include <wx/app.h> 
#include <wx/progdlg.h>
#include <wx/string.h>
#include <wx/glcanvas.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/treectrl.h>
#include <wx/icon.h>
#include <wx/stdpaths.h>
#include <wx/msgdlg.h>
#include <wx/filedlg.h>
#include <wx/aboutdlg.h>
#include <wx/fontdlg.h>
#include <wx/image.h>
#include <wx/treebase.h>
#include <wx/statline.h>
#include <wx/imaglist.h>
#include <wx/frame.h>
#include <wx/event.h>
#include <wx/filesys.h>
#include <wx/clrpicker.h>
#include <wx/utils.h>
#include <wx/colordlg.h>
#include <wx/icon.h>
#include <wx/msgdlg.h>
#include <wx/generic/aboutdlgg.h>
#include <wx/numdlg.h> 

// 3rd party
#include <ticpp/ticpp.h>

// Project files (add with caution!)
#include "../core/DataTypes.hpp"
#include "../utils/Common.hpp"
#include "../utils/Log.hpp"
#include "../utils/Error.hpp"

#endif
