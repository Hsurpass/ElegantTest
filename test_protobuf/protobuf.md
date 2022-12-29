http://www.52im.net/thread-323-1-1.html

https://www.jianshu.com/p/a24c88c0526a

https://www.jianshu.com/p/b33ca81b19b5

http://www.cppblog.com/sunicdavy/archive/2014/12/16/209189.html    // pb language service

https://marketplace.visualstudio.com/items?itemName=mreu.ProtobufLanguageService	//vs插件

https://blog.csdn.net/majianfei1023/article/details/45371743

https://cloud.tencent.com/developer/article/1056432

https://cloud.tencent.com/developer/article/1602549

https://blog.csdn.net/liangjisheng/article/details/84646949

https://blog.csdn.net/liangjisheng/article/details/84646949

https://www.freesion.com/article/8599353804/

https://blog.csdn.net/huakai16/article/details/79583150

https://blog.csdn.net/liangjisheng/article/details/84646949

https://www.cnblogs.com/shine-lee/p/10741786.html

http://doc.okbase.net/doclist/archive/264711.html#%E4%BA%8C%E8%BF%9B%E5%88%B6%E6%96%87%E4%BB%B6%E8%A7%A3%E6%9E%90

https://blog.51cto.com/u_9291927/2331980

https://zhuanlan.zhihu.com/p/60608963

https://blog.csdn.net/sanshengshui/article/details/82950531

https://www.cnblogs.com/tohxyblog/p/8974763.html

https://blog.csdn.net/qq_22660775/article/details/89163881

https://www.cntofu.com/book/116/reference/java/oneof.md

https://www.kaifaxueyuan.com/basic/protobuf3/oneof.html

https://wenfh2020.com/2020/10/28/protobuf-convert-json/

https://www.coder.work/article/121306

https://wenku.baidu.com/view/3c3aa22eaeaad1f347933faf.html



pb/json转换

https://zhuanlan.zhihu.com/p/442458452

## protobuf编译选项介绍


------------------------------------------------

| CMAKE_BUILD_TYPE               | 编译模式(Debug[调试模式 ]\|Release[发布模式]) |
| ------------------------------ | --------------------------------------------- |
| CMAKE_INSTALL_PREFIX           | 编译后安装路径 可以使用相对路径               |
| **protobuf_BUILD_SHARED_LIBS** | **是否编译为动态库(OFF\|ON)**                 |
| protobuf_WITH_ZLIB             | 是否使用ZLIB库((OFF\|ON  建议设置为OFF)       |
| protobuf_BUILD_TESTS           | 是否编译测试工程(OFF\|ON 建议设置为OFF)       |



## **windows安装protobuf**

**打开`Developer Command Prompt for vs2019`**

```bash
cd protobuf
cd cmake
mkdir buildvs2019 & cd buildvs2019
```

```bash
mkdir release & cd release
cmake -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../../../../installvs2019/release ../..
```

```bash
mkdir debug & cd debug
cmake -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=../../../../installvs2019/debug ../..
```

```bash
C:\Path\to\protobuf\cmake\build> mkdir solution & cd solution
cmake -G "Visual Studio 12 2013" -DCMAKE_INSTALL_PREFIX=../../../../installvs2019 ../..
cmake -G "Visual Studio 16 2019" -DCMAKE_INSTALL_PREFIX=../../../../installvs2019 ../..
```

```
nmake
nmake install
```

-----------------------------------------

1. **打开`Developer Command Prompt for vs2019`, 以protobuf3.16为例，其他版本查看文档**

   **https://github.com/protocolbuffers/protobuf/blob/main/cmake/README.md**

   **https://github.com/protocolbuffers/protobuf/blob/v3.16.0/src/README.md**

2. **构建 build**

   ```bash
   cd .../protobuf-3.16.0/cmake
   cmake -B ../../buildvs2019 -DCMAKE_INSTALL_PREFIX=../../installvs2019 -G "Visual Studio 16 2019"
   cmake -B ../../buildvs2019 -DCMAKE_INSTALL_PREFIX=../../installvs2019 -G "Visual Studio 16 2019" -Dprotobuf_BUILD_SHARED_LIBS=ON -Dprotobuf_WITH_ZLIB=ON -Dprotobuf_BUILD_TESTS=ON
   ```

3. **编译 compile**

   ```bash
   cmake --build ../../buildvs2019 --config release
   cmake --build ../../buildvs2019 --config debug
   ```

   

4. **安装 install**

   ```bash
   cmake --install ../../buildvs2019 --config release
   cmake --install ../../buildvs2019 --config debug
   ```

5. **配置环境变量**

   **配置完环境变量需要重启**

```bash
g++ addressbook.pb.cc main.cpp `pkg-config --cflags --libs protobuf` -std=c++11
```



## **linux安装protobuf**

```bash
sudo apt-get install autoconf automake libtool curl make g++ unzip
```

```bash
./configure # 默认安装在 /usr/local 目录下。/usr/local/include /usr/local/lib /usr/local/bin
	可以指定安装路径：./configure --prefix=/usr
 make
 make check
 sudo make install
 sudo ldconfig # refresh shared library cache. This is very important.
```

----------------------------------------------

1. **build**

   ```bash
   cmake -B ../../buildlinux
   cmake -B ../../buildlinux -DCMAKE_INSTALL_PREFIX=../../installLinuxxxx
   ```

   

2. **compile**

   ```bash
   cmake --build ../../buildlinux/ --config release --parallel 4
   ```

   

3. **install**

   ```bash
   cmake --install ../../buildlinux/ --config release
   ```

4. **config**

   **==默认安装在 /usr/local 目录下。/usr/local/include /usr/local/lib /usr/local/bin==**
   
   ```bash
   vi ~/.bashrc
   
   protobuf32112_root=/mnt/d/WorkSpace/4openSourceCode/Protobuf/installLinux3.21.12
   protobuf32112_include=${protobuf32112_root}/include
   protobuf32112_lib=${protobuf32112_root}/lib
   protoc_bin=${protobuf32112_root}/bin
   
   export CPLUS_INCLUDE_PATH=${protobuf32112_include}:$CPLUS_INCLUDE_PATH
   export LIBRARY_PATH=${protobuf32112_lib}:$LIBRARY_PATH
   export LD_LIBRARY_PATH=${protobuf32112_lib}:$LD_LIBRARY_PATH
   export PATH=${protobuf32112_root}:${protoc_bin}:$PATH
   ```
   
   



### **配置编译选项**

**To compile a package that uses Protocol Buffers, you need to pass various flags to your compiler and linker. As of version 2.2.0, Protocol Buffers integrates with pkg-config to manage this. If you have pkg-config installed, then you can invoke it to get a list of flags like so:**

```bash
pkg-config --cflags protobuf         # print compiler flags
	-pthread -I/usr/local/include
pkg-config --libs protobuf           # print linker flags
	-L/usr/local/lib -lprotobuf -pthread -lpthread
pkg-config --cflags --libs protobuf  # print both
```

```bash
sudo apt install pkg-config
```



##### **example:**

  **使用 protoc 将.proto 文件生成.h .cpp 文件的命令：**
```bash
protoc -I=$SRC_DIR --cpp_out=$DST_DIR $SRC_DIR/addressbook.proto
```



**linux平台下编译代码：**

```bash
g++ main.cpp *.cc `pkg-config --cflags --libs protobuf` -std=c++11
```

```bash
g++ main.cpp *.cc -I/usr/local/include -L/usr/local/lib -lprotobuf -lpthread -std=c++11
```



**windows平台下（VS013）编译：**

​	**需要配置include路径(-I)，lib库路径 (-L) , 静态库名称(-l)**



**reference:**

​	**https://github.com/protocolbuffers/protobuf/blob/master/src/README.md**