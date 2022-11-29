###C++
- new/delete 和 malloc/free 区别：
  new/delete是关键字，malloc/free是函数
  new/delete会调用构造和析构函数。
  内存分配失败，new会抛异常bad_alloc
- static
  修饰全局变量:作用域和生命周期都在全局，不能跨文件使用
  修饰局部变量:作用域在函数内, 生命周期在全局。
  修饰函数:不能跨文件使用
  修饰类成员:类内定义，类外初始化，全部对象共享一个static成员变量
  修饰类成员函数: 只能访问static成员变量(没有this指针).
###STL
- vector: 底层是数组，超过容量后会成倍增长，resize会调用构造函数，随机访问迭代器，取元素比较高效，在尾部插入元素比较高效，中间插入比较低效(会有元素的搬移)
- deque: 一个管理器和多个缓冲区，支持随机访问，首尾增删比较高效。
- list：底层是双向链表，双向迭代器，不支持随机访问，插入删除元素比较高效。
- stack: 容器适配器，底层结构可以选用vector,deque, list 
- queue: 容器适配器，底层结构可以选用deque, list. vector没有pop_back
- priority_queue: 底层可以使vector, 算法为二叉堆
- set: 红黑树, 自定义类型需要重载operator<()
- map: rb operator[]需要有默认的构造函数, 查找复杂度O(logn)
- multimap:
- multiset:rb
- unordered_map: hash表, 自定义类型需要重载operator==()，并提供hash-func
- unordered_set: hash表
- unordered_multimap: hash表
- unordered_multiset: hash表
  
###C++11
- auto_ptr: 复制和复制都会改变所有权
- unique_ptr: 不能copy，assign
- share_ptr：引用计数
- weak_ptr：监视share_ptr, 不会增加引用计数，lock()函数提升为shared_ptr,引用计数加1. 
  weak_ptr可以解决share_ptr循环引用造成的内存泄漏问题。

###算法
- 二叉搜索树：左子树都比根节点小，右子树都比根节点大。
- 平衡搜索二叉树：(解决二插搜索树退化成链表的问题)
  1.左子树都比根节点小，右子树都比根节点大。
  2.左右子树高度差不超过1
- AVL-tree:
  平衡因子：导致不平衡的最小子树的根节点
  ```
        5       5               5       5
       /         \             /         \
      3           8           3           8
     /             \           \         /
    1              10           4       7
  1.左旋：以某个节点的右子树为根节点的右子树插入节点导致不平衡     
  2.右旋: 以某个节点的左子树为根节点的左子树插入节点导致不平衡
  3.左右旋: 以某个节点的左子树为根节点的右子树插入节点导致不平衡
  4.右左旋: 以某个节点的右子树为根节点的左子树插入节点导致不平衡

- rb-tree特性:
  1.每个节点或者是红色，或者是黑色。
  2.根节点是黑色。
  3.叶子结点是黑色。
  4.如果一个节点是红色，那么他的左右孩子为黑色。
  5.从一个节点到该节点的子孙节点的所有路径上包含$\color{red} {相同数目的黑节点}$。

###设计模式
- 单例
- 观察者
- 工厂模式
  
###linux系统
- 进程:最小的资源分配单位
- 进程间通信:
  信号
  管道
  消息队列
  信号量
  共享内存
  socket
  eventfd
- 线程:最小的程序执行单位
###网络
- 1.如何判断大小端

  ```
  union bl
  {
      int data; // 0x12345678
      char byte;    // 0x78 -->低字节放在低地址：小端
      // uint8_t byte;
  };

- 2.

###HTTP
- cookie和session：
  cookie保存在客户端，session保存在服务端，当访问量增多session会影响服务器的的性能
  cookie不安全
