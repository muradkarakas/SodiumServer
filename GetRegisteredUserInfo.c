#include "LiveQuiz.h"

FastApiErrorCode
ExecuteGetRegisteredUserInfo(HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;

	IS_KEY_VALID(context);

	IS_REDIS_CONTEXT_VALID(context);

	context->Command.redisReply = redisCommand(REDISCONTEXT, "hmget %s name surname rolename", COMMANDKEY);

	IS_REDIS_REPLY_VALID(context);

	if (context->Command.redisReply->element[2]->str == NULL) {
		COPY_ERROR_MESSAGE(context, NOT_FOUND_MESSAGE);
	}

	if (context->Command.redisReply->elements == 3) {
		context->Command.Params.p.RegisterUserParams.name = (context->Command.redisReply->element[0]->str) ? context->Command.redisReply->element[0]->str:"";
		context->Command.Params.p.RegisterUserParams.surname = (context->Command.redisReply->element[1]->str) ? context->Command.redisReply->element[1]->str:"";
		context->Command.Params.p.RegisterUserParams.password = NULL;
		context->Command.Params.p.RegisterUserParams.rolename = (context->Command.redisReply->element[2]->str) ? context->Command.redisReply->element[2]->str:"";
	}

Failed:

	return retval;
}