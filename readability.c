# include <stdio.h>
# include <cs50.h>
# include <string.h>
# include <math.h>

int char_count(string s);
int word_count(string s);
int sentence_count(string s);
int lc,sc,wc;
float L,S;

int main (void){

    string input=get_string("Text: ");
    //get counts
    printf("%i letter(s)\n",char_count(input));
    printf("%i word(s)\n",word_count(input));
    printf("%i sentence(s)\n",sentence_count(input));

    // get the grade
    L = (lc*100.0)/wc; //it should be 100.0 here!!
    S = (sc*100.0)/wc;
    printf("%.4f\n", 0.0588 * L - 0.296 * S - 15.8);
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    printf("%i\n",index);

    if (index<1){
        printf("Before Grade 1\n");
    }
    else if (index >= 16){
        printf("Grade 16+\n");
    }
    else{
        printf("Grade %i\n", index);
    }

}

int char_count(string s){
    int count = 0;
    for(int i = 0; i < strlen(s); i++) {
        if((64<(int)s[i] && (int)s[i]<91) || (96<(int)s[i] && (int)s[i]<123 ))
            count++;
    }
    lc = count;
    return count;
}

int word_count(string s){
    int w_count = 0;
    for(int i = 0; i < strlen(s); i++){
        if(s[i]==' '){
            w_count++;
        }
    }
    wc = w_count+1;
    return w_count+1;
}

int sentence_count(string s){
    int s_count = 0;
    for(int i = 0; i < strlen(s); i++){
        if(s[i]=='.' || s[i]=='!' || s[i]=='?' )
        s_count++;
    }
    sc = s_count;
    return s_count;
}


