#include "FastApi.h"

#include "LiveQuiz.h"



void
CreatePostCommandResultAsJson(HttpContext *context) {

	switch (context->Command.type) {
		case REDIS_COMMAND_REGISTER_USER: {
			
			sprintf_s(
				JSON_RESULT(context),
				JSON_RESULT_SIZE,
				"{ \"command\" : \"registerUser\", \"" ERR_MESSAGE_KEY_NAME "\" : \"%s\", \"" PAYLOAD_KEY_NAME "\" : \"%s\", "
					"\"username\" : \"%s\" } ",
				
				GetResultAsString(context->err),
				context->errMessage,
				COMMANDKEY);
			break;
		}
		case REDIS_COMMAND_REGISTER_PLAYER: {
			sprintf_s(
				JSON_RESULT(context),
				JSON_RESULT_SIZE,
				"{ \"command\" : \"registerPlayer\", \"" ERR_MESSAGE_KEY_NAME "\" : \"%s\", \"" PAYLOAD_KEY_NAME "\" : \"%s\", "
					"\"username\" : \"%s\" } ",

				GetResultAsString(context->err),
				context->errMessage,
				context->Command.Params.p.registerPlayerParams.username);
			break;
		}
		case REDIS_COMMAND_REGISTER_OBSERVER: {
			sprintf_s(
				JSON_RESULT(context),
				JSON_RESULT_SIZE,
				"{ \"command\" : \"registerObserver\", \"" ERR_MESSAGE_KEY_NAME "\" : \"%s\", \"" PAYLOAD_KEY_NAME "\" : \"%s\", "
					"\"username\" : \"%s\" } ",

				GetResultAsString(context->err),
				context->errMessage,
				context->Command.Params.p.registerPlayerParams.username);
			break;
		}
		case REDIS_COMMAND_UNREGISTER_PLAYER: {
			sprintf_s(
				JSON_RESULT(context),
				JSON_RESULT_SIZE,
				"{ \"command\" : \"unregisterPlayer\", \"" ERR_MESSAGE_KEY_NAME "\" : \"%s\", \"" PAYLOAD_KEY_NAME "\" : \"%s\", "
					"\"username\" : \"%s\" } ",

				GetResultAsString(context->err),
				context->errMessage,
				context->Command.Params.p.registerPlayerParams.username);
			break;
		}
		case REDIS_COMMAND_DELETE_ALL_PLAYERS: {
			sprintf_s(
				JSON_RESULT(context),
				JSON_RESULT_SIZE,
				"{ \"command\" : \"deleteAllPlayers\", \"" ERR_MESSAGE_KEY_NAME "\" : \"%s\", \"" PAYLOAD_KEY_NAME "\" : \"%s\" } ",
				GetResultAsString(context->err),
				context->errMessage);
			break;
		}
		case REDIS_COMMAND_DELETE_ALL_OBSERVERS: {
			sprintf_s(
				JSON_RESULT(context),
				JSON_RESULT_SIZE,
				"{ \"command\" : \"deleteAllObservers\", \"" ERR_MESSAGE_KEY_NAME "\" : \"%s\", \"" PAYLOAD_KEY_NAME "\" : \"%s\" }",
				GetResultAsString(context->err),
				context->errMessage);
			break;
		}
		case REDIS_COMMAND_GET_TOTAL_PLAYER_COUNT: {
			sprintf_s(
				JSON_RESULT(context),
				JSON_RESULT_SIZE,
				"{ \"command\" : \"getTotalPlayerCount\", \"" ERR_MESSAGE_KEY_NAME "\" : \"%s\", \"" PAYLOAD_KEY_NAME "\" : \"%s\", "
				"\"totalPlayerCount\" : \"%I64u\" } ",

				GetResultAsString(context->err),
				context->errMessage,
				context->Command.Params.p.GetTotalPlayerCountParams.TotalPlayerCount
				);
			break;
		}
		case REDIS_COMMAND_IS_USER_REGISTERED: {
			sprintf_s(
				JSON_RESULT(context),
				JSON_RESULT_SIZE,
				"{ \"command\" : \"isUserRegistered\", \"" ERR_MESSAGE_KEY_NAME "\" : \"%s\", \"" PAYLOAD_KEY_NAME "\" : \"%s\", "
					"\"username\" : \"%s\", \"isExists\" : \"%s\" } ",

				GetResultAsString(context->err),
				context->errMessage,
				context->Command.Params.p.IsUserRegisteredParams.username,
				(context->Command.Params.p.IsUserRegisteredParams.isUserRegistered) ? "Registered" : "Unregistered");
			break;
		}
		case REDIS_COMMAND_GET_REGISTERED_USER: {
			sprintf_s(
				JSON_RESULT(context),
				JSON_RESULT_SIZE,
				"{ \"command\" : \"getUser\", \"" ERR_MESSAGE_KEY_NAME "\" : \"%s\", \"" PAYLOAD_KEY_NAME "\" : \"%s\", "
					"\"username\" : \"%s\", \"name\" : \"%s\", \"surname\" : \"%s\", \"role\" : \"%s\" } ",

				GetResultAsString(context->err),
				context->errMessage,

				COMMANDKEY,
				context->Command.Params.p.RegisterUserParams.name,
				context->Command.Params.p.RegisterUserParams.surname,
				context->Command.Params.p.RegisterUserParams.rolename);
			break;
		}
		case REDIS_COMMAND_SET_ROUND_INFO: {
			sprintf_s(
				JSON_RESULT(context),
				JSON_RESULT_SIZE,
				"{ \"command\" : \"setRoundInfo\", \"" ERR_MESSAGE_KEY_NAME "\" : \"%s\", \"" PAYLOAD_KEY_NAME "\" : \"%s\", "
					"\"roundId\" : \"%s\", \"questionCount\" : \"%s\", \"matchingStartTime\" : \"%s\", \"roundStartTime\" : \"%s\" } ",

				GetResultAsString(context->err),
				context->errMessage,
				COMMANDKEY,
				context->Command.Params.p.RoundInfoParams.questionCount,
				context->Command.Params.p.RoundInfoParams.matchingStartTime,
				context->Command.Params.p.RoundInfoParams.roundStartTime);
			break;
		}
		case REDIS_COMMAND_GET_ROUND_INFO: {
			sprintf_s(
				JSON_RESULT(context),
				JSON_RESULT_SIZE,
				"{ \"command\" : \"getRoundInfo\", \"" ERR_MESSAGE_KEY_NAME "\" : \"%s\", \"" PAYLOAD_KEY_NAME "\" : \"%s\", "
					"\"roundId\" : \"%s\", \"questionCount\" : \"%s\", \"matchingStartTime\" : \"%s\", \"roundStartTime\" : \"%s\" } ",

				GetResultAsString(context->err),
				context->errMessage,
				COMMANDKEY,
				context->Command.Params.p.RoundInfoParams.questionCount,
				context->Command.Params.p.RoundInfoParams.matchingStartTime,
				context->Command.Params.p.RoundInfoParams.roundStartTime);
			break;
		}
		case REDIS_COMMAND_GET_EVENT_INFO: {
			sprintf_s(
				JSON_RESULT(context),
				JSON_RESULT_SIZE,
				"{ \"command\" : \"getEventInfo\", \"" ERR_MESSAGE_KEY_NAME "\" : \"%s\", \"" PAYLOAD_KEY_NAME "\" : \"%s\", "
					"\"registerationStartTime\" : \"%s\", \"description\" : \"%s\", \"title\" : \"%s\" } ",

				GetResultAsString(context->err),
				context->errMessage,
				context->Command.Params.p.EventInfoParams.registerationStartTime,
				context->Command.Params.p.EventInfoParams.description,
				context->Command.Params.p.EventInfoParams.title);
			break;
		}
		case REDIS_COMMAND_SET_EVENT_INFO: {
			sprintf_s(
				JSON_RESULT(context),
				JSON_RESULT_SIZE,
				"{ \"command\" : \"setEventInfo\", \"" ERR_MESSAGE_KEY_NAME "\" : \"%s\", \"" PAYLOAD_KEY_NAME "\" : \"%s\", "
					"\"registerationStartTime\" : \"%s\", \"description\" : \"%s\", \"title\" : \"%s\" } ",

				GetResultAsString(context->err),
				context->errMessage,
				context->Command.Params.p.EventInfoParams.registerationStartTime,
				context->Command.Params.p.EventInfoParams.description,
				context->Command.Params.p.EventInfoParams.title);
			break;
		}
		case REDIS_COMMAND_SET_QUESTION_INFO: {
			sprintf_s(
				JSON_RESULT(context),
				JSON_RESULT_SIZE,
				"{ \"command\" : \"setQuestionInfo\", \"" ERR_MESSAGE_KEY_NAME "\" : \"%s\", \"" PAYLOAD_KEY_NAME "\" : \"%s\", "
					"\"text\" : \"%s\" } ",

				GetResultAsString(context->err),
				context->errMessage,
				context->Command.Params.p.QuestionInfoParams.text);
			break;
		}
		case REDIS_COMMAND_GET_QUESTION_INFO: {
			sprintf_s(
				JSON_RESULT(context),
				JSON_RESULT_SIZE,
				"{ \"command\" : \"getQuestionInfo\", \"" ERR_MESSAGE_KEY_NAME "\" : \"%s\", \"" PAYLOAD_KEY_NAME "\" : \"%s\", "
					" \"text\" : \"%s\", \"a1\" : \"%s\", \"a2\" : \"%s\", \"a3\" : \"%s\", \"a4\" : \"%s\", \"a5\" : \"%s\", \"trueOption\" : \"%s\", \"duration\" : \"%s\" } ",

				GetResultAsString(context->err),
				context->errMessage,

				context->Command.Params.p.QuestionInfoParams.text,
				context->Command.Params.p.QuestionInfoParams.a1,
				context->Command.Params.p.QuestionInfoParams.a2,
				context->Command.Params.p.QuestionInfoParams.a3,
				context->Command.Params.p.QuestionInfoParams.a4,
				context->Command.Params.p.QuestionInfoParams.a5,
				context->Command.Params.p.QuestionInfoParams.trueOption,
				context->Command.Params.p.QuestionInfoParams.duration);
			break;
		}
		case REDIS_COMMAND_RESET_OPPONENT_LIST: {
			sprintf_s(
				JSON_RESULT(context),
				JSON_RESULT_SIZE,
				"{ \"command\" : \"resetOpponentList\", \"" ERR_MESSAGE_KEY_NAME "\" : \"%s\", \"" PAYLOAD_KEY_NAME "\" : \"%s\" }",

				GetResultAsString(context->err),
				context->errMessage);
			break;
		}
	
	}

}
