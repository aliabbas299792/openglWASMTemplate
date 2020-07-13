source ~/emsdk/emsdk_env.sh >/dev/null 2>&1
#will compile all cpp files in current directory and subdirectories
emcc \
  $(find . -type f -iname \*.cpp) \
  -std=c++14 \
  -s WASM=1 \
  -s USE_GLFW=3 \
  -s FULL_ES3=1 \
  -s USE_WEBGL2=1 \
  -s MIN_WEBGL_VERSION=2 \
  -O3 \
  -o index.js \
  --preload-file assets \
  -Isrc
echo "Done";