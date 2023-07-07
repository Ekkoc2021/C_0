#include<stdio.h>
#define PERIOD '.'
int main(){
    int ch;
    int charcount=0;
    while ((ch=getchar())!=PERIOD){
        if(ch!='"' && ch!='\''){
            charcount++;
        }
    }
    printf("There are %d non-quote chareacters.\n",charcount); 
    return 0;
}
