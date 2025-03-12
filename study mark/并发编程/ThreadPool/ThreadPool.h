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
	std::queue<Task> tasks_;//�������
	std::atomic_int thread_num_;//�����߳���
	std::vector<std::thread> pool_;//�̳߳�
	std::atomic_bool         stop_;// ��ʾ�̳߳��Ƿ��˳�
	std::mutex               cv_mt_;//������
	std::condition_variable  cv_lock_;//��������
};

