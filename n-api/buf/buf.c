#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <node_api.h>
#include <string.h>
#include <assert.h>

static const char theText[]="Sascha geht ins Kino.";
napi_value bufferInfo(napi_env env, napi_callback_info info){
size_t argc=1;
napi_value args[1];
napi_status status;
status=napi_get_cb_info(env, info, &argc, args,NULL,NULL);
	assert(status==napi_ok);
	napi_value theBuffer=args[0];
	char* bufferData;
	napi_value returnValue;
	size_t bufferLength;
	status=napi_get_buffer_info(env,theBuffer,(void**)(&bufferData),&bufferLength);
	assert(status==napi_ok);
	printf("here: %s\n",bufferData);
	printf("here len: %zu\n",bufferLength);
	printf("sizeof(theText): %zu\n",sizeof(theText));
	status=napi_get_boolean(env,!strcmp(bufferData,theText) && bufferLength==sizeof(theText),&returnValue);
	assert(status==napi_ok);
	return returnValue;
}
napi_value Init(napi_env env,napi_value exports){
napi_value theValue;
napi_status status;
	status=napi_create_string_utf8(env,theText,sizeof(theText),&theValue);
	assert(status==napi_ok);
	status=napi_set_named_property(env,exports,"theText",theValue);
	assert(status==napi_ok);
	napi_property_descriptor methods[]={
		{"bufferInfo",0,bufferInfo,0,0,0,napi_default,0}
	};
	//{"Test",0,Test,0,0,0,napi_default,0}
	status=napi_define_properties(env,exports,sizeof(methods)/sizeof(methods[0]),methods);
	assert(status==napi_ok);
	return exports;
}
NAPI_MODULE(addon,Init)