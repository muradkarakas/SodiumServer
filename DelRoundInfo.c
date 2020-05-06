#include "FastApi.h"


FastApiErrorCode
ExecuteDelRoundInfo(HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;
	
	IS_KEY_VALID(CONTEXT);

	IS_REDIS_CONTEXT_VALID(CONTEXT);

	COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "del round%s", COMMANDKEY);

	IS_REDIS_REPLY_VALID(CONTEXT);
	
Failed:

	return retval;
}