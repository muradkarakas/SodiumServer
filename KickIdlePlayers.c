#include "FastApi.h"


FastApiErrorCode
ExecuteKickIdlePlayers(
	HttpContext *context) {

	redisReply *redisReply1 = NULL;
	redisReply *redisReply2 = NULL;

	GET_SERVER_TIME_FOR_LOGGER(lt);

	__int64  totalProcessedPlayerCount = 0;
	__int64  totalKickedPlayerCount = 0;
	char *player1 = NULL;
	char	tmStr[30];
	__int64 MaxServerIdleTimeAllowed = _strtoui64(COMMAND.Inputs.Params.KickIdlePlayersParams.idleTimeInSeconds, NULL, 10) * 1000; // 30 seconds
	__int64	player1LastAccessTime = 0;
	__int64 currentServerTime = 0;
	FastApiErrorCode retval = ERROR_SUCCESSFUL;

	IS_KEY_VALID(CONTEXT);

	IS_REDIS_CONTEXT_VALID(CONTEXT);

	//
	//	Start Redis Transaction
	//
	//COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "MULTI");
	//IS_REDIS_REPLY_VALID(CONTEXT);

	//	reset return values

	//	Tüm oyuncu listesini çek
	//
	char cursor[10] = "";
	char cursorCommand[100] = "";

	printf("\n///////////////////////////////////////////////////////////////////");
	printf("\n%s: Kick Idle Players started...", lt);

	//	fetching first bundle
	printf("\n\n%s:    Fetching players...", lt);
	strcpy_s(cursorCommand, 100, "sscan " PLAYER_LIST_KEY_NAME " 0");
	redisReply1 = redisCommand(REDIS_CONTEXT, cursorCommand);
	IS_LOCAL_REPLY_VALID(redisReply1);
	printf(" done.");

	while (redisReply1 && redisReply1->type != REDIS_REPLY_ERROR && redisReply1->elements == 2) {

		// prepare cursor for next loop
		strcpy_s(cursor, 10, redisReply1->element[0]->str);

		// bundle matching started
		int matchedPlayerCountInBundled = 0;

		FastApi_GetLocalTime(tmStr, 30);
		currentServerTime = _strtoui64(tmStr, NULL, 10);

		// loop for players for current bundle  
		for (; matchedPlayerCountInBundled < redisReply1->element[1]->elements; matchedPlayerCountInBundled++) {

			// matching
			player1 = redisReply1->element[1]->element[matchedPlayerCountInBundled]->str;

			redisReply2 = redisCommand(REDIS_CONTEXT, "hget %s lastAccessTime", player1);
			if (redisReply2 && redisReply2->type != REDIS_REPLY_ERROR) {
				player1LastAccessTime = _strtoui64(redisReply2->str, NULL, 10);					
				freeReplyObject(redisReply2);
				redisReply2 = NULL; 
				// getting current server time				
				
				// check how many milisecond passed since last access
				__int64 timePassed = currentServerTime - player1LastAccessTime;
				if (timePassed >= MaxServerIdleTimeAllowed) {
					/*_registerObserver(context, player1);					
					printf("\n    kicked: %s, idle for %.0f secs", player1, (double)(timePassed/1000));
					totalKickedPlayerCount++;*/
				}
			}
		}

		SET_SERVER_TIME_FOR_LOGGER(lt);
		printf("\n%s:    %d players processed\n", lt, matchedPlayerCountInBundled);

		totalProcessedPlayerCount += matchedPlayerCountInBundled;

		// fetching next bundle
		if (cursor[0] != '0') {
			// there is more bundle to read from server
			strcpy_s(cursorCommand, 100, "sscan " PLAYER_LIST_KEY_NAME " ");
			strcat_s(cursorCommand, 100, cursor);
			freeReplyObject(redisReply1);
			SET_SERVER_TIME_FOR_LOGGER(lt);
			printf("\n%s:    Fetching players...", lt);
			redisReply1 = redisCommand(REDIS_CONTEXT, cursorCommand);
			IS_LOCAL_REPLY_VALID(redisReply1);
			printf(" done.");
		}
		else {
			// no more bundle left 
			freeReplyObject(redisReply1);
			redisReply1 = NULL;
			break;
		}

	}

	SET_SERVER_TIME_FOR_LOGGER(lt);
	printf("\n%s: %I64u total players processed.", lt, totalProcessedPlayerCount);

	printf("\n\n%s: Kick Idle Players ended", lt);
	printf("\n///////////////////////////////////////////////////////////////////\n");
	//
	//	Commit Redis Transaction if no error occured
	//
	//COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "EXEC");
	//IS_REDIS_REPLY_VALID(CONTEXT);

	COMMAND.Output.KickIdlePlayersParams.processedPlayerCount = totalProcessedPlayerCount;
	COMMAND.Output.KickIdlePlayersParams.kickedPlayerCount = totalKickedPlayerCount;

Failed:
	if (redisReply1)
		freeReplyObject(redisReply1);

	if (redisReply2)
		freeReplyObject(redisReply2);
	
	return retval;
}

