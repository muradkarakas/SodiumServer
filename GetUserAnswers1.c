#include "FastApi.h"

FastApiErrorCode
ExecuteGetUserAnswers1(
	HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;

	IS_KEY_VALID(CONTEXT);

	IS_REDIS_CONTEXT_VALID(CONTEXT);

	COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "hmget answers:%s q1 d1 q2 d2 q3 d3 q4 d4 q5 d5 q6 d6 q7 d7 q8 d8 q9 d9 q10 d10",
		COMMANDKEY
	);

	IS_REDIS_REPLY_VALID(CONTEXT);

	COMMAND.Inputs.Params.UserRepliesDataSet.q1 = "";
	COMMAND.Inputs.Params.UserRepliesDataSet.q2 = "";
	COMMAND.Inputs.Params.UserRepliesDataSet.q3 = "";
	COMMAND.Inputs.Params.UserRepliesDataSet.q4 = "";
	COMMAND.Inputs.Params.UserRepliesDataSet.q5 = "";
	COMMAND.Inputs.Params.UserRepliesDataSet.q6 = "";
	COMMAND.Inputs.Params.UserRepliesDataSet.q7 = "";
	COMMAND.Inputs.Params.UserRepliesDataSet.q8 = "";
	COMMAND.Inputs.Params.UserRepliesDataSet.q9 = "";
	COMMAND.Inputs.Params.UserRepliesDataSet.q10 = "";
	
	COMMAND.Inputs.Params.UserRepliesDataSet.d1 = "";
	COMMAND.Inputs.Params.UserRepliesDataSet.d2 = "";
	COMMAND.Inputs.Params.UserRepliesDataSet.d3 = "";
	COMMAND.Inputs.Params.UserRepliesDataSet.d4 = "";
	COMMAND.Inputs.Params.UserRepliesDataSet.d5 = "";
	COMMAND.Inputs.Params.UserRepliesDataSet.d6 = "";
	COMMAND.Inputs.Params.UserRepliesDataSet.d7 = "";
	COMMAND.Inputs.Params.UserRepliesDataSet.d8 = "";
	COMMAND.Inputs.Params.UserRepliesDataSet.d9 = "";
	COMMAND.Inputs.Params.UserRepliesDataSet.d10 = "";

	if (COMMAND.redisReply->element[0]->type == REDIS_REPLY_NIL) {
		COPY_ERROR_MESSAGE(CONTEXT, NOT_FOUND_MESSAGE);
	}
	else {
		if (COMMAND.redisReply->elements == 20) {
			COMMAND.Inputs.Params.UserRepliesDataSet.q1 = (COMMAND.redisReply->element[0]->str) ? COMMAND.redisReply->element[0]->str : "";
			COMMAND.Inputs.Params.UserRepliesDataSet.d1 = (COMMAND.redisReply->element[1]->str) ? COMMAND.redisReply->element[1]->str : "";

			COMMAND.Inputs.Params.UserRepliesDataSet.q2 = (COMMAND.redisReply->element[2]->str) ? COMMAND.redisReply->element[2]->str : "";
			COMMAND.Inputs.Params.UserRepliesDataSet.d2 = (COMMAND.redisReply->element[3]->str) ? COMMAND.redisReply->element[3]->str : "";

			COMMAND.Inputs.Params.UserRepliesDataSet.q3 = (COMMAND.redisReply->element[4]->str) ? COMMAND.redisReply->element[4]->str : "";
			COMMAND.Inputs.Params.UserRepliesDataSet.d3 = (COMMAND.redisReply->element[5]->str) ? COMMAND.redisReply->element[5]->str : "";

			COMMAND.Inputs.Params.UserRepliesDataSet.q4 = (COMMAND.redisReply->element[6]->str) ? COMMAND.redisReply->element[6]->str : "";
			COMMAND.Inputs.Params.UserRepliesDataSet.d4 = (COMMAND.redisReply->element[7]->str) ? COMMAND.redisReply->element[7]->str : "";

			COMMAND.Inputs.Params.UserRepliesDataSet.q5 = (COMMAND.redisReply->element[8]->str) ? COMMAND.redisReply->element[8]->str : "";
			COMMAND.Inputs.Params.UserRepliesDataSet.d5 = (COMMAND.redisReply->element[9]->str) ? COMMAND.redisReply->element[9]->str : "";

			COMMAND.Inputs.Params.UserRepliesDataSet.q6 = (COMMAND.redisReply->element[10]->str) ? COMMAND.redisReply->element[10]->str : "";
			COMMAND.Inputs.Params.UserRepliesDataSet.d6 = (COMMAND.redisReply->element[11]->str) ? COMMAND.redisReply->element[11]->str : "";

			COMMAND.Inputs.Params.UserRepliesDataSet.q7 = (COMMAND.redisReply->element[12]->str) ? COMMAND.redisReply->element[12]->str : "";
			COMMAND.Inputs.Params.UserRepliesDataSet.d7 = (COMMAND.redisReply->element[13]->str) ? COMMAND.redisReply->element[13]->str : "";

			COMMAND.Inputs.Params.UserRepliesDataSet.q8 = (COMMAND.redisReply->element[14]->str) ? COMMAND.redisReply->element[14]->str : "";
			COMMAND.Inputs.Params.UserRepliesDataSet.d8 = (COMMAND.redisReply->element[15]->str) ? COMMAND.redisReply->element[15]->str : "";

			COMMAND.Inputs.Params.UserRepliesDataSet.q9 = (COMMAND.redisReply->element[16]->str) ? COMMAND.redisReply->element[16]->str : "";
			COMMAND.Inputs.Params.UserRepliesDataSet.d9 = (COMMAND.redisReply->element[17]->str) ? COMMAND.redisReply->element[17]->str : "";

			COMMAND.Inputs.Params.UserRepliesDataSet.q10 = (COMMAND.redisReply->element[18]->str) ? COMMAND.redisReply->element[18]->str : "";
			COMMAND.Inputs.Params.UserRepliesDataSet.d10 = (COMMAND.redisReply->element[19]->str) ? COMMAND.redisReply->element[19]->str : "";			
		}
	}

Failed:

	return retval;
}