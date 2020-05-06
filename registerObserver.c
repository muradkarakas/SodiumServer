#include "LiveQuiz.h"

FastApiErrorCode
ExecuteRegisterObserver(
	HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;

	if (context->Command.Params.p.registerPlayerParams.username == NULL) {
		retval = ERROR_MISSING_PARAMETER;
		COPY_ERROR_MESSAGE(context, "username is missing");
		goto Failed;
	}

	IS_KEY_VALID(context);

	IS_REDIS_CONTEXT_VALID(context);

	// TODO:	player olarak eklenen kullanıcı 
	//		*	registered bir kullanıcı mı ?
	//		*	observer listesinde de kayıtlı mı ?

	context->Command.redisReply = redisCommand(REDISCONTEXT, "sadd %s %s",
		OBSERVER_LIST_KEY_NAME,
		context->Command.Params.p.registerPlayerParams.username);

	IS_REDIS_REPLY_VALID(context);

Failed:

	return retval;
}