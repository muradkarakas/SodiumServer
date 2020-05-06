#include "FastApi.h"



FastApiErrorCode
ExecuteSetQuestionInfo(HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;
	
	IS_KEY_VALID(CONTEXT);

	IS_REDIS_CONTEXT_VALID(CONTEXT);

	COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "hmset q%s text %s a1 %s a2 %s a3 %s a4 %s a5 %s trueOption %s replyDuration %s waitDuration %s", 
		COMMANDKEY,
		(COMMAND.Inputs.Params.setQuestionInfoParams.QuestionDataSet.text) ? COMMAND.Inputs.Params.setQuestionInfoParams.QuestionDataSet.text: "",
		(COMMAND.Inputs.Params.setQuestionInfoParams.QuestionDataSet.a1) ? COMMAND.Inputs.Params.setQuestionInfoParams.QuestionDataSet.a1: "",
		(COMMAND.Inputs.Params.setQuestionInfoParams.QuestionDataSet.a2) ? COMMAND.Inputs.Params.setQuestionInfoParams.QuestionDataSet.a2: "",
		(COMMAND.Inputs.Params.setQuestionInfoParams.QuestionDataSet.a3) ? COMMAND.Inputs.Params.setQuestionInfoParams.QuestionDataSet.a3: "",
		(COMMAND.Inputs.Params.setQuestionInfoParams.QuestionDataSet.a4) ? COMMAND.Inputs.Params.setQuestionInfoParams.QuestionDataSet.a4: "",
		(COMMAND.Inputs.Params.setQuestionInfoParams.QuestionDataSet.a5) ? COMMAND.Inputs.Params.setQuestionInfoParams.QuestionDataSet.a5: "",
		(COMMAND.Inputs.Params.setQuestionInfoParams.QuestionDataSet.trueOption) ? COMMAND.Inputs.Params.setQuestionInfoParams.QuestionDataSet.trueOption: "",
		(COMMAND.Inputs.Params.setQuestionInfoParams.QuestionDataSet.replyDuration) ? COMMAND.Inputs.Params.setQuestionInfoParams.QuestionDataSet.replyDuration : "",
		(COMMAND.Inputs.Params.setQuestionInfoParams.QuestionDataSet.waitDuration) ? COMMAND.Inputs.Params.setQuestionInfoParams.QuestionDataSet.waitDuration : ""
		);

	IS_REDIS_REPLY_VALID(CONTEXT);

Failed:

	return retval;
}