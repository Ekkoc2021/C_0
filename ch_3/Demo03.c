#include <stdio.h>
#include <complex.h>

int main() {
    double complex z1 = 1.0 + 2.0 * I;  // 定义一个复�?
    double complex z2 = 2.0 - 1.0 * I;

    double complex sum = z1 + z2;  // 复数相加
    double complex product = z1 * z2;  // 复数相乘

    printf("Sum: %f + %fi\n", creal(sum), cimag(sum));  // 获取实部和虚�?
    printf("Product: %f + %fi\n", creal(product), cimag(product));

    return 0;
}