#include <time.h>
#include <stdio.h>
// #include <sys/stat.h>
int main(int argc, char const *argv[])
{

    time_t now;
    now = time(NULL);
    struct tm *nowDate = localtime(&now);
    printf("year: %d \n", nowDate->tm_year + 1900);
    printf("Month: %d\n", nowDate->tm_mon + 1);
    printf("Day: %d\n", nowDate->tm_mday);
    printf("Hour: %d\n", nowDate->tm_hour);
    printf("Minute: %d\n", nowDate->tm_min);
    printf("Second: %d\n", nowDate->tm_sec);
    return 0;
}
