#pragma once
#include <iostream>
using namespace std;
#include "worker.h"

class Boss :public Worker
{
public:
	//�������캯��
	Boss(int id, string name, int deptid);
	//������ʾ���˻���Ϣ����
	virtual void Show_Info();

	//������ȡ��λ���ƣ�Ա���������ϰ庯��
	virtual string Get_DeptId();
};