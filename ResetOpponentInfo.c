#include "FastApi.h"

FastApiErrorCode
ExecuteResetOpponentInfo(HttpContext *context) {

	FastApiErrorCode	retval = _resetOpponentInfo(CONTEXT, COMMANDKEY);

	return retval;

}