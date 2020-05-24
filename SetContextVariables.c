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

#include "pch.h"

#include "FastApi.h"

void
SetContextVariables(
	HttpContext* context,
	HANDLE hReqQueue,
	HTTP_REQUEST* pRequest)
{
	context->hReqQueue = hReqQueue;
	context->pRequest = pRequest;

	if (context->Current_Path[0] == L'\0') {
		_wgetcwd(context->Current_Path, MAX_PATH);
	}

	_wgetcwd(context->Current_Full_Path, MAX_PATH);
	wcscat_s(context->Current_Full_Path, MAX_PATH, context->pRequest->CookedUrl.pAbsPath);
	
	size_t len = wcsnlen_s(context->Current_Full_Path, MAX_PATH);
	if (context->Current_Full_Path[len - 1] == L'/') {
		context->Current_Full_Path[len - 1] = 0;
	}
	for (register int i = 0; i < len - 1; i++) {
		if (context->Current_Full_Path[i] == L'/')
			context->Current_Full_Path[i] = L'\\';
		if (context->Current_Full_Path[i] == L'?')
			context->Current_Full_Path[i] = L'\0';
	}
	
	errno_t err = _wsplitpath_s(context->Current_Full_Path, 
		context->Current_Drive, MAX_PATH, 
		context->Current_Directory, MAX_PATH, 
		context->Current_FileName, MAX_PATH, 
		context->Current_FileExt, _MAX_EXT);

	wcsncpy_s(context->Current_File, MAX_PATH, context->Current_FileName, MAX_PATH);
	wcscat_s(context->Current_File, MAX_PATH, context->Current_FileExt);

	wchar_t	 temp[MAX_PATH] = L"";
	wcsncpy_s(temp, MAX_PATH, context->Current_Drive, MAX_PATH);
	wcscat_s(temp, MAX_PATH, context->Current_Directory);
	wcsncpy_s(context->Current_Directory, MAX_PATH, temp, MAX_PATH);
}