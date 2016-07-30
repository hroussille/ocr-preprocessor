{
  "targets": [
  {
    "target_name": "ocr-preprocessor",
      "sources": [ "src/main.cc" , "src/preprocessor.cc" , "src/async_preprocessor.cc" , "src/Params.cc"],
      "include_dirs": ["<!(node -e \"require('nan')\")" , "<!@(node utils/find-opencv.js --cflags)" ,"includes"],
      "libraries": [
        "<!@(node utils/find-opencv.js --libs)"
      ],
      "conditions": [
        [ "OS==\"linux\" or OS==\"freebsd\" or OS==\"openbsd\" or OS==\"solaris\" or OS==\"aix\"", {
            "cflags": [
              "<!@(node utils/find-opencv.js --cflags)",
              "-Wall"
            ]
        }]],
  }
  ]
}
