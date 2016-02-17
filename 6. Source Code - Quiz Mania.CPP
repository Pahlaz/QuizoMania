/*============================================================================
  Name        : Quiz Mania.cpp
  Author      : Divyank Pahlazani & Gaurav Rajput
  Version     : 1.0
  Copyright   : Your copyright notice
  Description : Quiz Mania in C++
  ===========================================================================*/

#include <iostream.h>
#include <graphics.h>
#include <conio.h>
#include <fstream.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <dos.h>

int i;
const char courses[10][10] = {"JAVA", "HTML", "PYTHON", "DAA"};
char *participant;

void display(char s[]){
	for(i=0;s[i]!='\0';++i){
		cout<<s[i];
		delay(100);
	}
}

/*============================================================================
	This class contain the menu.
============================================================================*/
class Menu{
	public:
		void frontPage();
		void welcome(char *text);
		void thanks();
};
void Menu :: frontPage(){
	textmode(C80) ;
	clrscr() ;
	textbackground(BLUE);
	textcolor(GREEN) ;
	clrscr();
	
	gotoxy(35,10);
	display("Presenting");
	gotoxy(31,12) ;
	display("Q U I Z  M A N I A") ;
	gotoxy(5,21);
	display("CREATED BY :");
	gotoxy(5,22);
	display("Divyank Pahlazani & Gaurav Rajput");
	getch();
}
void Menu :: welcome(char *text){
	textmode(C80) ;
	clrscr() ;
	textbackground(LIGHTGRAY);
	textcolor(RED) ;
	clrscr();

	gotoxy(30,10) ;
	display("W E L C O M E") ;
	gotoxy(32,12);
	display(text);
	getch();
}
void Menu :: thanks(){
	textmode(C80) ;
	clrscr() ;
	textbackground(LIGHTGRAY);
	textcolor(RED) ;
	clrscr();

	gotoxy(12,12) ;
	display("T H A N K  Y O U") ;
	gotoxy(10, 20);
	cout<<"It's our pleasure to serve you.";
	gotoxy(1,23);
	cout<<"-------------------------------------------------------------------------------";
	gotoxy(5,24);
	cout<<"Keep Learning and Playing.";
}

/*============================================================================
	Main Functionality
============================================================================*/
class Quiz{
	public:
		void menu();
		void sub_menu(int, char []);
		void hide_sub_menu(int);
		void availableCourses();
		void Edit();
		void modify(char filename[13]) ;
		void modify_record(char filename[13], int) ;
		int  found_record(char filename[13], int) ;
		void add(char filename[13]) ;
		int  record_count(char filename[13]) ;
		void delete_record(char filename[13], int) ;
		void display_record(char filename[13], int) ;
		void keyConnect(int , int, int, int );
		void play(char []);
		void display_score(int , int);

		char t_sol, ch ;
		fstream file ;
		char *filename;
		char question[50], ans, options[4][20];
		int valid ;
		int  ques_no ;
		char ques[60] ;
		char ans1[50] ;
		char ans2[50] ;
		char ans3[50] ;
		char sol ;
};
void Quiz :: display_record(char filename[13], int t_ques_no){
   fstream file ;
   file.open(filename, ios::in) ;
   file.seekg(0,ios::beg) ;
   while (file.read((char *) this, sizeof(Quiz))){
	if (t_ques_no == ques_no){
		gotoxy(3,3) ;
		cout <<"question # " <<t_ques_no ;
		gotoxy(3,7) ;
		cout <<"question : " <<ques ;
		gotoxy(3,8) ;
		cout <<"answer 1 : " <<ans1 ;
		gotoxy(3,9) ;
		cout <<"answer 2 : " <<ans2 ;
		gotoxy(3,10) ;
		cout <<"answer 3 : " <<ans3 ;
		break ;
	}
   }
   file.close() ;
}
int  Quiz :: found_record(char filename[13], int t_ques_no){
   fstream file ;
   file.open(filename, ios::in) ;
   file.seekg(0,ios::beg) ;
   int found=0 ;
   while (file.read((char *) this, sizeof(Quiz))){
	if (t_ques_no == ques_no){
		found++ ;
		break ;
	}
   }
   file.close() ;
   return found ;
}
void Quiz :: modify_record(char filename[13], int t_ques_no){
   int valid, modified=0 ;
   char ch ;
   gotoxy(3,14) ;
   cout <<"QUESTION # " <<t_ques_no ;
   gotoxy(3,16) ;
   cout <<"QUESTION : " ;
   gotoxy(3,17) ;
   cout <<"ANSWER 1 : " ;
   gotoxy(3,18) ;
   cout <<"ANSWER 2 : " ;
   gotoxy(3,19) ;
   cout <<"ANSWER 3 : " ;
   gotoxy(3,20) ;
   cout <<"SOLUTION : " ;
   gotoxy(1,25) ;	clreol() ;
   gotoxy(14,16) ;
   cout <<"Change (y/n)  " ;
   do{
	valid = 1 ;
	gotoxy(28,16) ;
	ch = getche() ;
	ch = toupper(ch) ;
	if (ch != 'Y' && ch != 'N'){
		valid = 0 ;
		sound(500) ;
		delay(100) ;
		nosound() ;
		gotoxy(28,16) ; clreol() ;
	}
   } while (!valid) ;
   valid = 0 ;
   while (!valid && ch == 'Y'){
	modified = 1 ;
	valid = 1 ;
	gotoxy(14,16) ; clreol() ;
	gotoxy(72,25) ;
	cout <<"<0>=EXIT" ;
	gotoxy(3,25) ;
	cout <<"ENTER QUESTION" ;
	gotoxy(14,16) ;
	gets(ques) ;
	strupr(ques) ;
	if (ques[0] == '0')
		return ;
	if (strlen(ques) >159 || strlen(ques) == 0){
		valid = 0 ;
		sound(500) ;
		delay(100) ;
		nosound() ;
		gotoxy(1,25) ;	clreol() ;
		gotoxy(1,24) ;
		cout <<"LENGTH SHOULD NOT BLANK OR GREATER THAN 159" ;
		gotoxy(1,25) ;
		cout <<"Press any key to continue..." ;
		getch() ;
		gotoxy(1,24) ;	clreol() ;
		gotoxy(1,25) ;	clreol() ;
		gotoxy(14,16) ; clreol() ;
	}
   }
   gotoxy(1,25) ;	clreol() ;
   gotoxy(14,17) ;
   cout <<"Change (y/n)  " ;
   do{
	valid = 1 ;
	gotoxy(28,17) ;
	ch = getche() ;
	ch = toupper(ch) ;
	if (ch != 'Y' && ch != 'N'){
		valid = 0 ;
		sound(500) ;
		delay(100) ;
		nosound() ;
		gotoxy(28,17) ; clreol() ;
	}
   } while (!valid) ;
   valid = 0 ;
   while (!valid && ch == 'Y'){
	modified = 1 ;
	valid = 1 ;
	gotoxy(13,17) ; clreol() ;
	gotoxy(72,25) ;
	cout <<"<0>=EXIT" ;
	gotoxy(3,25) ;
	cout <<"ENTER ANSWER FOR THE QUESTION" ;
	gotoxy(14,17) ;
	gets(ans1) ;
	strupr(ans1) ;
	if (ans1[0] == '0')
		return ;
	if (strlen(ans1) > 49){
		valid = 0 ;
		sound(500) ;
		delay(100) ;
		nosound() ;
		gotoxy(1,25) ;	clreol() ;
		gotoxy(1,24) ;
		cout <<"LENGTH SHOULD NOT GREATER THAN 49" ;
		gotoxy(1,25) ;
		cout <<"Press any key to continue..." ;
		getch() ;
		gotoxy(1,24) ;	clreol() ;
		gotoxy(1,25) ;	clreol() ;
		gotoxy(14,17) ; clreol() ;
	}
   }
   gotoxy(1,25) ;	clreol() ;
   gotoxy(14,18) ;
   cout <<"Change (y/n)  " ;
   do{
	valid = 1 ;
	gotoxy(28,18) ;
	ch = getche() ;
	ch = toupper(ch) ;
	if (ch != 'Y' && ch != 'N'){
		valid = 0 ;
		sound(500) ;
		delay(100) ;
		nosound() ;
		gotoxy(28,18) ; clreol() ;
	}
   } while (!valid) ;
   valid = 0 ;
   while (!valid && ch == 'Y'){
	modified = 1 ;
	valid = 1 ;
	gotoxy(14,18) ; clreol() ;
	gotoxy(72,25) ;
	cout <<"<0>=EXIT" ;
	gotoxy(3,25) ;
	cout <<"ENTER ANSWER FOR THE QUESTION" ;
	gotoxy(14,18) ;
	gets(ans2) ;
	strupr(ans2) ;
	if (ans2[0] == '0')
		return ;
	if (strlen(ans2) > 49){
		valid = 0 ;
		sound(500) ;
		delay(100) ;
		nosound() ;
		gotoxy(1,25) ;	clreol() ;
		gotoxy(1,24) ;
		cout <<"LENGTH SHOULD NOT GREATER THAN 49" ;
		gotoxy(1,25) ;
		cout <<"Press any key to continue..." ;
		getch() ;
		gotoxy(1,24) ;	clreol() ;
		gotoxy(1,25) ;	clreol() ;
		gotoxy(14,18) ; clreol() ;
	}
   }
   gotoxy(1,25) ;	clreol() ;
   gotoxy(14,19) ;
   cout <<"Change (y/n)  " ;
   do{
	valid = 1 ;
	gotoxy(28,19) ;
	ch = getche() ;
	ch = toupper(ch) ;
	if (ch != 'Y' && ch != 'N'){
		valid = 0 ;
		sound(500) ;
		delay(100) ;
		nosound() ;
		gotoxy(28,19) ; clreol() ;
	}
   } while (!valid) ;
   valid = 0 ;
   while (!valid && ch == 'Y'){
	modified = 1 ;
	valid = 1 ;
	gotoxy(14,19) ; clreol() ;
	gotoxy(72,25) ;
	cout <<"<0>=EXIT" ;
	gotoxy(3,25) ;
	cout <<"ENTER ANSWER FOR THE QUESTION" ;
	gotoxy(14,19) ;
	gets(ans3) ;
	strupr(ans3) ;
	if (ans3[0] == '0')
		return ;
	if (strlen(ans3) > 49){
		valid = 0 ;
		sound(500) ;
		delay(100) ;
		nosound() ;
		gotoxy(1,25) ;	clreol() ;
		gotoxy(1,24) ;
		cout <<"LENGTH SHOULD NOT GREATER THAN 49" ;
		gotoxy(1,25) ;
		cout <<"Press any key to continue..." ;
		getch() ;
		gotoxy(1,24) ;	clreol() ;
		gotoxy(1,25) ;	clreol() ;
		gotoxy(14,19) ; clreol() ;
	}
   }
   if (!modified)
	return ;
   do{
	gotoxy(1,25) ;	clreol() ;
	valid = 1 ;
	gotoxy(72,25) ;
	cout <<"<0>=EXIT" ;
	gotoxy(3,25) ;
	cout <<"ENTER CORRECT SOLUTION FOR THE QUESTION (1/2/3)" ;
	gotoxy(14,20) ;
	sol = getche() ;
	if (sol == '0')
		return ;
	if (sol != '1' && sol != '2' && sol != '3'){
		valid = 0 ;
		sound(500) ;
		delay(100) ;
		nosound() ;
		gotoxy(14,20) ; clreol() ;
	}
   } while (!valid) ;
   gotoxy(1,25) ; clreol() ;
   gotoxy(1,24) ; clreol() ;
   gotoxy(1,22) ;
   cout <<"Do you want to save the record (y/n)  : " ;
   do{
	valid = 1 ;
	gotoxy(41,22) ;
	ch = getche() ;
	ch = toupper(ch) ;
	if (ch != 'Y' && ch != 'N'){
		valid = 0 ;
		sound(500) ;
		delay(100) ;
		nosound() ;
		gotoxy(41,22) ; clreol() ;
	}
   } while ( !valid ) ;
   if (ch == 'N')
	return ;
   fstream file ;
   file.open(filename, ios::out | ios::ate) ;
   int recno ;
   recno = t_ques_no ;
   int location ;
   location = (recno-1) * sizeof(Quiz) ;
   file.seekp(location) ;
   file.write((char *) this, sizeof(Quiz)) ;
   file.close() ;
   clrscr() ;
   sound(500) ;
   delay(100) ;
   nosound() ;
   gotoxy(1,14) ;
   cout <<"Record Modified" ;
   gotoxy(1,25) ;
   cout <<"Press any key to continue..." ;
   getch() ;
}
void Quiz :: modify(char filename[13]){
   clrscr() ;
   int valid ;
   int t_ques_no=0, t;
   char t1_ques_no[5] ;
   char ch ;
   gotoxy(72,25) ;
   cout <<"<0>=EXIT" ;
   gotoxy(3,3) ;
   cout <<"Enter question no. to be modify  : " ;
   do{
	gotoxy(38,3) ;
	gets(t1_ques_no) ;
   } while (strlen(t1_ques_no) == 0) ;
   t = atoi(t1_ques_no) ;
   t_ques_no = t ;
   if (t1_ques_no[0] == '0')
	return ;
   if (!found_record(filename,t_ques_no)){
	sound(500) ;
	delay(100) ;
	nosound() ;
	gotoxy(3,15) ;
	cout <<"question not found" ;
	gotoxy(1,25) ;
	cout <<"Press any key to continue..." ;
	getch() ;
	return ;
   }
   clrscr() ;
   display_record(filename,t_ques_no) ;
   gotoxy(3,12) ;
   cout <<"Do you want to modify this Record (y/n) : " ;
   do{
	valid = 1 ;
	gotoxy(45,12) ;
	ch = getche() ;
	ch = toupper(ch) ;
	if (ch != 'Y' && ch != 'N'){
		valid = 0 ;
		sound(500) ;
		delay(100) ;
		nosound() ;
		gotoxy(45,10) ; clreol() ;
	}
   } while (!valid ) ;
   if (ch == 'N')
	return ;
   modify_record(filename,t_ques_no) ;
}

int  Quiz :: record_count(char filename[13]){
   fstream file ;
   file.open(filename, ios::in) ;
   file.seekg(0,ios::beg) ;
   int t=0 ;
   while (file.read((char *) this, sizeof(Quiz)))
	t++ ;
   file.close() ;
   return t ;
}
void Quiz :: delete_record(char filename[13], int t_ques_no){
   fstream file ;
   file.open(filename, ios::in) ;
   fstream temp ;
   temp.open("temp.dat", ios::out) ;
   file.seekg(0,ios::beg) ;
   while (!file.eof()){
	file.read((char *) this, sizeof(Quiz)) ;
	if ( file.eof() )
		break ;
	if (ques_no != t_ques_no)
		temp.write((char *) this, sizeof(Quiz)) ;
   }
   file.close() ;
   temp.close() ;
   file.open(filename, ios::out) ;
   temp.open("temp.dat", ios::in) ;
   temp.seekg(0,ios::beg) ;
   t_ques_no = 1 ;
   while (!temp.eof()){
	temp.read((char *) this, sizeof(Quiz)) ;
	ques_no = t_ques_no ;
	if (temp.eof())
		break ;
	file.write((char *) this, sizeof(Quiz)) ;
	t_ques_no++ ;
   }
   file.close() ;
   temp.close() ;
}

void Quiz :: display_score(int played, int correct){
	clrscr() ;
	textbackground(WHITE) ;
	textcolor(BLACK) ;
	gotoxy(25,4) ;
	cprintf("                               ") ;
	gotoxy(30,4) ;
	cprintf("S C O R E   B O A R D") ;
	textbackground(BLACK) ;
	textcolor(LIGHTGRAY) ;
	gotoxy(10,7) ;
	cout <<"Player's Name : " <<participant ;
	gotoxy(10,9) ;
	cout <<"questions Attempted : " <<played ;
	gotoxy(10,11) ;
	cout <<"Correct answer      : " <<correct ;
	gotoxy(10,13) ;
	cout <<"Wrong answer        : " <<played-correct ;
	int score ;
	score = correct * 10 ;
	gotoxy(10,16) ;
	cout <<"Score  : " <<score ;
	int tplayed ;
	tplayed = played * 10 ;
	float percentage ;
	percentage = ((score*100)/tplayed) ;
	gotoxy(10,18) ;
	cout <<"Percentage : " <<percentage ;
	getch() ;
}
void Quiz :: play(char filename[13]){
	clrscr() ;
	char t_sol, ch ;
	int  correct=0, played=0, valid ;

	fstream file ;
	file.open(filename,ios::in) ;
	file.seekg(0,ios::beg) ;
	while (file.read((char *) this, sizeof(Quiz))){
		clrscr() ;
		gotoxy(25,3) ;
		cout <<"SCORE:" <<correct*10 ;
		valid = 1 ;
		gotoxy(28,24) ;
		cout <<"<ESC>=Exit" ;

		gotoxy(5,6);
		cout<<"Q "<<ques_no<<"  "<<ques;
		gotoxy(5,9);
		cout<<"1.)"<<ans1;
		gotoxy(5,11);
		cout<<"2.)"<<ans2;
		gotoxy(5,13);
		cout<<"3.)"<<ans3;
		gotoxy(5,15);
		cout<<"Solution : ";
		int i=0, j=0, time=20 ;
		do{
			valid = 1 ;
			gotoxy(3,21) ;
			cout <<"Time : " <<time ;
			gotoxy(28,15) ;
			do{
				delay(1) ;
				i++ ;
				j++ ;
				if (j == 600){
					j = 0 ;
					time-- ;
					gotoxy(11,21) ;
					cout <<" " ;
					gotoxy(10,21) ;
					cout <<time ;
					gotoxy(28,15) ;
				}
			} while (!kbhit() && i<12000) ;
			if (i >= 12000){
				played++ ;
				sound(500) ;
				delay(100) ;
				nosound() ;
				gotoxy(13,16) ;
				cout <<"Sorry Time up!" ;
				gotoxy(1,1) ;
				i = 0;
				getch() ;
//				if (played)
//					display_score(played,correct) ;
//				return ;
			}
			gotoxy(3,21) ;
			cout <<"             " ;
			gotoxy(28,15) ;
			t_sol = getche() ;
			if (t_sol == 27){
				if (played)
					display_score(played,correct) ;
				return ;
			}
			if (t_sol != '1' && t_sol != '2' && t_sol != '3'){
				valid = 0 ;
				sound(500) ;
				delay(100) ;
				nosound() ;
				gotoxy(28,15) ;
				cout <<"  " ;
			}
		} while (!valid) ;
		played++ ;
		if (t_sol != sol){
			sound(500) ;
			delay(100) ;
			nosound() ;
			gotoxy(14,16) ;
			cout <<"wrong answer" ;
			gotoxy(13,17) ;
			cout <<"Correct answer : " <<sol ;
			gotoxy(1,1) ;
			ch = getch() ;
			gotoxy(14,15) ;
			cout <<"            " ;
			gotoxy(13,16) ;
			cout <<"                    " ;
			gotoxy(3,24) ;
			cout <<"                                    " ;
		}
		else{
			correct++ ;
			sound(500) ;
			delay(100) ;
			nosound() ;
			gotoxy(16,16) ;
			cout <<"GOOD ! CORRECT ANSWER" ;
			gotoxy(25,3) ;
			cout <<"SCORE:" <<correct*10 ;
			gotoxy(1,1) ;
			ch = getch() ;
		}
		if (ch == 27){
			display_score(played,correct) ;
			return ;
		}
	}
	gotoxy(3,22) ;
	cout <<"No more questions available" ;
	getch() ;
	if (!played)
		return ;
	display_score(played,correct) ;
}
void Quiz :: add(char filename[13]){
   int valid ;
   int t_ques_no ;
   t_ques_no = record_count(filename) ;
   t_ques_no++ ;
   if (t_ques_no == 1){
	ques_no = t_ques_no ;
	strcpy(ques,"abc") ;
	strcpy(ans1,"-") ;
	strcpy(ans2,"-") ;
	strcpy(ans3,"-") ;
	sol = '0' ;
	fstream file ;
	file.open(filename, ios::out | ios::app ) ;
	file.write((char *) this, sizeof(Quiz)) ;
	file.close() ;
	delete_record(filename,t_ques_no) ;
   }
   char ch ;
   do{
	clrscr() ;

	gotoxy(15,4);
	cout<<"A D D   Q U E S T I O N S";

	gotoxy(5,8);
	cout<<"Q "<<t_ques_no;
	gotoxy(5,10);
	cout<<"1.)";
	gotoxy(5,12);
	cout<<"2.)";
	gotoxy(5,14);
	cout<<"3.)";
	gotoxy(5,16);
	cout<<"Solution : ";
	do{
		valid = 1 ;
		gotoxy(1,25) ;	clreol() ;
		gotoxy(72,25) ;
		cout <<"<0>=EXIT" ;
		gotoxy(3,25) ;
		cout <<"ENTER QUESTION" ;
		gotoxy(12,8) ;
		gets(ques) ;
		strupr(ques) ;
		if (ques[0] == '0')
			return ;
		if (strlen(ques) > 159 || strlen(ques) == 0){
			valid = 0 ;
			sound(500) ;
			delay(100) ;
			nosound() ;
			gotoxy(1,25) ;	clreol() ;
			gotoxy(1,24) ;
			cout <<"LENGTH SHOULD NOT BE BLANK OR GREATER THAN 159" ;
			gotoxy(1,25) ;
			cout <<"Press any key to continue..." ;
			getch() ;
			gotoxy(1,24) ;	clreol() ;
			gotoxy(1,25) ;	clreol() ;
			gotoxy(14,8) ; clreol() ;
		}
	} while ( !valid ) ;
	do{
		valid = 1 ;
		gotoxy(1,25) ;	clreol() ;
		gotoxy(72,25) ;
		cout <<"<0>=EXIT" ;
		gotoxy(3,25) ;
		cout <<"ENTER ANSWER FOR THE QUESTION" ;
		gotoxy(12,10) ;
		gets(ans1) ;
		strupr(ans1) ;
		if (ans1[0] == '0')
			return ;
		if (strlen(ans1) > 49){
			valid = 0 ;
			sound(500) ;
			delay(100) ;
			nosound() ;
			gotoxy(1,25) ;	clreol() ;
			gotoxy(1,24) ;
			cout <<"LENGTH SHOULD NOT GREATER THAN 49" ;
			gotoxy(1,25) ;
			cout <<"Press any key to continue..." ;
			getch() ;
			gotoxy(1,24) ;	clreol() ;
			gotoxy(1,25) ;	clreol() ;
			gotoxy(14,10) ; clreol() ;
		}
	} while ( !valid ) ;
	do{
		valid = 1 ;
		gotoxy(1,25) ;	clreol() ;
		gotoxy(72,25) ;
		cout <<"<0>=EXIT" ;
		gotoxy(3,25) ;
		cout <<"ENTER ANSWER FOR THE QUESTION" ;
		gotoxy(12,12) ;
		gets(ans2) ;
		strupr(ans2) ;
		if (ans2[0] == '0')
			return ;
		if (strlen(ans2) > 49){
			valid = 0 ;
			sound(500) ;
			delay(100) ;
			nosound() ;
			gotoxy(1,25) ;	clreol() ;
			gotoxy(1,24) ;
			cout <<"LENGTH SHOULD NOT GREATER THAN 49" ;
			gotoxy(1,25) ;
			cout <<"Press any key to continue..." ;
			getch() ;
			gotoxy(1,24) ;	clreol() ;
			gotoxy(1,25) ;	clreol() ;
			gotoxy(14,12) ; clreol() ;
		}
	} while ( !valid ) ;
	do{
		valid = 1 ;
		gotoxy(1,25) ;	clreol() ;
		gotoxy(72,25) ;
		cout <<"<0>=EXIT" ;
		gotoxy(3,25) ;
		cout <<"ENTER ANSWER FOR THE QUESTION" ;
		gotoxy(12,14) ;
		gets(ans3) ;
		strupr(ans3) ;
		if (ans3[0] == '0')
			return ;
		if (strlen(ans3) > 49){
			valid = 0 ;
			sound(500) ;
			delay(100) ;
			nosound() ;
			gotoxy(1,25) ;	clreol() ;
			gotoxy(1,24) ;
			cout <<"LENGTH SHOULD NOT GREATER THAN 49" ;
			gotoxy(1,25) ;
			cout <<"Press any key to continue..." ;
			getch() ;
			gotoxy(1,24) ;	clreol() ;
			gotoxy(1,25) ;	clreol() ;
			gotoxy(14,14) ; clreol() ;
		}
	} while ( !valid ) ;
	do{
		valid = 1 ;
		gotoxy(1,25) ;	clreol() ;
		gotoxy(72,25) ;
		cout <<"<0>=EXIT" ;
		gotoxy(3,25) ;
		cout <<"ENTER CORRECT SOLUTION FOR THE QUESTION (1/2/3)" ;
		gotoxy(16,16) ;
		sol = getche() ;
		if (sol == '0')
			return ;
		if (sol != '1' && sol != '2' && sol != '3'){
			valid = 0 ;
			sound(500) ;
			delay(100) ;
			nosound() ;
			gotoxy(14,16) ; clreol() ;
		}
	} while ( !valid ) ;
	gotoxy(1,25) ;	clreol() ;
	gotoxy(1,24) ;  clreol() ;
	gotoxy(72,25) ;
	cout <<"<0>=EXIT" ;
	gotoxy(3,19) ;
	cout <<"Do you want to save the record (y/n) : " ;
	do{
		valid = 1 ;
		gotoxy(42,19) ;
		ch = getche() ;
		ch = toupper(ch) ;
		if (ch == '0')
			return ;
		if (ch != 'Y' && ch != 'N'){
			valid = 0 ;
			sound(500) ;
			delay(100) ;
			nosound() ;
			gotoxy(42,19) ; clreol() ;
		}
	} while ( !valid ) ;
	if (ch == 'Y'){
		ques_no = t_ques_no ;
		fstream file ;
		file.open(filename, ios::app ) ;
		file.write((char *) this, sizeof(Quiz)) ;
		file.close() ;
		t_ques_no++ ;
	}
	gotoxy(72,25) ;
	cout <<"<0>=EXIT" ;
	gotoxy(3,21) ;
	cout <<"Do you want to add more questions (y/n) : " ;
	do{
		valid = 1 ;
		gotoxy(45,21) ;
		ch = getche() ;
		ch = toupper(ch) ;
		if (ch == '0')
			return ;
		if (ch != 'Y' && ch != 'N'){
			valid = 0 ;
			sound(500) ;
			delay(100) ;
			nosound() ;
			gotoxy(45,21) ; clreol() ;
		}
	} while ( !valid ) ;
   } while (ch == 'y');
}
void Quiz :: keyConnect(int x, int y, int n, int menu_no){
	char ch, chr=175 ;//  >>
	int up_limit = y, lower_limit = y+n-1;

	gotoxy(x, up_limit) ;
	cout <<chr ;
	do{
		ch = getch();
		// for moving the cursor in upward direction.
		if(ch == 72 && y > up_limit){
			gotoxy(x,y) ;
			cout <<" " ;
			y = (y - 1) ;
			gotoxy(x,y) ;
			cout <<chr ;
			sound(200) ;
			delay(30) ;
			nosound() ;
		}
		// for moving the cursor in downward direction.
		else if(ch == 80 && y<lower_limit){
			gotoxy(x,y) ;
			cout <<" " ;
			y = (y + 1) ;
			gotoxy(x,y) ;
			cout <<chr ;
			sound(200) ;
			delay(30) ;
			nosound() ;
		}

		// Main Menu
		if(y == 8 && ch == 13 && menu_no == 1){
			availableCourses();
		}
		if(y == 9 && ch == 13 && menu_no == 1){
			Edit();
		}
		if(y == 10 && ch == 13 && menu_no == 1){
			exit(0);
		}

		// Available Courses sub-menu
		if(y == 10 && ch == 13 && menu_no == 2){
			clrscr();
			textmode(C80) ;
			clrscr() ;
			textbackground(LIGHTGRAY);
			textcolor(RED) ;
			clrscr();
			gotoxy(5,5) ;
			display("J A V A");
			gotoxy(1,6);
			cout<<"-------------------------------------------------------------------------------";

			gotoxy(1,23);
			cout<<"-------------------------------------------------------------------------------";
			gotoxy(5,24);
			cout<<"Press escape to exit.";
			play("JAVA.DAT") ;
			clrscr() ;
			menu();
		}
		if(y == 11 && ch == 13 && menu_no == 2){
			char choice;

			textmode(C80) ;
			clrscr() ;
			textbackground(LIGHTGRAY) ;
			textcolor(RED) ;
			clrscr();
			gotoxy(5,5) ;
			display("H T M L");
			gotoxy(1,6);
			cout<<"-------------------------------------------------------------------------------";

			gotoxy(1,23);
			cout<<"-------------------------------------------------------------------------------";
			gotoxy(5,24);
			cout<<"Press escape to exit.";

			play("HTML.DAT") ;
			clrscr() ;
			menu();
		}
		if(y == 12 && ch == 13 && menu_no == 2){
			textmode(C80) ;
			clrscr() ;
			textbackground(LIGHTGRAY);
			textcolor(RED) ;
			clrscr();
			gotoxy(5,5) ;
			display("P Y T H O N");
			gotoxy(1,6);
			cout<<"-------------------------------------------------------------------------------";

			gotoxy(1,23);
			cout<<"-------------------------------------------------------------------------------";
			gotoxy(5,24);
			cout<<"Press escape to exit.";

			play("PYTHON.DAT") ;
			clrscr() ;
			menu();
		}
		if(y == 13 && ch == 13 && menu_no == 2){
			textmode(C80) ;
			clrscr() ;
			textbackground(LIGHTGRAY);
			textcolor(RED) ;
			clrscr();
			gotoxy(5,5) ;
			display("D A A");
			gotoxy(1,6);
			cout<<"-------------------------------------------------------------------------------";

			gotoxy(1,23);
			cout<<"-------------------------------------------------------------------------------";
			gotoxy(5,24);
			cout<<"Press escape to exit.";

			play("Daa.DAT") ;
			clrscr() ;
			menu();
		}
		if(ch == 27 && (menu_no == 2 || menu_no == 3)){
			hide_sub_menu(1);
			hide_sub_menu(2);
			break;
		}

		// Edit Menu
		if(y == 11 && ch == 13 && menu_no == 3){
			add("Daa.DAT");
			menu();
		}
		if(y == 12 && ch == 13 && menu_no == 3){
			modify("Daa.DAT");
			menu();
		}
	}while(ch != 27);
}
void Quiz :: sub_menu(int n, char title[]){
	gotoxy(25,6+n) ;
	cout<<"#####################"<<"\n";
	gotoxy(25,7+n) ;
	cout<<"#                   #"<<"\n";
	gotoxy(28,7+n);
	cout<<title;
	gotoxy(25,8+n) ;
	cout<<"#####################"<<"\n";
}
void Quiz :: hide_sub_menu(int n){
	for(i=0;i<12;i++){
		gotoxy(24,6+i+n) ;
		cout<<"                      "<<"\n";
	}
}
void Quiz :: menu(){
	textmode(C80) ;
	clrscr() ;
	textbackground(LIGHTGRAY);

	textcolor(RED) ;
	clrscr();
	gotoxy(5,5) ;
	display("Q U I Z  M A N I A") ;
	gotoxy(1,6);
	cout<<"-------------------------------------------------------------------------------";
	gotoxy(5,8) ;
	cout << "Available Courses";
	gotoxy(5,9) ;
	cout << "Edit";
	gotoxy(5,10) ;
	cout << "Exit";

	gotoxy(1,23);
	cout<<"-------------------------------------------------------------------------------";
	gotoxy(5,24);
	cout<<"Press escape to exit.";
	keyConnect(4, 8, 3, 1);
}
void Quiz :: availableCourses(){

	sub_menu(1, "COURSES");
	// no. of courses = 4
	for(i=0;i<4;i++){
		gotoxy(25,10+i);
		cout<<"#                   #"<<"\n";
		gotoxy(31, 10+i);
		cout<<i+1<<". ";
		cout<<courses[i];
		gotoxy(25,11+i) ;
		cout<<"#####################"<<"\n";
	}

	keyConnect(24, 10, 4, 2);
}
void Quiz :: Edit(){
	hide_sub_menu(1);
	hide_sub_menu(2);
	sub_menu(2, "EDIT MENU");

	gotoxy(25, 11);
	cout<<"#  Add Question     #"<<"\n";
	gotoxy(25, 12);
	cout<<"#  Modify Question  #"<<"\n";
	gotoxy(25, 13) ;
	cout<<"#####################"<<"\n";

	keyConnect(24, 11, 2, 3);
}

/*============================================================================
	Module is use for secure sign up and login.
============================================================================*/
class LogIn{
		char *pass;

		void validate(char [], char [], char []);
	public:
		char name[15], *id, ch;

		void menu(int, int);
		void signUp();
		void logIn();
//                void add_user();
};
void LogIn :: signUp(){
	textmode(C80) ;
	clrscr() ;
	textbackground(9);
	textcolor(3) ;
	clrscr();

	gotoxy(32,5);
	cout<<"################";
	gotoxy(32,6);
	cout<<"#    SignUp    #";
	gotoxy(32,7);
	cout<<"################";

	gotoxy(17,11);
	cout<<"Name      :";
	gotoxy(30,10);
	cout<<"#####################";
	gotoxy(30,11);
	cout<<"#                   #";
	gotoxy(30,12);
	cout<<"#####################";

	gotoxy(17,16);
	cout<<"Password  :";
	gotoxy(30,15);
	cout<<"#####################";
	gotoxy(30,16);
	cout<<"#                   #";
	gotoxy(30,17);
	cout<<"#####################";

	gotoxy(9,21);
	cout<<"ID (Admin/Guest)  :";
	gotoxy(30,20);
	cout<<"#####################";
	gotoxy(30,21);
	cout<<"#                   #";
	gotoxy(30,22);
	cout<<"#####################";
}
void LogIn :: logIn(){
	textmode(C80) ;
	clrscr() ;
	textbackground(3);
	textcolor(4) ;
	clrscr();

	gotoxy(32,5);
	cout<<"################";
	gotoxy(32,6);
	cout<<"#     LogIn    #";
	gotoxy(32,7);
	cout<<"################";

	gotoxy(17,11);
	cout<<"Name      :";
	gotoxy(30,10);
	cout<<"#####################";
	gotoxy(30,11);
	cout<<"#                   #";
	gotoxy(30,12);
	cout<<"#####################";

	gotoxy(17,16);
	cout<<"Password  :";
	gotoxy(30,15);
	cout<<"#####################";
	gotoxy(30,16);
	cout<<"#                   #";
	gotoxy(30,17);
	cout<<"#####################";

	gotoxy(9,21);
	cout<<"ID (Admin/Guest)  :";
	gotoxy(30,20);
	cout<<"#####################";
	gotoxy(30,21);
	cout<<"#                   #";
	gotoxy(30,22);
	cout<<"#####################";
}
void LogIn :: menu(int b_color, int t_color){
	int flag = 1;

	textmode(C80) ;
	clrscr() ;
	textbackground(b_color);
	textcolor(t_color) ;
	clrscr();

	gotoxy(20,5);
	cout<<"##########";
	gotoxy(20,6);
	cout<<"# SignUp #";
	gotoxy(20,7);
	cout<<"##########";

	gotoxy(50,5);
	cout<<"##########";
	gotoxy(50,6);
	cout<<"# LogIn  #";
	gotoxy(50,7);
	cout<<"##########";

	gotoxy(17,11);
	cout<<"Name      :";
	gotoxy(30,10);
	cout<<"#####################";
	gotoxy(30,11);
	cout<<"#                   #";
	gotoxy(30,12);
	cout<<"#####################";

	gotoxy(17,16);
	cout<<"Password  :";
	gotoxy(30,15);
	cout<<"#####################";
	gotoxy(30,16);
	cout<<"#                   #";
	gotoxy(30,17);
	cout<<"#####################";

	gotoxy(9,21);
	cout<<"ID (Admin/Guest)  :";
	gotoxy(30,20);
	cout<<"#####################";
	gotoxy(30,21);
	cout<<"#                   #";
	gotoxy(30,22);
	cout<<"#####################";

	do{
		ch = getch();

		if(ch == 27)    exit(1);
		// if left arrow key is pressed.
		if(ch == 75){
			flag = 0;
			signUp();
			sound(200) ;
			delay(30) ;
			nosound() ;
		}
		// if right arrow key is pressed.
		else if(ch == 77){
			flag = 1;
			logIn();
			sound(200) ;
			delay(30) ;
			nosound() ;
		}
	}while(ch != 13);
	// enter the username
	gotoxy(33,11);
	for(i=0;i<20;i++ ){
		name[i]=getche();
		if(name[i]==27)		exit(0);
		if(name[i]=='\r'){
			name[i]='\0';
			break;
		}
	}
	// enter the password
	gotoxy(33,16);
	for(i=0;i<20;i++ ){
		pass[i]=getche();
		if(pass[i]==27)		exit(0);
		if(pass[i]=='\r'){
			pass[i]='\0';
			break;
		}
		else{
			gotoxy(33+i,16);
			cout<< "*";
		}
	}
	// enter id
	gotoxy(33,21);
	for(i=0;i<20;i++ ){
		id[i]=getche();
		if(id[i]==27)		exit(0);
		if(id[i]=='\r'){
			id[i]='\0';
			break;
		}
	}
	if(flag != 0)
		validate(name, pass, id);
	else{
		Menu menu;
		menu.welcome("Guest");
		Quiz quiz;
		quiz.menu();
	}
}
void LogIn :: validate(char n[], char p[], char id[]){
	char userName[15], pass[15], identity[10];

	ifstream read("key.dat");
	read >> userName;
	read >> pass;
	read >> identity;

	cout<<identity;

	if(strcmp(n, userName) == 0 && strcmp(p, pass) == 0 && strcmp(identity, id) == 0){
		Menu menu;
		participant = n;
		menu.welcome(n);
		Quiz quiz;
		quiz.menu();
	}
	else{
		gotoxy(30,25);
		cout<<"Invalid User";
		delay(10);
		menu(7, 6);
	}
}

int main() {
	Menu menu;
	LogIn login;
	int gd=DETECT, gm;
	initgraph(&gd, &gm, " ");

	menu.frontPage();
	login.menu(7, 6);
	menu.thanks();

	return 0;
}