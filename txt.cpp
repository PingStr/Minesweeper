#include <random>
#include <iostream>
#include <time.h>
using namespace std;

int a[100][100], n;
char b[100][100];
int mat[100][100];
int di[] = {1, 0, 0, -1, 1, 1, -1, -1}, dj[] = {0, 1, -1, 0, 1, -1, 1, -1};
int cnt = 5;
int k = 0;

/*
    8 - spatiu gol;
    6 - bomba;
*/
void afis2()
{
    cout<<"Nr Bombe: "<<cnt<<"\t"<<"Marcate: "<<k<<"\n\n";
    cout<<" ";
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == 0 && j == 0)
                cout<<" |";
            else if(i == 0 && j > 9)
                cout<<j<<"|";
            else if(j == 0 && i > 9)
                cout<<i<<"|";
            else
                cout<<b[i][j]<<" |";
        }
        cout<<"\n";
    }
}
void afis3()
{
    cout<<"Nr Bombe: "<<cnt<<"\t"<<"Marcate: "<<k<<"\n\n";
    cout<<" ";
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if(a[i][j] == 6)
                cout<<"*"<<" |";
            else
            {
                if (i == 0 && j == 0)
                cout<<" |";
                else if(i == 0 && j > 9)
                    cout<<j<<"|";
                else if(j == 0 && i > 9)
                    cout<<i<<"|";
                else
                    cout<<b[i][j]<<" |";
            }
        }
        cout<<"\n";
    }
}

void ran(int cnt)
{
    int x, y;
    srand(time(NULL));
    for (int i = 1; i <= cnt; i++)
    {
        x = rand() % n + 1;
        y = rand() % n + 1;
        if (a[x][y] == 6)
        {
            while(a[x][y] == 6)
            {
                x = rand() % n + 1;
                y = rand() % n + 1;
            }
            a[x][y] = 6;
        }
        else
        {
            a[x][y] = 6;
        }
    }
}

bool inmat(int i, int j)
{
    return i > 0 && j > 0 && i <= n && j <= n;
}

void inBomb()
{
    int c;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            c = 0;
            if (a[i][j] == 0)
            {
                for (int k = 0; k < 8; k++)
                {
                    if ((a[i + di[k]][j + dj[k]] == 6) && inmat(i + di[k], j + dj[k]))
                        c++;
                    a[i][j] = c;
                }
            }
        }
    }
}

void fill(int i, int j)
{
    if (a[i][j] == 0)
    {
        for (int k = 0; k < 8; k++)
        {
            a[i][j] = 8;
            if (a[i + di[k]][j + dj[k]] == 0 && inmat(i + di[k], j + dj[k]) && a[i + di[k]][j + dj[k]] != 8)
            {
                fill(i + di[k], j + dj[k]);
            }
        }
    }
}

void contur()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if(a[i][j] == 8)
                b[i][j] = '0';
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            for (int k = 0; k < 8; k++)
                if (a[i][j] != 8 && a[i][j] != 6 && (a[i + di[k]][j + dj[k]] == 8))
                    b[i][j] = '0' + a[i][j];
        }
    }
}

void check_bombs(bool &chh)
{
    int g = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if ((mat[i][j] == 1) && (a[i][j] == 6))
                g++;
        }
    }
    if (g == cnt)
    {
        chh = 1;
    }
}

bool game(int i, int j, int c, bool &chh)
{
    if (c == 1)
    {
        if (a[i][j] == 6)
        {
            chh = 0;
            return 0;
        }
        else
        {
            if (a[i][j] == 0 || a[i][j] == 8)
            {
                fill(i, j);
                contur();
            }
            else
            {
                b[i][j] = '0' + a[i][j];
            }
        }
    }
    else if (c == 2)
    {
        b[i][j] = 'b';
        mat[i][j] = 1;
        ++k;
        if (k == cnt)
            check_bombs(chh);
        if (chh == 1)
        {
            return 0;
        }
    }
    else if (c == 3)
    {
        mat[i][j] = 0;
        --k;
        b[i][j] = '_';
    }
    return 1;
}

void citire(int &i, int &j, int &c)
{
    cout<<"i - rand"<<'\t'<<"j - coloana"<<'\n';
    cout<<"(o = 1 - click)"<<"   "<<"(o = 2 - marcare)"<<"   "<<"(o = 3 - undo)"<<"   "<<"(o = 4 - inca odata)"<<"\n";
    cout<<"i = ";
    cin>>i;
    cout<<"j = ";
    cin>>j;
    cout<<"o = ";
    cin>>c;
}
void citirein()
{
    cout<<"Introduceti numarul de bombe: ";
    cin>>cnt;
    cout<<"Introduceti dimensiunea campului de joc: ";
    cin>>n;
    system("cls");
}

int main()
{
    citirein();
    for (int i = 1; i <= n; i++)
    {
        b[0][i] = '0' + i;
        b[i][0] = '0' + i;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            b[i][j] = '_';
        }
    }
    ran(cnt);
    inBomb();
    int i, j, c;
    bool check = 0;

    int k = 0;
    while (game(i, j, c, check))
    {
        afis2();
        citire(i, j, c);
        system("cls");
    }
    if (check)
    {
        system("cls");
        afis3();
        cout<<"FELICITARI";
    }
    else
    {
        system("cls");
        afis3();
        cout<<"GAME OVER\n";
        cin>>n;
    }
    return 0;
}
