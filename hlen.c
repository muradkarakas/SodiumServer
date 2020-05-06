#include "FastApi.h"

inline FastApiErrorCode
ExecuteHlen(HttpContext *context) {

	FastApiErrorCode retval = ERROR_SUCCESSFUL;

	IS_KEY_VALID(context);

	IS_REDIS_CONTEXT_VALID(context);

	context->Command.Params.p.HlenParams.keyCount = 0;
	context->Command.Params.p.HlenParams.keyCountStr = NULL;

	context->Command.redisReply = redisCommand(REDISCONTEXT, "HLEN %s", COMMANDKEY);

	IS_REDIS_REPLY_VALID(context);

	char iStr[20];
	_i64toa_s(context->Command.redisReply->integer, iStr, 20, 10);
	size_t size = strlen(iStr) + 2;
	context->Command.Params.p.HlenParams.keyCountStr = malloc(size);
	if (context->Command.Params.p.HlenParams.keyCountStr) {
		strcpy_s(context->Command.Params.p.HlenParams.keyCountStr, size, iStr);
	}
	context->Command.Params.p.HlenParams.keyCount = context->Command.redisReply->integer;
	
Failed:

	return retval;
}
