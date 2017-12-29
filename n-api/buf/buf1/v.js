const uap=require('uaparser-js');
const {measure}=require('../../../measure.js');
const parser=uap();
const t="Mozilla/5.0 (Linux; U; Android 4.3; MediaPad 7 Youth 2 Build/HuaweiMediaPad) AppleWebKit/534.30 (KHTML, like Gecko) Version/4.0 Safari/534.30 OPR/23.0.2254.114329";
//let result=parser.parse(t);
//console.log('result: ',result.toString());
function boo(n){
for(var i=0;i<n;i++){
console.log(parser.parse(t).toString());console.log('i: ',i);
	//parser.parse(t);
}
}
var boo=measure(boo);
boo(1);
boo(1);
boo(1);
// 91.131ms if n=1 with console.log
// 70.539ms if n=1 with no console.log
//310.577ms if n=50 with console
//2345.805ms