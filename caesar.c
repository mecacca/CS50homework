# include <stdio.h>
# include <cs50.h>
# include <ctype.h>
# include <stdbool.h>
# include <string.h>
# include <stdlib.h>

bool isNumber(string s);
void move_onASCII (string s, int k);
int key ;


int main(int argc, string argv[])
{

    // check for single command line argument and digit input
    if (argc == 2 && isNumber(argv[1]) == 1)
    {
        printf("Success\n");

        //convert command line argument from a string into an integer 
        key = atoi(argv[1]);
        printf("%i\n", key);

        string c = get_string("string: ");

        //call encrypt method
        move_onASCII (c, key);

        return 0;
    }


    // if it is not a single command line argument, prompts usage and returns 1
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

}


bool isNumber(string s)
{
    // initiate status as false
    bool status = false;
    int digitcount = 0;

    for(int i=0; i<strlen(s); i++)
    {
        //if the i-th char is digit, digitcount + 1
        if(isdigit(s[i]))
        {
            digitcount++;
        }
    }

    if(digitcount == strlen(s))
    {
        status = true;
    }

    return status;
}

//encrypt ciphertext
void move_onASCII (string s, int k)
{

    printf("ciphertext: ");
    
    for (int i = 0; i < strlen(s); i++)
    {

        if (isupper(s[i]))
        {
            printf("%c", (((s[i] - 65) + k) % 26 + 65));
        }

        else if (islower(s[i]))
        {
            printf("%c", (((s[i] - 97) + k) % 26 + 97));
        }

        else
        {
            printf("%c", s[i]);
        }
        
    }

    printf("\n");

}
