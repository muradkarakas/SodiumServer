#include "FastApi.h"

int					extentionIndex = 0;
ExtensionRegistry	extentionList[10] = { 0 };


void
LoadExtension(wchar_t *extFileName) {

	wchar_t extUri[MAX_PATH * 2] = L"";

	// check parameters
	if (gwWorkingDirectory[0] == '\0') {
		wprintf_s(L"\nCurrent path variable is not valid");
		exit(-1);
	}

	// calculate path size	
	size_t sizefn = wcsnlen_s(extFileName, MAX_PATH);
	size_t sizewd = wcsnlen_s(gwWorkingDirectory, MAX_PATH);

	__try {
		wcsncpy_s(extUri, MAX_PATH+2, gwWorkingDirectory, sizewd);
		wcsncat_s(extUri, MAX_PATH+2, L"\\", 1);
		wcsncat_s(extUri, MAX_PATH+2, extFileName, sizefn);

		if (extUri == NULL) {
			wprintf_s(L"\nCannot allocate memory");
			exit(-1);
		}

		HMODULE hExtModule = LoadLibrary(extUri);
		if (hExtModule == NULL) {
			SetConsoleTextAttribute(hConsole, 4);
			char errorText[256];	
			FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), errorText, sizeof(errorText), NULL);
			wprintf_s(L"\nExtension cannot be loaded : %ws\nError Code & Message: 0x%X, %hs", extUri, GetLastError(), errorText);
			SetConsoleTextAttribute(hConsole, 15);
			exit(-1);
		}

		//
		//	Temporarily disable warning compiler message
		//
		//	warning C4133: '=': incompatible types - from 'FARPROC' to 'GetFastApiExtensionId'
#pragma warning(push)
#pragma warning(disable:4133)
		extentionList[extentionIndex].GetExtensionId = GetProcAddress(hExtModule, "SodiumGetExtensionId");
		extentionList[extentionIndex].HttpRequestHandler = GetProcAddress(hExtModule, "SodiumHttpRequestHandler");

		if (extentionList[extentionIndex].GetExtensionId == NULL) {
			wprintf_s(L"\nNot a valid FastAPI extension: %ws", extUri);
			exit(-1);
		}

		extentionList[extentionIndex].ExtensionId = extentionList[extentionIndex].GetExtensionId();

		wprintf_s(L"\nExtension loaded: #%d --> %ws", extentionList[extentionIndex].ExtensionId, extUri);

#pragma warning(pop) 

		extentionIndex++;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		SHOW_GET_LAST_ERROR_MESSAGE(L"%ws");
		if (GetExceptionCode() == STATUS_STACK_OVERFLOW)
			wprintf_s(L"\n_alloca failed: STATUS_STACK_OVERFLOW\n");
		exit(-1);
	};	

}