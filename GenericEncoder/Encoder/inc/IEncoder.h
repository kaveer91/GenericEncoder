#ifndef IENCODER_H
#define IENCODER_H

#include <string>
#include <vector>

class IEncoder   
{
public:
	virtual void Encode(const std::vector<std::string>& listOfFiles) = 0;
    virtual void Encode(const std::string& , const std::string&) = 0;
	virtual std::string GetVersion() = 0;
protected:
	virtual std::string GenerateMp3FileName(const std::string& wavFileName)=0;
};

#endif