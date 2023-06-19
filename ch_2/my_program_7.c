#include<stdio.h>
void one_three();
void two();
void three();

int main(){
    printf("starting now:\n");
    one_three();
    printf("done!");
    return 0;
}
void one_three(){
    printf("one\n");
    two();
}
void two(){
    printf("two\n");
    three();
}
void three(){
    printf("three\n");
}
