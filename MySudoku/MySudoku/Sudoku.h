#pragma once
//���ڱ�ʾ��������
class Sudoku {
public:
	Sudoku();//���캯��
	Sudoku(int num);//���캯��
	void MakeSudoku();//������Ϊ-c�����������վ�ʱҪ���õ������������ܵĺ���
	void WriteSudoku();//�������ļ�����������վֵĺ���
	void SetMark(int row, int col, int block, int flag);//���ڱ�ʶ������ÿһ�С��С��Ź��������������Ϣ
	void create(int o_row, int o_col);//��������һ���������վֵĺ���
	void IntoOutSu();//���Ѿ����ɵ������վֻ�����������Ҫ�������������һ���ȴ�����������У�׼��һ�������
	void SolveSudoku(char* filename);//������Ϊ-s���������ʱҪ���õ������������ĺ���
	bool ReadQuestion(FILE*);//�Ӹ��������������ļ��ж�ȡ�������⣬SolveSudoku()Ҫ���õĺ���
	bool solve(int i, int j);//����������⣬SolveSudoku()Ҫ���õĺ���
	int GetOne();//���ڲ��Ե�һ������
	int GetTwo();//���ڲ��Ե�һ������
private:
	int su[9][9];//��������������
	int now_num;//�����Ѿ����ɵ���������
	int out_num;//��Ҫ���ɵ���������
	int rowmark[9][10];//rowmark[i][j]��i���Ѿ���������j
	int colmark[9][10];//colmark[i][j]��i���Ѿ���������j
	int blockmark[9][10];//blockmark[i][j]��i���Ź����Ѿ���������j
	int* out_su;//����������õ�����
	int out_pointer;//�������ָ��
};
