#include "FastApi.h"

inline FastApiErrorCode
ExecuteScard(HttpContext *context) {

	FastApiErrorCode retval = ERROR_SUCCESSFUL;

	IS_KEY_VALID(context);

	IS_REDIS_CONTEXT_VALID(context);

	context->Command.Params.p.ScardParams.memberCount = 0;

	context->Command.redisReply = redisCommand(REDISCONTEXT, "SCARD %s", COMMANDKEY);

	IS_REDIS_REPLY_VALID(context);

	context->Command.Params.p.ScardParams.memberCount = context->Command.redisReply->integer;
	
Failed:

	return retval;
}
