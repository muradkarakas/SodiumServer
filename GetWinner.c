#include "FastApi.h"

FastApiErrorCode
ExecuteGetWinner(
	HttpContext *context) {

	FastApiErrorCode	err = ERROR_SUCCESSFUL;
	FastApiErrorCode	retval = ERROR_SUCCESSFUL;

	IS_KEY_VALID(CONTEXT);

	IS_REDIS_CONTEXT_VALID(CONTEXT);

	COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "smembers %s", COMMANDKEY);

	IS_REDIS_REPLY_VALID(CONTEXT);
	
	// TODO: komut redirection işlemleri için standart bir mekanizma geliştir.
	//		 Client'a dönen json içinde yer alan "AdditionalData" nesensi birden fazla komut çıktısını içermeli.
	//		 "COMMAND.Params" değişkeni dizi olmalı ve push/pop benzeri bir mekanizma ile çalışmalı
	//		
	RtlZeroMemory(&COMMAND.Inputs, sizeof(COMMAND.Inputs));
	COMMAND.Inputs.key = "getUserStatistics";
	COMMAND.type = API_COMMAND_GET_USER_STATISTICS;	
	
	if (COMMAND.redisReply->elements == 1 && COMMAND.redisReply->element[0]->str && COMMAND.redisReply->element[0]->str[0] != '\0') {
		if (gProgramOptions.printOutIncomingCommandCodes) {
			printf_s(" calls COMMAND_GET_USER_STATISTICS('%s')", COMMAND.redisReply->element[0]->str);
		}
		COMMANDKEY = COMMAND.redisReply->element[0]->str;		
	}
	else {
		COMMANDKEY = "";
		COPY_ERROR_MESSAGE(CONTEXT, NOT_FOUND_MESSAGE);
		if (gProgramOptions.printOutIncomingCommandCodes) {
			printf_s(" calls COMMAND_GET_USER_STATISTICS('%s')", "no winner");
		}
	}

	EXECUTE_POST_COMMAND(CONTEXT);

Failed:
FailedPost:

	return retval;
}