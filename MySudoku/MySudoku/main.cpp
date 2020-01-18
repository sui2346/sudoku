#include"stdafx.h"
using namespace std;

int main(int argc, char* argv[])
{
	Input inputs(argc, argv);
	//����������жϲ����Ƿ���ȷ
	inputs.ParameterProcess();
	clock_t start_time = 0, end_time = 0, output_time = 0;
	char type = inputs.GetType();
	if (type == 'c')
	{
		//���Ҫ���ɵ������վֵ�����
		int Num = inputs.GetNum();
		Sudoku sudokus(Num);
		//��¼��ʼʱ��
		start_time = clock();
		//�����վ�
		sudokus.MakeSudoku();
		//��¼�����վֽ���ʱ��
		end_time = clock();
		//���վ�������ļ�
		sudokus.WriteSudoku();
		//��¼�����ɵ�ʱ��
		output_time = clock();
	}
	if (type == 's')
	{

		Sudoku sudokus;
		//���������Ŀ���ļ���
		char* Filename = inputs.GetFileName();
		//��¼��ʼʱ��
		start_time = clock();
		//�����������
		sudokus.SolveSudoku(Filename);
		//��¼����ʱ��
		end_time = clock();
		//��������վ�
		sudokus.WriteSudoku();
		//��¼������ʱ��
		output_time = clock();

	}
	cout << "\n�����վ���ʱ��" << end_time - start_time << " ms" << endl;
	cout << "������ı���ʱ��" << output_time - end_time << " ms" << endl;
	return 0;

}