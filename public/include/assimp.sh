echo "Downloading Assimp..."
source ../emsdk/emsdk_env.sh >/dev/null 2>&1
mkdir temp_assimp
cd temp_assimp
wget https://github.com/assimp/assimp/archive/v5.0.1.tar.gz >/dev/null 2>&1
tar -zxvf *.tar.gz >/dev/null 2>&1
rm -rf *.tar.gz
cd *
mkdir build
#passing all those flags results in a smaller static library, so probably good for compile/link times
#from here https://github.com/assimp/assimp/blob/master/Build.md
#and here https://github.com/assimp/assimp/issues/1133
echo "Building Assimp...";
emcmake cmake -DEMSCRIPTEN=1 -DASSIMP_BUILD_TESTS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DBUILD_SHARED_LIBS=ON -DASSIMP_NO_EXPORT=1 -DCMAKE_C_FLAGS=-Wno-implicit-function-declaration -DCMAKE_CXX_FLAGS=-Wno-implicit-function-declaration -DCMAKE_BUILD_TYPE=Release -S . -B build >/dev/null 2>&1
cd build
#nproc gets the number of cores, and -j allows you to use all your cores to build, so you get faster build times
emmake make -j$(nproc) >/dev/null 2>&1
cp code/libassimp.a ../../../../libs
cp contrib/zlib/libzlib.a ../../../../libs
cp contrib/irrXML/libIrrXML.a ../../../../libs
cp include/assimp/config.h ../include/assimp
cd ..
mv include/assimp ../../
cd ../../
rm -rf temp_assimp
