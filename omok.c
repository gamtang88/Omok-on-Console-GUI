#include<stdio.h>
#include<conio.h>
#include<windows.h>

#define NUMOFMENU 3
#define GAMESTART 0
#define EXIT 2
#define PLAYER 1
#define COM 2
#define EMPTY 0
#define NONE 3
#define WIDTHPAN 19
#define POINT 3

#define col GetStdHandle(STD_OUTPUT_HANDLE)

#define RED SetConsoleTextAttribute(col,0x000c);
#define BLUE SetConsoleTextAttribute(col,0x0001|0x0008);
#define YEL SetConsoleTextAttribute(col,0x000e);
#define GREEN SetConsoleTextAttribute(col,0x0002);
#define GOLD SetConsoleTextAttribute(col,0x0006);
#define WHITE SetConsoleTextAttribute(col,0x000f);

int baduk[19][19];
/*
int whoseStone(int* baduk[]){
return 
}
*/

void paintMap(int poX,int poY,int turn){
	int i;int j;
	system("cls");
	YEL
		puts("※※※※※※※※※※※※※※※※※※※※※");
	puts("************** 5  M  O  K ***************");
	puts("※※※※※※※※※※※※※※※※※※※※※\n");
	WHITE
		puts("┏┳┳┳┳┳┳┳┳┳┳┳┳┳┳┳┳┳┳┳┓");
	for(i=0;i<WIDTHPAN;i++){
		fputs("┣",stdout);
		for(j=0;j<WIDTHPAN;j++){
			if(i==poY&&j==poX)fputs("⊙",stdout);
			else if(baduk[i][j]==EMPTY){//돌 없으면
				fputs("╋",stdout);
			}
			else {
				if(baduk[i][j]==PLAYER)fputs("○",stdout);
				else if(baduk[i][j]==COM) fputs("●",stdout); 
			}
		}
		puts("┫");
	}
	puts("┗┻┻┻┻┻┻┻┻┻┻┻┻┻┻┻┻┻┻┻┛\n");
	GREEN
		puts("*****************************************");
	puts(" ◈ 이동  : 방향키	◈ 선택  : ENTER");
	puts(" ◈ 메뉴  : SPACE	◈ 끝내기: q/Q");
	puts("*****************************************");

	RED
		printf("TURN :: %s.\n",turn==COM?"COM":"PLAYER");
	GREEN
		printf("X : %d,, Y : %d\n",poX,poY);
	WHITE
}

////////////////////////////////////////////////////////////////////////////////check5LINE
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
int horizonCheck(int i,int j){
	int target,matchCnt=1;
	target=(baduk[i][j]==PLAYER?PLAYER:COM);
	while(baduk[i][j]==baduk[i][j+1]){//다음거랑 다를때 까지
		matchCnt++;j++;
		if(matchCnt>=5)return target;
	}
	return NONE;
}

int verticalCheck(int i,int j){
	int target,matchCnt=1;
	target=(baduk[i][j]==PLAYER?PLAYER:COM);
	while(baduk[i][j]==baduk[i+1][j]){//다음거랑 다를때 까지
		matchCnt++;i++;
		if(matchCnt>=5)return target;
	}
	return NONE;
}

int slashCheck(int i,int j){ 
	int target,matchCnt=1;
	target=(baduk[i][j]==PLAYER?PLAYER:COM);
	while(baduk[i][j]==baduk[i+1][j+1]){//다음거랑 다를때 까지
		matchCnt++;j++;i++;
		if(matchCnt>=5)return target;
	}
	return NONE;
}

int invSlashCheck(int i,int j){
	int target,matchCnt=1;
	target=(baduk[i][j]==PLAYER?PLAYER:COM);
	while(baduk[i][j]==baduk[i+1][j-1]){//다음거랑 다를때 까지
		matchCnt++;j--;i++;
		if(matchCnt>=5)return target;
	}
	return NONE;
}

int basicCheck(int i,int j){
	int target,matchCnt=1;
	target=(baduk[i][j]==PLAYER?PLAYER:COM);
	return NONE;
}

int calResult(){
	int i=0,j=0,result=0;
	for(i=0;i<WIDTHPAN;i++){
		for(j=0;j<WIDTHPAN;j++){
			if(baduk[i][j]!=EMPTY){//비어있지 않을때만 검사해라
				result=horizonCheck(i,j);
				if(result!=NONE)return result;
				result=verticalCheck(i,j);
				if(result!=NONE)return result;
				result=slashCheck(i,j);
				if(result!=NONE)return result;
				result=invSlashCheck(i,j);
				if(result!=NONE)return result;
			}
		}
	}
	return NONE;
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////check5LINE

void gameOver(int whoWin){
	RED
		puts("게임끝!");
	GOLD
		printf("%s.WIN\n",whoWin==PLAYER?"플레이어":"컴퓨터");
	WHITE
		puts("메뉴로 돌아가시려면 아무키나 누르세요");
	_getch();
}

void choiceOmok(){
	char c;char backToMenu='\0';int turn=PLAYER;
	int poX=0,poY=0,prePoX=0,prePoY=0,value=0,result=NONE;
	while(1){
		c=_getch();
		switch(c){
		case 72://up
			poY--;
			if(poY<0)poY=WIDTHPAN-1;
			break;
		case 80://down
			poY++;
			poY%=WIDTHPAN;
			break;
		case 75: //left
			poX--;
			if(poX<0)poX=WIDTHPAN-1;
			break;
		case 77: //right
			poX++;
			poX%=WIDTHPAN;
			break;
		case 13://enter
			if(turn==PLAYER){
				if(baduk[poY][poX]!=EMPTY){
					puts("있는자리에 놓을수 없습니다.!!");
					_getch();
				}
				else{
					baduk[poY][poX]=PLAYER;
					result=calResult();
					if(result!=NONE){
						gameOver(result);
						backToMenu='b';
					}
				}
				turn=COM;
			}
			else{
				puts("COM 턴입니다.");
				_getch();
			}
			break;
		case 'c':
			if(turn==COM){
				if(baduk[poY][poX]!=EMPTY){
					puts("다른자리에!");
					_getch();
				}
				else{
					baduk[poY][poX]=COM;
					result=calResult();
					if(result!=NONE){
						gameOver(result);
						backToMenu='b';
					}
				}
				turn=PLAYER;
			}
			else{
				puts("PLAYER 턴입니다.");
				_getch();
			}
			break;
		case 'q'||'Q':
			puts("게임을 종료합니다.");
			exit(1);
			break;
		case 32:
			puts("정말 게임을 종료 하시겠씁니까?Y/N");
			c=_getch();
			if(c=='y' || c=='Y')
				backToMenu='b';
			break;
		}
	
		paintMap(poX,poY,turn);
		if(backToMenu=='b')break;
	}
}

void startOmok(){
	int i=0;int j=0;
	system("cls");
	for(i=0;i<WIDTHPAN;i++){//init
		for(j=0;j<WIDTHPAN;j++){
			baduk[i][j]=EMPTY;
		}
	}
	while(1){
		paintMap(0,0,PLAYER);
		choiceOmok();
		break;//return to menu
	}
}

void ai(){//우선 방어부터
	//세개일때...
	int i,j;
}

void showMenu(){
	int num=0;
	char c='\0';
	while(1){
		YEL
			puts("※※※※※※※※※※※※※※※※※※※※※");
		puts("************** 5  M  O  K ***************");
		puts("※※※※※※※※※※※※※※※※※※※※※\n");
		GREEN
			puts("┏━━━━━━━━━━━━━━━━━━━◀");
		puts("┃☆방향키로 원하는 메뉴로 이동");
		puts("┃☆엔터키로 선택");
		puts("┗━━━━━━━━━━━━━━━━━━━◀");
		RED
			printf("%s 게임 시작\n\n",num==0?"▶":"▷");
		printf("%s 난이도 조절\n\n",num==1?"▶":"▷");
		printf("%s 게임 종료\n\n",num==2?"▶":"▷");
		printf("%d\n",num);
		WHITE
			c=_getch();
		switch(c){
		case 72://up key
			num--;
			if(num<0)num=NUMOFMENU-1;
			break;
		case 80://down key
			num++;
			num%=NUMOFMENU;
			break;
		case 13://enter key
			switch(num){
			case GAMESTART:
				startOmok();
				break;
			case EXIT :
				puts("게임 종료 합니다.");
				_getch();
				exit(1);
			}
		}
		system("cls");
	}
}


int main(){
	showMenu();
}