#include "FastApi.h"

FastApiErrorCode
ExecuteResetOpponentList(HttpContext *context) {

	return CleanPlayersOpponentDataStructures(CONTEXT);
}