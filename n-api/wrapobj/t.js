'use strict';
const addon=require('./build/Release/binding');
const {measure}=require('../../measure.js');
const w=1000;
const obj=new addon.MyObject(9);
console.log(obj.value);
//let b=obj.multiply(10).value;
//console.log('b: ',b);
var boo=measure(boo);
boo(w);
function boo(n){
for(var i=0;i<n;i++){
obj.multiply(2).value;
}
}
console.log('val: ',obj.value);

function fuck(n){
return 9*n;
}
function doo(n){
for(var i=0;i<n;i++){
fuck(2);
}
}
var doo=measure(doo);
doo(w);