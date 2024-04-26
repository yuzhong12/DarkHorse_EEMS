#include "WorkManager.h"

WorkManager::WorkManager()
{
	//һ�������ֳ�ʼ����ʽ
	// 1.�ļ�δ������----��ʼ��
	
	ifstream ifs;
	ifs.open(FILENAME, ios::in);	//���ļ�

	if (!ifs.is_open())
	{
		//cout << "�ļ�������" << endl;
		
		//��ʼ��
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2.�ļ����ڣ�����û�м�¼
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ��" << endl;

		//��ʼ��
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3.�ļ����ڣ����Ҽ�¼����
	int num = this->Get_EmpNum();
	//cout << "ְ������Ϊ: " << num << endl;
	this->m_EmpNum = num;

	//���ٿռ�
	this->m_EmpArray = new Worker * [m_EmpNum];
	//���ļ��е����ݣ��浽������
	this->Init_Emp();

	//���Դ���
	/*for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << "ְ�����:" << this->m_EmpArray[i]->m_Id << " "
			<< "������ " << this->m_EmpArray[i]->m_Name << " "
			<< "���ű��:" << this->m_EmpArray[i]->m_DeptId << endl;
	}*/

}

//��ʾ�˵�
void WorkManager::Show_Menu()
{
	cout << "***************************************************" << endl;
	cout << "************** ��ӭʹ��ְ������ϵͳ�� *************" << endl;
	cout << "**************     0.�˳��������     *************" << endl;
	cout << "**************     1.����ְ����Ϣ     *************" << endl;
	cout << "**************     2.��ʾְ����Ϣ     *************" << endl;
	cout << "**************     3.ɾ����ְְ��     *************" << endl;
	cout << "**************     4.�޸�ְ����Ϣ     *************" << endl;
	cout << "**************     5.����ְ����Ϣ     *************" << endl;
	cout << "**************     6.���ձ������     *************" << endl;
	cout << "**************     7.��������ĵ�     *************" << endl;
	cout << "***************************************************" << endl;
}

//�˳�ϵͳ
void WorkManager::Exit_System()
{
	cout << "��ӭ�´�ʹ��!" << endl;
	system("pause");
	exit(0);	//�˳�����
}

//���ְ��
void WorkManager::Add_Emp()
{
	cout << "���������ְ������: " << endl;

	int addNum = 0;	//�����û�����������
	cin >> addNum;

	if (addNum > 0)
	{
		//���
		//������ӿռ��С
		int newSize = this->m_EmpNum + addNum;	//�¿ռ�����=ԭ����¼����+�¼�������
		
		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];

		//��ԭ���ռ������ݿ������¿ռ���
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		
		//�������������
		for (int i = 0; i < addNum; i++)
		{
			int id;	//ְ�����
			string name;	//ְ������
			int dSelect;	//����ѡ��

			cout << "�������" << i + 1 << "����ְ�����:" << endl;
			//�ж��Ƿ��Ѵ��ڸñ�ţ����ڷ����������룬�����������
			while (1)
			{
				int a = 0;
				cin >> id;
				for (int i = 0; i < this->m_EmpNum; i++)
				{
					if (id == this->m_EmpArray[i]->m_Id)
					{
						cout << "����Ѿ����ڣ������������š�" << endl;
						a = 1;
					}
				}
				if (a == 0)
				{
					break;
				}
			}
			cout << "�������" << i + 1 << "����ְ������:" << endl;
			cin >> name;

			cout << "��ѡ���ְ����λ: " << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			
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
				cout << "��������Ч���룺1 ��2��3����ѡ��" << endl;
				goto again;
				break;
			}
			//������ְ��ְ�𣬱��浽������
			newSpace[this->m_EmpNum + i] = worker;

		}
		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;

		//�����¿ռ��ָ��  ǳ������ʽ�����newSpace�����ͷ�
		this->m_EmpArray = newSpace;

		//�����µ�ְ������
		this->m_EmpNum = newSize;

		//�������ݵ��ļ���
		this->Save();

		//����ְ����Ϊ�ձ�־
		this->m_FileIsEmpty = false;

		//��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum << "����ְ��" << endl;
	}
	else
	{
		cout << "��������" << endl;
	}

	//��������������ص���һ��Ŀ¼
	system("pause");
	system("cls");
}

//�����ļ�
void WorkManager::Save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out); //������ķ�ʽ���ļ�--д�ļ�

	//��ÿ��������д�뵽�ļ���
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}

	//�ر��ļ�
	ofs.close();
}

//ͳ���ļ�������
int WorkManager::Get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);  //���ļ� ---��

	int id;
	string name;
	int deptid;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> deptid)
	{
		//ͳ����������
		num++;
	}
	return num;
}

//��ʼ��Ա������
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

		if (deptid == 1) //��ͨԱ��
		{
			worker = new Employee(id, name, deptid);
		}
		if (deptid == 2) //����
		{
			worker = new Manager(id, name, deptid);
		}
		if (deptid == 3) //��ͨԱ��
		{
			worker = new Boss(id, name, deptid);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}

	//�ر��ļ�
	ifs.close();
}

//��ʾְ��
void WorkManager::Show_Emp()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ����ļ�Ϊ��!" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//���ö�̬���ó���ӿ�
			this->m_EmpArray[i]->Show_Info();
		}
	}
	system("pause");
	system("cls");
}

//�ж�ְ���Ƿ����  ������ڷ���ְ�����������е�λ��
int WorkManager::IsExist(int id)
{
	int index = -1;

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			//�ҵ�ְ��
			index = i;
			break;
		}
	}
	return index;
}

//ɾ��ְ��
void WorkManager::Del_Emp()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ����ļ�Ϊ��!" << endl;
	}
	else
	{
		//����ְ���Ž���ɾ��
		cout << "��������Ҫɾ��ְ�����:" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id);

		if (index != -1)	//ְ������,����Ҫɾ��indexλ�õ�ְ��
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				//����ǰ��
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--; //���������м�¼��Ա����
			//����ͬ�����µ��ļ���
			this->Save();

			cout << "ɾ���ɹ�" << endl;

		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}
	}
	system("pause");
	system("cls");
}

//�޸�ְ��
void WorkManager::Mod_Emp()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ����ļ�Ϊ��!" << endl;
	}
	else
	{
		//����ְ���Ž����޸�
		cout << "��������Ҫ�޸ĵ�ְ�����:" << endl;
		int id = 0;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			delete this->m_EmpArray[ret];//ɾ��ָ��

			int newid;	//ְ�����
			string newname;	//ְ������
			int newdSelect;	//����ѡ��

			cout << "�������µ�ְ�����:" << endl;
			cin >> newid;

			cout << "�������µ�ְ������:" << endl;
			cin >> newname;

			cout << "��ѡ���ְ����λ: " << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
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
			//�������鵽������
			this->m_EmpArray[ret] = worker;

			cout << "�޸ĳɹ�" << endl;
			//���浽�ļ���
			this->Save();
		}
		else
		{
			cout << "�޸�ʧ�ܣ����޴��ˣ�" << endl;
		}
	}
	system("pause");
	system("cls");
}

//����ְ��
void WorkManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ�Ϊ��" << endl;
	}
	else
	{
		cout << "��������ҵķ���: " << endl;
		cout << "1������ְ����Ų���" << endl;
		cout << "2������ְ����������" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			//���ձ�Ų�
			int id=0;
			cout << "���������ְ���ı��" << endl;
			cin >> id;

			int ret = this->IsExist(id);
			if (ret != -1)
			{
				//�ҵ�ְ��
				cout << "���ҳɹ�����ְ������Ϣ����:" << endl;
				this->m_EmpArray[ret]->Show_Info();
			}
			else
			{
				cout << "����ʧ��" << endl;
			}
		}
		else if (select == 2)
		{
			//����������
			string name;
			cout << "���������ְ��������" << endl;
			cin >> name;

			//�����ж��Ƿ�鵽�ı�־
			bool flag = false; //Ĭ����ʾû�в鵽��ְ��

			for (int i = 0; i < this->m_EmpNum; i++)
			{
				
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "���ҳɹ���ְ�����Ϊ: "
						<< this->m_EmpArray[i]->m_Id
						<< "��ְ����Ϣ���£�" << endl;

					flag = true;

					//������ʾ��Ϣ�ӿ�
					this->m_EmpArray[i]->Show_Info();
				}	
			}
			if (!flag)
			{
				cout << "���޴��ˣ�����ʧ��" << endl;
			}
		}
		else
		{
			cout << "�����ѡ������" << endl;
		}

	}
	system("pause");
	system("cls");
}

//���ձ������---ѡ������
void WorkManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ�Ϊ��" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ" << endl;
		cout << "1�����������ŷ�" << endl;
		cout << "2�����ս����ŷ�" << endl;

		int select = 0;
		cin >> select;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrmax = i; //������Сֵ �� ���ֵ�±�
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)//����
				{
					if (this->m_EmpArray[minOrmax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrmax = j;
					}
				}
				else //����
				{
					if (this->m_EmpArray[minOrmax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOrmax = j;
					}
				}
			}

			//�ж�һ��ʼ�϶��� ��Сֵ�������ֵ �ǲ��� �������Сֵ�������ֵ
			if (i!=minOrmax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrmax];
				this->m_EmpArray[minOrmax] = temp;
			}
		}

		cout << "����ɹ��������Ľ����: " << endl;
		Save(); //�������������ݵ��ļ���
		Show_Emp();
	}
}

//��պ����ļ�
void WorkManager::Clean_File()
{
	cout << "ȷ�������" << endl;
	cout << "1�����ϵͳ�ļ�" << endl;
	cout << "2����������˳�" << endl;
	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//����ļ�
		ofstream ofs(FILENAME, ios::trunc); //ɾ���ļ������´���
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			//ɾ������ÿ��ְ������
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];
					this->m_EmpArray[i] = NULL;
				}
			}
			//ɾ����������ָ��
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "�ļ������" << endl;
	}
	else { cout << "�˳��ɹ���δ����ļ�" << endl; }
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
