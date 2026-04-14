/**
 * @file compress.c
 * @brief Simple JPEG compression using LibJPEG
 */

#include "compress.h"
#include "jpeglib.h"
#include <string.h>
#include <stdlib.h>

int compress(Image *src, Image *dst, int format, int quality)
{
    if (!src || !dst || !src->pixels || !dst->pixels) {
        return -1;
    }

    if (format != IMAGE_COMP_JPEG) {
        return -1;
    }

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    unsigned char *jpeg_buffer = NULL;
    unsigned long jpeg_size = 0;
    jpeg_mem_dest(&cinfo, &jpeg_buffer, &jpeg_size);

    cinfo.image_width = src->width;
    cinfo.image_height = src->height;

    JSAMPLE *row_buffer = NULL;
    int row_stride;

    if (src->format == IMAGE_FORMAT_RGB565) {
        /* RGB565 to JPEG */
        cinfo.input_components = 3;
        cinfo.in_color_space = JCS_RGB;
        jpeg_set_defaults(&cinfo);
        jpeg_set_quality(&cinfo, quality, TRUE);

        /* Performance optimizations */
        cinfo.dct_method = JDCT_IFAST;      // Fast integer DCT (2-3x faster)
        cinfo.optimize_coding = FALSE;      // Skip Huffman optimization

        jpeg_start_compress(&cinfo, TRUE);

        row_stride = src->width * 3;
        row_buffer = (JSAMPLE *)malloc(row_stride);
        if (!row_buffer) {
            jpeg_destroy_compress(&cinfo);
            return -1;
        }

        uint16_t *src_pixels = (uint16_t *)src->pixels;

        while (cinfo.next_scanline < cinfo.image_height) {
            for (uint32_t x = 0; x < src->width; x++) {
                uint16_t pixel = src_pixels[cinfo.next_scanline * src->width + x];
                uint8_t r = ((pixel >> 11) & 0x1F) << 3;
                uint8_t g = ((pixel >> 5) & 0x3F) << 2;
                uint8_t b = (pixel & 0x1F) << 3;
                row_buffer[x * 3 + 0] = r;
                row_buffer[x * 3 + 1] = g;
                row_buffer[x * 3 + 2] = b;
            }
            JSAMPROW row_pointer = row_buffer;
            jpeg_write_scanlines(&cinfo, &row_pointer, 1);
        }

    } else if (src->format == IMAGE_FORMAT_RGB888) {
        /* RGB888 to JPEG */
        cinfo.input_components = 3;
        cinfo.in_color_space = JCS_RGB;
        jpeg_set_defaults(&cinfo);
        jpeg_set_quality(&cinfo, quality, TRUE);

        /* Performance optimizations */
        cinfo.dct_method = JDCT_IFAST;
        cinfo.optimize_coding = FALSE;

        jpeg_start_compress(&cinfo, TRUE);

        row_stride = src->width * 3;
        uint8_t *src_pixels = (uint8_t *)src->pixels;

        while (cinfo.next_scanline < cinfo.image_height) {
            JSAMPROW row_pointer = &src_pixels[cinfo.next_scanline * row_stride];
            jpeg_write_scanlines(&cinfo, &row_pointer, 1);
        }

    } else if (src->format == IMAGE_FORMAT_GRAYSCALE) {
        /* Grayscale to JPEG */
        cinfo.input_components = 1;
        cinfo.in_color_space = JCS_GRAYSCALE;
        jpeg_set_defaults(&cinfo);
        jpeg_set_quality(&cinfo, quality, TRUE);

        /* Performance optimizations */
        cinfo.dct_method = JDCT_IFAST;
        cinfo.optimize_coding = FALSE;

        jpeg_start_compress(&cinfo, TRUE);

        row_stride = src->width;
        uint8_t *src_pixels = (uint8_t *)src->pixels;

        while (cinfo.next_scanline < cinfo.image_height) {
            JSAMPROW row_pointer = &src_pixels[cinfo.next_scanline * row_stride];
            jpeg_write_scanlines(&cinfo, &row_pointer, 1);
        }
    } else {
        jpeg_destroy_compress(&cinfo);
        return -1;
    }

    jpeg_finish_compress(&cinfo);

    int result = -1;
    if (jpeg_size > 0 && jpeg_buffer != NULL) {
        // Calculate actual buffer size in bytes (dst->size is pixel count, dst->depth is bytes per pixel)
        uint32_t buffer_size_bytes = dst->size * dst->depth;

        if (buffer_size_bytes >= jpeg_size) {
            memcpy(dst->pixels, jpeg_buffer, jpeg_size);
            dst->size = jpeg_size;  // Update size to actual JPEG size in bytes
            result = 0;
        }
        free(jpeg_buffer);
    }

    if (row_buffer) {
        free(row_buffer);
    }
    jpeg_destroy_compress(&cinfo);

    return result;
}