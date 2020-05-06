#include "FastApi.h"


FastApiErrorCode
ExecuteIsPlayerExists(HttpContext *context) {

	FastApiErrorCode	retval = ERROR_SUCCESSFUL;

	if (COMMAND.Inputs.Params.IsPlayerRegisteredParams.username == NULL) {
		retval = ERROR_MISSING_PARAMETER;
		COPY_ERROR_MESSAGE(CONTEXT, "username is missing");
		goto Failed;
	}
	
	retval = _isPlayerExists(CONTEXT, COMMAND.Inputs.Params.IsPlayerRegisteredParams.username, &COMMAND.Inputs.Params.IsPlayerRegisteredParams.isPlayerRegistered);

Failed:

	return retval;
}