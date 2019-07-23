#include "Maze.h"
#include<iostream>
#include<cstdlib>
#include<time.h>
#include<deque>
#include <queue>
#include<iomanip>
using namespace std;


class Element {
public:
    Element(int x, int y, int v): x(x), y(y), v(v) {}


    bool operator<(const Element &e) const {
        return v < e.v;
    }

    bool operator>(const Element &e) const {
        return v > e.v;
    }

    int x;
    int y;
    int v;
};

Maze::Maze(int w, int h) {
    width = w+2;
    height = h+2;
    board = new int*[width];

    for(int i=0;i<width;++i)
        board[i] = new int[height];
}


Maze::~Maze() {
    for(int i=0;i<width;++i)
        delete[] board[i];

    delete[] board;
}


void Maze::generate() {



srand(time(NULL));
for(int i=1;i<width-1;i++){
    for(int j=1;j<height-1;j++){
        board[i][j]=rand()%90+2;
    }
}




priority_queue<Element,vector<Element>,greater<Element> > pola;



int x=1;
int y=1;
pola.push(Element(x+1,y,board[x+1][y]));
pola.push(Element(x,y+1,board[x][y+1]));
board[x][y]=1;

Element e = pola.top();

int dok=0;


while(!pola.empty()){



    e = pola.top();
    x=e.x;
    y=e.y;



    pola.pop();
    if(x>1){
			if(board[x-1][y]==1){
				dok++;
			}
		}
    if(y>1){
			if(board[x][y-1]==1){
				dok++;
			}
		}
    if(x<width-3){
			if(board[x+1][y]==1){
				dok++;
			}
		}
    if(y<height-3){
			if(board[x][y+1]==1){
				dok++;
			}
		}


    if(dok==1){


		if(y>1){
            if(board[x][y-1]!=1){
                pola.push(Element(x,y-1,board[x][y-1]));

            }
		}
		if(x>1 ){
             if(board[x-1][y]!=1){
                pola.push(Element(x-1,y,board[x-1][y]));

            }
		}

		if(x<width-2 ){
            if(board[x+1][y]!=1){
                pola.push(Element(x+1,y,board[x+1][y]));
            }
		}

		if(y<height-2 ){
            if(board[x][y+1]!=1){
                pola.push(Element(x,y+1,board[x][y+1]));
            }
		}

        board[x][y]=1;

		}
    dok=0;
    e = pola.top();



}



for(int i=1;i<width-1;i++){
    for(int j=1;j<height-1;j++){
            if(board[i][j]!=1){
        board[i][j]=0;
            }
    }
}
for(int i=0;i<width;i++){
    for(int j=0;j<height;j++){
            if(i==0 or j==0 or i==width-1 or j==height-1){
        board[i][j]=3;
            }
    }
}

int ax=rand()%20+30;
int ay=rand()%15+15;
int n=1;
while(n==1){
        ax=rand()%20+30;
        ay=rand()%15+15;
    if(board[ax][ay]==1 and(ay>15 or ax>35)){
            cout<<endl<<endl<<"--------" << ax<<" "<<ay << "----------------" <<endl;
        board[ax][ay]=2;
        endX = ax;
        endY = ay;
        n=0;
    }
}
cout<<endl<<endl<<"--------" << ax<<" "<<ay << " " << endX << " " << endY << "----------------" <<endl;

}

int Maze::field(int x, int y) {
    return board[x][y];
}

int Maze::getWidth(){return width;}
int Maze::getHeight(){return height;}


int Maze::getEndX() { return endX; }
int Maze::getEndY() { return endY; }
