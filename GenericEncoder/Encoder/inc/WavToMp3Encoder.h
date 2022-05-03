#ifndef WAVTOMP3_ENCODER_H
#define WAVTOMP3_ENCODER_H

#include "IEncoder.h"

#define WAV_BUFFER_SIZE 4096
#define MP3_BUFFER_SIZE 4096

class WavToMp3Encoder : public IEncoder          
{
public:
    void Encode(const std::vector<std::string>& listOfFiles);
    void Encode(const std::string& sourceWavFilePath, const std::string& destinationMp3FilePath) = 0;
    std::string GetVersion() = 0;
protected:
    std::string GenerateMp3FileName(const std::string& wavFileName);
    
};

#endif