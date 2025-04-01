#pragma once
#include<iostream>
#include<thread>
#include<condition_variable>
#include<memory>
#include<mutex>
#include<queue>
#include<vector>
#include <functional>
#include"Singleton.h"
class ThreadPool :public Singleton<ThreadPool>
{
	friend Singleton<ThreadPool>;
public:
	std::vector<std::thread> _works;
	std::queue<std::function<void()>> tasks;
	std::mutex queue_mutex;
	std::condition_variable condition;
	bool _stop;
private:
	ThreadPool(int threadnum=std::thread::hardware_concurrency()):_stop(false) {
		for (int i = 0; i < threadnum; ++i) {
			_works.emplace_back([this]() {
				for (;;) {
					std::function<void()> task;
					{
						std::unique_lock<std::mutex> lock(this->queue_mutex);
						this->condition.wait(lock, [this] { return this->_stop || !this->tasks.empty(); });
						if (this->_stop && this->tasks.empty())
							return;
						task = std::move(this->tasks.front());
						this->tasks.pop();
					}

					task();
				}

				});
		}
	}

};

