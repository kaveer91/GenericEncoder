#include <fstream>
#include <cstdio>
#include <string.h>

#include "LameWavToMp3Encoder.h"
#include "lame.h"
#include "Logger.h"

#define TRACE_CLASS Logger::TRACE_CLASS_LAMEWAVTOMP3ENCODER

std::string LameWavToMp3Encoder::GetVersion()
{
    return "Not implemented";    
}

void LameWavToMp3Encoder::Encode(const std::string& sourceWavFilePath, const std::string& destinationMp3FilePath)
{
    LOG(Logger::LOG_LEVEL_DEBUG, std::string("Encoding file ")+sourceWavFilePath + "===================");
    
    lame_t lame = lame_init();
    lame_init_params(lame);
    
    FILE* wavInputStream = std::fopen(sourceWavFilePath.c_str(), "rb");
    FILE* mp3OutputStream = std::fopen(destinationMp3FilePath.c_str(), "wb");
    
    if(wavInputStream && mp3OutputStream)
    {
        short int wavBuffer[WAV_BUFFER_SIZE*2] = {};
        unsigned char mp3Buffer[MP3_BUFFER_SIZE] = {};
    
        int lameBytesEncoded = 0;
        int wavBytesRead = 0;
        
        do
        {
            wavBytesRead = std::fread(wavBuffer, 2 * sizeof(short int), WAV_BUFFER_SIZE, wavInputStream);
            
            if(wavBytesRead)
            {
                lameBytesEncoded = lame_encode_buffer_interleaved(lame, wavBuffer, wavBytesRead, mp3Buffer, MP3_BUFFER_SIZE);
            }
            else
            {
                lameBytesEncoded = lame_encode_flush(lame, mp3Buffer, MP3_BUFFER_SIZE);
            }
            fwrite(mp3Buffer, lameBytesEncoded, sizeof(char), mp3OutputStream);
            
        }while(wavBytesRead);
        
        fclose(wavInputStream);
        fclose(mp3OutputStream);
    }
    else
    {
        if(!wavInputStream)
        {
            LOG(Logger::LOG_LEVEL_ERROR, std::string("Failed to open file :") + sourceWavFilePath + " : error :" + strerror(errno));
        }
        if(!mp3OutputStream)
        {
            LOG(Logger::LOG_LEVEL_ERROR, std::string("Failed to open file :") + destinationMp3FilePath + " : error :" + strerror(errno));
        }
    }
    
    lame_close(lame);
    
    LOG(Logger::LOG_LEVEL_DEBUG, std::string("Encoding completed for file")+sourceWavFilePath + "===================");
}