#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <node_api.h>
#include <string.h>
#include <assert.h>

//#include "user_agent_parser.h"
//#include "regexes.yaml.h"
#if defined _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#define MAX_CANCEL_THREADS 6
#define nullptr ((void*)0)

typedef struct{
	int32_t _input;
	int32_t _output;
	napi_ref _callback;
	napi_async_work _request;
} carrier;
carrier the_carrier;
carrier async_carrier[MAX_CANCEL_THREADS];
// node-gyp configure && build // rebuild
void Execute(napi_env env,void* data){
#if defined _WIN32
	Sleep(1000);
	#else
	//sleep(1);
	#endif
	carrier* c=(carrier*)data;
	if(c !=&the_carrier){
	napi_throw_type_error(env,nullptr,"wrong data parameter to Execute");
		return;
	}
	c->_output=c->_input*2;
}

void Complete(napi_env env,napi_status status, void* data){
carrier* c=(carrier*)data;
	if(c !=&the_carrier){
	napi_throw_type_error(env,nullptr,"wrong data parameter to Complete");
		return;
	}
	if(status !=napi_ok){
	napi_throw_type_error(env,nullptr,"execute callback failed.");
		return;
	}
	napi_value argv[2];
	napi_get_null(env,&argv[0]);
	napi_create_int32(env,c->_output,&argv[1]);
	
	napi_value callback;
	napi_get_reference_value(env,c->_callback,&callback);
	napi_value global;
	napi_get_global(env,&global);
	napi_value result;
	napi_call_function(env,global,callback,2,argv,&result);
	napi_delete_reference(env,c->_callback);
	napi_delete_async_work(env,c->_request);
}

napi_value Test(napi_env env,napi_callback_info info){
size_t argc=3;
	napi_status status;
	napi_value argv[3];
	napi_value _this;
	napi_value resource_name;
	void* data;
	status=napi_get_cb_info(env,info,&argc,argv,&_this,&data);
	assert(status==napi_ok);
	if(argc >3){napi_throw_type_error(env,nullptr,"not enough arguments, expected 3?.");
				return nullptr;
				}
	napi_valuetype t;
	status=napi_typeof(env,argv[0],&t);
	assert(status==napi_ok);
	if(t !=napi_number){
	napi_throw_type_error(env,nullptr,"Wrong first argument, integer expected.");return nullptr;
	}
	
	status=napi_typeof(env,argv[1],&t);
	assert(status==napi_ok);
	if(t !=napi_object){
	napi_throw_type_error(env,nullptr, "wrong second argument, object expected.");
		return nullptr;
	}
		status=napi_typeof(env,argv[2],&t);
	assert(status==napi_ok);
	if(t !=napi_function){
		napi_throw_type_error(env,nullptr,"wrong third argument, function expected.");
		return nullptr;
	}	
	the_carrier._output=0;
	status=napi_get_value_int32(env,argv[0],&the_carrier._input);
	assert(status==napi_ok);
	
	
	status=napi_create_reference(env,argv[2],1,&the_carrier._callback);
	assert(status==napi_ok);
	status=napi_create_string_utf8(env,"TestResource",NAPI_AUTO_LENGTH,&resource_name);
	assert(status==napi_ok);
	status=napi_create_async_work(env,argv[1],resource_name,Execute,Complete,&the_carrier,&the_carrier._request);
	assert(status==napi_ok);
	status=napi_queue_async_work(env,the_carrier._request);
	assert(status==napi_ok);
	return nullptr;
	}


napi_value Init(napi_env env,napi_value exports){
	napi_status status;
napi_property_descriptor properties[]={
	{"Test",0,Test,0,0,0,napi_default,0}
};
status=napi_define_properties(env,exports,sizeof(properties)/sizeof(*properties),properties);
	assert(status==napi_ok);
return exports;
}
NAPI_MODULE(addon,Init)
/*
napi_value CreateObject(napi_env env,const napi_callback_info info){
//const char* st="Mozilla/5.0 (Linux; U; Android 4.3; MediaPad 7 Youth 2 Build/HuaweiMediaPad) AppleWebKit/534.30 (KHTML, like Gecko) Version/4.0 Safari/534.30 OPR/23.0.2254.114329";

	napi_status status;
	size_t argc=1;
	char sbuf[128];
	size_t bs=128,bres;
	napi_value args[1],ua_family,ua_major,ua_minor,ua_patch,os_family,os_major,os_minor, os_patch;
	napi_value device_family, device_brand, device_model;
	napi_value obj;
	napi_valuetype valuetype;
	
	status=napi_get_cb_info(env,info,&argc,args,nullptr,nullptr);
	assert(status==napi_ok);
	if(argc > 1){napi_throw_type_error(env,nullptr,"Wrong number of arguments!");return nullptr;}
	
	status=napi_typeof(env,args[0], &valuetype);
	assert(status==napi_ok);
	if(valuetype !=napi_string){
	napi_throw_type_error(env,nullptr,"Wrong type of argument. Expects a string!");return nullptr;
	}
	
	//napi_get_value_string_utf8(env,napi_value value,char*buf,size_t bufsize,size_t*result)
	status=napi_get_value_string_utf8(env,args[0],sbuf,bs,&bres);
	assert(status==napi_ok);
	printf("HERE must be a string from outside: %s\n",sbuf);
	struct user_agent_parser *ua_parser = user_agent_parser_create();
struct user_agent_info *ua_info = user_agent_info_create();
user_agent_parser_read_buffer(ua_parser, ___uap_core_regexes_yaml, ___uap_core_regexes_yaml_len);
	
if (user_agent_parser_parse_string(ua_parser, ua_info,sbuf)) {
	status=napi_create_string_utf8(env,ua_info->user_agent.family,NAPI_AUTO_LENGTH,&ua_family);
	assert(status==napi_ok);
	status=napi_create_string_utf8(env, ua_info->user_agent.major,NAPI_AUTO_LENGTH,&ua_major);
	assert(status==napi_ok);
	
		status=napi_create_string_utf8(env, ua_info->user_agent.minor,NAPI_AUTO_LENGTH,&ua_minor);
	assert(status==napi_ok);
		status=napi_create_string_utf8(env, ua_info->user_agent.patch,NAPI_AUTO_LENGTH,&ua_patch);
	assert(status==napi_ok);
		status=napi_create_string_utf8(env, ua_info->os.family,NAPI_AUTO_LENGTH,&os_family);
	assert(status==napi_ok);
		status=napi_create_string_utf8(env, ua_info->os.major,NAPI_AUTO_LENGTH,&os_major);
	assert(status==napi_ok);
		
		status=napi_create_string_utf8(env, ua_info->os.minor,NAPI_AUTO_LENGTH,&os_minor);
	assert(status==napi_ok);
		status=napi_create_string_utf8(env, ua_info->os.patch,NAPI_AUTO_LENGTH,&os_patch);
	assert(status==napi_ok);
		
		status=napi_create_string_utf8(env, ua_info->device.family,NAPI_AUTO_LENGTH,&device_family);
	assert(status==napi_ok);
		status=napi_create_string_utf8(env, ua_info->device.brand,NAPI_AUTO_LENGTH,&device_brand);
	assert(status==napi_ok);
		status=napi_create_string_utf8(env, ua_info->device.model,NAPI_AUTO_LENGTH,&device_model);
	assert(status==napi_ok);
		
	status=napi_create_object(env,&obj);
	assert(status==napi_ok);
	status=napi_set_named_property(env,obj,"ua_family",ua_family);//major,minor,patch
	assert(status==napi_ok);
	status=napi_set_named_property(env,obj,"ua_major", ua_major);
	assert(status==napi_ok);
		
		status=napi_set_named_property(env,obj,"ua_minor", ua_minor);
	assert(status==napi_ok);
		status=napi_set_named_property(env,obj,"ua_patch", ua_patch);
	assert(status==napi_ok);
		status=napi_set_named_property(env,obj,"os_family", os_family);
	assert(status==napi_ok);
		status=napi_set_named_property(env,obj,"os_major", os_major);
	assert(status==napi_ok);
	status=napi_set_named_property(env,obj,"os_minor", os_minor);
	assert(status==napi_ok);
		status=napi_set_named_property(env,obj,"os_patch", os_patch);
	assert(status==napi_ok);
		
		status=napi_set_named_property(env,obj,"device_family", device_family);
	assert(status==napi_ok);
		status=napi_set_named_property(env,obj,"device_brand", device_brand);
	assert(status==napi_ok);
		status=napi_set_named_property(env,obj,"device_model", device_model);
	assert(status==napi_ok);
	}
	user_agent_parser_destroy(ua_parser);
	user_agent_info_destroy(ua_info);
	return obj;
}
napi_value Init(napi_env env,napi_value exports){
napi_value new_exports;
	napi_status status=napi_create_function(env,"",NAPI_AUTO_LENGTH,CreateObject,nullptr,&new_exports);
	assert(status==napi_ok);
	return new_exports;
}
NAPI_MODULE(addon,Init)
*/
	/*
	var addon=require('addon');
	var ob1=addon('hello');
	console.log(obj1.msg)
	
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
	*/