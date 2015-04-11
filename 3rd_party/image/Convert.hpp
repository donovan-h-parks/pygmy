#ifndef _IMAGE_CONVERT_HPP
#define _IMAGE_CONVERT_HPP

// Image conversion utility functions
// Written by Gregor Miller, gregor.miller@freeviewpointvideo.co.uk

// Functions for converting between formats

#include "Image.hpp"

namespace Image {

// *** RGB images ***

namespace RGB {
	
namespace ConvertTo {
	// Conversion routines
	boost::shared_array<byte> BGR(const byte *img, int width, int height);
	void BGR(byte *img, int width, int height);
}

}

// *** BGR images ***

namespace BGR {
	
namespace ConvertTo {
	// Conversion routines
	boost::shared_array<byte> RGB(const byte *img, int width, int height);
	void RGB(byte *img, int width, int height);
}

}

} // namespace Image

#endif
