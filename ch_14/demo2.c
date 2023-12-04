
#include <stdio.h>
struct book
{
    char name[50];
    char author[50];
    float price;
};
void printBook(struct book b)
{
    b.author[1] = 'q';
    printf("地址:%p    书名:%s     价格:%f     作者:%s \n", &b, b.name, b.price, b.author);
}
int main(int argc, char const *argv[])
{
    struct book b1 =
        {
            "hello world",
            "ekko",
            0.001};
    printBook(b1);
    printf("地址:%p    书名:%s     价格:%f     作者:%s \n", &b1, b1.name, b1.price, b1.author);
    printBook((struct book){"vs", "code", 0.011});
    return 0;
}
