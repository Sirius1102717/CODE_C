#include <bits/stdc++.h>
using namespace std;

int board[10][10] = {0};
int tile = 1;

void tileBoard(int topRow,
               int topColumn,
               int defectRow,
               int defectColumn,
               int size)
{
    if (size == 1)
        return;
    int tileToUse = tile++, quadrantSize = size / 2;
    int centerRow = topRow + quadrantSize;
    int centerColumn = topColumn + quadrantSize;

    // leftUp
    if (defectRow < centerRow && defectColumn < centerColumn)
        tileBoard(topRow, topColumn, defectRow, defectColumn, quadrantSize);
    else {
        board[centerRow - 1][centerColumn - 1] = tileToUse;
        tileBoard(topRow, topColumn, centerRow - 1, centerColumn - 1,
                  quadrantSize);
    }

    // rightUp
    if (defectRow < centerRow && defectColumn >= centerColumn)
        tileBoard(topRow, centerColumn, defectRow, defectColumn, quadrantSize);
    else {
        board[centerRow - 1][centerColumn] = tileToUse;
        tileBoard(topRow, centerColumn, centerRow - 1, centerColumn,
                  quadrantSize);
    }

    // rightDown

    if (defectRow >= centerRow && defectColumn >= centerColumn)
        tileBoard(centerRow, centerColumn, defectRow, defectColumn,
                  quadrantSize);
    else {
        board[centerRow][centerColumn] = tileToUse;
        tileBoard(centerRow, centerColumn, centerRow, centerRow, quadrantSize);
    }

    // leftDown

    if (defectRow >= centerRow && defectColumn < centerColumn)
        tileBoard(centerRow, topColumn, defectRow, defectColumn, quadrantSize);
    else {
        board[centerRow][centerColumn - 1] = tileToUse;
        tileBoard(centerRow, topColumn, centerRow, centerColumn - 1,
                  quadrantSize);
    }
}

int main(int argc, char const *argv[])
{
    int topRow = 0;
    int topColunm = 0;
    int defectRow = 0;
    int defectColumn = 1;
    int size = 8;

    tileBoard(topRow, topColunm, defectRow, defectColumn, size);

    int i, j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++)
            printf("%2d ", board[i][j]);
        cout << "\n";
    }

    cout << tile << " "
         << "\n";
    return 0;
}