#include "FastApi.h"

FastApiErrorCode
ExecuteSetEventInfo(HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;

	IS_KEY_VALID(CONTEXT);

	IS_REDIS_CONTEXT_VALID(CONTEXT);

	COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "hmset %s registerationStartTime %s registerationStartDate %s description %s title %s", 
		COMMANDKEY,
		COMMAND.Inputs.Params.setEventInfoParams.EventInfoSet.registerationStartTime,
		COMMAND.Inputs.Params.setEventInfoParams.EventInfoSet.registerationStartDate,
		COMMAND.Inputs.Params.setEventInfoParams.EventInfoSet.description,
		COMMAND.Inputs.Params.setEventInfoParams.EventInfoSet.title
		);

	IS_REDIS_REPLY_VALID(CONTEXT);

Failed:

	return retval;
}