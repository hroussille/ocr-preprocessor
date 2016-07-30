let preprocessor = require('../build/Release/ocr-preprocessor.node');

let preprocess = function(input , output , options = {} , callback) {

  options.blur       = typeof options.blur       === 'undefined' ? 0     : options.blur;
  options.threshold  = typeof options.threshold  === 'undefined' ? 255   : options.threshold;
  options.matrix     = typeof options.matrix     === 'undefined' ? 3     : options.matrix;
  options.const      = typeof options.const      === 'undefined' ? 5     : options.const;
  options.revert     = typeof options.revert     === 'undefined' ? false : options.revert;
  options.isolate    = typeof options.isolate    === 'undefined' ? false : options.isolate;
  options.deskew     = typeof options.deskew     === 'undefined' ? false : options.deskew;
  options.matchCount = typeof options.matchCount === 'undefined' ? 100   : options.matchCount;
  options.ratio      = typeof options.ratio      === 'undefined' ? 2     : options.ratio;
  options.lineStep   = typeof options.lineStep   === 'undefined' ? 20    : options.lineStep;


  return preprocessor.preprocess(input , output , options.blur ,
                                                  options.threshold,
                                                  options.matrix,
                                                  options.const,
                                                  options.revert,
                                                  options.isolate,
                                                  options.deskew,
                                                  options.matchCount,
                                                  options.ratio,
                                                  options.lineStep,
                                                  callback);
}


module.exports = preprocess;
