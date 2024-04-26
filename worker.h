#pragma once
#include <iostream>
using namespace std;
#include <string>

//创建职工抽象类
class Worker
{
public:
	//创建显示个人信息函数
	virtual void Show_Info() = 0;

	//创建获取岗位名称：员工，经理，老板函数
	virtual string Get_DeptId() = 0;

	//职工编号
	int m_Id;
	//职工姓名
	string m_Name;
	//部门编号
	int m_DeptId;
	
};