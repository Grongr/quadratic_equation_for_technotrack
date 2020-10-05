#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define epsilon 1e-10

void   instructions();
void   elementary_error();
char   is_equal(double a, double b);
char   is_bigger(double a, double b);
char   is_less(double a, double b);
int    get_equation_result(double a, double b, double c, double* x1, double* x2);
double calculate_the_discrimimant(double a, double b, double c);
double calculate_linear_equation(double b, double c);
void   unit_tests();
void   print_result(double x1, double x2, int number_of_roots);
void   check_unit_test(double x1, double x2, int nroots, const double tx1,
                        const double tx2, const int tnroots, char* p, int test_number);

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
int main() {
  char command[100];
  printf("\n=====================================================================\n");
  printf("If you wanna view the instruction, please press <h> or read README file\n");
  printf("If you wanna test the programm with <unit_tests> function, than enter <u>\n");
  printf("If you don't need any instructions and you don't need unitests,\nyou is cool, so write <c>\n");
  printf("WARNING: To read instructions with <h> command you need to\nput <instructions.txt> file in the same directory as <quadratic_equation.c>\n\n");
  printf("=====================================================================\n");
  printf("Your command: ");
  
  fgets(command, 100, stdin);
  while (strcmp(command, "h\n") && strcmp(command, "u\n") && strcmp(command, "c\n")) {
    elementary_error();
    fgets(command, 100, stdin);
  } 

  if (!strcmp(command, "h\n")) {
    instructions();
  } else if (!strcmp(command, "u\n")) {
    unit_tests();
    return 0;
  }

  double a = 0, b = 0, c = 0;
  double x1 = 0, x2 = 0;
   
  printf("\n==================================\n");
  printf("Enter the coefficients of equation:\n");
  int count_of_normal_inputs = scanf("%lg %lg %lg", &a, &b, &c);
  if (count_of_normal_inputs != 3) {
    printf("\n==================================\n");
    printf("An input is not a numbers set.\nPlease, next time read manual normally.\n");
    abort();
  }
  
  if (is_bigger(abs(a), 1e100) || is_bigger(abs(b), 1e100) || is_bigger(abs(c), 1e100)) {
    printf("\n!!! Warning: Your input is too big. It may couse errors!\n\n");
  }
  if (is_less(abs(a), 1e-10) || is_less(abs(a), 1e-10) || is_less(abs(a), 1e-10)) {
    printf("\n!!! Warning : Your input is too small. It may couse errors!\n\n");
  }

  int number_of_roots = get_equation_result(a, b, c, &x1, &x2);

  print_result(x1, x2, number_of_roots);

  return 0;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void instructions() {
  FILE *fp = fopen("./instructions.txt", "r");
  if (fp == NULL) {
    printf("Something went wrong.\nCannot open file <instructions.txt>\n");
    printf("Place such a file in the same directory as an executable file\nand reboot the process.\n");
    printf("Or continue without instructions T_T\n");
    return;
  }
  char line[200];
  while (fgets(line, 200, fp)) {
    printf("%s", line);
  }
}

void elementary_error() {
  printf("\n=====================================================================\n");
  printf("Warning: wrong input, please try one more time.\nDo your best!\n");
  printf("=====================================================================\n");
  printf("Your command: ");
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
char is_equal(double a, double b) {
  if (abs(a - b) < epsilon) {
    return 1;
  } else {
    return 0;
  }
}

char is_bigger(double a, double b) {
  if (b + epsilon < a) {
    return 1;
  } else {
    return 0;
  }
}

char is_less(double a, double b) {
  if (b > a + epsilon) {
    return 1;
  } else {
    return 0;
  }
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
int get_equation_result(double a, double b, double c, double* x1, double* x2) {
  if (x1 == x2) {
    printf("x1 and x2 is different roots.\n");
    printf("You may want to do them non identically\n");
    abort();
  }

  if (is_equal(a, 0.0) && is_equal(b, 0.0) && !is_equal(c, 0.0)) {
    return 0;
  }

  if (a < 0) {
    a *= -1;
    b *= -1;
    c *= -1;
  }

  double D = 0;
  D = calculate_the_discrimimant(a, b, c);
  
  if (is_equal(a, 0.0) && is_equal(b, 0.0) && is_equal(c, 0.0)) {
    return -1;
  } else if (is_equal(a, 0.0)) {
    *x1 = calculate_linear_equation(b, c);
    return 1;
  } else if (is_equal(D, 0.0)) {
    *x1 =  calculate_linear_equation(2 * a, b);
    return 1;
  } else if (is_equal(D, -1.0)) {
    return 0;
  } else if (is_bigger(D, 0.0)) {
    *x1 = calculate_linear_equation(2 * a, (b + D));

    *x2 = calculate_linear_equation(2 * a, (b - D));
    return 2;
  } 
}

double calculate_the_discrimimant(double a, double b, double c) {
  double D = b * b - 4 * a * c;
  if (D >= 0) {
    return sqrt(D);
  } else {
    return -1;
  }
}

double calculate_linear_equation(double b, double c) {
  if (b == 0) {
    printf("You cannot divide by zero!\nLine %d\n", __LINE__ + 3);
    abort();
  }
  return (-c / b);
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void print_result(double x1, double x2, int number_of_roots) {
  printf("\n==================================\n");
  switch (number_of_roots) {
    case  1: printf("There is only one solution for your equation.\n");
             printf("x = %.4lg\n", x1);
             break;
    case  2: printf("There is two solutions of your equation.\n");
             printf("x1 = %.4lg\t", x1);
             printf("x2 = %.4lg\n", x2);
             break;
    case  0: printf("There is no solution of your equation.\n");
             break;
    case -1: printf("This equation has an infinit count of solutions\n");
             break;
    default: printf("Program exited with an error.\n");
             abort();
             break;
    }

}


// Unit Tests
// ---------------------------------------------------------------

void check_unit_test(double x1, double x2, int nroots, const double tx1, const double tx2, const int tnroots, char* p, int test_number) {
  if (!is_equal(tx1, x1) || !is_equal(tx2, x2)) {
    printf("\n==================================\n");
    printf("Error in unitests. Test %d failed.\n", test_number);
    printf("Result is %.4lg and %.4lg, but needed:\n%.4lg and %.4lg\n", x1, x2, tx1, tx2);
    *p = 0;
  }
  if (!is_equal(tnroots, nroots)) {
    printf("Number of roots needs to be %d, but it is %d\n", tnroots, nroots);
    *p = 0;
  }
}

void unit_tests() {
  char passed = 1;
  int test_number = 0;

  /* Test 1 */ {
    test_number = 1;
    double a = -1, b = -2, c = 15, x1 = 0, x2 = 0;
    int nroots = get_equation_result(a, b, c, &x1, &x2);
    
    const int true_nroots = 2;
    const double true_x1  = -5.0;
    const double true_x2  = 3.0;
    check_unit_test(x1, x2, nroots, true_x1, true_x2, true_nroots, &passed, test_number);
  }
  
  /* Test 2 */ {
    test_number = 2;
    double a = 0, b = 1, c = 1, x1 = 0, x2 = 0;
    int nroots = get_equation_result(a, b, c, &x1, &x2);
    
    const int true_nroots = 1;
    const double true_x1  = -1.0;
    const double true_x2  = 0;
    check_unit_test(x1, x2, nroots, true_x1, true_x2, true_nroots, &passed, test_number);
  }
  
  /* Test 3 */ {
    test_number = 3;
    double a = 1, b = 12, c = 36, x1 = 0, x2 = 0;
    int nroots = get_equation_result(a, b, c, &x1, &x2);
    
    const int true_nroots = 1;
    const double true_x1  = -6;
    const double true_x2  = 0;
    check_unit_test(x1, x2, nroots, true_x1, true_x2, true_nroots, &passed, test_number);
  }
  
  /* Test 4 */ {
    test_number = 4;
    double a = 1, b = 0, c = -16, x1 = 0, x2 = 0;
    int nroots = get_equation_result(a, b, c, &x1, &x2);
    
    const int true_nroots = 2;
    const double true_x1  = -4.0;
    const double true_x2  = 4.0;
    check_unit_test(x1, x2, nroots, true_x1, true_x2, true_nroots, &passed, test_number);
  }

  /* Test 5 */ {
    test_number = 5;
    double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
    int nroots = get_equation_result(a, b, c, &x1, &x2);
    
    const int true_nroots = -1;
    const double true_x1  = 0;
    const double true_x2  = 0;
    check_unit_test(x1, x2, nroots, true_x1, true_x2, true_nroots, &passed, test_number);
  }


  if (passed) {
    printf("\n==================================\n");
    printf("Tests passed without problems.\n");
  }
}
