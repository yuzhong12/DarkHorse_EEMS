#pragma once
#include <iostream>
using namespace std;
#include <string>

//����ְ��������
class Worker
{
public:
	//������ʾ������Ϣ����
	virtual void Show_Info() = 0;

	//������ȡ��λ���ƣ�Ա���������ϰ庯��
	virtual string Get_DeptId() = 0;

	//ְ�����
	int m_Id;
	//ְ������
	string m_Name;
	//���ű��
	int m_DeptId;
	
};