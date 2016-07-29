var preprocessor = require("./build/Release/ByBat-preprocessor");

preprocessor.preprocess("./test.jpg" , "./result.jpg" , function(err , path) {
  if (err) {
    console.log("Error !");
  }
  else {
    console.log("Preprocessed Image saved at : " + path);
  }
});
