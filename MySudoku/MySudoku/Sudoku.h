#pragma once
//用于表示数独的类
class Sudoku {
public:
	Sudoku();//构造函数
	Sudoku(int num);//构造函数
	void MakeSudoku();//当参数为-c，生成数独终局时要调用的生成数独功能的函数
	void WriteSudoku();//用于向文件中输出数独终局的函数
	void SetMark(int row, int col, int block, int flag);//用于标识数独的每一行、列、九宫格的已有数字信息
	void create(int o_row, int o_col);//用于生成一个个数独终局的函数
	void IntoOutSu();//将已经生成的数独终局或者其它即将要输出的数独放入一个等待输出的数组中，准备一次性输出
	void SolveSudoku(char* filename);//当参数为-s，求解数独时要调用的求解数独问题的函数
	bool ReadQuestion(FILE*);//从给定的数独问题文件中读取数独问题，SolveSudoku()要调用的函数
	bool solve(int i, int j);//解决数独问题，SolveSudoku()要调用的函数
	int GetOne();//用于测试的一个函数
	int GetTwo();//用于测试的一个函数
private:
	int su[9][9];//保存数独的数组
	int now_num;//现在已经生成的数独个数
	int out_num;//需要生成的数独个数
	int rowmark[9][10];//rowmark[i][j]第i行已经存在数字j
	int colmark[9][10];//colmark[i][j]第i列已经存在数字j
	int blockmark[9][10];//blockmark[i][j]第i个九宫格已经存在数字j
	int* out_su;//输出数独所用的数组
	int out_pointer;//输出数独指针
};
