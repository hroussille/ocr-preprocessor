# bybat-preprocessor

This is a simple OCR preprocessor module for NodeJS.
It has been made to isolate and detect Building licences on a picture , then process the image to make it suited for OCR. The result is a black text on white background.

## Install

Install it like any node module , by running :

```sh
npm install --save bybat-preprocessor
```

Note : This module is for now only compatible with Linux. And OpenCV 2.X

## Usage

### Require the package 

```js
var preprocessor = require("bybat-preprocessor");
```

### Use it on the image you want 

```js
preprocessor.preprocess("./test.jpg" , "./result.jpg" , function(err , path) {
  if (err) {
    console.log("Error !");
  }
  else {
    console.log("Preprocessed Image saved at : " + path);
  }
});
```

## Exports

This module export a single function : preprocess

This function accept 3 arguments : 

* input path   : path to the image to process
* output path : path to save the processed image
* callback  : callback function to execute when done.

## Asynchronous

This module is asynchronous. No work is done in the Node main loop which makes it suitable to be used on a big number of images at the same time.
