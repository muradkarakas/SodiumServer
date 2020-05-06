#include "FastApi.h"

inline
FastApiErrorCode
ExecuteHget(HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;

	IS_KEY_VALID(context);

	IS_REDIS_CONTEXT_VALID(context);

	if (context->Command.Params.p.HgetParams.propertyName == NULL) {
		retval = ERROR_MISSING_PARAMETER;
		COPY_ERROR_MESSAGE(context, "name is missing");
		goto Failed;
	}

	context->Command.redisReply = redisCommand(REDISCONTEXT, "HGET %s %s", COMMANDKEY, context->Command.Params.p.HgetParams.propertyName);

	IS_REDIS_REPLY_VALID(context);

	if (context->Command.redisReply->str) {
		size_t size = strlen(context->Command.redisReply->str) + 2;
		context->Command.Params.p.HsetParams.propertyValue = malloc(size);			
		if (context->Command.Params.p.HsetParams.propertyValue)
			strncpy_s(context->Command.Params.p.HsetParams.propertyValue, size, context->Command.redisReply->str, size - 1);
	}

	COPY_ERROR_MESSAGE(context, context->Command.redisReply->str);

Failed:
	
	return retval;
}
