/*
 * The Python Imaging Library
 * $Id$
 *
 * imaging access objects
 *
 * an access object can convert image data on the fly
 *
 * history:
 * 98-12-29 fl	Created
 *
 * Copyright (c) Secret Labs AB 1998.
 *
 * See the README file for information on usage and redistribution.
 */


#include "Imaging.h"


static void
destroy(ImagingAccess access)
{
    /* nop */
}

static int
getline(ImagingAccess access, char* buffer, int y)
{
    memcpy(buffer, access->im->image[y], access->im->linesize);
    return 1;
}

ImagingAccess
ImagingAccessNew(Imaging im)
{
    /* Create a standard access object */

    ImagingAccess access;

    access = calloc(1, sizeof(struct ImagingAccessInstance));
    if (!access)
	return (ImagingAccess) ImagingError_MemoryError();

    access->im = im;

    access->getline = getline;
    access->destroy = destroy;

    return access;
}

void
ImagingAccessDelete(ImagingAccess access)
{
    if (!access)
	return;

    if (access->destroy)
	access->destroy(access);

    free(access);
}
