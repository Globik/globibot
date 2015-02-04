var flash = require('connect-flash')
var express = require('express');
var path=require('path');
var passport=require('passport');
var cookieParser=require('cookie-parser');
var bodyparser=require('body-parser');
var met=require('method-override');
//var bcrypt=require('bcrypt');
var session=require('express-session');
var SkinStore=require('connect-mongoskin');
var express = require('express');
var app = express();

var routes=require('./routes/index');
var database = require('./routes/database');

var LocalStrategy = require('passport-local').Strategy;
/***
var users = [
    { id:1, username: 'Bob', password: 'secret', email: 'bob@example.com' }
  
];
***/
/***

function findById(id, fn) {
  var idx = id - 1;
  if (users[idx]) {
    fn(null, users[idx]);
  } else {
    fn(new Error('User ' + id + ' does not exist'));
  }
}

function findByUsername(username, fn) {
  for (var i = 0, len = users.length; i < len; i++) {
    var user = users[i];
    if (user.username === username) {
      return fn(null, user);
    }
  }
  return fn(null, null);
}
***/

 var db=require('mongoskin').db("mongodb://localhost:27017/todo");




 
 //var db=require('mongoskin').db(process.env.MONGOHQ_URL,{w:1});

/***
passport.serializeUser(function(user, done) {
  done(null, user.id);
});

passport.deserializeUser(function(id, done) {
  findById(id, function (err, user) {
    done(err, user);
  });
});
***/

passport.serializeUser(function(user, done) {
  done(null, user._id);});

passport.deserializeUser(function(_id, done) {
db.collection('users').findById(_id,function(err,user){
if(err){return done(err);}
done(null,user);
});
});

/***
bcrypt.genSalt(10,function(err,salt){
bcrypt.hash('secret',salt,function(err,crypted){
 console.log('crypted: ' + crypted);


 bcrypt.compare('secret', crypted, function(err, res) {
      console.log('compared true: ' + res);});


db.collection('users').update({username:'Bob'},{$set:{password:crypted}},function(err,res){
if(err)throw err;console.log('Updated!');});
});});
***/


passport.use(new LocalStrategy(
  function(username, password, done) {
    
    process.nextTick(function () {
      
      db.collection('users').findOne({'username':username}, function(err, user) {
        if (err) { return done(err); }
        if (!user) { 
return done(null, false, { message: 'Unknown user ' + username }); }

/***
bcrypt.compare(password, user.password, function(err, res) {
console.log('Compare to secret: '+res+' password : '+password);
if(err){return done(err);
console.log('err');}

if(res == true) {console.log('User.password: '+user.password);
***/
/***
        if (user.password != password) { return done(null, false, { message: 'Invalid password' }); }
***/

/***
return done(null, user);} 
else{return done(null,false,{message:'Invalid password,heh Admin)'});}
});
***/
 if (user.password != password) { return done(null, false, { message: 'Invalid password' }); }
return done(null,user);

      });
    });
  }));

/***
var pass='$2a$10$bKcMJ76efk8ZBYyIJJcGAOXmuM6VZHdSPXSdlXqeUE9ojnE4uvGPC';
bcrypt.compare('secret',pass, function(err, res) {
console.log('Compare to BBBsecret: '+res);});
***/



/***

passport.use(new LocalStrategy(
  function(username, password, done) {
    
    process.nextTick(function () {
      
      findByUsername(username, function(err, user) {
        if (err) { return done(err); }
        if (!user) { 
return done(null, false, { message: 'Unknown user ' + username }); 


}
        if (user.password != password) { return done(null, false, { message: 'Invalid password' }); }
        return done(null, user);
      })
    });
  }
));
***/
 //var db=require('mongoskin').db("mongodb://localhost:27017/todo");
 /***
var db=require('mongoskin').db("mongodb://alik:123456@dogen.mongohq.com:10004/alikon-fantastic-database");
***/
 //var db=require('mongoskin').db(process.env.MONGOHQ_URL,{w:1});

app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

app.set('port', (process.env.PORT || 5000));

app.use(bodyparser.urlencoded({extended:true}));
app.use(bodyparser.json());
app.use(met());
app.use(cookieParser('secret','mysecret'));
app.use(session({cookie:{httpOnly:true,secure:false,maxAge:60*60*4000},secret:'somestring',resave:false,saveUninitialized:false,store:new SkinStore(db)}));
app.use(flash());
app.use(passport.initialize());
app.use(passport.session());
app.use(express.static(path.join(__dirname, 'public')));
 
  

  //var db=require('mongoskin').db(process.env.MONGOHQ_URL,{w:1});

app.use(function(req,res,next){
    req.db = db;
    next();
});

app.use(function(req,res,next){
res.locals.message=req.flash('message','OK Flash');
next();
});

app.use('/', routes);
app.use('/',database);

app.all('*', function(req, res){
  res.send(404);
})

/***
app.get('/', function(req, res) {
var drinks=[
{name:'Bloody Mary',drunk:3},
{name:'Alik',drunk:5},
{name:'Dima',drunk:10}
];

db.collection('tasks').find().toArray(function(err,result){
if(err)throw err;

  res.render('index', { drinks:drinks, title: 'Express',user:req.user,resul:result});
});});
***/


/***
app.get('/', function(request, response) {
 
  response.send("  Hello world and Globi!!!");
});
***/

app.listen(app.get('port'), function() {
  console.log("Node app is running at localhost:" + app.get('port'));
});

/***
git push heroku master
***/