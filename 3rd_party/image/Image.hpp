#ifndef _IMAGE_HPP
#define _IMAGE_HPP

// Annoying that some systems globally define a macro called RGB, so undefine it
#ifdef RGB
#undef RGB
#endif

// Image utility functions
// Written by Gregor Miller, gregor.miller@freeviewpointvideo.co.uk

// Basic methods and types for images

#include <boost/shared_array.hpp>

namespace Image {

// Types
typedef unsigned char byte;

// Allocate memory
inline boost::shared_array<byte> Allocate(int size)
{
	return boost::shared_array<byte>(new byte[size]);
}


} // namespace Image

#endif
