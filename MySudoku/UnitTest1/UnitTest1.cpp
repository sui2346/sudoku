#include "pch.h"
#include "CppUnitTest.h"
#include"../MySudoku/stdafx.h"
#include"../MySudoku/Sudoku.cpp"
#include"../MySudoku/InputControl.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		int argc;
		char **argv1,**argv2;
		UnitTest1()
		{
			argc = 3;
			argv1 = new char* [3];
			argv2 = new char* [3];

			for (int i = 0; i < 3; i++)
			{
				argv1[i] = new char[30];
				argv2[i] = new char[30];
			}

			strcpy_s(argv1[0], 30, "sudoku.exe");
			strcpy_s(argv1[1], 30, "-c");
			strcpy_s(argv1[2], 30, "1000");

			strcpy_s(argv2[0], 30, "sudoku.exe");
			strcpy_s(argv2[1], 30, "-s");
			strcpy_s(argv2[2], 30, "q2.txt");

		}

		//测试函数ParameterProcess(),参数为-c时
		TEST_METHOD(TestMethod1)
		{
			Input inputs(argc, argv1);
			inputs.ParameterProcess();
			Assert::AreEqual(inputs.GetNum() == 1000, true);
			Assert::AreEqual(inputs.GetType() == 'c', true);
		}
		
		//测试函数ParameterProcess(), 参数为 - s时
		TEST_METHOD(TestMethod2)
		{
			Input inputs(argc, argv2);
			inputs.ParameterProcess();
			Assert::AreEqual(inputs.GetType() == 's', true);
			Assert::AreEqual(strcmp("q2.txt", inputs.GetFileName()), 0);
		}
		
		//测试函数ParameterProcess()，命令行参数不是2个
		TEST_METHOD(TestMethod3)
		{
			argc = 2;
			Input inputs(argc, argv1);
			Assert::AreEqual(inputs.GetType() == 'n', true);
			//'n'代表没有类别，表示没有输入正确的参数-c和-s
		}

		//测试函数ParameterProcess()，参数不是-c和-s
		TEST_METHOD(TestMethod4)
		{
			argv1[1][1] = 'x';
			Input inputs(argc, argv1);
			Assert::AreEqual(inputs.GetType() == 'n', true);
			//'n'代表没有类别，表示没有输入正确的参数-c和-s
		}

		//测试-c时输入的数量
		TEST_METHOD(TestMethod5)
		{
			argv1[2][0] = '-';
			argv1[2][1] = '1';
			Input inputs(argc, argv1);
			Assert::AreEqual(inputs.GetNum() == 0, true);
		}

		//测试生成数独MakeSudoku()函数
		TEST_METHOD(TestMethod6)
		{
			strcpy_s(argv1[2], 30, "1");
			Input inputs(argc, argv1);
			inputs.ParameterProcess();
			Sudoku sudokus(inputs.GetNum());
			sudokus.MakeSudoku();
			int x;
			x = sudokus.GetOne();
			Assert::AreEqual(2, x);
		}

		//测试求解数独函数SolveSudoku()
		TEST_METHOD(TestMethod7)
		{
			Input inputs(argc, argv2);
			inputs.ParameterProcess();
			Sudoku sudokus;
			sudokus.SolveSudoku(inputs.GetFileName());
			int x=sudokus.GetOne();
			int y = sudokus.GetTwo();
			Assert::AreEqual(2, x);
			Assert::AreEqual(5, y);
		}
	};
}
