# ocr-preprocessor

This is an **asynchronous** OCR **preprocessor** module for NodeJS.

## Install

Use npm to install it by running :

```sh
npm install --save ocr-preprocessor
```

Note : This module is only compatible with **Linux** and **OpenCV 2.X**

## Usage

### Require the package 

```js
var preprocessor = require("ocr-preprocessor");
```

### Use it on the image you want to process

```js
let options = 
{ 
    blur: 3 , 
    threshold: 255 ,
    matrix: 7 ,
    constant: 5  
};
              
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

This module export itself as a single function 

This function accept 4 arguments : 

| Argument        |                 Description             |   Type    |
| -------------   |:---------------------------------------:|:---------:|
| Input Path      | Path to the source image                | String    |
| Output Path     | Path to the destination image           | String    |
| Options         | Options passed to preprocessing engine  | Object    |
| Callback        | Callback executed on return             | Function  |


### Options

|     Option    |           Description             |   Type    | Default |
| ------------- |:---------------------------------:|:---------:|:-------:|
| blur          |  Blur value                       | Number    |   0     |
| threshold     |  Threshold value                  | Number    |  255    |
| matrix        |  Threshold matrix size            | Number    |  3      |
| constant      |  Threshold constant               | Number    |  5      |
| revert        |  Revert the image                 | Boolean   |  false  |
| isolate       |  Find and isolate biggest area    | Boolean   |  false  |
| deskew        |  Run deskew algorithm             | Boolean   |  false  |
| matchCount    |  Deskew sensibility               | Number    |  100    |
| ratio         |  Line width threshold for deskew  | Number    |  2      |
| lineStep      |  Minimum line spacing for deskew  | Number    |  20     |

Note : ratio is used this way inside of the module :

```c++
image.width() / ratio;
```

Therefore , to select lined that are half the width of the image , ratio should be set to 2.

## Asynchronous

This module is asynchronous. All the work is done outside of the node main loop. It allows you to preprocess a big amount
of images at the same time.
