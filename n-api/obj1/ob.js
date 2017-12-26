var addon=require('./build/Release/ob');
var ob=addon('hello');
var c=ob.msg;
console.log('Object: ',ob);