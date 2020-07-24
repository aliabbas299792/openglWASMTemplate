# OpenGL ES 3.0 WASM Template
The project uses GLFW3, OpenGL ES 3.0 and so consequently WebGL 2.0.

In the public/src/main.cpp file I learned about the lambda capturing method for the `emscripten_set_main_loop` function from https://github.com/timhutton/opengl-canvas-wasm.

To see this work simply do `node install` or `yarn` in the main directory, and then do `node index.js` and then go to `localhost:2000` to see the sample running.

![alt text](https://github.com/aliabbas299792/openglWASMTemplate/blob/master/screenshot.png?raw=true)
