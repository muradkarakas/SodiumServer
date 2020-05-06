#include "FastApi.h"

FastApiErrorCode
ExecuteSetRoundInfo(HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;
	
	IS_KEY_VALID(CONTEXT);

	IS_REDIS_CONTEXT_VALID(CONTEXT);

	COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "hmset round%s questionCount %s %s %s %s %s %s %s",
		COMMANDKEY,
		(COMMAND.Inputs.Params.setRoundInfoParams.RoundInfoSet.questionCount) ? COMMAND.Inputs.Params.setRoundInfoParams.RoundInfoSet.questionCount:"",

		(COMMAND.Inputs.Params.setRoundInfoParams.RoundInfoSet.matchingStartTime) ? "matchingStartDate":"",
		(COMMAND.Inputs.Params.setRoundInfoParams.RoundInfoSet.matchingStartTime) ? COMMAND.Inputs.Params.setRoundInfoParams.RoundInfoSet.matchingStartTime:"",

		(COMMAND.Inputs.Params.setRoundInfoParams.RoundInfoSet.roundStartTime) ? "roundStartDate" : "",
		(COMMAND.Inputs.Params.setRoundInfoParams.RoundInfoSet.roundStartTime) ? COMMAND.Inputs.Params.setRoundInfoParams.RoundInfoSet.roundStartTime:"",

		(COMMAND.Inputs.Params.setRoundInfoParams.RoundInfoSet.calculatedEndTime) ? "calculatedEndTime" : "",
		(COMMAND.Inputs.Params.setRoundInfoParams.RoundInfoSet.calculatedEndTime) ? COMMAND.Inputs.Params.setRoundInfoParams.RoundInfoSet.calculatedEndTime :"");

	IS_REDIS_REPLY_VALID(CONTEXT);

Failed:

	return retval;
}