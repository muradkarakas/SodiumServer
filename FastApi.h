/**
 * This file is part of Sodium Language project
 *
 * Copyright © 2020 Murad Karakaþ <muradkarakas@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License v3.0
 * as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 *	https://choosealicense.com/licenses/gpl-3.0/
 */

#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <http.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#pragma comment(lib, "httpapi.lib")


#define			MAX_PARAM_COUNT			20
#define			BUFF_SIZE				2048
#define			MAX_ULONG_STR			((ULONG) sizeof("4294967295"))
#define			PAYLOAD_KEY_NAME		"ErrorMessage"
#define			ERR_MESSAGE_KEY_NAME	"StatusCode"
#define			NOT_FOUND_MESSAGE		"Not found"
#define			NO_ERROR_MESSAGE		"No Error"
#define			JSON_RESULT_SIZE					2045


#include "yuarel.h"
#include "HtmlToSodiumBridge.h"
#include "LoadExtensions.h"

void
SetContextVariables(
	HttpContext* context,
	HANDLE hReqQueue,
	HTTP_REQUEST* pRequest);

DWORD	
SendHttpResponse(
	IN HANDLE        hReqQueue,
	IN PHTTP_REQUEST pRequest,
	IN USHORT        StatusCode,
	IN PSTR          pReason,
	IN PSTR          pEntity
);

DWORD	
SendHttpJsonResponse(
	IN HANDLE        hReqQueue,
	IN PHTTP_REQUEST pRequest,
	IN USHORT        StatusCode,
	IN PSTR          pContent);

DWORD	
SendHttpFileResponse(
	IN HANDLE        hReqQueue,
	IN PHTTP_REQUEST pRequest,
	IN USHORT        StatusCode,
	IN PSTR          pReason,
	IN LPWSTR		 pFilePath
);

DWORD	
SendHttpPostResponse(
	IN HANDLE        hReqQueue,
	IN PHTTP_REQUEST pRequest
);

void
urldecode2(
	char *dst,
	const char *src);


//
// Macros.
//
#define INITIALIZE_HTTP_RESPONSE( resp, status, reason )    \
    do                                                      \
    {                                                       \
        RtlZeroMemory( (resp), sizeof(*(resp)) );           \
        (resp)->StatusCode = (status);                      \
        (resp)->pReason = (reason);                         \
        (resp)->ReasonLength = (USHORT) strlen(reason);     \
    } while (FALSE)



#define ALLOC_MEM(cb) HeapAlloc(GetProcessHeap(), 0, (cb))

#define FREE_MEM(ptr) HeapFree(GetProcessHeap(), 0, (ptr))
#define INITIALIZE_HTTP_RESPONSE( resp, status, reason )    \
    do                                                      \
    {                                                       \
        RtlZeroMemory( (resp), sizeof(*(resp)) );           \
        (resp)->StatusCode = (status);                      \
        (resp)->pReason = (reason);                         \
        (resp)->ReasonLength = (USHORT) strlen(reason);     \
    } while (FALSE)



#define ALLOC_MEM(cb) HeapAlloc(GetProcessHeap(), 0, (cb))

#define FREE_MEM(ptr) HeapFree(GetProcessHeap(), 0, (ptr))


//
// Prototypes.
//
DWORD
DoReceiveRequests(
	IN HANDLE hReqQueue);

DWORD
SendHttpResponse(
	IN HANDLE        hReqQueue,
	IN PHTTP_REQUEST pRequest,
	IN USHORT        StatusCode,
	IN PSTR          pReason,
	IN PSTR          pEntity
);

DWORD
SendHttpPostResponse(
	IN HANDLE        hReqQueue,
	IN PHTTP_REQUEST pRequest
);


//
//	Global Variables
//
CRITICAL_SECTION	FastApiCriticalSection;
const wchar_t		FastAPIVersion[];
HANDLE				hConsole;


//
//	Functions
//
wchar_t				gwWorkingDirectory[MAX_PATH];
CRITICAL_SECTION	FastApiCriticalSection;
void				GetWindowsErrorMessageText(wchar_t* buf, int bufSize);
void				LoadExtension(wchar_t* extFileName);


//
//	Macros
//


#define			SHOW_GET_LAST_ERROR_MESSAGE(str)	{													\
														wchar_t errStr[MAX_PATH];						\
														GetWindowsErrorMessageText(errStr, MAX_PATH);	\
														wprintf(str, errStr);							\
													}



#define			COPY_ERROR_MESSAGE(cntx, sstr)		if (sstr) {												\
														strncpy_s(cntx->errMessage, 1000, sstr, 1000);	\
													} else {												\
														cntx->errMessage[0] = '\0';						\
													}

#define			JSON_RESULT(cntx)					cntx->Command.jsonResult

#define			COPY_JSON_RESULT(cntx, sstr)		if (cntx) {												\
														strncpy_s(JSON_RESULT(cntx), BUFF_SIZE, sstr, BUFF_SIZE);	\
													} 




