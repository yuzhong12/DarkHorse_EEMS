#pragma once   //��ֹͷ�ļ��ظ�����

#include <iostream>
using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

#include <fstream>
#define FILENAME "empFile.txt"

//���� WorkManager ������
class WorkManager
{
public:
	//�������캯��
	WorkManager();

	//�����˵�����
	void Show_Menu();

	//�����˳�ϵͳ����
	void Exit_System();

	//�������ְ������
	void Add_Emp();

	//�����ļ�
	void Save();

	//ͳ���ļ�������
	int Get_EmpNum();

	//��ʼ��Ա������
	void Init_Emp();

	//��ʾְ��
	void Show_Emp();

	//�ж�ְ���Ƿ����  ������ڷ���ְ�����������е�λ��
	int IsExist(int id);

	//ɾ��ְ��
	void Del_Emp();

	//�޸�ְ��
	void Mod_Emp();

	//����ְ��
	void Find_Emp();

	//���ձ������---ѡ������
	void Sort_Emp();

	//��պ����ļ�
	void Clean_File();

	//������������
	~WorkManager();

	//��¼ְ������
	int m_EmpNum;

	//��Ҫ��ָ����գ�����ʲôָ���ȡ�����������������ͣ�Ҳ���ǣ��������ͣ�*����worker*����һ���������;���
	//ְ������ָ��
	Worker** m_EmpArray;

	//�ж��ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;
};
