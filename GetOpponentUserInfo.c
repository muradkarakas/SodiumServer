#include "FastApi.h"

FastApiErrorCode
ExecuteGetOpponentUserInfo(HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;

	IS_KEY_VALID(CONTEXT);

	IS_REDIS_CONTEXT_VALID(CONTEXT);

	COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "hmget %s rolename opponentUsername", COMMANDKEY);

	IS_REDIS_REPLY_VALID(CONTEXT);

	COMMAND.Inputs.Params.UserDataSet.name = "";
	COMMAND.Inputs.Params.UserDataSet.surname = "";
	COMMAND.Inputs.Params.UserDataSet.password = "";
	COMMAND.Inputs.Params.UserDataSet.rolename = "";

	COMMAND.Inputs.Params.UserDataSet.totalTrueReplyCount = "";
	COMMAND.Inputs.Params.UserDataSet.totalFalseReplyCount = "";
	COMMAND.Inputs.Params.UserDataSet.totalNoReplyCount = "";

	COMMAND.Inputs.Params.UserDataSet.totalReplyDuration = "";
	COMMAND.Inputs.Params.UserDataSet.lastAccessTime = "";
	COMMAND.Inputs.Params.UserDataSet.opponentUsername = "";
	COMMAND.Inputs.Params.UserDataSet.type = "";

	// Check "rolename" 
	if (COMMAND.redisReply->element[0]->str == NULL) {
		COPY_ERROR_MESSAGE(CONTEXT, NOT_FOUND_MESSAGE);
	}
	else {

		if (COMMAND.redisReply->elements == 2) {

			if (COMMAND.redisReply->element[1]->str) {
				char opponentUsername[100];
				strncpy_s(opponentUsername, 100, COMMAND.redisReply->element[1]->str, 100);

				FREE_REDIS_REPLY(CONTEXT);

				COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "HMGET %s name surname rolename totalTrueReplyCount totalFalseReplyCount totalNoReplyCount totalReplyDuration lastAccessTime opponentUsername username type",
					opponentUsername
				);

				IS_REDIS_REPLY_VALID(CONTEXT);

				// check if role name is exists
				if (COMMAND.redisReply->element[2]->str == NULL) {
					COPY_ERROR_MESSAGE(CONTEXT, NOT_FOUND_MESSAGE);
				}
				else {
					if (COMMAND.redisReply->elements == 11) {
						COMMAND.Inputs.Params.UserDataSet.name = (COMMAND.redisReply->element[0]->str) ? COMMAND.redisReply->element[0]->str : "";
						COMMAND.Inputs.Params.UserDataSet.surname = (COMMAND.redisReply->element[1]->str) ? COMMAND.redisReply->element[1]->str : "";
						COMMAND.Inputs.Params.UserDataSet.password = NULL;
						COMMAND.Inputs.Params.UserDataSet.rolename = (COMMAND.redisReply->element[2]->str) ? COMMAND.redisReply->element[2]->str : "";

						COMMAND.Inputs.Params.UserDataSet.totalTrueReplyCount = (COMMAND.redisReply->element[3]->str) ? COMMAND.redisReply->element[3]->str : "0";
						COMMAND.Inputs.Params.UserDataSet.totalFalseReplyCount = (COMMAND.redisReply->element[4]->str) ? COMMAND.redisReply->element[4]->str : "0";
						COMMAND.Inputs.Params.UserDataSet.totalNoReplyCount = (COMMAND.redisReply->element[5]->str) ? COMMAND.redisReply->element[5]->str : "0";

						COMMAND.Inputs.Params.UserDataSet.totalReplyDuration = (COMMAND.redisReply->element[6]->str) ? COMMAND.redisReply->element[6]->str : "0";
						COMMAND.Inputs.Params.UserDataSet.lastAccessTime = (COMMAND.redisReply->element[7]->str) ? COMMAND.redisReply->element[7]->str : "0";
						COMMAND.Inputs.Params.UserDataSet.opponentUsername = (COMMAND.redisReply->element[8]->str) ? COMMAND.redisReply->element[8]->str : "0";
						COMMAND.Inputs.Params.UserDataSet.username = (COMMAND.redisReply->element[9]->str) ? COMMAND.redisReply->element[9]->str : "";
						COMMAND.Inputs.Params.UserDataSet.type = (COMMAND.redisReply->element[10]->str) ? COMMAND.redisReply->element[10]->str : "";
					}
				}
			}
			else {
				COPY_ERROR_MESSAGE(CONTEXT, NOT_FOUND_MESSAGE);
				//ZeroMemory(&COMMAND.Inputs.Params.RegisterUserParams, sizeof(COMMAND.Inputs.Params.RegisterUserParams));
			}
			
		}
	}
	
Failed:

	return retval;
}