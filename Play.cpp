#include <iostream>
#include <termios.h>
#include <random>
#include <string>
#include <fstream>
#include <stdio.h>
#include <sstream>

#define clear() printf("\033[2J\033[1;1H") //define for

#include "Play.h"

using namespace std;

int Play::randomNumber() { // random number 1 -10
    random_device num;

    // default_random_engine ran(time(0));
    default_random_engine ran(num());
    uniform_int_distribution<int> rdm(-6, 6);

    int a ;
    a =  rdm(ran);
    return a;
}

int Play::getDistrubtionX(){

    return  distrubtionx;

}

int Play::getDistrubtionY(){

    return distrubtiony;

}
void Play::setDistrubtionX(int a){

    distrubtionx = a;

}

void Play::setDistrubtionY(int a){

    distrubtiony = a;

}
//distrubtiony
void Play::setDistrubion(){

  distrubtionx = randomNumber();

  distrubtiony = randomNumber();

}

void Play::setPlayerName(string player_odd, string player_even){

  p1 = player_odd;

  p2 = player_even;

}

string Play::getPlayerNameEven(){

  return p2;

}

string Play::getPlayerNameOdd(){

  return p1;

}

void Play::setDefaultScore(){


  for(int o =0; o<=6; o++){

      score[o] = -1;  // score default becomes 1

  }

}

void Play::setScore(int val, int h){

  score[h] = val;

}

int Play::totalScoreEvenPlayer(){
  int scr=0;
  for(int o =1; o<=6; o++){

       (o%2==0)?  scr += getScore(o) :0;//declare player turn

  }

  return scr;
}

int Play::getScore(int x){

  return  score[x];

}

int Play::totalScoreOddPlayer(){
  int scr=0;
  for(int o =1; o<=6; o++){

       (o%2!=0)?  scr += getScore(o) :0;//declare player turn

  }

  return scr;
}

void Play::writeToScoreFile(){
  string inputFile = "file_sys/score.txt";
  //string myStr = a;
  ofstream myStream(inputFile);
  if(myStream.is_open()){

    // int scr=0;
    for(int o =1; o<=6; o++){

         myStream << getScore(o)<<endl;

      }

    }

  myStream.close();
}

void Play::updateLeaderBoard(string a){ // format is updateLeaderBoard(std::to_string(winner_score)+" | "+winner_player);

  string ipt = "file_sys/leader_board.txt";

  string txt = a;

  ofstream myStream(ipt, ios::app);
  if (myStream.is_open())
  myStream << "\n" << txt;

  myStream.close();

}

  void Play::deletLeaderBoard(){

    string ipt = "file_sys/leader_board.txt";
    //string myStr = a;
    ofstream myStream(ipt);
    if(myStream.is_open()){

      myStream <<"";

      }

    myStream.close();

  }

void Play::writeToPlayerNameFile(string p1, string p2){

  string ipt = "file_sys/player_name.txt";
  //string myStr = a;
  ofstream myStream(ipt);
  if(myStream.is_open()){

    myStream <<p1<<"\n"<<p2;

    }

  myStream.close();

}

  void Play::readFileScore(){
    string ipt = "file_sys/score.txt";
    string line;
    int rowInt, i =1;

    ifstream myStream(ipt);
    if(myStream.is_open()){

      while(getline(myStream,line)){

        rowInt = stoi(line);

        if(rowInt != -1){

        //  cout << rowInt << endl;

          setScore(rowInt,i);

          i++;

        }
      }
    }
  }


  void Play::sortingArrayLeaderBoard(){

    string ipt = "file_sys/leader_board.txt";

    string array[2];
    string string_array[90][2];
    int fstElement[90];
    string sorted_array[90][2];
    string lines;
    // int tmp;

    ifstream myStream(ipt);


    //extracting

    if(myStream.is_open()) {

      // vector<Names> aa;
      int ii = 0;
      while(getline(myStream,lines)){
        if(!lines.empty()){

          string foo = lines;
          std::stringstream ss(foo);
          string st;

          ss >> array[0] >> st >> array[1] >> st;
        //  cout<<ii<<" "<< array[1] <<" ==> "<< array[0]<<endl;

          fstElement[ii] = stoi(array[0]);


          string_array[ii][0] = array[0];
          string_array[ii][1] = array[1];

          ii++;
        }
      }

      //cout<<ii;
      //deletLeaderBoard()
      // cout<<endl<<endl<<string_array[0][0]<<" -- > "<<string_array[0][1]<<endl;
      // cout<<endl<<endl<<string_array[1][0]<<" -- > "<<string_array[1][1]<<endl;
      // cout<<endl<<endl<<string_array[2][0]<<" -- > "<<string_array[2][1]<<endl;
      // cout<<endl<<endl<<string_array[3][0]<<" -- > "<<string_array[3][1]<<endl;
      //cout<<string_array[1][0]<<endl;
      //cout<<endl<<"after sorting: "<<endl;

      // #empty txt

      deletLeaderBoard();
      // #sorting algorithm

      int temp;
      string temp2,temp3;

      for(int i=0; i<=ii-1; i++)
       {
           for(int j=i+1; j<=ii-1; j++)
               {
                   if(fstElement[i]<fstElement[j])
                       {

                           temp=fstElement[j]; //
                           temp2 = string_array[j][0];
                           temp3 = string_array[j][1];

                           fstElement[j]=fstElement[i];//
                           string_array[j][0] = string_array[i][0];
                           string_array[j][1] = string_array[i][1];


                           fstElement[i]=temp;//
                           string_array[i][0] = temp2;
                           string_array[i][1] = temp3;
                           //output sorting

                       }
               }
        //  cout << string_array[i][0]<<" ==> "<<string_array[i][1] << "\n"; //write to leaderboard

          // only save the best 20;
          if(i <=19){
            cout <<i+1 <<" : "<< string_array[i][1]<<" ==> "<<string_array[i][0] << "\n"; //write to leaderboard

            updateLeaderBoard(string_array[i][0]+" | "+string_array[i][1]);
          }

       }

      // i++;

    } // open connection

    myStream.close();

  }

  void Play::readFileLeaderBoard(){

    string ipt = "file_sys/leader_board.txt";

    // int a,b;
    string array[2];

    string lines;
    int i=1;

    ifstream myStream(ipt);


    //extracting

    if(myStream.is_open()) {

      while(getline(myStream,lines)){

        string foo = lines;
        std::stringstream ss(foo);
        string st;

        ss >> array[0] >> st >> array[1] >> st;
        cout<<i<<" "<< array[1] <<" ==> "<< array[0]<<endl;


        i++;

      }

    } // open connection

    myStream.close();

  }

  void Play::readPlayerName(){ // for load game
    int i=1;
    string ipt = "file_sys/player_name.txt";
    string row;
    
    ifstream myStream(ipt);
    if(myStream.is_open()){

      string name [3]; // safe player name to this

      while(getline(myStream,row)){ // get lines

          name[i] = row;

          i++;

        }

        setPlayerName(name[1], name[2]);

      }

    myStream.close();

  }

int Play::getTurn(){ // get turn and set score

  int turn=1; //set default turn
  for(int oo = 1;oo<=6;oo++){

    if(getScore(oo)!=-1){

      turn++; // only count if value >= 0

    }
  }

  return turn;

}
//   string inputFile = "test.txt";
// string line;
// ifstream myStream(inputFile);
// if(myStream.is_open()){
// while(getline(myStream,line))
// cout << line << endl;
// }
