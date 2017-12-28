var {measure}=require("../../measure.js");
var t="Mozilla/5.0 (Linux; U; Android 4.3; MediaPad 7 Youth 2 Build/HuaweiMediaPad) AppleWebKit/534.30 (KHTML, like Gecko) Version/4.0 Safari/534.30 OPR/23.0.2254.114329";
var addon=require('./build/Release/ob');
function boo(n){
//var g=addon(t);
	//console.log(g);
	for(var i=0;i<n;i++){
	console.log(addon(t));console.log('i: ',i);
	//	addon(t)
	}
}
var boo=measure(boo);
boo(50);
// 2345.805ms if n=50 with console.log
// 61.961ms if n=1 ~ 47.328ms if with no console.log in boo()
