#pragma once

//��ʾ�������ݵ���
class Input {
public:
	void ParameterProcess();//��������ĺ���
	Input(int a, char** b);//���캯��
	char GetType();//�����������ͣ�-c��-s��
	int GetNum();//���Ҫ��������������
	char* GetFileName();//���������Ŀ���ļ���
private:
	int argcs;//�����в�������
	char** argvs;//�����в���
	char type;//��������-c��-s
	int num;//Ҫ���������վֵĸ���
	char* filename;//������Ŀ���ļ���
};


