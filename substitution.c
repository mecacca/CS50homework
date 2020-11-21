# include <stdio.h>
# include <cs50.h>
# include <ctype.h>
# include <string.h>
# include <stdbool.h>

int letters_count(string s);
bool is_repetitive(string s);
void encrypt(string key, string input);


int main(int argc, string argv[])
{

    //validate for single line argument && 26 only-letter chars && no repetition
    if (argc == 2 && letters_count(argv[1]) == 26 && is_repetitive(argv[1]) == 0)
    {
        string plaintext = get_string("plaintext: ");

        // encrypt plaintext 
        encrypt(argv[1], plaintext);

        return 0;

    }


    // prompts usage info and returns 1 
    else
    {
        printf("Usage: ./substitution key\n");

        return 1;
    }

}


int letters_count(string s)
{

    // initiate the number of letters as 0
    int count = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if ((64 < (int)s[i] && (int)s[i] < 91) || (96 < (int)s[i] && (int)s[i] < 123))
        {
            count++;
        }

    }

    return count;
}


bool is_repetitive(string s)
{

    //initiate repetition as false
    bool repetition = false;

    //initiate the duplicate count of char as 0, meaning no duplicate
    int count2 = 0;

    for (int i = 0; i < strlen(s); i++)
    {

        // initiate the apearance count of i-th letter as 1, meaning appear once
        int count = 1;

        //compare each char with the next one, add one to appearance count when they are the same
        for(int j = i + 1 ; j < strlen(s); j++)
        {
            if (s[i] == s[j] && s[i] != ' ')
            {
                count++;
            }
        }

        // add one to duplicate count if appearance count > 1, meaning one duplicate
        if (count > 1)
        {
            count2++;
        }

    }


    // if duplicate count > 0, meaning repetition is true, else repetition remains false
    if (count2 > 0)
    {
        repetition = true;
    }

    return repetition;

}


void encrypt(string key, string input)
{

    printf("ciphertext: ");

    for (int i = 0; i < strlen(input); i++)
    {
    
        //encrypt upper case letters
        if (isupper(input[i]))
        {
            printf("%c", toupper(key[input[i] - 65]));
        }

        //encrypt lower case letters
        else if (islower(input[i]))
        {
            printf("%c", tolower(key[input[i] - 97]));
        }

        //print non-letter chars
        else
        {
            printf("%c", input[i]);
        }

    }

    printf("\n");

}
