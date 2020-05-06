#include "FastApi.h"


FastApiErrorCode
eliminateLosers(
	HttpContext *context,
	char	*player1,
	char	*player2) {

	FastApiErrorCode retval = ERROR_SUCCESSFUL;

	if (player1 && player2) {

		BOOLEAN isPlayer1StillExists = FALSE;
		BOOLEAN isPlayer2StillExists = FALSE;

		BOOLEAN player1StaticticsFound = FALSE;
		BOOLEAN player2StaticticsFound = FALSE;

		__int64 player1TrueCount = 0, player1FalseCount = 0, player1Duration = 0;
		__int64 player2TrueCount = 0, player2FalseCount = 0, player2Duration = 0;

		//
		// We are provided 2 players.
		//

		////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//
		//	Check if they are still active players or not
		//
		_isPlayerExists(CONTEXT, player1, &isPlayer1StillExists);
		_isPlayerExists(CONTEXT, player2, &isPlayer2StillExists);

		if (isPlayer1StillExists == FALSE || isPlayer2StillExists == FALSE) {

			if (isPlayer1StillExists == FALSE) {
				printf("  (None. Reason: not a player now: %s)", player1);
			}
			if (isPlayer2StillExists == FALSE) {
				printf("  (None. Reason: not a player now: %s)", player2);
			}

			goto Failed;
		}

		////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//
		//	Getting player1's statistics
		//
		COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "HMGET %s totalTrueReplyCount totalFalseReplyCount totalReplyDuration", player1);

		IS_REDIS_REPLY_VALID(CONTEXT);
		if (COMMAND.redisReply->element[0]->type != REDIS_REPLY_NIL) {
			player1StaticticsFound = TRUE;
			player1TrueCount = _strtoui64(COMMAND.redisReply->element[0]->str, NULL, 10);
			player1FalseCount = _strtoui64(COMMAND.redisReply->element[1]->str, NULL, 10);
			player1Duration = _strtoui64(COMMAND.redisReply->element[2]->str, NULL, 10);
		}
		FREE_REDIS_REPLY(CONTEXT);

		////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//
		//	Getting player2's statistics
		//
		COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "HMGET %s totalTrueReplyCount totalFalseReplyCount totalReplyDuration", player2);

		IS_REDIS_REPLY_VALID(CONTEXT);
		if (COMMAND.redisReply->element[0]->type != REDIS_REPLY_NIL) {
			player2StaticticsFound = TRUE;
			player2TrueCount = _strtoui64(COMMAND.redisReply->element[0]->str, NULL, 10);
			player2FalseCount = _strtoui64(COMMAND.redisReply->element[1]->str, NULL, 10);
			player2Duration = _strtoui64(COMMAND.redisReply->element[2]->str, NULL, 10);
		}
		FREE_REDIS_REPLY(CONTEXT);


		if (gProgramOptions.printOutIncomingCommandCodes) {
			//////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////
			//
			//	Debug output ?
			//
			printf("\n%s-> True: %I64u, False: %I64u, Duration: %I64u", player1, player1TrueCount, player1FalseCount, player1Duration);
			printf("\n%s-> True: %I64u, False: %I64u, Duration: %I64u", player2, player2TrueCount, player2FalseCount, player2Duration);
		}

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//
		//	Check players' statistics exists or not ?
		//
		if (player1StaticticsFound == FALSE || player2StaticticsFound == FALSE) {

			if (player1StaticticsFound == FALSE) {
				retval = _registerObserver(CONTEXT, player1);
				if (retval == ERROR_SUCCESSFUL) {
					retval = _resetOpponentInfo(CONTEXT, player1);
					printf("  (%s. Reason: no statistic info available)", player1);
				}
			}
			if (player2StaticticsFound == FALSE) {
				retval = _registerObserver(CONTEXT, player2);
				if (retval == ERROR_SUCCESSFUL) {
					retval = _resetOpponentInfo(CONTEXT, player2);
					printf("  (%s. Reason: no statistic info available)", player2);
				}
			}

			goto Failed;
		}

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//
		//	Time to check to learn who is the winner ?
		//

		if (player1TrueCount > player2TrueCount) {
			retval = _registerObserver(CONTEXT, player2);
			if (retval == ERROR_SUCCESSFUL) {
				retval = _resetOpponentInfo(CONTEXT, player2);
				printf("  (%s. Reason: score)", player2);
			}
		}
		else if (player1TrueCount < player2TrueCount) {
			retval = _registerObserver(CONTEXT, player1);
			if (retval == ERROR_SUCCESSFUL) {
				retval = _resetOpponentInfo(CONTEXT, player1);
				printf("  (%s. Reason: score)", player1);
			}
		}
		else {
			// score are equal
			if (player1Duration > player2Duration) {
				retval = _registerObserver(CONTEXT, player1);
				if (retval == ERROR_SUCCESSFUL) {
					retval = _resetOpponentInfo(CONTEXT, player1);
					printf("  (%s. Reason: duration)", player1);
				}
			}
			else if (player1Duration < player2Duration) {
				retval = _registerObserver(CONTEXT, player2);
				if (retval == ERROR_SUCCESSFUL) {
					retval = _resetOpponentInfo(CONTEXT, player2);
					printf("  (%s. Reason: duration)", player2);
				}
			}
			else {
				// scores and durations are both equal
				// looking for false count
				if (player1FalseCount > player2FalseCount) {
					retval = _registerObserver(CONTEXT, player1);
					if (retval == ERROR_SUCCESSFUL) {
						retval = _resetOpponentInfo(CONTEXT, player1);
						printf("  (%s. Reason: false count)", player1);
					}
				}
				else if (player1FalseCount < player2FalseCount) {
					retval = _registerObserver(CONTEXT, player2);
					if (retval == ERROR_SUCCESSFUL) {
						retval = _resetOpponentInfo(CONTEXT, player2);
						printf("  (%s. Reason: false count)", player2);
					}
				}
				else {
					//	scores, durations and false counts are equal
					//	if they got a score more than zero, they both will pass the round,
					//	if they both got zero score (this means they do not play, just watch), both will fail.
					if (player1TrueCount == 0) {
						retval = _registerObserver(CONTEXT, player1);
						retval = _registerObserver(CONTEXT, player2);
						retval = _resetOpponentInfo(CONTEXT, player1);
						retval = _resetOpponentInfo(CONTEXT, player2);
						printf("  (Both. Reason: not played)");
					}
					else {
						printf("     No one defeated.");
					}
				}

			}
		}
	}

Failed:

	return retval;
}

FastApiErrorCode
ExecuteEliminateLosers(
	HttpContext *context) {

	redisReply *redisReply1 = NULL;
	redisReply *redisReply2 = NULL;
	redisReply *redisReply3 = NULL;

	GET_SERVER_TIME_FOR_LOGGER(lt);

	int  totalProcessedPlayerCount = 0;
	char *player1 = NULL, *player2 = NULL;
	FastApiErrorCode	retval = ERROR_SUCCESSFUL;

	IS_KEY_VALID(CONTEXT);

	IS_REDIS_CONTEXT_VALID(CONTEXT);

	//
	//	Start Redis Transaction
	//
	//COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "MULTI");
	//IS_REDIS_REPLY_VALID(CONTEXT);

	//	reset return values
	COMMAND.Output.EliminateLosersParams.processedPlayerCount = 0;
	COMMAND.Output.EliminateLosersParams.totalPlayerCountLeft = 0;

	//	Tüm oyuncu listesini çek
	//
	char cursor[10] = "";
	char cursorCommand[100] = "";

	printf("\n///////////////////////////////////////////////////////////////////");
	printf("\n%s: Eliminate Losers started...", lt);

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

		// loop for players for current bundle  
		for (; matchedPlayerCountInBundled < redisReply1->element[1]->elements; matchedPlayerCountInBundled++) {

			// matching
			player1 = redisReply1->element[1]->element[matchedPlayerCountInBundled]->str;

			redisReply2 = redisCommand(REDIS_CONTEXT, "hget %s opponentUsername", player1);
			if (redisReply2 && redisReply2->type != REDIS_REPLY_ERROR) {
				player2 = redisReply2->str;
			}

			if (player1 && player2) {
				// eliminate one of the players in a transaction
				SET_SERVER_TIME_FOR_LOGGER(lt);
				printf("\n%s:      %s vs %s", lt, player1, player2);
				retval = eliminateLosers(CONTEXT, player1, player2);
				if (retval != ERROR_SUCCESSFUL)
					goto Failed;
				printf(" done.");
				player1 = player2 = NULL;
			}

			freeReplyObject(redisReply2);
			redisReply2 = NULL;
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
	printf("\n%s: %d total players processed.", lt, totalProcessedPlayerCount);

	printf("\n\n%s: Eliminate Losers ended", lt);
	printf("\n///////////////////////////////////////////////////////////////////\n");
	//
	//	Commit Redis Transaction if no error occured
	//
	//COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "EXEC");
	//IS_REDIS_REPLY_VALID(CONTEXT);

	redisReply3 = redisCommand(REDIS_CONTEXT, "scard %s", PLAYER_LIST_KEY_NAME);
	IS_LOCAL_REPLY_VALID(redisReply3);

	COMMAND.Output.EliminateLosersParams.processedPlayerCount = totalProcessedPlayerCount;
	COMMAND.Output.EliminateLosersParams.totalPlayerCountLeft = redisReply3->integer;

Failed:
	if (redisReply1)
		freeReplyObject(redisReply1);

	if (redisReply2)
		freeReplyObject(redisReply2);
	
	if (redisReply3)
		freeReplyObject(redisReply3);

	if (retval != ERROR_SUCCESSFUL)
		printf("\nError occured while matching players: %s %s", player1, player2);

	return retval;
}

