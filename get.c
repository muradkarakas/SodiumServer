#include "FastApi.h"

inline 
FastApiErrorCode ExecuteGet(HttpContext *context) {

	FastApiErrorCode retval = ERROR_SUCCESSFUL;

	IS_KEY_VALID(context);

	IS_REDIS_CONTEXT_VALID(context);

	context->Command.Params.p.GetParams.variableValue = NULL;

	context->Command.redisReply = redisCommand(REDISCONTEXT, "GET %s", COMMANDKEY);

	IS_REDIS_REPLY_VALID(context);

	if (context->Command.redisReply->str) {
		size_t size = strlen(context->Command.redisReply->str) + 2;
		context->Command.Params.p.GetParams.variableValue = malloc(size);	// MCODE-2
		if (context->Command.Params.p.GetParams.variableValue)
			strncpy_s(context->Command.Params.p.GetParams.variableValue, size, context->Command.redisReply->str, size - 1);
	}
	else {
		context->Command.Params.p.GetParams.variableValue = NULL;
	}
	
Failed:

	return retval;
}
