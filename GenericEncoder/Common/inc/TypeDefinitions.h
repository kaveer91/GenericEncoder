
#ifndef TYPE_DEFINITIONS_H
#define TYPE_DEFINITIONS_H

#include <unordered_map>
#include <string>

#include "BaseTypes.h"

enum Extension
{
    EXT_MP3,
    EXT_WAV
};

extern const std::unordered_map<tU16, std::string> mapToFileExtension;

#endif