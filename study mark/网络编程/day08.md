```c++
int main()
{
    try {
        boost::asio::io_context  io_context;
        boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);
        //创建一个信号集，绑定到io_context。这里监听的信号是
        //SIGINT（通常是Ctrl+C产生的中断信号）和SIGTERM（终止信号）。这意味着当程序接收到这些信号时，会触发相应的操作。
        signals.async_wait([&io_context](auto, auto) {//注册一个异步等待的回调函数。当接收到指定的信号(上面绑定的信号集)时，这个函数会被调用
            io_context.stop();
            });
        CServer s(io_context, 10086);
        io_context.run();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << endl;
    }
}
```
异步等待信号集，不会阻塞进程


# 回调函数
typedef  function<void(shared_ptr<CSession>, short msg_id, string msg_data)> FunCallBack; //定义回调函数类型
//void 为函数的返回类型，shared_ptr<CSession> 为第一个参数，short 为第二个参数，string 为第三个参数。

_fun_callbacks[MSG_HELLO_WORD] = std::bind(&LogicSystem::HelloWordCallBack,
this, std::placeholders::_1, std::placeholders::_2,std::placeholders::_3); //绑定回调函数到消息处理函数

MSG_HELLO_WORD 为消息ID，_fun_callbacks[MSG_HELLO_WORD] 为回调函数。


# 
```c++
void LogicSystem::PostMsgToQue(shared_ptr<LogicNode> msg)//外部的session对逻辑队列操作
{
    std::unique_lock<std::mutex> unique_lk(_mutex);
    _msg_que.push(msg);
    //由0变为1则发送通知信号//投递一个msg之后唤醒一个线程
    //生产者消费者模型
    if (_msg_que.size() == 1) {
        unique_lk.unlock();
        _consume.notify_one();
    }
}
void LogicSystem::DealMsg()
{
    for (;;) {
        std::unique_lock<std::mutex> unique_lk(_mutex);//对mutex加锁
        //判断队列为空则用条件变量等待
        while (_msg_que.empty() && !_b_stop){
            _consume.wait(unique_lk);
        }//条件变量挂起
        //判断如果为关闭状态，去除逻辑队列所有数据及时处理并退出循环
        if (_b_stop) {
            while (!_msg_que.empty()) {
                auto msg_node = _msg_que.front();
                std::cout << "recv_msg id  is " << msg_node->_recvnode->_msg_id << std::endl;
                auto call_back_iter = _fun_callbacks.find(msg_node->_recvnode->_msg_id);//回调函数id
                if (call_back_iter == _fun_callbacks.end()) {
                    _msg_que.pop();
                    continue;
                }
                call_back_iter->second(msg_node->_session, msg_node->_recvnode->_msg_id,
                    std::string(msg_node->_recvnode->_data, msg_node->_recvnode->_cur_len));
                _msg_que.pop();
            }
            break;
        }

        //如果没有停服，且说明队列中有数据
        auto msg_node = _msg_que.front();
        cout << "recv_msg id  is " << msg_node->_recvnode->_msg_id << endl;
        auto call_back_iter = _fun_callbacks.find(msg_node->_recvnode->_msg_id);
        if (call_back_iter == _fun_callbacks.end()) {
            _msg_que.pop();
            continue;
        }
        call_back_iter->second(msg_node->_session, msg_node->_recvnode->_msg_id,
            std::string(msg_node->_recvnode->_data, msg_node->_recvnode->_cur_len));
        _msg_que.pop();
    }
}
```
上面的LogicSystem与多个Session实例的组合中，采用了多线程思想

生产者负责创建和发送数据（在这里是Session实例），消费者负责处理数据（在这里是LogicSystem）

    多个Session可以同时将消息推送到LogicSystem的消息队列中。这些消息的处理则在单独的工作线程（LogicSystem的DealMsg方法）行，
从而实现了生产者和消费者之间的解耦。

使用std::mutex来保护共享资源（消息队列）

使用std::condition_variable实现线程之间的通信，当消息队列为空时，消费者线程可以等待条件变量的通知，避免了忙等（busy-waiting）

非阻塞设计: 生产者（多个Session）可以持续投递消息，而消费者（LogicSystem）在处理消息时不会阻塞其他生成消息的操作，这种设计使得系统能够同时处理多个操作，增强了响应能力。

 std::unique_lock<std::mutex> unique_lk(_mutex)创建时会锁住mutex，在unique_lk离开作用域时自动释放锁。
 在队列非空且线程未停止时，调用_consume.wait(unique_lk)，会释放锁，并且挂起线程，等待notify_one()或notify_all()的调用。
 session投递数据到空的逻辑队列时，会调用notify_one()通知挂起的消费者线程，消费者线程被唤醒，处理队列中的数据。