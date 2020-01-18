#include"stdafx.h"
//���캯��
Input::Input(int a, char** b)
{
	this->argcs = a;
	this->argvs = b;
	type = 'n';//��û��ȷ������
	char* c;
	c = new char[50];
	filename = c;
	this->num = 0;
}

void Input::ParameterProcess()
{
	//�жϲ��������Ƿ���ȷ
	if (this->argcs != 3)
	{
		printf("����������������������������ʵ�������վֺ�������������\n");
		exit(1);
	}
	else
	{
		//�ж������Ƿ�Ϊ-c��-s
		if ((this->argvs[1][0] != '-') || ((this->argvs[1][1] != 'c') && (this->argvs[1][1] != 's')) || (this->argvs[1][2] != '\0'))
		{
			printf("������-c��-s�����������վֻ���������\n");
			exit(1);
		}
		//����Ϊ-c
		else if (this->argvs[1][1] == 'c')
		{
			//�������в���ת��Ϊ����
			int number = atoi(argvs[2]);
			if (number < 1 || number>1000000)
			{
				printf("������1��1000000֮�������\n");
				exit(1);
			}
			else 
			{
				this->num = number;
				this->type = 'c';
			}
			
		}
		//����Ϊ-s
		else if (this->argvs[1][1] == 's')
		{
			this->type = 's';
			this->filename = argvs[2];
		}
	}
}

//��ò�������
char Input::GetType()
{
	char c;
	c = this->type;
	return c;
}

//�����������������
int Input::GetNum()
{
	int x;
	x = this->num;
	return x;
}

//���������Ŀ�ļ���
char* Input::GetFileName()
{
	char* filename;
	filename = this->filename;
	return filename;
}
