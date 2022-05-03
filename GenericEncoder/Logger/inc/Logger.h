#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <array>
#include <string>

namespace Logger
{
	enum LogLevel
	{
		LOG_LEVEL_DEBUG = 0,
		LOG_LEVEL_INFO,
		LOG_LEVEL_ERROR,
		LOG_LEVEL_FATAL,
		LOG_LEVEL_MAX,
	};
	
	enum TraceClass
	{
		TRACE_CLASS_MAIN = 0,
		TRACE_CLASS_READFILES,
		TRACE_CLASS_READFILESFROMDIRECTORY,
		TRACE_CLASS_WRITEFILESTODIRECTORY,
		TRACE_CLASS_WAVTOMP3ENCODER,
		TRACE_CLASS_LAMEWAVTOMP3ENCODER,
		TRACE_CLASS_THREADPOOL,
		TRACE_CLASS_ENCODERTASK,
		TRACE_CLASS_MAX,
	};
	
	extern const std::array<std::string, LOG_LEVEL_MAX> logLevelString;
	extern const std::array<std::string, TRACE_CLASS_MAX+1> traceClassString;
}

#define LOG(LOGLEVEL, msg)  LogWriter(LOGLEVEL,TRACE_CLASS,msg)

void LogWriter(Logger::LogLevel logLevel, Logger::TraceClass traceClass, std::string message);

#endif
