"use strict";
const pizd="/home/globik/globibot/uap-c/test"
const child_process_1 = require('child_process');
const t=`Mozilla/5.0 (Linux; U; Android 4.3; MediaPad 7 Youth 2 Build/HuaweiMediaPad) AppleWebKit/534.30 (KHTML, like Gecko) Version/4.0 Safari/534.30 OPR/23.0.2254.114329`;//\0`;//\u0000`;


class Encoder {
    static encode(value, path, options) {
        let buffer = Buffer.from ? Buffer.from(value) : new Buffer(value);
        options = Object.assign({}, this.options, options);
       
        return new Promise((resolve, reject) => {
            let process = child_process_1.spawn(pizd,[buffer]);
            process.stdout.on('data', (data) => {
                resolve(data);
            });
            process.stderr.on('data', (data) => {
                reject(data);
            });
            process.on('close', (exitstatus) => {
                if (exitstatus) {
                    reject(`Exit with status error - ${exitstatus}`);
                }
                else {
                    resolve();
                }
            });
        });
    }
}

exports.Encoder = Encoder;
