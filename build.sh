#!/bin/bash

# create the public folder if it doesn't exist
mkdir -p public

# compile the c++ code
# -I./cpp tells the compiler to look inside the cpp folder for header files
emcc cpp/wasm_bridge.cpp -o public/calculator.js \
  -I./cpp \
  -s EXPORTED_FUNCTIONS='["_api_add", "_api_subtract", "_api_multiply", "_api_divide"]' \
  -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' \
  -s WASM=1

echo "Build complete! Check the /public folder."