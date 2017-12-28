var ad=require('./build/Release/b');

var t="Sascha geht ins Kino.\u0000";//18 21 22?
var t1="Sascha geht ins Kino.";
//Sascha geht ins Kino.
//var buf=Buffer.from(t);
var buf=Buffer(t);
var a=ad.bufferInfo(buf);
console.log('a: ',a,t.length);
console.log('ob?: ',ad);