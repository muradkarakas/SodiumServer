#pragma once

#include <direct.h>
#include <malloc.h>

typedef int	(APIENTRY* _SodiumGetExtensionId)();
typedef void	(APIENTRY* _SodiumHttpRequestHandler)();

typedef struct {
	int		ExtensionId;
	_SodiumGetExtensionId		GetExtensionId;
	_SodiumHttpRequestHandler	HttpRequestHandler;
} ExtensionRegistry;


extern int					extentionIndex;
extern ExtensionRegistry	extentionList[10];

typedef struct {

	wchar_t	 Current_Path[MAX_PATH];
	wchar_t	 Current_FileName[MAX_PATH];
	wchar_t	 Current_FileExt[MAX_PATH];
	wchar_t	 Current_File[MAX_PATH];
	wchar_t	 Current_Drive[MAX_PATH];
	wchar_t	 Current_Directory[MAX_PATH];
	wchar_t		Current_Full_Path[MAX_PATH];
		
	HANDLE			hReqQueue;
	HTTP_REQUEST	*pRequest;
	HTTP_RESPONSE	response;

	char			* RequestBody;
	ULONG 			  RequestBodySize;

} HttpContext;