#!/usr/bin/python3

#https://www.liaoxuefeng.com/wiki/1016959663602400/1017631559645600#0

from multiprocessing.managers import BaseManager
import queue, random

from multiprocessing.managers import BaseManager

#发送任务的队列
task_queue = queue.Queue()
#接收结果的队列
result_queue = queue.Queue()

#从BaseManager继承QueueManager
class QueueManager(BaseManager):
    pass


# 把两个Queue都注册到网络上, callable参数关联了Queue对象:
QueueManager.register('get_task_queue', callable = lambda:task_queue)
QueueManager.register('get_result_queue', callable = lambda:result_queue)

# 绑定端口5000, 设置验证码'abc':
manager = QueueManager(address=('', 5000), authkey= b'abc')

#启动Queue
manager.start()


#请注意，当我们在一台机器上写多进程程序时，创建的Queue可以直接拿来用，
# 但是，在分布式多进程环境下，添加任务到Queue不可以直接对原始的task_queue进行操作，
# 那样就绕过了QueueManager的封装，必须通过manager.get_task_queue()获得的Queue接口添加。

# 获得通过网络访问的Queue对象:
task = manager.get_task_queue()
result = manager.get_result_queue()

# 放几个任务进去:
for i in range(10):
    n = random.randint(0, 10000)
    print('Put task %d...' % n)
    task.put(n)

# 从result队列读取结果:
print('Try get results...')
for i in range(10):
    r = result.get(timeout=10)
    print('Result: %s' % r)

#关闭
manager.shutdown()
print('master exit')


#而Queue之所以能通过网络访问，就是通过QueueManager实现的。
# 由于QueueManager管理的不止一个Queue，所以，要给每个Queue的网络调用接口起个名字，比如get_task_queue。

#authkey有什么用？这是为了保证两台机器正常通信，不被其他机器恶意干扰。
# 如果task_worker.py的authkey和task_master.py的authkey不一致，肯定连接不上。
