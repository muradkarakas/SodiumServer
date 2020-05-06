#include "LiveQuiz.h"

FastApiErrorCode
ExecuteSetRoundInfo(HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;
	
	IS_KEY_VALID(context);

	IS_REDIS_CONTEXT_VALID(context);

	context->Command.redisReply = redisCommand(REDISCONTEXT, "hmset round%s questionCount %s matchingStartDate %s roundStartDate %s", 
		COMMANDKEY,
		context->Command.Params.p.RoundInfoParams.questionCount,
		context->Command.Params.p.RoundInfoParams.matchingStartTime,
		context->Command.Params.p.RoundInfoParams.roundStartTime);

	IS_REDIS_REPLY_VALID(context);

Failed:

	return retval;
}