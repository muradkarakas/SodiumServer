#include "FastApi.h"

inline
FastApiErrorCode
ExecuteSismember(HttpContext *context) {

	FastApiErrorCode retval = ERROR_SUCCESSFUL;

	IS_KEY_VALID(context);

	IS_REDIS_CONTEXT_VALID(context);

	if (context->Command.Params.p.SisMemberParams.memberName == NULL) {
		retval = ERROR_MISSING_PARAMETER;
		COPY_ERROR_MESSAGE(context, "value parameter is missing");
		goto Failed;
	}
	
	context->Command.redisReply = redisCommand(REDISCONTEXT, "SISMEMBER %s %s", COMMANDKEY, context->Command.Params.p.SisMemberParams.memberName);

	IS_REDIS_REPLY_VALID(context);

	if (context->Command.redisReply->integer == 0) {
		context->Command.Params.p.SisMemberParams.isExists = "0";
	}
	else if (context->Command.redisReply->integer == 1) {
		context->Command.Params.p.SisMemberParams.isExists = "1";
	}

Failed:

	return retval;
}