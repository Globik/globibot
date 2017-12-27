const ua_agent="Mozilla/5.0 (Linux; U; Android 4.3; MediaPad 7 Youth 2 Build/HuaweiMediaPad) AppleWebKit/534.30 (KHTML, like Gecko) Version/4.0 Safari/534.30 OPR/23.0.2254.114329";

const addon=require('./build/Release/ob');
addon.Test(5,{type:'start'},function(err,val){console.log('error: ',err);console.log('value: ',val);})