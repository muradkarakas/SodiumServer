#include "FastApi.h"

#include <time.h>
#include <stdio.h>

FastApiErrorCode
ExecuteSetQuestionResult(
	HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;
	char	tmStr[30];	

	FastApi_GetLocalTime(tmStr, 30);

	IS_KEY_VALID(CONTEXT);

	IS_REDIS_CONTEXT_VALID(CONTEXT);

	//
	//  İŞLEMLER:
	//

	//
	//	COMMANDKEY içinde yer alan "username" geçerli bir oyuncu mu ?
	//
	IS_USER_REGISTERED(CONTEXT, COMMANDKEY);

	//
	//	Start Redis Transaction
	//
		COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "MULTI");
		IS_REDIS_REPLY_VALID(CONTEXT);		

	//
	//	*	Cevap doğru ise oyuncunun "totalTrueReplyCount"unu ARTTIR

		if (COMMAND.Inputs.Params.SetQuesionResultParams.isTrueSelected[0] == '1') {
			COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "HINCRBY %s totalTrueReplyCount 1",
				COMMANDKEY
			);
			IS_REDIS_REPLY_VALID(CONTEXT);
		}
	//
	//	*	Cevap yanlış ise oyuncunun "totalFalseReplyCount"unu ARTTIR
	//
		if (COMMAND.Inputs.Params.SetQuesionResultParams.isTrueSelected[0] == '0') {
			COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "HINCRBY %s totalFalseReplyCount 1",
				COMMANDKEY
			);
			IS_REDIS_REPLY_VALID(CONTEXT);
		}
		
	//
	//	*	Oyuncu tarafindan hiç bir seçenek geçerli süre içinde işaretlenmediyse oyuncunun "totalNoReplyCount"unu ARTTIR
	//
		if (COMMAND.Inputs.Params.SetQuesionResultParams.answerno[0] == '-' && COMMAND.Inputs.Params.SetQuesionResultParams.answerno[1] == '1') {
			COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "HINCRBY %s totalNoReplyCount 1",
				COMMANDKEY
			);
			IS_REDIS_REPLY_VALID(CONTEXT);
		}

	//
	//	*	Cevplanma süresi yani "replyDuration" değerini oyuncunun "totalReplyDuration" değerine EKLE
	//
		COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "HINCRBY %s totalReplyDuration %s",
			COMMANDKEY,
			COMMAND.Inputs.Params.SetQuesionResultParams.replyDuration
		);
		IS_REDIS_REPLY_VALID(CONTEXT);

	//
	//	*	Oyuncuların hangi sorulara verdikleri 
	//			Cevap seçeneği
	//			Cevap süresi
	//			
	//		Örnek set komutu:
	//			HMSET answers:mehmet q1 2 d1 4
	//		Açıklama:
	//			mehmet 1'i sorunun 2'nci seçeneğini 4 milisaniye içinde işaretlemiş
	//		farklı bir HSET'e ekle
	//
		COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "HMSET answers:%s q%s %s d%s %s",
			COMMANDKEY,														// hset key
			COMMAND.Inputs.Params.SetQuesionResultParams.questionno,	// field		q1
			COMMAND.Inputs.Params.SetQuesionResultParams.answerno,		//	 value		2
			COMMAND.Inputs.Params.SetQuesionResultParams.questionno,	// field		d1
			COMMAND.Inputs.Params.SetQuesionResultParams.replyDuration  //	 value		4
		);
		IS_REDIS_REPLY_VALID(CONTEXT);

	//
	//	*	Oyuncunun son işlem tarihini güncelle
	//	
		COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "HSET %s lastAccessTime %s",
			COMMANDKEY,
			tmStr
		);
		IS_REDIS_REPLY_VALID(CONTEXT);

	//
	//	Commit Redis Transaction if no error occured
	//
	COMMAND.redisReply = redisCommand(REDIS_CONTEXT, "EXEC");
	IS_REDIS_REPLY_VALID(CONTEXT);

Failed:

	return retval;
}