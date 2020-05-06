// JavaScript source code

function _getCallback(_userCallback, httpStatus, data, request_time, _userCallbackParameters) {
    
    var jsonRaw = null;

    if (data != null)
        jsonRaw = eval(data);

    // preparing callback data from server as an object instance to pass user callback function
    var json = {
        "key": (jsonRaw) ? jsonRaw.key : null,
        "value": (jsonRaw) ? jsonRaw.value : null,
        "httpStatus": httpStatus,
        "request_time": request_time
    };

    // calling user callback
    _userCallback(json, _userCallbackParameters);
}

function _get(key, _userCallback, _userCallbackParameters) {

    var lUrl = '/FastAPI/Public?c=get&key=' + key;

    $.ajax({
        type: 'GET',
        url: lUrl,
        dataType: 'json',
        beforeSend: function (request, settings) {
            start_time = new Date().getTime();
        },
        success: function (data) {
            let request_time = new Date().getTime() - start_time;
            _getCallback(_userCallback, "success", data, request_time, _userCallbackParameters);
        },
        error: function (jqXHR, exception) {

            var httpStatus = '';
            if (jqXHR.status === 0) {
                httpStatus = 'Not connect.\n Verify Network.';
            } else if (jqXHR.status == 404) {
                httpStatus = 'Requested page not found. [404]';
            } else if (jqXHR.status == 500) {
                httpStatus = 'Internal Server Error [500].';
            } else if (exception === 'parsererror') {
                httpStatus = 'Requested JSON parse failed.';
            } else if (exception === 'timeout') {
                httpStatus = 'Time out error.';
            } else if (exception === 'abort') {
                httpStatus = 'Ajax request aborted.';
            } else {
                httpStatus = 'Uncaught Error.\n' + jqXHR.responseText;
            }

            let request_time = new Date().getTime() - start_time;
            _getCallback(_userCallback, httpStatus, null, request_time, _userCallbackParameters);
        }
    });
}

function _setCallback(_userCallback, httpStatus, data, request_time, _userCallbackParameters) {

    var jsonRaw = null;

    if (data != null)
        jsonRaw = eval(data);

    // preparing callback data from server as an object instance to pass user callback function
    var json = {
        "key": (jsonRaw) ? jsonRaw.key : null,
        "value": (jsonRaw) ? jsonRaw.value : null,
        "httpStatus": httpStatus,
        "request_time": request_time
    };

    //alert(JSON.stringify(json));

    // calling user callback
    _userCallback(json, _userCallbackParameters);
}

function _set(key, value, _userCallback, _userCallbackParameters) {

    var lUrl = '/FastAPI/Public?c=set&key=' + key + '&value=' + value;

    $.ajax({
        type: 'GET',
        url: lUrl,
        dataType: 'json',
        beforeSend: function (request, settings) {
            start_time = new Date().getTime();
        },
        success: function (data) {
            let request_time = new Date().getTime() - start_time;
            _setCallback(_userCallback, "success", data, request_time, _userCallbackParameters);
        },
        error: function (jqXHR, exception) {

            var httpStatus = '';
            if (jqXHR.status === 0) {
                httpStatus = 'Not connect.\n Verify Network.';
            } else if (jqXHR.status == 404) {
                httpStatus = 'Requested page not found. [404]';
            } else if (jqXHR.status == 500) {
                httpStatus = 'Internal Server Error [500].';
            } else if (exception === 'parsererror') {
                httpStatus = 'Requested JSON parse failed.';
            } else if (exception === 'timeout') {
                httpStatus = 'Time out error.';
            } else if (exception === 'abort') {
                httpStatus = 'Ajax request aborted.';
            } else {
                httpStatus = 'Uncaught Error.\n' + jqXHR.responseText;
            }

            let request_time = new Date().getTime() - start_time;
            _setCallback(_userCallback, httpStatus, null, request_time, _userCallbackParameters);
        }
    });
}







