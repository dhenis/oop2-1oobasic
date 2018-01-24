#include <iostream>
#include <termios.h>
#include <random>
#include <string>
#include <fstream>
#include <stdio.h>
#include <sstream>

#include "Arena.h"
#include "Play.h"

#define clear() printf("\033[2J\033[1;1H") //define for clear screen

using namespace std;


static struct termios old, new1; // im using Termios library for reading user input wtihout pressing spacebar

// this input keyboard function is from https://stackoverflow.com/questions/7469139/what-is-equivalent-to-getch-getche-in-linux
// because
// the function of this is to get input keyboard, because i don't use windows,i cannot use getch() from conio.h library,
// so i found this code so useful for me to replace getch() in my unix computer;


/* Initialize new terminal i/o settings */
void initTermios(int echo)
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  new1 = old; /* make new settings same as old settings */
  new1.c_lflag &= ~ICANON; /* disable buffered i/o */
  new1.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &new1); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void)
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo)
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void)
{
  return getch_(0);
}

/* Read 1 character with echo */
char getche(void)
{
  return getch_(1);
}


int main(){

Play bb;

char choice = '0';
int goGame = 1;
int load_game = 0;
int x= 0,y=0;

int turn = 1;


// go to game
while(goGame==1){

clear();

if(choice == '1'){ // newgame

string p1,p2,name; // temporary variable
  // set player name if it is new game
if(load_game ==0){

  cout<<"Insert player 1 nickname (one word only) : ";cin>>p1;

  cout<<endl;

  cout<<"Insert player 2 nickname (one word only): ";cin>>p2;

  cout<<endl<<endl;

}else{ // if load game

  bb.readPlayerName();

  p1 = bb.getPlayerNameOdd();
  p2 = bb.getPlayerNameEven();

cout<<p1<<endl<<p2;
}

  // initiate game

  bb.setTerrain(); //define value
  bb.printTerrain(); // printing to array
  bb.setDistrubion(); // set distrubtion
  bb.setDefaultScore();// set default score
  bb.setPlayerName(p1,p2); // player1 and player 2



  if(load_game ==1){ // only works if player player load game

    bb.readFileScore(); // this fail
    // set Score

    turn = bb.getTurn();


    (turn%2==0)?name = p2:name = p1;//declare player turn

    // welcome message (1st apperance ) for new game
    printf("Game loaded\n \n It is %s' turn \n \n", name.c_str());
    printf("press arrow to move the green cursor, \n (press 's' anytime to save and to leave game) \n");

  }else{

    // welcome message (1st apperance ) for new game
    printf("\n It is %s' turn \n", p1.c_str());
    printf("press arrow to move the green cursor, \n (press 's' anytime to save and to leave game)");


  }

//just check
// //getScore(turn)
// cout<<endl<<endl<<turn<<endl;
//
// cout<<endl<<bb.getScore(1)<<endl;
// cout<<endl<<bb.getScore(2)<<endl;
// cout<<endl<<bb.getScore(3)<<endl;
// cout<<endl<<bb.getScore(4)<<endl;
// cout<<endl<<bb.getScore(5)<<endl;
// cout<<endl<<bb.getScore(6)<<endl;



  while(turn <= 6){

    (turn%2==0)?name = p2:name = p1;//declare player turn

    //clue for player
    string clue = "\n Wind vane (x : "+ to_string(bb.getDistrubtionX()/2)+") (y : "+to_string(-(bb.getDistrubtionY()/2))+") \n";
    // using (-) for y to invert the value

    switch(getch()) { // the real value
            case 'A':

                if(x>=0 and x<=18){

                  x--;

                  if(x<=0){x=0;} // limiter if the cursor out of range

                  bb.setTerrain();

                  // bb.setScore(bb.getTerrainValue(x+bb.getDistrubtionX(),y+bb.getDistrubtionY()),turn); // save score

                  bb.setCursor(x,y);

                  bb.printTerrain();

                }

                  //getDistrubtionx()

                  printf("\n This is %s' turn \n %s", name.c_str(), clue.c_str());

                  //printf("\n Wind vane (x : %i) (y : %i) \n", (bb.getDistrubtionX()/3),(bb.getDistrubtionY()/3));


                  //printf("\n This is %s' turn \n", name.c_str());


            break;

            case 'B':

            if(x>=0 and x<=18){

              x++;
              if(x>=18){x=18;} // limiter if the cursor out of range


              bb.setTerrain();

              // bb.setScore(bb.getTerrainValue(x+bb.getDistrubtionX(),y+bb.getDistrubtionY()),turn); // save score

              bb.setCursor(x,y);

              bb.printTerrain();


            }

              printf("\n This is %s' turn \n %s", name.c_str(), clue.c_str());

                // code for arrow down
            break;

            case 'C':

            if(x>=0 and x<=18){

              y++;

              if(y>=18){y=18;} // limiter if the cursor out of range

              bb.setTerrain();

              // bb.setScore(bb.getTerrainValue(x+bb.getDistrubtionX(),y+bb.getDistrubtionY()),turn); // save score

              bb.setCursor(x,y);

              bb.printTerrain();


            }

              printf("\n This is %s' turn \n %s", name.c_str(), clue.c_str());

                // code for arrow right
            break;

            case 'D':

            if(x>=0 and x<=18){

              y--;

              if(y<=0){y=0;}

              bb.setTerrain();

              // bb.setScore(bb.getTerrainValue(x+bb.getDistrubtionX(),y+bb.getDistrubtionY()),turn); // save score

              bb.setCursor(x,y);

              bb.printTerrain();


            }

              printf("\n This is %s' turn \n %s", name.c_str(), clue.c_str());
              // code for arrow left

            break;


            case ' ': // enter to shoot

            //shoot logic
                bb.setTerrain();
                bb.setScore(bb.getTerrainValue(x+bb.getDistrubtionX(),y+bb.getDistrubtionY()),turn); // save score

                bb.setCursorAfterShoot(x+bb.getDistrubtionX(),y+bb.getDistrubtionY());
                bb.printTerrain();

                printf("\n %s' score is %i  \n \n", name.c_str(),bb.getScore(turn));

                turn ++; // next turn

                bb.setDistrubion(); // set distrubtion

                if(turn<=6){

                  (turn%2==0)?name = p2:name = p1;//declare player turn

                  printf("\n Now is  %s' turn, Press arrow to continue \n", name.c_str());


                }else{
                  //report summary

                  clear();
                  for(int o =1; o<=6; o++){

                    (o%2==0)?name = p2:name = p1;//declare player turn

                    printf("Score turn %i of %s was %i \n",o, name.c_str(),bb.getScore(o));

                    //totalScoreOddPlayer
                    //set new distrubtion oafter


                  }


                  // this is report section

                  cout<<endl<<"Total score of "<<bb.getPlayerNameEven()<<" is "<<bb.totalScoreEvenPlayer()<<endl;

                  cout<<"Total score of "<<bb.getPlayerNameOdd()<<" is "<<bb.totalScoreOddPlayer()<<endl<<endl;

                  int winner_score = (bb.totalScoreEvenPlayer()>bb.totalScoreOddPlayer())?bb.totalScoreEvenPlayer():bb.totalScoreOddPlayer();

                  string winner_player = (bb.totalScoreEvenPlayer()>bb.totalScoreOddPlayer())?bb.getPlayerNameEven():bb.getPlayerNameOdd();

                  cout<<"The Winner is :\e[32m\e[1m "<<winner_player<<"\e[0m"<<" with score "<<winner_score<<endl<<endl;

                  // write to leader board in the end of game
                  bb.updateLeaderBoard(std::to_string(winner_score)+" | "+winner_player);

                }



            break;


            case 's': // press s to save

                // main logic

                //bb.printTerrain();

                clear();
                // saving play

                bb.writeToPlayerNameFile(bb.getPlayerNameOdd(), bb.getPlayerNameEven()); // save player names

                //set score

                bb.writeToScoreFile(); // write scores to file


                turn = 99; // quit iteration

                printf("\n Game saved.  \n \n");

            break;

        }

  }


  goGame ++; // stop the game

}else if(choice == '2'){ // load game


load_game =1;
choice ='1';
goGame =1;  // stop the game


}else if(choice == '3'){ // high score

cout<<"This is high score board"<<endl<<endl;
//deletLeaderBoard
bb.sortingArrayLeaderBoard();
//bb.deletLeaderBoard();

goGame =99;  // stop the game

}else{ // main menu

  cout<<"Welcome to shooting game "<<endl;
  cout<<"press '1' to start a new game "<<endl;
  cout<<"press '2' to load saved game "<<endl;
  cout<<"press '3' to see high score "<<endl<<endl;


  cout<<"Your Choice : ";

  cin>>choice;

  goGame =1; // stop the game

  }

}


//  cout << "\033[2J\033[1;1H"; // clear screen, thanks to https://stackoverflow.com/questions/17335816/clear-screen-using-c

return 0;

 // 27 decimal 0x1B
} // end of main
