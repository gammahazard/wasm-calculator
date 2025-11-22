#!/bin/bash


# this makes sure you are always testing the latest c++ code
echo "building project..."
./build.sh

# check if build worked
if [ $? -ne 0 ]; then
    echo "build failed, fix errors above first."
    exit 1
fi

# 2. start a python web server in the /public folder
# python handles the correct 'mime types' so the browser knows what a .wasm file is
echo "starting server at http://localhost:8000"
echo "press ctrl+c to stop"

# checking if python3 or python is available
if command -v python3 &>/dev/null; then
    python3 -m http.server 8000 -d public
else
    python -m http.server 8000 -d public
fi