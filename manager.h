#pragma once
#include <iostream>
using namespace std;
#include "worker.h"

class Manager :public Worker
{
public:
	//�������캯��
	Manager(int id,string name,int deptid);
	//������ʾ���˻���Ϣ����
	virtual void Show_Info();

	//������ȡ��λ���ƣ�Ա���������ϰ庯��
	virtual string Get_DeptId();
};
