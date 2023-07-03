#include "FileLoadCmd.h"
#include "FileDataCmd.h"
#include "SndMan.h"


float soundPanOnFileLoad = 0.0f;
float setVolumeOnFileLoad = 0.0f;

FileLoadCmd::FileLoadCmd(Wave::ID id, const char *const _pWaveName, Wave *_pWave)
	: Command(),
	wave_id(id),
	pWaveName(_pWaveName),
	pWave(_pWave)
{
	assert(pWaveName);
	assert(pWave);
}

FileLoadCmd::~FileLoadCmd()
{

}

void FileLoadCmd::SetVolume(float volume)
{
	setVolumeOnFileLoad = volume;
}

void FileLoadCmd::SetPan(float snd_pan)
{
	soundPanOnFileLoad = snd_pan;
}

// From Audio --> File to execute
void FileLoadCmd::Execute()
{
	// Load the file and fill in the data structure
	// This will block on File Thread doing the loading.
	FileDataCmd *pCmd = new FileDataCmd(this->pWaveName, this->pWave);
	assert(pCmd);

	// Send the data to the Audio thread to register
	bool status = SndMan::Send(pCmd);
	assert(status == true);

	delete this;
}


// --- End of File ---