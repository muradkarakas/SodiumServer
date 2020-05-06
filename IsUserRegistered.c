#include "LiveQuiz.h"

FastApiErrorCode
ExecuteIsUserRegistered(HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;

	IS_KEY_VALID(context);

	IS_REDIS_CONTEXT_VALID(context);

	if (context->Command.Params.p.IsUserRegisteredParams.username == NULL) {
		retval = ERROR_MISSING_PARAMETER;
		COPY_ERROR_MESSAGE(context, "username is missing");
		goto Failed;
	}
	

	context->Command.redisReply = redisCommand(REDISCONTEXT, "sismember %s %s", 
		REGISTERED_USER_LIST_KEY_NAME, 
		context->Command.Params.p.IsUserRegisteredParams.username);

	IS_REDIS_REPLY_VALID(context);
	
	context->Command.Params.p.IsUserRegisteredParams.isUserRegistered = (context->Command.redisReply->integer == 1);
Failed:

	return retval;
}