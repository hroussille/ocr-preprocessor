var preprocessor = require("./lib/ocr-preprocessor");

let options = { blur: 0 ,
  threshold: 255
};


preprocessor("./test.jpg" , "./result.jpg" , options , function(err , path) {
  if (err) {
    console.log("Error !");
  }
  else {
    console.log("Preprocessed Image saved at : " + path);
  }
});
