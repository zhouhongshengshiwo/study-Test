```c++

struct func {
    int& _i;
    func(int & i): _i(i){}
    void operator()() {
        for (int i = 0; i < 3; i++) {
            _i = i;
            std::cout << "_i is " << _i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};

void oops() {

        int some_local_state = 0;
        func myfunc(some_local_state);
        std::thread functhread(myfunc);
        //隐患，访问局部变量，局部变量可能会随着}结束而回收或随着主线程退出而回收
        functhread.detach();    
}

// detach 注意事项
oops();
//防止主线程退出过快，需要停顿一下，让子线程跑起来detach
std::this_thread::sleep_for(std::chrono::seconds(1));
```
在 C++ 中，当你创建一个对象并试图以函数调用的方式使用它时，编译器会自动调用该对象的 operator() 方法