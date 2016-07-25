#include <stdio.h>
#include <windows.h>
#define WHITE 0
#define RED 1
#define BLUE 2
#define GREEN 3
typedef struct _node{
	int x,y;
	int color;
}Node;
Node node[201];
int GetXy(int *X,int *Y);							  //返回鼠标在控制台单击的坐标
void GotoXy(int x,int y);							  //移动光标到(x,y)
void PutCursor();									  //显示光标
void HideCursor();									  //隐藏光标
void ChangeColor(int x,int y);						  //改变日期颜色
void ChangeColor_new(int x,int y);
void PrintCalendar();								  //打印日历
void PrintCalendar_new();
void PrintMonth(int day,int space);					  //打印某月日历
int Search(int x,int y);							  //查找(x,y)的节点,若存在则返回下标，否则返回0
void PrintDay(int x,int y);							  //打印该坐标的日期
void PrintDay_new(int x,int y);
int Save();											  //保存node数组信息到save.dat，成功返回1，否则返回0
int Save_new();
int Recovery();										  //
int Recovery_new();
int Init();											  //初始化node数组并将日历修改成相关颜色，先读取save.dat，若不存在则读取recoveryy.dat，成功初始化返回1，否则返回0
int Init_new();
int SelectTerm();									  //选择学期，返回1(新学期)或0(旧学期)
void PrintTerm();									  //打印学期选择界面
void HideCursor(){
	CONSOLE_CURSOR_INFO cursor_info={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}
void PutCursor(){
	CONSOLE_CURSOR_INFO cursor_info={1,1};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}
void GotoXy(int x,int y){
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
int GetXy(int *X,int *Y){
	HANDLE hInput;                              //获取标准输入设备句柄
    INPUT_RECORD inRec;                         //返回数据记录
    DWORD res;                                  //返回已读取的记录数
    int x=-1,y=-1;
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	do{
		ReadConsoleInput(hInput, &inRec, 1, &res);
		if(inRec.EventType==MOUSE_EVENT&&inRec.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED){
			x=(int)inRec.Event.MouseEvent.dwMousePosition.X;
			y=(int)inRec.Event.MouseEvent.dwMousePosition.Y;
		}
	}while(x<0||y<0);
	*X=x;
	*Y=y;
	return 1;
}
void PrintMonth(int day,int space){
	int i,n;
	for(i=0,n=1;i<space+day;i++){
		if(i%7==0&&i)printf("\n   ");
		else if(!i)printf("   ");
		if(i<space)printf("    ");
		else printf("%4d",n++);
	}
	printf("\n");
}
int Search(int x,int y){
	int i;
	if(x%2==0)x--;
	for(i=1;i<=node[0].color;i++){
		if(node[i].x==x&node[i].y==y)return i;
	}
	return 0;
}
void PrintCalendar_new(){
	int i,n;
	char *ch[7]={"九","十","十一","十二","一","二","月"};
	printf("     一  二  三  四  五  六  日\n");
	PrintMonth(30,3);
	PrintMonth(31,5);
	PrintMonth(30,1);
	PrintMonth(31,3);
	PrintMonth(31,6);
	PrintMonth(28,2);
	for(i=3,n=0;n<6;n++){
		GotoXy(0,i);
		printf("%s",ch[n]);
		GotoXy(0,i+1);
		printf("%s",ch[6]);
		i+=5;
	}
	GotoXy(7,33);
	printf("保存设置");
	GotoXy(19,33);
	printf("恢复默认");
	GotoXy(15,35);
	printf("退出");
}
void PrintCalendar(){
	int i,n;
	char *ch[7]={"二","三","四","五","六","七","月"};
	printf("     一  二  三  四  五  六  日\n");
	PrintMonth(29,0);
	PrintMonth(31,1);
	PrintMonth(30,4);
	PrintMonth(31,6);
	PrintMonth(30,2);
	PrintMonth(31,4);
	for(i=3,n=0;n<6;n++){
		GotoXy(0,i);
		printf("%s",ch[n]);
		GotoXy(0,i+1);
		printf("%s",ch[6]);
		i+=5;
	}
	GotoXy(7,33);
	printf("保存设置");
	GotoXy(19,33);
	printf("恢复默认");
	GotoXy(15,35);
	printf("退出");
}
void PrintDay(int x,int y){
	int num;
	if(x%2)x++;
	if(y<=15){
		int shang=(y-1)/5;
		int yu=(y-1)%5;
		switch(shang){
			case 0:num=yu*7+(x-6)/4+1;break;
			case 1:num=yu*7+(x-6)/4;break;
			case 2:num=yu*7+(x-6)/4-3;break;
		}
	}else if(y>=16&&y<=21){
		int yu=y-16;
		num=yu*7+(x-6)/4-5;
	}else if(y>=22&&y<=26){
		int yu=y-22;
		num=yu*7+(x-6)/4-1;
	}else if(y>=27&&y<=31){
		int yu=y-27;
		num=yu*7+(x-6)/4-3;
	}
	GotoXy(x-1,y);
	printf("%2d",num);
}
void PrintDay_new(int x,int y){
	int num;
	int yu;
	if(x%2)x++;
	if(y<=5){
		yu=y-1;
		num=yu*7+(x-6)/4-2;
	}else if(y<=11){
		yu=y-6;
		num=yu*7+(x-6)/4-4;
	}else if(y<=16){
		yu=y-12;
		num=yu*7+(x-6)/4;
	}else if(y<=21){
		yu=y-17;
		num=yu*7+(x-6)/4-2;
	}else if(y<=27){
		yu=y-22;
		num=yu*7+(x-6)/4-5;
	}else if(y<=33){
		int yu=y-28;
		num=yu*7+(x-6)/4-1;
	}
	GotoXy(x-1,y);
	printf("%2d",num);
}
void ChangeColor(int x,int y){
	int index;
	index=Search(x,y);
	if(!y||y>31)return;
	if(x>30||x<5||!(((x+1)/2)%2))return;
	if(index){
		node[index].color++;
		node[index].color%=4;
		switch(node[index].color){
			case WHITE:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);break;
			case RED:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);break;
			case BLUE:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);break;
			case GREEN:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);break;
		}
	}else{
		node[0].color++;
		if(x%2==0)node[node[0].color].x=x-1;
		else node[node[0].color].x=x;
		node[node[0].color].y=y;
		node[node[0].color].color=RED;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	}
	GotoXy(x,y);
	PrintDay(x,y);
	GotoXy(0,35);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
}
void ChangeColor_new(int x,int y){
	int index;
	index=Search(x,y);
	if(!y||y>31)return;
	if(x>30||x<5||!(((x+1)/2)%2))return;
	if(index){
		node[index].color++;
		node[index].color%=4;
		switch(node[index].color){
			case WHITE:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);break;
			case RED:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);break;
			case BLUE:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);break;
			case GREEN:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);break;
		}
	}else{
		node[0].color++;
		if(x%2==0)node[node[0].color].x=x-1;
		else node[node[0].color].x=x;
		node[node[0].color].y=y;
		node[node[0].color].color=RED;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	}
	GotoXy(x,y);
	PrintDay_new(x,y);
	GotoXy(0,35);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
}
int Save(){
	FILE *fp;
	int i;
	if(!(fp=fopen("save.dat","wb")))return 0;
	else fwrite(node,sizeof(Node),node[0].color+1,fp);
	return 1;
}
int Save_new(){
	FILE *fp;
	int i;
	if(!(fp=fopen("save_new.dat","wb")))return 0;
	else fwrite(node,sizeof(Node),node[0].color+1,fp);
	return 1;
}
int Recovery(){
	FILE *fin;
	int i;
	if(!(fin=fopen("recovery.dat","rb")))return 0;
	fread(node,sizeof(Node),1,fin);
	fread(node+1,sizeof(Node),node[0].color,fin);
	fclose(fin);
	GotoXy(0,0);
	PrintCalendar();
	for(i=1;i<=node[0].color;i++){
		node[i].color--;
		ChangeColor(node[i].x,node[i].y);
	}
	return 1;
}
int Recovery_new(){
	FILE *fin;
	int i;
	if(!(fin=fopen("recovery_new.dat","rb")))return 0;
	fread(node,sizeof(Node),1,fin);
	fread(node+1,sizeof(Node),node[0].color,fin);
	fclose(fin);
	GotoXy(0,0);
	PrintCalendar();
	for(i=1;i<=node[0].color;i++){
		node[i].color--;
		ChangeColor_new(node[i].x,node[i].y);
	}
	return 1;
}
int Init(){
	FILE *fin;
	int i;
	if(!(fin=fopen("save.dat","rb"))){
		if(!(fin=fopen("recovery.dat","rb")))return 0;
	}
	fread(node,sizeof(Node),1,fin);
	fread(node+1,sizeof(Node),node[0].color,fin);
	fclose(fin);
	for(i=1;i<=node[0].color;i++){
		node[i].color--;
		ChangeColor(node[i].x,node[i].y);
	}
	return 1;
}
int Init_new(){
	FILE *fin;
	int i;
	if(!(fin=fopen("save_new.dat","rb"))){
		if(!(fin=fopen("recovery_new.dat","rb")))return 0;
	}
	fread(node,sizeof(Node),1,fin);
	fread(node+1,sizeof(Node),node[0].color,fin);
	fclose(fin);
	for(i=1;i<=node[0].color;i++){
		node[i].color--;
		ChangeColor_new(node[i].x,node[i].y);
	}
	return 1;
}
void PrintTerm(){
	GotoXy(6,8);
	printf("请选择：");
	GotoXy(6,10);
	printf("新学期");
	GotoXy(6,11);
	printf("旧学期");
}
int SelectTerm(){
	int x,y;
	do{
	GetXy(&x,&y);
	}while(!(x>=6&&x<=11&&y>9&&y<12));
	return y==10?1:0;
}
int main(){
	int x,y;
	int term;
	HideCursor();
	PrintTerm();
	term=SelectTerm();
	GotoXy(0,0);
	for(x=0;x<20;x++){
		for(y=0;y<50;y++){
			printf(" ");
		}
	}
	GotoXy(0,0);
	if(term == 0){
		PrintCalendar();
		Init();
		do{
			GetXy(&x,&y);
			if(y==33&&x>=7&&x<=14){
				GotoXy(0,34);
				if(Save())printf("保存成功！");
				else printf("保存失败！");
			}else if(y==33&&x>=19&&x<=26){
				if(Recovery()){
					GotoXy(0,34);
					printf("已恢复默认设置！");
				}else{
					GotoXy(0,34);
					printf("缺少文件，恢复失败！");
				}
			}else{
				GotoXy(0,34);
				printf("                 ");
				GotoXy(0,34);
				ChangeColor(x,y);
			}
		}while(!(y==35&&x>=15&&x<=18));
	}else if(term == 1){
		PrintCalendar_new();
		Init_new();
		do{
			GetXy(&x,&y);
			if(y==33&&x>=7&&x<=14){
				GotoXy(0,34);
				if(Save_new())printf("保存成功！");
				else printf("保存失败！");
			}else if(y==33&&x>=19&&x<=26){
				if(Recovery_new()){
					GotoXy(0,34);
					printf("已恢复默认设置！");
				}else{
					GotoXy(0,34);
					printf("缺少文件，恢复失败！");
				}
			}else{
				GotoXy(0,34);
				printf("                 ");
				GotoXy(0,34);
				ChangeColor_new(x,y);
			}
		}while(!(y==35&&x>=15&&x<=18));
	}
	return 0;
}
