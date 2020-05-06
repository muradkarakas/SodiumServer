#include "FastApi.h"

inline FastApiErrorCode
ExecuteHdel(HttpContext *context) {

	FastApiErrorCode retval = ERROR_SUCCESSFUL;

	IS_KEY_VALID(context);

	IS_REDIS_CONTEXT_VALID(context);

	if (context->Command.Params.p.HdelParams.propertyName == NULL) {
		retval = ERROR_MISSING_PARAMETER;
		COPY_ERROR_MESSAGE(context, "name is missing");
		goto Failed;
	}

	context->Command.redisReply = redisCommand(REDISCONTEXT, "HDEL %s %s", COMMANDKEY, context->Command.Params.p.HdelParams.propertyName);

	IS_REDIS_REPLY_VALID(context);

Failed:

	return retval;
}
