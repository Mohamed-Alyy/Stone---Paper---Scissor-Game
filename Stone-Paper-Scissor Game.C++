//
//  main.cpp
//  Stone-Stone-Scissor
//
//  Created by Mohamed Ali on 10/12/2023.
//

#include <iostream>
#include <string>
#include <cstdlib> // for generate random numbers
#include <vector>

using namespace std;

struct GameInfo
{
short player = 0;
short computer = 0;
short draw = 0;
short totalRound = 0;
short roundNumer = 0;
};

GameInfo gameinfo;
    
enum enGameChoise {Paper = 1 , Stone = 2 , Scissor = 3};

enum enWinner {Player  , Computer  , Draw  };

void roundCount(){
    int roundCount;
    cout<< "Enter the number of round you want to play ?" << "\n";
    cin >> roundCount;
    gameinfo.totalRound = roundCount;
}

void roundPlus() {
    gameinfo.roundNumer +=1;
    cout << "--------------- Round : [" << gameinfo.roundNumer << "] begin ---------------\n\n";
}

string resultMsg(int winner){
    string whoWinner [3] = {"Player won!","Compter won!","No Winner [Draw!]"};
    return winner == 1 ? whoWinner[0] : winner == 2 ? whoWinner[1] : whoWinner[2] ;
}

string showPlayesChoise(enGameChoise choise){
    switch(choise){
        case 1: return "Paper"; break;
        case 2: return "Stone"; break;
        case 3: return "Scissor"; break;
    }
}

string printRoundResult(enWinner winer){
    switch (winer) {
        case Player: return resultMsg(1); break;
        case Computer: return resultMsg(2); break;
        case Draw: return resultMsg(3); break;
    }
}

string printFinalResult(GameInfo gameInfo){
     cout << "\n||-------------------- *** G a m e  O v e r *** ---------------------||\n\n";
    cout << "||------------------------- Game Result ---------------------------||\n\n";
    cout<< "                      Round Counts     :[" << gameInfo.totalRound << "]\n";
    cout<< "                      Draw Score       :[" << gameInfo.draw << "]\n";
    cout<< "                      Player Score     :[" << gameInfo.player << "]\n";
    cout<< "                      Computer Score   :[" << gameInfo.computer << "]\n";
    if(gameinfo.player > gameinfo.computer)
    cout<< "                     The Winner is     :[Player] \n";
    else if (gameInfo.computer > gameInfo.player)
    cout<< "                     The Winner is     :[Computer]\n";
    else cout<< "                The Winner is     : No Winner\n";
    return gameInfo.player > gameInfo.computer ? resultMsg(1): gameInfo.computer > gameInfo.player ? resultMsg(2) : resultMsg(3);
}

enGameChoise player1Choice(){
    short choice;
    cout<< "Pleas Type [1] for Paper , [2]  for Stone , [3] for Scissor :";
    cin >> choice;
    return choice == 1 ? Paper : choice == 2 ? Stone : Scissor;
    
}

enGameChoise randomChoise (){
    int random = rand() % (3-1+1) + 1;
    return random == 1 ? Paper : random == 2 ? Stone : Scissor;
}

int computerChoice() {return randomChoise();}

enWinner gameResult(enGameChoise player , enGameChoise computer){
    enWinner winnerPlayer ;
    
    if (player == computer) winnerPlayer = Draw;
    
    if (player == Paper){
        if (computer == Stone) winnerPlayer = Player;
        if (computer == Scissor) winnerPlayer = Computer;
    }
    if (player == :: Stone){
        if (computer == :: Scissor) winnerPlayer = Player;
        if (computer == :: Paper) winnerPlayer = Computer;
    }
    
    if (player == :: Scissor){
        if (computer == :: Paper) winnerPlayer = Player;
        if (computer == :: Stone) winnerPlayer = Computer;
    }
  
    return winnerPlayer;
}

void pointCounter (enWinner winner){
    switch (winner){
        case Player:gameinfo.player ++; break;
        case Computer: gameinfo.computer ++ ; break;
        case Draw: gameinfo.draw ++ ; break;
    }
}

void resetCounters(){
    gameinfo.player = 0;
    gameinfo.computer = 0;
    gameinfo.draw = 0;
    gameinfo.totalRound = 0;
    gameinfo.roundNumer = 0;
}


void setScreenColor(enWinner winner){
    switch(winner){
        case Player:
          cout<< "\x1b[32m"; // Green Color
            break;
        case Computer:
        cout<< "\x1b[31m"; // Red Color
            cout<<"\a";
            break;
        case Draw:
       cout<< "\x1b[33m"; // Yellow Color
            break;
    }
}

void resetScreen(){
     cout<< "\x1b[0m"; // reset all color attributes back to normal
    system("clear");  // clear terminal
    
}

void resetGame (){
    cout<< "\x1b[0m"; // reset all color attributes back to normal
    int userAnswer;
    cout<< "do you want to play agine [1] Yes , [Any Key] No : ";
    cin >> userAnswer;
    if (userAnswer == 1) {
        resetCounters();
        roundCount();
        resetScreen();
        cout<<"\n---------------- Now You Can Play Again ----------------\n" << endl;
    }else{
        resetCounters();
        resetScreen();
        cout<<"----------------------||| Game Ended |||----------------------" << endl;
    }
  
}


void startGame(){
roundCount();
  do {
    roundPlus();
    enGameChoise p1 = player1Choice();
    enGameChoise comp = randomChoise();
    enWinner winner = gameResult(p1, comp);
    
    cout<< "\nPlayer choose : [" << showPlayesChoise(p1) << "]\n";
    cout << "Computer choose : ["<< showPlayesChoise(comp) << "] \n";
    cout << "\nRound Winner : " << printRoundResult(winner) << "\n\n";
    
    pointCounter(winner);
      setScreenColor(winner);
    
    if (gameinfo.roundNumer == gameinfo.totalRound)
    {
        printFinalResult(gameinfo);
        resetGame();
    }
  } while(gameinfo.roundNumer < gameinfo.totalRound);
}


int main() {
    srand((unsigned)time(NULL));
    startGame();
    return 0;
}


/*

===== Change color in OS X console output =====

To set only the foreground color:

 "\x1b[30m"

To set only the background color:

 "\x1b[40m"

To set foreground and background color:

 "\x1b[30;40m"

To reset all color attributes back to normal:

 "\x1b[0m"

In the above strings the numbers 30 and 40 are just placeholders for foreground and background color codes,
 they can be replaced by the numbers from the table below to get one of 8 standard colors:

+---------+------------+------------+
|  color  | foreground | background |
|         |    code    |    code    |
+---------+------------+------------+
| black   |     30     |     40     |
| red     |     31     |     41     |
| green   |     32     |     42     |
| yellow  |     33     |     43     |
| blue    |     34     |     44     |
| magenta |     35     |     45     |
| cyan    |     36     |     46     |
| white   |     37     |     47     |
+---------+------------+------------+
*/
