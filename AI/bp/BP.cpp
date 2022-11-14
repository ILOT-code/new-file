#include<cstdio>
#include<ctime>
#include<fstream>
#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;

const double INF = 1000000;	//定义无穷大
const int inputnum = 784;  	//输入层结点数
const int hiddennum = 200;  	//隐藏层节点数
const int outputnum = 10;  	//输出层节点数
const double alpha = 0.25; 	//学习率

int input[inputnum];      	 //输入,原始像素点映射到0或1
int expected[outputnum];   	//期望输出，即label
double output1[hiddennum]; 	//隐藏层结点输出值
double output2[outputnum]; 	//输出层结点输出值
double delta1[hiddennum]; 	//前文已介绍，为方便更新而设置的数组
double delta2[outputnum];
double w1[inputnum][hiddennum];  //输入层与隐藏层之间全连接的权重矩阵
double w2[hiddennum][outputnum]; //隐藏层与输出层之间全连接的权重矩阵
double b1[hiddennum];            //隐藏层偏置
double b2[outputnum];            //输出层偏置

double _g(double x) { return 1.0 / (1.0 + exp(-x)); } //激励函数，取sigmod函数
//正向传播函数
void forward() {
	//从输入层传到隐藏层
	for (int j = 0; j < hiddennum; j++) {
		double temp = 0;
		for (int i = 0; i < inputnum; i++)
			temp += input[i] * w1[i][j];
		output1[j] = _g(temp + b1[j]);
	}
	//从隐藏层传到输出层
	for (int k = 0; k < outputnum; k++) {
		double temp = 0;
		for (int j = 0; j < hiddennum; j++)
			temp += output1[j] * w2[j][k];
		output2[k] = _g(temp + b2[k]);
	}
}
//计算delta数组
void cal_delta() {
	//按照文中给出的结论给出的方式计算data[2]
	for (int k = 0; k < outputnum; k++)
		delta2[k] = output2[k] * (1.0 - output2[k]) * (expected[k] - output2[k]);
	//按照文中给出的结论给出的方式计算data[1]
	for (int j = 0; j < hiddennum; j++) {
		double temp = 0;
		for (int k = 0; k < outputnum; k++)
			temp += w2[j][k] * delta2[k];
		delta1[j] = (output1[j]) * (1.0 - output1[j]) * temp;
	}
}
//反向传播
void backward() {
	//对输出层的偏置以及隐藏层与输出层之间的权重矩阵进行更新
	for (int k = 0; k < outputnum; k++) {
		b2[k] = b2[k] + alpha * delta2[k];
		for (int j = 0; j < hiddennum; j++)
			w2[j][k] = w2[j][k] + alpha * output1[j] * delta2[k];
	}
	//对隐藏层的偏置以及输入层与隐藏层之间的权重矩阵进行更新
	for (int j = 0; j < hiddennum; j++) {
		b1[j] = b1[j] + alpha * delta1[j];
		for (int i = 0; i < inputnum; i++)
			w1[i][j] = w1[i][j] + alpha * input[i] * delta1[j];
	}
}
//随机初始化各参数
void init() {
	srand((int)time(0) + rand());
	for (int i = 0; i < inputnum; i++)
		for (int j = 0; j < hiddennum; j++)
			w1[i][j] = rand() % 1000 * 0.001 - 0.5;

	for (int j = 0; j < hiddennum; j++)
		for (int k = 0; k < outputnum; k++)
			w2[j][k] = rand() % 1000 * 0.001 - 0.5;

	for (int j = 0; j < hiddennum; j++)
		b1[j] = rand() % 1000 * 0.001 - 0.5;

	for (int k = 0; k < outputnum; k++)
		b2[k] = rand() % 1000 * 0.001 - 0.5;
}
//训练模块
void training(int train_num) {
	clock_t begin, end;   		//计时
	begin = clock();
	FILE *images = fopen("./data/train-images.idx3-ubyte", "rb"); //打开训练用图片文件
	FILE *labels = fopen("./data/train-labels.idx1-ubyte", "rb"); //打开训练用标签文件

	unsigned char image_buf[784], label_buf[1];  	//缓存区，每次读取一张(784)字节的图片以及1字节的标签
	unsigned char basetext[100];					//存入每个文件前面的描述基本信息的字节
	fread(basetext, 1, 16, images);					//图片文件前16个字节描述基本信息
	fread(basetext, 1, 8, labels);					//标签文件前8个字节描述基本信息

	int cnt = 0;									//训练计数器
	printf("Start training.\n");

	while (!feof(images) && !feof(labels)) {
		//每次读取一张图片与标签
		fread(image_buf, 1, 784, images);
		fread(label_buf, 1, 1, labels);
		//对原始图片黑白化处理
		for (int i = 0; i < 784; i++)
			input[i] = image_buf[i] < 128 ? 0 : 1;
		//给出期望的输出
		int expected_num = (unsigned int)label_buf[0];			//储存标签
		for (int k = 0; k < outputnum; k++) expected[k] = 0;
		expected[expected_num] = 1;

		forward();		//正向传输
		cal_delta();	//计算delta数组
		backward();		//反向传播

		if ((++cnt) % 10000 == 0) printf("has trainning %d images.\n", cnt);
		if (cnt == train_num) break;		//达到规定次数，退出
	}
	end = clock();
	printf("The training time for %d pictures is %.4lf s\n\n", train_num, double(end - begin) / CLOCKS_PER_SEC);
}

void testing(int test_num) {
	clock_t begin, end;		//计时
	begin = clock();
	FILE *images = fopen("./data/t10k-images.idx3-ubyte", "rb"); //打开测试用图片文件
	FILE *labels = fopen("./data/t10k-labels.idx1-ubyte", "rb"); //打开测试用标签文件

	unsigned char image_buf[784], label_buf[1];  	//缓存区，每次读取一张(784)字节的图片以及1字节的标签
	unsigned char basetext[1000];					//存入每个文件前面的描述基本信息的字节
	fread(basetext, 1, 16, images);					//图片文件前16个字节描述基本信息
	fread(basetext, 1, 8, labels);                  //标签文件前8个字节描述基本信息

	int success_cnt = 0, tot_cnt = 0;				//测试成功数的计数器和总测试数的计数器
	while (!feof(images) && !feof(labels)) {
		//每次读取一张图片与标签
		fread(image_buf, 1, 784, images);
		fread(label_buf, 1, 1, labels);
		//对原始图片黑白化处理
		for (int i = 0; i < 784; i++)
			input[i] = image_buf[i] < 128 ? 0 : 1;
		//给出期望的输出
		int expected_num = (unsigned int)label_buf[0];			//储存标签
		for (int k = 0; k < outputnum; k++) expected[k] = 0;
		expected[expected_num] = 1;

		forward();   		//正向传播，计算输出值
		//得到输出层输出值最大的结点，也就是网络预测的值
		double max_value = -INF;
		int idx = 0;
		for (int k = 0; k < outputnum; k++) {
			if (output2[k] > max_value) {
				max_value = output2[k];
				idx = k;
			}
		}

		if (expected[idx] == 1) success_cnt++;	//预测成功
		tot_cnt++;
		if (tot_cnt == test_num) break;			//达到测试次数，退出
	}
	end = clock();
	printf("The testing time for %d pictures is %.4lf s\n\n", test_num, double(end - begin) / CLOCKS_PER_SEC);
	printf("The success rate is %.4lf\n", (double)success_cnt / (double)tot_cnt);
}

int main() {
	init();
	training(60000);
	testing(10000);
}