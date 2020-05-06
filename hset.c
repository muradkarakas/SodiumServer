#include "FastApi.h"

inline
FastApiErrorCode
ExecuteHset(HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;

	IS_KEY_VALID(context);

	IS_REDIS_CONTEXT_VALID(context);

	if (context->Command.Params.p.HsetParams.propertyName == NULL) {
		retval = ERROR_MISSING_PARAMETER;
		COPY_ERROR_MESSAGE(context, "name is missing");
		goto Failed;
	}

	if (context->Command.Params.p.HsetParams.propertyValue == NULL) {
		retval = ERROR_MISSING_PARAMETER;
		COPY_ERROR_MESSAGE(context, "value is missing");
		goto Failed;
	}

	context->Command.redisReply = redisCommand(REDISCONTEXT, "HSET %s %s %s", COMMANDKEY, context->Command.Params.p.HsetParams.propertyName, context->Command.Params.p.HsetParams.propertyValue);
	
	IS_REDIS_REPLY_VALID(context);

	COPY_ERROR_MESSAGE(context, context->Command.redisReply->str);

Failed:

	return retval;
}
