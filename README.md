# ocr-preprocessor

This is a simple OCR preprocessor module for NodeJS.
It has been made to isolate and detect Building licences on a picture , then process the image to make it suited for OCR. The result is a black text on white background.

## Install

Install it like any node module , by running :

```sh
npm install --save ocr-preprocessor
```

Note : This module is for now only compatible with Linux. And OpenCV 2.X

## Usage

### Require the package 

```js
var preprocessor = require("ocr-preprocessor");
```

### Use it on the image you want 

```js
preprocessor("./test.jpg" , "./result.jpg" , options , function(err , path) {
  if (err) {
    console.log("Error !");
  }
  else {
    console.log("Preprocessed Image saved at : " + path);
  }
});
```

## Exports

This module export itself as a function 

This function accept 4 arguments : 

* input path   : path to the image to process
* output path : path to save the processed image
* options : options for the preprocessing
* callback  : callback function to execute when done.


### Options

* blur : blur value - default to 0
* threshold : threshold value - default to 255
* matrix : matrix-size used for thresholding - default to 3
* const : constant used for thresholding - default to 5
* revert : does the image need to be reverted - default to false
* isolate : does the biggest region of the imaged need to be isolated - default to false


## Asynchronous

This module is asynchronous. No work is done in the Node main loop which makes it suitable to be used on a big number of images at the same time.
