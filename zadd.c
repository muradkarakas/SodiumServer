#include "FastApi.h"

inline 
FastApiErrorCode 
ExecuteZadd(HttpContext *context) {

	FastApiErrorCode retval = ERROR_SUCCESSFUL;

	IS_KEY_VALID(context);

	IS_REDIS_CONTEXT_VALID(context);

	if (context->Command.Params.p.ZaddParams.itemScore == NULL) {
		retval = ERROR_MISSING_PARAMETER;
		COPY_ERROR_MESSAGE(context, "score is missing");
		goto Failed;
	}
	if (context->Command.Params.p.ZaddParams.itemValue == NULL) {
		retval = ERROR_MISSING_PARAMETER;
		COPY_ERROR_MESSAGE(context, "value is missing");
		goto Failed;
	}
	
	context->Command.redisReply = redisCommand(REDISCONTEXT, "ZADD %s %s %s '%s'",
		COMMANDKEY,
		(context->Command.Params.p.ZaddParams.options) ? context->Command.Params.p.ZaddParams.options : "",
		context->Command.Params.p.ZaddParams.itemScore,
		context->Command.Params.p.ZaddParams.itemValue);

	IS_REDIS_REPLY_VALID(context);
	
Failed:

	return retval;
}
