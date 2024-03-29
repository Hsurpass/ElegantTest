# volatile的作用

volatile关键字是一个类型修饰符，用它声明的类型变量表示随时可能被某编译器未知的因素的修改。比如OS,hardware or other threads. 简单来说，如果一个变量使用了volatile进行修饰，那么每次去读取该值的时候是从对应的地址中去读取，而不会因为编译器发现程序中间没有对该值进行操作所以不从内存而是从上次读到的数据进行操作（这个就是编译器的优化，而==使用了volatile关键字表示编译器不对次进行优化，每次都从对应的内存中读取==）。**这样就保证了对特殊地址的稳定访问。**

volatile告诉编译器，我是易变的，不要随便优化，每次都要从内存中读取，而不是寄存器中。在多线程的情况下，有可能这个变量在更改，而编译器优化后不能及时发现这个变量已经改变了。

```c++
int some_int = 100;
while(some_int == 100)
{
   //your code
}
```

如果编译器发现程序从来没有尝试改变some_int的值，所以它可能会试图通过将循环从更改为等价的东西来优化while循环执行可能很快（因为循环中的条件似乎总是一样的）。**while(some_int == 100) ---> while(true) **

如果编译器不对其进行优化，那么它必须在每次迭代中获取 100 的值并将其与 100 进行比较，这显然有点慢。）

当两个线程都要用到某一个变量且该变量的值会被改变时，应该用 volatile 声明，**该关键字的作用是防止优化编译器把变量从内存装入 CPU 寄存器中。如果变量被装入寄存器，那么两个线程有可能一个使用内存中的变量，一个使用寄存器中的变量，这会造成程序的错误执行**。==volatile 的意思是让编译器每次操作该变量时一定要从内存中真正取出，而不是使用已经存在寄存器中的值.==



references:

[c/c++中的volatile](https://www.jianshu.com/p/9aa858ff46bd)

[c++ volatile的一些理解](https://segmentfault.com/a/1190000041829657)

