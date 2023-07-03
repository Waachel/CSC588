
#include "FileDataCmd.h"

using namespace ThreadFramework;

float setVolumeOnFileData = 0.0f;
float soundPanOnFileData = 0.0f;

FileDataCmd::FileDataCmd(const char *const pWaveName, Wave *_pWave)
	: poWfx(nullptr),
	poRawBuff(nullptr),
	rawBuffSize(0),
	pWave(_pWave)
{
	assert(pWave);
	this->LoadBuffer(pWaveName);
}

void FileDataCmd::SetVolume(float volume)
{
	setVolumeOnFileData = volume;
}

void FileDataCmd::SetPan(float snd_pan)
{
	soundPanOnFileData = snd_pan;
}

void FileDataCmd::Execute() 
{
	Debug::out("Register Wave loaded");

	assert(this->pWave);
	this->pWave->Register(poWfx, poRawBuff, rawBuffSize);

	delete this;
}

void FileDataCmd::LoadBuffer(const char *const pWaveName)
{
	assert(pWaveName);

	Debug::out("FileDataCmd::LoadBuffer(%s) start\n", pWaveName);

	//--------------------------------------------------------
	// zero out wfx and the buffer
	//--------------------------------------------------------

	this->poWfx = new WAVEFORMATEXTENSIBLE();
	assert(this->poWfx);

	*this->poWfx = { {0} };    // zeros out the complete structure

	// -------------------------------------------------------
	// Open File
	// -------------------------------------------------------

	FileSlow::Handle FileHandle;
	FileSlow::Error ferror;

	// Open file
		// Take the name and add a path to it.
	const char *pDir = "..//..//AudioFiles//";
	size_t size = strlen(pDir) + strlen(pWaveName) + 1;
	char *pFullNameAndPath = new char[size]();
	strcat_s(pFullNameAndPath, size, pDir);
	strcat_s(pFullNameAndPath, size, pWaveName);

	ferror = FileSlow::Open(FileHandle, pFullNameAndPath, FileSlow::Mode::READ);
	assert(ferror == FileSlow::Error::SUCCESS);

	delete[] pFullNameAndPath;

	// Set file to beginning
	ferror = FileSlow::Seek(FileHandle, FileSlow::Location::BEGIN, 0);
	assert(ferror == FileSlow::Error::SUCCESS);

	// -------------------------------------------------------
	// Find and load specific Chunks
	// -------------------------------------------------------

	DWORD dwChunkPosition;
	DWORD filetype;
	ChunkError cerror;

	// Scan to the RIFF and load file type
	cerror = FindChunk(FileHandle, fourccRIFF, this->rawBuffSize, dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);
	cerror = ReadChunkData(FileHandle, &filetype, sizeof(DWORD), dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);

	// Make sure its not in the compressed format, WAVE format is uncompressed
	if(filetype != fourccWAVE)
	{
		assert(false);
	}

	// Read the FMT: format
	cerror = FindChunk(FileHandle, fourccFMT, this->rawBuffSize, dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);
	cerror = ReadChunkData(FileHandle, this->poWfx, this->rawBuffSize, dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);

	// Scan to the DATA chunk, read the size, allocate buffer of that size
	cerror = FindChunk(FileHandle, fourccDATA, this->rawBuffSize, dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);

	this->poRawBuff = new unsigned char[this->rawBuffSize];
	assert(this->poRawBuff);

	// Fill the data...
	cerror = ReadChunkData(FileHandle, this->poRawBuff, this->rawBuffSize, dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);

	ferror = FileSlow::Close(FileHandle);
	assert(ferror == FileSlow::Error::SUCCESS);

	Debug::out("FileDataCmd::LoadBuffer(%s) end\n", pWaveName);
}