#include "LiveQuiz.h"

FastApiErrorCode
ExecuteGetQuestionInfo(HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;
	
	IS_KEY_VALID(context);

	IS_REDIS_CONTEXT_VALID(context);

	context->Command.redisReply = redisCommand(REDISCONTEXT, "hmget q%s text a1 a2 a3 a4 a5 trueOption duration", COMMANDKEY);

	IS_REDIS_REPLY_VALID(context);

	if (context->Command.redisReply->element[0]->str == NULL)
		COPY_ERROR_MESSAGE(context, NOT_FOUND_MESSAGE);

	if (context->Command.redisReply->elements == 8) {
		context->Command.Params.p.QuestionInfoParams.text = (context->Command.redisReply->element[0]->str) ? context->Command.redisReply->element[0]->str:"";
		context->Command.Params.p.QuestionInfoParams.a1 = (context->Command.redisReply->element[1]->str) ? context->Command.redisReply->element[1]->str:"";
		context->Command.Params.p.QuestionInfoParams.a2 = (context->Command.redisReply->element[2]->str) ? context->Command.redisReply->element[2]->str:"";
		context->Command.Params.p.QuestionInfoParams.a3 = (context->Command.redisReply->element[3]->str) ? context->Command.redisReply->element[3]->str:"";
		context->Command.Params.p.QuestionInfoParams.a4 = (context->Command.redisReply->element[4]->str) ? context->Command.redisReply->element[4]->str:"";
		context->Command.Params.p.QuestionInfoParams.a5 = (context->Command.redisReply->element[5]->str) ? context->Command.redisReply->element[5]->str:"";
		context->Command.Params.p.QuestionInfoParams.trueOption = (context->Command.redisReply->element[6]->str) ? context->Command.redisReply->element[6]->str:"";
		context->Command.Params.p.QuestionInfoParams.duration = (context->Command.redisReply->element[7]->str) ? context->Command.redisReply->element[7]->str:"";
	}

Failed:

	return retval;
}