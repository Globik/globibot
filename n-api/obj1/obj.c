#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <node_api.h>
#include <string.h>
#include <assert.h>
#define nullptr ((void*)0)
// node-gyp configure && build // rebuild
napi_value CreateObject(napi_env env,const napi_callback_info info){
napi_status status;
	size_t argc=1;
	char sbuf[128];
	size_t bs=128,bres;
	napi_value args[1],some_str,another_str;
	
	status=napi_create_string_utf8(env,"suzuki",NAPI_AUTO_LENGTH,&some_str);
	assert(status==napi_ok);
	status=napi_create_string_utf8(env,"Some another string",NAPI_AUTO_LENGTH,&another_str);
	assert(status==napi_ok);
	
	status=napi_get_cb_info(env,info,&argc,args,nullptr,nullptr);
	assert(status==napi_ok);
	//printf("here%s\n",args[1]);
	//napi_get_value_string_utf8(env,napi_value value,char*buf,size_t bufsize,size_t*result)
	status=napi_get_value_string_utf8(env,args[0],sbuf,bs,&bres);
	assert(status==napi_ok);
	printf("HERE must be a string from outside: %s\n",sbuf);
	napi_value obj;
	status=napi_create_object(env,&obj);
	assert(status==napi_ok);
	status=napi_set_named_property(env,obj,"msg",/*args[0]*/some_str);
	assert(status==napi_ok);
	status=napi_set_named_property(env,obj,"pidor",another_str);
	assert(status==napi_ok);
	return obj;
}
napi_value Init(napi_env env,napi_value exports){
napi_value new_exports;
	napi_status status=napi_create_function(env,"",NAPI_AUTO_LENGTH,CreateObject,nullptr,&new_exports);
	assert(status==napi_ok);
	return new_exports;
}
NAPI_MODULE(addon,Init)
	/*
	var addon=require('addon');
	var ob1=addon('hello');
	console.log(obj1.msg)
	*/