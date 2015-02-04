(function(){
var lastTime=0;
var vendors=['ms','moz','webkit','o'];
for(var x=0;x<vendors.length && !window.requestAnimationFrame;++x){
window.requestAnimationFrame=window[vendors[x]+'RequestAnimationFrame'];
window.cancelAnimationFrame=window[vendors[x]+'CancelAnimationFrame'] ||
window[vendors[x]+'CancelRequestAnimationFrame'];
}
if(!window.requestAnimationFrame)
window.requestAnimationFrame=function(callback,element){
var currTime=new Date().getTime();
var timeToCall=Math.max(0,16 - (currTime - lastTime));
var id=window.setTimeout(function(){callback(currTime+timeToCall);},timeToCall);
lastTime=currTime+timeToCall;
return id;
};
if(!window.cancelAnimationFrame)
window.cancelAnimationFrame=function(id){
clearTimeout(id);
};
}());

var show=document.getElementById('show33');
var cnv = document.getElementById('canv');
var c = cnv.getContext('2d');
c.fillStyle='rgb(0,0,0)';
c.fillRect(0,0,650,200);
var ww=cnv.width;
var hh=cnv.height;

show.checked=true;

var go;

var b=0;
var text='ANDROID';
var cnv2=document.createElement('canvas');
var c2=cnv2.getContext('2d');
 cnv2.width=190;
 cnv2.height=22;

var h1=cnv2.height;
var w =cnv2.width;

c2.font="bold 20pt Arial";
c2.fillText(text,3,20);

var imd=c2.getImageData(0,0,w,h1);

var ab=new Uint8Array(imd.data);

var tiles=[];
for(var y1=0;y1<h1;y1+=1){
for(var x1=0;x1<w;x1+=1){
ix=((y1*w+x1)*4)-1;

var pixel=ab[ix];
if(pixel & 255){
tiles.push({
 orx: (5*x1)-7, ory:5*y1+hh*.25,
 curx:(5*x1)-7, cury:5*y1+hh*.25,
 vx:0,vy:0,f:0});}
}}

requestAnimationFrame(render);
b=1;

var then=new Date()*0.001;
var tx=50;
var ty=75;

var velX=160;
var velY=160;

function render(){
if(b !=0){
requestAnimationFrame(render);
}

c.fillStyle='rgba(0,0,0,0.2)';
c.fillRect(0,0,650,200);
var now=new Date()*0.001;
var delta=(now-then);
then=now;

//tiles.forEach(function(it,i){
for(var i=0;i<tiles.length;i++){
var tile = tiles[i];

if(tile.f> 2.0){ 
tile.vx *= tile.f;
tile.vy *= tile.f;

tile.curx += tile.vx;
tile.cury += tile.vy;

 tile.f *= 0.2;
 if(tile.curx <= 0 || tile.curx >= 436) { tile.vx *= -1;}
 if(tile.cury <= 0 || tile.cury >= 200){tile.vy *= -1;}

}

 else if(tile.curx !=tile.orx || tile.cury !=tile.ory){
 var difx= (tile.orx-tile.curx)*0.06;
 var dify= (tile.ory-tile.cury)*0.06;
 if(Math.abs(difx) < 0.5){tile.curx = tile.orx;}
 else{tile.curx += difx;}
 if(Math.abs(dify) < 0.5){tile.cury = tile.ory;}
 else{tile.cury += dify;}
} 
 else {tile.f=0;}


c.save();
c.fillStyle='rgba(100,100,200,0.5)';
c.fillRect(tile.curx,tile.cury,4,4);
c.restore();
}
//);

bomb(tx,ty);
 if(tx <= 0) {tx=0;velX = - velX;}
 if(tx >= ww-10) { tx = ww-10; velX = - velX;}
 if(ty <=0) {ty=0;velY = - velY;}
 if(ty >= hh-10){ty=hh-10; velY = - velY;}
 tx+= delta * velX;
 ty+= delta * velY;
}

function bomb(x2,y2){
if(show.checked){
frei(x2,y2);
}
//explode(x2,y2);
}

function grob(event){
var touchobj=event.changedTouches[0];
posx=parseInt(touchobj.clientX)-cnv.getBoundingClientRect().left;
posy=parseInt(touchobj.clientY)-cnv.getBoundingClientRect().top;
explode(posx,posy);
event.preventDefault();
}

function handler(event){
if(event.preventManipulation)
event.preventManipulation();
posx=parseInt(event.clientX)-cnv.getBoundingClientRect().left;
posy=parseInt(event.clientY)-cnv.getBoundingClientRect().top;
explode(posx,posy);
}


function dropBomb(event){
posx= event.clientX-cnv.getBoundingClientRect().left;
//(cnv.offsetLeft- document.body.scrollLeft);
posy = event.clientY-cnv.getBoundingClientRect().top;
//(cnv.offsetTop - document.body.scrollTop);
explode(posx,posy);
}

function explode(x, y){
//tiles.forEach(function(it,i){
for(var i=0;i<tiles.length;i++){
var tile = tiles[i];
var xdiff =tile.curx-x;
var ydiff = tile.cury-y;
var dist = Math.sqrt(xdiff*xdiff + ydiff*ydiff);
var randRange = 220+(Math.random()*30);
var range = randRange-dist;
var force = 6*(range/randRange);
if(force > tile.f){
tile.f = force;
var radians = Math.atan2(ydiff, xdiff);
tile.vx = Math.cos(radians);
tile.vy = Math.sin(radians);
}
}
//);
}

 



function frei(x2,y2){
var pass= pass|| 8;
c.save();
c.globalAlpha=0.025;
c.globalCompositeOperation='lighter';
c.fillStyle='rgba(255,255,0,1)';
for(var k=1;k <= pass;k++)
for(var m=-1.5;m<3;m++){
for(var n=-1.5;n<3;n++){
c.fillRect(x2+n * k-3, y2+m * k-3, 6, 6);
}}

c.restore();
c.save();
c.fillStyle='white';
c.fillRect(x2-1.5,y2-1.5,3,3);
c.restore();
}

button.innerHTML='Stop';

function stop(el){
if(b) {
b=0;
el.innerHTML='Play';


}
else{
b=1;
 requestAnimationFrame(render);
el.innerHTML='Stop';
}
}
