
# Project robocar

This project is created for children programming.


# purpose
Children programming



## GPIO mapping

![](https://raw.github.com/hyhrob/robocar/deploy/images/RaspberryPiGPIOPins.png)


# About program

## Compilling
### Compile on Raspberry PI
> cmake -H. -Bbuild -G"Unix Makefiles"
> 
> cmake --build build --config release --target robocar

### Compile on Mac OS X with gcc
> cmake -H. -Bbuild -G"Unix Makefiles"
> 
> cmake --build build --config release --target robocar


### Compile on Mac OS X for iOS
> cmake -H. -Bbuild_xcode -G"Xcode" -DCMAKE_TOOLCHAIN_FILE="cmake/ios.toolchain.cmake" -DIOS_PLATFORM=SIMULATOR64
> 
> [Then go to build_xcode folder and open and compile this project with xcode]

### Windows OS + vs2017
> cmake -H. -Bbuild -G"Visual Studio 15 2017 Win64"
> 
> cmake --build build --config release --target robocar

