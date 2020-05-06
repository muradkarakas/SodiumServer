#include "FastApi.h"

inline
FastApiErrorCode
ExecuteSadd(HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;

	IS_KEY_VALID(context);

	IS_REDIS_CONTEXT_VALID(context);

	if (context->Command.Params.p.SaddParams.variableValue == NULL) {
		retval = ERROR_MISSING_PARAMETER;
		COPY_ERROR_MESSAGE(context, "value is missing");
		goto Failed;
	}

	if (context->Command.Params.p.SaddParams.variableValue) {
		context->Command.redisReply = redisCommand(REDISCONTEXT, "SADD %s %s", COMMANDKEY, context->Command.Params.p.SaddParams.variableValue);
	}
	else
		context->Command.redisReply = redisCommand(REDISCONTEXT, "SADD %s '%s'", COMMANDKEY, "");

	IS_REDIS_REPLY_VALID(context);

	COPY_ERROR_MESSAGE(context, context->Command.redisReply->str);

Failed:

	return retval;
}
