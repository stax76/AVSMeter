/*
	This file is part of AVSMeter, (c) Groucho2004.

	AVSMeter is free software. You can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation, either
	version 3 of the License, or any later version.

	AVSMeter is distributed in the hope that it will be useful
	but WITHOUT ANY WARRANTY and without the implied warranty
	of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with AVSMeter. If not, see <http://www.gnu.org/licenses/>.
*/


#if !defined(_TIMER_H)
#define _TIMER_H

#include "common.h"

class CTimer
{
public:
	CTimer();
	virtual          ~CTimer();
	double           GetTimer();
	double           GetSTDTimer();
	unsigned __int64 GetSTDTimerMS();
	string           FormatTimeString(__int64 i_milliseconds, BOOL b_rightaligned);
	LARGE_INTEGER    liPerfFreq;
	double           dPerfFreq;
	BOOL             supported;
};

CTimer::CTimer()
{
	liPerfFreq.QuadPart = 0;
	supported = TRUE;
	if (::QueryPerformanceFrequency(&liPerfFreq) == 0)
		supported = FALSE;

	dPerfFreq = (double)liPerfFreq.QuadPart;
}

CTimer::~CTimer()
{
}



double CTimer::GetTimer()
{
	LARGE_INTEGER liPerfCounter = {0,0};
	DWORD_PTR dwpOldMask = ::SetThreadAffinityMask(::GetCurrentThread(), 0x1);
	Sleep(0);
	::QueryPerformanceCounter(&liPerfCounter);

	if (dwpOldMask != 0)
		::SetThreadAffinityMask(::GetCurrentThread(), dwpOldMask);

	return (double)liPerfCounter.QuadPart / dPerfFreq;
}


double CTimer::GetSTDTimer()
{
	return ((double)GetSTDTimerMS() / 1000.0);
}


unsigned __int64 CTimer::GetSTDTimerMS()
{
	static unsigned __int64 uiLastSTDTimer;
	unsigned __int64 uiSTDTimer = (unsigned __int64)GetTickCount();
	unsigned __int64 uiTimerWrapComp = (uiSTDTimer < uiLastSTDTimer) ? 4294967296 : 0;
	uiLastSTDTimer = uiSTDTimer;

	return (uiSTDTimer + uiTimerWrapComp);
}


string CTimer::FormatTimeString(__int64 i_milliseconds, BOOL b_rightaligned)
{
	char buffer[128];
	unsigned int hours = (unsigned int)(i_milliseconds / 3600000);
	unsigned int minutes = (unsigned int)(i_milliseconds / 60000) % 60;
	unsigned int seconds = (unsigned int)(i_milliseconds / 1000) % 60;
	unsigned int milliseconds = (unsigned int)i_milliseconds % 1000;

	int iRet = -1;
	if (hours < 100)
		iRet = sprintf(buffer, "   %02u:%02u:%02u.%03u", hours, minutes, seconds, milliseconds);
	else
		iRet = sprintf(buffer, "%5u:%02u:%02u.%03u", hours, minutes, seconds, milliseconds);

	if (iRet < 0)
		return "buffer overflow";

	string sTime = &buffer[0];

	if (!b_rightaligned)
		sTime.erase(0, sTime.find_first_not_of(" "));

	return sTime;
}


#endif //_TIMER_H

