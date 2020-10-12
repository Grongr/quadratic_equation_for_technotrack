#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define epsilon 1e-10

//--------------------------------------------------------------//
//!        Prints some information and instructions
//--------------------------------------------------------------//
int    hello(); 

//--------------------------------------------------------------//
//!    Prints some instructions from <instruction.txt> file
//!    @note  <instructions.txt> should be on the same 
//!          directory as executable
//--------------------------------------------------------------//
void   instructions();

//--------------------------------------------------------------//
//!            Shows a massage about wrong input
//--------------------------------------------------------------//
void   elementary_error();

//--------------------------------------------------------------//
//!   Gets three coefficients of equation a*x^2 + b*x + c = 0
//!  
//!   @param [out] a  a-coefficient
//!   @param [out] b  b-coefficient
//!   @param [out] c  c-coefficient
//!
//!   @note  Checks if input is correct
//--------------------------------------------------------------//
void   get_coefficients(double* a, double* b, double* c); 

//--------------------------------------------------------------//
//!    Comparator for double numbers with epsilon = 10e-10
//!
//!    @param [in] a  first number to compare
//!    @param [in] b  second number to compare
//!
//!    @return  1 if a > b
//!            -1 if b > a
//!             0 if a == b
//--------------------------------------------------------------//
int    cmp(double a, double b);

//--------------------------------------------------------------//
//!      Solves a quadratic equation a*x^2 + b*x + c = 0
//!
//!      @param [in]   a   a-coefficient
//!      @param [in]   b   b-coefficient
//!      @param [in]   c   c-coefficient
//!      @param [out] x1   Pointer to the first root
//!      @param [out] x2   Pointer to the second root
//!
//!      @return  Number of roots
//--------------------------------------------------------------//
int    get_equation_result(double a, double b, double c, double* x1, double* x2);

//--------------------------------------------------------------//
//! Calculstes the discriminant of equation a*x^2 + b*x + c = 0
//!
//!   @param [in] a   a-coefficient
//!   @param [in] b   b-coefficient
//!   @param [in] c   c-coefficient
//!
//!   @return Discriminant
//!   
//!   @note   If Discriminant are less than zero
//!           returns -1
//--------------------------------------------------------------//
double calculate_the_discrimimant(double a, double b, double c);

//--------------------------------------------------------------//
//!         Calculates the equation b*x + c = 0
//!    
//!    @param [in]   b  b-coefficient
//!    @param [in]   c  c-coefficient
//!    @param [out] x1  Pointer to the solution of the equation
//!
//!    @return Returns thenumber of solutions
//!            if there are n solutions returns -1
//--------------------------------------------------------------//
int    calculate_linear_equation(double b, double c, double* x1);

//--------------------------------------------------------------//
//!           Prints all the solutions of the equation
//!                   dependingon their count
//!
//!   @param [in]  x1  first solution of the equation
//!   @param [in]  x2  second solution of the equation
//!   @param [in]  number_of_roots   nothing to say there
//--------------------------------------------------------------//
void   print_result(double x1, double x2, int number_of_roots);

//--------------------------------------------------------------//
//!          Only unit tests. Nothing to say there
//--------------------------------------------------------------//
void   unit_tests();
void   check_unit_test(double x1, double x2, int nroots, const double tx1,
                        const double tx2, const int tnroots, char* p, int test_number);

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
int main() {

  if (hello()) {
    return 0;
  }

  double a = 0, b = 0, c = 0;
  double x1 = 0, x2 = 0;

  get_coefficients(&a, &b, &c);
   
  int number_of_roots = get_equation_result(a, b, c, &x1, &x2);

  print_result(x1, x2, number_of_roots);

  return 0;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

int hello() {

  char command = 0;

  printf("\n=====================================================================\n");
  printf("If you wanna view the instruction, please press <h> or read README file\n");
  printf("If you wanna test the programm with <unit_tests> function, than enter <u>\n");
  printf("If you don't need any instructions and you don't need unitests,\nyou is cool, so write <c>\n");
  printf("WARNING: To read instructions with <h> command you need to\nput <instructions.txt> file in the same directory as <quadratic_equation.c>\n\n");
  printf("=====================================================================\n");
  printf("Your command: ");

  command = getchar();
  if (getchar() != '\n')
    scanf("%*s");

  while (command != 'h' && command != 'u' && command != 'c') {

    elementary_error();

    command = getchar();
    if(getchar() != '\n') scanf("%*s");
  } 

  if (command == 'h') {

    instructions();

  } else if (command == 'u') {
    
    unit_tests();

    return 1;
  }
  
  return 0;
}

void get_coefficients(double* a, double* b, double* c) {

  assert(!(a == b));
  assert(!(b == c));

  printf("\n==================================\n");
  printf("Enter the coefficients of equation:\n");

  int count_of_normal_inputs = scanf("%lg %lg %lg", a, b, c);

  while (count_of_normal_inputs != 3) {
    printf("\n==================================\n");
    printf("An input is not a numbers set.\nPlease, enter the coefficientd one more time:\n");
    count_of_normal_inputs = scanf("%lg %lg %lg", a, b, c);
  }

  assert(isfinite(*a));
  assert(isfinite(*b));
  assert(isfinite(*c));

  return;
}

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

  return;
}

void elementary_error() {

  printf("\n=====================================================================\n");
  printf("Warning: wrong input, please try one more time.\nDo your best!\n");
  printf("=====================================================================\n");
  printf("Your command: ");

  return;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

int cmp(double a, double b) {
  
  if (a - b <= epsilon)
    return 0;
  else if (b + epsilon < a)
    return 1;
  else if (a + epsilon < b)
    return -1;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

int get_equation_result(double a, double b, double c, double* x1, double* x2) {

  assert(!(x1 == x2));

  if (a < 0) {
    a *= -1;
    b *= -1;
    c *= -1;
  }

  double D = 0;

  D = calculate_the_discrimimant(a, b, c);

  if (!cmp(a, 0.0)) {

    return calculate_linear_equation(b, c, x1);

  } else if (!cmp(D, 0.0)) {

    calculate_linear_equation(2 * a, b, x1);

    return 1;

  } else if (!cmp(D, -1.0)) {

    return 0;

  } else if (cmp(D, 0.0) == 1) {

    calculate_linear_equation(2 * a, (b + D), x1);

    calculate_linear_equation(2 * a, (b - D), x2);

    return 2;
  } 
}

double calculate_the_discrimimant(double a, double b, double c) {

  assert(isfinite(b * b));
  assert(isfinite(4 * a * c));

  double D = b * b - 4 * a * c;

  if (cmp(D, 0.0) == 1 || !cmp(D, 0.0)) {

    return sqrt(D);

  } else {
    
    return -1;

  }

}

int calculate_linear_equation(double b, double c, double* x1) {
  
  if (!cmp(b, 0.0) && !cmp(c, 0.0)) {

    return -1;

  } else if (!cmp(b, 0.0)) {

    return 0;

  } else {

    *x1 = -c / b;

    return 1;
  }
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void print_result(double x1, double x2, int number_of_roots) {

  printf("\n==================================\n");

  switch (number_of_roots) {
    case  1: 
      printf("There is only one solution for your equation.\n");
      printf("x = %.4lg\n", x1);
    break;

    case  2: 
      printf("There is two solutions of your equation.\n");
      printf("x1 = %.4lg\t", x1);
      printf("x2 = %.4lg\n", x2);
    break;

    case  0: 
      printf("There is no solution of your equation.\n");
    break;

    case -1:
      printf("This equation has an infinit count of solutions\n");
    break;

    default:
      printf("Program exited with an error.\n");
      abort();
    break;
  }

}


// Unit Tests
// ---------------------------------------------------------------

void check_unit_test(double x1, double x2, int nroots, const double tx1, const double tx2, const int tnroots, char* p, int test_number) {
  if (cmp(tx1, x1) || cmp(tx2, x2)) {
    printf("\n==================================\n");
    printf("Error in unitests. Test %d failed.\n", test_number);
    printf("Result is %.4lg and %.4lg, but needed:\n%.4lg and %.4lg\n", x1, x2, tx1, tx2);
    *p = 0;
  }
  if (cmp(tnroots, nroots)) {
    printf("Error in unitests. Test %d failed.\n", test_number);
    printf("Number of roots needs to be %d, but it is %d\n", tnroots, nroots);
    *p = 0;
  }
}

#define TEST(NUM_TEST, A, B, C, X1, X2, NUM_ROOTS)                                               \
    test_number = NUM_TEST;                                                                      \
    double a = A, b = B, c = C, x1 = 0, x2 = 0;                                                  \
    int nroots = get_equation_result(a, b, c, &x1, &x2);                                         \
                                                                                                 \
    const int true_nroots = NUM_ROOTS;                                                           \
    const double true_x1  = X1;                                                                  \
    const double true_x2  = X2;                                                                  \
    check_unit_test(x1, x2, nroots, true_x1, true_x2, true_nroots, &passed, test_number);        

void unit_tests() {
  char passed = 1;
  int test_number = 0;

  //     num     a     b      c    x1   x2  numOfRoot
  {
    TEST(  1, -1.0, -2.0,  15.0, -5.0, 3.0,         2)
  }

  //     num     a     b      c    x1   x2  numOfRoot
  {
    TEST(  2,  0.0,  1.0,   1.0, -1.0, 0.0,         1)
  }

  //     num     a     b      c    x1   x2  numOfRoot
  {
    TEST(  3,  1.0, 12.0,  36.0, -6.0, 0.0,         1)
  }

  //     num     a     b      c    x1   x2  numOfRoot
  {
    TEST(  4,  1.0,  0.0, -16.0, -4.0, 4.0,         2)
  }

  //     num     a     b      c    x1   x2  numOfRoot
  {
    TEST(  5,  0.0,  0.0,   0.0,  0.0, 0.0,        -1)
  }

  #undef TEST
  if (passed) {
    printf("\n==================================\n");
    printf("Tests passed without problems.\n");
  }
}
