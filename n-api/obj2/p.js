"use strict";
const child_process_1 = require('child_process');

class Encoder {
    static encode(value, path, options) {
        let buffer = Buffer.from ? Buffer.from(value) : new Buffer(value);
        options = Object.assign({}, this.options, options);
        let qrencode_args = [
            '-s', options.dot_size,
            '-m', options.margin,
            '-l', options.level,
            '-v', options.version,
            '-t', options.type,
            '-o', path || '-'
        ];
        qrencode_args[qrencode_args.length] = '--foreground=' + options.foreground_color.replace('#', '');
        qrencode_args[qrencode_args.length] = '--background=' + options.background_color.replace('#', '');
        if (options.case_sensitive) {
            qrencode_args[qrencode_args.length] = '-i';
        }
        qrencode_args[qrencode_args.length] = buffer;
        return new Promise((resolve, reject) => {
            let process = child_process_1.spawn('test', qrencode_args);
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
