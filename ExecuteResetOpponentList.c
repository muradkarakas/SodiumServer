#include "LiveQuiz.h"

FastApiErrorCode
ExecuteResetOpponentList(HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;

	IS_KEY_VALID(context);

	IS_REDIS_CONTEXT_VALID(context);

	//	
	//	Delete OPPONENT_USER_LIST_KEY_NAME list first
	//
	context->Command.redisReply = redisCommand(REDISCONTEXT, "del %s", OPPONENT_USER_LIST_KEY_NAME);

	IS_REDIS_REPLY_VALID(context);

	// 
	// Copy Registered user list to Opponent User list
	// 
	context->Command.redisReply = redisCommand(REDISCONTEXT, "SUNIONSTORE %s %s", OPPONENT_USER_LIST_KEY_NAME, REGISTERED_USER_LIST_KEY_NAME);

	IS_REDIS_REPLY_VALID(context);

	//
	// Done
	//

Failed:

	return retval;
}