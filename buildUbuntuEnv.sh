sudo apt update

sudo apt install build-essential gcc g++ autoconf libtool pkg-config
sudo apt gdb vim git cmake

# sudo spt install cgdb

# clang and LLVM C++ lib is only required for sanitizer builds
# sudo apt-get install clang libc++-dev

sudo apt install man-db manpages-posix
sudo apt install manpages-dev manpages-posix-dev

# 搜狗输入法
# https://shurufa.sogou.com/linux/guide
# flameshot
# https://flameshot.org/docs/guide/key-bindings/
# https://www.bilibili.com/read/cv16612038  # Alt+A F1
# https://github.com/flameshot-org/flameshot
# https://gitcode.net/mirrors/flameshot-org/flameshot?utm_source=csdn_github_accelerator
# sudo apt install flameshot

# terminator
# https://zhuanlan.zhihu.com/p/346665734
sudo apt-get install terminator
# 选中即复制
# 粘贴：Ctrl+V
# 新建窗口：Ctrl+Shift+T
# 关闭窗口：Ctrl+W
# 水平划分窗口：Alt+H
# 垂直划分窗口：Alt+V
# 窗口切换：Ctrl+Tab或者Alt+方向键

# typora
# sudo dpkg -i typora_0.11.18_amd64.deb

# chrome

# vscode

# 录屏软件 obs-studio
# https://blog.csdn.net/qq_45642410/article/details/120889267
# 如果最后一步显示找不到包，可以添加以下仓库源后在执行安装命令：sudo add-apt-repository ppa:obsproject/obs-studio

# wps

# 视频播放器smplayer
# sudo add-apt-repository ppa:rvm/smplayer 
# sudo apt-get update 
# sudo apt-get install smplayer smplayer-themes smplayer-skins

# 有道词典
# https://blog.csdn.net/m0_72983118/article/details/130464581

# typora 0.11.18

# 代码比对工具
# meld beyondcompare https://blog.csdn.net/mao_hui_fei/article/details/127529618

# 时间同步
# https://blog.csdn.net/weixin_35804181/article/details/125778648
# https://blog.csdn.net/vor234/article/details/127100891

# 清理日志以及无用包
# 在/var/log/journal/垃圾日志文件占用比较大，可以通过如下命令来清除:
# journalctl --disk-usage        # 检查日志大小
# sudo journalctl --vacuum-time=1w    # 只保留一周的日志
# sudo journalctl --vacuum-size=500M    # 只保留500MB的日志
# 清理升级缓存以及无用包
# sudo apt-get autoclean                # 删除旧版本软件缓存
# sudo apt-get clean                    # 删除系统内所有软件缓存
# sudo apt-get autoremove             # 删除系统不再使用的孤立软件



