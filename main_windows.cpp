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

void afis()
{
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            cout<<a[i][j]<<" ";
        }
        cout<<"\n";
    }
}

void afis2()
{
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            cout<<b[i][j]<<" ";
        }
        cout<<"\n";
    }
}

void ran(int dif)
{
    int x, y;
    int g = 0;
    srand(time(NULL));
    for (int i = 1; i <= dif; i++)
    {
        g = 0;
        x = rand() % n + 1;
        y = rand() % n + 1;
        if (a[x][y] == 1)
        {
            while(a[x][y] == 1)
            {
                x = rand() % n + 1;
                y = rand() % n + 1;
            }
            a[x][y] = 6;
            g = 1;
        }
        if (g == 0)
        {
            a[x][y] = 6;
        }
    }
}

bool inmat(int i, int j)
{
    return i > 0 && j > 0 && i <= n && j <= n;
}

void bagabom()
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
        for (int k = 0; k < 4; k++)
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

bool game(int i, int j, int c, bool &chh, int &k)
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

int main()
{
    n = 9;
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
    bagabom();
    int i, j, c;
    bool check = 0;
    /*afis2();
    citire(i, j, c);
    system("cls");
    cout<<" ";*/
    int k = 0;
    while (game(i, j, c, check, k))
    {
        afis2();
        citire(i, j, c);
        system("cls");
        cout<<" ";
    }
    if (check)
    {
        system("cls");
        cout<<"\n";
        afis();
        cout<<"CONGRAJULASIUOBS";
    }
    else
    {
        system("cls");
        afis();
        cout<<"\n";
        cout<<"GAMe OVER";
    }
    return 0;
}
