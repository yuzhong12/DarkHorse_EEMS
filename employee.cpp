#include "employee.h"

//���캯��
Employee::Employee(int id, string name, int deptid)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = deptid;
}
//��ʾ���˻���Ϣ
void Employee::Show_Info()
{
	cout << "Ա����ţ� " << this->m_Id
		<< "\tԱ�������� " << this->m_Name
		<< "\tԱ����λ�� " << this->Get_DeptId()
		<< "\tԱ��ְ����ɾ����·������� " << endl;
}
//��ȡ��λ���ƣ�Ա���������ϰ�
string Employee::Get_DeptId()
{
	return string("Ա��");
}