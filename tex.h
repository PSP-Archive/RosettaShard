//
//  Tex
//  Texture manager for PSP
//
//  Licensed under the BSD license. See LICENSE for details.
//  Copyright (c) 2006 Daniel S. Neumeyer <dan@captaindan.org>
//

#ifndef __TEX_H__
#define __TEX_H__

#include <psptypes.h>


//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
// --- Constants ----------------------------------------------------------- //
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//


#define TEX_MAX_BLOCK_SIZE (0)


//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
// --- Types --------------------------------------------------------------- //
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//


typedef struct
{
	void *pixels;
	u16   pixelFormat;  // uses GU_PSM_* constants in pspgu.h
	u16   bufferWidth;
	u16   bufferHeight;
	u16   imageWidth;
	u16   imageHeight;
	void *tableEntry;   // don't touch this
}
TexTexture;


//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
// --- Prototypes ---------------------------------------------------------- //
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//


void texInit(void *vramBlockBase, u32 vramBlockSize);

TexTexture *texLoad(const char *file);
void texFree(TexTexture *texture);
TexTexture **texLoadList(const char **files, unsigned count);
void texFreeList(TexTexture **textures, unsigned count);

TexTexture *texNew(u16 width, u16 height, u16 pixelFormat);
void texSwizzle(TexTexture *texture);

void texSet(const TexTexture *texture);


#endif // __TEX_H__
