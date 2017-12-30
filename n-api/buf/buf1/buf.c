#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <node_api.h>
#include <string.h>
#include <assert.h>
#include "user_agent_parser.h"
#include "regexes.yaml.h"
#define nullptr ((void*)0)
struct user_agent_parser *ua_parser=NULL;
struct user_agent_info *ua_info = NULL;
static const char theText[]="Sascha geht ins Kino.";

napi_value bInit(napi_env env, napi_callback_info info){
	int a;
napi_value world;
	ua_parser=user_agent_parser_create();
	ua_info=user_agent_info_create();
	a=user_agent_parser_read_buffer(ua_parser,___uap_core_regexes_yaml,___uap_core_regexes_yaml_len);
	printf("zustand: %d\n",a);
	const char* str="ok";
	size_t str_len=strlen(str);
	napi_status status;
	status=napi_create_string_utf8(env,str,str_len,&world);
	if(status !=napi_ok){return NULL;}
	return world;
}
napi_value bEnd(napi_env env, napi_callback_info info){
	user_agent_parser_destroy(ua_parser);
	ua_parser=NULL;
	user_agent_info_destroy(ua_info);
	ua_info=NULL;
napi_value mir;
	const char* str2="ok";
	size_t str_len2=strlen(str2);
	napi_status status;
	status=napi_create_string_utf8(env,str2,str_len2,&mir);
	if(status !=napi_ok){return NULL;}
	return mir;
}

napi_value bufferInfo(napi_env env, napi_callback_info info){
size_t argc=1;
napi_value args[1];
napi_status status;
//napi_valuetype valuetype;
//bool valuetype;
status=napi_get_cb_info(env, info, &argc, args,NULL,NULL);
	if(status !=napi_ok){return NULL;}
//assert(status==napi_ok);
//if(argc > 1){napi_throw_type_error(env,nullptr,"Wrong number of arguments!");
				// return NULL;
				//}
//status=napi_is_buffer(env,args[0], &valuetype);
	//if(status !=napi_ok){return status;}
//assert(status==napi_ok);
//if(valuetype == false){
//napi_throw_type_error(env,nullptr,"Wrong type of argument. Expects a buffer!");
//return NULL;
//}

	napi_value theBuffer=args[0], ua_family;
	
	const char* bufferData;
	napi_value obj;
	//size_t bufferLength;
	status=napi_get_buffer_info(env,theBuffer,(void**)(&bufferData),/*&bufferLength*/NULL);
	if(status !=napi_ok){return NULL;}
	//assert(status==napi_ok);
	//printf("here: %s\n",bufferData);
	//printf("here len: %zu\n",bufferLength);
	//printf("sizeof(theText): %zu\n",sizeof(theText));
	//status=napi_get_boolean(env,!strcmp(bufferData,theText) && bufferLength==sizeof(theText),&returnValue);
	//assert(status==napi_ok);
//struct user_agent_parser *ua_parser = user_agent_parser_create();
//struct user_agent_info *ua_info = user_agent_info_create();
//user_agent_parser_read_buffer(ua_parser, ___uap_core_regexes_yaml, ___uap_core_regexes_yaml_len);
	status=napi_create_object(env,&obj);
	if(status !=napi_ok){return NULL;}

if (user_agent_parser_parse_string(ua_parser, ua_info,bufferData)) {
	//status=
	napi_create_string_utf8(env,ua_info->user_agent.family,NAPI_AUTO_LENGTH,&ua_family);
	//if(status !=napi_ok){return NULL;}
	//assert(status==napi_ok);
	
	//assert(status==napi_ok);
	//status=napi_set_named_property(env,obj,"ua_family",ua_family);//major,minor,patch
	//if(status !=napi_ok){return NULL;}
	//assert(status==napi_ok);
}
	napi_property_descriptor descriptors[]={
		{"ua_family",NULL,0,0,0,ua_family,napi_default,0}
	};
	status=napi_define_properties(env,obj,sizeof(descriptors)/sizeof(descriptors[0]),descriptors);
	//assert(status==napi_ok);
	//user_agent_parser_destroy(ua_parser);
	//user_agent_info_destroy(ua_info);
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
//napi_value new_exports;
napi_status status;
//=napi_create_function(env,"",NAPI_AUTO_LENGTH, bufferInfo,nullptr, &new_exports);
//	assert(status==napi_ok);
napi_property_descriptor properties[]={
{"bufferInfo",0,bufferInfo,0,0,0,napi_default,0},
	{"bEnd",0,bEnd,0,0,0,napi_default,0},
	{"bInit",0,bInit,0,0,0,napi_default,0}
};	
	status=napi_define_properties(env,exports,sizeof(properties)/sizeof(properties[0]), properties);
	assert(status==napi_ok);
	return exports;
}
NAPI_MODULE(addon,Init)