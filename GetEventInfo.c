#include "FastApi.h"

FastApiErrorCode
ExecuteGetEventInfo(HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;
	
	IS_KEY_VALID(CONTEXT);

	IS_REDIS_CONTEXT_VALID(CONTEXT);

	COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "hmget %s registerationStartTime registerationStartDate description title", COMMANDKEY);

	IS_REDIS_REPLY_VALID(CONTEXT);

	if (COMMAND.redisReply->element[0]->str == NULL) {
		COPY_ERROR_MESSAGE(CONTEXT, NOT_FOUND_MESSAGE);
	
	} else {

		if (COMMAND.redisReply->elements == 4) {
			COMMAND.Output.getEventInfoParams.EventInfoSet.registerationStartTime = (COMMAND.redisReply->element[0]->str) ? COMMAND.redisReply->element[0]->str : "";
			COMMAND.Output.getEventInfoParams.EventInfoSet.registerationStartDate = (COMMAND.redisReply->element[1]->str) ? COMMAND.redisReply->element[1]->str : "";
			COMMAND.Output.getEventInfoParams.EventInfoSet.description = (COMMAND.redisReply->element[2]->str) ? COMMAND.redisReply->element[2]->str : "";
			COMMAND.Output.getEventInfoParams.EventInfoSet.title = (COMMAND.redisReply->element[3]->str) ? COMMAND.redisReply->element[3]->str : "";
		}

	}	

Failed:

	return retval;
}