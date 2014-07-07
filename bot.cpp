#include "2048.h"
#include "2048.cpp"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>

using namespace std;

void play(int n);
int addgrid(Grid a)
{
    int sum = 0;
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            sum += a(i,j);
    return sum;
}

bool lisfull(Grid a)
{
    for(int i=0;i<4;i++)
        if(a[i * 4] == 0) return false;
    return true;
}

int detect_rb_lu(Grid a)
{
    int tmp = 0;
    if(a[1] == a[4]  && a[1] > 0) tmp++;
    if(a[2] == a[5] && a[2] > 0) tmp++;
    if(a[3] == a[6] && a[3] > 0) tmp++;
    if(a[5] == a[8] && a[5] > 0) tmp++;
    if(a[6] == a[9] && a[6] > 0) tmp++;
    if(a[7] == a[10] && a[7] > 0) tmp++;
    if(a[9] == a[12] && a[9] > 0) tmp++;
    if(a[10] == a[13] && a[10] > 0) tmp++;
    if(a[11] == a[14] && a[11] > 0) tmp++;
    return tmp;
}

int detect_ru_lb(Grid a)
{
    int tmp = 0;
    if(a[0] == a[5] && a[0] > 0) tmp++;
    if(a[1] == a[6] && a[1] > 0) tmp++;
    if(a[2] == a[7] && a[2] > 0) tmp++;
    if(a[4] == a[9] && a[4] > 0) tmp++;
    if(a[5] == a[10] && a[5] > 0) tmp++;
    if(a[6] == a[11] && a[6] > 0) tmp++;
    if(a[8] == a[13] && a[8] > 0) tmp++;
    if(a[9] == a[14] && a[9] > 0) tmp++;
    if(a[10] == a[15] && a[10] > 0) tmp++;
    return tmp;
}

int main()
{
    play(1);
    return 0;
}

void play(int n)
{
    Grid grid;
    Game game;
    bool gameover = false;
    int past = 0 ,current = 0;
    dir_e dir;
    int state = 0;
    for(int r=0;r<n;r++)
    {
        game.reset();
        while(!game.isGameOver())
        {
            game.getCurrentGrid(grid);
            if(lisfull(grid))
            {
                if(grid[0] == grid[4] || grid[4] == grid[8] || grid[8] == grid[12]) game.insertDirection(UP);
                else if(detect_rb_lu(grid)>0) game.insertDirection(DOWN);
                else if(detect_ru_lb(grid)>0) game.insertDirection(UP);
                cout<<detect_rb_lu(grid)<<" "<<detect_ru_lb(grid)<<endl;
            }
            state = 0;
            game.insertDirection(LEFT);
            game.getCurrentGrid(grid);
            current = addgrid(grid);
            while(past == current){
                if(state == 0) dir = UP;
                else if(state == 1) dir = DOWN;
                else dir = RIGHT;
                state++;
                game.insertDirection(dir);
                game.getCurrentGrid(grid);
                current = addgrid(grid);
            }
            past = current;
            for(int i=0;i<4;i++)
            {
                for(int j=0;j<4;j++)
                    cout<<setw(4)<<grid(i,j)<<" ";
                cout<<endl;
            }
            system("pause");
            cout<<"====================================="<<endl;
            cout<<"score: "<<game.getScore()<<endl;
            cout<<"Max score: "<<game.getMaxScore()<<endl;
            cout<<"====================================="<<endl;
            //system("pause");
        }
    }
}
