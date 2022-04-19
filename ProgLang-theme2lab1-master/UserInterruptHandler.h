#pragma once

#ifndef UserInterruptHandler_H
#define UserInterruptHandler_H

#ifdef _WIN32
#include <Windows.h>
#else
#include <signal.h>
#endif

#include <stdexcept>

class UserInterruptHandler
{
public:
	UserInterruptHandler()
	{
#ifdef _WIN32
		_isValid = SetConsoleCtrlHandler(reinterpret_cast<PHANDLER_ROUTINE>(UserInterruptHandler::Handler), true);
#else
		_isValid = (SIG_ERR != signal(SIGINT, UserInterruptHandler::Handler));
#endif
	}

	~UserInterruptHandler()
	{
#ifdef _WIN32
		if (_isValid)
		{
			SetConsoleCtrlHandler(reinterpret_cast<PHANDLER_ROUTINE>(UserInterruptHandler::Handler), false);
		}
#endif
	}

#ifdef _WIN32
	static bool WINAPI Handler(DWORD dwCtrlType)
	{
		if (CTRL_C_EVENT == dwCtrlType)
		{
			_interruptionFlag = true;
			return true;
		}
		return false;
	}
#else
	static void Handler(int sigVal)
	{
		_interruptionFlag = true;
	}
#endif

	bool checkInterruption() { return _interruptionFlag; }

	void checkInterruptionAndThrow() { if (_interruptionFlag) throw std::runtime_error("Ctrl+C"); }

	bool isValid() { return _isValid; }

private:
	static bool _interruptionFlag;
	bool _isValid;
};

bool UserInterruptHandler::_interruptionFlag = false;

#endif // !UserInterruptHandler_H
