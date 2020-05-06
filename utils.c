#include "FastApi.h"

void CopyResultString(HttpContext *context, const char *str) {
	strncpy_s(context->resultMessage, 1000, str, 1000);
}

