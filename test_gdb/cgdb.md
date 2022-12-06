

```
$ git clone git@github.com:Hsurpass/cgdb.git
$ cd cgdb
$ mkdir build _install
$ ./autogen.sh
(a prebuilt configure script is not included in the git repository, so it must be generated with the autogen.sh script.)
```

Installing
cgdb depends on `libreadline` and `ncurses` development libraries.
```
$ cd build
$ ../configure --prefix=$PWD/../_install
$ make
$ sudo make install
```
(1)出现错误：
```
configure: error: CGDB requires curses.h or ncurses/curses.h to build.
```
解决方案:
```
重要：确认是否安装ncurses库，且必须要安装 libncursesw5-dev，否则中文乱码

apt install libncurses5-dev
apt install libncursesw5-dev
```
(2) 出现错误：
```
configure: error: Please install flex before installing
```
解决:
```
sudo apt install flex
```

configure: error: Please install makeinfo before installing
sudo apt install texinfo

configure: error: CGDB requires GNU readline 5.1 or greater to link.
  If you used --with-readline instead of using the system readline library,
  make sure to set the correct readline library on the linker search path
  via LD_LIBRARY_PATH or some other facility.

  sudo apt install libreadline-dev


vi ~/.bashrc
export PATH=/mnt/d/WorkSpace/4openSourceCode/cgdb/_install/bin:$PATH

references:
    官网: http://cgdb.github.io/
    github: https://github.com/cgdb/cgdb
    中文文档: https://github.com/leeyiw/cgdb-manual-in-chinese
