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
	int login_no;//�n�J���� 
	int money;//�x�Ȫ� 
	int XAXBwin,XAXBeven,XAXBloss;
	int Sudokutime;
};
struct userlist{
	int user_no;//�M�椤���X�ӤH 
	user member[100];//�̦h�N�O100��user 
};
struct drink{
	int drinkno;//���~ 
	int size;//�j�p 
	int ice;//�B�� 
	int sugar;//���� 
	int addition;//�[�ï] 
	int cup;//�M�� 
};
struct orderlist{
	int mealno;//�s�񥿦b�s�@���渹
	int orderno;//�s��{�b�`�@���h�֭q��
	int earnings;
	int WhoOrder[100];//100��user�̭��O�֪��� 
	int OrderPrice[100];
	int cart_no[100];//�@���q�椤���ʪ����̦��X�� 
	drink list[100][10];//�s��Ҧ��U���I�L���q��(orderno)||�s�ʪ���(no) 
};
//function for user interface
userlist LoadUsers();//Ū��
void SaveUsers(userlist users);//�g��
int Login(userlist users);//��J�b���K�X�ΧP�_�M��̬O�_���o�ձb�K 
void CreateAccount(userlist users);//�Ыطs�b�� 
void input_username(char un[],char ni[],int flag);//��Jusername 
void input_password(char un[],char ni[],char pw[],char checkpw[],int flag);//��J�K�X(�P�ɤ]�n�L�O����user) 
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
void Sudoku_Init(int p[][9][10]);//�Ҧ���l[(0,0)~(9,9)]�����1-9
void Sudoku_Update(int p[][9][10],int R,int C,int N);//�⤣���Ʀrn����l��N(���Ӽ�)�令0(���](6,8)�쥻�O(100100000)->�i�H��1��4�A�{�b���H�I�s��4�����A�ҥH�ܦ�(100000000)
void Sudoku_Read(int Qno,int Q[][9],int p[][9][10]);//Ū�� 
void Sudoku_Print(int Q[][9],int A[][9],int R, int C);//�L��u��A�� 
int Sudoku_Check(int p[][9][10],int R,int C);//�^�ǰߤ@�ѡA�p�G�S���N�^��0 
void Sudoku_MainUI(int Q[][9], int A[][9]);//�����a��Ʀr 
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
	enter=time(NULL);//�}�l�p�� 
	char c[2];
	int user_id;
	userlist users;
	users=LoadUsers();//��userŪ�i�� 
	user_id=Login(users);//�^�Ǥ@��user
	if(user_id!=-1)//���JMainScreen 
	{
		users=LoadUsers();//�]���i�঳��s�L�A�ҥH��Ū�@�� 
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
						cout<<"�Ы����N���~��:";
						getch();
						break;
					case 2:
						ReadOrders_Main(user_id);
						users=LoadUsers();
						cout<<endl<<endl<<endl<<endl<<endl;
						cout<<"------------------------------------------------------------------------------------------"<<endl;
						cout << "�Ы����N���~��:";
						getch();
						break;
					case 3:
						Changepw(users,user_id);
						users=LoadUsers();//����s�L�A�ҥH��Ū�@�� 
						break;
					case 4:
						Chatroom_Main(users.member[user_id].nickname,users);
						cout<<endl<<endl<<endl<<endl<<endl;
						cout<<"------------------------------------------------------------------------------------------"<<endl;
						cout << "�Ы����N���~��:";
						getch();
						break;
					case 5:
						users.member[user_id].money+=Sudoku_Main(users,user_id);
						users.member[user_id].Sudokutime++;
						SaveUsers(users);
						cout<<endl<<endl<<endl<<endl<<endl;
						users=LoadUsers();//����s�L�A�ҥH��Ū�@�� 
						cout<<"------------------------------------------------------------------------------------------"<<endl;
						cout << "�Ы����N���~��:";
						getch();
						break;
					case 6:
						users.member[user_id].money+=XAXB_Main(users,user_id);
						SaveUsers(users);
						users=LoadUsers();
						cout<<endl<<endl<<endl<<endl<<endl;
						cout<<"------------------------------------------------------------------------------------------"<<endl;
						cout << "�Ы����N���~��:";
						getch();
						break;
				}
				SaveUsers(users);
			}while(select!=0);
			cout<<"                 �z�T�w�n���}���t�ζ�(Y/N): ";
			cin>>c;
			if(strcmp(c,"Y")==0||strcmp(c,"y")==0)
				break;	
			else
				continue;			
		}
		SaveUsers(users);//�s�� 
		quit=time(NULL);//�����p�� 
		timediff=difftime(quit,enter);//��ɶ��t 
		min=timediff/60;
		sec=timediff%60;
		cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl; 
		cout<<"                 ���´f�U!�z�������d�F"<<min<<"��"<<sec<<"��A���ݱz�A���ϥΥ��t��"<<endl;
		cout<<"                 �Ы����N���~��:";
		getch(); 
		return 0;
	}
	else
	{
		while(true)
		{
			KEBUKE_Main();
			cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
			cout<<"               �z�T�w�n���}���t�ζ�(Y/N): ";
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
		cout<<endl<<"�L�k�ϥΦ��b���W�١A�Э��s��J�C"<<endl; 
		cout << "�Ы����N���~��: ";
		getch();	
		stp=1;
	}
	for(i=0;i<users.user_no-1;i++)//�p�G��J���O�J�����ϥΪ� 
		if(strcmp(username,users.member[i].username)==0)
		{
			cout<<endl<<"���b���w�s�b!"<<endl; 
			cout << "�Ы����N���~��: ";
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
		//�ˬd�⦸���K�X�O�_�ۦP 
		if(strlen(password)!=strlen(checkpw))
		{
			cout<<endl<<"�K�X���ۦP�A�Э��s��J!"<<endl;
			cout << "�Ы����N���~��: ";
			getch();
		}	
		else
		{
			for(i=0;i<=strlen(password);i++)
			{
				if((int)password[i]!=(int)checkpw[i])
				{
					cout<<endl<<"�K�X���ۦP�A�Э��s��J!"<<endl;
					cout << "�Ы����N���~��: ";
					getch();
					wrong=1;
					break;
				}	
			}
			if(wrong==0)
			{
				cout<<endl<<"�w�Ыطs�b���A�Э��s�n�J�C"<<endl;
				cout << "�Ы����N���~��: ";
				getch();
				//�Ыطs�ϥΪ̪����
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
	flag=0(���O�s�رb��)
	flag>0(�s�رb��)
	flag<0(���K�X) 
	*/
	char username[13];
	char password[13];
	char nickname[13];
	char checkpw[13];
	do{
		ctn=0;
		input_username(username,nickname,0);//��J�b�� 
		if(strcmp(username,"KEBUKE")==0)
			return -1;
		if(strcmp(username,"register")==0||strcmp(username,"Register")==0)//���U 
		{
			CreateAccount(users);
			users=LoadUsers();//�]������s�L�A�ҥH��Ū�@�� 
			ctn=1;
		}
		if(ctn==1)
			continue;	
		for(i=0;i<users.user_no;i++)
			if(strcmp(username,users.member[i].username)==0)
				break;
		if(i==users.user_no)//�䤣��ϥΪ� 
		{
			ctn=1;
			cout<<endl<<"�d�L���b���A�Э��s��J�ε��U�s�b��"<<endl;
			cout<<"�Ы����N���~��: "<<endl;
			getch();//���ϥΪ̫��@�ӫ��� 
		}
		if(ctn==1)
			continue;
		input_password(username,nickname,password,checkpw,flag);//�}�l��J�K�X 
		if(strcmp(password,users.member[i].password)==0)//�p�G��J���K�X��M�椤�ӨϥΪ̪��۵�
			return i;	
		else//�K�X���F����
		{
			do{
				cout<<endl<<"�K�X���~�A�Э��s��J"<<endl;
				cout<<"�Ы����N���~��: "<<endl;
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
	flag=0(���O�s�رb���A�L��J�ϥΪ̦W��)
	flag>0(�n�зs�b���A�L�Ыطs�b��) 
	flag<0(��J�ʺ�) 
	*/	
	char c1,c2;
	int n=0,i,check=0;
	do
	{
		system("cls");
		if(flag>0)
		{
			cout<<"�Ыطs�b��"<<endl;
			cout<<"�ϥΪ̦W��(����ݬ��^��r���B���׶���4-12�X): ";
			for(i=0;i<n;i++)
				cout<<un[i];//��X��ثe����X�k���r�� 
		} 
		else if(flag==0)	
		{
			cout<<"�п�J�ϥΪ̦W�١A�ο�Jregister�H���U�b��: ";
			for(i=0;i<n;i++)
				cout<<un[i];//��X��ثe����X�k���r�� 
		}	
		else
		{
			cout<<"�Ыطs�b��"<<endl;
			cout<<"�ϥΪ̦W��(����ݬ��^��r���B���׶���4-12�X): ";
			for(i=0;un[i]!='\0';i++)
				cout<<un[i];//��X��ثe����X�k���r�� 
			cout<<endl<<"�ϥΪ̼ʺ�: ";
			for(i=0;i<n;i++)
				cout<<ni[i];//��X��ثe����X�k���r�� 
		}
		c1=getch();//�ݤU�@�X
		if(c1==-32||c1==0)//0��32�O�S��X���}�Y�A��S��X����@�X�s��c2(�᭱���|�B�zc2)(�S��X�����(eg:(-32,75)) 
			c2=getch();// 
		if((c1>='a'&&c1<='z')||(c1>='A'&&c1<='Z')||(c1>='0'&&c1<='9')||c1=='_')//�p�G�X�k�A�s��U�@��A�U���A�@�_��X 
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
			if(n==12)//�p�Gn�O12�A�j���L���11�X(�]�N�O���|����13�X)
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
		if(c1==8&&n>0)//��h�� 
			n--;
		if(n>=4)
			check=1;
		else
			check=0;
		if(flag<0)
			check=1;
	}while(c1!=13||check==0||n==0);//�P�w��enter�ɿ�J�O���O�Ū�(�O�Ū��N�n�~���J)|c1!=13�N�٭n�~���J 
	if(flag>=0)
		un[n]='\0';//�b�̫�񰱤�
	else
		ni[n]='\0'; 
}
void input_password(char un[],char ni[],char pw[],char checkpw[],int flag){
	/*
	flag=0(���O�s�رb���A��X�ϥΪ̦W��+�K�X)
	flag>0(�s�رb���A��X�Ыطs�b��+�K�X||flag=2�ɦh�L�X���e��J���K�X)
	flag<0(���K�X�A-1�L�п�J��K�X�A-2�L�п�J�s�K�X�A-3�h�L���e��J���K�X) 
	flag=2||-3�ɬO�n�A��J�K�X�i������ 
	*/
	char c1,c2;
	int n=0,i,check=0;
	do
	{
		system("cls");
		if(flag>0)
		{
			cout<<"�Ыطs�b��"<<endl;
			cout<<"�ϥΪ̦W��(����ݬ��^��r���B���׶���4-12�X): "<<un<<endl;
			cout<<"�ϥΪ̼ʺ�: "<<ni<<endl; 
		}
		else if(flag==0)
			cout<<"�ϥΪ̦W��: "<<un<<endl;	
		else if(flag==-1)
			cout<<"�п�J��";
		else
			cout<<"�п�J�s";
		cout<<"�K�X: ";
		if(flag==2||flag==-3)
		{
			for(i=0;pw[i]!='\0';i++)
				cout<<"*";
			cout<<endl<<"�T�{�K�X: ";
		}
		for(i=0;i<n;i++)
			cout<<"*";//��X��ثe����K�X(�H*���) 
		c1=getch();//�ݤU�@�X
		if(c1==-32||c1==0)//0��32�O�S��X���}�Y�A��S��X����@�X�s��c2(�᭱���|�B�zc2)(�S��X�����(eg:(-32,75)) 
			c2=getch();// 
		if((c1>='a'&&c1<='z')||(c1>='A'&&c1<='Z')||(c1>='0'&&c1<='9')||c1=='_')//�p�G�X�k�A�s��U�@��A�U���A�@�_��X 
		{
			if(n==12)//�p�Gn�O12�A�j���L���11�X(�]�N�O���|����13�X)
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
		if(c1==8&&n>0)//��h�� 
			n--;
		if(n>=4)
			check=1;
		else
			check=0;
	}while(c1!=13||check==0||n==0);//�P�w��enter�ɿ�J�O���O�Ū�(�O�Ū��N�n�~���J)|c1!=13�N�٭n�~���J 
	if(flag==2||flag==-3)
		checkpw[n]='\0';//�b�̫�񰱤� 
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
		if(strlen(password)!=strlen(users.member[user_id].password))//��J��K�X�Mlist�̪����@�P 
		{
			cout<<endl<<"�K�X���ۦP�A�Э��s��J!"<<endl;
			cout << "�Ы����N���~��: ";
			getch();
			stp=1;
		}	
		else
			for(i=0;i<=strlen(password);i++)
				if((int)password[i]!=(int)users.member[user_id].password[i])//��J��K�X�Mlist�̪����@�P 
				{
					cout<<endl<<"�K�X���ۦP�A�Э��s��J!"<<endl;
					cout << "�Ы����N���~��: ";
					getch();
					stp=1;
					break;
				}	
		do{
			if(stp==1)
				break;
			wrong=0;
			input_password(users.member[user_id].username,nickname,password,checkpw,-2);//��Jpassword 
			input_password(users.member[user_id].username,nickname,password,checkpw,-3);//��Jcheckpw 
			//�ˬd�⦸���K�X�O�_�ۦP 
			if(strlen(password)!=strlen(checkpw))
			{
				cout<<endl<<"�K�X���ۦP�A�Э��s��J!"<<endl;
				cout << "�Ы����N���~��: ";
				getch();
			}	
			else
			{
				for(i=0;i<=strlen(password);i++)
				{
					if((int)password[i]!=(int)checkpw[i])
					{
						cout<<endl<<"�K�X���ۦP�A�Э��s��J!"<<endl;
						cout << "�Ы����N���~��: ";
						getch();
						wrong=1;
						break;
					}	
				}
				if(wrong==0)
				{
					cout<<endl<<"�w���K�X�C"<<endl;
					cout << "�Ы����N���~��: ";
					getch();
					//��K�X 
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
	//cout<<"�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i"<<endl;
	cout<<"�i                                                                        �i"<<endl; 
	cout<<"�i   |=|   |=|   |=======| |======|   |=|     |=| |=|   |=|   |=======|   �i"<<endl;
	cout<<"�i   |=|  |=|    |=|       |=|   |=|  |=|     |=| |=|  |=|    |=|         �i"<<endl;
	cout<<"�i   |=| |=|     |=|       |=|    |=| |=|     |=| |=| |=|     |=|         �i"<<endl;
	cout<<"�i   ||=||       |=====|   |======|   |=|     |=| ||=||       |=====|     �i"<<endl;
	cout<<"�i   |=|  |=|    |=|       |=|   |=|  |=|     |=| |=|  |=|    |=|         �i"<<endl;
	cout<<"�i   |=|   |=|   |=|       |=|    |=| |=|     |=| |=|   |=|   |=|         �i"<<endl;
	cout<<"�i   |=|     |=| |=======| |=======|   |=======|  |=|     |=| |=======|   �i"<<endl;
	cout<<"�i        �i       ��       �i       ��       ��       ��       ��        �i"<<endl;
	cout<<"�i                                                                        �i"<<endl;
	//cout<<"�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i�i"<<endl;
	cout << endl<< endl<< endl;
	cout <<"                  "<<users.member[user_id].nickname<<"�z�n�A�w��Y�{�i���i�A�z�`�@�w�n�J"<<users.member[user_id].login_no<<"��"<<endl; 
	cout <<"                  �z�{�b�֦�"<<users.member[user_id].money<<"���o�]��"<<endl;
	cout <<"                  -------------------------------------------"<<endl;
	cout <<"                 |          "<< L[1] << "1" << R[1] << " �U�q��                       |" << endl;
	cout <<"                 |          "<< L[2] << "2" << R[2] << " �d�q��                       |" << endl;
	cout <<"                 |          "<< L[3] << "3" << R[3] << " �ק�|�����                 |" << endl;
	cout <<"                 |          "<< L[4] << "4" << R[4] << " ��ѫ�                       |" << endl;
	cout <<"                 |          "<< L[5] << "5" << R[5] << " �ƿW�C��                     |" << endl;
	cout <<"                 |          "<< L[6] << "6" << R[6] << " �q�Ʀr                       |" << endl;
	cout <<"                 |          "<< L[0] << "0" << R[0] << " ���}�t��                     |" << endl;
	cout <<"                  -------------------------------------------"<<endl;     
}
int MainScreen_MainUI(int select,int user_id){
	char x,x1;
	do{
		MainScreen(select,user_id);
		x = getch();
		if(x==-32)//�W�U���k�䪺�Ĥ@�ӼƦr 
		{
			x1 = getch();//��᭱���� 
			if(x1==72)
				select = (select + 6)%7;//�W 
			if(x1==80)
				select = (select + 1)%7;//�U 
			if(x1==77)//�k��=ENTER 
				x=13;
		}
		if(x>='0'&&x<='6')//��L��0~6 
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
	cout<<"              �i   ��   �i   ��   ��   ��   ��              "<<endl; 
	cout<<"============================================================"<<endl;
	cout<<"                   �z�{�b�֦�: "<<users.member[user_id].money<<"���o�]��"<<endl;
	cout<<"                   �ݵ��b���B: "<<totalprice<<"��"<<endl;
	cout<<endl<<endl<<endl<<endl<<endl;
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
	cout<<"                  �~ �W       �� ��                         "<<endl;
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl; 
	cout<<"              "<< L[1] << "1" << R[1] << " ��������    M 25/L 30" << endl;
	cout<<"              "<< L[2] << "2" << R[2] << " �R�K����    M 25/L 30" << endl;
	cout<<"              "<< L[3] << "3" << R[3] << " �Ӧm����    M 30/L 35" << endl;
	cout<<"              "<< L[4] << "4" << R[4] << " �گ׬���    M 35/L 40" << endl;
	cout<<"              "<< L[5] << "5" << R[5] << " ���ì���    M 45/L 55" << endl;
	cout<<"              "<< L[6] << "6" << R[6] << " �����N�S    M 25/L 30" << endl;
	cout<<"              "<< L[7] << "7" << R[7] << " �K�ާN�S    M 25/L 30" << endl;
	cout<<"              "<< L[8] << "8" << R[8] << " �K�޺��    M 25/L 30" << endl;
	cout<<"              "<< L[9] << "9" << R[9] << " ��������    M 40/L 50" << endl;
	cout<<"              "<< L[10] << "A" << R[10] << " �եɼ���    M 50/L 60" << endl;
	cout<<"              "<< L[11] << "B" << R[11] << " �گצh�h    M 40/L 50" << endl;
	cout<<"              "<< L[12] << "C" << R[12] << " ���ɼ���    M 60/L 70" << endl;
	cout<<"              "<< L[0] << "0" << R[0] << " ��    �b" << endl;
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
			case 1://��������:25/30
				drinks.cart_no[drinks.orderno]++;
				drinks=Order_CreateOrder(1,drinks,drinks.orderno,drinks.cart_no[drinks.orderno]);
				price=Order_CreatePrice(25,drinks.orderno,drinks.cart_no[drinks.orderno],drinks,1);
				if(price==0)
					drinks.cart_no[drinks.orderno]--;
				else
					totalprice+=price; 
				break;	
			case 2://�R�K����:25/30	
				drinks.cart_no[drinks.orderno]++;
				drinks=Order_CreateOrder(2,drinks,drinks.orderno,drinks.cart_no[drinks.orderno]);
				price=Order_CreatePrice(25,drinks.orderno,drinks.cart_no[drinks.orderno],drinks,1);
				if(price==0)
					drinks.cart_no[drinks.orderno]--;
				else
					totalprice+=price; 
				break;	
			case 3://�Ӧm����:30/35
				drinks.cart_no[drinks.orderno]++;
				drinks=Order_CreateOrder(3,drinks,drinks.orderno,drinks.cart_no[drinks.orderno]);
				price=Order_CreatePrice(30,drinks.orderno,drinks.cart_no[drinks.orderno],drinks,1);
				if(price==0)
					drinks.cart_no[drinks.orderno]--;
				else
					totalprice+=price; 
				break;	
			case 4://�گ׬���:35/40
				drinks.cart_no[drinks.orderno]++;
				drinks=Order_CreateOrder(4,drinks,drinks.orderno,drinks.cart_no[drinks.orderno]);
				price=Order_CreatePrice(35,drinks.orderno,drinks.cart_no[drinks.orderno],drinks,1);
				if(price==0)
					drinks.cart_no[drinks.orderno]--;
				else
					totalprice+=price; 
				break;	
			case 5://���ì���:45/55
				drinks.cart_no[drinks.orderno]++;
				drinks=Order_CreateOrder(5,drinks,drinks.orderno,drinks.cart_no[drinks.orderno]);
				price=Order_CreatePrice(45,drinks.orderno,drinks.cart_no[drinks.orderno],drinks,2);
				if(price==0)
					drinks.cart_no[drinks.orderno]--;
				else
					totalprice+=price; 
				break;	
			case 6://�����N�S:25/30
				drinks.cart_no[drinks.orderno]++;
				drinks=Order_CreateOrder(6,drinks,drinks.orderno,drinks.cart_no[drinks.orderno]);
				price=Order_CreatePrice(25,drinks.orderno,drinks.cart_no[drinks.orderno],drinks,1);
				if(price==0)
					drinks.cart_no[drinks.orderno]--;
				else
					totalprice+=price; 
				break;				
			case 7://�K�ާN�S:25/30
				drinks.cart_no[drinks.orderno]++;
				drinks=Order_CreateOrder(7,drinks,drinks.orderno,drinks.cart_no[drinks.orderno]);
				price=Order_CreatePrice(25,drinks.orderno,drinks.cart_no[drinks.orderno],drinks,1);
				if(price==0)
					drinks.cart_no[drinks.orderno]--;
				else
					totalprice+=price; 
				break;				
			case 8://�K�޺��:25/30
				drinks.cart_no[drinks.orderno]++;
				drinks=Order_CreateOrder(8,drinks,drinks.orderno,drinks.cart_no[drinks.orderno]);
				price=Order_CreatePrice(25,drinks.orderno,drinks.cart_no[drinks.orderno],drinks,1);
				if(price==0)
					drinks.cart_no[drinks.orderno]--;
				else
					totalprice+=price; 
				break;				
			case 9://��������:40/50
				drinks.cart_no[drinks.orderno]++;
				drinks=Order_CreateOrder(9,drinks,drinks.orderno,drinks.cart_no[drinks.orderno]);
				price=Order_CreatePrice(40,drinks.orderno,drinks.cart_no[drinks.orderno],drinks,2);
				if(price==0)
					drinks.cart_no[drinks.orderno]--;
				else
					totalprice+=price; 
				break;	
			case 10://�եɼ���:40/50
				drinks.cart_no[drinks.orderno]++;
				drinks=Order_CreateOrder(10,drinks,drinks.orderno,drinks.cart_no[drinks.orderno]);
				price=Order_CreatePrice(40,drinks.orderno,drinks.cart_no[drinks.orderno],drinks,2);
				if(price==0)
					drinks.cart_no[drinks.orderno]--;
				else
					totalprice+=price; 
				break;				
			case 11://�گצh�h:40/50
				drinks.cart_no[drinks.orderno]++;
				drinks=Order_CreateOrder(11,drinks,drinks.orderno,drinks.cart_no[drinks.orderno]);
				price=Order_CreatePrice(40,drinks.orderno,drinks.cart_no[drinks.orderno],drinks,2);
				if(price==0)
					drinks.cart_no[drinks.orderno]--;
				else
					totalprice+=price; 
				break;					
			case 12://���ɼ���:60/70
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
		cout<<"              �o�]�������A�w�����q��A�ЦV���a�x�ȩάO�C���p�C���H���o�o�]��!"<<endl;
		cout<<"==========================================================================================="<<endl;
		totalprice=0;
		drinks.orderno--;
		SaveOrders(drinks);
	}
	else if(totalprice==0)
	{
		cout<<"==================================================="<<endl;
		cout<<"                   �w��A�ץ��{!"<<endl; 
		cout<<"==================================================="<<endl;
	}
	else
	{
		cout<<"==================================================="<<endl;
		cout<<"              �q��w����!�`�@�O"<<totalprice<<"��"<<endl;
		cout<<"                   �w��A�ץ��{!"<<endl; 
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
	cout<<"              �i   ��   �i   ��   ��   ��   ��              "<<endl; 
	cout<<"============================================================"<<endl;
	cout << endl<< endl<< endl<< endl<< endl;
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
	cout<<"                       �� �� �� �� �q                       "<<endl; 
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
	cout <<"                  "<< L[0] << "1" << R[0] << "       ���M" << endl;
	cout <<"                  "<< L[1] << "2" << R[1] << "       �j�M" << endl;
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
	cout<<"              �i   ��   �i   ��   ��   ��   ��              "<<endl; 
	cout<<"============================================================"<<endl;
	cout << endl<< endl<< endl<< endl<< endl;
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
	cout<<"                    �� �� �� �� �~ �� ��                    "<<endl; 
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
	cout <<"                 "<< L[0] << "1" << R[0] <<"      �� �` �B" << endl;
	cout <<"                 "<< L[1] << "2" << R[1] <<"      ��    �B" << endl;
	cout <<"                 "<< L[2] << "3" << R[2] <<"      �L    �B" << endl;
	cout <<"                 "<< L[3] << "4" << R[3] <<"      �h    �B" << endl;
	cout <<"                 "<< L[4] << "5" << R[4] <<"      �����h�B" << endl;
	cout <<"                 "<< L[5] << "6" << R[5] <<"      �`    ��" << endl;
	cout <<"                 "<< L[6] << "7" << R[6] <<"         ��   " << endl;
	cout <<"                 "<< L[7] << "8" << R[7] <<"         ��   " << endl;
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
	cout<<"              �i   ��   �i   ��   ��   ��   ��              "<<endl; 
	cout<<"============================================================"<<endl;
	cout << endl<< endl<< endl<< endl<< endl;
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
	cout<<"                       �� �� �� �� ��                       "<<endl; 
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
	cout <<"                  "<< L[0] << "1" << R[0] <<"  1 0 0 %   ���`�}" << endl;
	cout <<"                  "<< L[1] << "2" << R[1] <<"    7 0 %   ��  �}" << endl;
	cout <<"                  "<< L[2] << "3" << R[2] <<"    5 0 %   �b  �}" << endl;
	cout <<"                  "<< L[3] << "4" << R[3] <<"    3 0 %   �L  �}" << endl;
	cout <<"                  "<< L[4] << "5" << R[4] <<"    2 0 %   �G���}" << endl;
	cout <<"                  "<< L[5] << "6" << R[5] <<"    1 0 %   �@���}" << endl;
	cout <<"                  "<< L[6] << "7" << R[6] <<"      0 %   �L  �}" << endl;
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
	cout<<"              �i   ��   �i   ��   ��   ��   ��              "<<endl; 
	cout<<"============================================================"<<endl;
	cout << endl<< endl<< endl<< endl<< endl;
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
	cout<<"                    �� �� �� �[ �� �� ��                    "<<endl; 
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
	cout <<"                  "<< L[1] << "1" << R[1] << "      �[�ե�(+10��)" << endl;
	cout <<"                  "<< L[2] << "2" << R[2] << "      �[����(+15��)" << endl;
	cout <<"                  "<< L[0] << "0" << R[0] << "      ���ݭn" << endl;
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
		cout<<"              �i   ��   �i   ��   ��   ��   ��              "<<endl; 
		cout<<"============================================================"<<endl;
		cout << endl<< endl<< endl<< endl<< endl;
		cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
		cout<<"                     �� �� �J �M ��(0~99)                   "<<endl;
		cout<<"                    (��J0�H���������q��)                   "<<endl;
		cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
		cout<<"                        �M��: ";
		for(i=0;i<n;i++)
			cout<<c[i];//��X��ثe����X�k���r�� 
		c1=getch();//�ݤU�@�X
		if(c1==-32||c1==0)//0��32�O�S��X���}�Y�A��S��X����@�X�s��c2(�᭱���|�B�zc2)(�S��X�����(eg:(-32,75)) 
			c2=getch();// 
		if(c1>='0'&&c1<='9')//�p�G�X�k�A�s��U�@��A�U���A�@�_��X 
		{
			if(n==2)//�p�Gn�O12�A�j���L���11�X(�]�N�O���|����13�X)
			{
				c[1]=c1;	
			} 
			else
			{
				c[n]=c1;
				n++;
			}
		}
		if(c1==8&&n>0)//��h�� 
			n--;
	}while(c1!=13||n==0);//�P�w��enter�ɿ�J�O���O�Ū�(�O�Ū��N�n�~���J)|c1!=13�N�٭n�~���J 
	c[n]='\0';//�b�̫�񰱤� 
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
	cout<<"              �i   ��   �i   ��   ��   ��   ��              "<<endl; 
	cout<<"============================================================"<<endl;
	cout << endl<< endl<< endl<< endl<< endl;
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
	cout<<"                       �d  ��  �q  ��                       "<<endl; 
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
	cout <<"                  "<< L[1] << "1" << R[1] << "�s�@�����q�����" << endl;
	cout <<"                  "<< L[2] << "2" << R[2] << "�z�����v�q�ʬ���" << endl;
	cout <<"                  "<< L[3] << "3" << R[3] << "    �����q��    " << endl;	
	cout <<"                  "<< L[0] << "0" << R[0] << "      ���}      " << endl;
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
	cout<<"              �i   ��   �i   ��   ��   ��   ��              "<<endl; 
	cout<<"============================================================"<<endl;
	cout << endl<< endl<< endl<< endl<< endl;
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
	cout<<"                       ";
	if(flag>=0)
		cout<<"�d  ��";
	else
		cout<<"��  ��";
	cout<<"  �q  ��                       "<<endl; 
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
	if(flag==0||flag==-1)
	{
		cout<<"                      ���b�s�@���q��: "<<drinks.mealno<<endl<<endl;
		i=drinks.mealno;
	}
	else
	{
		cout<<"                          ���v�q��"<<endl<<endl<<endl;
		i=1;
	}	
	while(i<=drinks.orderno)
	{
		if(drinks.WhoOrder[i]==user_id)
		{
			if(i!=0) 
				cout<<"                         �q��s��: "<<i<<endl; 
			for(int j=1;j<=drinks.cart_no[i];j++)
			{
				switch(drinks.list[i][j].drinkno)
				{
					case 1:
						cout<<"                         ��������"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 2:
						cout<<"                         �R�K����"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 3:
						cout<<"                         �Ӧm����"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 4:
						cout<<"                         �گ׬���"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 5:
						cout<<"                         ���ì���"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 6:
						cout<<"                         �����N�S"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 7:
						cout<<"                         �K�ާN�S"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 8:
						cout<<"                         �K�޺��"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 9:
						cout<<"                         ��������"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 10:
						cout<<"                         �եɼ���"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 11:
						cout<<"                         �گצh�h"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 12:
						cout<<"                         ���ɼ���"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
				}
				switch(drinks.list[i][j].size)
				{
					case 0:
						cout<<"                   ���M/";
						break;
					case 1:
						cout<<"                   �j�M/";
						break;
				}
				switch(drinks.list[i][j].ice)
				{
					case 5:
						cout<<"���`�B/";
						break;
					case 4:
						cout<<"�֦B/";
						break;
					case 3:
						cout<<"�L�B/";
						break;
					case 2:
						cout<<"�h�B/";
						break;
					case 1:
						cout<<"�����h�B/";
						break;
					case 0:
						cout<<"�`��/";
						break;
					case -1:
						cout<<"��/";
						break;
					case -2:
						cout<<"��/";
						break;
				}
				switch(drinks.list[i][j].sugar)
				{
					case 100:
						cout<<"���`�}";
						break;
					case 70:
						cout<<"�ֿ}";
						break;
					case 50:
						cout<<"�b�}";
						break;
					case 30:
						cout<<"�L�}";
						break;
					case 20:
						cout<<"�G���}";
						break;
					case 10:
						cout<<"�@���}";
						break;
					case 0:
						cout<<"�L�}";
						break;
				}
				switch(drinks.list[i][j].addition)
				{
					case 10:
						cout<<"/�[�ե�"<<endl;
						break;
					case 15:
						cout<<"/�[����"<<endl;
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
		cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
		cout<<"                       �Ы����N���~��:";
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
		cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
		cout<<"              �п�J�Q�n�������q��A�ο�J0�H���}: ";
		cin>>Cancel_ID;
		if(Cancel_ID==0)
			flag=1;
		else if(Cancel_ID>drinks.orderno||Cancel_ID<0)
		{
			cout<<endl<<endl<<"                          �d�L���q��"<<endl;
			cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
			cout<<"                        �Ы����N���~��:";
			getch(); 
		}
		else if(Cancel_ID<drinks.mealno)
		{
			cout<<endl<<endl<<"                         ���q��w����!"<<endl;
			cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
			cout<<"                        �Ы����N���~��:";
			getch(); 
		}
		else if(drinks.WhoOrder[Cancel_ID]!=user_id)
		{
			cout<<endl<<endl<<"                       �z�L�k�������q��!"<<endl;
			cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
			cout<<"                        �Ы����N���~��:";
			getch(); 
		}
		else
			flag=1;
	}while(flag==0);
	if(Cancel_ID!=0)
	{
		cout<<endl<<endl<<"                �w�����q��A�w�h�^�o�]��"<<drinks.OrderPrice[Cancel_ID]<<"��"<<endl; 
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
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
	cout<<"                        �Ы����N���~��:";
	getch(); 
}
//function for Sudoku
int Sudoku_Main(userlist users,int user_id){
	int r,c,n,modified=1,count=0;
	int Q[9][9];//�G���}�C�A�ȬO�n�Ъ��Ʀr 
	int A[9][9];//�s���T���� 
	int A2[9][9];//�s�A�񪺵��� 
	int pool[9][9][10];//�e���O�G���}�C(0,0)~(8,8)�A��@��O��񪺼Ʀr(1~9)�A�ȬO0��1(�ण���) 
	Sudoku_Init(pool);
	Sudoku_Read(1,Q,pool);
	for(r=0;r<9;r++)//copy�쵪��(A)���}�C 
		for(c=0;c<9;c++)
		{
			A[r][c]=Q[r][c];
			A2[r][c]=Q[r][c];
		}	
	cout<<endl;
	Sudoku_Cutscenes(users,user_id);
	Sudoku_MainUI(Q,A2);
	while(modified==1)//modified�O�}���A�w�]�O1�A�i�J�O0�A�p�G���i�H�񪺫K��W�A�A���}�}��(���L����) 
	{
		modified=0;
		for(r=0;r<9;r++)
		{
			for(c=0;c<9;c++)
			{
				if(A[r][c]==0)//�٨S��(�ťժ�) 
				{
					n=Sudoku_Check(pool,r,c);//0-9�����S���ߤ@�ѡA0�O�S�� 
					if(n>0)
					{
						A[r][c]=n;
						Sudoku_Update(pool,r,c,n);//��s 
						modified=1;//�}�}�� 
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
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
	if(flag==1)
	{
		cout<<"                     ����!������o20���o�]��!"<<endl;
		return 20;
	}	
	else
	{
		if(count<=20)
		{
			cout<<"                     �@����"<<count<<"��A��o"<<20-count<<"���o�]��"<<endl;
			return 20-count;
		}
		else
		{
			cout<<"                     �@����"<<count<<"��A��o0���o�]��"<<endl;
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
	for(r=R/3*3;r<=R/3*3+2;r++)//(0,1,2�q0�}�l;3,4,5�q3�}�l;6,7,8�q6�}�l)
		for(c=C/3*3;c<=C/3*3+2;c++)
			p[r][c][N] = 0;
	for(n=1;n<=9;n++)//��s�L����Ʈw 
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
			if(n>0)//���O0(�ť�)���ܫK�n��s(��P��P�C�P�E�c�檺n�����) 
				Sudoku_Update(p,r,c,n);
		}
	}
	fin.close();
}
int Sudoku_Check(int p[][9][10],int R,int C){		
	int sum=0,n,a,r,c,tmp;
	for(n=1;n<=9;n++)//�p�G��L�P�檺�������n�A����N��L 
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
	for(n=1;n<=9;n++)//�p�G��L�P�C���������n�A����N��L 
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
	for(n=1;n<=9;n++)//�p�G��L�P�E�c�檺�������n�A����N��L 
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
	for(n=1;n<=9;n++)//�ˬd�ۤv�O���O���ߤ@�� 
	{
		sum+=p[R][C][n];//�����[�_��(����2�N�X��) 
		if(p[R][C][n]==1)
			a=n;
	}
	if(sum==1)//����1�N�O���ߤ@�� 
		return a;
	else
		return 0;
}
void Sudoku_Print(int Q[][9],int A[][9],int R, int C){

	int r,c;
	system("cls");//�M�ſù� 
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
	cout<<"            _______ _     _ ______   _____  _     _ _     _           "<<endl;
	cout<<"            |______ |     | |     \\ |     | |____/  |     |           "<<endl;
	cout<<"            ______| |_____| |_____/ |_____| |    \\_ |_____|           "<<endl<<endl;                                          
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl<<endl<<endl<<endl;
	char left[9][9],right[9][9];//�ǳ�81��s���A����k�A�� 
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
			cout<<left[r][c];//��X<>or[] 
			if(A[r][c]==0)//�S�񪺿�X�Ů�
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
		if(c1==-32)//�S����O-32,? 
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
	}while(c1!=13);//���Oenter 
}
void Sudoku_Cutscenes(userlist users,int user_id){
	system("cls");//�M�ſù� 
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
	cout<<"            _______ _     _ ______   _____  _     _ _     _           "<<endl;
	cout<<"            |______ |     | |     \\ |     | |____/  |     |           "<<endl;
	cout<<"            ______| |_____| |_____/ |_____| |    \\_ |_____|           "<<endl<<endl;                                        
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
	cout<<"                   �C����9��3 ��3�Ӫ��E�c��զ��C                   "<<endl<<endl;
	cout<<"         �C�@��C���Ʀr�����]�t1��9�A����ʤ֡A�]���୫�ơC         "<<endl<<endl; 
	cout<<"�C�@�c(�ʶ½u��_�Ӫ��ϰ�)���Ʀr�����]�t 1��9�A����ʤ֡A�]���୫�ơC "<<endl<<endl;
	cout<<"----------------------------------------------------------------------"<<endl;
	cout<<"                           �z�ثe�w�C��"<<users.member[user_id].Sudokutime<<"��                           "<<endl; 
	cout<<"                           �Ы����N��}�l:";
	getch();	
}
//function for XAXB
void XAXB_num2digit(int num,int digit[]){//��Ʀr�arrey 
	digit[0]=num/1000;
	digit[1]=num%1000/100;
	digit[2]=num%100/10;
	digit[3]=num%10;
}
bool XAXB_isLegal(int num){//�P�w�Ʀr�O���O�X�k
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
void XAXB_Check(int G,int A,int AB[]){//�ﵪ�סAA��bAB[0]�AB��bAB[1] 
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
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
	cout<<"                      XX    XX   AAA   XX    XX BBBBB                         "<<endl;
	cout<<"                       XX  XX   AAAAA   XX  XX  BB   B                        "<<endl;
	cout<<"                        XXXX   AA   AA   XXXX   BBBBBB                        "<<endl;
	cout<<"                       XX  XX  AAAAAAA  XX  XX  BB   BB                       "<<endl;
	cout<<"                      XX    XX AA   AA XX    XX BBBBBB                        "<<endl;
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
	srand(time(NULL));
	int comG,comA,userG,userA,count=0;
	int comAB[2],userAB[2],tmpAB[2];//0==A,1==B
	do{
		comA=rand()%10000;
	}while(XAXB_isLegal(comA)==false);//(�q��������)�p�G�üƲ��X�Ӫ��Ʀr���X�k�N���� 
	do{
		cout<<"                      �п�J�z������: ";
		cin>>userA;
	}while(XAXB_isLegal(userA)==false);//(���a������)�p�G��J���Ʀr���X�k�N����J 
	int pool[10000];
	int i;
	for(i=0;i<10000;i++)//���w�]��(0000=0,1234=1>>�X�k��1�A���X�k��0) 
	{
		if(XAXB_isLegal(i))//isLegal==true 
			pool[i]=1;
		else
			pool[i]=0;
	}
	do{
		do{
		cout<<"                      �п�J�z�Q�q�����Ʀr: ";
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
		cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
		cout<<"                      �AĹ�F!�n�ڨ��!�n��20!"<<endl;
		return 20;
	}	
	else if(comAB[0]>userAB[0]) 
	{
		users.member[user_id].XAXBloss++;
		SaveUsers(users);
		cout<<endl;
		cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
		cout<<"                      �A��F!7414��!�����A��!"<<endl;
		return 0;
	}
	else
	{
		users.member[user_id].XAXBeven++;
		SaveUsers(users);
		cout<<endl;
		cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
		cout<<"                      ����!���A10��!"<<endl;
		return 10;
	}
}
void XAXB_Cutscenes(userlist users,int user_id){
	system("cls");//�M�ſù� 
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
	cout<<"                      XX    XX   AAA   XX    XX BBBBB                         "<<endl;
	cout<<"                       XX  XX   AAAAA   XX  XX  BB   B                        "<<endl;
	cout<<"                        XXXX   AA   AA   XXXX   BBBBBB                        "<<endl;
	cout<<"                       XX  XX  AAAAAAA  XX  XX  BB   BB                       "<<endl;
	cout<<"                      XX    XX AA   AA XX    XX BBBBBB                        "<<endl;
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
    cout<<"              �A�P�q���U�]�w�@�ե|�X���Ʀr�@�������A�浹���q�C              "<<endl<<endl; 
	cout<<"�C�q�@�ӼơA�X�ƪ̴N�n�ھڳo�ӼƦr���X���ܡA���ܥHXAYB�Φ��e�{�A����q������C"<<endl<<endl;
	cout<<"      �䤤X��ܦ�m���T���ƪ��ӼơA��Y��ܼƦr���T�Ӧ�m���諸�ƪ��ӼơC      "<<endl<<endl;                        
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
	cout<<"                           �z�ثe�����Z��"<<users.member[user_id].XAXBwin<<"��"<<users.member[user_id].XAXBloss<<"��"<<users.member[user_id].XAXBeven<<"�M  "<<endl; 
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
	cout<<"                           �Ы����N��}�l:";
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
		cout<<" �X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
		cout<<"|   �п�JExit�H���}��ѫǡA��J�S�w���ϥΪ̦W�٥H�i��p��   |"<<endl; 
		cout<<" �X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
		fin.open("msg.txt");//Ū��ѫ� 
		while(!fin.eof())//���ɮ׵����ɰ��� 
		{
			fin.getline(talk,99);//�q�ɮפ�Ū�@���
			cout<<talk<<endl;//��X�@�� 
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
			fout.open(("msg.txt"),std::ofstream::app);//�w�]�O�Ƽg�A�[std::ofstream::app�O�⥦�令�[�W�h 
			fout<<un<<" :"<<talk<<endl;//�⥴���ܥ[�i��ѫǤ�(�Υ[�W�h���Ӥ��O�Ƽg)
			fout.close(); 
		}
	}while(true);
}
void PrivateChatroom_Main(char un1[],char un2[]){//un1����un2�H�� 
	char talk[100];
	ifstream fin;
	ofstream fout;
	int flag,i;
	do{
		system("cls");
		cout<<" �X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
		cout<<"|   �п�JExit�H���}��ѫ�   |"<<endl; 
		cout<<" �X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
		fin.open("privatechat.txt");//Ū��ѫ� 
		while(!fin.eof())//���ɮ׵����ɰ��� 
		{
			flag=1;
			fin.getline(talk,99);//�q�ɮפ�Ū�@���
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
			fout.open(("privatechat.txt"),std::ofstream::app);//�w�]�O�Ƽg�A�[std::ofstream::app�O�⥦�令�[�W�h 
			fout<<un1<<","<<un2<<" :"<<talk<<endl;//�⥴���ܥ[�i��ѫǤ�(�Υ[�W�h���Ӥ��O�Ƽg)
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
	cout<<"              �i   ��   �i   ��   ��   ��   ��              "<<endl; 
	cout<<"============================================================"<<endl;
	cout << endl<< endl<< endl<< endl<< endl;
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
	cout<<"                       ��  �a  �n  �J                       "<<endl; 
	cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
	cout<<"                     �I�ܥثe���ֿn���J: "<<drinks.earnings<<endl; 
	cout<<endl<<endl<<endl<<endl<<endl;
	cout <<"                  "<< L[1] << "1" << R[1] << "     �d�߭q��" << endl;
	cout <<"                  "<< L[2] << "2" << R[2] << "     �U���x��" << endl;
	cout <<"                  "<< L[0] << "0" << R[0] << "     ���}�t��" << endl;
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
		cout<<"              �i   ��   �i   ��   ��   ��   ��              "<<endl; 
		cout<<"============================================================"<<endl;
		cout << endl<< endl<< endl<< endl<< endl;
		cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
		cout<<"                       �d  ��  �q  ��                       "<<endl; 
		cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
		cout<<endl<<endl<<endl<<endl<<endl;
		if(i==drinks.mealno)
		{
			flag=0;
			cout<<"                       �s��: "<<i<<endl; 
			for(int j=1;j<=drinks.cart_no[i];j++)
			{
				switch(drinks.list[i][j].drinkno)
				{
					case 1:
						cout<<"                     ��������"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 2:
						cout<<"                     �R�K����"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 3:
						cout<<"                     �Ӧm����"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 4:
						cout<<"                     �گ׬���"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 5:
						cout<<"                     ���ì���"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 6:
						cout<<"                     �����N�S"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 7:
						cout<<"                     �K�ާN�S"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 8:
						cout<<"                     �K�޺��"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 9:
						cout<<"                     ��������"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 10:
						cout<<"                     �եɼ���"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 11:
						cout<<"                     �گצh�h"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
					case 12:
						cout<<"                     ���ɼ���"<<"*"<<drinks.list[i][j].cup<<endl;
						break;
				}
				switch(drinks.list[i][j].size)
				{
					case 0:
						cout<<"                     ���M/";
						break;
					case 1:
						cout<<"                     �j�M/";
						break;
				}
				switch(drinks.list[i][j].ice)
				{
					case 5:
						cout<<"���`�B/";
						break;
					case 4:
						cout<<"�֦B/";
						break;
					case 3:
						cout<<"�L�B/";
						break;
					case 2:
						cout<<"�h�B/";
						break;
					case 1:
						cout<<"�����h�B/";
						break;
					case 0:
						cout<<"�`��/";
						break;
					case -1:
						cout<<"��/";
						break;
					case -2:
						cout<<"��/";
						break;
				}
				switch(drinks.list[i][j].sugar)
				{
					case 100:
						cout<<"���`�}";
						break;
					case 70:
						cout<<"�ֿ}";
						break;
					case 50:
						cout<<"�b�}";
						break;
					case 30:
						cout<<"�L�}";
						break;
					case 20:
						cout<<"�G���}";
						break;
					case 10:
						cout<<"�@���}";
						break;
					case 0:
						cout<<"�L�}";
						break;
				}
				switch(drinks.list[i][j].addition)
				{
					case 10:
						cout<<"/�[�ե�"<<endl;
						break;
					case 15:
						cout<<"/�[����"<<endl;
						break;
					case 0:
						cout<<endl; 
						break;
				}
			}
			cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
			cout<<"                   �Ы��U�V�U���PgDn�H�e�X�q��"<<endl;
			cout<<"                   �Ы��UESC��H���}"<<endl; 
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
		cout<<"              �i   ��   �i   ��   ��   ��   ��              "<<endl; 
		cout<<"============================================================"<<endl;
		cout << endl<< endl<< endl<< endl<< endl;
		cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
		cout<<"                       �d  ��  �q  ��                       "<<endl; 
		cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
		cout<<endl<<endl<<endl<<endl<<endl;
		cout<<"                   �ثe�|�L�ݭn�s�@���q��"<<endl;
		cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
		cout<<"               	  �Ы����N���~��:";
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
		cout<<"              �i   ��   �i   ��   ��   ��   ��              "<<endl; 
		cout<<"============================================================"<<endl;
		cout << endl<< endl<< endl<< endl<< endl;
		cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
		cout<<"                       �U  ��  �x  ��                       "<<endl; 
		cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
		cout<<endl<<endl<<endl<<endl<<endl;
		cout<<"                    �п�J�U�Ƚs���A��J-1�H���}: ";
		cin>>id;
		if(id==-1)
			break;
		for(i=0;i<users.user_no;i++)
		{
			if(i==id)
			{
				cout<<endl<<"                    �п�J�x�Ȫ��B: ";
				cin>>addmoney;
				users.member[i].money+=addmoney;
				SaveUsers(users);
				cout<<endl<<"                    �x�ȧ����C"<<endl;
				cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
				cout<<"               	   �Ы����N���~��:";
				getch(); 
				flag=0;
				break;
			}
		}
		if(i==users.user_no&&flag==1)
		{
			cout<<"                    �d�L���U�ȡA�Э��s��J�C"<<endl;
			cout<<"�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X"<<endl;
			cout<<"               	   �Ы����N���~��:";
			getch();
		}
	}while(flag==1);
}

