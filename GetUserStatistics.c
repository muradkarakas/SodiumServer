#include "FastApi.h"

FastApiErrorCode
ExecuteGetUserStatistics(
	HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;

	IS_KEY_VALID(CONTEXT);

	IS_REDIS_CONTEXT_VALID(CONTEXT);

	COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "HMGET %s totalTrueReplyCount totalFalseReplyCount totalNoReplyCount totalReplyDuration lastAccessTime",
		COMMANDKEY
	);

	IS_REDIS_REPLY_VALID(CONTEXT);

	COMMAND.Inputs.Params.UserDataSet.totalTrueReplyCount = "";
	COMMAND.Inputs.Params.UserDataSet.totalFalseReplyCount = "";
	COMMAND.Inputs.Params.UserDataSet.totalNoReplyCount = "";
	COMMAND.Inputs.Params.UserDataSet.totalReplyDuration = "";
	COMMAND.Inputs.Params.UserDataSet.lastAccessTime = "";

	if (COMMAND.redisReply->element[0]->type == REDIS_REPLY_NIL) {
		COPY_ERROR_MESSAGE(CONTEXT, NOT_FOUND_MESSAGE);
	}
	else {
		if (COMMAND.redisReply->elements == 5) {
			COMMAND.Inputs.Params.UserDataSet.totalTrueReplyCount = (COMMAND.redisReply->element[0]->str) ? COMMAND.redisReply->element[0]->str : "0";
			COMMAND.Inputs.Params.UserDataSet.totalFalseReplyCount = (COMMAND.redisReply->element[1]->str) ? COMMAND.redisReply->element[1]->str : "0";
			COMMAND.Inputs.Params.UserDataSet.totalNoReplyCount = (COMMAND.redisReply->element[2]->str) ? COMMAND.redisReply->element[2]->str : "0";
			COMMAND.Inputs.Params.UserDataSet.totalReplyDuration = (COMMAND.redisReply->element[3]->str) ? COMMAND.redisReply->element[3]->str : "0";
			COMMAND.Inputs.Params.UserDataSet.lastAccessTime = (COMMAND.redisReply->element[4]->str) ? COMMAND.redisReply->element[4]->str : "0";
		}
	}

Failed:

	return retval;
}