#include "LiveQuiz.h"

FastApiErrorCode
ExecuteDeleteAllPlayers(
	HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;

	if (REDISCONTEXT->err != 0) {
		COPY_ERROR_MESSAGE(context, REDISCONTEXT->errstr);
		retval = ERROR_REDIS_ERROR_OCCURED;
		goto Failed;
	}
	
	IS_KEY_VALID(context);

	IS_REDIS_CONTEXT_VALID(context);

	// TODO:	player olarak eklenen kullanıcı 
	//		*	registered bir kullanıcı mı ?
	//		*	observer listesinde de kayıtlı mı ?

	context->Command.redisReply = redisCommand(REDISCONTEXT, "del %s", PLAYER_LIST_KEY_NAME);

	IS_REDIS_REPLY_VALID(context);

Failed:

	return retval;
}