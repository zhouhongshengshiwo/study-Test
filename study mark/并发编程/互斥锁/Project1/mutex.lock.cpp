#include<iostream>
#include<mutex>
using namespace std;
std::mutex mutex1;
int shared_data = 0;
int main() {

	useguard_lock();
	return 0;
}
void useguard_lock() {
	std::lock_guard<std::mutex> lock1(mutex1);//自动加锁，在作用域结束的时候自动解锁
	shared_data++;


}
