//!!!! routes/index.js !!!!

var express=require('express');
var router=express.Router();
var passport=require('passport');

router.get('/', function(req, res) {
var db=req.db;
var drinks=[
{name:'Bloody Mary',drunk:3},
{name:'Alik',drunk:5},
{name:'Dima',drunk:10}
];
console.log('req.session: '+req.session.views);
console.log('req.session.cookie.originalMaxAge: '+req.session.cookie.originalMaxAge);
console.log('Expires :'+req.session.cookie.expires);
console.log('Secure :'+req.session.cookie.secure);
console.log('httpOnly :'+req.session.cookie.httpOnly);
console.log('Path : '+req.session.cookie.path);
console.log('req.session._id : '+req.session._id);
console.log('req.session.passport.user : '+req.session.passport.user);
//console.log('req.session.flush.info : '+req.session.flash.info);
//req.session.items="Warenhouse";
//console.log('req.session.items : '+req.session.items);
//console.log('req.cookies.number : '+req.cookies.number);
var msg='Hello!';
var cookie=req.cookies;
console.log('req.cooies: '+req.cookies.thisCookie);
if(cookie !=undefined && cookie.thisCookie !=undefined){
console.log('Saved: '+cookie.thisCookie)}
res.cookie('thisCookie','textAboutCookie',{maxAge:600000});
//req.flash('info','Info Coala');
db.collection('tasks').find().toArray(function(err,result){
if(err)throw err;

  res.render('index', { drinks:drinks, title: 'Express',user:req.user,resul:result,message:req.flash('message'),session:req.session.items});
});});

router.get('/catalog',function(req,res){
var db=req.db;
req.session.items=new Date();
req.cookies.number=2000;
//console.log('req.session.items : '+req.session.items);
//req.flash('kiu');
//console.log('req.cookies.number : '+req.cookies.number);
db.collection('catalog').find().toArray(function(err,result){
if(err)throw err;
res.render('catalog',{catalog:'catalog',user:req.user,result:result});
});});

router.get('/error',function(req,res){
res.render('error',{user:req.user});});

router.get('/catalog/:id', function(req, res) {
console.log('req.params.id :'+req.params.id);
var db=req.db;
    db.collection('catalog').findById(req.params.id, function(err, article){ 
if(err) return next(err);
if(article !== null){
console.log('article :'+article)
//console.log('article._id :'+article._id);

 res.render('article_view',{user:req.user,article:article});}
else {res.redirect('/error');}
});});

router.post('/saveArticle',function(req,res){
 var db=req.db;

db.collection('catalog').updateById(req.body._id,{$set:{article:req.body.article,content:req.body.cont,dascription:req.body.artBody,redaktiert:new Date()}},function(err,result){
if(err)throw err;
console.log('result :'+result);
console.log('visible :');

console.log('You have edeted this article id: '+req.body._id);
console.log('req.body.artBody :'+req.body.artBody);
res.send('OK - saved! '+req.body._id);
});
});

router.get('/account', ensureAuthenticated, function(req, res){

  res.render('account', { user: req.user,message:req.flash('message') });
});


router.get('/login', function(req, res){
  res.render('login', { user: req.user, message: req.flash('error') });
});

router.post('/login', 
  passport.authenticate('local', { failureRedirect: '/login', failureFlash: true }),
  function(req, res) {
req.flash('message','Hi there');
    res.redirect('/');
  });

router.get('/logout', function(req, res){
  req.logout();
  res.redirect('/');
});

function ensureAuthenticated(req, res, next) {
  if (req.isAuthenticated()) { return next(); }
  res.redirect('/login');
}

module.exports = router;

