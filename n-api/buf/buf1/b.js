// home/globik/globibot/n-api/buf/buf1/b.js
var ad=require('./build/Release/b');
var {measure}=require("../../../measure.js");
var t=`Mozilla/5.0 (Linux; U; Android 4.3; MediaPad 7 Youth 2 Build/HuaweiMediaPad)
AppleWebKit/534.30 (KHTML, like Gecko) Version/4.0 Safari/534.30 OPR/23.0.2254.114329`;//\0`;//\u0000`;
//function init(){
//Sascha geht ins Kino.
var buf=Buffer.from(t+'\0');
let m=ad.bInit();
console.log('bInit: ',m);
//let a=ad.bufferInfo(buf);
//console.log('obj: ',a)

var boo=measure(boo);

boo(1);
boo(5)

function boo(n){
	for(var i=0;i<n;i++){
		ad.bufferInfo(buf);
		//console.log('mi: ',mi);
	}
}
function boo1(n,buf){
return new Promise((res,rej)=>{
res(ad.bufferInfo(buf));
})
}
let dr=ad.bEnd();
console.log('bEnd: ',dr);
//var boo=measure(boo);
//boo(50);
//2420.806ms
// 61 ms if n=1
//33912.998ms if n=5000
console.log('du');
process.on('beforeExit',()=>{console.log("beforeExit")})
process.on('exit',(code)=>{console.log('exit: ',code)})