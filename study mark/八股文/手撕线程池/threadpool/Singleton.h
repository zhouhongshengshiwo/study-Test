#pragma once
#include<memory>
template <class T>
class Singleton
{
protected:
	Singleton() = default;
	Singleton ( const Singleton<T>& ) = delete;
	Singleton& operator=(const Singleton<T>&) = delete;
	static std::shared_ptr<T> _instance 
public:
	 static std::shared_ptr<T>& GetInstance() {
		 _instance = new T;
		 return _instance;
	}
};
template <class T>
static std::shared_ptr<T> Singleton<T>::_instance = nullptr;
