#include <iostream>
#include <termios.h>
#include <random>
#include <string>
#include <fstream>
#include <stdio.h>
#include <sstream>

#define clear() printf("\033[2J\033[1;1H") //define for

#include "Arena.h"

using namespace std;


void Arena::printTerrain(){ // method to display terrain

    for(int i = 0; i<19; i++){

        for(int j = 0 ; j < 19; j++){

            if(terrain[i][j] >30 ){

              if(terrain[i][j] ==77 ){

                cout<<"\e[32m\e[1m"<<terrain[i][j]<<"\e[0m"<<" "; // makes bold white

              }else if (terrain[i][j] ==88){

                cout<<"\e[35m\e[1m"<<terrain[i][j]<<"\e[0m"<<" "; // makes bold white

              }else{

                cout<<"\e[1m"<<terrain[i][j]<<"\e[0m"<<" "; // makes bold white

              }

            }else{

              cout<<terrain[i][j]<<" ";

            }

        }

        cout<<endl;

    } // end of open terrain

}


void Arena::setDefaultTerrain(){ // set value of array used

      // ------------------------ // make suqare

        // int x = 0;

        for(int i = 0; i<=18; i++){ // main terrain

            for(int j = 0 ; j <= 18; j++){

                (i == 0 or i == 18 or j == 0 or j == 18)?terrain[i][j] = 90:terrain[i][j] = 20; // fill top

            }
        } // end of main terrain


        for(int i = 3; i<=15; i++){ // 2nd square

            for(int j = 3 ; j <= 15; j++){

                (i == 3 or i == 15 or j == 3 or j == 15)?terrain[i][j] = 45:terrain[i][j] = 30; // fill top

            }
        } // end of main terrain


        for(int i = 7; i<=11; i++){ // 3rd square

            for(int j = 7 ; j <= 11; j++){

                (i == 7 or i == 11 or j == 7 or j == 11)?terrain[i][j] = 60:terrain[i][j] = 70; // fill top

            }

        } // end of main terrain

      terrain[9][9] = 99; //centre

      // --------------------------------------------- //

}

                  // from , to , coordinate, base , edge
void Arena::setLeftTopCorner(int a, int b, int c, int d,int e){

    int x =a;
  //  int y =c;
    int fromTemp = a;
    int  toTemp = b;

    for(int i = toTemp ; i >= fromTemp; i--){ // row // anchor
     int y=fromTemp;
       for(int j = fromTemp ; j <=i; j++){ // collumn

         terrain[x][y] = e ;

         y++;
       }
       x++;

    } // fix left top

    x  = a;

    toTemp = b - 1;

    for(int i = toTemp ; i >= fromTemp; i--){ // row // anchor
     int y=fromTemp;
       for(int j = fromTemp ; j <=i; j++){ // collumn
       terrain[x][y] = d;
         y++;
       }
       x++;


    } // fix left top square 2
    x =c;
}

                  //   from , to ,  cordiate,  base , edge
void Arena::setRightTopCorner(int a, int b, int c, int d, int e){

  int x =a;
  int fromTemp = a;
  int  toTemp = b;

  // RIHT CORNER FIX head//

  x= 0;

  for(int i = toTemp ; i >= fromTemp +1; i--){ // row // anchor
    int y = c ;
      for(int j = fromTemp ; j <=i; j++){ // collumn

        terrain[y][i] = e;

        y++;

      }
      x++;
  }


  x= 0;

  for(int i = toTemp ; i >= fromTemp +1 ; i--){ // row // anchor
    int y = c ;
      for(int j = fromTemp +1; j <=i; j++){ // collumn

        terrain[y][i] = d;

        y++;
      }
      x++;
  }

  // RIHT CORNER FIX head// square 2

}

                  //   from , to ,  cordiate,  base , edge
void Arena::setBottomLeftCorner(int a, int b, int c, int d , int e){

  // LEFT BOTTOM FIX HEAD

    int x =a;
    int fromTemp = a;
    int  toTemp = b;

    for(int i = fromTemp, ex=c ; i <= toTemp ; i++,ex++ ){ // row // anchor


      for(int j = c, y=fromTemp ; j <=ex; j++){ // collumn


        terrain[i][j] = e;

        y++;
      }
      x++;
    }


    x= 0;

    for(int i = fromTemp+1, ex=c ; i <= toTemp ; i++,ex++ ){ // row // anchor


      for(int j = c, y=fromTemp+1 ; j <=ex; j++){ // collumn


        terrain[i][j] = d;

        y++;

      }

      x++;

    }

    // LEFT BOTTOM TAIL

}

void Arena::setBottomRightCorner(int a, int b, int c, int d , int e){

    int fromTemp = a;
    int  toTemp = b;

  // RIGHT BOTTOM head
    int x= c;

    for(int i = fromTemp; i <= toTemp ; i++){ // row // anchor


        for(int j = fromTemp, y=toTemp ; j <=i ; j++){ // collumn


          terrain[y][i] = e;

          y--;

        }

      x--;

    }

    x= c;

    for(int i = fromTemp+1; i <= toTemp ; i++){ // row // anchor


        for(int j = fromTemp+1, y=toTemp ; j <=i ; j++){ // collumn


          terrain[y][i] = d;

            y--;

        }

      x--;

    }

}


void Arena::setSquare(int nodex,int nodey,int value){
    terrain[nodex][nodey] = value;
    terrain[nodex+4][nodey] = value;
    terrain[nodex][nodey+4] = value;
    terrain[nodex+4][nodey+4] = value;
}

void Arena::setZero(){
  terrain[3][3] = 0;

}

void Arena::setTerrain(){ // set main value of terrain

  clear();

  //#set default terrain
  setDefaultTerrain(); // only square

  // set value by edge
  setLeftTopCorner(0,5,0,10,90);
  setLeftTopCorner(3,6,0,20,45);

  setRightTopCorner(13,18,0,10,90);
  setRightTopCorner(12,15,3,20,45);

  setBottomLeftCorner(13,18,0,10,90);
  setBottomLeftCorner(12,15,3,20,45);

  setBottomRightCorner(13,18,18,10,90);
  setBottomRightCorner(12,15,15,20,45);

  setSquare(7,7,30);

}
//setCursorAfterShoot

void Arena::setCursor(int inX , int inY){

  terrain[inX][inY] = 77;

} // end of  set cursor

void Arena::setCursorAfterShoot(int inX , int inY){

  terrain[inX][inY] = 88;

} // end of  set cursor

int Arena::getTerrainValue(int inX , int inY){

    return terrain[inX][inY];

} // end of  set cursor
