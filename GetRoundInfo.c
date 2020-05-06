#include "FastApi.h"


FastApiErrorCode
ExecuteGetRoundInfo(HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;
	
	IS_KEY_VALID(CONTEXT);

	IS_REDIS_CONTEXT_VALID(CONTEXT);

	COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "hmget round%s questionCount matchingStartDate roundStartDate calculatedEndTime", COMMANDKEY);

	IS_REDIS_REPLY_VALID(CONTEXT);

	COMMAND.Inputs.Params.setRoundInfoParams.RoundInfoSet.questionCount = "";
	COMMAND.Inputs.Params.setRoundInfoParams.RoundInfoSet.matchingStartTime = "";
	COMMAND.Inputs.Params.setRoundInfoParams.RoundInfoSet.roundStartTime = "";
	COMMAND.Inputs.Params.setRoundInfoParams.RoundInfoSet.calculatedEndTime = "";

	if (COMMAND.redisReply->element[1]->str == NULL) {
		COPY_ERROR_MESSAGE(CONTEXT, NOT_FOUND_MESSAGE);
	}
	else {
		if (COMMAND.redisReply->elements == 4) {
			COMMAND.Inputs.Params.setRoundInfoParams.RoundInfoSet.questionCount = (COMMAND.redisReply->element[0]->str) ? COMMAND.redisReply->element[0]->str : "";
			COMMAND.Inputs.Params.setRoundInfoParams.RoundInfoSet.matchingStartTime = (COMMAND.redisReply->element[1]->str) ? COMMAND.redisReply->element[1]->str : "";
			COMMAND.Inputs.Params.setRoundInfoParams.RoundInfoSet.roundStartTime = (COMMAND.redisReply->element[2]->str) ? COMMAND.redisReply->element[2]->str : "";
			COMMAND.Inputs.Params.setRoundInfoParams.RoundInfoSet.calculatedEndTime = (COMMAND.redisReply->element[3]->str) ? COMMAND.redisReply->element[3]->str : "";
		}
	}
	

Failed:

	return retval;
}