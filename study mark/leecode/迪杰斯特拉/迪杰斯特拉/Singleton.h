#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<memory>
using namespace std;

template<class T>
class Singleton {
protected:
	Singleton(const Singleton<T>&) = delete;
	Singleton<T>& operator=(const Singleton<T>&) = delete;
	Singleton()=default;
	static shared_ptr<T> _instance;
public:
	static shared_ptr<T>* GetInstance() {
		static std::once_flag S_flage;
		std::call_once(S_flag, [&]() {
			_instance = shared_ptr<T>(new T);
			});
		return  _instance;
	}
};

template<class T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr;