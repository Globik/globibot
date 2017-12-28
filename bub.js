var {measure}=require('./measure.js');
function fact(n){
if(n<2){return 1;}
	return n*fact(n-1);
}
function suka(n){
	for(var i=0;i<500000;i++){}
//console.log(n.length);
		// 525.952ms
}
//var fact=measure(fact);
//fact(4);
var suka=measure(suka);
suka("Mama geht ins Kino.");