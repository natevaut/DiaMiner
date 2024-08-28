#pragma once
// COMP710 GP Framework 2022
#ifndef LOGMANAGER_H
#define LOGMANAGER_H
class LogManager
{
	// Member methods:
public:
	static LogManager &GetInstance();
	static void DestroyInstance();
	void Log(const char *pcMessage);
	void LogPart(const char* pcMessage);

protected:
private:
	LogManager();
	~LogManager();
	LogManager(const LogManager &logManager);
	LogManager &operator=(const LogManager &logManager);
	// Member data:
public:
protected:
	static LogManager *sm_pInstance;

private:
	// pptx cuts off here
};

#endif /* LOGMANAGER_H */
