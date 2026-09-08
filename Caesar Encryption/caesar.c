#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Error\n");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int k = atoi(argv[1]);
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        char c = plaintext[i];
        if (isupper(c))
        {
            printf("%c", ((c - 65 + k) % 26) + 65);
        }
        else if (islower(c))
        {
            printf("%c", ((c - 97 + k) % 26) + 97);
        }
        else
        {
            printf("%c", c);
        }
    }
    printf("\n");
    return 0;
}
