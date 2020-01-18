#include"stdafx.h"
using namespace std;

int main(int argc, char* argv[])
{
	Input inputs(argc, argv);
	//处理参数，判断参数是否正确
	inputs.ParameterProcess();
	clock_t start_time = 0, end_time = 0, output_time = 0;
	char type = inputs.GetType();
	if (type == 'c')
	{
		//获得要生成的数独终局的数量
		int Num = inputs.GetNum();
		Sudoku sudokus(Num);
		//记录开始时间
		start_time = clock();
		//生成终局
		sudokus.MakeSudoku();
		//记录生成终局结束时间
		end_time = clock();
		//将终局输出到文件
		sudokus.WriteSudoku();
		//记录输出完成的时间
		output_time = clock();
	}
	if (type == 's')
	{

		Sudoku sudokus;
		//获得数独题目的文件名
		char* Filename = inputs.GetFileName();
		//记录开始时间
		start_time = clock();
		//求解数独问题
		sudokus.SolveSudoku(Filename);
		//记录结束时间
		end_time = clock();
		//输出数独终局
		sudokus.WriteSudoku();
		//记录输出完成时间
		output_time = clock();

	}
	cout << "\n生成终局用时：" << end_time - start_time << " ms" << endl;
	cout << "输出到文本用时：" << output_time - end_time << " ms" << endl;
	return 0;

}