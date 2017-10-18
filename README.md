*临时用于文档和代码同步*

---

# Project robocar

这是一个儿童教育机器人编程平台。



---

# purpose
儿童机器人编程

# 配件表

- 树莓派3b，用于执行小车控制逻辑程序
- 两个电机驱动板（每个驱动板能驱动两个电机，或一个驱动板带四路驱动），用于执行逻辑并驱动直流电机
- 四个直流电机与电机驱动板连接，执行行走指令
- 后面可能增加：
  - SLAM室内导航
  - 执行逻辑解释器




| 配件名             |  型号   |      |   价格 |                    |
| --------------- | :---: | ---- | ---: | ------------------ |
| raspberry pi 3b | pi 3b | x1   | ￥210 |                    |
| 电机驱动板           |       | x2   | ￥9x2 | 一个驱动板带两路驱动         |
| 移动平台            | 奥松4DW | x1   | ￥167 | 带车架、四个直流电机、6节5号电池盒 |







---

# 编程相关

## GPIO映射表

![](https://raw.github.com/hyhrob/robocar/deploy/images/RaspberryPiGPIOPins.png)


# TMP
## issue 1: shm_open() and crypt() link error
> yuanhui@yuanhui-desktop:~/robocar$ cmake -H. -Bbuild -G"Unix Makefiles"
> -- Lib baselib
> -- Lib fiblib
> -- Lib gpiorw
> -- Lib walkdriver
> -- App: robocar
> -- Demo: gpio_test
> -- Configuring done
> -- Generating done
> -- Build files have been written to: /home/yuanhui/robocar/build
> yuanhui@yuanhui-desktop:~/robocar$ cmake --build build --config release --target all
> [ 13%] Built target baselib
> [ 26%] Built target fiblib
> [ 33%] Linking CXX shared library ../../libgpiorw.so
> [ 40%] Built target gpiorw
> [ 46%] Linking CXX shared library ../../libwalkdriver.so
> [ 66%] Built target walkdriver
> [ 73%] Linking CXX executable ../../robocar
> //usr/local/lib/libwiringPi.so: undefined reference to `shm_open'
> //usr/local/lib/libwiringPi.so: undefined reference to `crypt'
> collect2: error: ld returned 1 exit status
> source/robocar/CMakeFiles/robocar.dir/build.make:123: recipe for target 'robocar' failed
> make[2]: *** [robocar] Error 1
> CMakeFiles/Makefile2:343: recipe for target 'source/robocar/CMakeFiles/robocar.dir/all' failed
> make[1]: *** [source/robocar/CMakeFiles/robocar.dir/all] Error 2
> Makefile:138: recipe for target 'all' failed
> make: *** [all] Error 2
> yuanhui@yuanhui-desktop:~/robocar$ 
>