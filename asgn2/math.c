#include <ctype.h>
#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "sctea"
#define EPSILON 0.00000001
double Sin();
double Cos();
double Tan();
double Exp();
double Factorial();
double Power();
const double PI = 3.141592653589793238462643383279502884197;

// this function will take in a flag and print out answers
int main(int argc, char **argv) {
  int opt = 0;
  while ((opt = getopt(argc, argv, OPTIONS)) != -1) { // continue while
    if (argc > 2) {                                   // only 1 argument exists
      printf("ERROR\n");
      return -1;
    }
    double z = 0;
    double approx, answer, diff = 0;
    switch (opt) { // created switch/case for argv
    case 's':      // sin(x)
      printf("%s %15s %19s %18s\n", "x", "Sin", "Library", "Difference");
      printf("%s %15s %19s %18s\n", "-", "---", "-------", "----------");
      for (z = -2.0 * PI; z <= 2.0 * PI + 0.001; z += PI / 16.0) {
        answer = sin(z);        // Library answer
        approx = Sin(z);        // my approx sin function
        diff = approx - answer; // differnece
        printf("%8.5f %15.8f %15.8f %15.8f\n", z, approx, answer, diff);
      }
      break;
    case 'c': // for cos(x)
      printf("%s %15s %19s %18s\n", "x", "Cos", "Library", "Difference");
      printf("%s %15s %19s %18s\n", "-", "---", "-------", "----------");
      for (z = -2.0 * PI; z <= 2.0 * PI + 0.001; z += PI / 16.0) {
        answer = cos(z); // Library answer
        approx = Cos(z); // my function
        diff = approx - answer;
        printf("%8.5f %15.8f %15.8f %15.8f\n", z, approx, answer, diff);
      }
      break;
    case 't': // for tan(x)
      printf("%s %15s %19s %18s\n", "x", "Tan", "Library", "Difference");
      printf("%s %15s %19s %18s\n", "-", "---", "-------", "----------");
      for (z = -(PI / 2 - 0.001); z <= (PI / 2 - 0.001) + 0.1;
           z += PI / 16.00) {
        answer = tan(z); // sin(x)/Cos(x)
        approx = Tan(z);
        diff = approx - answer;
        printf("%8.5f %15.8f %15.8f %15.8f\n", z, approx, answer, diff);
      }
      break;
    case 'e': // exp function
      printf("%s %15s %19s %18s\n", "x", "Exp", "Library", "Difference");
      printf("%s %15s %19s %18s\n", "-", "---", "-------", "----------");
      for (z = 0; z <= 10; z += 0.1) {
        approx = Exp(z);
        answer = exp(z);
        diff = answer - approx;
        printf("%8.5f %15.8f %15.8f %15.8f\n", z, approx, answer, diff);
      }
      break;
    case 'a': // print all
      printf("%s %15s %19s %18s\n", "x", "Sin", "Library", "Difference");
      printf("%s %15s %19s %18s\n", "-", "---", "-------", "----------");
      for (z = -2.0 * PI; z <= 2.0 * PI + 0.001; z += PI / 16.0) {
        answer = sin(z);
        approx = Sin(z);
        diff = approx - answer;
        printf("%8.5f %15.8f %15.8f %15.8f\n", z, approx, answer, diff);
      }
      printf("%s %15s %19s %18s\n", "x", "Cos", "Library", "Difference");
      printf("%s %15s %19s %18s\n", "-", "---", "-------", "----------");
      for (z = -2.0 * PI; z <= 2.0 * PI + 0.001; z += PI / 16.0) {
        answer = cos(z);
        approx = Cos(z);
        diff = approx - answer;
        printf("%8.5f %15.8f %15.8f %15.8f\n", z, approx, answer, diff);
      }
      printf("%s %15s %19s %18s\n", "x", "Tan", "Library", "Difference");
      printf("%s %15s %19s %18s\n", "-", "---", "-------", "----------");
      for (z = -(PI / 2 - 0.001); z <= (PI / 2 - 0.001) + 0.1;
           z += PI / 16.00) {
        answer = tan(z);
        approx = Tan(z);
        diff = approx - answer;
        printf("%8.5f %15.8f %15.8f %15.8f\n", z, approx, answer, diff);
      }
      printf("%s %15s %19s %18s\n", "x", "Exp", "Library", "Difference");
      printf("%s %15s %19s %18s\n", "-", "---", "-------", "----------");
      for (z = 0; z <= 10; z += 0.1) {
        approx = Exp(z);
        answer = exp(z);
        diff = answer - approx;
        printf("%8.5f %15.8f %15.8f %15.8f\n", z, approx, answer, diff);
      }
      break;

    case '?': // break if no -e -s -c -t -a
      printf("ERROR\n");
      return -1;
    }
  }

  return 0;
}

double Sin(double x) {
  int i = 0;
  double sign, p, f = 0;
  double approx = 0;
  if (x > PI) { // if radian > PI then -2*PI (same value)
    x = x - 2 * PI;
  } else if (x < -PI) { // if radian < -PI then +2*PI
    x = x + 2 * PI;
  }
  for (i = 0; i <= 10; i++) { //
    sign = pow(-1.0, i);
    p = Power(x, 2.0 * i + 1.0);
    f = Factorial(2.0 * i + 1.0);
    approx += sign * p / f;
  }
  return approx;
}

double Cos(double x) { // same as Sin(x)

  int i = 0;
  double sign, p, f = 0;
  double approx = 0;
  if (x > PI) {
    x = x - 2 * PI;
  } else if (x < -PI) {
    x = x + 2 * PI;
  }
  for (i = 0; i <= 10; i++) {
    sign = pow(-1.0, i);
    p = Power(x, 2.0 * i);
    f = Factorial(2.0 * i);
    approx += sign * p / f;
  }
  return approx;
}
double Tan(double x) { // go into Sin(x) and Cos(x) function
  double s, c = 0;     // divide Sin(x) by Cos(x)
  double approx = 0;
  s = Sin(x);
  c = Cos(x);
  approx = s / c;
  return approx;
}
double Exp(double x) {
  bool check = false;
  double i = 1.0;
  double term = 1.0;
  double sum = term;
  if (x < 0.0) { // if x is negative get reciprocal
    check = true;
    x *= -1.0;
  }
  while (term > EPSILON) {             // this while loop keeps on adding taylor
    term = Power(x, i) / Factorial(i); // until very small
    i += 1.0;
    sum += term;
  }
  if (check == true) {
    return 1.0 / sum;
  }
  return sum;
}

double Factorial(double a) { // recurison factorial
  if (a == 0 || a == 1) {
    return 1;
  } else {

    return a * (Factorial(a - 1));
  }
}

double Power(double a, double b) { // Power function
  int i = 0;
  double result = a;
  if (b == 0) {
    return 1;
  }
  for (i = 1; i < b; i++) {
    result *= a;
  }
  return result;
}
