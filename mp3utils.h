//
//  mp3utils.h
//  Utilities for handling MP3 metadata (ID3 tags) and such
//
//  Licensed under the BSD license. See LICENSE for details.
//  Copyright (c) 2006 Daniel S. Neumeyer <dan@captaindan.org>
//

#ifndef __MP3UTILS_H__
#define __MP3UTILS_H__

#include <psptypes.h>
#include <tex.h>


//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
// --- Types --------------------------------------------------------------- //
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//


typedef struct
{
	u32   sampleOffset;
	void *bufferStart;
	u32   bufferLength;
}
MP3SeekTableEntry;

typedef struct
{
	u32 sampleCount;
	u32 entryCount;
	MP3SeekTableEntry *table;
}
MP3SeekTable;


typedef void *MP3ID3Tag;


typedef SceBool MP3ProgressCallback(int current, int goal);


//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
// --- Prototypes ---------------------------------------------------------- //
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//


MP3ID3Tag *mp3GetID3Tag(const void *mp3Data);
u32 mp3GetID3TagSize(const MP3ID3Tag *id3Tag);
char *mp3GetTitle(const MP3ID3Tag *id3Tag);
char *mp3GetAlbum(const MP3ID3Tag *id3Tag);
char *mp3GetArtist(const MP3ID3Tag *id3Tag);
int mp3GetTempo(const MP3ID3Tag *id3Tag);

void *mp3GetPrivateData(const MP3ID3Tag *id3Tag, const char *url, u32 *outLength);
// void mp3SetPrivateData(void *mp3Data, u32 mp3Length, const char *url, const void *data, u32 dataLength);

MP3SeekTable *mp3CreateSeekTable(const void *mp3Data, u32 length);
MP3SeekTableEntry *mp3Seek(const MP3SeekTable *seekTable, u32 sampleIndex);
void mp3FreeSeekTable(MP3SeekTable *seekTable);

TexTexture *mp3CreateWaveformTexture(const void *mp3Data, u32 length, u16 texWidth, u16 texHeight, MP3ProgressCallback *progressCallback);


#endif // __MP3UTILS_H__
