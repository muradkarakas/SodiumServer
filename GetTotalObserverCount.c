#include "FastApi.h"



FastApiErrorCode
ExecuteGetTotalObserverCount(
	HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;

	if (REDIS_CONTEXT->err != 0) {
		COPY_ERROR_MESSAGE(CONTEXT, REDIS_CONTEXT->errstr);
		retval = ERROR_REDIS_ERROR_OCCURED;
		goto Failed;
	}

	IS_KEY_VALID(CONTEXT);

	IS_REDIS_CONTEXT_VALID(CONTEXT);

	COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "scard %s", OBSERVER_LIST_KEY_NAME);

	IS_REDIS_REPLY_VALID(CONTEXT);

	//char str[20];
	//_i64toa_s(COMMAND.redisReply->integer, str, 20, 10);
	COMMAND.Output.GetTotalObserverCountParams.TotalObserverCount = COMMAND.redisReply->integer;
	
Failed:

	return retval;
}