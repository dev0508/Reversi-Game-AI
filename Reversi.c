#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
void printboard(int size, char re[][26]);
bool check_LegalIn_Direction(int n, int row, int col, char colour, char board[][26], int *p);
int changeDirection(int n, int row, int col, char colour, char board[][26]);
void main()
{
    int dim, i, j, ch = 2, r = 0, max = 0, f1 = 0, f2 = 0, ch1 = 1, ch2, ch3, wc = 0, bc = 0, uc = 0, p, k;
    bool check;
    char a, b, c, cm;
    printf("Enter the board dimension: ");
    scanf("%d", &dim);
    char arr[dim][dim];
    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j++)
        {
            arr[i][j] = 'U';
        }
    }
    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j++)
        {
            if (i == j && i > 0 && j > 0 && i < (dim - 1) && j < (dim - 1) && ((i == (dim - 1) / 2) || (i == (dim - 1) / 2 + 1)))
                arr[i][j] = 'W';
            if (((i + j) == (dim - 1)) && i > 0 && j > 0 && i < dim && j < dim && ((j == (dim - 1) / 2) || (j == (dim - 1) / 2 + 1)))
                arr[i][j] = 'B';
        }
    }
    //dim=8;
    //char arr[8][8]={{'W','U','U','U','U','U','U','U'},{'B','W','W','U','U','U','U','U'},{'B','B','U','B','U','U','U','U'},{'U','B','U','U','U','U','U','U'},{'U','U','U','U','U','U','U','U'},{'U','U','U','U','U','U','U','U'},{'U','U','U','U','U','U','U','U'},{'U','U','U','U','U','U','U','U'}};
    printf("Computer plays (B/W): ");
    getchar();
    scanf("%c", &cm);
    printboard(dim, arr);
    if (cm == 'W')
    {
        while (true)
        {
            uc = bc = wc = 0;
            for (i = 0; i < dim; i++)
            {
                for (j = 0; j < dim; j++)
                {
                    if (arr[i][j] == 'U')
                        uc++;
                    if (arr[i][j] == 'B')
                        bc++;
                    if (arr[i][j] == 'W')
                        wc++;
                }
            }
            if (uc != 0)
            {
                if (ch % 2 == 0)
                {
                    ch2 = 0;
                    for (i = 0; i < dim; i++)
                    {
                        for (j = 0; j < dim; j++)
                        {
                            if (arr[i][j] == 'U')
                            {
                                check = check_LegalIn_Direction(dim, i, j, 'B', arr, &r);
                                if (check == true)
                                {
                                    ch2++;
                                    break;
                                }
                            }
                        }
                        if (ch2 != 0)
                            break;
                    }
                    if (ch2 != 0)
                    {
                        printf("Enter move for colour B (RowCol): ");
                        scanf(" %c %c", &a, &b);
                        r = 0;
                        if (check_LegalIn_Direction(dim, (int)a - 97, (int)b - 97, 'B', arr, &r) == true)
                        {
                            int con = changeDirection(dim, (int)a - 97, (int)b - 97, 'B', arr);
                            printboard(dim, arr);
                        }
                        else
                        {
                            printf("Invalid move.\n");
                            printf("W player wins.\n");
                            break;
                        }
                    }
                    else
                    {
                        printf("B player has no valid move.\n");
                    }
                }
                else
                {
                    f1 = 0;
                    f2 = 0;
                    ch3 = 0;
                    max = 0;
                    int numi1, numi2, numi3, numi4, numj1, numj2, numj3, numj4;
                    bool check;
                    int count[26];
                    for (i = 0; i < dim; i++)
                    {
                        for (j = 0; j < dim; j++)
                        {
                            if (arr[i][j] == 'U')
                            {
                                r = 0;
                                check = check_LegalIn_Direction(dim, i, j, 'W', arr, &r);
                                if (check == true)
                                {
                                    count[ch3] = (i * 10) + j;
                                    ch3++;
                                }
                            }
                        }
                    }
                    if (ch3 != 0)
                    {
                        int temp;
                        for (i = 0; i < ch3; i++)
                        {
                            numi1 = (count[i]) / 10;
                            numj1 = (count[i]) % 10;
                            numi2 = (dim - 1) - numi1;
                            numj2 = (dim - 1) - numj1;
                            for (j = i+1; j < ch3; j++)
                            {
                                numi3 = (count[j]) / 10;
                                numi4 = (dim - 1) - (count[j]) / 10;
                                numj3 = (count[j]) % 10;
                                numj4 = (dim - 1) - ((count[j]) % 10);
                                if ((numi3 == 0 && numj3 == 0) || (numi3 == (dim - 1) && numj3 == (dim - 1)) || (numi3 == 0 && numj4 == 0) || (numi4 == 0 && numj3 == 0))
                                {
                                    temp = count[j];
                                    count[j] = count[i];
                                    count[i] = temp;
                                }
                                else if (numi1 < numi2)
                                {
                                    if (numi1 > numi3)
                                    {
                                        if (numj1 < numj2)
                                        {
                                            if (numj1 > numj3)
                                            {
                                                temp = count[j];
                                                count[j] = count[i];
                                                count[i] = temp;
                                            }
                                            else
                                            {
                                                if (numi3 < numj1)
                                                {
                                                    temp = count[j];
                                                    count[j] = count[i];
                                                    count[i] = temp;
                                                }
                                            }
                                        }
                                        else
                                        {
                                            if (numj2 > numj4)
                                            {
                                                temp = count[j];
                                                count[j] = count[i];
                                                count[i] = temp;
                                            }
                                            else
                                            {
                                                if (numi3 < numj2)
                                                {
                                                    temp = count[j];
                                                    count[j] = count[i];
                                                    count[i] = temp;
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        if (numj1 < numj2)
                                        {
                                            if (numj1 > numj3)
                                            {
                                                if (numj3 < numi1)
                                                {
                                                    temp = count[j];
                                                    count[j] = count[i];
                                                    count[i] = temp;
                                                }
                                            }
                                        }
                                        else
                                        {
                                            if (numj2 > numj4)
                                            {
                                                if (numj4 < numi1)
                                                {
                                                    temp = count[j];
                                                    count[j] = count[i];
                                                    count[i] = temp;
                                                }
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    if (numi2 > numi4)
                                    {
                                        if (numj1 < numj2)
                                        {
                                            if (numj1 > numj3)
                                            {
                                                temp = count[j];
                                                count[j] = count[i];
                                                count[i] = temp;
                                            }
                                            else
                                            {
                                                if (numi4 < numj1)
                                                {
                                                    temp = count[j];
                                                    count[j] = count[i];
                                                    count[i] = temp;
                                                }
                                            }
                                        }
                                        else
                                        {
                                            if (numj2 > numj4)
                                            {
                                                temp = count[j];
                                                count[j] = count[i];
                                                count[i] = temp;
                                            }
                                            else
                                            {
                                                if (numi4 < numj2)
                                                {
                                                    temp = count[j];
                                                    count[j] = count[i];
                                                    count[i] = temp;
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        if (numj1 < numj2)
                                        {
                                            if (numj1 > numj3)
                                            {
                                                if (numj3 < numi2)
                                                {
                                                    temp = count[j];
                                                    count[j] = count[i];
                                                    count[i] = temp;
                                                }
                                            }
                                        }
                                        else
                                        {
                                            if (numj2 > numj4)
                                            {
                                                if (numj4 < numi2)
                                                {
                                                    temp = count[j];
                                                    count[j] = count[i];
                                                    count[i] = temp;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        for (i = 0; i < ch3; i++)
                        {
                            for (j = i+1; j < ch3; j++)
                            {
                                int r1 = 0;
                                int r2 = 0;
                                if (count[i] / 10 == count[j] / 10)
                                {
                                    if (count[i] % 10 == (dim - 1) - count[j] % 10 || (dim - 1) - count[i] % 10 == count[j] % 10)
                                    {
                                        bool arb1 = check_LegalIn_Direction(dim, count[i] / 10, count[i] % 10, 'W', arr, &r1);
                                        bool arb2 = check_LegalIn_Direction(dim, count[j] / 10, count[j] % 10, 'W', arr, &r2);
                                        if (r2 > r1)
                                        {
                                            temp = count[j];
                                            count[j] = count[i];
                                            count[i] = temp;
                                        }
                                    }
                                }
                                else if (count[i] % 10 == count[j] % 10)
                                {
                                    if (count[i] / 10 == (dim - 1) - count[j] / 10 || (dim - 1) - count[i] / 10 == count[j] / 10)
                                    {
                                        bool arb1 = check_LegalIn_Direction(dim, count[i] / 10, count[i] % 10, 'W', arr, &r1);
                                        bool arb2 = check_LegalIn_Direction(dim, count[j] / 10, count[j] % 10, 'W', arr, &r2);
                                        if (r2 > r1)
                                        {
                                            temp = count[j];
                                            count[j] = count[i];
                                            count[i] = temp;
                                        }
                                    }
                                }
                                else if(count[i]%10==count[j]/10)
                                {
                                    bool arb1 = check_LegalIn_Direction(dim, count[i] / 10, count[i] % 10, 'W', arr, &r1);
                                    bool arb2 = check_LegalIn_Direction(dim, count[j] / 10, count[j] % 10, 'W', arr, &r2);
                                        if (r2 > r1)
                                        {
                                            temp = count[j];
                                            count[j] = count[i];
                                            count[i] = temp;
                                        }
                                }
                                else if(count[i]/10==count[j]%10)
                                {
                                    bool arb1 = check_LegalIn_Direction(dim, count[i] / 10, count[i] % 10, 'W', arr, &r1);
                                    bool arb2 = check_LegalIn_Direction(dim, count[j] / 10, count[j] % 10, 'W', arr, &r2);
                                    if (r2 > r1)
                                    {
                                            temp = count[j];
                                            count[j] = count[i];
                                            count[i] = temp;
                                    }
                                }
                            }
                        }
                        if (ch3 != 1)
                        {
                            for (i = 0; i < ch3-1; i++)
                            {
                                if ((count[i] / 10 == 1 && count[i] % 10 == 1) || (count[i] / 10 == (dim - 2) && count[i] % 10 == (dim - 2)) || (count[i] / 10 == 1 && (dim - 1) - count[i] % 10 == 1) || ((dim - 1) - count[i] / 10 == 1 && count[i] % 10 == 1) || (count[i] / 10 == 0 && count[i] % 10 == 1) || (count[i] / 10 == 1 && count[i] % 10 == 0) || (count[i] / 10 == (dim - 2) && count[i] % 10 == (dim - 1)) || (count[i] / 10 == (dim - 1) && count[i] % 10 == (dim - 2)) || (count[i] / 10 == 0 && (dim - 1) - count[i] % 10 == 1) || ((dim - 1) - count[i] / 10 == 1 && count[i] % 10 == 0) || ((dim - 1) - count[i] / 10 == 0 && count[i] % 10 == 1) || (count[i] / 10 == 0 && (dim - 1) - count[i] % 10 == 1))
                                    count[i] = 1000000;
                            }
                        }
                        for (i = 0; i < ch3; i++)
                        {
                            if (count[i] != 1000000)
                            {
                                f1 = count[i] / 10;
                                f2 = count[i] % 10;
                                break;
                            }
                        }
                    }
                    if (ch3 != 0)
                    {
                        printf("Computer places W at %c%c.\n", (char)(f1 + 97), (char)(f2 + 97));
                        int con = changeDirection(dim, f1, f2, 'W', arr);
                        printboard(dim, arr);
                    }
                    else
                    {
                        printf("W player has no valid move.\n");
                    }
                }
                ch++;
            }
            else
            {
                if (wc > bc)
                    printf("W player wins.\n");
                else
                    printf("B player wins.\n");
                break;
            }
        }
    }
    else
    {
        ch = 1;
        while (true)
        {
            uc = bc = wc = 0;
            for (i = 0; i < dim; i++)
            {
                for (j = 0; j < dim; j++)
                {
                    if (arr[i][j] == 'U')
                        uc++;
                    if (arr[i][j] == 'B')
                        bc++;
                    if (arr[i][j] == 'W')
                        wc++;
                }
            }
            if (uc != 0)
            {
                if (ch % 2 == 0)
                {
                    ch2 = 0;
                    for (i = 0; i < dim; i++)
                    {
                        for (j = 0; j < dim; j++)
                        {
                            if (arr[i][j] == 'U')
                            {
                                check = check_LegalIn_Direction(dim, i, j, 'W', arr, &r);
                                if (check == true)
                                {
                                    ch2++;
                                    break;
                                }
                            }
                        }
                        if (ch2 != 0)
                            break;
                    }
                    if (ch2 != 0)
                    {
                        printf("Enter move for colour W (RowCol): ");
                        scanf(" %c %c", &a, &b);
                        r = 0;
                        if (check_LegalIn_Direction(dim, (int)a - 97, (int)b - 97, 'W', arr, &r) == true)
                        {
                            int con = changeDirection(dim, (int)a - 97, (int)b - 97, 'W', arr);
                            printboard(dim, arr);
                        }
                        else
                        {
                            printf("Invalid move.\n");
                            printf("B player wins.\n");
                            break;
                        }
                    }
                    else
                    {
                        printf("W player has no valid move.\n");
                    }
                }
                else
                {
                    f1 = 0;
                    f2 = 0;
                    ch3 = 0;
                    max = 0;
                    char arr1[dim][dim];
                    for (i = 0; i < dim; i++)
                    {
                        for (j = 0; j < dim; j++)
                        {
                            if (arr[i][j] == 'U')
                            {
                                r = 0;
                                check = check_LegalIn_Direction(dim, i, j, 'B', arr, &r);
                                if (check == true)
                                {
                                    ch3++;
                                    if (r > max)
                                    {
                                        f1 = i;
                                        f2 = j;
                                        max = r;
                                    }
                                    else if (r == max)
                                    {
                                        if (i < f1)
                                            f1 = i;
                                        else if (i == f1)
                                        {
                                            if (j < f2)
                                                f2 = j;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (ch3 != 0)
                    {
                        printf("Computer places B at %c%c.\n", (char)(f1 + 97), (char)(f2 + 97));
                        int con = changeDirection(dim, f1, f2, 'B', arr);
                        printboard(dim, arr);
                    }
                    else
                    {
                        printf("B player has no valid move.\n");
                    }
                }
                ch++;
            }
            else
            {
                if (wc > bc)
                    printf("W player wins.\n");
                else
                    printf("B player wins.\n");
                break;
            }
        }
    }
}
void printboard(int size, char re[][size])
{
    int i, j;
    for (i = -1; i < size; i++)
    {
        for (j = -1; j < size; j++)
        {
            if (i == -1 && j == -1)
                printf("  ");
            else if (i == -1)
                printf("%c", (char)(j + 97));
            else if (j == -1)
                printf("%c ", (char)(i + 97));
            else
                printf("%c", re[i][j]);
        }
        printf("\n");
    }
}
bool position_In_Bounds(int n, int row, int col)
{
    if (row >= 0 && col >= 0 && row < n && col < n)
        return true;
    else
        return false;
}

bool check_LegalIn_Direction(int n, int row, int col, char colour, char board[][n], int *p)
{
    int i, j, p1, p2, ch = 0, c = 0;
    for (i = -1; i <= 1; i++)
    {
        for (j = -1; j <= 1; j++)
        {
            ch = 0, c = 0;
            if ((i != 0 || j != 0) && (position_In_Bounds(n, row, col)))
            {
                if (position_In_Bounds(n, row + i, col + j) == true)
                {
                    if (board[row + i][col + j] == (char)((int)colour - 21) || board[row + i][col + j] == (char)((int)colour + 21))
                    {
                        p1 = row + i;
                        p2 = col + j;
                        c = c + 1;
                        while (position_In_Bounds(n, p1, p2) == true)
                        {
                            if (board[p1][p2] == 'U')
                            {
                                c = 0;
                                break;
                            }
                            else if (board[p1][p2] == colour)
                            {
                                ch++;
                                c = c + 1;
                                break;
                            }
                            p1 = p1 + i;
                            p2 = p2 + j;
                            c = c + 1;
                        }
                        if (ch == 0)
                            c = 0;
                    }
                }
            }
            *p = *p + c;
        }
    }
    if (*p == 0)
        return false;
    else
        return true;
}
int changeDirection(int n, int row, int col, char colour, char board[][n])
{
    int i, j, p1, p2, c1, c2, ch = 0;
    for (i = -1; i <= 1; i++)
    {
        for (j = -1; j <= 1; j++)
        {
            ch = 0;
            if (position_In_Bounds(n, row + i, col + j) == true)
            {
                if (board[row + i][col + j] == (char)((int)colour - 21) || board[row + i][col + j] == (char)((int)colour + 21))
                {
                    p1 = row + i;
                    p2 = col + j;
                    while (position_In_Bounds(n, p1, p2) == true)
                    {
                        if (board[p1][p2] == colour)
                        {
                            c1 = p1;
                            c2 = p2;
                            p1 = row;
                            p2 = col;
                            while ((p1 != c1 || p2 != c2) && ch == 0)
                            {
                                board[p1][p2] = colour;
                                p1 = p1 + i;
                                p2 = p2 + j;
                            }
                            break;
                        }
                        else if (board[p1][p2] == 'U')
                        {
                            ch++;
                            break;
                        }
                        p1 = p1 + i;
                        p2 = p2 + j;
                    }
                }
            }
        }
    }
    return 0;
}