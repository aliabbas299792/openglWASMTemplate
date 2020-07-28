emsdkPresence=$(ls | grep 'emsdk' | wc -l)

if [[ $emsdkPresence -eq 0 ]]
then
  echo "Setting up Emscripten..."
  git clone https://github.com/emscripten-core/emsdk.git >/dev/null 2>&1
  cd emsdk
  ./emsdk install latest >/dev/null 2>&1
  ./emsdk activate latest >/dev/null 2>&1
  source ./emsdk_env.sh >/dev/null 2>&1
  cd ..
fi

includeLibrariesPresence=$(ls ./include | grep 'RETRIEVED_FILES_DO_NOT_DELETE' | wc -l)

if [[ includeLibrariesPresence -eq 0 ]]
then
  cd include
  for script in *.sh
  do
    ./$script
  done
  touch "RETRIEVED_FILES_DO_NOT_DELETE"
  cd ..
  echo "Beginning compilation..."
fi

source ./emsdk/emsdk_env.sh >/dev/null 2>&1
#will compile all cpp files in current directory and subdirectories
emcc \
  $(find -name "*.cpp" -not \( -path "./include/*" -o -path "./emsdk/*" \) ) \
  -std=c++14 \
  -s WASM=1 \
  -s USE_GLFW=3 \
  -s FULL_ES3=1 \
  -s USE_WEBGL2=1 \
  -s MIN_WEBGL_VERSION=2 \
  -O3 \
  -o index.js \
  --preload-file assets \
  -Isrc \
  -Iinclude
echo "Done";