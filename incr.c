#include "FastApi.h"

inline FastApiErrorCode
ExecuteIncr(
	HttpContext *context) 
{
	FastApiErrorCode retval = ERROR_SUCCESSFUL;

	IS_KEY_VALID(context);

	IS_REDIS_CONTEXT_VALID(context);

	context->Command.redisReply = redisCommand(REDISCONTEXT, "INCR %s", COMMANDKEY);
	
	IS_REDIS_REPLY_VALID(context);

Failed:

	return retval;
}
