#include "boss.h"

//���캯��
Boss::Boss(int id, string name, int deptid)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = deptid;
}
//��ʾ���˻���Ϣ
void Boss::Show_Info()
{
	cout << "Ա����ţ� " << this->m_Id
		<< "\tԱ�������� " << this->m_Name 
		<< "\tԱ����λ�� " << this->Get_DeptId()
		<< "\tԱ��ְ�𣺹���˾ " << endl;
}

//��ȡ��λ���ƣ�Ա���������ϰ�
string Boss::Get_DeptId()
{
	return string("�ϰ�");
}