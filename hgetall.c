#include "FastApi.h"

inline FastApiErrorCode
ExecuteHgetall(HttpContext *context) {

	FastApiErrorCode retval = ERROR_SUCCESSFUL;
	
	IS_KEY_VALID(context);

	IS_REDIS_CONTEXT_VALID(context);

	context->Command.Params.p.HgetAllParams.allKeysAndValues = NULL;

	context->Command.redisReply = redisCommand(REDISCONTEXT, "HGETALL  %s", COMMANDKEY);

	IS_REDIS_REPLY_VALID(context);

	switch (context->Command.redisReply->type) {
		case REDIS_REPLY_ARRAY: {
			// TODO: alloca ile dinamik local değişken oluştur
			char str[1000] = { 0 };

			for (int i = 0; i < context->Command.redisReply->elements; i++) {
				// TODO: alloca ile dinamik local değişken oluştur
				char el[1000];
				sprintf_s(el, 1000, "\"%s\" : \"%s\"",
					context->Command.redisReply->element[i++]->str,
					context->Command.redisReply->element[i]->str);

				if (str[0] != '\0')
					strncat_s(str, 1000, ",", 1);

				strncat_s(str, 1000, el, 1000);
			}
			
			size_t size = strlen(str)+2;
			context->Command.Params.p.HgetAllParams.allKeysAndValues = malloc(size);
			if (context->Command.Params.p.HgetAllParams.allKeysAndValues)
				strncpy_s(context->Command.Params.p.HgetAllParams.allKeysAndValues, size, str, size);

			break;
		}

	}

Failed:

	return retval;
}
