const ua_agent="Mozilla/5.0 (Linux; U; Android 4.3; MediaPad 7 Youth 2 Build/HuaweiMediaPad) AppleWebKit/534.30 (KHTML, like Gecko) Version/4.0 Safari/534.30 OPR/23.0.2254.114329";

const addon=require('./build/Release/ob');
/*
try{
var ob=addon(ua_agent);
console.log('Object: ',ob);
}catch(e){console.log("Some error: ",e);}
*/
bob(ua_agent).then(resu=>{console.log('resu: ',resu)})
console.log('after obj');

bob(ua_agent).then(resu=>{console.log('resu: ',resu)})
console.log('after obj');
function bob(n){
return new Promise((res,rej)=>{
res(addon(n));
})
}
var ab=Buffer.from(ua_agent);
console.log('length: ', ab.length,'len: ',ua_agent.length);
console.log('ab: ',ab)