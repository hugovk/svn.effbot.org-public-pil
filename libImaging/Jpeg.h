/*
 * The Python Imaging Library.
 * $Id: Jpeg.h 2134 2004-10-06 08:55:20Z fredrik $
 *
 * declarations for the IJG JPEG codec interface.
 *
 * Copyright (c) 1995-2001 by Secret Labs AB
 * Copyright (c) 1995-1996 by Fredrik Lundh
 */

#include "jpeglib.h"

#include <setjmp.h>


typedef struct {
    struct jpeg_error_mgr pub;	/* "public" fields */
    jmp_buf setjmp_buffer;	/* for return to caller */
} JPEGERROR;


/* -------------------------------------------------------------------- */
/* Decoder								*/

typedef struct {
    struct jpeg_source_mgr pub;
    int skip;
} JPEGSOURCE;

typedef struct {

    /* CONFIGURATION */

    /* Jpeg file mode (empty if not known) */
    char jpegmode[8+1];

    /* Converter output mode (input to the shuffler).  If empty,
       convert conversions are disabled */
    char rawmode[8+1];

    /* If set, trade quality for speed */
    int draft;

    /* Scale factor (1, 2, 4, 8) */
    int scale;

    /* PRIVATE CONTEXT (set by decoder) */

    struct jpeg_decompress_struct cinfo;

    JPEGERROR error;

    JPEGSOURCE source;

} JPEGSTATE;


/* -------------------------------------------------------------------- */
/* Encoder								*/

typedef struct {
    struct jpeg_destination_mgr pub;
    /* might add something some other day */
} JPEGDESTINATION;

typedef struct {

    /* CONFIGURATION */

    /* Quality (1-100, 0 means default) */
    int quality;

    /* Progressive mode */
    int progressive;

    /* Smoothing factor (1-100, 0 means none) */
    int smooth;

    /* Optimize Huffman tables (slow) */
    int optimize;

    /* Stream type (0=full, 1=tables only, 2=image only) */
    int streamtype;

    /* DPI setting (0=square pixels, otherwide DPI) */
    int xdpi, ydpi;

    /* PRIVATE CONTEXT (set by encoder) */

    struct jpeg_compress_struct cinfo;

    JPEGERROR error;

    JPEGDESTINATION destination;

} JPEGENCODERSTATE;