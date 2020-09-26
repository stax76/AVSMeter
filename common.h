/*
	This file is part of AVSMeter, Copyright(C) Groucho2004.

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


#if !defined(_COMMON_H)
#define _COMMON_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <shlobj.h>
#include <commdlg.h>
#include <process.h>
#include <math.h>
#include <string>
#include <algorithm>
#include <mmsystem.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <wintrust.h>
#include <imagehlp.h>
#include <conio.h>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <eh.h>

using std::string;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::sort;
using std::map;
using std::set;
using std::transform;
using std::getline;
using std::remove;
using std::exception;

#define MAX_PATH_LEN 32768
#define DSE_DELAY 500
const BOOL PROCESS_64 = (sizeof(void*) == 8) ? TRUE : FALSE;
const HWND ConsoleHWND = GetConsoleWindow();

static BOOL CompareNoCase(string first, string second)
{
  size_t i = 0;
  while ((i < first.length()) && (i < second.length()))
  {
    if (tolower (first[i]) < tolower (second[i]))
			return true;
    else if (tolower (first[i]) > tolower (second[i]))
			return false;
 
   i++;
  }

  if (first.length() < second.length())
		return true;
  else
		return false;
}


#endif //_COMMON_H
