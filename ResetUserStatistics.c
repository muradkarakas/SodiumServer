#include "FastApi.h"



FastApiErrorCode
ExecuteResetUserStatistics(
	HttpContext *context) {

	FastApiErrorCode	retval = _resetUserStatistics(CONTEXT, COMMANDKEY);

	return retval;
}

