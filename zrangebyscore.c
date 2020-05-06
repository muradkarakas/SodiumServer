#include "FastApi.h"

inline FastApiErrorCode
ExecuteZrangeByScore(HttpContext *context) {

	FastApiErrorCode retval = ERROR_SUCCESSFUL;
	context->Command.Params.p.ZrangeByScore.elements = NULL;

	IS_KEY_VALID(context);

	IS_REDIS_CONTEXT_VALID(context);

	context->Command.redisReply = redisCommand(REDISCONTEXT, "ZRANGEBYSCORE  %s %s %s WITHSCORES",
		COMMANDKEY,
		context->Command.Params.p.ZrangeByScore.minScore,
		context->Command.Params.p.ZrangeByScore.maxScore);

	IS_REDIS_REPLY_VALID(context);

	switch (context->Command.redisReply->type) {
		case REDIS_REPLY_ARRAY: {
			// TODO: alloca ile dinamik local değişken oluştur
			char str[1000] = { 0 };

			for (int i = 0; i < context->Command.redisReply->elements; i++) {
				// TODO: alloca ile dinamik local değişken oluştur
				char el[1000];
				sprintf_s(el, 1000, "{ \"value\" : \"%s\", \"score\": \"%s\" }", 
					context->Command.redisReply->element[i++]->str,
					context->Command.redisReply->element[i]->str);

				if (str[0] != '\0')
					strncat_s(str, 1000, ",", 1);
				
				strncat_s(str, 1000, el, 1000);
			}

			size_t size = strlen(str) + 2;
			context->Command.Params.p.ZrangeByScore.elements = malloc(size);
			if (context->Command.Params.p.ZrangeByScore.elements)
				strncpy_s(context->Command.Params.p.ZrangeByScore.elements, size, str, size);

			break;
		}
	}

Failed:

	return retval;
}
