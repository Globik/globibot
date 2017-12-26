#include <node_api.h>
//#include <string.h>
#include <assert.h>
#define nullptr ((void*)0)

napi_value CreateObject(napi_env env,const napi_callback_info info){
napi_status status;
	size_t argc=1;
	napi_value args[1];
	status=napi_get_cb_info(env,info,&argc,args,nullptr,nullptr);
	assert(status==napi_ok);
	napi_value obj;
	status=napi_create_object(env,&obj);
	assert(status==napi_ok);
	status=napi_set_named_property(env,obj,"msg",args[0]);
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