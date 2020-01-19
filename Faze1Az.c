#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#define COL 4
#define R 4
#define INFINIT 20
// 1 S pacman
// 2 . food
// 0 * block
// 3   empty
typedef struct{
	int x;
	int y;
}coord;
void drawMap(int Map[COL][R]);
void gotoxy(int,int);
void BellMan(coord,int Map[COL][R],int Path[COL][R]);
void Move(int,coord*,int Map[COL][R],int Path[COL][R]);
int Min(int,int,int,int);
int GPS(int Path[COL][R],coord);
int main(){
	coord pacman={0,0};
	int Map[COL][R]={
             1,3,0,3,
			 3,3,3,2,
			 3,3,3,0,
			 3,3,3,2
	};
	static int Path[COL][R]={0};
	drawMap(Map);
	while(1){
		int choice;
		gotoxy(pacman.x,pacman.y);
		printf("%c",'S');
        BellMan(pacman,Map,Path);
		choice=GPS(Path,pacman);
		Sleep(500);
		gotoxy(pacman.x,pacman.y);
		printf(" ");

		if(choice)
			Move(choice,&pacman,Map,Path);
		else
			break;
	}
	gotoxy(0,11);
	printf("FINISH:)");
}
void drawMap(int Map[COL][R]){
	char block;
	int a,b;
	for(a=0;a<COL;a++){
		for(b=0;b<R;b++){
			switch(Map [a][b]){
				case 0:
					block='*';
					break;
				case 2:
					block='.';
					break;
				case 3:
					block=' ';
					break;
			}
			printf("%c",block);
		}
		printf("\n");
	}
}
void gotoxy(int x,int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle,coord);
}
void Move(int choice,coord *pacman,int Map[COL][R],int Path[COL][R]){
		Map[pacman->y][pacman->x]=3;
		switch(choice){
			case 1:
				if(pacman->y&&Map[pacman->y-1][pacman->x])
					pacman->y--;
					break;
			case 2:
				if(pacman->y+1<COL&&Map[pacman->y+1][pacman->x])
					pacman->y++;
					break;
			case 3:
				if(pacman->x&&Map[pacman->y][pacman->x-1])
					pacman->x--;

					break;
			case 4:
				if(pacman->x+1<R&&Map[pacman->y][pacman->x+1])
					pacman->x++;
					break;
		}
		Map[pacman->y][pacman->x]=1;
}
int Min(int a,int b,int c,int d){
	int temp=(a>b?b:a);
	temp=(temp>c?c:temp);
	temp=(temp>d?d:temp);
	return temp;
}
void BellMan(coord pacman,int Map[COL][R],int Path[COL][R]){
	int i,j;
	int dist[COL][R];
	int flag=1,prev,n,m,a,b,c,d;
	for( i=0;i<COL;i++){
		for( j=0;j<R;j++){
			dist[i][j]=INFINIT;
			Path[i][j]=0;
		}
	}
	dist[pacman.y][pacman.x]=0;
	while(flag){
		flag=0;
		for(i=0;i<COL;i++){
			for(j=0;j<R;j++){
                prev=dist[i][j];
				if(Map[i][j])
                    if (i!=pacman.y || j!=pacman.x){
					a=((i>0) ? dist[i-1][j]:INFINIT);
					b=((j>0) ? dist[i][j-1]:INFINIT);
					c=((i<3) ? dist[i+1][j]:INFINIT);
					d=((j<3) ? dist[i][j+1]:INFINIT);
					dist[i][j]=Min(a,b,c,d)+1;
				}
				if(prev!=dist[i][j])
					flag=1;
			}
		}
	}
	for( i=0;i<COL;i++){
		for( j=0;j<R;j++){
			if(Map[i][j]==2){
				coord food={j,i};
				n=i;m=j;
				Path[i][j]=1;
				while(dist[n][m]!=1){
				if(n>0&&dist[n-1][m]<dist[n][m]){
					Path[n-1][m]=1;
					n=n-1;
				}
				else if(m>0&&dist[n][m-1]<dist[n][m]){
					Path[n][m-1]=1;
					m=m-1;
				}
				else if(n<3&&dist[n+1][m]<dist[n][m]){
					Path[n+1][m]=1;
					n=n+1;
				}
				else if(m<3&&dist[n][m+1]<dist[n][m]){
					Path[n][m+1]=1;
					m=m+1;
				}
			  }
                return;
			}
		}
	}
}
int GPS(int Path[COL][R],coord pacman){
	int i=pacman.y;
	int j=pacman.x;
	if(i<3&&Path[i+1][j]==1) return 2;
	if(i>0&&Path[i-1][j]==1) return 1;
	if(j<3&&Path[i][j+1]==1) return 4;
	if(j>0&&Path[i][j-1]==1) return 3;
		return 0;
}
