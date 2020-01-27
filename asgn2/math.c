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
      for (z = -2.0 * M_PI; z <= 2.0 * M_PI; z += M_PI / 16.0) {
        answer = sin(z);        // Library answer
        approx = Sin(z);        // my approx sin function
        diff = approx - answer; // differnece
        printf("%8.5f %15.8f %15.8f %15.8f\n", z, approx, answer, diff);
      }
      break;
    case 'c': // for cos(x)
      printf("%s %15s %19s %18s\n", "x", "Cos", "Library", "Difference");
      printf("%s %15s %19s %18s\n", "-", "---", "-------", "----------");
      for (z = -2.0 * M_PI; z <= 2.0 * M_PI; z += M_PI / 16.0) {
        answer = cos(z); // Library answer
        approx = Cos(z); // my function
        diff = approx - answer;
        printf("%8.5f %15.8f %15.8f %15.8f\n", z, approx, answer, diff);
      }
      break;
    case 't': // for tan(x)
      printf("%s %15s %19s %18s\n", "x", "Tan", "Library", "Difference");
      printf("%s %15s %19s %18s\n", "-", "---", "-------", "----------");
      for (z = -(M_PI / 2 - 0.001); z <= (M_PI / 2 - 0.001) + 0.1;
           z += M_PI / 16.00) {
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
      for (z = -2.0 * M_PI; z <= 2.0 * M_PI; z += M_PI / 16.0) {
        answer = sin(z);
        approx = Sin(z);
        diff = approx - answer;
        printf("%8.5f %15.8f %15.8f %15.8f\n", z, approx, answer, diff);
      }
      printf("%s %15s %19s %18s\n", "x", "Cos", "Library", "Difference");
      printf("%s %15s %19s %18s\n", "-", "---", "-------", "----------");
      for (z = -2.0 * M_PI; z <= 2.0 * M_PI; z += M_PI / 16.0) {
        answer = cos(z);
        approx = Cos(z);
        diff = approx - answer;
        printf("%8.5f %15.8f %15.8f %15.8f\n", z, approx, answer, diff);
      }
      printf("%s %15s %19s %18s\n", "x", "Tan", "Library", "Difference");
      printf("%s %15s %19s %18s\n", "-", "---", "-------", "----------");
      for (z = -(M_PI / 2 - 0.001); z <= (M_PI / 2 - 0.001) + 0.1;
           z += M_PI / 16.00) {
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

//USED PROFESSOR LONG's CODE
double Sin(double x) {
  double answer, answer2 = 0;
  if (x > M_PI) {
    x -= 2 * M_PI;
  }
  if (x < -M_PI) {
    x += 2 * M_PI;
  }
  double square = x * x;
  answer =
      x * (312140082454773707300540774400.00 +
           square * (-46874038261167705331462118400.00 +
                     square * (1786120037873661209340741120.00 +
                               square * (-25976870613633842126864640.00 +
                                         square * (159210544441105257620520.00 -
                                                   352265759709839993316.00 *
                                                       square)))));
  answer2 =
      312140082454773707300540774400.00 +
      square *
          (5149308814627912551961344000.00 +
           square *
               (43170819855199073829792000.00 +
                square * (239915282947229725355520.00 +
                          square * (953460195521182909560.00 +
                                    square * (2641606814451060456.00 +
                                              4128322445936963 * square)))));
  return answer / answer2;
}

//USED PROFESSOR LONG's CODE
double Cos(double x) { // same as Sin(x)
  double answer, answer2 = 0;
  x += M_PI / 2;
  if (x > 3 * M_PI / 2) {
    x -= 2 * M_PI;
  }
  double square = x * x;
  answer =
      x * (312140082454773707300540774400.00 +
           square * (-46874038261167705331462118400.00 +
                     square * (1786120037873661209340741120.00 +
                               square * (-25976870613633842126864640.00 +
                                         square * (159210544441105257620520.00 -
                                                   352265759709839993316.00 *
                                                       square)))));
  answer2 =
      312140082454773707300540774400.00 +
      square *
          (5149308814627912551961344000.00 +
           square *
               (43170819855199073829792000.00 +
                square * (239915282947229725355520.00 +
                          square * (953460195521182909560.00 +
                                    square * (2641606814451060456.00 +
                                              4128322445936963 * square)))));

  return answer / answer2;
}

double Tan(double x) {
  double answer, answer2 = 0;
  double square = x * x;
  answer =
      x * (square * (square * (square * (square - 990) + 135135) - 4729725) +
           34459425);
  answer2 =
      45 *
      (square * (square * (square * (square - 308) + 21021) - 360360) + 765765);

  return answer / answer2;
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
