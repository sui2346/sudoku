#include"stdafx.h"

//���캯������Sudoku����г�ʼ��
Sudoku::Sudoku()
{
	this->su[0][0] = 2;//ѧ�ź���λΪ91,(9+1)%9+1=2
	this->rowmark[0][2] = 1;//��0���Ѿ�������2
	this->colmark[0][2] = 1;//��0���Ѿ�������2
	this->blockmark[0][2] = 1;//��0���Ź����Ѿ�������2
	this->now_num = 0;//�Ѿ����������վָ���Ϊ0
	this->out_num = 0;//Ҫ�����������վָ���Ϊ0
	this->out_pointer = 0;//�������ָ��Ϊ0
	this->out_su = NULL;//�����������Ϊ��

}

//���캯��������numΪҪ���ɵ������վ���
Sudoku::Sudoku(int num)
{
	memset(this->su, 0, sizeof(int));
	memset(this->rowmark, 0, sizeof(int));
	memset(this->colmark, 0, sizeof(int));
	memset(this->blockmark, 0, sizeof(int));

	this->su[0][0] = 2;//ѧ�ź���λΪ91,(9+1)%9+1=2
	this->rowmark[0][2] = 1;//��0���Ѿ�������2
	this->colmark[0][2] = 1;//��0���Ѿ�������2
	this->blockmark[0][2] = 1;//��0���Ź����Ѿ�������2
	this->now_num = 0;//�Ѿ����ɵ���������Ϊ0
	this->out_num = num;//Ҫ�����ɵ���������Ϊnum
	this->out_su = new int[81 * num];//�����������ĳ�ʼ������СΪ��������*81
	this->out_pointer = 0;//�����������ָ��Ϊ0
}

//���ڱ�ʶ������ÿһ�С��С��Ź��������������Ϣ
//����Ϊ���������������֡�flagΪҪ��ʶ����Ϣ��0����û�и����֣�1������ڸ����֣�����������������0��ʼ����
void Sudoku::SetMark(int row, int col, int num, int flag)
{
	this->rowmark[row][num] = flag;//flag=0����row�Ѿ���������num��flag=1����row����������num
	this->colmark[col][num] = flag;//flag=0����col�Ѿ���������num��flag=1����col����������num
	int blo = ((row / 3) * 3) + (col / 3);//�������������������ھŹ������ţ����Ϊ0-8�������ϵ�����
	this->blockmark[blo][num] = flag;//flag=0���Ź���blo�Ѿ���������num��flag=1���Ź���blo����������num
}


//������Ϊ-c�����������վ�ʱҪ���õ������������ܵĺ���
void Sudoku::MakeSudoku()
{
	int i = 0, j = 0;
	this->su[0][0] = 2;//ѧ�ź���λΪ91,(9+1)%9+1=2
	this->SetMark(0, 0, 2, 1);//0�С�0�м���Ӧ�Ź����Ѿ���������2
	this->create(0, 1);//�ӵ�0�е�1�п�ʼ���������վ�
}


// ��������һ���������վֵĺ���
void Sudoku::create(int o_row, int o_col)
{
	int row, col;
	row = o_row;
	col = o_col;

	//���������ɵ������վָ�������Ҫ�����ɵ������վָ���ʱ������
	if (this->now_num == this->out_num)
	{
		return;
	}

	//����һ�������վ�
	if (row == 8 && col == 9)
	{
		//�������վֵ�����Ҫ����������У��ȴ�������ļ�
		this->IntoOutSu();
		//�����������վָ�����һ
		this->now_num++;
		return;
	}

	//����
	if (row != 8 && col == 9)
	{
		row++;
		col = 0;
	}
	//���㵱ǰ�С��С���Ӧ�ľŹ�����
	int blo = ((row / 3) * 3) + (col / 3);
	for (int x = 1; x <= 9; x++)
	{
		//����x��Ҫ�����С��С��Ź����ж�������������x
		if ((this->rowmark[row][x] != 1) && (this->colmark[col][x] != 1) && (this->blockmark[blo][x] != 1))
		{
			//��x��������
			this->su[row][col] = x;
			//����С��С��Ź����Ѿ���������x
			SetMark(row, col, x, 1);
			//����+1�ݹ���ú���
			this->create(row, col + 1);
			//����С��С��Ź��񲻴�������x
			//��֤���ݺ�״̬Ҳ�ָ�
			SetMark(row, col, x, 0);
		}
	}
	//����x��1��9�ڵ�ǰλ�ö������ʣ�����ʱ�ѵ�ǰλ����������0
	this->su[row][col] = 0;
}


//���Ѿ����ɵ������վֻ�����������Ҫ�������������һ���ȴ�����������У�׼��һ�������
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

//�������ļ�����������վֵĺ���
void Sudoku::WriteSudoku()
{
	int i = 0;
	char path[20] = "./sudoku.txt";
	FILE* fp = NULL;

	fp = fopen(path, "w");

	if (fp == NULL)
	{
		printf("�����ļ�ʧ��\n");
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


//������Ϊ-s���������ʱҪ���õ������������ĺ���
void Sudoku::SolveSudoku(char* filename)
{
	FILE* question = NULL;
	question = fopen(filename, "r+");
	this->out_su = new int[1000000 * 81];
	if (question == NULL)
	{
		printf("���ļ�ʧ�ܣ���ȷ���Ƿ���ڸ��ļ���\n");
		exit(1);
	}
	else
	{	
		//����ȡ������ʱ
		while (this->ReadQuestion(question))
		{
			//����������ӵ�0�е�0�п�ʼ
			if (this->solve(0, 0))
			{
				//����������������׼�������������
				this->IntoOutSu();
			}
		}
	}
	//�ر��ļ�
	fclose(question);

}

//����������⣬SolveSudoku()Ҫ���õĺ���
bool Sudoku::solve(int i, int j)
{
	//�������һ������ʱ������
	if (i == 8 && j == 9)
	{
		return true;
	}

	//����
	if (i != 8 && j == 9)
	{
		i++;
		j = 0;
	}

	//���������ַ�0
	if (this->su[i][j] != 0)
	{
		//ֱ�ӻ�����һ�����ֵ����
		return this->solve(i, j + 1);
	}
	//��������������ȷ���Ź�����
	int blo = ((i / 3) * 3) + (j / 3);
	for (int x = 1; x <= 9; x++)
	{
		//�������С��С��Ź��񶼲�����xʱ
		if ((this->rowmark[i][x] != 1) && (this->colmark[j][x] != 1) && (this->blockmark[blo][x] != 1))
		{
			this->su[i][j] = x;
			//����С��С��Ź����Ѿ�����x
			SetMark(i, j, x, 1);
			//�ݹ��������
			bool flag = this->solve(i, j + 1);

			if (flag)
			{
				return true;
			}
			//����С��С��Ź��񲻴�������x
			//��֤���ݺ�״̬Ҳ�ָ�
			SetMark(i, j, x, 0);
		}
	}
	//��λ������1-9�������ʣ���ʱ��Ϊ0
	this->su[i][j] = 0;
	return false;
}

//�Ӹ��������������ļ��ж�ȡ�������⣬SolveSudoku()Ҫ���õĺ���
bool Sudoku::ReadQuestion(FILE* question)
{
	//������С��С��Ź�������鶼��0��������һ��������Ӱ��
	memset(this->rowmark, 0, sizeof(this->rowmark));
	memset(this->colmark, 0, sizeof(this->colmark));
	memset(this->blockmark, 0, sizeof(this->blockmark));
	char content[20];
	int flag = 0;
	int k = 0, j = 0;
	for (int i = 0; i < 9;)
	{
		//��ȡ�ļ�����Ϊ��
		if (fgets(content, 20, question) == NULL)
		{
			return false;
		}

		//��������������֮����ڿո�k+=2
		for (k = 0, j = 0; k <= 16; k += 2, j++)
		{
			flag = 0;
			if (content[k] >= '0' && content[k] <= '9')
			{
				int num = content[k] - '0';
				this->su[i][j] = num;
				//��Ǵ���
				SetMark(i, j, num, 1);
				//��ʾ��һ���������֣������ǿո�
				flag = 1;
			}
		}
		//������Ϊ����ʱ�������ż�һ
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