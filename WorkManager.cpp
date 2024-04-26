#include "WorkManager.h"

WorkManager::WorkManager()
{
	//一共有三种初始化方式
	// 1.文件未被创建----初始化
	
	ifstream ifs;
	ifs.open(FILENAME, ios::in);	//读文件

	if (!ifs.is_open())
	{
		//cout << "文件不存在" << endl;
		
		//初始化
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2.文件存在，但是没有记录
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空" << endl;

		//初始化
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3.文件存在，并且记录数据
	int num = this->Get_EmpNum();
	//cout << "职工人数为: " << num << endl;
	this->m_EmpNum = num;

	//开辟空间
	this->m_EmpArray = new Worker * [m_EmpNum];
	//将文件中的数据，存到数组中
	this->Init_Emp();

	//测试代码
	/*for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << "职工编号:" << this->m_EmpArray[i]->m_Id << " "
			<< "姓名： " << this->m_EmpArray[i]->m_Name << " "
			<< "部门编号:" << this->m_EmpArray[i]->m_DeptId << endl;
	}*/

}

//显示菜单
void WorkManager::Show_Menu()
{
	cout << "***************************************************" << endl;
	cout << "************** 欢迎使用职工管理系统！ *************" << endl;
	cout << "**************     0.退出管理程序     *************" << endl;
	cout << "**************     1.增加职工信息     *************" << endl;
	cout << "**************     2.显示职工信息     *************" << endl;
	cout << "**************     3.删除离职职工     *************" << endl;
	cout << "**************     4.修改职工信息     *************" << endl;
	cout << "**************     5.查找职工信息     *************" << endl;
	cout << "**************     6.按照编号排序     *************" << endl;
	cout << "**************     7.清空所有文档     *************" << endl;
	cout << "***************************************************" << endl;
}

//退出系统
void WorkManager::Exit_System()
{
	cout << "欢迎下次使用!" << endl;
	system("pause");
	exit(0);	//退出函数
}

//添加职工
void WorkManager::Add_Emp()
{
	cout << "请输入添加职工数量: " << endl;

	int addNum = 0;	//保存用户的输入数量
	cin >> addNum;

	if (addNum > 0)
	{
		//添加
		//计算添加空间大小
		int newSize = this->m_EmpNum + addNum;	//新空间人数=原来记录人数+新加入人数
		
		//开辟新空间
		Worker** newSpace = new Worker * [newSize];

		//将原来空间下数据拷贝到新空间下
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		
		//批量添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;	//职工编号
			string name;	//职工姓名
			int dSelect;	//部门选择

			cout << "请输入第" << i + 1 << "个新职工编号:" << endl;
			//判断是否已存在该编号，存在返回重新输入，不存在则加入
			while (1)
			{
				int a = 0;
				cin >> id;
				for (int i = 0; i < this->m_EmpNum; i++)
				{
					if (id == this->m_EmpArray[i]->m_Id)
					{
						cout << "编号已经存在，请重新输入编号。" << endl;
						a = 1;
					}
				}
				if (a == 0)
				{
					break;
				}
			}
			cout << "请输入第" << i + 1 << "个新职工姓名:" << endl;
			cin >> name;

			cout << "请选择该职工岗位: " << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			
			Worker* worker = NULL;
			again:cin >> dSelect;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				cout << "请输入有效输入：1 ，2，3任意选项" << endl;
				goto again;
				break;
			}
			//将创建职工职责，保存到数组中
			newSpace[this->m_EmpNum + i] = worker;

		}
		//释放原有空间
		delete[] this->m_EmpArray;

		//更新新空间的指向  浅拷贝方式，因此newSpace不能释放
		this->m_EmpArray = newSpace;

		//更新新的职工人数
		this->m_EmpNum = newSize;

		//保存数据到文件中
		this->Save();

		//更新职工不为空标志
		this->m_FileIsEmpty = false;

		//提示添加成功
		cout << "成功添加" << addNum << "名新职工" << endl;
	}
	else
	{
		cout << "输入有误" << endl;
	}

	//按任意键，清屏回到上一级目录
	system("pause");
	system("cls");
}

//保存文件
void WorkManager::Save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out); //用输出的方式打开文件--写文件

	//将每个人数据写入到文件中
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}

	//关闭文件
	ofs.close();
}

//统计文件中人数
int WorkManager::Get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);  //打开文件 ---读

	int id;
	string name;
	int deptid;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> deptid)
	{
		//统计人数变量
		num++;
	}
	return num;
}

//初始化员工函数
void WorkManager::Init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME,ios::in);

	int id;
	string name;
	int deptid;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> deptid)
	{
		Worker* worker = NULL;

		if (deptid == 1) //普通员工
		{
			worker = new Employee(id, name, deptid);
		}
		if (deptid == 2) //经理
		{
			worker = new Manager(id, name, deptid);
		}
		if (deptid == 3) //普通员工
		{
			worker = new Boss(id, name, deptid);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}

	//关闭文件
	ifs.close();
}

//显示职工
void WorkManager::Show_Emp()
{
	//判断文件是否为空
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者文件为空!" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//利用多态调用程序接口
			this->m_EmpArray[i]->Show_Info();
		}
	}
	system("pause");
	system("cls");
}

//判断职工是否存在  如果存在返回职工所在数组中的位置
int WorkManager::IsExist(int id)
{
	int index = -1;

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			//找到职工
			index = i;
			break;
		}
	}
	return index;
}

//删除职工
void WorkManager::Del_Emp()
{
	//判断文件是否为空
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者文件为空!" << endl;
	}
	else
	{
		//按照职工号进行删除
		cout << "请输入想要删除职工编号:" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id);

		if (index != -1)	//职工存在,并且要删除index位置的职工
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				//数据前移
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--; //更新数组中记录人员个数
			//数据同步更新到文件中
			this->Save();

			cout << "删除成功" << endl;

		}
		else
		{
			cout << "删除失败，未找到该职工" << endl;
		}
	}
	system("pause");
	system("cls");
}

//修改职工
void WorkManager::Mod_Emp()
{
	//判断文件是否为空
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者文件为空!" << endl;
	}
	else
	{
		//按照职工号进行修改
		cout << "请输入想要修改的职工编号:" << endl;
		int id = 0;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			delete this->m_EmpArray[ret];//删除指针

			int newid;	//职工编号
			string newname;	//职工姓名
			int newdSelect;	//部门选择

			cout << "请输入新的职工编号:" << endl;
			cin >> newid;

			cout << "请输入新的职工姓名:" << endl;
			cin >> newname;

			cout << "请选择该职工岗位: " << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> newdSelect;

			Worker* worker = NULL;
			switch (newdSelect)
			{
			case 1:
				worker = new Employee(newid, newname, 1);
				break;
			case 2:
				worker = new Manager(newid, newname, 2);
				break;
			case 3:
				worker = new Boss(newid, newname, 3);
				break;
			default:
				break;
			}
			//更新数组到数组中
			this->m_EmpArray[ret] = worker;

			cout << "修改成功" << endl;
			//保存到文件中
			this->Save();
		}
		else
		{
			cout << "修改失败，查无此人！" << endl;
		}
	}
	system("pause");
	system("cls");
}

//查找职工
void WorkManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或为空" << endl;
	}
	else
	{
		cout << "请输入查找的方法: " << endl;
		cout << "1、按照职工编号查找" << endl;
		cout << "2、按照职工姓名查找" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			//按照编号查
			int id=0;
			cout << "请输入查找职工的编号" << endl;
			cin >> id;

			int ret = this->IsExist(id);
			if (ret != -1)
			{
				//找到职工
				cout << "查找成功！该职工的信息如下:" << endl;
				this->m_EmpArray[ret]->Show_Info();
			}
			else
			{
				cout << "查找失败" << endl;
			}
		}
		else if (select == 2)
		{
			//按照姓名查
			string name;
			cout << "请输入查找职工的姓名" << endl;
			cin >> name;

			//加入判断是否查到的标志
			bool flag = false; //默认显示没有查到此职工

			for (int i = 0; i < this->m_EmpNum; i++)
			{
				
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功，职工编号为: "
						<< this->m_EmpArray[i]->m_Id
						<< "号职工信息如下：" << endl;

					flag = true;

					//调用显示信息接口
					this->m_EmpArray[i]->Show_Info();
				}	
			}
			if (!flag)
			{
				cout << "查无此人，查找失败" << endl;
			}
		}
		else
		{
			cout << "输入的选项有误！" << endl;
		}

	}
	system("pause");
	system("cls");
}

//按照编号排序---选择排序
void WorkManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或为空" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式" << endl;
		cout << "1、按照升序排放" << endl;
		cout << "2、按照降序排放" << endl;

		int select = 0;
		cin >> select;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrmax = i; //声明最小值 或 最大值下标
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)//升序
				{
					if (this->m_EmpArray[minOrmax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrmax = j;
					}
				}
				else //降序
				{
					if (this->m_EmpArray[minOrmax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOrmax = j;
					}
				}
			}

			//判断一开始认定的 最小值或者最大值 是不是 计算的最小值或者最大值
			if (i!=minOrmax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrmax];
				this->m_EmpArray[minOrmax] = temp;
			}
		}

		cout << "排序成功，排序后的结果是: " << endl;
		Save(); //更新排序后的数据到文件中
		Show_Emp();
	}
}

//清空函数文件
void WorkManager::Clean_File()
{
	cout << "确定清空吗？" << endl;
	cout << "1、清空系统文件" << endl;
	cout << "2、误操作，退出" << endl;
	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//清空文件
		ofstream ofs(FILENAME, ios::trunc); //删除文件后重新创建
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			//删除堆区每个职工对象
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];
					this->m_EmpArray[i] = NULL;
				}
			}
			//删除堆区数组指针
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "文件已清空" << endl;
	}
	else { cout << "退出成功，未清空文件" << endl; }
	system("pause");
	system("cls");
}

WorkManager::~WorkManager()
{
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}
