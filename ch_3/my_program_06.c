#include<stdio.h>
int main(){
    float massOfOneMoleculeWater=3e-7;
    int count;
    printf("ˮ�Ŀ����: _\b");
    scanf("%d",&count);
    printf("%d��˵�ˮ���ӹ���%f��ˮ����!",count,(count*950)/massOfOneMoleculeWater);
    return 0;
}