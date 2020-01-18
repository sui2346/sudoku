#include"stdafx.h"

//构造函数，对Sudoku类进行初始化
Sudoku::Sudoku()
{
	this->su[0][0] = 2;//学号后两位为91,(9+1)%9+1=2
	this->rowmark[0][2] = 1;//第0行已经有数字2
	this->colmark[0][2] = 1;//第0列已经有数字2
	this->blockmark[0][2] = 1;//第0个九宫格已经有数字2
	this->now_num = 0;//已经生成数独终局个数为0
	this->out_num = 0;//要求生成数独终局个数为0
	this->out_pointer = 0;//输出数独指针为0
	this->out_su = NULL;//输出数独数组为空

}

//构造函数，参数num为要生成的数独终局数
Sudoku::Sudoku(int num)
{
	memset(this->su, 0, sizeof(int));
	memset(this->rowmark, 0, sizeof(int));
	memset(this->colmark, 0, sizeof(int));
	memset(this->blockmark, 0, sizeof(int));

	this->su[0][0] = 2;//学号后两位为91,(9+1)%9+1=2
	this->rowmark[0][2] = 1;//第0行已经有数字2
	this->colmark[0][2] = 1;//第0列已经有数字2
	this->blockmark[0][2] = 1;//第0个九宫格已经有数字2
	this->now_num = 0;//已经生成的数独个数为0
	this->out_num = num;//要求生成的数独个数为num
	this->out_su = new int[81 * num];//输出数独数组的初始化，大小为数独个数*81
	this->out_pointer = 0;//输出数独数组指针为0
}

//用于标识数独的每一行、列、九宫格的已有数字信息
//参数为行数、列数、数字、flag为要标识的信息（0代表没有该数字，1代表存在该数字），行数、列数都从0开始计数
void Sudoku::SetMark(int row, int col, int num, int flag)
{
	this->rowmark[row][num] = flag;//flag=0，行row已经存在数字num，flag=1，行row不存在数字num
	this->colmark[col][num] = flag;//flag=0，列col已经存在数字num，flag=1，列col不存在数字num
	int blo = ((row / 3) * 3) + (col / 3);//由行数和列数计算所在九宫格的序号，序号为0-8，从左上到右下
	this->blockmark[blo][num] = flag;//flag=0，九宫格blo已经存在数字num，flag=1，九宫格blo不存在数字num
}


//当参数为-c，生成数独终局时要调用的生成数独功能的函数
void Sudoku::MakeSudoku()
{
	int i = 0, j = 0;
	this->su[0][0] = 2;//学号后两位为91,(9+1)%9+1=2
	this->SetMark(0, 0, 2, 1);//0行、0列及对应九宫格已经存在数字2
	this->create(0, 1);//从第0行第1列开始生成数独终局
}


// 用于生成一个个数独终局的函数
void Sudoku::create(int o_row, int o_col)
{
	int row, col;
	row = o_row;
	col = o_col;

	//当现在生成的数独终局个数等于要求生成的数独终局个数时，返回
	if (this->now_num == this->out_num)
	{
		return;
	}

	//生成一个数独终局
	if (row == 8 && col == 9)
	{
		//将数独终局导出到要输出的数组中，等待输出到文件
		this->IntoOutSu();
		//已生成数独终局个数加一
		this->now_num++;
		return;
	}

	//换行
	if (row != 8 && col == 9)
	{
		row++;
		col = 0;
	}
	//计算当前行、列、对应的九宫格数
	int blo = ((row / 3) * 3) + (col / 3);
	for (int x = 1; x <= 9; x++)
	{
		//数字x将要填充的行、列、九宫格中都还不存在数字x
		if ((this->rowmark[row][x] != 1) && (this->colmark[col][x] != 1) && (this->blockmark[blo][x] != 1))
		{
			//将x填入数独
			this->su[row][col] = x;
			//标记行、列、九宫格已经存在数字x
			SetMark(row, col, x, 1);
			//列数+1递归调用函数
			this->create(row, col + 1);
			//标记行、列、九宫格不存在数字x
			//保证回溯后状态也恢复
			SetMark(row, col, x, 0);
		}
	}
	//数字x从1到9在当前位置都不合适，先暂时把当前位置填入数字0
	this->su[row][col] = 0;
}


//将已经生成的数独终局或者其它即将要输出的数独放入一个等待输出的数组中，准备一次性输出
void Sudoku::IntoOutSu()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			this->out_su[this->out_pointer++] = this->su[i][j];
		}
	}
}

//用于向文件中输出数独终局的函数
void Sudoku::WriteSudoku()
{
	int i = 0;
	char path[20] = "./sudoku.txt";
	FILE* fp = NULL;

	fp = fopen(path, "w");

	if (fp == NULL)
	{
		printf("创建文件失败\n");
		exit(1);
	}

	else {
		for (i = 0; i < this->out_pointer; i++)
		{
			if (i % 9 < 8)
			{
				fprintf(fp, "%d ", this->out_su[i]);
			}
			else if (((i + 1) % 81 == 0) && ((i + 1) / 81 != this->out_num))
			{
				fprintf(fp, "%d\n\n", this->out_su[i]);
			}
			else if (((i + 1) % 81 == 0) && ((i + 1) / 81 == this->out_num))
			{
				fprintf(fp, "%d", this->out_su[i]);
			}
			else if (i % 9 == 8)
			{
				fprintf(fp, "%d\n", this->out_su[i]);
			}

		}

		fclose(fp);
		fp = NULL;
	}


}


//当参数为-s，求解数独时要调用的求解数独问题的函数
void Sudoku::SolveSudoku(char* filename)
{
	FILE* question = NULL;
	question = fopen(filename, "r+");
	this->out_su = new int[1000000 * 81];
	if (question == NULL)
	{
		printf("打开文件失败！请确定是否存在该文件！\n");
		exit(1);
	}
	else
	{	
		//当读取到数独时
		while (this->ReadQuestion(question))
		{
			//求解数独，从第0行第0列开始
			if (this->solve(0, 0))
			{
				//将求解完的数独放入准备输出的数组中
				this->IntoOutSu();
			}
		}
	}
	//关闭文件
	fclose(question);

}

//解决数独问题，SolveSudoku()要调用的函数
bool Sudoku::solve(int i, int j)
{
	//当求解完一个数独时，返回
	if (i == 8 && j == 9)
	{
		return true;
	}

	//换行
	if (i != 8 && j == 9)
	{
		i++;
		j = 0;
	}

	//当数独数字非0
	if (this->su[i][j] != 0)
	{
		//直接换到下一个数字的求解
		return this->solve(i, j + 1);
	}
	//根据行数、列数确定九宫格数
	int blo = ((i / 3) * 3) + (j / 3);
	for (int x = 1; x <= 9; x++)
	{
		//当所在行、列、九宫格都不存在x时
		if ((this->rowmark[i][x] != 1) && (this->colmark[j][x] != 1) && (this->blockmark[blo][x] != 1))
		{
			this->su[i][j] = x;
			//标记行、列、九宫格已经存在x
			SetMark(i, j, x, 1);
			//递归求解数独
			bool flag = this->solve(i, j + 1);

			if (flag)
			{
				return true;
			}
			//标记行、列、九宫格不存在数字x
			//保证回溯后状态也恢复
			SetMark(i, j, x, 0);
		}
	}
	//该位置填入1-9都不合适，暂时标为0
	this->su[i][j] = 0;
	return false;
}

//从给定的数独问题文件中读取数独问题，SolveSudoku()要调用的函数
bool Sudoku::ReadQuestion(FILE* question)
{
	//将标记行、列、九宫格的数组都置0，消除上一个数独的影响
	memset(this->rowmark, 0, sizeof(this->rowmark));
	memset(this->colmark, 0, sizeof(this->colmark));
	memset(this->blockmark, 0, sizeof(this->blockmark));
	char content[20];
	int flag = 0;
	int k = 0, j = 0;
	for (int i = 0; i < 9;)
	{
		//读取文件内容为空
		if (fgets(content, 20, question) == NULL)
		{
			return false;
		}

		//数独中两个数字之间存在空格，k+=2
		for (k = 0, j = 0; k <= 16; k += 2, j++)
		{
			flag = 0;
			if (content[k] >= '0' && content[k] <= '9')
			{
				int num = content[k] - '0';
				this->su[i][j] = num;
				//标记存在
				SetMark(i, j, num, 1);
				//表示这一行中是数字，而不是空格
				flag = 1;
			}
		}
		//当本行为数独时，行数才加一
		if (flag == 1)
		{
			i++;
		}

	}
	return true;
}

int Sudoku::GetOne()
{
	return this->su[0][0];
}

int Sudoku::GetTwo()
{
	return this->su[1][1];
}