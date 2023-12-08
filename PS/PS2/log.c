#include <stdio.h>

double approxLog(double a, int n)
{
    /*
        TODO: Use trapezoid integration to approximate the logarithm.
    */

    double sum = 0, delta = (a - 1) / n;
    for (int k = 1; k < n; ++k)
        sum += 1.0 / (1 + k * delta);
    return delta * ((1.0 / (1 + n * delta) + 1) / 2.0 + sum);
}

int main(int argc, char* argv[])
{
  double a;
  int n;
  printf("Enter a: ");
  scanf("%lf", &a);
  printf("Enter n: ");
  scanf("%d", &n);
  double logarithm = approxLog(a, n);
  printf("Natural logarithm: %lf\n", logarithm);
  return 0;
}
