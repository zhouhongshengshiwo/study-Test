#pragma once
#include<iostream>
#include<memory>
#include<algorithm>
#include<mutex>
using namespace std;

template <class T>
class Singleton
{
public:

	static std::shared_ptr<T> GetInstance() {
		static std::once_flag S_flag;

		std::call_once(S_flag, [&]() {
			_instance = std::shared_ptr<T>(new T);
			});
		return _instance;
	}
private:
	Singleton()=default;
	Singleton(Const Singleton<T>&) = delete;
	Singleton<T>& operator=(Const Singleton<T>&) = delete;
	static std::shared_ptr<T>_instance;
};
template <class T>
static std::shared_ptr<T> Singleton<T>:: _instance = nullptr;
