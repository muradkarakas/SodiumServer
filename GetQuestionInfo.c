#include "FastApi.h"

FastApiErrorCode
ExecuteGetQuestionInfo(HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;
	
	IS_KEY_VALID(CONTEXT);

	IS_REDIS_CONTEXT_VALID(CONTEXT);

	COMMAND.Output.getQuestionInfoParams.QuestionDataSet.text = "";
	COMMAND.Output.getQuestionInfoParams.QuestionDataSet.a1 = "";
	COMMAND.Output.getQuestionInfoParams.QuestionDataSet.a2 = "";
	COMMAND.Output.getQuestionInfoParams.QuestionDataSet.a3 = "";
	COMMAND.Output.getQuestionInfoParams.QuestionDataSet.a4 = "";
	COMMAND.Output.getQuestionInfoParams.QuestionDataSet.a5 = "";
	COMMAND.Output.getQuestionInfoParams.QuestionDataSet.trueOption = "";
	COMMAND.Output.getQuestionInfoParams.QuestionDataSet.replyDuration = "";
	COMMAND.Output.getQuestionInfoParams.QuestionDataSet.waitDuration = "";

	COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "hmget q%s text a1 a2 a3 a4 a5 trueOption replyDuration waitDuration", COMMANDKEY);

	IS_REDIS_REPLY_VALID(CONTEXT);

	if (COMMAND.redisReply->element[0]->str == NULL) {
		COPY_ERROR_MESSAGE(CONTEXT, NOT_FOUND_MESSAGE);
	}
	else {
		if (COMMAND.redisReply->elements == 9) {
			COMMAND.Output.getQuestionInfoParams.QuestionDataSet.text = (COMMAND.redisReply->element[0]->str) ? COMMAND.redisReply->element[0]->str : "";
			COMMAND.Output.getQuestionInfoParams.QuestionDataSet.a1 = (COMMAND.redisReply->element[1]->str) ? COMMAND.redisReply->element[1]->str : "";
			COMMAND.Output.getQuestionInfoParams.QuestionDataSet.a2 = (COMMAND.redisReply->element[2]->str) ? COMMAND.redisReply->element[2]->str : "";
			COMMAND.Output.getQuestionInfoParams.QuestionDataSet.a3 = (COMMAND.redisReply->element[3]->str) ? COMMAND.redisReply->element[3]->str : "";
			COMMAND.Output.getQuestionInfoParams.QuestionDataSet.a4 = (COMMAND.redisReply->element[4]->str) ? COMMAND.redisReply->element[4]->str : "";
			COMMAND.Output.getQuestionInfoParams.QuestionDataSet.a5 = (COMMAND.redisReply->element[5]->str) ? COMMAND.redisReply->element[5]->str : "";
			COMMAND.Output.getQuestionInfoParams.QuestionDataSet.trueOption = (COMMAND.redisReply->element[6]->str) ? COMMAND.redisReply->element[6]->str : "";
			COMMAND.Output.getQuestionInfoParams.QuestionDataSet.replyDuration = (COMMAND.redisReply->element[7]->str) ? COMMAND.redisReply->element[7]->str : "";
			COMMAND.Output.getQuestionInfoParams.QuestionDataSet.waitDuration = (COMMAND.redisReply->element[8]->str) ? COMMAND.redisReply->element[8]->str : "";
		}
	}	

Failed:

	return retval;
}