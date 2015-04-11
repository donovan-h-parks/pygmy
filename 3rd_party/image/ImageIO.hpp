#ifndef _IMAGEIO_HPP
#define _IMAGEIO_HPP

// Image IO utility functions
// Written by Gregor Miller, gregor.miller@freeviewpointvideo.co.uk

// Functions for reading and writing to various formats of file

#include <string>

#include "Image.hpp"

namespace Image {

// PNG Library
#include "../png/png.h"

// *** Binary images ***

namespace Binary {

// PBM: Uncompressed binary images (1 bit per pixel)
namespace PBM {
	// File IO
	boost::shared_array<byte> Read(const std::string &filename, int &width, int &height);
	void Write(const std::string &filename, const byte *img, const int width, const int height);
}

}

// *** Greyscale images ***

namespace Greyscale {

// PNG: Losslessly compressed greyscale images
namespace PNG {
	// File IO
	boost::shared_array<byte> Read(const std::string &filename, int &width, int &height);
	void Write(const std::string &filename, const byte *img, const int width, const int height);
}

}

// *** RGB images ***

namespace RGB {

// BMP: Uncompressed RGB images (3 bytes per pixel)
namespace BMP {
	// File IO
	// (not implemented!) boost::shared_array<byte> Read(const std::string &filename, int &width, int &height);
	void Write(const std::string &filename, const byte *img, const int width, const int height);
}

// PPM: Uncompressed RGB images (3 bytes per pixel)
namespace PPM {
	// File IO
	boost::shared_array<byte> Read(const std::string &filename, int &width, int &height);
	void Write(const std::string &filename, const byte *img, const int width, const int height);
}

// PNG: Losslessly compressed RGB images (3 bytes per pixel)
namespace PNG {
	// File IO
	boost::shared_array<byte> Read(const std::string &filename, int &width, int &height);
	void Write(const std::string &filename, const byte *img, const int width, const int height);
}

}


// *** RGBA images ***

namespace RGBA {

// PNG: Losslessly compressed RGBA images (4 bytes per pixel)
namespace PNG {
	// File IO
	boost::shared_array<byte> Read(const std::string &filename, int &width, int &height);
	void Write(const std::string &filename, const byte *img, const int width, const int height);
}

}

} // namespace Image

#endif
