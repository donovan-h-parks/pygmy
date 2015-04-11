// Image conversion utility functions
// Written by Gregor Miller, gregor.miller@freeviewpointvideo.co.uk

// Functions for converting between formats

#include "Convert.hpp"

namespace Image {

// *** RGB images ***

namespace RGB {
	
namespace ConvertTo {
	// Conversion routines
	boost::shared_array<byte> BGR(const byte *img, int width, int height)
	{
		boost::shared_array<byte> new_image = Allocate(width*height*3);
		byte *p = new_image.get();
		for(int i=0; i < width*height*3; i+=3) {
			p[i] = img[i+2];
			p[i+1] = img[i+1];
			p[i+2] = img[i];
		}
		return new_image;
	}

	void BGR(byte *img, int width, int height)
	{
		for(int i=0; i < width*height*3; i+=3) {
			byte tmp = img[i];
			img[i] = img[i+2];
			img[i+2] = tmp;
		}
	}
}

}

// *** BGR images ***

namespace BGR {
	
namespace ConvertTo {
	// Conversion routines
	boost::shared_array<byte> RGB(const byte *img, int width, int height)
	{
		return RGB::ConvertTo::BGR(img, width, height);
	}

	void RGB(byte *img, int width, int height)
	{
		RGB::ConvertTo::BGR(img, width, height);
	}
}

}

} // namespace Image


