// 职工管理系统.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。本项目的功能
//     0.退出管理程序    
//     1.增加职工信息    
//     2.显示职工信息     
//     3.删除离职职工     
//     4.修改职工信息     
//     5.查找职工信息    
//     6.按照编号排序     
//     7.清空所有文档 

//  ****************************
//  Author: Mr Bingxiang Kang  Time:2024.4.14
//  Why: Just for learning
//  ****************************

#include "WorkManager.h"
#include <iostream>
using namespace std;

//测试代码
//#include "worker.h"
//#include "employee.h"
//#include "manager.h"
//#include "boss.h"

int main()
{
	//实例化一个对象
	WorkManager wm;

	////测试员工类代码
	//Worker * Worker = NULL;
	//Worker = new Employee(1, "张三", 1);
	//Worker->Show_Info();
	//delete Worker;

	//Worker = new Manager(2, "李四", 2);
	//Worker->Show_Info();
	//delete Worker;

	//Worker = new Boss(3, "王五", 3);
	//Worker->Show_Info();
	//delete Worker;

	int choice = 0;		//用来储蓄用户的选择

	while (true)
	{
		//调用显示菜单功能函数
		wm.Show_Menu();

		cout << "请输入您的选项： " << endl;
		cin >> choice;	//记录用户选项

		switch (choice)
		{
		case 0:	//退出系统
			wm.Exit_System();
			break;
		case 1:
			wm.Add_Emp();
			break;
		case 2:
			wm.Show_Emp();
			break;
		case 3:
			wm.Del_Emp();
			break;
		case 4:
			wm.Mod_Emp();
			break;
		case 5:
			wm.Find_Emp();
			break;
		case 6:
			wm.Sort_Emp();
			break;
		case 7:
			wm.Clean_File();
			break;
		default:
			break;
		}

	}
	
	system("pause");
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
