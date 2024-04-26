#include "employee.h"

//构造函数
Employee::Employee(int id, string name, int deptid)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = deptid;
}
//显示个人化信息
void Employee::Show_Info()
{
	cout << "员工编号： " << this->m_Id
		<< "\t员工姓名： " << this->m_Name
		<< "\t员工岗位： " << this->Get_DeptId()
		<< "\t员工职责：完成经理下发的任务 " << endl;
}
//获取岗位名称：员工，经理，老板
string Employee::Get_DeptId()
{
	return string("员工");
}