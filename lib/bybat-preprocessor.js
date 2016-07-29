let preprocessor = require('../build/Release/bybat-preprocessor.node');

let preprocess = function(input , output , options = {} , callback) {

  options.blur       = typeof options.blur       === 'undefined' ? 0     : options.blur;
  options.threshold  = typeof options.threshold  === 'undefined' ? 255   : options.threshold;
  options.matrix     = typeof options.matrix     === 'undefined' ? 3     : options.matrix;
  options.const      = typeof options.const      === 'undefined' ? 5     : options.const;
  options.revert     = typeof options.revert     === 'undefined' ? false : options.revert;
  options.isolate    = typeof options.isolate    === 'undefined' ? false : options.isolate;


  return preprocessor.preprocess(input , output , options.blur ,
                                                  options.threshold,
                                                  options.matrix,
                                                  options.const,
                                                  options.revert,
                                                  options.isolate,
                                                  callback);
}


module.exports = preprocess;
