# include <stdio.h>
# include <cs50.h>
# include <math.h>
int main (void){
    float owed;
    do{
    owed = get_float("Owed: ");
    }
    while(owed<0);

    int counter = 0;
    owed = round(owed * 100);
    if(owed/25>=1){
        counter += (int)(owed/25);
        owed = (int)owed % 25;
    }
    if(owed/10>=1){
        counter += (int)(owed/10);;
        owed = (int)owed % 10;
    }
    if(owed/5>=1){
        counter += (int)(owed/5);
        owed = (int)owed % 5;
    }
    if(owed/1>=1){
        counter += (int)(owed/1);
        owed = (int)owed % 1;

    }
    printf("%i\n",counter);
}
