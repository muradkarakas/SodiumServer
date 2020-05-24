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

DWORD 
DoReceiveRequests(
	IN HANDLE hReqQueue)
{
	ULONG              result;
	HTTP_REQUEST_ID    requestId;
	DWORD              bytesRead;
	PHTTP_REQUEST      pRequest;
	PCHAR              pRequestBuffer;
	ULONG              RequestBufferLength;
		
	//
	// Allocate a 2 KB buffer. This size should work for most 
	// requests. The buffer size can be increased if required. Space
	// is also required for an HTTP_REQUEST structure.
	//
	RequestBufferLength = sizeof(HTTP_REQUEST) + 4096;
	pRequestBuffer = (PCHAR)ALLOC_MEM(RequestBufferLength);

	if (pRequestBuffer == NULL) {
		return ERROR_NOT_ENOUGH_MEMORY;
	}

	pRequest = (PHTTP_REQUEST)pRequestBuffer;

	//
	// Wait for a new request. This is indicated by a NULL 
	// request ID.
	//

	HTTP_SET_NULL_ID(&requestId);
			
	for (;;) {
			
		RtlZeroMemory(pRequest, RequestBufferLength);

		result = HttpReceiveHttpRequest(
			hReqQueue,          // Req Queue
			requestId,          // Req ID
			HTTP_RECEIVE_REQUEST_FLAG_FLUSH_BODY,                   // Flags:  All of the entity bodies are copied along with the request headers. The pEntityChunks member of the HTTP_REQUEST structure points to the entity body. 
			pRequest,           // HTTP request buffer
			RequestBufferLength,// req buffer length
			&bytesRead,         // bytes received
			NULL                // LPOVERLAPPED
		);

		if (NO_ERROR == result) {

			HttpContext c = { 0 };
			HttpContext *context = &c;

			SetContextVariables(context, hReqQueue, pRequest);

			if (extentionList[0].HttpRequestHandler) {
				extentionList[0].HttpRequestHandler(context);
			}

			//
			// Reset the Request ID to handle the next request.
			//
			HTTP_SET_NULL_ID(&requestId);
		}

		else if (result == ERROR_MORE_DATA) {

			putchar('?');
			//
			// The input buffer was too small to hold the request
			// headers. Increase the buffer size and call the 
			// API again. 
			//
			// When calling the API again, handle the request
			// that failed by passing a RequestID.
			//
			// This RequestID is read from the old buffer.
			//
			requestId = pRequest->RequestId;

			//
			// Free the old buffer and allocate a new buffer.
			//
			RequestBufferLength = bytesRead;
			FREE_MEM(pRequestBuffer);
			pRequestBuffer = (PCHAR)ALLOC_MEM(RequestBufferLength);

			if (pRequestBuffer == NULL) {
				putchar('6');
				result = ERROR_NOT_ENOUGH_MEMORY;
				break;
			}

			pRequest = (PHTTP_REQUEST)pRequestBuffer;

		}

		else if (ERROR_CONNECTION_INVALID == result && !HTTP_IS_NULL_ID(&requestId)) {

			// The TCP connection was corrupted by the peer when
			// attempting to handle a request with more buffer. 
			// Continue to the next request.
			putchar('5');
			HTTP_SET_NULL_ID(&requestId);
			break;
		} else if (ERROR_INVALID_PARAMETER == result) {

			// The TCP connection was corrupted by the peer when
			// attempting to handle a request with more buffer. 
			// Continue to the next request.
			printf("\nERROR_INVALID_PARAMETER");
			HTTP_SET_NULL_ID(&requestId);
			//break;
		}
		else {
			putchar('#');
			break;
		}

	}
	
	if (pRequestBuffer) {
		FREE_MEM(pRequestBuffer);
	}
	
	return result;
}

