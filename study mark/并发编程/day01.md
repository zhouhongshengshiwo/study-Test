# 在 C++ 中，当你创建一个对象并试图以函数调用的方式使用它时，编译器会自动调用该对象的 operator() 方法，实现仿函数
```c++
class background_task {
public:
	void operator()(std::string str) {//仿函数，使用括号运算符
		std::cout << "str is " << str << std::endl;
	}
};
int mian(){
    	std::thread t2{background_task()};//参数为void
	t2.join();
}

```
```c++
# detach
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
上面的例子存在隐患，因为some_local_state是局部变量, 当oops调用结束后局部变量some_local_state就可能被释放了，而线程还在detach后台运行，容易出现崩溃。 所以当我们在线程中使用局部变量的时候可以采取几个措施解决局部变量的问题

1.通过智能指针传递参数，因为引用计数会随着赋值增加，可保证局部变量在使用期间不被释放，这也就是我们之前提到的伪闭包策略。
2.将局部变量的值作为参数传递，这么做需要局部变量有拷贝复制的功能，而且拷贝耗费空间和效率。
3.将线程运行的方式修改为join，这样能保证局部变量被释放前线程已经运行结束。但是这么做可能会影响运行逻辑。 比如下面的修改 ``` cpp void use_join() { int some_local_state = 0; func myfunc(some_local_state); std::thread functhread(myfunc); functhread.join(); }

# 异常处理
当我们启动一个线程后，如果主线程产生崩溃，会导致子线程也会异常退出，就是调用terminate，如果子线程在进行一些重要的操作比如将充值信息入库等，丢失这些信息是很危险的。所以常用的做法是捕获异常，并且在异常情况下保证子线程稳定运行结束后，主线程抛出异常结束运行。
```c++
void catch_exception() {
	int some_local_state = 0;
	func myfunc(some_local_state);
	std::thread  functhread{ myfunc };
	try {
		//本线程做一些事情,可能引发崩溃
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	catch (std::exception& e) {//主线程崩溃后依然跑完子线程
		functhread.join();
		throw;
	}

	functhread.join();
}
```

# 线程安全
# 可以采用RAII技术，保证线程对象析构的时候等待线程运行结束，回收资源。如果大家还记得我基于asio实现异步服务时，逻辑处理类LogicSystem的析构函数里等待线程退出
```c++
class thread_guard {
private:
	std::thread& _t;
public:
	explicit thread_guard(std::thread& t) :_t(t) {}
	~thread_guard() {
		//join只能调用一次
		if (_t.joinable()) {
			_t.join();
		}
	}

	thread_guard(thread_guard const&) = delete;
	thread_guard& operator=(thread_guard const&) = delete;
};
void auto_guard() {
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread  t(my_func);
	thread_guard g(t);
	//本线程做一些事情
	std::cout << "auto guard finished " << std::endl;
}
```
    //指针常量  char* const p 指针本身不能变
    //常量指针  const char* p指向的内容不能变
