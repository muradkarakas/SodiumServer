#include "FastApi.h"

FastApiErrorCode
GetRegisteredUserCount(
	HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;

	IS_KEY_VALID(CONTEXT);

	IS_REDIS_CONTEXT_VALID(CONTEXT);

	COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "scard " REGISTERED_USER_LIST_KEY_NAME);

	IS_REDIS_REPLY_VALID(CONTEXT);

	//char str[20];
	//_i64toa_s(COMMAND.redisReply->integer, str, 20, 10);
	COMMAND.Inputs.Params.UserDataSet.registeredUserCount = COMMAND.redisReply->integer;

Failed:

	return retval;
}