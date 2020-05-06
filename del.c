#include "FastApi.h"

inline
FastApiErrorCode ExecuteDel(HttpContext *context) {
	
	FastApiErrorCode retval = ERROR_SUCCESSFUL;

	IS_KEY_VALID(context);

	IS_REDIS_CONTEXT_VALID(context);

	context->Command.redisReply = redisCommand(REDISCONTEXT, "DEL %s", COMMANDKEY);
	
	IS_REDIS_REPLY_VALID(context);

Failed:

	return retval;
}
