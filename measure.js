function measure(target){
let is_call=false;
	return new Proxy(target,{
		apply:(target,thisArg,args)=>{
			if(!target.name){throw 'The function must have a name'}
			if(!is_call){
			console.time(target.name);
				is_call=true;
				const result=Reflect.apply(target,thisArg,args);
				is_call=false;
				console.timeEnd(target.name);
				return result;
			}else{return Reflect.apply(target,thisArg,args);}}});
}
module.exports={measure}