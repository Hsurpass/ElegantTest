# volatile的作用

volatile关键字是一个类型修饰符，用它声明的类型变量表示随时可能被某编译器未知的因素的修改。比如OS,hardware or other threads.简单来说，如果一个变量使用了volatile进行修饰，那么每次去读取该值的时候是从对应的地址中去读取，而不会因为编译器发现程序中间没有对该值进行操作所以不从内存而是从上次读到的数据进行操作（这个就是编译器的优化，而使用了volatile关键字表示编译器不对次进行优化，每次都从对应的内存中读取）。这样就保证了对特殊地址的稳定访问。



references:

[c/c++中的volatile](https://www.jianshu.com/p/9aa858ff46bd)

[c++ volatile的一些理解](https://segmentfault.com/a/1190000041829657)

