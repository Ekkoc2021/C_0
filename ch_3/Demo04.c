#include <stdio.h>
#include <complex.h>

int main() {
    float complex z = 0.03 + 2.0 * I;  // 纯虚数，实部�?0.0

    printf("Real: %f\n", crealf(z));  // 获取实部（应该输�?0.0�?
    printf("Imaginary: %f\n", cimagf(z));  // 获取虚部（应该输�?2.0�?

    return 0;
}