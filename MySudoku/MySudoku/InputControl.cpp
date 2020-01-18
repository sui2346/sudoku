#include"stdafx.h"
//构造函数
Input::Input(int a, char** b)
{
	this->argcs = a;
	this->argvs = b;
	type = 'n';//还没有确定类型
	char* c;
	c = new char[50];
	filename = c;
	this->num = 0;
}

void Input::ParameterProcess()
{
	//判断参数数量是否正确
	if (this->argcs != 3)
	{
		printf("参数数量错误！请输入两个参数来实现生成终局和求解数独的命令。\n");
		exit(1);
	}
	else
	{
		//判断命令是否为-c或-s
		if ((this->argvs[1][0] != '-') || ((this->argvs[1][1] != 'c') && (this->argvs[1][1] != 's')) || (this->argvs[1][2] != '\0'))
		{
			printf("请输入-c或-s来生成数独终局或求解解数独\n");
			exit(1);
		}
		//命令为-c
		else if (this->argvs[1][1] == 'c')
		{
			//将命令行参数转换为整数
			int number = atoi(argvs[2]);
			if (number < 1 || number>1000000)
			{
				printf("请输入1到1000000之间的整数\n");
				exit(1);
			}
			else 
			{
				this->num = number;
				this->type = 'c';
			}
			
		}
		//命令为-s
		else if (this->argvs[1][1] == 's')
		{
			this->type = 's';
			this->filename = argvs[2];
		}
	}
}

//获得参数类型
char Input::GetType()
{
	char c;
	c = this->type;
	return c;
}

//获得生成数独的数量
int Input::GetNum()
{
	int x;
	x = this->num;
	return x;
}

//获得数独题目文件名
char* Input::GetFileName()
{
	char* filename;
	filename = this->filename;
	return filename;
}
