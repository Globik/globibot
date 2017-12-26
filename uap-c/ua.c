#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <node_api.h>
#include <string.h>
#include <assert.h>

#include "user_agent_parser.h"
#include "regexes.yaml.h"
// gcc -I.build -I./include -o ua ua.c -L. -luaparser -lyaml -lpcre
 #define nullptr ((void*)0)
napi_value RunCallback(napi_env env,const napi_callback_info info){
const char* st="Mozilla/5.0 (Linux; U; Android 4.3; MediaPad 7 Youth 2 Build/HuaweiMediaPad) AppleWebKit/534.30 (KHTML, like Gecko) Version/4.0 Safari/534.30 OPR/23.0.2254.114329";
struct user_agent_parser *ua_parser = user_agent_parser_create();
struct user_agent_info *ua_info = user_agent_info_create();
user_agent_parser_read_buffer(ua_parser, ___uap_core_regexes_yaml, ___uap_core_regexes_yaml_len);
const char *fuck;
if (user_agent_parser_parse_string(ua_parser, ua_info, st)) {
//printf("user_agent.family\t%s\n",  ua_info->user_agent.family);
	fuck=ua_info->user_agent.family;
	printf("from source code family: %s\n",fuck);

	//user_agent_parser_destroy(ua_parser);
	//user_agent_info_destroy(ua_info);

napi_status status;
	size_t argc=1;
	napi_value args[1];
	status=napi_get_cb_info(env,info,&argc,args,nullptr,nullptr);
	assert(status==napi_ok);
	napi_value cb=args[0];
	napi_value argv[1];
	status=napi_create_string_utf8(env,/*"hello world"*/ua_info->user_agent.family,NAPI_AUTO_LENGTH,argv);
	assert(status==napi_ok);
	napi_value global;
	status=napi_get_global(env,&global);
	assert(status==napi_ok);
	napi_value result;
	status=napi_call_function(env,global,cb,1,argv,&result);
	assert(status==napi_ok);
}
	user_agent_parser_destroy(ua_parser);
	user_agent_info_destroy(ua_info);
	return nullptr;
}

napi_value Init(napi_env env,napi_value exports){
napi_value new_exports;
	napi_status status=napi_create_function(env,"",NAPI_AUTO_LENGTH,RunCallback,nullptr,&new_exports);
	assert(status==napi_ok);
	return new_exports;
}
NAPI_MODULE(addon,Init)
	/*
	// node-gyp configure
	// node-gyp build
	var addon=require('bindings')('addon');
addon(function(msg){console.log(msg);});
*/
/*
int main(int argc, char **argv) {

	if (argc < 2) {
		printf("usage: %s <user agent string>\n", argv[0]);
		return -1;
	}
const char* st="Mozilla/5.0 (Linux; U; Android 4.3; MediaPad 7 Youth 2 Build/HuaweiMediaPad) AppleWebKit/534.30 (KHTML, like Gecko) Version/4.0 Safari/534.30 OPR/23.0.2254.114329";

struct user_agent_parser *ua_parser = user_agent_parser_create();
struct user_agent_info *ua_info = user_agent_info_create();

	user_agent_parser_read_buffer(ua_parser, ___uap_core_regexes_yaml, ___uap_core_regexes_yaml_len);

	if (user_agent_parser_parse_string(ua_parser, ua_info, st)) {

		printf("user_agent.family\t%s\n",  ua_info->user_agent.family);
		printf("user_agent.major\t%s\n",   ua_info->user_agent.major);
		printf("user_agent.minor\t%s\n",   ua_info->user_agent.minor);
		printf("user_agent.patch\t%s\n",   ua_info->user_agent.patch);

		printf("os.family\t%s\n",          ua_info->os.family);
		printf("os.major\t%s\n",           ua_info->os.major);
		printf("os.minor\t%s\n",           ua_info->os.minor);
		printf("os.patch\t%s\n",           ua_info->os.patch);
		printf("os.patchMinor\t%s\n",      ua_info->os.patch);

		printf("device.family\t%s\n",      ua_info->device.family);
		printf("device.brand\t%s\n",       ua_info->device.brand);
		printf("device.model\t%s\n",       ua_info->device.model);

	}else{
	printf("oh, fuck\n");
	}
	user_agent_parser_destroy(ua_parser);
	user_agent_info_destroy(ua_info);
	return 0;
}
*/
