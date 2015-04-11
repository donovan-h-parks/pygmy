
#include "ImageIO.hpp"

namespace Image {

namespace Binary {

// *******************************************
// *** BinaryImage implementation

namespace PBM {

boost::shared_array<byte> Read(const std::string &filename, int &width, int &height)
{
	FILE *ifp;
	char buffer[80];
	int i;
	int header[2]; // width, height
	int tmp;
	byte pixels;
  
	ifp = fopen(filename.c_str(), "rb");
	if( !ifp ) {
		printf("Error opening file\n");
	}
	  
	i = 0;
	fgets(buffer, 80, ifp);
	if( strncmp(buffer, "P4", 2) ) {
		printf("%s is not a valid PBM file\n",filename.c_str());
		fclose(ifp);
	}

	while( (i < 2) ) {
		if( (tmp=fgetc(ifp)) == '#' ) {
		fgets(buffer, 80, ifp); // read out comment
		continue;
		} else {
		ungetc(tmp, ifp);
		fscanf(ifp, "%d", &header[i++]);
		}
	}
	fgets(buffer, 80, ifp); // read to newline

	// Allocate space
	width = header[0];
	height = header[1];
	int size = width * height;
	boost::shared_array<byte> img = Allocate(size);	

	int n=0;
	byte val = 0x80;
	int bit_count = 0;
	fread(&pixels, 1, 1, ifp);
	for(int i=0; i < size; i++, n++, bit_count++ ){
		// There are 8 pixels per byte, so need to unpack them
		img[i] = ((pixels & val) >> (7-n));
		val = val >> 1;
		if( bit_count == width-1 ) { // read width bits, then move on to the next bit
			fread(&pixels, 1, 1, ifp);
			n = -1;
			val = 0x80;
			bit_count = -1;
		} else {
			// One byte read, move on to the next
			if( n == 7 ) {
				fread(&pixels, 1, 1, ifp);
				n = -1;
				val = 0x80;
			}
		}
	}

	fclose(ifp);

	return img;
}

// Extension ".pbm"
void Write(const std::string &filename, const byte *img, const int width, const int height)
{
	FILE *ifp;
	byte pixels;
	ifp = fopen(filename.c_str(), "wb");
	if( !ifp ) {
		printf("Error opening file\n");
	}
		
	fprintf(ifp, "P4\n%d %d\n", width, height);
		
	int n=0;
	int bit_count = 0;
	pixels = 0;
	for(int i=0; i < width*height; i++, n++, bit_count++) {
		// Need to write 8 pixels per byte, so have to pack them in
		byte tmp = img[i] << (7-n);
		pixels |= tmp;//(*it) << (7-n);
		if( bit_count == (width-1) ) { // write width bits, then pack extra bits in there (random, doesn't matter), move on to the next row
			fwrite(&pixels, 1, 1, ifp);
			n=-1;
			pixels = 0;
			bit_count = -1;
		} else {
			if(n == 7) { // That's 8 bits, write to a file and move on to the next
				fwrite(&pixels, 1, 1, ifp);
				n=-1;
				pixels = 0;
			}
		}
    }
  
	fclose(ifp);
}

} // namespace PBM

} // namespace Binary

// ***
// *******************************************

namespace Greyscale {

// *******************************************
// *** GreyscaleImage implementation

namespace PNG {

boost::shared_array<byte> Read(const std::string &filename, int &width, int &height)
{
	png_structp png_ptr;
	png_infop info_ptr;
	unsigned int sig_read = 0;
	FILE *fp;
	
	if ((fp = fopen(filename.c_str(), "rb")) == NULL) {
		throw std::string("File \"") + filename + std::string("\" not found");
	}

	/* Create and initialize the png_struct with the desired error handler
	 * functions.  If you want to use the default stderr and longjump method,
	 * you can supply NULL for the last three parameters.  We also supply the
	 * the compiler header file version, so that we know if the application
	 * was compiled with a compatible version of the library.  REQUIRED
	 */
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
									 NULL, NULL, NULL);
	
	if (png_ptr == NULL) {
		fclose(fp);
		throw std::string("Could not create read structure for PNG");
	}
	
	/* Allocate/initialize the memory for image information.  REQUIRED. */
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fclose(fp);
		png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
		throw std::string("Out of memory in Greyscale::PNG::Read()");
	}
	
	/* Set error handling if you are using the setjmp/longjmp method (this is
	 * the normal method of doing things with libpng).  REQUIRED unless you
	 * set up your own error handlers in the png_create_read_struct() earlier.
	 */
	
	if (setjmp(png_jmpbuf(png_ptr))) {
		/* Free all of the memory associated with the png_ptr and info_ptr */
		png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
		fclose(fp);
		/* If we get here, we had a problem reading the file */
		throw std::string("Could not set up error handling for PNG");
	}
	
	/* Set up the input control if you are using standard C streams */
	png_init_io(png_ptr, fp);
	
	/* If we have already read some of the signature */
	png_set_sig_bytes(png_ptr, sig_read);
	
	/*
	 * If you have enough memory to read in the entire image at once,
	 * and you need to specify only transforms that can be controlled
	 * with one of the PNG_TRANSFORM_* bits (this presently excludes
	 * dithering, filling, setting background, and doing gamma
	 * adjustment), then you can read the entire image (including
	 * pixels) into the info structure with this call:
	 */
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, png_voidp_NULL);

	if( png_get_bit_depth(png_ptr, info_ptr) != 8 || // Bits per channel per pixel
		png_get_color_type(png_ptr, info_ptr) != PNG_COLOR_TYPE_GRAY ) {
		throw std::string("Expected 8-bit greyscale image");
	}

	// Renew image
	width = png_get_image_width(png_ptr, info_ptr);
	height = png_get_image_height(png_ptr, info_ptr);
	boost::shared_array<byte> img = Allocate(width*height);
	
	// Read the image
	png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);
	for(int j=0; j < height; j++) {
		for(int i=0; i < width; i++){
			img[i+(j*width)] = row_pointers[j][i];
		}
	}

	/* clean up after the read, and free any memory allocated - REQUIRED */
	png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);

   /* close the file */
   fclose(fp);

   return img;
}

void Write(const std::string &filename, const byte *img, const int width, const int height)
{
	FILE *fp;
	png_structp png_ptr;
	png_infop info_ptr;
	
	/* open the file */
	fp = fopen(filename.c_str(), "wb");
	if (fp == NULL) {
		throw std::string("File \"") + filename + std::string("\" could not be created");
	}
	
	/* Create and initialize the png_struct with the desired error handler
	 * functions.  If you want to use the default stderr and longjump method,
	 * you can supply NULL for the last three parameters.  We also check that
	 * the library version is compatible with the one used at compile time,
	 * in case we are using dynamically linked libraries.  REQUIRED.
     */
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
									  NULL, NULL, NULL);
	
	if (png_ptr == NULL) {
		fclose(fp);
		throw std::string("Could not create PNG structure for file \"") + filename + std::string("\"");
	}
	
	/* Allocate/initialize the image information data.  REQUIRED */
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fclose(fp);
		png_destroy_write_struct(&png_ptr,  png_infopp_NULL);
		throw std::string("Out of memory in Greyscale::PNG::Write()");
	}
	
	/* Set error handling.  REQUIRED if you aren't supplying your own
	 * error handling functions in the png_create_write_struct() call.
	 */
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		/* If we get here, we had a problem reading the file */
		fclose(fp);
		png_destroy_write_struct(&png_ptr, &info_ptr);
		throw std::string("Could not set up error handling for PNG");
	}
	
	/* set up the output control if you are using standard C streams */
	png_init_io(png_ptr, fp);
	
	/* This is the easy way.  Use it if you already have all the
	 * image info living info in the structure.  You could "|" many
	 * PNG_TRANSFORM flags into the png_transforms integer here.
	 */
	//   png_write_png(png_ptr, info_ptr, png_transforms, png_voidp_NULL);
	

	/* This is the hard way */
	
	/* Set the image information here.  Width and height are up to 2^31,
	 * bit_depth is one of 1, 2, 4, 8, or 16, but valid values also depend on
	 * the color_type selected. color_type is one of PNG_COLOR_TYPE_GRAY,
	 * PNG_COLOR_TYPE_GRAY_ALPHA, PNG_COLOR_TYPE_PALETTE, PNG_COLOR_TYPE_RGB,
	 * or PNG_COLOR_TYPE_RGB_ALPHA.  interlace is either PNG_INTERLACE_NONE or
	 * PNG_INTERLACE_ADAM7, and the compression_type and filter_type MUST
	 * currently be PNG_COMPRESSION_TYPE_BASE and PNG_FILTER_TYPE_BASE. REQUIRED
	 */
	png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_GRAY,
				 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	
	/* Write the file header information.  REQUIRED */
	png_write_info(png_ptr, info_ptr);
	
	/* If you want, you can write the info in two steps, in case you need to
	 * write your private chunk ahead of PLTE:
	 *
	 *   png_write_info_before_PLTE(write_ptr, write_info_ptr);
     *   write_my_chunk();
	 *   png_write_info(png_ptr, info_ptr);
     *
	 * However, given the level of known- and unknown-chunk support in 1.1.0
	 * and up, this should no longer be necessary.
	 */
	
	/* Once we write out the header, the compression type on the text
	 * chunks gets changed to PNG_TEXT_COMPRESSION_NONE_WR or
	 * PNG_TEXT_COMPRESSION_zTXt_WR, so it doesn't get written out again
	 * at the end.
	 */
	
	/* set up the transformations you want.  Note that these are
	 * all optional.  Only call them if you want them.
	 */
	
	/* The easiest way to write the image (you may have a different memory
	 * layout, however, so choose what fits your needs best).  You need to
	 * use the first method if you aren't handling interlacing yourself.
	 */
	png_bytep *row_pointers = new png_bytep[height];
	
	if( (png_uint_32)height > (png_uint_32)(PNG_UINT_32_MAX/png_sizeof(png_bytep))) {
		fclose(fp);
		png_destroy_write_struct(&png_ptr, &info_ptr);
		throw std::string("Image is too tall to process in memory");
	}
	
	for(int k = 0; k < height; k++)
		row_pointers[k] = (png_bytep)img + k*width;
	
	/* write out the entire image data in one call */
	png_write_image(png_ptr, row_pointers);
	
	/* You can write optional chunks like tEXt, zTXt, and tIME at the end
	 * as well.  Shouldn't be necessary in 1.1.0 and up as all the public
	 * chunks are supported and you can use png_set_unknown_chunks() to
	 * register unknown chunks into the info structure to be written out.
	 */
	
	/* It is REQUIRED to call this to finish writing the rest of the file */
	png_write_end(png_ptr, info_ptr);
	
	/* clean up after the write, and free any memory allocated */
	png_destroy_write_struct(&png_ptr, &info_ptr);

	delete[] row_pointers;
	row_pointers = NULL;

   /* close the file */
   fclose(fp);
}

} // namespace PNG

} // namespace Greyscale

namespace RGB {

// *******************************************
// *** RGBImage implementation

namespace BMP {

//File information header provides general information about the file
#pragma pack(1)	// turn off byte-alignment for struct: this is necessary! 
typedef struct tagBITMAPFILEHEADER { 
  unsigned short    bfType; 
  unsigned long   bfSize; 
  unsigned short    bfReserved1; 
  unsigned short    bfReserved2; 
  unsigned long   bfOffBits; 
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;
#pragma pack()

// Bitmap information header provides information specific to the image data
typedef struct tagBITMAPINFOHEADER{
  unsigned long  biSize; 
  unsigned long   biWidth; 
  unsigned long   biHeight; 
  unsigned short   biPlanes; 
  unsigned short   biBitCount; 
  unsigned long  biCompression; 
  unsigned long  biSizeImage; 
  unsigned long   biXPelsPerMeter; 
  unsigned long   biYPelsPerMeter; 
  unsigned long  biClrUsed; 
  unsigned long  biClrImportant; 
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;

/*
boost::shared_array<byte> Read(const std::string &filename, int &width, int &height)
{
	// not implemented
}
*/

void Write(const std::string &filename, const byte *img, const int width, const int height)
{
	// write header
	BITMAPFILEHEADER hdr; // file header
	BITMAPINFOHEADER bi;  // info header
	// set up info header
	bi.biSize  = sizeof(BITMAPINFOHEADER);
	bi.biWidth  = width;
	bi.biHeight   = height;
	bi.biPlanes   = 1;
	bi.biBitCount  = 24;
	bi.biCompression = 0;
	bi.biSizeImage  = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed  = 0;
	bi.biClrImportant = 0;

	// set up file header
	hdr.bfType  = ((unsigned short) ('M' << 8) | 'B'); // is always "BM"
	hdr.bfSize  =  sizeof( hdr ) + sizeof(bi) + width*height*3;
	hdr.bfReserved1  = 0;
	hdr.bfReserved2  = 0;
	hdr.bfOffBits  = (unsigned long) (sizeof( hdr ) + bi.biSize );

	 // write to disk  
	FILE* file = fopen(filename.c_str(), "wb");
	if( !file ) {
		throw std::string("Error opening file \"") + filename + std::string("\"");
	}	  

	// write to disk
	fwrite(&hdr, sizeof(hdr), 1, file);	// file header
	fwrite(&bi, sizeof(bi), 1, file);		// info header
	
	fwrite(img, 3, width * height, file);

	fclose(file);
}

} // namespace BMP

namespace PPM {

boost::shared_array<byte> Read(const std::string &filename, int &width, int &height)
{
	FILE *ifp;
	char buffer[80];
	int i;
	int header[3]; // width, height, maxval
	int tmp;

	// Warning - Number of references to this class might cause problems when reading images
	  
	ifp = fopen(filename.c_str(), "rb");
	if( !ifp ) {
		throw std::string("Error opening file \"") + filename + std::string("\"");
	}
	  
	i = 0;
	fgets(buffer, 80, ifp);
	if( strncmp(buffer, "P6", 2) ) {
		fclose(ifp);
		throw std::string("File is not in valid PPM format");
	}

	while( (i < 3) ) {
		if( (tmp=fgetc(ifp)) == '#' ) {
		fgets(buffer, 80, ifp); // read out comment
		continue;
		} else {
		ungetc(tmp, ifp);
		fscanf(ifp, "%d", &header[i++]);
		}
	}
	fgets(buffer, 80, ifp); // read to newline

	// Renew image
	width = header[0];
	height = header[1];
	boost::shared_array<byte> img = Allocate(width*height*3);

	fread(img.get(), 3, width * height, ifp);
	  
	fclose(ifp);
	return img;
}

void Write(const std::string &filename, const byte *img, const int width, const int height)
{
	FILE *ifp;
	ifp = fopen(filename.c_str(), "wb");
	if( !ifp ) {
		throw std::string("Error opening file \"") + filename + std::string("\"");
	}
	  
	fprintf(ifp, "P6\n%d %d\n255\n", width, height);

	fwrite(img, 3, width * height, ifp);
	  
	fclose(ifp);
}

} // namespace PPM

namespace PNG {

boost::shared_array<byte> Read(const std::string &filename, int &width, int &height)
{
	png_structp png_ptr;
	png_infop info_ptr;
	unsigned int sig_read = 0;
	FILE *fp;
	
	if ((fp = fopen(filename.c_str(), "rb")) == NULL) {
		throw std::string("File \"") + filename + std::string("\" not found");
	}

	/* Create and initialize the png_struct with the desired error handler
	 * functions.  If you want to use the default stderr and longjump method,
	 * you can supply NULL for the last three parameters.  We also supply the
	 * the compiler header file version, so that we know if the application
	 * was compiled with a compatible version of the library.  REQUIRED
	 */
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
									 NULL, NULL, NULL);
	
	if (png_ptr == NULL) {
		fclose(fp);
		throw std::string("Cannot create PNG read structure for file \"") + filename + std::string("\"");
	}
	
	/* Allocate/initialize the memory for image information.  REQUIRED. */
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fclose(fp);
		png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
		throw std::string("Out of memory in RGB::PNG::Read()");
	}
	
	/* Set error handling if you are using the setjmp/longjmp method (this is
	 * the normal method of doing things with libpng).  REQUIRED unless you
	 * set up your own error handlers in the png_create_read_struct() earlier.
	 */
	
	if (setjmp(png_jmpbuf(png_ptr))) {
		/* Free all of the memory associated with the png_ptr and info_ptr */
		png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
		fclose(fp);
		/* If we get here, we had a problem reading the file */
		throw std::string("Could not set up PNG error handling for file \"") + filename + std::string("\"");
	}
	
	/* Set up the input control if you are using standard C streams */
	png_init_io(png_ptr, fp);
	
	/* If we have already read some of the signature */
	png_set_sig_bytes(png_ptr, sig_read);
	
	/*
	 * If you have enough memory to read in the entire image at once,
	 * and you need to specify only transforms that can be controlled
	 * with one of the PNG_TRANSFORM_* bits (this presently excludes
	 * dithering, filling, setting background, and doing gamma
	 * adjustment), then you can read the entire image (including
	 * pixels) into the info structure with this call:
	 */
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, png_voidp_NULL);

	if( png_get_bit_depth(png_ptr, info_ptr) != 8 || // Bits per channel per pixel
		png_get_color_type(png_ptr, info_ptr) != PNG_COLOR_TYPE_RGB ) {
		throw std::string("Expected 8-bit RGB from file \"") + filename + std::string("\"");
	}

	// Renew image
	width = png_get_image_width(png_ptr, info_ptr);
	height = png_get_image_height(png_ptr, info_ptr);
	boost::shared_array<byte> img = Allocate(width*height*3);
	
	// Read the image
	png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);
	for(int j=0; j < height; j++) {
		for(int i=0; i < width; i++){
			for(int k=0; k < 3; k++) {
				img[(j*width*3) + (i*3) + k] = row_pointers[j][(i*3) + k];
			}
		}
	}

	/* clean up after the read, and free any memory allocated - REQUIRED */
	png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);

   /* close the file */
   fclose(fp);

   /* that's it */
   return img;
}

void Write(const std::string &filename, const byte *img, const int width, const int height)
{
	FILE *fp;
	png_structp png_ptr;
	png_infop info_ptr;
	
	/* open the file */
	fp = fopen(filename.c_str(), "wb");
	if (fp == NULL) {
		throw std::string("Cannot create file \"") + filename + std::string("\"");
	}
	
	/* Create and initialize the png_struct with the desired error handler
	 * functions.  If you want to use the default stderr and longjump method,
	 * you can supply NULL for the last three parameters.  We also check that
	 * the library version is compatible with the one used at compile time,
	 * in case we are using dynamically linked libraries.  REQUIRED.
     */
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
									  NULL, NULL, NULL);
	
	if (png_ptr == NULL) {
		fclose(fp);
		throw std::string("Cannot create PNG write structure from file \"") + filename + std::string("\"");
	}
	
	/* Allocate/initialize the image information data.  REQUIRED */
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fclose(fp);
		png_destroy_write_struct(&png_ptr,  png_infopp_NULL);
		throw std::string("Cannot allocate memory for file \"") + filename + std::string("\"");
	}
	
	/* Set error handling.  REQUIRED if you aren't supplying your own
	 * error handling functions in the png_create_write_struct() call.
	 */
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		/* If we get here, we had a problem reading the file */
		fclose(fp);
		png_destroy_write_struct(&png_ptr, &info_ptr);
		throw std::string("Error writing PNG to file \"") + filename + std::string("\"");
	}
	
	/* set up the output control if you are using standard C streams */
	png_init_io(png_ptr, fp);
	
	/* This is the easy way.  Use it if you already have all the
	 * image info living info in the structure.  You could "|" many
	 * PNG_TRANSFORM flags into the png_transforms integer here.
	 */
	//   png_write_png(png_ptr, info_ptr, png_transforms, png_voidp_NULL);
	

	/* This is the hard way */
	
	/* Set the image information here.  Width and height are up to 2^31,
	 * bit_depth is one of 1, 2, 4, 8, or 16, but valid values also depend on
	 * the color_type selected. color_type is one of PNG_COLOR_TYPE_GRAY,
	 * PNG_COLOR_TYPE_GRAY_ALPHA, PNG_COLOR_TYPE_PALETTE, PNG_COLOR_TYPE_RGB,
	 * or PNG_COLOR_TYPE_RGB_ALPHA.  interlace is either PNG_INTERLACE_NONE or
	 * PNG_INTERLACE_ADAM7, and the compression_type and filter_type MUST
	 * currently be PNG_COMPRESSION_TYPE_BASE and PNG_FILTER_TYPE_BASE. REQUIRED
	 */
	png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB,
				 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	
	/* Write the file header information.  REQUIRED */
	png_write_info(png_ptr, info_ptr);
	
	/* If you want, you can write the info in two steps, in case you need to
	 * write your private chunk ahead of PLTE:
	 *
	 *   png_write_info_before_PLTE(write_ptr, write_info_ptr);
     *   write_my_chunk();
	 *   png_write_info(png_ptr, info_ptr);
     *
	 * However, given the level of known- and unknown-chunk support in 1.1.0
	 * and up, this should no longer be necessary.
	 */
	
	/* Once we write out the header, the compression type on the text
	 * chunks gets changed to PNG_TEXT_COMPRESSION_NONE_WR or
	 * PNG_TEXT_COMPRESSION_zTXt_WR, so it doesn't get written out again
	 * at the end.
	 */
	
	/* set up the transformations you want.  Note that these are
	 * all optional.  Only call them if you want them.
	 */
	
	/* The easiest way to write the image (you may have a different memory
	 * layout, however, so choose what fits your needs best).  You need to
	 * use the first method if you aren't handling interlacing yourself.
	 */
	png_bytep *row_pointers = new png_bytep[height];
	
	if( (png_uint_32)height > (png_uint_32)(PNG_UINT_32_MAX/png_sizeof(png_bytep)) ) {
		fclose(fp);
		png_destroy_write_struct(&png_ptr, &info_ptr);
		throw std::string("Image too tall to process in memory");
	}
	
	for(int k = 0; k < height; k++)
		row_pointers[k] = (byte*)img + k*width*3;
	
	/* write out the entire image data in one call */
	png_write_image(png_ptr, row_pointers);
	
	/* You can write optional chunks like tEXt, zTXt, and tIME at the end
	 * as well.  Shouldn't be necessary in 1.1.0 and up as all the public
	 * chunks are supported and you can use png_set_unknown_chunks() to
	 * register unknown chunks into the info structure to be written out.
	 */
	
	/* It is REQUIRED to call this to finish writing the rest of the file */
	png_write_end(png_ptr, info_ptr);
	
	/* clean up after the write, and free any memory allocated */
	png_destroy_write_struct(&png_ptr, &info_ptr);

	delete[] row_pointers;
	row_pointers = NULL;

   /* close the file */
   fclose(fp);

   /* that's it */
}

} // namespace PNG

} // namespace RGB

namespace RGBA {

namespace PNG {

boost::shared_array<byte> Read(const std::string &filename, int &width, int &height)
{
	png_structp png_ptr;
	png_infop info_ptr;
	unsigned int sig_read = 0;
	FILE *fp;
	
	if ((fp = fopen(filename.c_str(), "rb")) == NULL) {
		throw std::string("File \"") + filename + std::string("\" not found");
	}

	/* Create and initialize the png_struct with the desired error handler
	 * functions.  If you want to use the default stderr and longjump method,
	 * you can supply NULL for the last three parameters.  We also supply the
	 * the compiler header file version, so that we know if the application
	 * was compiled with a compatible version of the library.  REQUIRED
	 */
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
									 NULL, NULL, NULL);
	
	if (png_ptr == NULL) {
		fclose(fp);
		throw std::string("Could not create PNG read structure for file \"") + filename + std::string("\"");
	}
	
	/* Allocate/initialize the memory for image information.  REQUIRED. */
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fclose(fp);
		png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
		throw std::string("Out of memory in RGBA::PNG::Read()");
	}
	
	/* Set error handling if you are using the setjmp/longjmp method (this is
	 * the normal method of doing things with libpng).  REQUIRED unless you
	 * set up your own error handlers in the png_create_read_struct() earlier.
	 */
	
	if (setjmp(png_jmpbuf(png_ptr))) {
		/* Free all of the memory associated with the png_ptr and info_ptr */
		png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
		fclose(fp);
		/* If we get here, we had a problem reading the file */
		throw std::string("Could not set up error handling for PNG");
	}
	
	/* Set up the input control if you are using standard C streams */
	png_init_io(png_ptr, fp);
	
	/* If we have already read some of the signature */
	png_set_sig_bytes(png_ptr, sig_read);
	
	/*
	 * If you have enough memory to read in the entire image at once,
	 * and you need to specify only transforms that can be controlled
	 * with one of the PNG_TRANSFORM_* bits (this presently excludes
	 * dithering, filling, setting background, and doing gamma
	 * adjustment), then you can read the entire image (including
	 * pixels) into the info structure with this call:
	 */
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, png_voidp_NULL);

	if( png_get_bit_depth(png_ptr, info_ptr) != 8 || // Bits per channel per pixel
		png_get_color_type(png_ptr, info_ptr) != PNG_COLOR_TYPE_RGB_ALPHA ) {
		throw std::string("Expected 8-bit RGBA");
	}

	// Renew image
	width = png_get_image_width(png_ptr, info_ptr);
	height = png_get_image_height(png_ptr, info_ptr);
	boost::shared_array<byte> img = Allocate(width*height*4);
	
	// Read the image
	png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);
	for(int j=0; j < height; j++) {
		for(int i=0; i < width; i++){
			for(int k=0; k < 4; k++) {
				img[i+(j*width)+k] = row_pointers[j][i*4+k];
			}
		}
	}

	/* clean up after the read, and free any memory allocated - REQUIRED */
	png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);

   /* close the file */
   fclose(fp);
}

void Write(const std::string &filename, const byte *img, const int width, const int height)
{
	FILE *fp;
	png_structp png_ptr;
	png_infop info_ptr;
	
	/* open the file */
	fp = fopen(filename.c_str(), "wb");
	if (fp == NULL) {
		throw std::string("Cannot create file \"") + filename + std::string("\"");
	}
	
	/* Create and initialize the png_struct with the desired error handler
	 * functions.  If you want to use the default stderr and longjump method,
	 * you can supply NULL for the last three parameters.  We also check that
	 * the library version is compatible with the one used at compile time,
	 * in case we are using dynamically linked libraries.  REQUIRED.
     */
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
									  NULL, NULL, NULL);
	
	if (png_ptr == NULL) {
		fclose(fp);
		throw std::string("Cannot create PNG write structure for file \"") + filename + std::string("\"");
	}
	
	/* Allocate/initialize the image information data.  REQUIRED */
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fclose(fp);
		png_destroy_write_struct(&png_ptr,  png_infopp_NULL);
		throw std::string("Out of memory in RGBA::PNG::Write()");
	}
	
	/* Set error handling.  REQUIRED if you aren't supplying your own
	 * error handling functions in the png_create_write_struct() call.
	 */
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		/* If we get here, we had a problem reading the file */
		fclose(fp);
		png_destroy_write_struct(&png_ptr, &info_ptr);
		throw std::string("Could not set up error handling for PNG");
	}
	
	/* set up the output control if you are using standard C streams */
	png_init_io(png_ptr, fp);
	
	/* This is the easy way.  Use it if you already have all the
	 * image info living info in the structure.  You could "|" many
	 * PNG_TRANSFORM flags into the png_transforms integer here.
	 */
	//   png_write_png(png_ptr, info_ptr, png_transforms, png_voidp_NULL);
	

	/* This is the hard way */
	
	/* Set the image information here.  Width and height are up to 2^31,
	 * bit_depth is one of 1, 2, 4, 8, or 16, but valid values also depend on
	 * the color_type selected. color_type is one of PNG_COLOR_TYPE_GRAY,
	 * PNG_COLOR_TYPE_GRAY_ALPHA, PNG_COLOR_TYPE_PALETTE, PNG_COLOR_TYPE_RGB,
	 * or PNG_COLOR_TYPE_RGB_ALPHA.  interlace is either PNG_INTERLACE_NONE or
	 * PNG_INTERLACE_ADAM7, and the compression_type and filter_type MUST
	 * currently be PNG_COMPRESSION_TYPE_BASE and PNG_FILTER_TYPE_BASE. REQUIRED
	 */
	png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB_ALPHA,
				 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	
	/* Write the file header information.  REQUIRED */
	png_write_info(png_ptr, info_ptr);
	
	/* If you want, you can write the info in two steps, in case you need to
	 * write your private chunk ahead of PLTE:
	 *
	 *   png_write_info_before_PLTE(write_ptr, write_info_ptr);
     *   write_my_chunk();
	 *   png_write_info(png_ptr, info_ptr);
     *
	 * However, given the level of known- and unknown-chunk support in 1.1.0
	 * and up, this should no longer be necessary.
	 */
	
	/* Once we write out the header, the compression type on the text
	 * chunks gets changed to PNG_TEXT_COMPRESSION_NONE_WR or
	 * PNG_TEXT_COMPRESSION_zTXt_WR, so it doesn't get written out again
	 * at the end.
	 */
	
	/* set up the transformations you want.  Note that these are
	 * all optional.  Only call them if you want them.
	 */
	
	/* The easiest way to write the image (you may have a different memory
	 * layout, however, so choose what fits your needs best).  You need to
	 * use the first method if you aren't handling interlacing yourself.
	 */
	png_bytep *row_pointers = new png_bytep[height];
	
	if( (png_uint_32)height > (png_uint_32)(PNG_UINT_32_MAX/png_sizeof(png_bytep)) ) {
		fclose(fp);
		png_destroy_write_struct(&png_ptr, &info_ptr);
		throw std::string("Image is too tall to process in memory");
	}
	
	for(int k = 0; k < height; k++)
		row_pointers[k] = (byte*)img + k*width*4;
	
	/* write out the entire image data in one call */
	png_write_image(png_ptr, row_pointers);
	
	/* You can write optional chunks like tEXt, zTXt, and tIME at the end
	 * as well.  Shouldn't be necessary in 1.1.0 and up as all the public
	 * chunks are supported and you can use png_set_unknown_chunks() to
	 * register unknown chunks into the info structure to be written out.
	 */
	
	/* It is REQUIRED to call this to finish writing the rest of the file */
	png_write_end(png_ptr, info_ptr);
	
	/* clean up after the write, and free any memory allocated */
	png_destroy_write_struct(&png_ptr, &info_ptr);

	delete[] row_pointers;
	row_pointers = NULL;

   /* close the file */
   fclose(fp);
}

} // namespace PNG

} // namespace RGBA

} // namespace ImageIO
