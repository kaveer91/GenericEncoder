#include "Logger.h"

namespace Logger
{
	const std::array<std::string, LOG_LEVEL_MAX> logLevelString{"DEBUG","INFO","ERROR", "FATAL"};
	
	const std::array<std::string, TRACE_CLASS_MAX+1> traceClassString{"MAIN","READFILES","READFILESFROMDIRECTORY","WRITEFILESTODIRECTORY","WAVTOMP3ENCODER","LAMEWAVTOMP3ENCODER","THREADPOOL","ENCODERTASK"};
}

Logger::LogLevel enabledLogLevel = Logger::LOG_LEVEL_INFO;

void LogWriter(Logger::LogLevel logLevel, Logger::TraceClass traceClass, std::string message)
{
    if(logLevel >= enabledLogLevel)
	{
		std::cout << Logger::logLevelString[logLevel] << ":" << Logger::traceClassString[traceClass] <<":"<< message << std::endl;
	}
}
