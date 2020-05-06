#include "LiveQuiz.h"

FastApiErrorCode
ExecuteRegisterUser(
	HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;

	IS_KEY_VALID(context);

	IS_REDIS_CONTEXT_VALID(context);

	context->Command.redisReply = redisCommand(REDISCONTEXT, "HMSET %s %s %s %s %s %s %s %s %s",
		COMMANDKEY,
		// name
		(context->Command.Params.p.RegisterUserParams.name) ? "name":"",
		(context->Command.Params.p.RegisterUserParams.name) ? context->Command.Params.p.RegisterUserParams.name:"",
		// surname
		(context->Command.Params.p.RegisterUserParams.surname) ? "surname" : "",
		(context->Command.Params.p.RegisterUserParams.surname) ? context->Command.Params.p.RegisterUserParams.surname:"",
		// password
		(context->Command.Params.p.RegisterUserParams.password) ? "password" : "",
		(context->Command.Params.p.RegisterUserParams.password) ? context->Command.Params.p.RegisterUserParams.password:"",
		// rolename
		(context->Command.Params.p.RegisterUserParams.rolename) ? "rolename" : "",
		(context->Command.Params.p.RegisterUserParams.rolename) ? context->Command.Params.p.RegisterUserParams.rolename:""
		);

	IS_REDIS_REPLY_VALID(context);

	context->Command.redisReply = redisCommand(REDISCONTEXT, "sadd %s %s", REGISTERED_USER_LIST_KEY_NAME, COMMANDKEY);

	IS_REDIS_REPLY_VALID(context);

Failed:

	return retval;
}