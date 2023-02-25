#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

void convert_jpg_to_png(const char* jpg_filename, const char* png_filename) {
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *infile;
    JSAMPARRAY buffer;
    int row_stride;

    // Open the JPEG file for reading
    if ((infile = fopen(jpg_filename, "rb")) == NULL) {
        fprintf(stderr, "Error: could not open JPEG file for reading\n");
        return;
    }

    // Initialize the JPEG decompression object
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, infile);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    // Set up the PNG output file
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        fprintf(stderr, "Error: could not create PNG write structure\n");
        return;
    }
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        fprintf(stderr, "Error: could not create PNG info structure\n");
        return;
    }
    if (setjmp(png_jmpbuf(png_ptr))) {
        fprintf(stderr, "Error: error during PNG write\n");
        return;
    }
    FILE *outfile = fopen(png_filename, "wb");
    png_init_io(png_ptr, outfile);
    png_set_IHDR(png_ptr, info_ptr, cinfo.output_width, cinfo.output_height, 8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    // Allocate memory for the pixel data buffer
    row_stride = cinfo.output_width * cinfo.output_components;
    buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, row_stride, 1);

    // Read the JPEG image data, row by row
    while (cinfo.output_scanline < cinfo.output_height) {
        jpeg_read_scanlines(&cinfo, buffer, 1);
        png_write_row(png_ptr, (png_bytep) buffer[0]);
    }

    // Finish up and clean up
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);
    png_write_end(png_ptr, NULL);
    fclose(outfile);
    png_destroy_write_struct(&png_ptr, &info_ptr);
}
