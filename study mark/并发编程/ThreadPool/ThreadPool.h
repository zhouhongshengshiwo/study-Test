#pragma once
#include<iostream>
#include<memory>
#include<thread>
#include<mutex>
#include<algorithm>
#include<queue>
#include <future>
#include <functional>
//#include<>
#include"Singleton.h"
using namespace std;
using Task = std::packaged_task<void()>;

class ThreadPool:public Singleton
{
protected:
	~ThreadPool() {
		stop();
	}
public:
	static ThreadPool& GetInstance() {
		static ThreadPool ins;
		return ins;
	}
	void start();
private:
	void stop();	
	ThreadPool(unsigned int num=std::thread::hardware_concurrency());
	std::queue<Task> tasks_;//任务队列
	std::atomic_int thread_num_;//空闲线程数
	std::vector<std::thread> pool_;//线程池
	std::atomic_bool         stop_;// 表示线程池是否退出
	std::mutex               cv_mt_;//互斥量
	std::condition_variable  cv_lock_;//条件变量
};

