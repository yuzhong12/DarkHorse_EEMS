#pragma once   //防止头文件重复包含

#include <iostream>
using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

#include <fstream>
#define FILENAME "empFile.txt"

//创建 WorkManager 功能类
class WorkManager
{
public:
	//创建构造函数
	WorkManager();

	//创建菜单函数
	void Show_Menu();

	//创建退出系统函数
	void Exit_System();

	//创建添加职工函数
	void Add_Emp();

	//保存文件
	void Save();

	//统计文件中人数
	int Get_EmpNum();

	//初始化员工函数
	void Init_Emp();

	//显示职工
	void Show_Emp();

	//判断职工是否存在  如果存在返回职工所在数组中的位置
	int IsExist(int id);

	//删除职工
	void Del_Emp();

	//修改职工
	void Mod_Emp();

	//查找职工
	void Find_Emp();

	//按照编号排序---选择排序
	void Sort_Emp();

	//清空函数文件
	void Clean_File();

	//创建析构函数
	~WorkManager();

	//记录职工人数
	int m_EmpNum;

	//你要用指针接收，而用什么指针就取决于你后面的数据类型，也就是（数据类型）*，把worker*当作一种数据类型就行
	//职工数组指针
	Worker** m_EmpArray;

	//判断文件是否为空
	bool m_FileIsEmpty;
};
