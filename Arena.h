#ifndef ARENA_H
#define	ARENA_H

class Arena {
public:

    void printTerrain();
    void setDefaultTerrain();
    void setLeftTopCorner(int a, int b, int c, int d,int e);
    void setRightTopCorner(int a, int b, int c, int d, int e);
    void setBottomLeftCorner(int a, int b, int c, int d , int e);
    void setBottomRightCorner(int a, int b, int c, int d , int e);
    void setSquare(int nodex,int nodey,int value);
    void setZero();
    void setTerrain();
    void setCursor(int inX , int inY);
    void setCursorAfterShoot(int inX , int inY);
    int getTerrainValue(int inX , int inY);

    // Board2D(int numOfRows, int numOfCols);
    // Board2D(Board2D& orig);
    // virtual ~Board2D();
    // void setValueAtIndex(int row, int col, int val);
    // int getValueAtIndex(int row, int col);
    // virtual void printToScreen();
    // int getNumOfRows();
    // int getNumOfCols();
private:
    int numOfRows, numOfCols;
    int** arr;
    int** createArray();

private:

  int terrain[19][19];


};
#endif
