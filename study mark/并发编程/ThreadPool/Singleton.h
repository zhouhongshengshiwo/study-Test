#pragma once
#include<iostream>

class Singleton
{
public:
protected:
	Singleton() {};
private:
	Singleton(const Singleton&) = delete;
	Singleton operator=(const Singleton&) = delete;
};

