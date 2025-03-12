#pragma once
#include<iostream>
#include<mutex>
#include"testPro.h"

using namespace std;
class big_object_mgr {
public:
    big_object_mgr(int data = 0) :_obj(data) {}
    void printinfo() {
        std::cout << "current obj data is " << _obj << std::endl;
    }
    friend void danger_swap(big_object_mgr& objm1, big_object_mgr& objm2);
    friend void safe_swap(big_object_mgr& objm1, big_object_mgr& objm2);
    friend void safe_swap_scope(big_object_mgr& objm1, big_object_mgr& objm2);
private:
    std::mutex _mtx;
    som_big_object _obj;
};
void danger_swap(big_object_mgr& objm1, big_object_mgr& objm2) {
    std::cout << "thread [ " << std::this_thread::get_id() << " ] begin" << std::endl;
    if (&objm1 == &objm2) {
        return;
    }
    std::lock_guard <std::mutex> gurad1(objm1._mtx);
    //�˴�Ϊ�˹��������������������߳�С˯һ��
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::lock_guard<std::mutex> guard2(objm2._mtx);
    swap(objm1._obj, objm2._obj);
    std::cout << "thread [ " << std::this_thread::get_id() << " ] end" << std::endl;
}
void  test_danger_swap() {
    big_object_mgr objm1(5);
    big_object_mgr objm2(100);

    std::thread t1(danger_swap, std::ref(objm1), std::ref(objm2));
    std::thread t2(danger_swap, std::ref(objm2), std::ref(objm1));
    t1.join();
    t2.join();

    objm1.printinfo();
    objm2.printinfo();
}
void safe_swap(big_object_mgr& objm1, big_object_mgr& objm2) {
    std::cout << "thread [ " << std::this_thread::get_id() << " ] begin" << std::endl;
    if (&objm1 == &objm2) {
        return;
    }

    std::lock(objm1._mtx, objm2._mtx);
    //�������������Զ��ͷ�
    std::lock_guard <std::mutex> gurad1(objm1._mtx, std::adopt_lock);

    //�˴�Ϊ�˹��������������������߳�С˯һ��
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::lock_guard <std::mutex> gurad2(objm2._mtx, std::adopt_lock);

    swap(objm1._obj, objm2._obj);
    std::cout << "thread [ " << std::this_thread::get_id() << " ] end" << std::endl;
}

void test_safe_swap() {
    big_object_mgr objm1(5);
    big_object_mgr objm2(100);

    std::thread t1(safe_swap, std::ref(objm1), std::ref(objm2));
    std::thread t2(safe_swap, std::ref(objm2), std::ref(objm1));
    t1.join();
    t2.join();

    objm1.printinfo();
    objm2.printinfo();
}