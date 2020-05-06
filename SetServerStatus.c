#include "FastApi.h"

FastApiErrorCode
ExecuteSetServerStatus(HttpContext *context) {
	
	FastApiErrorCode	retval = ERROR_SUCCESSFUL;

	IS_KEY_VALID(CONTEXT);

	IS_REDIS_CONTEXT_VALID(CONTEXT);

	COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "hmset " SERVER_STATUS_KEY_NAME " %s %s",		
		(COMMAND.Inputs.Params.SetServerStatusParams.gameStatus) ? "gameStatus" : "",
		(COMMAND.Inputs.Params.SetServerStatusParams.gameStatus) ? COMMAND.Inputs.Params.SetServerStatusParams.gameStatus : ""
	);

	IS_REDIS_REPLY_VALID(CONTEXT);

Failed:

	return retval;
}