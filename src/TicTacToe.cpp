//============================================================================
// Name        : TicTacToe.cpp
// Author      : rish_ftw
// Version     : 1.01
// Copyright   : rish©ftw
// Description : TicTacToe
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <fstream>
#include <sstream>
using namespace std;

typedef class HallOfFame{
	string name;
	int score;
	int rank;
public:
	string getName();//Returns name of highscorer
	int getScore();//Returns score of highscorer
	int getRank();//Returns rank of highscorer
	void setName(string n);//Assigns value to name
	void setScore(int s);//Assigns value to score
	void setRank(int r);//Assigns value to rank
}highScore;//Definition of the class to store scores details

string HallOfFame::getName(){
	return name;
}

int HallOfFame::getScore(){
	return score;
}

int HallOfFame::getRank(){
	return rank;
}

void HallOfFame::setName(string n){
	name = n;
}

void HallOfFame::setScore(int s){
	score = s;
}

void HallOfFame::setRank(int r){
	rank = r;
}

class TicTacToe{
	enum winner{
		player, player2, draw
	};//Definition of enum, containing possible winners

	int score, score2;
	string name1, name2;
	winner winnerComp;
	highScore *highs;

	void playGame();//Start playing
	void readSaveData();//Read highscore data from save file
	void writeSaveData();//Write HighScore data to save file
	void playComp();//Play a game with the computer
	void playSecondPlayer();//Play a game with another person
	void viewHallOfFame();//See the High scores
	void displayTable(char vals[9], string msg, int unAm);//Display the tictactoe table without asking for input
	int displayTable(char vals[9], string heading);//Display tictactoe table with input query
	bool checkDone(char vals[9], int position);//Check whether position is already used
	void compTurn(char vals[9]);//Play computer's turn
	bool checkWin(char vals[9]);//Check if game has ended
	string rishEncrypt(int key, string alphaNum);//Simple encryption.
	string rishDecrypt(int key, string encryptedString);//Simple decryption

public:
	TicTacToe();
};

TicTacToe::TicTacToe(){
	score = 0;
	score2 = 0;
	name1 = "";
	name2 = "Anonymous";
	winnerComp = draw;
	highs = new highScore[2];
	playGame();
}

void TicTacToe::playGame(){
	readSaveData();

	int ch;
	bool done=false;

	cout<<"Heyy, Welcome to Tic-Tac-Toe:D\n";
	cout<<"Enter Your Name:\n";
	cin>>name1;
	highs[0].setName(name1);

	while(done==false){
	   cout<<"Choose a Mode:\n1)Vs Computer\n2)Vs Second Player\n3)Hall Of Fame\n4)Exit\n";
	   cin>>ch;

	   switch(ch){
		case 1:	playComp();
				break;
		case 2:	cout<<"Enter Second Player's Name\n";
				cin>>name2;
				highs[1].setName(name2);
				playSecondPlayer();
				break;
		case 3:	viewHallOfFame();
				break;
		case 4:	writeSaveData();
				done=true;
				break;
		default:cout<<"Invalid Choice, Selected Default(Vs Comp.)";
				playComp();
				  break;
	   }
	}

	cout<<"Thanks For Playing.\nGame by Rishav Guha.\nGoodbye...";
				cout<<"\n3"<<endl;
				Sleep(1000);
				cout<<"2"<<endl;
				Sleep(1000);
				cout<<"1"<<endl;
				Sleep(1000);
				exit(0);
}

void TicTacToe::readSaveData(){
	string tempName1, tempName2;
	string tempScore1, tempScore2;

	ifstream saveDataFile(".saveData.txt");
	if(saveDataFile.is_open()){
		if(saveDataFile.good()==true){
			getline(saveDataFile,tempName1);
		}

		if(saveDataFile.good()==true){
			getline(saveDataFile,tempScore1);
		}

		if(saveDataFile.good()==true){
			getline(saveDataFile,tempName2);
		}

		if(saveDataFile.good()==true){
			getline(saveDataFile,tempScore2);
		}
		highs[0].setName(rishDecrypt(28, tempName1));
		highs[1].setName(rishDecrypt(28, tempName2));
		highs[0].setScore(atoi((rishDecrypt(28,tempScore1)).c_str()));
		highs[1].setScore(atoi((rishDecrypt(28,tempScore2)).c_str()));

		saveDataFile.close();
	}else{
		highs[0].setName("Anonymous");
		highs[1].setName("Anonymous");
		highs[0].setScore(0);
		highs[1].setScore(0);
	}
}

void TicTacToe::writeSaveData(){
	ofstream saveDataFile(".saveData.txt");
	if(saveDataFile.is_open()){
		string score1Temp, score2Temp;
		ostringstream convert;
		ostringstream convert2;
		convert<<highs[0].getScore();
		convert2<<highs[1].getScore();
		score1Temp = convert.str();
		score2Temp = convert2.str();
		saveDataFile<<rishEncrypt(28, highs[0].getName())<<"\n";
		saveDataFile<<rishEncrypt(28, score1Temp)<<"\n";
		saveDataFile<<rishEncrypt(28, highs[1].getName())<<"\n";
		saveDataFile<<rishEncrypt(28, score2Temp)<<"\n";
	}else{
		;
	}
}

void TicTacToe::playComp(){
	int ans=1;

	string h1="Congratulations!!!", h2="Sorry!:'(", h3="Draw:/";

	while(ans==1){
		winnerComp=draw;

		char vals[9] = {'1','2','3','4','5','6','7','8','9'};
		bool win=false;

		while(win==false){
			int position = displayTable(vals,"Your Turn:");
			vals[position-1]='X';

			win = checkWin(vals);

			if(win==true){
				break;
			}

			compTurn(vals);

			win = checkWin(vals);
		 }

		 if(winnerComp==player2){
			 displayTable(vals,h2,2);
			 cout<<"You Lost 25 Points!\n";
			 score-=25;
		 }else if(winnerComp==player){
			 displayTable(vals, h1,2);
			 cout<<"You Won 50 Points!!\n";
			 score+=50;
		 }else{
			 displayTable(vals, h3,2);
			 cout<<"You Won 0 Points!!\n";
		 }
		 highs[0].setScore(score);

		 writeSaveData();

		 cout<<"Press:\n1->To Play again\n2->Main Menu\n3->HighScores\n";
		 cin>>ans;
	}

	writeSaveData();

    if(ans==3){
    	viewHallOfFame();
    }

}

void TicTacToe::playSecondPlayer(){
	int ans=1;

	string h1="Congratulations " + name1 + " !!!", h2="Congratulations " + name2 + " !!!", h3="Draw:/";

	while(ans==1){
		winnerComp=draw;

		char vals[9] = {'1','2','3','4','5','6','7','8','9'};
		bool win=false;

		while(win==false){
			string heading1 = name1 + "'s Turn:";
			string heading2 = name2 + "'s Turn:";

			int position1 = displayTable(vals,heading1);
			vals[position1-1]='X';

			win = checkWin(vals);

			if(win==true){
				break;
			}

			int position2 = displayTable(vals,heading2);
			vals[position2-1]='O';

			win = checkWin(vals);
		 }

		 if(winnerComp==player2){
			 displayTable(vals,h2,2);
			 cout<<name2<<" Won 50 Points!!\n";
			 score2+=50;
		 }else if(winnerComp==player){
			 displayTable(vals,h1,2);
			 cout<<name1<<" Won 50 Points!!\n";
			 score+=50;
		 }else{
			 displayTable(vals,h3,2);
			 cout<<"Draw!!\n";
		 }
		 highs[0].setScore(score);
		 highs[1].setScore(score2);

		 writeSaveData();

		 cout<<"Press:\n1->To Play again\n2->Main Menu\n3->HighScores\n";
		 cin>>ans;
	}
	writeSaveData();


    if(ans==3){
    	viewHallOfFame();
    }

}

void TicTacToe::displayTable(char vals[9], string msg, int unAm){


			cout<<msg<<endl;

			cout<<"     |     |     \n";
			cout<<"  "<<vals[0]<<"  |  "<<vals[1]<<"  |  "<<vals[2]<<"  \n";
			cout<<"_____|_____|_____\n";

			cout<<"     |     |     \n";
			cout<<"  "<<vals[3]<<"  |  "<<vals[4]<<"  |  "<<vals[5]<<"  \n";
			cout<<"_____|_____|_____\n";

			cout<<"     |     |     \n";
			cout<<"  "<<vals[6]<<"  |  "<<vals[7]<<"  |  "<<vals[8]<<"  \n";
			cout<<"     |     |     \n";

}

int TicTacToe::displayTable(char vals[9], string heading){

	bool ok = false;

	int position;

	while (ok==false){

		cout<<endl<<heading<<endl;

		cout<<"     |     |     \n";
		cout<<"  "<<vals[0]<<"  |  "<<vals[1]<<"  |  "<<vals[2]<<"  \n";
		cout<<"_____|_____|_____\n";

		cout<<"     |     |     \n";
		cout<<"  "<<vals[3]<<"  |  "<<vals[4]<<"  |  "<<vals[5]<<"  \n";
		cout<<"_____|_____|_____\n";

		cout<<"     |     |     \n";
		cout<<"  "<<vals[6]<<"  |  "<<vals[7]<<"  |  "<<vals[8]<<"  \n";
		cout<<"     |     |     \n";

		cout<<"\nEnter Position of Next Move:\n";
		cin>>position;

		if(position>9||position<1){
			heading = "Invalid Position, Try Again";
		}else if(checkDone(vals,position)==true){
			heading = "Position Already Done, Choose Another Position";
		}else{
			ok=true;
		}
	}

   return position;
}

bool TicTacToe::checkDone(char vals[], int position){
	if(vals[position-1]=='X'||vals[position-1]=='O'){
		return true;
	}else{
		return false;
	}

}

void TicTacToe::compTurn(char vals[9]){
	srand(time(NULL));

	int position;

	bool ok = false;

	while(ok==false){
		position = rand() % 10;

		if(position>9||position<1){
			;
		}else if(checkDone(vals,position)==true){
			;
		}else{
			ok=true;
		}
	}

	vals[position-1]='O';

}

bool TicTacToe::checkWin(char vals[9]){
	bool win=false, matchFound=false;

	int tempCtr=0;

	for(int i=0;i<9;i++){
		if(vals[i]=='X'||vals[i]=='O'){
			tempCtr++;
		}
	}

	if(tempCtr>=9&&(matchFound==false)){
			win=true;
			winnerComp=draw;
			matchFound=true;
	}

	if(vals[2]=='X'&&(matchFound==false)){
		if(vals[4]=='X'&&vals[6]=='X'){
			win=true;
			winnerComp=player;
			matchFound=true;
		}
	}

	if(vals[0]=='X'&&(matchFound==false)){
		if(vals[1]=='X'&&vals[2]=='X'){
			win=true;
			winnerComp=player;
			matchFound=true;
		}else if(vals[4]=='X'&&vals[8]=='X'){
			win=true;
			winnerComp=player;
			matchFound=true;
		}else if(vals[3]=='X'&&vals[6]=='X'){
			win=true;
			winnerComp=player;
			matchFound=true;
		}
	}

	if(vals[8]=='X'&&(matchFound==false)){
		if(vals[5]=='X'&&vals[2]=='X'){
			win=true;
			winnerComp=player;
			matchFound=true;
		}else if(vals[7]=='X'&&vals[6]=='X'){
			win=true;
			winnerComp=player;
			matchFound=true;
		}
	}

	if(vals[4]=='X'&&(matchFound==false)){
		if(vals[1]=='X'&&vals[7]=='X'){
			win=true;
			winnerComp=player;
			matchFound=true;
		}else if(vals[3]=='X'&&vals[5]=='X'){
			win=true;
			winnerComp=player;
			matchFound=true;
		}
	}

	if(vals[2]=='O'&&(matchFound==false)){
		if(vals[4]=='O'&&vals[6]=='O'){
			win=true;
			winnerComp=player2;
			matchFound=true;
		}
	}

	if(vals[0]=='O'&&(matchFound==false)){
		if(vals[1]=='O'&&vals[2]=='O'){
			win=true;
			winnerComp=player2;
			matchFound=true;
		}else if(vals[4]=='O'&&vals[8]=='O'){
			win=true;
			winnerComp=player2;
			matchFound=true;
		}else if(vals[3]=='O'&&vals[6]=='O'){
			win=true;
			winnerComp=player2;
			matchFound=true;
		}
	}

	if(vals[8]=='O'&&(matchFound==false)){
		if(vals[5]=='O'&&vals[2]=='O'){
			win=true;
			winnerComp=player2;
			matchFound=true;
		}else if(vals[7]=='O'&&vals[6]=='O'){
			win=true;
			winnerComp=player2;
			matchFound=true;
		}
	}

	if(vals[4]=='O'&&(matchFound==false)){
		if(vals[1]=='O'&&vals[7]=='O'){
			win=true;
			winnerComp=player2;
			matchFound=true;
		}else if(vals[3]=='O'&&vals[5]=='O'){
			win=true;
			winnerComp=player2;
			matchFound=true;
		}
	}

	return win;
}

void TicTacToe::viewHallOfFame(){
	if(highs[0].getScore()>highs[1].getScore()){
		highs[0].setRank(1);
		highs[1].setRank(2);
	}else if(highs[1].getScore()>highs[0].getScore()){
		highs[0].setRank(2);
		highs[1].setRank(1);
	}else{
		highs[0].setRank(1);
		highs[1].setRank(1);
	}
	cout<<"\t\t\t\tName : Score : Rank\n";
	cout<<"\t\t\t\t"<<highs[0].getName()<<" : "<<highs[0].getScore()<<" : "<<highs[0].getRank()<<endl;
	cout<<"\t\t\t\t"<<highs[1].getName()<<" : "<<highs[1].getScore()<<" : "<<highs[1].getRank()<<endl;
}

string TicTacToe::rishEncrypt(int key, string alphaNum){
	for(int i=0;key>100;i++){//make key less than 100
	            key-=100;
	}
	string charString  = alphaNum;//split and store string in another string
	int len = charString.length();//get length of string(for reversal and encryption)
	for(int i = 0, j = len-1;i<len/2;i++,j--){
		char tmp = charString[i];//reverse string
		charString[i]=charString[j];
		charString[j] = tmp;
		charString[i]+=key;//each char of string incremented by key
		charString[j]+=key+1;
	}
	if(len%2!=0){
		charString[len/2]+=key;//if odd, increases middle element(the one which doesnt take part
							   //in above loop)
	}
	alphaNum = charString;//integrate and save the modified string into original string
	return alphaNum;//return encrypted string
}

string TicTacToe::rishDecrypt(int key, string encryptedString){
    for(int i=0;key>100;i++){//make key less than 100
        key-=100;
    }
    string charString  = encryptedString;//split and store string in another string
    int len = charString.length();//get length of string(for reversal and encryption)
    for(int i = 0, j = len-1;i<len/2;i++,j--){
        char tmp = charString[i];//reverse string
        charString[i]=charString[j];
        charString[j] = tmp;
        charString[i]-=key+1;//each char of string decremented by key
        charString[j]-=key;
    }
    if(len%2!=0){
        charString[len/2]-=key;//if odd, decreases middle element(the one which doesnt take part
                               //in above loop)
    }

    encryptedString = charString;//integrate and save the modified string into original string
    return encryptedString;//return decrypted string
}

int main(){
	TicTacToe *ticTacToe = new TicTacToe;

	delete ticTacToe;
	ticTacToe = 0;

	return 0;
}
