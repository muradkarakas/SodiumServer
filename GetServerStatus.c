#include "FastApi.h"

FastApiErrorCode
ExecuteGetServerStatus(HttpContext *context) {
	
	FastApiErrorCode	retval = ERROR_SUCCESSFUL;

	//COMMAND.Output.GetServerStatusParams.gameStatus = "";

	IS_KEY_VALID(CONTEXT);

	IS_REDIS_CONTEXT_VALID(CONTEXT);

	COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "hmget " SERVER_STATUS_KEY_NAME " gameStatus");

	IS_REDIS_REPLY_VALID(CONTEXT);
	
	if (COMMAND.redisReply->type != REDIS_REPLY_ARRAY) {
		COPY_ERROR_MESSAGE(CONTEXT, NOT_FOUND_MESSAGE);
	}
	else {
		if (COMMAND.redisReply->elements == 1) {
			COMMAND.Output.GetServerStatusParams.gameStatus = (COMMAND.redisReply->element[0]->str) ? COMMAND.redisReply->element[0]->str : "unknown";
		}
	}

Failed:

	return retval;
}