#include "manager.h"

//���캯��
Manager::Manager(int id, string name, int deptid)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = deptid;
}
//��ʾ���˻���Ϣ
void Manager::Show_Info() 
{
	cout << "Ա����ţ� " << this->m_Id
		<< "\tԱ�������� " << this->m_Name
		<< "\tԱ����λ�� " << this->Get_DeptId()
		<< "\tԱ��ְ������ϰ�������񣬲��ҽ���������Ա�� " << endl;
}

//��ȡ��λ���ƣ�Ա���������ϰ�
string Manager::Get_DeptId()
{
	return string("����");
}