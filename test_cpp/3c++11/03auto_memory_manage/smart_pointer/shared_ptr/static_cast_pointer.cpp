/*
根据 static_cast 的知识：编译器隐式执行的任何类型转换都可以由static_cast 显示完成（如 int -> char；）； 
如果编译器不提供自动转换，使用 static_cast 来执行类型转换也是很有用的（如，找回存放在 void* 指针中的值）。

注意：static_cast 转换的一个特点就是：它只会生成原变量的副本，不会对原变量有任何修改。
而static_pointer_cast 工作的前提是：static_cast<T*>(r.get()) 必须是有效的。二者理念相同！

*/