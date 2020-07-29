# OpenGL ES 3.0 WASM Template
The project uses GLFW3, GLM, OpenGL ES 3.0 and so consequently WebGL 2.0.

This is the example with textures, the main one is [here](https://github.com/aliabbas299792/openglWASMTemplate).

In the public/src/main.cpp file I learned about the lambda capturing method for the `emscripten_set_main_loop` function from https://github.com/timhutton/opengl-canvas-wasm.

To see this work simply do `node install` or `yarn` in the main directory, and then do `node index.js` and then go to `localhost:2000` to see the sample running.

![alt text](https://raw.githubusercontent.com/aliabbas299792/openglWASMTemplate/textures/screenshot.jpg)

Emscripten SDK and required libraries are downloaded via compile.sh, which in turn invokes the script(s) in the include directory, which setup the header files and stuff as required, to compile the source code.
