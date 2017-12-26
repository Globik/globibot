var addon=require('./build/Release/ua');
addon(function(msg){console.log('Here it is : )',msg.toString());});