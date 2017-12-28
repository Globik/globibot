#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <node_api.h>
#include <string.h>
#include <assert.h>

#include "user_agent_parser.h"
#include "regexes.yaml.h"
#define nullptr ((void*)0)
static const char theText[]="Sascha geht ins Kino.";

napi_value bufferInfo(napi_env env, napi_callback_info info){
size_t argc=1;
napi_value args[1];
napi_status status;
//napi_valuetype valuetype;
bool valuetype;
status=napi_get_cb_info(env, info, &argc, args,NULL,NULL);
assert(status==napi_ok);
if(argc > 1){napi_throw_type_error(env,nullptr,"Wrong number of arguments!");
				 return NULL;
				}
status=napi_is_buffer(env,args[0], &valuetype);
assert(status==napi_ok);
if(valuetype == false){
napi_throw_type_error(env,nullptr,"Wrong type of argument. Expects a buffer!");
return NULL;
}

	napi_value theBuffer=args[0], ua_family;
	
	char* bufferData;
	napi_value obj;
	size_t bufferLength;
	status=napi_get_buffer_info(env,theBuffer,(void**)(&bufferData),&bufferLength);
	assert(status==napi_ok);
	printf("here: %s\n",bufferData);
	printf("here len: %zu\n",bufferLength);
	printf("sizeof(theText): %zu\n",sizeof(theText));
	//status=napi_get_boolean(env,!strcmp(bufferData,theText) && bufferLength==sizeof(theText),&returnValue);
	//assert(status==napi_ok);
struct user_agent_parser *ua_parser = user_agent_parser_create();
struct user_agent_info *ua_info = user_agent_info_create();
user_agent_parser_read_buffer(ua_parser, ___uap_core_regexes_yaml, ___uap_core_regexes_yaml_len);
	
if (user_agent_parser_parse_string(ua_parser, ua_info,bufferData)) {
	status=napi_create_string_utf8(env,ua_info->user_agent.family,NAPI_AUTO_LENGTH,&ua_family);
	assert(status==napi_ok);
	status=napi_create_object(env,&obj);
	assert(status==napi_ok);
	status=napi_set_named_property(env,obj,"ua_family",ua_family);//major,minor,patch
	assert(status==napi_ok);
}
	user_agent_parser_destroy(ua_parser);
	user_agent_info_destroy(ua_info);
	return obj;
}
/*
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
}*/
napi_value Init(napi_env env,napi_value exports){
napi_value new_exports;
	napi_status status=napi_create_function(env,"",NAPI_AUTO_LENGTH, bufferInfo,nullptr, &new_exports);
	assert(status==napi_ok);
	return new_exports;
}
NAPI_MODULE(addon,Init)