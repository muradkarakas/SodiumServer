﻿#include "FastApi.h"

FastApiErrorCode
ExecuteDeleteAllObservers(
	HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;

	IS_KEY_VALID(context);

	IS_REDIS_CONTEXT_VALID(context);

	// TODO:	player olarak eklenen kullanıcı 
	//		*	registered bir kullanıcı mı ?
	//		*	observer listesinde de kayıtlı mı ?

	context->Command.redisReply = redisCommand(REDISCONTEXT, "del %s", OBSERVER_LIST_KEY_NAME);

	IS_REDIS_REPLY_VALID(context);

Failed:

	return retval;
}