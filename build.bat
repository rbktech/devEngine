rd /q/s %CACHE%\devEngine\build

cmake -G "MinGW Makefiles" -B %CACHE%/devEngine/build -DCMAKE_INSTALL_PREFIX=%LIBRARY%/devEngine -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF