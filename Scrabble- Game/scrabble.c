#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int points[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    string input1 = get_string("Player 1: ");
    string input2 = get_string("Player 2: ");
    int length1 = strlen(input1);
    int length2 = strlen(input2);
    int c1 = 0;
    int c2 = 0;
    for (int i = 0; i < length1; i++)
    {
        char ch = input1[i];
        ch = toupper(ch);
        if (ch >= 65 && ch <= 90)
        {
            int s1 = (int) ch - 65;
            c1 = c1 + points[s1];
        }
    }
    for (int i = 0; i < length2; i++)
    {
        char ch = input2[i];
        ch = toupper(ch);
        if (ch >= 65 && ch <= 90)
        {
            int s2 = (int) ch - 65;
            c2 = c2 + points[s2];
        }
    }
    if (c1 == c2)
    {
        printf("Tie!");
    }
    else if (c1 > c2)
    {
        printf("Player 1 Wins!");
    }
    else if (c1 < c2)
    {
        printf("Player 2 Wins!");
    }
    return 0;
}
