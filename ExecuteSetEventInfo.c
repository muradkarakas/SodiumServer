#include "LiveQuiz.h"

FastApiErrorCode
ExecuteSetEventInfo(HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;

	IS_KEY_VALID(context);

	IS_REDIS_CONTEXT_VALID(context);

	context->Command.redisReply = redisCommand(REDISCONTEXT, "hmset %s registerationStartTime %s description %s title %s", 
		COMMANDKEY,
		context->Command.Params.p.EventInfoParams.registerationStartTime,
		context->Command.Params.p.EventInfoParams.description,
		context->Command.Params.p.EventInfoParams.title
		);

	IS_REDIS_REPLY_VALID(context);

Failed:

	return retval;
}