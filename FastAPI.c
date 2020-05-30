/**
 * This file is part of Sodium Language project
 *
 * Copyright © 2020 Murad Karakaş <muradkarakas@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License v3.0
 * as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 *	https://choosealicense.com/licenses/gpl-3.0/
 */

#include "pch.h"

#include "FastApi.h"

#include "HtmlToSodiumBridge.c"
 

const wchar_t 
FastAPIVersion[] = L"0.0.8"    ;

void
PrintLogo() {
	/*
		Color Codes

		0   BLACK
		1   BLUE
		2   GREEN
		3   CYAN
		4   RED
		5   MAGENTA
		6   BROWN
		7   LIGHTGRAY
		8   DARKGRAY
		9   LIGHTBLUE
		10  LIGHTGREEN
		11  LIGHTCYAN
		12  LIGHTRED
		13  LIGHTMAGENTA
		14  YELLOW
		15  WHITE
	*/
	SetConsoleTextAttribute(hConsole, 10);

	wprintf(L"\n                                ,_-=(!7(7/zs_.        ");
	wprintf(L"\n                             .='  ' .`/,/!(=)Zm.      ");
	wprintf(L"\n               .._,,._..  ,-`- `,\\ ` -` -`\\\\7//WW.    ");
	wprintf(L"\n          ,v=~/.-,-\\- -!|V-s.)iT-|s|\\-.'   `///mK%%.   ");
	wprintf(L"\n        v!`i!-.e]-g`bT/i(/[=.Z/m)K(YNYi..   /-]i44M.  ");
	wprintf(L"\n      v`/,`|v]-DvLcfZ/eV/iDLN\\D/ZK@%%8W[Z..   `/d!Z8m  ");
	wprintf(L"\n     //,c\\(2(X/NYNY8]ZZ/bZd\\()/\\7WY%%WKKW)   -'|(][%%4. ");
	wprintf(L"\n   ,\\\\i\\c(e)WX@WKKZKDKWMZ8(b5/ZK8]Z7%%ffVM,   -.Y!bNMi ");
	wprintf(L"\n   /-iit5N)KWG%%%%8%%%%%%%%W8%%ZWM(8YZvD)XN(@.  [   \\]!/GXW[ ");
	wprintf(L"\n  / ))G8\\NMN%%W%%%%%%%%%%%%%%%%%%%%8KK@WZKYK*ZG5KMi,-   vi[NZGM[ ");
	wprintf(L"\n i\\!(44Y8K%%8%%%%%%**~YZYZ@%%%%%%%%%%4KWZ/PKN)ZDZ7   c=//WZK%%! ");
	wprintf(L"\n,\\v\\YtMZW8W%%%%f`,`.t/bNZZK%%%%W%%%%ZXb*K(K5DZ   -c\\\\/KM48  ");
	wprintf(L"\n-|c5PbM4DDW%%f  v./c\\[tMY8W%%PMW%%D@KW)Gbf   -/(=ZZKM8[  ");
	wprintf(L"\n2(N8YXWK85@K   -'c|K4/KKK%%@  V%%@@WD8e~  .//ct)8ZK%%8`  ");
	wprintf(L"\n=)b%%]Nd)@KM[  !'\\cG!iWYK%%%%|   !M@KZf    -c\\))ZDKW%%`   ");
	wprintf(L"\nYYKWZGNM4/Pb  '-VscP4]b@W%%     'Mf`   -L\\///KM(%%W!    ");
	wprintf(L"\n!KKW4ZK/W7)Z. '/cttbY)DKW%%     -`  .',\\v)K(5KW%%%%f     ");
	wprintf(L"\n'W)KWKZZg)Z2/,!/L(-DYYb54%%  ,,`, -\\-/v(((KK5WW%%f      ");
	wprintf(L"\n \\M4NDDKZZ(e!/\\7vNTtZd)8\\Mi!\\-,-/i-v((tKNGN%%W%%%%       ");
	wprintf(L"\n 'M8M88(Zd))///((|D\\tDY\\\\KK-`/-i(=)KtNNN@W%%%%%%@%%[      ");
	wprintf(L"\n  !8%%@KW5KKN4///s(\\Pd!ROBY8/=2(/4ZdzKD%%K%%%%%%M8@%%%%      ");
	wprintf(L"\n   '%%%%%%W%%dGNtPK(c\\/2\\[Z(ttNYZ2NZW8W8K%%%%%%%%YKM%%M%%%%.     ");
	wprintf(L"\n     *%%%%W%%GW5@/%%!e]_tZdY()v)ZXMZW%%W%%%%%%*5Y]K%%ZK%%8[     ");
	wprintf(L"\n      '*%%%%%%%%8%%8WK\\)[/ZmZ/Zi]!/M%%%%%%%%@f\\ \\Y/NNMK%%%%!     ");
	wprintf(L"\n        'VM%%%%%%%%W%%WN5Z/Gt5/b)((cV@f`  - |cZbMKW%%%%|     ");
	wprintf(L"\n           'V*M%%%%%%WZ/ZG\\t5((+)L'-,,/  -)X(NWW%%%%       ");
	wprintf(L"\n                `~`MZ/DZGNZG5(((\\,    ,t\\\\Z)KW%%@      ");
	wprintf(L"\n                   'M8K%%8GN8\\5(5///]i!v\\K)85W%%%%f      ");
	wprintf(L"\n                     YWWKKKKWZ8G54X/GGMeK@WM8%%@       ");
	wprintf(L"\n                      !M8%%8%%48WG@KWYbW%%WWW%%%%%%@        ");
	wprintf(L"\n                        VM%%WKWK%%8K%%%%8WWWW%%%%%%@`        ");
	wprintf(L"\n                          ~*%%%%%%%%%%%%W%%%%%%%%%%%%%%@~          ");
	wprintf(L"\n                             ~*MM%%%%%%%%%%%%@f`            ");
	wprintf(L"\n                                 '''''                ");

	wprintf(L"\n");

};



int wmain(int argc, wchar_t * argv[]) 
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	
	//
	// saving current color information
	//
	GetConsoleScreenBufferInfo(hConsole, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
	
	PrintLogo();

	SetConsoleTextAttribute(hConsole, 15);

	wprintf_s(L"\n                      Sodium Server (Alpha)");
	wprintf_s(L"\n                         Version %ws\n\n", FastAPIVersion);

	ULONG           retCode;
	HANDLE          hReqQueue = NULL;
	int             UrlAdded = 0;
	HTTPAPI_VERSION HttpApiVersion = HTTPAPI_VERSION_1;

	if (argc < 2) {
		wprintf(L"%ws: <Url1> [Url2] ... \n", argv[0]);
		return -1;
	}

	GetCurrentDirectory(MAX_PATH, gwWorkingDirectory);

	//
	// Initialize HTTP Server APIs
	//
	retCode = HttpInitialize(HttpApiVersion, HTTP_INITIALIZE_SERVER, NULL);

	if (retCode != NO_ERROR) {
		wprintf(L"HttpInitialize failed with %lu \n", retCode);
		return retCode;
	}

	//
	// Create a Request Queue Handle
	//
	retCode = HttpCreateHttpHandle(&hReqQueue, 0);

	if (retCode != NO_ERROR) {
		wprintf(L"HttpCreateHttpHandle failed with %lu \n", retCode);
		goto CleanUp;
	}

	// Get Url from command line
	retCode = HttpAddUrl(hReqQueue, argv[1],NULL);
	if (retCode != NO_ERROR) {
		wprintf(L"HttpAddUrl failed with %lu \n", retCode);
		getchar();
		goto CleanUp;
	}
	
	// Load extensions
	if (argv[2])
		LoadExtension(argv[2]);

	InitializeCriticalSection(&FastApiCriticalSection);

	wprintf(L"\nReady to accept connecion on the following url: %s\n", argv[1]);

	DoReceiveRequests(hReqQueue);
	
CleanUp:

	DeleteCriticalSection(&FastApiCriticalSection);

	//
	// Call HttpRemoveUrl for all added URLs.
	//
	for (int i = 1; i <= UrlAdded; i++) {
		HttpRemoveUrl(
			hReqQueue,     // Req Queue
			argv[i]        // Fully qualified URL
		);
	}

	//
	// Close the Request Queue handle.
	//
	if (hReqQueue) {
		CloseHandle(hReqQueue);
	}

	// 
	// Call HttpTerminate.
	//
	HttpTerminate(HTTP_INITIALIZE_SERVER, NULL);

	//
    // restoring the original colors
    //
	SetConsoleTextAttribute(hConsole, wOldColorAttrs);

	return retCode;
}
