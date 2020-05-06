#include "LiveQuiz.h"

FastApiErrorCode
ExecuteSetQuestionInfo(HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;
	
	IS_KEY_VALID(context);

	IS_REDIS_CONTEXT_VALID(context);

	context->Command.redisReply = redisCommand(REDISCONTEXT, "hmset q%s text %s a1 %s a2 %s a3 %s a4 %s a5 %s trueOption %s duration %s", 
		COMMANDKEY,
		context->Command.Params.p.QuestionInfoParams.text,
		context->Command.Params.p.QuestionInfoParams.a1,
		context->Command.Params.p.QuestionInfoParams.a2,
		context->Command.Params.p.QuestionInfoParams.a3,
		context->Command.Params.p.QuestionInfoParams.a4,
		context->Command.Params.p.QuestionInfoParams.a5,
		context->Command.Params.p.QuestionInfoParams.trueOption,
		context->Command.Params.p.QuestionInfoParams.duration
		);

	IS_REDIS_REPLY_VALID(context);

Failed:

	return retval;
}