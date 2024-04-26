#pragma once
#include <iostream>
using namespace std;
#include "worker.h"

class Employee :public Worker
{
public:
	//构造函数
	Employee(int id, string name, int deptid);

	//创建显示个人化信息函数
	virtual void Show_Info();
	//创建获取岗位名称：员工，经理，老板函数
	virtual string Get_DeptId();
};
