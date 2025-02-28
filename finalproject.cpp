#include<iostream>
#include<fstream>
#include<conio.h>
#include<string.h> 
#include<stdlib.h>
#include<time.h> 
using namespace std;

struct user{
	char username[13];
	char nickname[13];
	char password[13];
	int login_no;//登入次數 
	int money;//儲值金 
	int XAXBwin,XAXBeven,XAXBloss;
	int Sudokutime;
};
struct userlist{
	int user_no;//清單中有幾個人 
	user member[100];//最多就是100個user 
};
struct drink{
	int drinkno;//飲品 
	int size;//大小 
	int ice;//冰塊 
	int sugar;//甜度 
	int addition;//加珍珠 
	int cup;//杯數 
};
struct orderlist{
	int mealno;//存放正在製作的單號
	int orderno;//存放現在總共有多少訂單
	int earnings;
	int WhoOrder[100];//100個user裡面是誰的單 
	int OrderPrice[100];
	int cart_no[100];//一份訂單中的購物車裡有幾項 
	drink list[100][10];//存放所有顧客點過的訂單(orderno)||存購物車(no) 
};
//function for user interface
userlist LoadUsers();//讀檔
void SaveUsers(userlist users);//寫檔
int Login(userlist users);//輸入帳號密碼及判斷清單裡是否有這組帳密 
void CreateAccount(userlist users);//創建新帳號 
void input_username(char un[],char ni[],int flag);//輸入username 
void input_password(char un[],char ni[],char pw[],char checkpw[],int flag);//輸入密碼(同時也要印是哪個user) 
//function for MainScreen
void MainScreen(int select,int user_id);
int MainScreen_MainUI(int select,int user_id);
//function for order
void Order_MainScreen(int select,int user_id,int totalprice);
int Order_MainUI(int select,int user_id,int totalprice);
int Order_Main(int user_id,int money);
void Order_SizeMainScreen(int select);
int Order_SizeMainUI(int select);
int Order_SizeMain();
void Order_IceMainScreen(int select);
int Order_IceMainUI(int select);
int Order_IceMain();
void Order_SugarMainScreen(int select);
int Order_SugarMainUI(int select);
int Order_SugarMain();
void Order_AdditionMainScreen(int select);
int Order_AdditionMainUI(int select);
int Order_AdditionMain();
int Order_CupMain();
orderlist Order_CreateOrder(int drink_no,orderlist drinks,int order_no,int cart_no);
int Order_CreatePrice(int price,int order_no,int cart_no,orderlist drinks,int flag);
orderlist LoadOrders();
void SaveOrders(orderlist drinks);
void ReadOrders(int user_id,int flag);
int ReadOrder_MainUI(int select);
void ReadOrders_Main(int user_id);
int ReadOrder_MainUI(int select);
void CancelOrder(int user_id,orderlist drinks);
//function for changepw
void Changepw(userlist users,int user_id);
//function for Sudoku
void Sudoku_Init(int p[][9][10]);//所有格子[(0,0)~(9,9)]都能填1-9
void Sudoku_Update(int p[][9][10],int R,int C,int N);//把不能填數字n的格子的N(那個數)改成0(假設(6,8)原本是(100100000)->可以填1跟4，現在有人呼叫說4不能填，所以變成(100000000)
void Sudoku_Read(int Qno,int Q[][9],int p[][9][10]);//讀檔 
void Sudoku_Print(int Q[][9],int A[][9],int R, int C);//印格線跟括號 
int Sudoku_Check(int p[][9][10],int R,int C);//回傳唯一解，如果沒有就回傳0 
void Sudoku_MainUI(int Q[][9], int A[][9]);//讓玩家填數字 
int Sudoku_Main(userlist users,int user_id);
void Sudoku_Cutscenes(userlist users,int user_id);
//function for XAXB
void XAXB_num2digit(int num,int digit[]);
bool XAXB_isLegal(int num);
void XAXB_Check(int G,int A,int AB[]);
int XAXB_Main(userlist users,int user_id);
void XAXB_Cutscenes(userlist users,int user_id);
//function for chatroom
void Chatroom_Main(char un[],userlist users);
void PrivateChatroom_Main(char un1[],char un2[]);
//functions for KEBUKE
void KEBUKE_DoOrders();
void KEBUKE_Deposit();
void KEBUKE_Main();
int KEBUKE_MainUI(int select);
void KEBUKE_MainScreen(int select);

int main(){
	time_t enter,quit;
	int timediff,min,sec;
	enter=time(NULL);//開始計時 
	char c[2];
	int user_id;
	userlist users;
	users=LoadUsers();//把user讀進來 
	user_id=Login(users);//回傳一個user
	if(user_id!=-1)//載入MainScreen 
	{
		users=LoadUsers();//因為可能有更新過，所以重讀一份 
		users.member[user_id].login_no++;
		SaveUsers(users);
		while(true)
		{
			int select = 1;
			do
			{
				select = MainScreen_MainUI(select,user_id);
				switch(select)
				{
					case 1:
						users.member[user_id].money-=Order_Main(user_id,users.member[user_id].money);
						cout<<endl<<endl<<endl<<endl<<endl;
						cout<<"------------------------------------------------------------------------------------------"<<endl;
						cout<<"請按任意鍵繼續:";
						getch();
						break;
					case 2:
						ReadOrders_Main(user_id);
						users=LoadUsers();
						cout<<endl<<endl<<endl<<endl<<endl;
						cout<<"------------------------------------------------------------------------------------------"<<endl;
						cout << "請按任意鍵繼續:";
						getch();
						break;
					case 3:
						Changepw(users,user_id);
						users=LoadUsers();//有更新過，所以重讀一份 
						break;
					case 4:
						Chatroom_Main(users.member[user_id].nickname,users);
						cout<<endl<<endl<<endl<<endl<<endl;
						cout<<"------------------------------------------------------------------------------------------"<<endl;
						cout << "請按任意鍵繼續:";
						getch();
						break;
					case 5:
						users.member[user_id].money+=Sudoku_Main(users,user_id);
						users.member[user_id].Sudokutime++;
						SaveUsers(users);
						cout<<endl<<endl<<endl<<endl<<endl;
						users=LoadUsers();//有更新過，所以重讀一份 
						cout<<"------------------------------------------------------------------------------------------"<<endl;
						cout << "請按任意鍵繼續:";
						getch();
						break;
					case 6:
						users.member[user_id].money+=XAXB_Main(users,user_id);
						SaveUsers(users);
						users=LoadUsers();
						cout<<endl<<endl<<endl<<endl<<endl;
						cout<<"------------------------------------------------------------------------------------------"<<endl;
						cout << "請按任意鍵繼續:";
						getch();
						break;
				}
				SaveUsers(users);
			}while(select!=0);
			cout<<"                 您確定要離開此系統嗎(Y/N): ";
			cin>>c;
			if(strcmp(c,"Y")==0||strcmp(c,"y")==0)
				break;	
			else
				continue;			
		}
		SaveUsers(users);//存檔 
		quit=time(NULL);//結束計時 
		timediff=difftime(quit,enter);//算時間差 
		min=timediff/60;
		sec=timediff%60;
		cout<<"—————————————————————————————————————"<<endl; 
		cout<<"                 謝謝惠顧!您本次停留了"<<min<<"分"<<sec<<"秒，期待您再次使用本系統"<<endl;
		cout<<"                 請按任意鍵繼續:";
		getch(); 
		return 0;
	}
	else
	{
		while(true)
		{
			KEBUKE_Main();
			cout<<"—————————————————————————————————————"<<endl;
			cout<<"               您確定要離開此系統嗎(Y/N): ";
			cin>>c;
			if(strcmp(c,"Y")==0||strcmp(c,"y")==0)
				break;	
			else
				continue;
		} 
		return 0;
	}
}
//function for user interface
userlist LoadUsers(){ 
	userlist users;
	ifstream fin;
	fin.open("memberlist.txt");
	fin>>users.user_no; 
	for(int i=0;i<users.user_no;i++)
	{
		fin>>users.member[i].username;
		fin>>users.member[i].nickname;
		fin>>users.member[i].password;
		fin>>users.member[i].login_no;
		fin>>users.member[i].money;
		fin>>users.member[i].XAXBwin;
		fin>>users.member[i].XAXBeven;
		fin>>users.member[i].XAXBloss;
		fin>>users.member[i].Sudokutime;
	} 
	fin.close();
	return users;
}
void SaveUsers(userlist users){
	ofstream fout;
	fout.open("memberlist.txt"); 
	fout<<users.user_no<<endl;
	for(int i=0;i<users.user_no;i++)
	{
		fout<<users.member[i].username<<endl;
		fout<<users.member[i].nickname<<endl;
		fout<<users.member[i].password<<endl;
		fout<<users.member[i].login_no<<endl;
		fout<<users.member[i].money<<endl;
		fout<<users.member[i].XAXBwin<<endl;
		fout<<users.member[i].XAXBeven<<endl;
		fout<<users.member[i].XAXBloss<<endl;
		fout<<users.member[i].Sudokutime<<endl;
	}
	fout.close();
}
void CreateAccount(userlist users){
	int i,wrong,stp=0;
	char username[13];
	char nickname[13];
	char password[13];
	char checkpw[13];
	users.user_no++; 
	input_username(username,nickname,1);
	input_username(username,nickname,-1);
	if(strcmp(username,"register")==0||strcmp(username,"Register")==0||strcmp(username,"KEBUKE")==0)
	{
		cout<<endl<<"無法使用此帳號名稱，請重新輸入。"<<endl; 
		cout << "請按任意鍵繼續: ";
		getch();	
		stp=1;
	}
	for(i=0;i<users.user_no-1;i++)//如果輸入的是既有的使用者 
		if(strcmp(username,users.member[i].username)==0)
		{
			cout<<endl<<"此帳號已存在!"<<endl; 
			cout << "請按任意鍵繼續: ";
			getch();	
			stp=1;
			break;
		} 
	do{
		if(stp==1)
			break;
		wrong=0;
		input_password(username,nickname,password,checkpw,1);
		input_password(username,nickname,password,checkpw,2);
		//檢查兩次的密碼是否相同 
		if(strlen(password)!=strlen(checkpw))
		{
			cout<<endl<<"密碼不相同，請重新輸入!"<<endl;
			cout << "請按任意鍵繼續: ";
			getch();
		}	
		else
		{
			for(i=0;i<=strlen(password);i++)
			{
				if((int)password[i]!=(int)checkpw[i])
				{
					cout<<endl<<"密碼不相同，請重新輸入!"<<endl;
					cout << "請按任意鍵繼續: ";
					getch();
					wrong=1;
					break;
				}	
			}
			if(wrong==0)
			{
				cout<<endl<<"已創建新帳號，請重新登入。"<<endl;
				cout << "請按任意鍵繼續: ";
				getch();
				//創建新使用者的資料
				for(i=0;i<strlen(username);i++)
					users.member[users.user_no-1].username[i]=username[i];
				for(i=0;i<strlen(nickname);i++)
					users.member[users.user_no-1].nickname[i]=nickname[i];
				for(i=0;i<strlen(password);i++)
					users.member[users.user_no-1].password[i]=password[i];
				users.member[users.user_no-1].login_no=0;
				users.member[users.user_no-1].money=0;
				users.member[users.user_no-1].XAXBwin=0;
				users.member[users.user_no-1].XAXBeven=0;
				users.member[users.user_no-1].XAXBloss=0;
				users.member[users.user_no-1].Sudokutime=0; 
				SaveUsers(users);
				break;
			}
		}
	}while(true); 
}
int Login(userlist users){
	int ctn=0;
	int i,j,flag=0;
	/*
	flag=0(不是新建帳號)
	flag>0(新建帳號)
	flag<0(更改密碼) 
	*/
	char username[13];
	char password[13];
	char nickname[13];
	char checkpw[13];
	do{
		ctn=0;
		input_username(username,nickname,0);//輸入帳號 
		if(strcmp(username,"KEBUKE")==0)
			return -1;
		if(strcmp(username,"register")==0||strcmp(username,"Register")==0)//註冊 
		{
			CreateAccount(users);
			users=LoadUsers();//因為有更新過，所以重讀一份 
			ctn=1;
		}
		if(ctn==1)
			continue;	
		for(i=0;i<users.user_no;i++)
			if(strcmp(username,users.member[i].username)==0)
				break;
		if(i==users.user_no)//找不到使用者 
		{
			ctn=1;
			cout<<endl<<"查無此帳號，請重新輸入或註冊新帳號"<<endl;
			cout<<"請按任意鍵繼續: "<<endl;
			getch();//讓使用者按一個按鍵 
		}
		if(ctn==1)
			continue;
		input_password(username,nickname,password,checkpw,flag);//開始輸入密碼 
		if(strcmp(password,users.member[i].password)==0)//如果輸入的密碼跟清單中該使用者的相等
			return i;	
		else//密碼錯了的話
		{
			do{
				cout<<endl<<"密碼錯誤，請重新輸入"<<endl;
				cout<<"請按任意鍵繼續: "<<endl;
				getch(); 
				input_password(username,nickname,password,checkpw,flag);
					if(strcmp(password,users.member[i].password)==0)
						return i;
			}while(true);
		}	
	}while(true);
}
void input_username(char un[],char ni[],int flag){ 
	/*
	flag=0(不是新建帳號，印輸入使用者名稱)
	flag>0(要創新帳號，印創建新帳號) 
	flag<0(輸入暱稱) 
	*/	
	char c1,c2;
	int n=0,i,check=0;
	do
	{
		system("cls");
		if(flag>0)
		{
			cout<<"創建新帳號"<<endl;
			cout<<"使用者名稱(首格需為英文字母且長度須為4-12碼): ";
			for(i=0;i<n;i++)
				cout<<un[i];//輸出到目前為止合法的字元 
		} 
		else if(flag==0)	
		{
			cout<<"請輸入使用者名稱，或輸入register以註冊帳號: ";
			for(i=0;i<n;i++)
				cout<<un[i];//輸出到目前為止合法的字元 
		}	
		else
		{
			cout<<"創建新帳號"<<endl;
			cout<<"使用者名稱(首格需為英文字母且長度須為4-12碼): ";
			for(i=0;un[i]!='\0';i++)
				cout<<un[i];//輸出到目前為止合法的字元 
			cout<<endl<<"使用者暱稱: ";
			for(i=0;i<n;i++)
				cout<<ni[i];//輸出到目前為止合法的字元 
		}
		c1=getch();//看下一碼
		if(c1==-32||c1==0)//0跟32是特殊碼的開頭，把特殊碼的後一碼存到c2(後面不會處理c2)(特殊碼有兩位(eg:(-32,75)) 
			c2=getch();// 
		if((c1>='a'&&c1<='z')||(c1>='A'&&c1<='Z')||(c1>='0'&&c1<='9')||c1=='_')//如果合法，存到下一格，下次再一起輸出 
		{
			if(n==0&&flag>=0)
			{
				if((c1>='a'&&c1<='z')||(c1>='A'&&c1<='Z'))
				{
					un[0]=c1;
					n++;
					continue;
				}	
				else
					continue;
			}
			if(n==12)//如果n是12，強迫他改第11碼(也就是不會輸到第13碼)
			{
				if(flag>=0)
					un[11]=c1;	
				else
					ni[11]=c1;
			}
				
			else
			{
				if(flag>=0)
				{
					un[n]=c1;
					n++;
				}
				else
				{
					ni[n]=c1;
					n++;
				}
			}
		}
		if(c1==8&&n>0)//後退鍵 
			n--;
		if(n>=4)
			check=1;
		else
			check=0;
		if(flag<0)
			check=1;
	}while(c1!=13||check==0||n==0);//判定按enter時輸入是不是空的(是空的就要繼續輸入)|c1!=13就還要繼續輸入 
	if(flag>=0)
		un[n]='\0';//在最後放停止
	else
		ni[n]='\0'; 
}
void input_password(char un[],char ni[],char pw[],char checkpw[],int flag){
	/*
	flag=0(不是新建帳號，輸出使用者名稱+密碼)
	flag>0(新建帳號，輸出創建新帳號+密碼||flag=2時多印出先前輸入的密碼)
	flag<0(更改密碼，-1印請輸入原密碼，-2印請輸入新密碼，-3多印先前輸入的密碼) 
	flag=2||-3時是要再輸入密碼進行驗證 
	*/
	char c1,c2;
	int n=0,i,check=0;
	do
	{
		system("cls");
		if(flag>0)
		{
			cout<<"創建新帳號"<<endl;
			cout<<"使用者名稱(首格需為英文字母且長度須為4-12碼): "<<un<<endl;
			cout<<"使用者暱稱: "<<ni<<endl; 
		}
		else if(flag==0)
			cout<<"使用者名稱: "<<un<<endl;	
		else if(flag==-1)
			cout<<"請輸入原";
		else
			cout<<"請輸入新";
		cout<<"密碼: ";
		if(flag==2||flag==-3)
		{
			for(i=0;pw[i]!='\0';i++)
				cout<<"*";
			cout<<endl<<"確認密碼: ";
		}
		for(i=0;i<n;i++)
			cout<<"*";//輸出到目前為止的密碼(以*表示) 
		c1=getch();//看下一碼
		if(c1==-32||c1==0)//0跟32是特殊碼的開頭，把特殊碼的後一碼存到c2(後面不會處理c2)(特殊碼有兩位(eg:(-32,75)) 
			c2=getch();// 
		if((c1>='a'&&c1<='z')||(c1>='A'&&c1<='Z')||(c1>='0'&&c1<='9')||c1=='_')//如果合法，存到下一格，下次再一起輸出 
		{
			if(n==12)//如果n是12，強迫他改第11碼(也就是不會輸到第13碼)
			{
				if(flag==2||flag==-3)
					checkpw[11]=c1;
				else
					pw[11]=c1;	
			}
				
			else
			{
				if(flag==2||flag==-3)
					checkpw[n]=c1;
				else 
					pw[n]=c1;
				n++;
			}
		}
		if(c1==8&&n>0)//後退鍵 
			n--;
		if(n>=4)
			check=1;
		else
			check=0;
	}while(c1!=13||check==0||n==0);//判定按enter時輸入是不是空的(是空的就要繼續輸入)|c1!=13就還要繼續輸入 
	if(flag==2||flag==-3)
		checkpw[n]='\0';//在最後放停止 
	else
		pw[n]='\0';
}
//function for changepw
void Changepw(userlist users,int user_id){
	int stp,i,wrong;
	char password[13];
	char nickname[13];
	char checkpw[13];
	do{
		stp=0;
		input_password(users.member[user_id].username,nickname,password,checkpw,-1);
		if(strlen(password)!=strlen(users.member[user_id].password))//輸入原密碼和list裡的不一致 
		{
			cout<<endl<<"密碼不相同，請重新輸入!"<<endl;
			cout << "請按任意鍵繼續: ";
			getch();
			stp=1;
		}	
		else
			for(i=0;i<=strlen(password);i++)
				if((int)password[i]!=(int)users.member[user_id].password[i])//輸入原密碼和list裡的不一致 
				{
					cout<<endl<<"密碼不相同，請重新輸入!"<<endl;
					cout << "請按任意鍵繼續: ";
					getch();
					stp=1;
					break;
				}	
		do{
			if(stp==1)
				break;
			wrong=0;
			input_password(users.member[user_id].username,nickname,password,checkpw,-2);//輸入password 
			input_password(users.member[user_id].username,nickname,password,checkpw,-3);//輸入checkpw 
			//檢查兩次的密碼是否相同 
			if(strlen(password)!=strlen(checkpw))
			{
				cout<<endl<<"密碼不相同，請重新輸入!"<<endl;
				cout << "請按任意鍵繼續: ";
				getch();
			}	
			else
			{
				for(i=0;i<=strlen(password);i++)
				{
					if((int)password[i]!=(int)checkpw[i])
					{
						cout<<endl<<"密碼不相同，請重新輸入!"<<endl;
						cout << "請按任意鍵繼續: ";
						getch();
						wrong=1;
						break;
					}	
				}
				if(wrong==0)
				{
					cout<<endl<<"已更改密碼。"<<endl;
					cout << "請按任意鍵繼續: ";
					getch();
					//改密碼 
					for(i=0;i<strlen(password);i++)
						users.member[user_id].password[i]=password[i];
					users.member[user_id].password[i]='\0';
					SaveUsers(users);
					break;
				}
			}
		}while(true); 
	}while(stp==1);
		
}
//function for MainScreen
void MainScreen(int select,int user_id){
	system("color 52");
	userlist users;
	users=LoadUsers();
	system("cls");
	int i;
	char L[7],R[7];
	for(i=0;i<6;i++)
	{
		L[i] = ' ';
		R[i] = ' ';
	}
	L[select] = '[';
	R[select] = ']';                                                      
	//cout<<"██████████████████████████████████████"<<endl;
	cout<<"█                                                                        █"<<endl; 
	cout<<"█   |=|   |=|   |=======| |======|   |=|     |=| |=|   |=|   |=======|   █"<<endl;
	cout<<"█   |=|  |=|    |=|       |=|   |=|  |=|     |=| |=|  |=|    |=|         █"<<endl;
	cout<<"█   |=| |=|     |=|       |=|    |=| |=|     |=| |=| |=|     |=|         █"<<endl;
	cout<<"█   ||=||       |=====|   |======|   |=|     |=| ||=||       |=====|     █"<<endl;
	cout<<"█   |=|  |=|    |=|       |=|   |=|  |=|     |=| |=|  |=|    |=|         █"<<endl;
	cout<<"█   |=|   |=|   |=|       |=|    |=| |=|     |=| |=|   |=|   |=|         █"<<endl;
	cout<<"█   |=|     |=| |=======| |=======|   |=======|  |=|     |=| |=======|   █"<<endl;
	cout<<"█        可       不       可       熟       成       紅       茶        █"<<endl;
	cout<<"█                                                                        █"<<endl;
	//cout<<"██████████████████████████████████████"<<endl;
	cout << endl<< endl<< endl;
	cout <<"                  "<<users.member[user_id].nickname<<"您好，歡迎蒞臨可不可，您總共已登入"<<users.member[user_id].login_no<<"次"<<endl; 
	cout <<"                  您現在擁有"<<users.member[user_id].money<<"元發財金"<<endl;
	cout <<"                  -------------------------------------------"<<endl;
	cout <<"                 |          "<< L[1] << "1" << R[1] << " 下訂單                       |" << endl;
	cout <<"                 |          "<< L[2] << "2" << R[2] << " 查訂單                       |" << endl;
	cout <<"                 |          "<< L[3] << "3" << R[3] << " 修改會員資料                 |" << endl;
	cout <<"                 |          "<< L[4] << "4" << R[4] << " 聊天室                       |" << endl;
	cout <<"                 |          "<< L[5] << "5" << R[5] << " 數獨遊戲                     |" << endl;
	cout <<"                 |          "<< L[6] << "6" << R[6] << " 猜數字                       |" << endl;
	cout <<"                 |          "<< L[0] << "0" << R[0] << " 離開系統                     |" << endl;
	cout <<"                  -------------------------------------------"<<endl;     
}
int MainScreen_MainUI(int select,int user_id){
	char x,x1;
	do{
		MainScreen(select,user_id);
		x = getch();
		if(x==-32)//上下左右鍵的第一個數字 
		{
			x1 = getch();//抓後面那個 
			if(x1==72)
				select = (select + 6)%7;//上 
			if(x1==80)
				select = (select + 1)%7;//下 
			if(x1==77)//右鍵=ENTER 
				x=13;
		}
		if(x>='0'&&x<='6')//鍵盤的0~6 
			select = x - '0';
	}while(x!=13);
	return select;
}
//function for order
void Order_MainScreen(int select,int user_id,int totalprice){
	system("cls");
	int i;
	userlist users;
	users=LoadUsers();
	char L[13],R[13];
	for(i=0;i<13;i++)
	{
		L[i] = ' ';
		R[i] = ' ';
	}
	L[select] = '[';
	R[select] = ']';
	cout<<"============================================================"<<endl;
	cout<<"              可   不   可   熟   成   紅   茶              "<<endl; 
	cout<<"============================================================"<<endl;
	cout<<"                   您現在擁有: "<<users.member[user_id].money<<"元發財金"<<endl;
	cout<<"                   待結帳金額: "<<totalprice<<"元"<<endl;
	cout<<endl<<endl<<endl<<endl<<endl;
	cout<<"——————————————————————————————"<<endl;
	cout<<"                  品 名       價 錢                         "<<endl;
	cout<<"——————————————————————————————"<<endl; 
	cout<<"              "<< L[1] << "1" << R[1] << " 熟成紅茶    M 25/L 30" << endl;
	cout<<"              "<< L[2] << "2" << R[2] << " 麗春紅茶    M 25/L 30" << endl;
	cout<<"              "<< L[3] << "3" << R[3] << " 太妃紅茶    M 30/L 35" << endl;
	cout<<"              "<< L[4] << "4" << R[4] << " 胭脂紅茶    M 35/L 40" << endl;
	cout<<"              "<< L[5] << "5" << R[5] << " 雪藏紅茶    M 45/L 55" << endl;
	cout<<"              "<< L[6] << "6" << R[6] << " 熟成冷露    M 25/L 30" << endl;
	cout<<"              "<< L[7] << "7" << R[7] << " 春芽冷露    M 25/L 30" << endl;
	cout<<"              "<< L[8] << "8" << R[8] << " 春芽綠茶    M 25/L 30" << endl;
	cout<<"              "<< L[9] << "9" << R[9] << " 熟成歐蕾    M 40/L 50" << endl;
	cout<<"              "<< L[10] << "A" << R[10] << " 白玉歐蕾    M 50/L 60" << endl;
	cout<<"              "<< L[11] << "B" << R[11] << " 胭脂多多    M 40/L 50" << endl;
	cout<<"              "<< L[12] << "C" << R[12] << " 黃玉歐蕾    M 60/L 70" << endl;
	cout<<"              "<< L[0] << "0" << R[0] << " 結    帳" << endl;
}
int Order_MainUI(int select, int user_id,int totalprice){
	char x,x1;
	do{
		Order_MainScreen(select,user_id,totalprice);
		x = getch();
		if(x==-32)
		{
			x1 = getch();
			if(x1==72)
				select = (select + 12)%13;
			if(x1==80)
				select = (select + 1)%13;
			if(x1==77)
				x=13;
		}
		if(x>='0'&&x<='9')
			select = x - '0';
		if(x>='a'&&x<='c')
			select = x - 'a'+ 10;
		if(x>='A'&&x<='C')
			select = x - 'A'+ 10;
	}while(x!=13);
	return select;
}
int Order_Main(int user_id,int money){
	ofstream fout;
	int select = 1,price,totalprice=0,flag;
	orderlist drinks;
	drinks=LoadOrders();
	drinks.orderno++;
	drinks.cart_no[drinks.orderno]=0;
	drinks.WhoOrder[drinks.orderno]=user_id;
	do
	{
		price=0;
		select = Order_MainUI(select,user_id,totalprice);
		switch(select)
		{
			case 1://熟成紅茶:25/30
				drinks.cart_no[drinks.orderno]++;
				drinks=Order_CreateOrder(1,drinks,drinks.orderno,drinks.cart_no[drinks.orderno]);
				price=Order_CreatePrice(25,drinks.orderno,drinks.cart_no[drinks.orderno],drinks,1);
				if(price==0)
					drinks.cart_no[drinks.orderno]--;
				else
					totalprice+=price; 
				break;	
			case 2://麗春紅茶:25/30	
				drinks.cart_no[drinks.orderno]++;
				drinks=Order_CreateOrder(2,drinks,drinks.orderno,drinks.cart_no[drinks.orderno]);
				price=Order_CreatePrice(25,drinks.orderno,drinks.cart_no[drinks.orderno],drinks,1);
				if(price==0)
					drinks.cart_no[drinks.orderno]--;
				else
					totalprice+=price; 
				break;	
			case 3://太妃紅茶:30/35
				drinks.cart_no[drinks.orderno]++;
				drinks=Order_CreateOrder(3,drinks,drinks.orderno,drinks.cart_no[drinks.orderno]);
				price=Order_CreatePrice(30,drinks.orderno,drinks.cart_no[drinks.orderno],drinks,1);
				if(price==0)
					drinks.cart_no[drinks.orderno]--;
				else
					totalprice+=price; 
				break;	
			case 4://胭脂紅茶:35/40
				drinks.cart_no[drinks.orderno]++;
				drinks=Order_CreateOrder(4,drinks,drinks.orderno,drinks.cart_no[drinks.orderno]);
				price=Order_CreatePrice(35,drinks.orderno,drinks.cart_no[drinks.orderno],drinks,1);
				if(price==0)
					drinks.cart_no[drinks.orderno]--;
				else
					totalprice+=price; 
				break;	
			case 5://雪藏紅茶:45/55
				drinks.cart_no[drinks.orderno]++;
				drinks=Order_CreateOrder(5,drinks,drinks.orderno,drinks.cart_no[drinks.orderno]);
				price=Order_CreatePrice(45,drinks.orderno,drinks.cart_no[drinks.orderno],drinks,2);
				if(price==0)
					drinks.cart_no[drinks.orderno]--;
				else
					totalprice+=price; 
				break;	
			case 6://熟成冷露:25/30
				drinks.cart_no[drinks.orderno]++;
				drinks=Order_CreateOrder(6,drinks,drinks.orderno,drinks.cart_no[drinks.orderno]);
				price=Order_CreatePrice(25,drinks.orderno,drinks.cart_no[drinks.orderno],drinks,1);
				if(price==0)
					drinks.cart_no[drinks.orderno]--;
				else
					totalprice+=price; 
				break;				
			case 7://春芽冷露:25/30
				drinks.cart_no[drinks.orderno]++;
				drinks=Order_CreateOrder(7,drinks,drinks.orderno,drinks.cart_no[drinks.orderno]);
				price=Order_CreatePrice(25,drinks.orderno,drinks.cart_no[drinks.orderno],drinks,1);
				if(price==0)
					drinks.cart_no[drinks.orderno]--;
				else
					totalprice+=price; 
				break;				
			case 8://春芽綠茶:25/30
				drinks.cart_no[drinks.orderno]++;
				drinks=Order_CreateOrder(8,drinks,drinks.orderno,drinks.cart_no[drinks.orderno]);
				price=Order_CreatePrice(25,drinks.orderno,drinks.cart_no[drinks.orderno],drinks,1);
				if(price==0)
					drinks.cart_no[drinks.orderno]--;
				else
					totalprice+=price; 
				break;				
			case 9://熟成歐蕾:40/50
				drinks.cart_no[drinks.orderno]++;
				drinks=Order_CreateOrder(9,drinks,drinks.orderno,drinks.cart_no[drinks.orderno]);
				price=Order_CreatePrice(40,drinks.orderno,drinks.cart_no[drinks.orderno],drinks,2);
				if(price==0)
					drinks.cart_no[drinks.orderno]--;
				else
					totalprice+=price; 
				break;	
			case 10://白玉歐蕾:40/50
				drinks.cart_no[drinks.orderno]++;
				drinks=Order_CreateOrder(10,drinks,drinks.orderno,drinks.cart_no[drinks.orderno]);
				price=Order_CreatePrice(40,drinks.orderno,drinks.cart_no[drinks.orderno],drinks,2);
				if(price==0)
					drinks.cart_no[drinks.orderno]--;
				else
					totalprice+=price; 
				break;				
			case 11://胭脂多多:40/50
				drinks.cart_no[drinks.orderno]++;
				drinks=Order_CreateOrder(11,drinks,drinks.orderno,drinks.cart_no[drinks.orderno]);
				price=Order_CreatePrice(40,drinks.orderno,drinks.cart_no[drinks.orderno],drinks,2);
				if(price==0)
					drinks.cart_no[drinks.orderno]--;
				else
					totalprice+=price; 
				break;					
			case 12://黃玉歐蕾:60/70
				drinks.cart_no[drinks.orderno]++;
				drinks=Order_CreateOrder(12,drinks,drinks.orderno,drinks.cart_no[drinks.orderno]);
				price=Order_CreatePrice(60,drinks.orderno,drinks.cart_no[drinks.orderno],drinks,2);
				if(price==0)
					drinks.cart_no[drinks.orderno]--;
				else
					totalprice+=price; 
				break;									
		}
	}while(select!=0);
	if(totalprice>money)
	{
		cout<<"==========================================================================================="<<endl;
		cout<<"              發財金不足，已取消訂單，請向店家儲值或是遊玩小遊戲以取得發財金!"<<endl;
		cout<<"==========================================================================================="<<endl;
		totalprice=0;
		drinks.orderno--;
		SaveOrders(drinks);
	}
	else if(totalprice==0)
	{
		cout<<"==================================================="<<endl;
		cout<<"                   歡迎再度光臨!"<<endl; 
		cout<<"==================================================="<<endl;
	}
	else
	{
		cout<<"==================================================="<<endl;
		cout<<"              訂單已成立!總共是"<<totalprice<<"元"<<endl;
		cout<<"                   歡迎再度光臨!"<<endl; 
		cout<<"==================================================="<<endl;
		drinks.OrderPrice[drinks.orderno]=totalprice;
		drinks.earnings+=totalprice;
		SaveOrders(drinks);
	}	
	return totalprice;
}
//size function
void Order_SizeMainScreen(int select){
	system("cls");
	int i;
	char L[2],R[2];
	for(i=0;i<2;i++)
	{
		L[i] = ' ';
		R[i] = ' ';
	}
	L[select] = '[';
	R[select] = ']';
	cout<<"============================================================"<<endl;
	cout<<"              可   不   可   熟   成   紅   茶              "<<endl; 
	cout<<"============================================================"<<endl;
	cout << endl<< endl<< endl<< endl<< endl;
	cout<<"——————————————————————————————"<<endl;
	cout<<"                       請 選 擇 份 量                       "<<endl; 
	cout<<"——————————————————————————————"<<endl;
	cout <<"                  "<< L[0] << "1" << R[0] << "       中杯" << endl;
	cout <<"                  "<< L[1] << "2" << R[1] << "       大杯" << endl;
}
int Order_SizeMainUI(int select){
	char x,x1;
	do{
		Order_SizeMainScreen(select);
		x = getch();
		if(x==-32)
		{
			x1 = getch();
			if(x1==72)
				select = (select + 1)%2;
			if(x1==80)
				select = (select + 1)%2;
			if(x1==77)
				x=13;
		}
		if(x>='1'&&x<='2')
			select = x - '1';
	}while(x!=13);
	return select;
}
int Order_Sizemain(){
	int select = 0;
	do
	{
		select = Order_SizeMainUI(select);
		switch(select)
		{
			case 0:
				return 0;
			case 1:
				return 1;
		}
	}while(true);
}
//ice function
void Order_IceMainScreen(int select){
	system("cls");
	int i;
	char L[8],R[8];
	for(i=0;i<8;i++)
	{
		L[i] = ' ';
		R[i] = ' ';
	}
	L[select] = '[';
	R[select] = ']';
	cout<<"============================================================"<<endl;
	cout<<"              可   不   可   熟   成   紅   茶              "<<endl; 
	cout<<"============================================================"<<endl;
	cout << endl<< endl<< endl<< endl<< endl;
	cout<<"——————————————————————————————"<<endl;
	cout<<"                    請 選 擇 飲 品 溫 度                    "<<endl; 
	cout<<"——————————————————————————————"<<endl;
	cout <<"                 "<< L[0] << "1" << R[0] <<"      正 常 冰" << endl;
	cout <<"                 "<< L[1] << "2" << R[1] <<"      少    冰" << endl;
	cout <<"                 "<< L[2] << "3" << R[2] <<"      微    冰" << endl;
	cout <<"                 "<< L[3] << "4" << R[3] <<"      去    冰" << endl;
	cout <<"                 "<< L[4] << "5" << R[4] <<"      完全去冰" << endl;
	cout <<"                 "<< L[5] << "6" << R[5] <<"      常    溫" << endl;
	cout <<"                 "<< L[6] << "7" << R[6] <<"         溫   " << endl;
	cout <<"                 "<< L[7] << "8" << R[7] <<"         熱   " << endl;
}
int Order_IceMainUI(int select){
	char x,x1;
	do{
		Order_IceMainScreen(select);
		x = getch();
		if(x==-32)
		{
			x1 = getch();
			if(x1==72)
				select = (select + 7)%8;
			if(x1==80)
				select = (select + 1)%8;
			if(x1==77)
				x=13;
		}
		if(x>='1'&&x<='8')
			select = x - '1';
	}while(x!=13);
	return select;
}
int Order_Icemain(){
	int select = 0;
	do
	{
		select = Order_IceMainUI(select);
		switch(select)
		{
			case 0:
				return 5;
			case 1:
				return 4;
			case 2:
				return 3;
			case 3:
				return 2;
			case 4:
				return 1;
			case 5:
				return 0;
			case 6:
				return -1;
			case 7:
				return -2;
		}
	}while(true);
}
//sugar function
void Order_SugarMainScreen(int select){
	system("cls");
	int i;
	char L[7],R[7];
	for(i=0;i<7;i++)
	{
		L[i] = ' ';
		R[i] = ' ';
	}
	L[select] = '[';
	R[select] = ']';
	cout<<"============================================================"<<endl;
	cout<<"              可   不   可   熟   成   紅   茶              "<<endl; 
	cout<<"============================================================"<<endl;
	cout << endl<< endl<< endl<< endl<< endl;
	cout<<"——————————————————————————————"<<endl;
	cout<<"                       請 選 擇 甜 度                       "<<endl; 
	cout<<"——————————————————————————————"<<endl;
	cout <<"                  "<< L[0] << "1" << R[0] <<"  1 0 0 %   正常糖" << endl;
	cout <<"                  "<< L[1] << "2" << R[1] <<"    7 0 %   少  糖" << endl;
	cout <<"                  "<< L[2] << "3" << R[2] <<"    5 0 %   半  糖" << endl;
	cout <<"                  "<< L[3] << "4" << R[3] <<"    3 0 %   微  糖" << endl;
	cout <<"                  "<< L[4] << "5" << R[4] <<"    2 0 %   二分糖" << endl;
	cout <<"                  "<< L[5] << "6" << R[5] <<"    1 0 %   一分糖" << endl;
	cout <<"                  "<< L[6] << "7" << R[6] <<"      0 %   無  糖" << endl;
}
int Order_SugarMainUI(int select){
	char x,x1;
	do{
		Order_SugarMainScreen(select);
		x = getch();
		if(x==-32)
		{
			x1 = getch();
			if(x1==72)
				select = (select + 6)%7;
			if(x1==80)
				select = (select + 1)%7;
			if(x1==77)
				x=13;
		}
		if(x>='1'&&x<='7')
			select = x - '1';
	}while(x!=13);
	return select;
}
int Order_Sugarmain(){
	int select = 0;
	do
	{
		select = Order_SugarMainUI(select);
		switch(select)
		{
			case 0:
				return 100;
			case 1:
				return 70;
			case 2:
				return 50;
			case 3:
				return 30;
			case 4:
				return 20;
			case 5:
				return 10;
			case 6:
				return 0;
		}
	}while(true);
}
//addition function 
void Order_AdditionMainScreen(int select){
	system("cls");
	int i;
	char L[3],R[3];
	for(i=0;i<3;i++)
	{
		L[i] = ' ';
		R[i] = ' ';
	}
	L[select] = '[';
	R[select] = ']';
	cout<<"============================================================"<<endl;
	cout<<"              可   不   可   熟   成   紅   茶              "<<endl; 
	cout<<"============================================================"<<endl;
	cout << endl<< endl<< endl<< endl<< endl;
	cout<<"——————————————————————————————"<<endl;
	cout<<"                    請 選 擇 加 購 項 目                    "<<endl; 
	cout<<"——————————————————————————————"<<endl;
	cout <<"                  "<< L[1] << "1" << R[1] << "      加白玉(+10元)" << endl;
	cout <<"                  "<< L[2] << "2" << R[2] << "      加墨玉(+15元)" << endl;
	cout <<"                  "<< L[0] << "0" << R[0] << "      不需要" << endl;
}
int Order_AdditionMainUI(int select){
	char x,x1;
	do{
		Order_AdditionMainScreen(select);
		x = getch();
		if(x==-32)
		{
			x1 = getch();
			if(x1==72)
				select = (select + 2)%3;
			if(x1==80)
				select = (select + 1)%3;
			if(x1==77)
				x=13;
		}
		if(x>='0'&&x<='2')
			select = x - '0';
	}while(x!=13);
	return select;
}
int Order_Additionmain(){
	int select = 1;
	do
	{
		select = Order_AdditionMainUI(select);
		switch(select)
		{
			case 0:
				return 0;
			case 1:
				return 10;
			case 2:
				return 15;
		}
	}while(true);
}
//cup function
int Order_Cupmain(){
	int cup;
	char c1,c2;
	char c[3];
	int n=0,i;
	do
	{	system("cls");
		cout<<"============================================================"<<endl;
		cout<<"              可   不   可   熟   成   紅   茶              "<<endl; 
		cout<<"============================================================"<<endl;
		cout << endl<< endl<< endl<< endl<< endl;
		cout<<"——————————————————————————————"<<endl;
		cout<<"                     請 輸 入 杯 數(0~99)                   "<<endl;
		cout<<"                    (輸入0以取消本次訂購)                   "<<endl;
		cout<<"——————————————————————————————"<<endl;
		cout<<"                        杯數: ";
		for(i=0;i<n;i++)
			cout<<c[i];//輸出到目前為止合法的字元 
		c1=getch();//看下一碼
		if(c1==-32||c1==0)//0跟32是特殊碼的開頭，把特殊碼的後一碼存到c2(後面不會處理c2)(特殊碼有兩位(eg:(-32,75)) 
			c2=getch();// 
		if(c1>='0'&&c1<='9')//如果合法，存到下一格，下次再一起輸出 
		{
			if(n==2)//如果n是12，強迫他改第11碼(也就是不會輸到第13碼)
			{
				c[1]=c1;	
			} 
			else
			{
				c[n]=c1;
				n++;
			}
		}
		if(c1==8&&n>0)//後退鍵 
			n--;
	}while(c1!=13||n==0);//判定按enter時輸入是不是空的(是空的就要繼續輸入)|c1!=13就還要繼續輸入 
	c[n]='\0';//在最後放停止 
	if(c[1]=='\0')
		cup=c[0]-'0';
	else
		cup=(c[0]-'0')*10+(c[1]-'0');
	return cup;
}
//create order
orderlist Order_CreateOrder(int drink_no,orderlist drinks,int order_no,int cart_no){
	drinks.list[order_no][cart_no].drinkno=drink_no;
	drinks.list[order_no][cart_no].size=Order_Sizemain();
	drinks.list[order_no][cart_no].ice=Order_Icemain();
	drinks.list[order_no][cart_no].sugar=Order_Sugarmain();
	drinks.list[order_no][cart_no].addition=Order_Additionmain();
	drinks.list[order_no][cart_no].cup=Order_Cupmain();
	return drinks;
}
int Order_CreatePrice(int price,int order_no,int cart_no,orderlist drinks,int flag){
	price+=5*flag*drinks.list[order_no][cart_no].size;
	price+=drinks.list[order_no][cart_no].addition;
	price*=drinks.list[order_no][cart_no].cup;
	return price;
}
//fin orderlist
orderlist LoadOrders(){
	orderlist drinks;
	ifstream fin;
	fin.open("orderlist.txt");
	fin>>drinks.orderno;
	fin>>drinks.mealno;
	fin>>drinks.earnings;
	for(int i=1;i<=drinks.orderno;i++)
	{
		fin>>drinks.WhoOrder[i];
		fin>>drinks.cart_no[i];
		fin>>drinks.OrderPrice[i];
		for(int j=1;j<=drinks.cart_no[i];j++)
		{
			fin>>drinks.list[i][j].drinkno;
			fin>>drinks.list[i][j].size;
			fin>>drinks.list[i][j].ice;
			fin>>drinks.list[i][j].sugar;
			fin>>drinks.list[i][j].addition;
			fin>>drinks.list[i][j].cup;
		}
	} 
	fin.close();
	return drinks;
}
void SaveOrders(orderlist drinks){
	ofstream fout;
	fout.open("orderlist.txt"); 
	fout<<drinks.orderno<<endl;
	fout<<drinks.mealno<<endl;
	fout<<drinks.earnings<<endl;
	for(int i=1;i<=drinks.orderno;i++)
	{
		fout<<drinks.WhoOrder[i]<<endl;
		fout<<drinks.cart_no[i]<<endl;
		fout<<drinks.OrderPrice[i]<<endl;
		for(int j=1;j<=drinks.cart_no[i];j++)
		{
			fout<<drinks.list[i][j].drinkno<<endl;
			fout<<drinks.list[i][j].size<<endl;
			fout<<drinks.list[i][j].ice<<endl;
			fout<<drinks.list[i][j].sugar<<endl;
			fout<<drinks.list[i][j].addition<<endl;
			fout<<drinks.list[i][j].cup<<endl;
		}
	} 
	fout.close();
}
void ReadOrder_MainScreen(int select){
	system("cls");
	int i;
	char L[4],R[4];
	for(i=0;i<4;i++)
	{
		L[i] = ' ';
		R[i] = ' ';
	}
	L[select] = '[';
	R[select] = ']';
	cout<<"============================================================"<<endl;
	cout<<"              可   不   可   熟   成   紅   茶              "<<endl; 
	cout<<"============================================================"<<endl;
	cout << endl<< endl<< endl<< endl<< endl;
	cout<<"——————————————————————————————"<<endl;
	cout<<"                       查  詢  訂  單                       "<<endl; 
	cout<<"——————————————————————————————"<<endl;
	cout <<"                  "<< L[1] << "1" << R[1] << "製作中的訂單明細" << endl;
	cout <<"                  "<< L[2] << "2" << R[2] << "您的歷史訂購紀錄" << endl;
	cout <<"                  "<< L[3] << "3" << R[3] << "    取消訂單    " << endl;	
	cout <<"                  "<< L[0] << "0" << R[0] << "      離開      " << endl;
}
int ReadOrder_MainUI(int select){
	char x,x1;
	do{
		ReadOrder_MainScreen(select);
		x = getch();
		if(x==-32)
		{
			x1 = getch();
			if(x1==72)
				select = (select + 3)%4;
			if(x1==80)
				select = (select + 1)%4;
			if(x1==77)
				x=13;
		}
		if(x>='0'&&x<='3')
			select = x - '0';
	}while(x!=13);
	return select;
}
void ReadOrders_Main(int user_id){
	orderlist drinks;
	drinks=LoadOrders();
	int select = 1,flag=1;
	do
	{
		select = ReadOrder_MainUI(select);
		switch(select)
		{
			case 1:
				ReadOrders(user_id,0);
				break;
			case 2:
				ReadOrders(user_id,1);
				break;
			case 3:
				CancelOrder(user_id,drinks);
				drinks=LoadOrders();
				break;
			case 0:
				flag=0;
				break;
		}
	}while(flag==1);
}
void ReadOrders(int user_id,int flag){
	orderlist drinks;
	drinks=LoadOrders();
	int i;
	system("cls");
	cout<<"============================================================"<<endl;
	cout<<"              可   不   可   熟   成   紅   茶              "<<endl; 
	cout<<"============================================================"<<endl;
	cout << endl<< endl<< endl<< endl<< endl;
	cout<<"——————————————————————————————"<<endl;
	cout<<"                       ";
	if(flag>=0)
		cout<<"查  詢";
	else
		cout<<"取  消";
	cout<<"  訂  單                       "<<endl; 
	cout<<"——————————————————————————————"<<endl;
	if(flag==0||flag==-1)
	{
		cout<<"                      正在製作的訂單: "<<drinks.mealno<<endl<<endl;
		i=drinks.mealno;
	}
	else
	{
		cout<<"                          歷史訂單"<<endl<<endl<<endl;
		i=1;
	}	
	while(i<=drinks.orderno)
	{
		if(drinks.WhoOrder[i]==user_id)
		{
			if(i!=0) 
				cout<<"                         訂單編號: "<<i<<endl; 
			for(int j=1;j<=drinks.cart_no[i];j++)
			{
				switch(drinks.list[i][j].drinkno)
				{
					case 1:
						cout<<"                         熟成紅茶"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 2:
						cout<<"                         麗春紅茶"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 3:
						cout<<"                         太妃紅茶"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 4:
						cout<<"                         胭脂紅茶"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 5:
						cout<<"                         雪藏紅茶"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 6:
						cout<<"                         熟成冷露"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 7:
						cout<<"                         春芽冷露"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 8:
						cout<<"                         春芽綠茶"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 9:
						cout<<"                         熟成歐蕾"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 10:
						cout<<"                         白玉歐蕾"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 11:
						cout<<"                         胭脂多多"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 12:
						cout<<"                         黃玉歐蕾"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
				}
				switch(drinks.list[i][j].size)
				{
					case 0:
						cout<<"                   中杯/";
						break;
					case 1:
						cout<<"                   大杯/";
						break;
				}
				switch(drinks.list[i][j].ice)
				{
					case 5:
						cout<<"正常冰/";
						break;
					case 4:
						cout<<"少冰/";
						break;
					case 3:
						cout<<"微冰/";
						break;
					case 2:
						cout<<"去冰/";
						break;
					case 1:
						cout<<"完全去冰/";
						break;
					case 0:
						cout<<"常溫/";
						break;
					case -1:
						cout<<"溫/";
						break;
					case -2:
						cout<<"熱/";
						break;
				}
				switch(drinks.list[i][j].sugar)
				{
					case 100:
						cout<<"正常糖";
						break;
					case 70:
						cout<<"少糖";
						break;
					case 50:
						cout<<"半糖";
						break;
					case 30:
						cout<<"微糖";
						break;
					case 20:
						cout<<"二分糖";
						break;
					case 10:
						cout<<"一分糖";
						break;
					case 0:
						cout<<"無糖";
						break;
				}
				switch(drinks.list[i][j].addition)
				{
					case 10:
						cout<<"/加白玉"<<endl;
						break;
					case 15:
						cout<<"/加墨玉"<<endl;
						break;
					case 0:
						cout<<endl; 
						break;
				}
			}
			cout<<endl;
		}
		i++;
	}
	if(flag!=-1)
	{
		cout<<"——————————————————————————————"<<endl;
		cout<<"                       請按任意鍵繼續:";
		getch(); 
	}
}
void CancelOrder(int user_id,orderlist drinks){
	int Cancel_ID,i,flag=0;	
	ofstream fout;
	userlist users;
	users=LoadUsers();
	do{
		system("cls");
		ReadOrders(user_id,-1);
		cout<<"——————————————————————————————"<<endl;
		cout<<"              請輸入想要取消的訂單，或輸入0以離開: ";
		cin>>Cancel_ID;
		if(Cancel_ID==0)
			flag=1;
		else if(Cancel_ID>drinks.orderno||Cancel_ID<0)
		{
			cout<<endl<<endl<<"                          查無此訂單"<<endl;
			cout<<"——————————————————————————————"<<endl;
			cout<<"                        請按任意鍵繼續:";
			getch(); 
		}
		else if(Cancel_ID<drinks.mealno)
		{
			cout<<endl<<endl<<"                         此訂單已完成!"<<endl;
			cout<<"——————————————————————————————"<<endl;
			cout<<"                        請按任意鍵繼續:";
			getch(); 
		}
		else if(drinks.WhoOrder[Cancel_ID]!=user_id)
		{
			cout<<endl<<endl<<"                       您無法取消此訂單!"<<endl;
			cout<<"——————————————————————————————"<<endl;
			cout<<"                        請按任意鍵繼續:";
			getch(); 
		}
		else
			flag=1;
	}while(flag==0);
	if(Cancel_ID!=0)
	{
		cout<<endl<<endl<<"                已取消訂單，已退回發財金"<<drinks.OrderPrice[Cancel_ID]<<"元"<<endl; 
		drinks.earnings-=drinks.OrderPrice[Cancel_ID];
		users.member[user_id].money+=drinks.OrderPrice[Cancel_ID];
		fout.open("orderlist.txt"); 
		fout<<drinks.orderno-1<<endl;
		fout<<drinks.mealno<<endl;
		fout<<drinks.earnings<<endl;
		for(i=1;i<=drinks.orderno;i++)
		{
			if(i!=Cancel_ID)
			{
				fout<<drinks.WhoOrder[i]<<endl;
				fout<<drinks.cart_no[i]<<endl;
				fout<<drinks.OrderPrice[i]<<endl;
				for(int j=1;j<=drinks.cart_no[i];j++)
				{
					fout<<drinks.list[i][j].drinkno<<endl;
					fout<<drinks.list[i][j].size<<endl;
					fout<<drinks.list[i][j].ice<<endl;
					fout<<drinks.list[i][j].sugar<<endl;
					fout<<drinks.list[i][j].addition<<endl;
					fout<<drinks.list[i][j].cup<<endl;
				}
			}
		} 
		fout.close();	
		SaveUsers(users);
	}
	cout<<endl<<endl<<endl;
	cout<<"——————————————————————————————"<<endl;
	cout<<"                        請按任意鍵繼續:";
	getch(); 
}
//function for Sudoku
int Sudoku_Main(userlist users,int user_id){
	int r,c,n,modified=1,count=0;
	int Q[9][9];//二維陣列，值是要瑱的數字 
	int A[9][9];//存正確答案 
	int A2[9][9];//存你填的答案 
	int pool[9][9][10];//前兩格是二維陣列(0,0)~(8,8)，後一格是能填的數字(1~9)，值是0或1(能不能填) 
	Sudoku_Init(pool);
	Sudoku_Read(1,Q,pool);
	for(r=0;r<9;r++)//copy到答案(A)的陣列 
		for(c=0;c<9;c++)
		{
			A[r][c]=Q[r][c];
			A2[r][c]=Q[r][c];
		}	
	cout<<endl;
	Sudoku_Cutscenes(users,user_id);
	Sudoku_MainUI(Q,A2);
	while(modified==1)//modified是開關，預設是1，進入是0，如果有可以填的便填上，再打開開關(讓他重做) 
	{
		modified=0;
		for(r=0;r<9;r++)
		{
			for(c=0;c<9;c++)
			{
				if(A[r][c]==0)//還沒填(空白的) 
				{
					n=Sudoku_Check(pool,r,c);//0-9中有沒有唯一解，0是沒有 
					if(n>0)
					{
						A[r][c]=n;
						Sudoku_Update(pool,r,c,n);//更新 
						modified=1;//開開關 
					}
				}
			}
		}
	}	
	//check if A and A2 is equal
	int flag=1;
	for(r=0;r<9;r++)
		for(c=0;c<9;c++)
		{
			if(A[r][c]!=A2[r][c])
			{
				flag=0;
				count++;
			}
		}
	cout<<endl<<endl<<endl;
	cout<<"———————————————————————————————————"<<endl;
	if(flag==1)
	{
		cout<<"                     全對!恭喜獲得20塊發財金!"<<endl;
		return 20;
	}	
	else
	{
		if(count<=20)
		{
			cout<<"                     共答錯"<<count<<"格，獲得"<<20-count<<"元發財金"<<endl;
			return 20-count;
		}
		else
		{
			cout<<"                     共答錯"<<count<<"格，獲得0元發財金"<<endl;
			return 0;
		}	
	}
}
void Sudoku_Init(int p[][9][10]){
	int r,c,n;
	for(r=0;r<9;r++)
		for(c=0;c<9;c++)
			for(n=1;n<=9;n++)
				p[r][c][n]=1;
}
void Sudoku_Update(int p[][9][10],int R,int C,int N){
	int r,c,n;
	// the same row
	for(c=0;c<9;c++) 
		p[R][c][N] = 0;
	// the same col
	for(r=0;r<9;r++)
		p[r][C][N] = 0;
	// the same block
	for(r=R/3*3;r<=R/3*3+2;r++)//(0,1,2從0開始;3,4,5從3開始;6,7,8從6開始)
		for(c=C/3*3;c<=C/3*3+2;c++)
			p[r][c][N] = 0;
	for(n=1;n<=9;n++)//更新他的資料庫 
		if(n!=N)
			p[R][C][n]=0;
	p[R][C][N] = 1;
}
void Sudoku_Read(int Qno,int Q[][9],int p[][9][10]){
	int r,c,n,q;
	srand(time(NULL));
	q=rand()%3;
	ifstream fin;
	if(q==0)
		fin.open("Q1.txt");
	else if(q==1)
		fin.open("Q2.txt");
	else
		fin.open("Q3.txt");
	for(r=0;r<9;r++)
	{
		for(c=0;c<9;c++)
		{
			fin>>n;
			Q[r][c]=n;
			if(n>0)//不是0(空白)的話便要更新(跟同行同列同九宮格的n不能填) 
				Sudoku_Update(p,r,c,n);
		}
	}
	fin.close();
}
int Sudoku_Check(int p[][9][10],int R,int C){		
	int sum=0,n,a,r,c,tmp;
	for(n=1;n<=9;n++)//如果跟他同行的都不能填n，那格就填他 
	{
		tmp=0;
		for(r=0;r<9;r++)
		{
			if(r==R)
				continue;
			tmp+=p[r][C][n];
		}
		if(tmp==0)
			return n;
	}	
	for(n=1;n<=9;n++)//如果跟他同列的都不能填n，那格就填他 
	{
		tmp=0;
		for(c=0;c<9;c++)
		{
			if(c==C)
				continue;
			tmp+=p[R][c][n];
		}
		if(tmp==0)
			return n;
	}	
	for(n=1;n<=9;n++)//如果跟他同九宮格的都不能填n，那格就填他 
	{
		tmp=0;
		for(r=R/3*3;r<=R/3*3+2;r++)
			for(c=C/3*3;c<=C/3*3+2;c++)
			{
				if(r==R&&c==C)
					continue;
				tmp+=p[r][c][n];	
			}
		if(tmp==0)
			return n;
	}	
	sum=0;
	for(n=1;n<=9;n++)//檢查自己是不是有唯一解 
	{
		sum+=p[R][C][n];//全部加起來(等於2就出局) 
		if(p[R][C][n]==1)
			a=n;
	}
	if(sum==1)//等於1就是有唯一解 
		return a;
	else
		return 0;
}
void Sudoku_Print(int Q[][9],int A[][9],int R, int C){

	int r,c;
	system("cls");//清空螢幕 
	cout<<"———————————————————————————————————"<<endl;
	cout<<"            _______ _     _ ______   _____  _     _ _     _           "<<endl;
	cout<<"            |______ |     | |     \\ |     | |____/  |     |           "<<endl;
	cout<<"            ______| |_____| |_____/ |_____| |    \\_ |_____|           "<<endl<<endl;                                          
	cout<<"———————————————————————————————————"<<endl<<endl<<endl<<endl;
	char left[9][9],right[9][9];//準備81格存左括號跟右括號 
	for(r=0;r<9;r++)
		for(c=0;c<9;c++)
		{
			left[r][c]=' ';
			right[r][c]=' ';
		}
	if(Q[R][C]==0)
	{
		left[R][C]='<';
		right[R][C]='>';
	}
	else
	{
		left[R][C]='[';
		right[R][C]=']';
	}
	for(r=0;r<9;r++)
	{
		cout<<"                     ";
		for(c=0;c<9;c++)
		{
			cout<<left[r][c];//輸出<>or[] 
			if(A[r][c]==0)//沒填的輸出空格
				cout<<" ";
			else
				cout<<A[r][c];
			cout<<right[r][c];	
			if(c==2||c==5)
				cout<<"|";
		}
		cout<<endl;
		if(r==2||r==5)
			cout<<"                     -----------------------------                     "<<endl;
	}
}
void Sudoku_MainUI(int Q[][9], int A[][9]){
	int r=0,c=0;//roll&column
	char c1,c2;
	do
	{
		Sudoku_Print(Q,A,r,c);
		c1=getch();
		if(c1==-32)//特殊鍵是-32,? 
		{
			c2=getch();
			switch(c2)
			{
				case 72://up
					r=(r+8)%9;
					break;
				case 75://left
					c=(c+8)%9;
					break;
				case 77://right
					c=(c+1)%9;
					break;
				case 80://down
					r=(r+1)%9;
					break;			
			}
		}
		if(c1>='0'&&c1<='9')
		{
			if(Q[r][c]==0)
				A[r][c]=c1-'0';
		}
	}while(c1!=13);//不是enter 
}
void Sudoku_Cutscenes(userlist users,int user_id){
	system("cls");//清空螢幕 
	cout<<"———————————————————————————————————"<<endl;
	cout<<"            _______ _     _ ______   _____  _     _ _     _           "<<endl;
	cout<<"            |______ |     | |     \\ |     | |____/  |     |           "<<endl;
	cout<<"            ______| |_____| |_____/ |_____| |    \\_ |_____|           "<<endl<<endl;                                        
	cout<<"———————————————————————————————————"<<endl;
	cout<<"                   遊戲由9個3 ×3個的九宮格組成。                   "<<endl<<endl;
	cout<<"         每一行列的數字均須包含1～9，不能缺少，也不能重複。         "<<endl<<endl; 
	cout<<"每一宮(粗黑線圍起來的區域)的數字均須包含 1～9，不能缺少，也不能重複。 "<<endl<<endl;
	cout<<"----------------------------------------------------------------------"<<endl;
	cout<<"                           您目前已遊玩"<<users.member[user_id].Sudokutime<<"次                           "<<endl; 
	cout<<"                           請按任意鍵開始:";
	getch();	
}
//function for XAXB
void XAXB_num2digit(int num,int digit[]){//把數字拆成arrey 
	digit[0]=num/1000;
	digit[1]=num%1000/100;
	digit[2]=num%100/10;
	digit[3]=num%10;
}
bool XAXB_isLegal(int num){//判定數字是不是合法
	int d[4],i,j;
	XAXB_num2digit(num,d);
	for(i=0;i<3;i++)
	{
		for(j=i+1;j<4;j++)
		{
			if(d[i]==d[j])
				return false;
		}
	}
	return true;
}
void XAXB_Check(int G,int A,int AB[]){//對答案，A放在AB[0]，B放在AB[1] 
	AB[0]=0;
	AB[1]=0;
	int GD[4];//guestdigit
	int AD[4];//answerdigit
	int i,j;
	XAXB_num2digit(G,GD);
	XAXB_num2digit(A,AD);
	for(i=0;i<4;i++)
	{
		if(GD[i]==AD[i])
			AB[0]++;
	}
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(GD[i]==AD[j])
				AB[1]++;
		}
	}
	if(AB[0]!=0)
		AB[1]-=AB[0];
}
int XAXB_Main(userlist users,int user_id){	
	XAXB_Cutscenes(users,user_id);
	system("cls");
	cout<<"———————————————————————————————————————"<<endl;
	cout<<"                      XX    XX   AAA   XX    XX BBBBB                         "<<endl;
	cout<<"                       XX  XX   AAAAA   XX  XX  BB   B                        "<<endl;
	cout<<"                        XXXX   AA   AA   XXXX   BBBBBB                        "<<endl;
	cout<<"                       XX  XX  AAAAAAA  XX  XX  BB   BB                       "<<endl;
	cout<<"                      XX    XX AA   AA XX    XX BBBBBB                        "<<endl;
	cout<<"———————————————————————————————————————"<<endl;
	srand(time(NULL));
	int comG,comA,userG,userA,count=0;
	int comAB[2],userAB[2],tmpAB[2];//0==A,1==B
	do{
		comA=rand()%10000;
	}while(XAXB_isLegal(comA)==false);//(電腦的答案)如果亂數產出來的數字不合法就重產 
	do{
		cout<<"                      請輸入您的答案: ";
		cin>>userA;
	}while(XAXB_isLegal(userA)==false);//(玩家的答案)如果輸入的數字不合法就重輸入 
	int pool[10000];
	int i;
	for(i=0;i<10000;i++)//給預設值(0000=0,1234=1>>合法給1，不合法給0) 
	{
		if(XAXB_isLegal(i))//isLegal==true 
			pool[i]=1;
		else
			pool[i]=0;
	}
	do{
		do{
		cout<<"                      請輸入您想猜測的數字: ";
		cin>>userG;
		}while(XAXB_isLegal(userG)==false);
		for(i=0;i<10000;i++)
			if(pool[i]==1)
				break;	
		comG=i;
		XAXB_Check(comG,userA,comAB);
		XAXB_Check(userG,comA,userAB);
		count++;
		cout<<"                      ("<<count<<")"<<"Com Guess: "<<comG<<"	 "<<comAB[0]<<"A"<<comAB[1]<<"B"<<endl;
		cout<<"                         "<<"User Guess: "<<userG<<"	 "<<userAB[0]<<"A"<<userAB[1]<<"B"<<endl;
		for(i=0;i<10000;i++)
		{
			if(pool[i]==1)
			{
				XAXB_Check(comG,i,tmpAB);
				if(tmpAB[0]!=comAB[0]||tmpAB[1]!=comAB[1])
					pool[i]=0;
			}
		} 
	}while(comAB[0]!=4&&userAB[0]!=4);
	if(comAB[0]<userAB[0])
	{
		users.member[user_id].XAXBwin++;
		SaveUsers(users);
		cout<<endl;
		cout<<"———————————————————————————————————————"<<endl;
		cout<<"                      你贏了!爽啊刺啊!爽賺20!"<<endl;
		return 20;
	}	
	else if(comAB[0]>userAB[0]) 
	{
		users.member[user_id].XAXBloss++;
		SaveUsers(users);
		cout<<endl;
		cout<<"———————————————————————————————————————"<<endl;
		cout<<"                      你輸了!7414啦!不給你錢!"<<endl;
		return 0;
	}
	else
	{
		users.member[user_id].XAXBeven++;
		SaveUsers(users);
		cout<<endl;
		cout<<"———————————————————————————————————————"<<endl;
		cout<<"                      平手!給你10塊!"<<endl;
		return 10;
	}
}
void XAXB_Cutscenes(userlist users,int user_id){
	system("cls");//清空螢幕 
	cout<<"———————————————————————————————————————"<<endl;
	cout<<"                      XX    XX   AAA   XX    XX BBBBB                         "<<endl;
	cout<<"                       XX  XX   AAAAA   XX  XX  BB   B                        "<<endl;
	cout<<"                        XXXX   AA   AA   XXXX   BBBBBB                        "<<endl;
	cout<<"                       XX  XX  AAAAAAA  XX  XX  BB   BB                       "<<endl;
	cout<<"                      XX    XX AA   AA XX    XX BBBBBB                        "<<endl;
	cout<<"———————————————————————————————————————"<<endl;
    cout<<"              你與電腦各設定一組四碼的數字作為謎底，交給對方猜。              "<<endl<<endl; 
	cout<<"每猜一個數，出數者就要根據這個數字給出提示，提示以XAYB形式呈現，直到猜中為止。"<<endl<<endl;
	cout<<"      其中X表示位置正確的數的個數，而Y表示數字正確而位置不對的數的個數。      "<<endl<<endl;                        
	cout<<"———————————————————————————————————————"<<endl;
	cout<<"                           您目前的戰績為"<<users.member[user_id].XAXBwin<<"勝"<<users.member[user_id].XAXBloss<<"敗"<<users.member[user_id].XAXBeven<<"和  "<<endl; 
	cout<<"———————————————————————————————————————"<<endl;
	cout<<"                           請按任意鍵開始:";
	getch();	
}
//function for chatroom
void Chatroom_Main(char un[],userlist users){
	char talk[100];
	int i,flag=1;
	ifstream fin;
	ofstream fout;
	do{
		system("cls");
		cout<<" ——————————————————————————————"<<endl;
		cout<<"|   請輸入Exit以離開聊天室，輸入特定的使用者名稱以進行私聊   |"<<endl; 
		cout<<" ——————————————————————————————"<<endl;
		fin.open("msg.txt");//讀聊天室 
		while(!fin.eof())//到檔案結尾時停住 
		{
			fin.getline(talk,99);//從檔案中讀一整行
			cout<<talk<<endl;//輸出一行 
		}
		fin.close();
		cout<<"---------------------------------------------"<<endl;
		cout<<un<<" :";
		cin.getline(talk,99); 
		if(strcmp(talk,"Exit")==0||strcmp(talk,"exit")==0)
			break;
		for(i=0;i<users.user_no;i++)
		{
			if(strcmp(talk,users.member[i].nickname)==0)
			{
				flag=0;
				PrivateChatroom_Main(talk,un);
			}
		}
		if(flag==0)
			break;
		if(strlen(talk)>0)
		{	
			fout.open(("msg.txt"),std::ofstream::app);//預設是複寫，加std::ofstream::app是把它改成加上去 
			fout<<un<<" :"<<talk<<endl;//把打的話加進聊天室中(用加上去的而不是複寫)
			fout.close(); 
		}
	}while(true);
}
void PrivateChatroom_Main(char un1[],char un2[]){//un1收件un2寄件 
	char talk[100];
	ifstream fin;
	ofstream fout;
	int flag,i;
	do{
		system("cls");
		cout<<" ——————————————"<<endl;
		cout<<"|   請輸入Exit以離開聊天室   |"<<endl; 
		cout<<" ——————————————"<<endl;
		fin.open("privatechat.txt");//讀聊天室 
		while(!fin.eof())//到檔案結尾時停住 
		{
			flag=1;
			fin.getline(talk,99);//從檔案中讀一整行
			for(i=0;i<strlen(un1);i++)
			{
				if(talk[i]!=un1[i])
					flag=0;	
			}
			for(i=strlen(un1)+1;i<strlen(un1)+1+strlen(un2);i++)
			{
				if(talk[i]!=un2[i-(strlen(un1)+1)])
					flag=0;	
			}
			if(flag==1)
			{
				for(i=strlen(un1)+1;i<strlen(talk);i++)
					cout<<talk[i];
				cout<<endl;
			}	
			flag=1;
			for(i=0;i<strlen(un2);i++)
			{
				if(talk[i]!=un2[i])
					flag=0;	
			}
			for(i=strlen(un2)+1;i<strlen(un2)+1+strlen(un1);i++)
			{
				if(talk[i]!=un1[i-strlen(un2)-1])
					flag=0;	
			}
			if(flag==1)
			{
				for(i=strlen(un2)+1;i<strlen(talk);i++)
					cout<<talk[i];
				cout<<endl;
			}
				
		}
		fin.close();
		cout<<"---------------------------------------------"<<endl;
		cout<<un2<<" :";
		cin.getline(talk,99);
		if(strcmp(talk,"Exit")==0||strcmp(talk,"exit")==0)
			break;
		if(strlen(talk)>0)
		{	
			fout.open(("privatechat.txt"),std::ofstream::app);//預設是複寫，加std::ofstream::app是把它改成加上去 
			fout<<un1<<","<<un2<<" :"<<talk<<endl;//把打的話加進聊天室中(用加上去的而不是複寫)
			fout.close(); 
		}
	}while(true);
}
//function for KEBUKE
void KEBUKEMainScreen(int select){
	orderlist drinks;
	drinks=LoadOrders();
	system("cls");
	int i;
	char L[3],R[3];
	for(i=0;i<3;i++)
	{
		L[i] = ' ';
		R[i] = ' ';
	}
	L[select] = '[';
	R[select] = ']';
	cout<<"============================================================"<<endl;
	cout<<"              可   不   可   熟   成   紅   茶              "<<endl; 
	cout<<"============================================================"<<endl;
	cout << endl<< endl<< endl<< endl<< endl;
	cout<<"——————————————————————————————"<<endl;
	cout<<"                       店  家  登  入                       "<<endl; 
	cout<<"——————————————————————————————"<<endl;
	cout<<"                     截至目前的累積收入: "<<drinks.earnings<<endl; 
	cout<<endl<<endl<<endl<<endl<<endl;
	cout <<"                  "<< L[1] << "1" << R[1] << "     查詢訂單" << endl;
	cout <<"                  "<< L[2] << "2" << R[2] << "     顧客儲值" << endl;
	cout <<"                  "<< L[0] << "0" << R[0] << "     離開系統" << endl;
}
int KEBUKEMainUI(int select){
	char x,x1;
	do{
		KEBUKEMainScreen(select);
		x = getch();
		if(x==-32)
		{
			x1 = getch();
			if(x1==72)
				select = (select + 2)%3;
			if(x1==80)
				select = (select + 1)%3;
			if(x1==77)
				x=13;
		}
		if(x>='0'&&x<='2')
			select = x - '0';
	}while(x!=13);
	return select;
}
void KEBUKE_Main(){
	int select =1,flag=1;
	do
	{
		select = KEBUKEMainUI(select);
		switch(select)
		{
			case 1:
				KEBUKE_DoOrders();
				break;
			case 2:
				KEBUKE_Deposit(); 
				break;
			case 0:
				flag=0;
				break;
		}
		if(flag==0)
			break;
	}while(true);
}
void KEBUKE_DoOrders(){
	char c1,c2;
	int flag=1,i;
	orderlist drinks;
	drinks=LoadOrders();
	for(i=1;i<=drinks.orderno;i++)
	{
		flag=1;
		system("cls");
		cout<<"============================================================"<<endl;
		cout<<"              可   不   可   熟   成   紅   茶              "<<endl; 
		cout<<"============================================================"<<endl;
		cout << endl<< endl<< endl<< endl<< endl;
		cout<<"——————————————————————————————"<<endl;
		cout<<"                       查  詢  訂  單                       "<<endl; 
		cout<<"——————————————————————————————"<<endl;
		cout<<endl<<endl<<endl<<endl<<endl;
		if(i==drinks.mealno)
		{
			flag=0;
			cout<<"                       編號: "<<i<<endl; 
			for(int j=1;j<=drinks.cart_no[i];j++)
			{
				switch(drinks.list[i][j].drinkno)
				{
					case 1:
						cout<<"                     熟成紅茶"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 2:
						cout<<"                     麗春紅茶"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 3:
						cout<<"                     太妃紅茶"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 4:
						cout<<"                     胭脂紅茶"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 5:
						cout<<"                     雪藏紅茶"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 6:
						cout<<"                     熟成冷露"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 7:
						cout<<"                     春芽冷露"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 8:
						cout<<"                     春芽綠茶"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 9:
						cout<<"                     熟成歐蕾"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 10:
						cout<<"                     白玉歐蕾"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 11:
						cout<<"                     胭脂多多"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 12:
						cout<<"                     黃玉歐蕾"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
				}
				switch(drinks.list[i][j].size)
				{
					case 0:
						cout<<"                     中杯/";
						break;
					case 1:
						cout<<"                     大杯/";
						break;
				}
				switch(drinks.list[i][j].ice)
				{
					case 5:
						cout<<"正常冰/";
						break;
					case 4:
						cout<<"少冰/";
						break;
					case 3:
						cout<<"微冰/";
						break;
					case 2:
						cout<<"去冰/";
						break;
					case 1:
						cout<<"完全去冰/";
						break;
					case 0:
						cout<<"常溫/";
						break;
					case -1:
						cout<<"溫/";
						break;
					case -2:
						cout<<"熱/";
						break;
				}
				switch(drinks.list[i][j].sugar)
				{
					case 100:
						cout<<"正常糖";
						break;
					case 70:
						cout<<"少糖";
						break;
					case 50:
						cout<<"半糖";
						break;
					case 30:
						cout<<"微糖";
						break;
					case 20:
						cout<<"二分糖";
						break;
					case 10:
						cout<<"一分糖";
						break;
					case 0:
						cout<<"無糖";
						break;
				}
				switch(drinks.list[i][j].addition)
				{
					case 10:
						cout<<"/加白玉"<<endl;
						break;
					case 15:
						cout<<"/加墨玉"<<endl;
						break;
					case 0:
						cout<<endl; 
						break;
				}
			}
			cout<<"——————————————————————————————"<<endl;
			cout<<"                   請按下向下鍵或PgDn以送出訂單"<<endl;
			cout<<"                   請按下ESC鍵以離開"<<endl; 
			do{
				c1=getch();
				if(c1==-32)
				{
					c2=getch();
					if(c2==80||c2==81)
						break;
				}
				if(c1==27)
				{
					flag=-1;
					break;
				}	
			}while(true);
			if(flag==0)
				drinks.mealno++;	
			else
			{
				SaveOrders(drinks);
				break;
			}
		}
	}
	if(flag==1||i>drinks.orderno)
	{
		SaveOrders(drinks);
		system("cls");
		cout<<"============================================================"<<endl;
		cout<<"              可   不   可   熟   成   紅   茶              "<<endl; 
		cout<<"============================================================"<<endl;
		cout << endl<< endl<< endl<< endl<< endl;
		cout<<"——————————————————————————————"<<endl;
		cout<<"                       查  詢  訂  單                       "<<endl; 
		cout<<"——————————————————————————————"<<endl;
		cout<<endl<<endl<<endl<<endl<<endl;
		cout<<"                   目前尚無需要製作的訂單"<<endl;
		cout<<"——————————————————————————————"<<endl;
		cout<<"               	  請按任意鍵繼續:";
		getch(); 
	}
}
void KEBUKE_Deposit(){
	userlist users;
	users=LoadUsers();
	int id,i,addmoney,flag;
	do{
		flag=1;
		system("cls");
		cout<<"============================================================"<<endl;
		cout<<"              可   不   可   熟   成   紅   茶              "<<endl; 
		cout<<"============================================================"<<endl;
		cout << endl<< endl<< endl<< endl<< endl;
		cout<<"——————————————————————————————"<<endl;
		cout<<"                       顧  客  儲  值                       "<<endl; 
		cout<<"——————————————————————————————"<<endl;
		cout<<endl<<endl<<endl<<endl<<endl;
		cout<<"                    請輸入顧客編號，輸入-1以離開: ";
		cin>>id;
		if(id==-1)
			break;
		for(i=0;i<users.user_no;i++)
		{
			if(i==id)
			{
				cout<<endl<<"                    請輸入儲值金額: ";
				cin>>addmoney;
				users.member[i].money+=addmoney;
				SaveUsers(users);
				cout<<endl<<"                    儲值完成。"<<endl;
				cout<<"——————————————————————————————"<<endl;
				cout<<"               	   請按任意鍵繼續:";
				getch(); 
				flag=0;
				break;
			}
		}
		if(i==users.user_no&&flag==1)
		{
			cout<<"                    查無此顧客，請重新輸入。"<<endl;
			cout<<"——————————————————————————————"<<endl;
			cout<<"               	   請按任意鍵繼續:";
			getch();
		}
	}while(flag==1);
}

