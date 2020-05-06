#include "FastApi.h"


FastApiErrorCode
matchPlayers(
	HttpContext *context,
	char	*player1,
	char	*player2) {

	FastApiErrorCode retval = ERROR_SUCCESSFUL;

	//
	//	Starting new Redis Transaction
	//
	COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "MULTI");
	IS_REDIS_REPLY_VALID(CONTEXT);

	if (player1 && player2) {
		//
		// We are provided 2 players.
		//

		//
		//	Setting player1's opponent property		
		//
		COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "HMSET %s opponentUsername %s", player1, player2);
		IS_REDIS_REPLY_VALID(CONTEXT);
		
		//
		//	Setting player2's opponent property		
		//
		COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "HMSET %s opponentUsername %s", player2, player1);
		IS_REDIS_REPLY_VALID(CONTEXT);

		// setting player1's statistics
		_resetUserStatistics(CONTEXT, player1);

		// setting player2's statistics
		_resetUserStatistics(CONTEXT, player2);
	}
	else if (player1 && !player2) {
		//
		//	We have only one player
		//

		//
		//	Cleaning player1's opponent property	
		//
		COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "HDEL %s opponentUsername", player1);
		IS_REDIS_REPLY_VALID(CONTEXT);

		// setting player1's statistics
		_resetUserStatistics(CONTEXT, player1);
	}

	//
	//	Commit Redis Transaction if no error occured
	//
	COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "EXEC");
	IS_REDIS_REPLY_VALID(CONTEXT);

Failed:

	return retval;
}

FastApiErrorCode
ExecuteMatchPlayers(
	HttpContext *context) {

	int  totalProcessedPlayerCount = 0, totalMatchedPlayerCount = 0;
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
	COMMAND.Output.MatchPlayersParams.matchedPlayerCount = 0;
	COMMAND.Output.MatchPlayersParams.unMatchedPlayerCount = 0;

	//	Tüm oyuncu listesini çek
	//
	char cursor[10] = "";
	char cursorCommand[100] = "";
	GET_SERVER_TIME_FOR_LOGGER(lt);

	printf("\n///////////////////////////////////////////////////////////////////");
	printf("\n%s: Matching started...", lt);
	
	// Cleaning data structures
	/*SET_SERVER_TIME_FOR_LOGGER(lt);
	printf("\n\n%s: Preparing...", lt);
	retval = CleanPlayersOpponentDataStructures(CONTEXT);
	if (retval != ERROR_SUCCESSFUL)
		goto Failed;
		printf(" done.");*/

	//	fetching first bundle
	SET_SERVER_TIME_FOR_LOGGER(lt);
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
		for (; matchedPlayerCountInBundled < redisReply->element[1]->elements; ) {

			// matching
			if (player1 == NULL) {
				player1 = redisReply->element[1]->element[matchedPlayerCountInBundled]->str;
				matchedPlayerCountInBundled++;
			}
			else if (player2 == NULL) {
				player2 = redisReply->element[1]->element[matchedPlayerCountInBundled]->str;
				matchedPlayerCountInBundled++;
			}
			if (player1 && player2) {
				// matching players in a transaction
				SET_SERVER_TIME_FOR_LOGGER(lt);
				printf("\n%s:      %s vs %s", lt, player1, player2);
				retval = matchPlayers(CONTEXT, player1, player2);
				if (retval != ERROR_SUCCESSFUL)
					goto Failed;
				printf(" done.");
				player1 = player2 = NULL;
				totalMatchedPlayerCount += 2;
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
			freeReplyObject(redisReply);
			SET_SERVER_TIME_FOR_LOGGER(lt);
			printf("\n%s:    Fetching players...", lt);
			redisReply = redisCommand(REDIS_CONTEXT, cursorCommand);
			IS_LOCAL_REPLY_VALID(redisReply);
			printf(" done.");
		}
		else {
			// no more bundle left 

			if (player1) {
				if (player2) {
					// matching last players
					retval = matchPlayers(CONTEXT, player1, player2);
					if (retval != ERROR_SUCCESSFUL)
						goto Failed;
					SET_SERVER_TIME_FOR_LOGGER(lt);
					printf("\n%s:      %s vs %s", lt, player1, player2);
					player1 = player2 = NULL;
				}
				else {
					SET_SERVER_TIME_FOR_LOGGER(lt);
					printf("\n\n%s: Unmatched players:", lt);
					printf("   !!! \"%s\" has no oppenent !!!\n", player1);
					retval = matchPlayers(CONTEXT, player1, player2);
					if (retval != ERROR_SUCCESSFUL)
						goto Failed;
				}
			}

			freeReplyObject(redisReply);
			redisReply = NULL;
			break;
		}

	}

	SET_SERVER_TIME_FOR_LOGGER(lt);
	printf("\n%s: %d total players processed.", lt, totalProcessedPlayerCount);
	printf("\n%s: %d total players matched.", lt, totalMatchedPlayerCount);

	printf("\n\n%s: Matching ended", lt);
	printf("\n///////////////////////////////////////////////////////////////////\n");
	//
	//	Commit Redis Transaction if no error occured
	//
	//COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "EXEC");
	//IS_REDIS_REPLY_VALID(CONTEXT);

	COMMAND.Output.MatchPlayersParams.matchedPlayerCount = totalMatchedPlayerCount;
	COMMAND.Output.MatchPlayersParams.unMatchedPlayerCount = totalProcessedPlayerCount - totalMatchedPlayerCount;
	COMMAND.Output.MatchPlayersParams.processedPlayerCount = totalProcessedPlayerCount;
	//COMMAND.Output.MatchPlayersParams.unmatchedUsername = player1;
Failed:

	if (retval != ERROR_SUCCESSFUL)
		printf("\nError occured while matching players: %s %s", player1, player2);

	return retval;
}