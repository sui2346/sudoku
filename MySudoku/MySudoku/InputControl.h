#pragma once

//表示输入内容的类
class Input {
public:
	void ParameterProcess();//处理参数的函数
	Input(int a, char** b);//构造函数
	char GetType();//获得输入的类型（-c或-s）
	int GetNum();//获得要生成数独的数量
	char* GetFileName();//获得数独题目的文件名
private:
	int argcs;//命令行参数个数
	char** argvs;//命令行参数
	char type;//参数类型-c或-s
	int num;//要生成数独终局的个数
	char* filename;//数独题目的文件名
};


