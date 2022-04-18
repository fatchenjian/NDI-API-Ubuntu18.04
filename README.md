# NDI-API-Ubuntu18.04
![logo](https://img.shields.io/badge/ubuntu18.04-build%20pass-green?logo=ubuntu) 

Communication with NDI Aurora Tracker using C++ on Ubuntu 18.04.

NDI官网提供了API(NDI-master)，但只提供了windows下的例程。PlusToolkit库提供一个C接口库ndicapi(https://github.com/PlusToolkit/ndicapi)。
这里主要是在Ubuntu18.04 环境下对C接口的API进行配置和测试。

## 安装Toolbox
```bash
sudo chmod +x ToolBox 5.002.022 for Linux.sh
sh ./ToolBox 5.002.022 for Linux.sh
```
按照步骤安装。

Linux版本不需要安装USB driver，给USB权限后可直接运行桌面的NDI Track等软件。
```bash
sudo chmod 777 /dev/ttyUSBx
```
注：x是Aurora SIU的USB序号
## 安装依赖
```bash
sudo apt-get install build-essential dpkg-dev flex bison autotools-dev automake liborc-dev autopoint libtool gtk-doc-tools
sudo apt-get install libxv-dev libasound2-dev libtheora-dev libogg-dev libvorbis-dev
sudo apt-get install libbz2-dev libv4l-dev libvpx-dev libjack-jackd2-dev libsoup2.4-dev libpulse-dev
sudo apt-get install faad libfaad-dev libfaac-dev
sudo apt-get install libx264-dev libmad0-dev
sudo apt-get install yasm
sudo apt-get install libssl-dev
```

## 安装gstreamer1.16.2

```bash
cd gstreamer-1.16.2 && ./configure && make && sudo make install
```

## 安装automake1.16
```bash
cd automake-1.16 && ./configure && make && sudo make install
```
安装automake的主要目的是为了防止出现以下问题
```bash
missing: line 81: aclocal-1.16: command not found
```
## 安装gst-plugins-base-1.16.1
```bash
cd gst-plugins-base-1.16.1 && ./configure && make && sudo make install
```
## 编译ndicapi-master
```bash
mkdir build
cd build && cmake.. && make && sudo make install
```
## 编译NDI-master
```bash
make
```
## 测试
编译
```bash
cd nditest
mkdir build
cd build && cmake .. && make
```
注意需要修改CMakeLists.txt中的NDI-master的绝对路径
```bash
set(ROOT_FILE <NDI-master 路径>)
```
运行
```bash
./NDITracking /dev/ttyUSBx
```
