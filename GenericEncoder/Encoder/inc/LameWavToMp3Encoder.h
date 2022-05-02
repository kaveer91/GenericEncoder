#ifndef LAME_WAVTOMP3_ENCODER_H
#define LAME_WAVTOMP3_ENCODER_H

#include "WavToMp3Encoder.h"

class LameWavToMp3Encoder : public WavToMp3Encoder
{	
public:
	void Encode(const std::string& sourceWavFilePath, const std::string& destinationMp3FilePath);
    std::string GetVersion();
};

#endif