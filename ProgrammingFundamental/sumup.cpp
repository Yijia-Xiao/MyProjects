#include<iostream>
#include<ctime>
#include<cstdlib>
#include<windows.h>
#include<cstring>
#include <stdio.h>
#include<bits/stdc++.h>
#include "math.h"
#include <iostream>
#define LENGTH_NAME_BMP 50
#include<queue>

//bmp图片文件名的最大长度--50以内
using namespace std;
//system("CLS");

int m,n;
//the scale of the digit puzzle
const int sleept=20;

int a[200][200];
//the array used for storing the current state of the board
int prim[200][200];
//the array used for Function"R"--restart the game to the initial state
int pri[200][200];
//this is used to check the correctness of the current state
int random[40000];
//the array is used for generating the random numbers
int save_num=0; 
//the counter used for storing how many records the user has
int rec_num=0;
//the counter used to determine the order number of the target record
void welcome();
 void bye();
//cout welcome info
bool Solvable();
//judge whether the puzzle is solable
char strFile[LENGTH_NAME_BMP];
//the name of the picture
void GenerateRandom();
//the function swap the items of the array to produce random number
void ReGenerateRandom();
//if the current array is not solvable, this function ReGenerate another
int blankX();
//this function i used to locate the x coordinate of the blank
int blankY();
//this function i used to locate the y coordinate of the blank
int targetX(int id);
//This function determines the x coordinates of each target block
int targetY(int id);
////This function determines the y coordinates of each target block
void Print();
void Prin();
void intiPri();
//print out the current state
void Simple();
void Recover();
void up(int step);
//move the blank up "step" times
void left(int step);
//move the blank left "step" times
void down(int step);
//move the blank down "step" times
void right(int step);
//move the blank right "step" times

void mov_up(int step);
void mov_left(int step);
void mov_right(int step);
//for the target piece of number

void blank_up(int id);
void blank_right(int id);
void blank_left(int id);


void readPic();
//read the picture into the program
void PrintPic();
//move the blank in a direction continuously "step" times
struct Rec{
	char name[200];
	int rec[200][200];
} record[50] ;
//used for storing the users' records
//max volume is 50




int main()
{
	
	//READ THE FIGURE
	//读图
	
	welcome();
	
	
	
	//int m,n;
	cout<<"请输入拼图的行数和列数:\n";
	cout<<"行数:\n";
	cin>>m;
	cout<<"列数:\n";
	cin>>n;
	
	
	GenerateRandom();
	
	intiPri();

	
	readPic();
	
	//可行性 
	{
		if(Solvable())
			cout<<"嗨！真不错！此数表可解~\n";
		else
			cout<<"咦~好像解不了~\n";
			cout<<"您可以输入Q来重新生成随机数表！"; 
			cout<<endl;
			
	}
	
	//打印状态 
	cout<<endl;Print() ;
	Sleep(30);
//	system("CLS");
	//输入指令 
	
	char Inp;
	cin>>Inp;
	while(Inp!='P')
	{
		//TEST
		//TEST the effectiveness of all the newly written functions 
		if(Inp=='U')
		{
			//Recover();
			int t;
			cin>>t;
			while(t) 
			{
				int x=targetX(t);
				int y=targetY(t);
				
				blank_left(t);
				cout<<"Re"<<endl;
				cout<<endl;Print() ;
				cin>>t;
			}
			
		}
		if(Inp=='W'||Inp=='A'||Inp=='S'||Inp=='D')
		{
			int x=blankX();
			int y=blankY();
			{
				if(Inp=='W')
				{
					if(x==0)
					{
						cout<<"非法输入！空格已经在最上方了，再试试~\n";
					}
					else
					{
						swap(a[x][y],a[x-1][y]);
						cout<<endl;Print() ;
					}
				}
				
				if(Inp=='S')
				{
					if(x==m-1)
					{
						cout<<"非法输入！空格已经在最下方了，再试试~\n";
					}
					else
					{
						swap(a[x][y],a[x+1][y]);
						cout<<endl;Print() ;
					}
				}
				
				if(Inp=='A')
				{
					if(y==0)
					{
						cout<<"非法输入！空格已经在最左方了，再试试~\n";
					}
					else
					{
						swap(a[x][y],a[x][y-1]);
						cout<<endl;Print() ;
					}
				}
				
				if(Inp=='D')
				{
					if(y==n-1)
					{
						cout<<"非法输入！空格已经在最右方了，再试试~\n";
					}
					else
					{
						swap(a[x][y],a[x][y+1]);
						cout<<endl;Print() ;
					}
				}
			}
		}
		
		
		else
		{
			if(Inp=='C')
			{
				system("CLS");
			}
			if(Inp=='R')
			{
				for(int i=0;i<m;i++)
				for(int j=0;j<n;j++)
				a[i][j]=prim[i][j];
				cout<<endl;Print() ;
				cout<<"好的，现在我们恢复到开始的状态，加油！！\n";
			}
			
			if(Inp=='I')
			{
				save_num++;
				cout<<"请输入存档名称：\n";
				cin>>record[save_num].name;
				for(int i=0;i<m;i++)
				for(int j=0;j<n;j++)
				record[save_num].rec[i][j]=a[i][j];
				cout<<"存档成功！您可以输入O，来读取历史存档！\n";
			}
			
			if(Inp=='O')
			{
				cout<<"请输入存档的名称：\n";
				char temp_name[200];
				cin>>temp_name;
				for(int i=1;i<save_num+3;i++)
				{
					if(strcmp(record[i].name,temp_name)==0)
					rec_num=i;
				}
				
				if(rec_num==0)
					cout<<"名称错误，请输入O后，再试试名称\n";
				else
				{
					for(int i=0;i<m;i++)
					for(int j=0;j<n;j++)
					a[i][j]=record[rec_num].rec[i][j];
						cout<<"读档成功！加油！\n";
					cout<<endl;Print() ;
				}
			}
			
			//若随机数表不可恢复，重新生成 
			if(Inp=='Q')
			{
			//	void ReGenerateRandom();
			//DECLARATION
				ReGenerateRandom();
				cout<<"好的，我们重新生产了一张随机数表！\n\n";
				cout<<endl;Print() ;
				{
				if(Solvable())
					cout<<"\n嗨！真不错！此数表可解~\n";
				else
					cout<<"\n咦~好像解不了~\n";
				}
			}
			
			if(Inp=='F')
			{
				Recover();
				cout<<endl<<endl;
				cout<<endl;Print() ;
				
				//cout<<"\n\n以上就是复原方案，加油哦！\n\n";
			}
			
			if(Inp=='G')
			{
				PrintPic();
			}
		}
		
		cin>>Inp;
		
		if(Inp=='P')
		{
			bye();
		}
	
	}
	
}


bool Solvable()
{
	int reverse=0;
	for(int i=0;i<m*n-2;i++)
	{
		for(int j=i+1;j<m*n-1;j++)
		{
			if(random[i]>random[j])
				reverse++;
			
	//		cout<<reverse<<"---"<<random[i]<<endl<<random[j]<<"!!"<<endl;
		}
	//	cout<<"Random"<<i<<"--"<<random[i]<<endl<<endl;
	}
	//cout<<"REVERSE--Solvable:\n"<<reverse<<endl;
	if(((reverse+blankX()+blankY())%2)==((m+1)*(n+1))%2)
		return true;
	else
		return false;
}


void GenerateRandom()
{
	for (int i = 0; i < m*n-1; i++)
		random[i] = i;
	random[m*n - 1] = -1;
	srand(time(0));
	
	
	int p=rand() % (m*n-1);
	while(p<(m*n/2))
		p=rand() % (m*n-1);
	
	int l=m*n-1;
	
	while(p--)
	{
		swap(random[rand()%l],random[rand()%l]);
	}
	
//	for (int i = 0; i <p; i++)
//	{
//		srand(time(0));
//		int t = rand() % (m*n-1);
//		swap(random[i], random[t]);
//	}
//	for (int i = p+1; i <m*n-1; i++)
//	{
//		srand(time(0));
//		int t = rand() % (m*n-1);
//		swap(random[i], random[t]);
//	}
	int ctr=0;
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
		{
			a[i][j]=random[ctr++];
			prim[i][j]=a[i][j];
		}
	//for(int i=0;i<m*n;i++)
		
}


int blankX()
{
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(a[i][j]==-1)
			return i;
		}
	}
	cout<<endl;Print() ;
}


void ReGenerateRandom()
{
	//srand(time(0));
	for (int i = 0; i < m*n-1; i++)
		random[i] = i;
	random[m*n - 1] = -1;
	
	
	
	int p=rand() % (m*n-1);
	while(p<(m*n/2))
		p=rand() % (m*n-1);	
	
	int l=m*n-1;
	
	while(p--)
	{
		swap(random[rand()%l],random[rand()%l]);
	}
	int ctr=0;
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
		{
			a[i][j]=random[ctr++];
			prim[i][j]=a[i][j];
		}
}




int blankY()
{
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(a[i][j]==-1)
			return j;
		}
	}
	cout<<endl;Print() ;
}


void Print()
{
	Sleep(sleept);
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			cout<<a[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<"\n\n"; 
}
void Prin()
{
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
				cout<<prim[i][j]<<"\t";
			cout<<endl;
		}
		}
void up(int step)
{
	int x=blankX();
	int y=blankY();
	for(int i=1;i<=step;i++)
	{
		swap(a[x][y],a[x-1][y]);
		x--;
		cout<<'W'<<" ";
		cout<<endl;Print() ;
	}
}

void down(int step)
{
	int x=blankX();
	int y=blankY();
	for(int i=1;i<=step;i++)
	{
		swap(a[x][y],a[x+1][y]);
		x++;
		cout<<'S'<<" ";
		cout<<endl;cout<<endl;Print() ;
	}
}

void left(int step)
{
	int x=blankX();
	int y=blankY();
	for(int i=1;i<=step;i++)
	{
		swap(a[x][y],a[x][y-1]);
		y--;
		cout<<'A'<<" ";
		cout<<endl;cout<<endl;Print() ;
	}
}


void right(int step)
{
	int x=blankX();
	int y=blankY();
	for(int i=1;i<=step;i++)
	{
		swap(a[x][y],a[x][y+1]);
		y++;
		cout<<'D'<<" ";
		cout<<endl;cout<<endl;Print() ;
	}
	cout<<endl;cout<<endl;Print() ;
}

void blank_right(int id)
{
	int dx=targetX(id)-blankX();
	int dy=targetY(id)-blankY();
	if(dy>=0)
	{
		right(dy+1);
	}
	else
	{
		left(-dy-1);
	}
	if(dx>=0)
		down(dx);
	else
		up(-dx);
	
	cout<<endl;cout<<endl;Print() ;
}


void blank_left(int id)
{
	int dx=targetX(id)-blankX();
	int dy=targetY(id)-blankY();
	if(dy>0)
	{
		right(dy-1);
	}
	else
	{
		left(-dy+1);
	}
	if(dx>=0)
		down(dx);
	else
		up(-dx);
	cout<<endl;Print() ;
}
void blank_up(int id)
{
	
	int dx=targetX(id)-blankX();
	int dy=targetY(id)-blankY();
	if(dx==0)
		up(1);
	else if(dx>0)
		down(dx-1);
	else
		down(-dx+1);
	
	if(dy>=0)
	{
		right(dy);
	}
	else
	{
		left(-dy);
	}
	cout<<endl;Print() ;
}
struct node{
	int x,y,step;
	char Lj[1005];
	int MAPAMP[4][4];
}F;

int counter=0;

string in[4][4];

int fstate[4][4]={0,0,0,0,0,1,2,3,0,4,5,6,0,7,8,0};//正确的状态 

char sh[4]={'S','A','D','W'};//标记数码移动的动作 

int dxy[4][2]={1,0,0,-1,0,1,-1,0};//预处理x坐标的变化 

bool vis[362880];

int fact[9]={0,1,2,6,24,120,720,5040,40320};

int code=0;

int pc(node w){//判重的部分 

	code=0;

	for(int i=0;i<9;i++){

		int x1=i/3+1;

		int y1=i%3+1;

		int ct=0; 

        for(int j=i+1;j<9;j++){

        	int x2=j/3+1;

        	int y2=j%3+1;

        	if(w.MAPAMP[x1][y1]<w.MAPAMP[x2][y2])ct++; 

    	} 

        code+=fact[8-i]*ct; 

	}

	return code;

}

bool check(node w){//判断是不是正确 

	for(int i=1;i<=3;i++){

		for(int j=1;j<=3;j++){

			if(w.MAPAMP[i][j]!=fstate[i][j])return false;

		} 

	}

	return true;

}

node bfs(){//广搜部分 

	queue<node>q;

	node p=F;

	q.push(p);
	while(!q.empty()){
		node e=q.front();q.pop();

		for(int i=0;i<=3;i++){

			node next=e;

			next.x=e.x+dxy[i][0];

			next.y=e.y+dxy[i][1];

			if(next.x>=1 && next.x<=3 && next.y>=1 && next.y<=3){

				swap(next.MAPAMP[next.x][next.y],next.MAPAMP[e.x][e.y]);

			}

			else continue;

			int m=pc(next);	

			if(vis[m])continue;

			vis[m]=1;

			if(check(next)){

				next.Lj[e.step+1]=sh[i];

				counter=e.step+1; 
			//	cout<<"------=====================--"<<endl;
				for(int l=1;l<=counter;l++){
					if(e.Lj[l]=='W'){
						up(1);	
					}
					
					if(e.Lj[l]=='A'){
						left(1);	
					}
					if(e.Lj[l]=='S'){
						down(1);	
					}
					
					if(e.Lj[l]=='D'){
						right(1);	
					}
				}
				cout<<e.Lj+1<<endl;
				
				
				return next;

			}

			else{

				next.step=e.step+1;

				next.Lj[next.step]=sh[i];

				q.push(next);

			}

		}

	}

}

void Recover()
{
	/*
	for(int i=0;i<m*n-1;i++)
	{
		int idx=targetX(i);
		int idy=targetY(i);
		int dx=(i/m)-idx;
		int dy=(i%m)-idy;
		
		if(idy==n-1)
		{
			blank_left;
			right(1);
		}
		if(dy>0)
			right(dy);
		if(dy<0)
			left(-dy);
		if(dx>0)
			up(dx);
		if(dx<0)
			down(-dx);
	}
	//*/
	
	if(m==3&&n==3)
	{
	memset(vis,0,sizeof(vis));
	counter=0; 
	F.step=0;
	for(int i=1;i<=3;i++){

		for(int j=1;j<=3;j++){

			F.MAPAMP[i][j]=a[i-1][j-1]+1;
			if(a[i-1][j-1]==-1){
				
				F.x=i;

				F.y=j;
			}
			
		}

	}

	F.step=0;

	node t=bfs();
	for(int i=1;i<=3;i++){

		for(int j=1;j<=3;j++){
			a[i-1][j-1]=t.MAPAMP[i][j]-1;

		}

	}
	}
	
	//below are the function for the bigger board
	//This is the violent solution
	//Unstable and unreliable
	else
	{
	for(int p=0;p<10;p++)
	{
		for(int i=0;i<m*n-1;i++)
	{
		int idx=targetX(i);
		
		int idy=targetY(i);
		//find the target number
		
		int dx=(i/m)-idx;
		int dy=(i%m)-idy;
		
		if(idy==n-1)
		{
			blank_left;
			right(1);
		}
		if(dy>0)
			right(dy);
		if(dy<0)
			left(-dy);
		if(dx>0)
			up(dx);
		if(dx<0)
			down(-dx);
	}
	}
	intiPri();
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
			{
				cout<<pri[i][j]<<" ";
			}
	}
	}
}


int targetX(int id)
{
	for(int i=0;i<m;i++)
	for(int j=0;j<n;j++)
	if(a[i][j]==id)
	return i;
}
int targetY(int id)
{
	for(int i=0;i<m;i++)
	for(int j=0;j<n;j++)
	if(a[i][j]==id)
	return j;
}
void intiPri()
{
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
			{
				if(i<m-1||j<n-1)
				pri[i][j]=i*n+j;
				else
				if(j==n-1)
				pri[i][j]=-1;
			}
	}
//	pri[m][n]=-1;
	
		
//	for(int i=0;i<m;i++)
//		for(int j=0;j<n;j++)
//		cout<<pri[i][j]<<" ";
	
}


void readPic()
{
	
	cout<<"请输入目标图片名：\n";
	//the name of the target pic
	cin>>strFile;
	
}

void PrintPic()
{
	typedef unsigned char byte;
	typedef unsigned short word;
	typedef unsigned int Dword;
	typedef long Long;

	typedef struct  tagOfHeader {
		//word bfType;
		//0x424D, represent BM
		Dword bfSize;
		//size of the file
		word bfReserved1;
		word bfReserved2;
		Dword bfOffBits;
	}BITMAPFILEHEADER;

	byte j233=233;
	byte j8=255;
	byte j9=122;
	byte j6=77;
	
	typedef struct tagbmpInfoHeader {
		Dword biSize;
		//the size of the header
		Long biWidth;
		//the width of the bmp pic
		Long biHeight;
		//the height of the picture
		word biPlanes;
		//I don't quite understand this part,so I imitated this
	//	word biBitCount;
	//	the upper line is optional
		Dword  biCompression; 
		//the type of compression
		Dword  biSizeImage; 
		
		Long  biXPelsPerMeter; 
		//pels in x axis
		Long  biYPelsPerMeter; 
		//pels in y axis
		Dword  biClrUsed; 
		Dword  biClrImportant; 
	}bmpInfoHeader; 
	//define the header
	
	typedef struct tagRGBQUAD {
		byte rgbBlue; 
		//blue part
		byte rgbGreen; 
		//green part
		byte rgbRed; 
		//red part
		byte rgbReserved; //保留值
	}RGBQUAD;
	
	
	
	typedef struct tagIMAGEDATA {
		byte red;
		byte green;
		byte blue;
	}IMAGEDATA;
	
	
	//int P[9*8*7*6*5];
	//this size is enough
	
	
	
	struct piece {
		tagIMAGEDATA x[2500][2500];
	};
	//the max volumn of each piece of picture
	
	//piece pic[1800];
	//define an array of "piece"
	
	
	BITMAPFILEHEADER strHead;
	bmpInfoHeader strInfo;
	//for test
	//int ins=-1;
	//while(ins)
	//here is not well-designed
	//the local array has the same name as the global one
//	int a[m+1][n+1];
	//cin>>m>>n;

	IMAGEDATA *imagedata = NULL;
	// IMAGEDATA存储图片信息 
	int width,height;//图片的宽度和高度
	
	
	//test
	//cout<<"请输入所要读取的文件名:"<<endl;
	//cin>>strFile;
	
	FILE *fpi,*fpw;
	fpi=fopen(strFile,"rb");
	if(fpi != NULL) {
		//先读取文件类型
		word bfType;
		fread(&bfType,1,sizeof(word),fpi);
		if(0x4d42!=bfType) {
			cout<<"the file is not a bmp file!"<<endl;
			
		}
		//读取bmp文件的文件头和信息头
		//十六进制的BM为4d42
		//防止读入错误格式的文件 
		fread(&strHead,1,sizeof(tagOfHeader),fpi);
		//读入信息--文件头 
		fread(&strInfo,1,sizeof(tagbmpInfoHeader),fpi);
		//读入信息--图片信息 
		width = strInfo.biWidth;
		//图片文件的宽度 
		height = strInfo.biHeight;
		//高度 
		imagedata = (IMAGEDATA*)malloc(width * height * sizeof(IMAGEDATA));
		//读出图片的像素数据
		fread(imagedata,sizeof(struct tagIMAGEDATA) * width,height,fpi);
		fclose(fpi);
	}
	else {
		//格式错误给出提示 
		cout<<"file open error!"<<endl;
	}
	
	//for test
	//cout<<"输入状态"<<endl; 
//	for(int i=0;i<=8;i++)
//	cin>>P[i];
	int P[900]={1,2,3,4,5,6,7,8,0};
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			int t=a[m-i-1][j];
			if(t!=-1){
				int x=t/n;
				int y=t%n;
				x=m-x-1;
				t=x*n+y;
			} 
			P[i*n+j]=t;
		}
	}
	for(int i=0;i<9;i++){
		cerr<<P[i]<<'!';
	}
	cerr<<endl;
//	for(int i=0;i<m;i++)
//	for(int j=0;j<n;j++)
//	{
//		cout<<a[i][j];
//		cout<<endl;
//		P[i*m+j]=a[i][j];
//	}
	//honor code
	//this part I, together with another classmate,
	//consulted some DaLao in our class
	int dechight=height,decwidth=width;
	while(dechight%m) dechight--;
	while(decwidth%n) decwidth--;
	strInfo.biClrUsed=0;
	printf("%d %d",height, width);
	
	{
		//cout<<"请输入输出文件名："
		char outputName[60];
		cout<<"请输入输出图片名：\n";
		//cout<<"要以.bmp为后缀\n";
		cin>>outputName;
		if((fpw=fopen(outputName,"wb"))==NULL) {
			cout<<"图片创建错误！"<<endl;
		}
		word bfType_w=0x4d42;
		fwrite(&bfType_w,1,sizeof(word),fpw);
		fwrite(&strHead,1,sizeof(tagOfHeader),fpw);
		fwrite(&strInfo,1,sizeof(tagbmpInfoHeader),fpw);
		for(int i =0;i < height;++i) {
			for(int j = 0;j < width;++j) {
				if(i>=dechight||j>=decwidth) { 
					fwrite( &(j8),1,sizeof(byte),fpw);//注意三条语句的顺序：否则颜色会发生变化
					fwrite( &(j8),1,sizeof(byte),fpw);
					fwrite( &(j8),1,sizeof(byte),fpw);
					continue;
				}
				int ho=dechight/m;
				int wo=decwidth/n;
				int I=i/ho;
				int J=j/wo;
				int ir=i%ho;
				int jr=j%wo;
				int p=I*n+J;
				int pp=P[p];
				int Ip=pp/n;
				int Jp=pp%n;
				int is=Ip*ho+ir;
				int js=Jp*wo+jr;
				if(pp==-1) {
					fwrite( &(j8),1,sizeof(byte),fpw);//注意三条语句的顺序：否则颜色会发生变化
					fwrite( &(j8),1,sizeof(byte),fpw);
					fwrite( &(j8),1,sizeof(byte),fpw);
					continue;
				}
				tagIMAGEDATA DATA=*(imagedata+is*width+js);
				fwrite( &(DATA.red),1,sizeof(byte),fpw);//注意三条语句的顺序：否则颜色会发生变化
				fwrite( &(DATA.green),1,sizeof(byte),fpw);
				fwrite( &(DATA.blue),1,sizeof(byte),fpw);
			}
		}
		fclose(fpw);
	}
	//cout<<"Ins"<<endl;
	//cin>>ins;

}
void welcome()
{
	cout<<"                                                                                        "<<endl;
	cout<<"                                                                                        "<<endl;
	cout<<"                                                                                        "<<endl;
	cout<<"                   //                                                                     "<<endl;
	cout<<"                  //                           \\            //     ||=======                         "<<endl;
	cout<<"==========       //===========//                \\          //      ||      ||           "<<endl;
	cout<<"=========       // ==========//               ======       //       ||      ||                            "<<endl;
	cout<<"\\      //     //     //    //                     ||     //        ||      ||                "<<endl;
	cout<<" \\    //     //     //    //                      ||     ||        ||      ||              "<<endl;
	cout<<"  \\  //     //     //    //                       ||     ||        ||      ||                       "<<endl;
	cout<<"   \\//     //     //    //                        ||     ||        ||      ||                 "<<endl;
	cout<<"   // \\         //\\                              ||     || //             ||                  "<<endl;      
	cout<<"  //   \\       //  \\                             ||     ||//              ||                        "<<endl;
	cout<<" //     \\     //    \\                            ||                       ||                                  "<<endl;
	cout<<"//            //      \\                           ||                       ||                                        "<<endl;
	cout<<"             //        \\                          ||                       ||                                  "<<endl;
	cout<<"            //          \\                         ||===================================             "<<endl;
	cout<<"           //            \\___*                   //                                                             "<<endl;

 } 
 
 
 
 
 void bye()
 {
 		{
			cout<<"  -----------------               -----------------                        ||                  "<<endl;
			cout<<"  -----------------               -----------------                        ||                            "<<endl;
			cout<<"         ||                      ||      ||       ||                       ||                      "<<endl;
			cout<<"  -------||-------               ||      ||       ||                       ||                               "<<endl;
			cout<<"  ||     ||      ||              ||      ||       ||                       ||                          "<<endl;
			cout<<"  ||     ||      ||              ||      ||       ||                       ||                      "<<endl;
			cout<<"  ||-----||------||              ||      ||       ||                       ||                       "<<endl;
			cout<<"  ||-----||------||              ||      ||       ||                       ||                  "<<endl;
			cout<<"  ||     ||      ||              ||      ||       ||                       ||                         "<<endl;
			cout<<"  ||     ||      ||              ||      ||       ||                       ||      "<<endl;
			cout<<"--||-----||------||----                  //\\                              ||                             "<<endl;
			cout<<"--||-----||------||----                 //  \\                             ||                             "<<endl;
			cout<<"  ||     ||      ||                    //    \\                            ||                          "<<endl;
			cout<<"  ||     ||      ||                   //      \\                           ||                            "<<endl;
			cout<<"  ||     ||      ||                  //        \\                          ||                            "<<endl;
			cout<<"  ||     ||      ||                 //          \\____                     @@                              "<<endl;
		}
 }
void mov_up(int step)
{
	for(int i=1;i<=step;i++)
	{
	up(1);
	left(1);
	down(1);
	right(1);
	up(1);
	}
	cout<<endl;Print() ;
}

void mov_left(int step)
{
	for(int i=1;i<=step;i++)
	{
	down(1);
	left(1);
	left(1);
	up(1);
	right(1);
	}
	cout<<endl;Print() ;
}

void mov_right(int step)
{
	for(int i=1;i<=step;i++)
	{
	left(1);
	down(1);
	right(1);
	right(1);
	up(1);
	}
	cout<<endl;Print() ;
}


