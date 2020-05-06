#include "FastApi.h"

inline
FastApiErrorCode
ExecuteHincrby(HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;

	context->Command.Params.p.HincrbyParams.propertyValue = NULL;

	IS_KEY_VALID(context);

	IS_REDIS_CONTEXT_VALID(context);

	if (context->Command.Params.p.HincrbyParams.propertyName == NULL) {
		retval = ERROR_MISSING_PARAMETER;
		COPY_ERROR_MESSAGE(context, "name is missing");
		goto Failed;
	}

	if (context->Command.Params.p.HincrbyParams.incrementBy == NULL) {
		retval = ERROR_MISSING_PARAMETER;
		COPY_ERROR_MESSAGE(context, "value is missing");
		goto Failed;
	}

	context->Command.redisReply = redisCommand(REDISCONTEXT, "HINCRBY %s %s %s", COMMANDKEY, context->Command.Params.p.HincrbyParams.propertyName, context->Command.Params.p.HincrbyParams.incrementBy);

	IS_REDIS_REPLY_VALID(context);

	char iStr[20];
	_i64toa_s(context->Command.redisReply->integer, iStr, 20, 10);
	size_t size = strlen(iStr) + 2;
	context->Command.Params.p.HincrbyParams.propertyValue = malloc(size);
	if (context->Command.Params.p.HincrbyParams.propertyValue) {
		strcpy_s(context->Command.Params.p.HincrbyParams.propertyValue, size, iStr);		
	}
	COPY_ERROR_MESSAGE(context, context->Command.redisReply->str);

Failed:

	return retval;
}
