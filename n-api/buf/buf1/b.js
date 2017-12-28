var ad=require('./build/Release/b');
var {measure}=require("../../../measure.js");
var t=`Mozilla/5.0 (Linux; U; Android 4.3; MediaPad 7 Youth 2 Build/HuaweiMediaPad)
AppleWebKit/534.30 (KHTML, like Gecko) Version/4.0 Safari/534.30 OPR/23.0.2254.114329`;//\0`;//\u0000`;

//Sascha geht ins Kino.
var buf=Buffer.from(t+'\0');
//var buf=Buffer(t);
/*var a=ad(buf);
console.log('a: ',a);
console.log('ob?: ',ad);
*/
function boo(n){
//var g=addon(t);
	//console.log(g);
	for(var i=0;i<n;i++){
	//console.log(ad(buf));console.log('i: ',i);
		ad(buf)
	}
}
var boo=measure(boo);
boo(50);
//2420.806ms
// 61 ms if n=1
console.log('du');