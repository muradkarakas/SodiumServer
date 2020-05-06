#include "FastApi.h"

FastApiErrorCode
ExecuteResetAllPlayersStatistics(
	HttpContext *context) {

	int  totalProcessedPlayerCount = 0;
	FastApiErrorCode	retval = ERROR_SUCCESSFUL;
	
	IS_KEY_VALID(CONTEXT);

	IS_REDIS_CONTEXT_VALID(CONTEXT);

	//
	//	Start Redis Transaction
	//
	//COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "MULTI");
	//IS_REDIS_REPLY_VALID(CONTEXT);

	//	reset return values
	COMMAND.Output.ResetAllPlayersStatisticsParams.processedPlayerCount = 0;

	//	Tüm oyuncu listesini çek
	//
	char cursor[10] = "";
	char cursorCommand[100] = "";
	GET_SERVER_TIME_FOR_LOGGER(lt);

	printf("\n///////////////////////////////////////////////////////////////////");
	printf("\n%s: Reset all players' statistics started...", lt);
		
	//	fetching first bundle
	printf("\n\n%s:    Fetching players...", lt);
	strcpy_s(cursorCommand, 100, "sscan " PLAYER_LIST_KEY_NAME " 0");
	redisReply *redisReply = redisCommand(REDIS_CONTEXT, cursorCommand);
	IS_LOCAL_REPLY_VALID(redisReply);
	printf(" done.");

	while (redisReply && redisReply->type != REDIS_REPLY_ERROR && redisReply->elements == 2) {

		// prepare cursor for next loop
		strcpy_s(cursor, 10, redisReply->element[0]->str);

		// bundle matching started
		int matchedPlayerCountInBundled = 0;

		// loop for players for current bundle  
		for (; matchedPlayerCountInBundled < redisReply->element[1]->elements; matchedPlayerCountInBundled++) {
			retval = _resetUserStatistics(CONTEXT, redisReply->element[1]->element[matchedPlayerCountInBundled]->str);
			if (retval != ERROR_SUCCESSFUL)
				goto Failed;
		}

		SET_SERVER_TIME_FOR_LOGGER(lt);
		printf("\n%s:    %d players processed\n", lt, matchedPlayerCountInBundled);

		totalProcessedPlayerCount += matchedPlayerCountInBundled;

		// fetching next bundle
		if (cursor[0] != '0') {
			// there is more bundle to read from server
			strcpy_s(cursorCommand, 100, "sscan " PLAYER_LIST_KEY_NAME " ");
			strcat_s(cursorCommand, 100, cursor);
			freeReplyObject(redisReply);
			GET_SERVER_TIME_FOR_LOGGER(lt);
			printf("\n%s:    Fetching players...", lt);
			redisReply = redisCommand(REDIS_CONTEXT, cursorCommand);
			IS_LOCAL_REPLY_VALID(redisReply);
			printf(" done.");
		}
		else {
			// no more bundle left 
			
			freeReplyObject(redisReply);
			redisReply = NULL;
			break;
		}

	}

	COMMAND.Output.ResetAllPlayersStatisticsParams.processedPlayerCount = totalProcessedPlayerCount;
	
	SET_SERVER_TIME_FOR_LOGGER(lt);
	printf("\n%s: %I64u total players' statistics are cleared.", lt, COMMAND.Output.ResetAllPlayersStatisticsParams.processedPlayerCount);
	SET_SERVER_TIME_FOR_LOGGER(lt);
	printf("\n\n%s: Reset all players' statistics ended", lt);
	printf("\n///////////////////////////////////////////////////////////////////\n");
	//
	//	Commit Redis Transaction if no error occured
	//
	//COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "EXEC");
	//IS_REDIS_REPLY_VALID(CONTEXT);

Failed:

	if (retval != ERROR_SUCCESSFUL)
		printf("\nError occured while clearing players' statistics.");

	return retval;
}

