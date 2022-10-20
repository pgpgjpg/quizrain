#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;

#define _MACRO_H
// x,y 좌표로 커서 이동
#define gotoxy(x,y)	printf("[%d;%dH", y, x)
// 화면에 입력 문자 echo 
#define setecho()	system("stty echo")
// 화면에 입력 문자 noecho 
#define setnoecho()	system("stty -echo")
// 한글자씩 입력
#define setraw()	system("stty raw");
// 한 문장씩 입력(개행문자 올때까지)
#define resetraw()	system("stty -raw -istrip sane")
// 화면 지우기
#define clearTerminal()		system("clear")

class Point
{
protected:
	int x, y;
	char ch;

public:
    Point(int ax, int ay) { x = ax; y = ay; }
	Point(int ax, int ay, char ach) { x = ax; y = ay; ch = ach; }
	void show() {
		gotoxy(x, y); putchar(ch);
	}
	void hide() {
		gotoxy(x, y); putchar(' ');
	}
	void move(int nx, int ny) {
		hide();
		x = nx;
		y = ny;
		show();
	}
};

class Rect : public Point
{
protected:
	int width, height;

public:
	Rect(int ax, int ay, int awidth, int aheight, char ach) : Point(ax, ay, ach) { width = awidth; height = aheight; }
	void show() {
		for (int c = 0; c < width; ++c) {
			gotoxy(c+x, y);
            putchar(ch);
            gotoxy(c+x, height+1);
            putchar(ch);
		}
        for(int r = 0; r < height; ++r){
            gotoxy(x, r+y);
            putchar(ch);
            gotoxy(width, r+y);
            putchar(ch);
        }
        gotoxy(0, 0);
	}
	void hide() {		
        for (int c = 0; c < width; ++c) {
			gotoxy(c+x, y);
            putchar(' ');
            gotoxy(c+x, height);
            putchar(' ');
		}
        for(int r = 0; r < height; ++r){
            gotoxy(x, r+y);
            putchar(' ');
            gotoxy(width, r+y);
            putchar(' ');
        }
        gotoxy(0, 0);
	}    
};

class HorizontalLine : public Point
{
protected:
	int length;
public:
	HorizontalLine(int ax, int ay, int len, char ach) : Point(ax, ay, ach) { this->length = len; }
	void show() {       
        for(int c = 0; c < length; ++c){
            gotoxy(x+c, y);
            putchar(ch);
        }
        gotoxy(0, 0);
	}
	void hide() {		
        for(int c = x; c < length; ++c){
            gotoxy(x+c, y);
            putchar(' ');
        }
        gotoxy(0, 0);
	}    
};

class VerticalLine : public Point
{
protected:
	int length;
public:
	VerticalLine(int ax, int ay, int len, char ach) : Point(ax, ay, ach) { this->length = len; }
	void show() {       
        for(int r = 0; r < length; ++r){
            gotoxy(x, y+r);
            putchar(ch);
        }
        gotoxy(0, 0);
	}
	void hide() {		
        for(int r = y; r < length; ++r){
            gotoxy(x, y+r);
            putchar(' ');
        }
        gotoxy(0, 0);
	}    
};

class Text : public Point
{
protected:	
    string text;

public:
    Text() : Point(0, 0) {}
	Text(int ax, int ay, string text) : Point(ax, ay) { this->text = text; }
    void set(int ax, int ay, string text) { x = ax; y = ay; this->text = text; }
	void show() {   
        gotoxy(x, y);    
        cout << text;
        gotoxy(0, 0);
	}
	void hide() {		
        gotoxy(x, y);    
        for(int i = 0; i < text.length(); ++i) putchar(' ');        
        gotoxy(0, 0);
	}    
    void setText(string str){text = str;}
};

class StringRain : public Point
{
protected:	
    string text;
    int height;
    double speed;

public:
    StringRain():Point(0, 0) {}
	StringRain(int ax, int ay, int height, string text, int speed) : Point(ax, ay) { this->height = height; this->text = text; this->speed = speed;}
    void set(int ax, int ay, int height, string text, int speed) { x = ax; y = ay; this->height = height; this->text = text; this->speed = speed;}
	void show() {   
        for(int r = y; r < height; ++r){
            gotoxy(x, r);        
            cout << text << endl;
            //fflush(stdout);
            usleep(speed);   
            gotoxy(x, r);      
            for(int i = 0; i < text.length(); ++i) putchar(' ');
        }          
        
        gotoxy(0, 0);
	}	
};

class Map{
    int origin_x, origin_y;
    int width;
    int height;
    int time;
    int maxLenStr;
    int nThreads;
    
    bool stopRain;

    Text textQuiz;    
    Text textScore;
    Text textName;
    Text textAnswer;
    
    string strAnswer;
    string strName;

    pthread_t *vThreads;    
    StringRain *sr;
    
public:
    Map() : width(100), height(25), origin_x(0), origin_y(2), maxLenStr(100/2-2) {strAnswer = "NULL";}
    Map(int w, int h) : width(w), height(h), origin_x(0), origin_y(2), maxLenStr(w/2-2) {strAnswer = "NULL";}
    ~Map();
    void showFrame(char ch);    
    void showQuiz(string text);        
    void showRain(vector<string> answers, int fallingTime);        
    void showScore(int score);        
    void showName(string name);        
    void showAnswer(string name);
    void showText(int x, int y, string text);

    void removeQuiz();
    void removeRain();
    void removeScore();
    void removeName();   

    
    string waitAnswer();
    void getAnswer();
};