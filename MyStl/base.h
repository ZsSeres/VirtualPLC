#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdio>
#include "cfg.h";

using namespace::std;

template <typename T>

class Generic_Container {
public:
	int elem_num = 0;
	int MAX_NUM = DEF_MAX_SIZE;
	T* element;
public:
	Generic_Container() {
		element = new T[MAX_NUM];
	}
	Generic_Container(int max_num) {
		MAX_NUM = max_num;
		element = new T[MAX_NUM];
	}
	~Generic_Container() {
		elem_num = 0;
		MAX_NUM = 0;
		element = nullptr;
	}
	 void add(T new_element)
	{
		element[elem_num] = new_element;
		elem_num++;
	}
	T get(unsigned int x)
	{
		for (int i = 0; i < elem_num; i++)
		{
			if (x == i)
				return element[i];
		}
	}
	T* param()
	{
		return element;
	}
	virtual void print() {
		cout << "Mittudomén";
	};
};

class status_word 
{
public:
	unsigned int PC;
	bool RLO;
	bool ERROR;
	bool OV;
	bool ZERO;
	bool FIRSTSCAN;
	unsigned int STACK;//arra hivatott, hogy ha fv-t hívunk akkor tudjunk visszatérni
};