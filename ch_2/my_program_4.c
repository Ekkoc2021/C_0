#include<stdio.h>

void sayGood();
void say();
int main(void){
    sayGood();
    sayGood();
    sayGood();
    say();
    return 0;
}
void sayGood(){
    printf("For he's a jolly good fellow!\n");
}
void say(){
    printf("Which nobody can deny!");
}