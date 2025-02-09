#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>
#include <stack>
#include <share.h>
#include <errno.h>
#include <fstream>
#include <sstream> 
#include<vector>
using namespace std;

const char* text; //读取的被查询的文献
const char* lib;  // 保存读取的库文件
const char* textStr;

#define N 100

struct textStruct {

	string textSentence; // 保存句子的内容

	int wordCount; // 该句子单词的个数

};

int sentenceSplitlib(textStruct textStruct[])
{
	int wordCount = 0; //  统计单词的个数

	int num = 0; // 句子的个数

	string tempSentence; // 用于存储当前处理的句子

	string Word; //临时存储单词

	// 读取文件
	//string txt = read();
	std::string filename = "lib.txt"; // 替换为你的文件名  
	std::string libtxt;
	std::ifstream file(filename);

	// 检查文件是否成功打开  
	if (!file.is_open()) {
		std::cerr << "无法打开文件: " << filename << std::endl;
		return 1;
	}

	// 读取文件内容到字符串中  
	std::stringstream buffer;
	buffer << file.rdbuf(); // 使用rdbuf()读取文件缓冲区  
	libtxt = buffer.str(); // 获取字符串流中的字符串  

	// 关闭文件  
	file.close();

	//cout << "libtxt" << libtxt;

	textStr = libtxt.c_str(); // 转换成字符数组

	for (int k = 0; k < strlen(textStr); k++)
	{

		//int last = 0;// 记录句子最后一个字符的下标

		if ((textStr[k] >= 'a') && (textStr[k] <= 'z') || (textStr[k] >= 'A') && (textStr[k] <= 'Z'))
		{
			//tempSentence += textStr[k];
			Word += textStr[k];
		}
		if ((textStr[k + 1] < 'A') || ((textStr[k + 1] > 'Z') && (textStr[k + 1] < 'a')) || (textStr[k + 1] > 'z'))
		{
			if (Word != "")
			{
				wordCount++;

				tempSentence += Word + " ";

				Word = "";  // 重置
			}
		}
		if ((textStr[k] == '.') || (textStr[k] == '?') || (textStr[k] == '!'))
		{

			transform(tempSentence.begin(), tempSentence.end(), tempSentence.begin(), ::tolower);
			textStruct[num].textSentence = tempSentence;
			textStruct[num].wordCount = wordCount;
			tempSentence = ""; // 重置临时句子
			wordCount = 0; //重置
			num++;
		}

	}
	return num;

}

int sentenceSplittext(textStruct textStruct[])
{
	int wordCount = 0; //  统计单词的个数

	int num = 0; // 句子的个数

	string tempSentence; // 用于存储当前处理的句子

	string Word; //临时存储单词

	// 读取文件
	//string txt = read();
	std::string filename = "text.txt"; // 替换为你的文件名  
	std::string texttxt;
	std::ifstream file(filename);

	// 检查文件是否成功打开  
	if (!file.is_open()) {
		std::cerr << "无法打开文件: " << filename << std::endl;
		return 1;
	}

	// 读取文件内容到字符串中  
	std::stringstream buffer;
	buffer << file.rdbuf(); // 使用rdbuf()读取文件缓冲区  
	texttxt = buffer.str(); // 获取字符串流中的字符串  

	// 关闭文件  
	file.close();

	textStr = texttxt.c_str(); // 转换成字符数组

	for (int k = 0; k < strlen(textStr); k++)
	{

		//int last = 0;// 记录句子最后一个字符的下标

		if ((textStr[k] >= 'a') && (textStr[k] <= 'z') || (textStr[k] >= 'A') && (textStr[k] <= 'Z'))
		{
			//tempSentence += textStr[k];
			Word += textStr[k];
		}
		if ((textStr[k + 1] < 'A') || ((textStr[k + 1] > 'Z') && (textStr[k + 1] < 'a')) || (textStr[k + 1] > 'z'))
		{
			if (Word != "")
			{
				wordCount++;

				tempSentence += Word + " ";

				Word = "";  // 重置
			}
		}
		if ((textStr[k] == '.') || (textStr[k] == '?') || (textStr[k] == '!'))
		{

			transform(tempSentence.begin(), tempSentence.end(), tempSentence.begin(), ::tolower);
			textStruct[num].textSentence = tempSentence;
			textStruct[num].wordCount = wordCount;
			tempSentence = ""; // 重置临时句子
			wordCount = 0; //重置
			num++;
		}

	}
	return num;
}

namespace sentenceTools {

	int wordSplit(string sentence, string wordList[])
	{
		int m = 0;

		string Word;

		text = sentence.c_str(); //转化成字符数组

		for (int k = 0; k < strlen(text); k++)
		{
			if ((text[k] >= 'a') && (text[k] <= 'z') || (text[k] >= 'A') && (text[k] <= 'Z'))
			{
				Word += text[k];
			}
			if ((text[k + 1] < 'A') || ((text[k + 1] > 'Z') && (text[k + 1] < 'a')) || (text[k + 1] > 'z'))
			{
				if (Word != "")
				{
					wordList[m] = Word;

					m++;

					Word = "";  // 重置
				}
			}

		}
		return m;
	}
}

string tempWord, libWord; // 表示从tempSentence与libSentence分别取的单词

void dynamicAlgorithm(int** wordSimilarity, float** score, int*** max_insert_space)
{
	int k = 0;

	//读取
	textStruct text[500];
	textStruct lib[500];

	int textCount = sentenceSplittext(text);

	int libCount = sentenceSplitlib(lib);

	int*** insert_space = new int** [60];
	for (int i = 0; i < 60; i++)
	{
		insert_space[i] = new int* [60];
		for (int j = 0; j < 60; j++)
		{
			insert_space[i][j] = new int[2];
			insert_space[i][j][0] = 0;
			insert_space[i][j][1] = 0;
		}
	}
	
	for (k = 0; k < textCount; k++)
	{
		string* tempWord = new string[text[k].wordCount];  // 存储tempSentence中的单词

		sentenceTools::wordSplit(text[k].textSentence, tempWord); //得到当前句子的所有单词

		float maxSimilarity = 1000;

		//记录相似句子的下标
		int simIndex = 0;
		int libsimIndex = 0;
		
		for (int x = 0; x < libCount; x++)
		{
			string* libWord = new string[lib[x].wordCount]; // 存储libSentence中的单词
			sentenceTools::wordSplit(lib[x].textSentence, libWord); //得到lib文件中句子的全部单词

			//得出相似矩阵：--->这个句子与当前lib中的句子
			for (int r = 0; r < text[k].wordCount; r++)
			{
				for (int t = 0; t < lib[x].wordCount; t++)
				{
					wordSimilarity[r][t] = 0;
				}
			}

			//计算score

			int m = text[k].wordCount; // 两个句子的单词数 
			int n = lib[x].wordCount;

			
			for (int i = 0; i < m; i++)
			{
				score[i][0] = i;
			}
			for (int i = 0; i < n; i++)
			{
				score[0][i] = i;
			}
			
			for (int i = 1;i <= m;++i) 
			{
				for (int j = 1;j <= n;++j) 
				{
					if (tempWord[i - 1] == libWord[j - 1])
					{
						score[i][j] = score[i - 1][j - 1];
						insert_space[i][j][0] = i - 1;
						insert_space[i][j][1] = j - 1;
					}
					else
					{
						score[i][j] = 1 + min(score[i - 1][j - 1], min(score[i][j - 1], score[i - 1][j]));
						if (score[i][j] == score[i - 1][j - 1] - 1)
						{
							insert_space[i][j][0] = i - 1;
							insert_space[i][j][1] = j - 1;
						}
						else if (score[i][j] == score[i][j - 1] - 1)
						{
							insert_space[i][j][0] = i-1;
							insert_space[i][j][1] = j;
						}
						else if (score[i][j] == score[i-1][j] - 1)
						{
							insert_space[i][j][0] = i;
							insert_space[i][j][1] = j-1;
						}
					}
				}
			}
			
			if (maxSimilarity > score[m][n])
			{
				for (int i = 0; i < m; i++)
				{
					for (int j = 0; j < n; j++)
					{
						max_insert_space[i][j][0] = insert_space[i][j][0];
						max_insert_space[i][j][1] = insert_space[i][j][1];
					}
				}
				maxSimilarity = score[m][n];
				simIndex = k;
				libsimIndex = x;
			}
		}
		
		int mm = text[simIndex].wordCount;
		int nn = lib[libsimIndex].wordCount;

		stack<int*> insert_space_stack;
		insert_space_stack.push(new int[2]);
		insert_space_stack.top()[0] = mm - 1;
		insert_space_stack.top()[1] = nn - 1;

		//回溯过程
		for (int i = mm - 1, j = nn - 1; i > 0 && j > 0;)
		{
			insert_space_stack.push(max_insert_space[i][j]);
			int temp = i;
			i = max_insert_space[temp][j][0];
			j = max_insert_space[temp][j][1];
		}
		
		string new_text;
		string new_lib_text;

		string* tWord = new string[text[simIndex].wordCount];  // 存储tempSentence中的单词
		string* libWord = new string[lib[libsimIndex].wordCount];  // 存储tempSentence中的单词


		sentenceTools::wordSplit(text[simIndex].textSentence, tWord); //得到当前句子的所有单词
		sentenceTools::wordSplit(lib[libsimIndex].textSentence, libWord); //得到当前句子的所有单词
		
		int i, j, before_i = -1, before_j = -1;
		while (!insert_space_stack.empty()) {
			i = insert_space_stack.top()[0];
			j = insert_space_stack.top()[1];
			if (i != before_i && j != before_j) {
				new_text.append(tWord[i] + ' ');
				new_lib_text.append(libWord[j] + ' ');
				int w = tWord[i].size() - libWord[j].size();
				while (w > 0) {
					new_lib_text.append(" ");
					w--;
				}
				while (w < 0) {
					new_text.append(" ");
					w++;
				}
			}
			else if (i == before_i)
			{
				new_lib_text.append(libWord[j] + ' ');
				for (int l = 0; l <= libWord[j].size(); l++)
				{
					new_text.append(" ");
				}
			}
			else if(j == before_j)
			{
				new_text.append(tWord[i] + ' ');
				for (int l = 0; l <= tWord[i].size(); l++)
				{
					new_lib_text.append(" ");
				}
			}

			before_i = i;
			before_j = j;

			insert_space_stack.pop();
		}

		float percent = ((libCount - maxSimilarity) / libCount)*100;

		std::cout << endl << "text中的第" << simIndex + 1 << "句话与lib中的第" << libsimIndex + 1 << "句话相似度最高，相似度为：" << percent << "%" << endl;
		std::cout << "文本对照结果：" << endl;
		std::cout << new_text << endl << new_lib_text << endl << endl;
	}
}

int main()
{
	textStruct text[100];
	textStruct lib[100];

	int textCount = sentenceSplittext(text);

	std::cout << "text中句子的个数为：" << textCount << endl;

	int libCount = sentenceSplitlib(lib);

	std::cout << "lib中句子的个数为：" << libCount << endl;

	//二维数组
	int** wordSimilarity = new int* [60];
	float** score = new float* [60];
	int*** insert_space = new int** [60];
	for (int i = 0; i < 60; i++)
	{
		wordSimilarity[i] = new int[60];
		score[i] = new float[60];
		insert_space[i] = new int* [60];
		for (int j = 0; j < 60; j++)
		{
			insert_space[i][j] = new int[2];
			insert_space[i][j][0] = 0;
			insert_space[i][j][1] = 0;
		}
	}

	//初始化
	for (int i = 0; i < 60; i++)
	{
		for (int j = 0; j < 60; j++)
		{
			wordSimilarity[i][j] = 0;
			score[i][j] = 0;
		}

	}

	dynamicAlgorithm(wordSimilarity, score, insert_space);

	return 0;
}