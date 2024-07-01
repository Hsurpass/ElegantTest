#!/usr/bin/python3

class MyContextManager:  
    def __enter__(self):  
        print("Entering the context")  
        return self  # 通常返回一些资源或状态对象，但这里为了简单起见返回self  
  
    def __exit__(self, exc_type, exc_val, exc_tb):  
        print("Exiting the context")  
  
# 使用 with 语句  
with MyContextManager() as cm:  
    print("Inside the context block")  
    # 这里可以执行任何你想要的代码  
    # 当这些代码执行完毕后，with 块会自动结束  
  
# 输出将是：  
# Entering the context  
# Inside the context block  
# Exiting the context