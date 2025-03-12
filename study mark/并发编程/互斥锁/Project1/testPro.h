#pragma once
#include<iostream>
#include<mutex>
using namespace std;
class som_big_object {
public:
    som_big_object(int data) :_data(data) {}
    //��������
    som_big_object(const som_big_object& b2) :_data(b2._data) {
        _data = b2._data;
    }
    //�ƶ�����
    som_big_object(som_big_object&& b2) :_data(std::move(b2._data)) {

    }
    //������������
    friend std::ostream& operator << (std::ostream& os, const som_big_object& big_obj) {
        os << big_obj._data;
        return os;
    }

    //���ظ�ֵ�����
    som_big_object& operator = (const som_big_object& b2) {
        if (this == &b2) {
            return *this;
        }
        _data = b2._data;
        return *this;
    }

    //��������
    friend void swap(som_big_object& b1, som_big_object& b2) {
        som_big_object temp = std::move(b1);
        b1 = std::move(b2);
        b2 = std::move(temp);
    }
private:
    int _data;
};