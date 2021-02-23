#include <math.h>
#include <stdio.h>
void TileBoard(int tr, int tc, int dr, int dc, int size);
void OutputBoard(int size);

int tile = 1;
int Board[1025][1025];
int main( )
{
    int n, a, b;
    scanf("%d", &n);  //输入2的幂次
    int sum;
    sum = pow(2, n);
    scanf("%d %d", &a, &b);
    Board[sum - a - 1][b - 1] = 0;
    TileBoard(0, 0, a - 1, b - 1, sum);
    OutputBoard(sum);
    return 0;
}

void TileBoard(int tr, int tc, int dr, int dc, int size)
{  //覆盖残缺棋盘
    if (size == 1)
        return;
    int t = tile++,    //所使用的三格板的数目
        s = size / 2;  //象限大小
    //覆盖左上象限
    if (dr < tr + s && dc < tc + s)  //残缺方格位于本象限
        TileBoard(tr, tc, dr, dc, s);
    else {  //本象限中没有残缺方格, 把三格板t放在右下角
        Board[tr + s - 1][tc + s - 1] = t;
        //覆盖其余部分
        TileBoard(tr, tc, tr + s - 1, tc + s - 1, s);
    }
    //覆盖右上象限
    if (dr < tr + s && dc >= tc + s)  //残缺方格位于本象限
        TileBoard(tr, tc + s, dr, dc, s);
    else {  //本象限中没有残缺方格, 把三格板t放在左下角
        Board[tr + s - 1][tc + s] = t;
        //覆盖其余部分
        TileBoard(tr, tc + s, tr + s - 1, tc + s, s);
    }
    //覆盖左下象限
    if (dr >= tr + s && dc < tc + s)  //残缺方格位于本象限
        TileBoard(tr + s, tc, dr, dc, s);
    else {  //把三格板t放在右上角
        Board[tr + s][tc + s - 1] = t;
        //覆盖其余部分
        TileBoard(tr + s, tc, tr + s, tc + s - 1, s);
    }
    //覆盖右下象限
    if (dr >= tr + s && dc >= tc + s)  //残缺方格位于本象限
        TileBoard(tr + s, tc + s, dr, dc, s);
    else {  //把三格板t放在左上角
        Board[tr + s][tc + s] = t;
        //覆盖其余部分
        TileBoard(tr + s, tc + s, tr + s, tc + s, s);
    }
}
void OutputBoard(int size)
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            printf("%-3d", Board[i][j]);
        printf("\n");
    }
}