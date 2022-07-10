#include <stdio.h>
#include <math.h> 
#include <stdint.h> //for usage of unitmax type 

// FROM HERE AND NEXT WE WORK WITH POLYNOMIAL FUNCTION AS X^N 
// Let's use a step of differentiation as DELTA_OF_DIFFERENTIATION  =  0.000001
// For sine and cosine let's computate 15 elements of Taylor series

#define DELTA_OF_DIFFERENTIATION 0.000001 
#define TAYLOR_SERIES 10
#define PI 3.1415 

//define x in power of n
double power(double x, double n);

//define factorial
uintmax_t factorial(uintmax_t n);

//define the sine and cosine
double sine(double x);
double cosine(double x);

//define numerical integral
double find_integral_of_polynomial_function(double n, double min__, double max__);

//define numerical derrivative 
double find_derivative_of_polynomial_function(double x, double n);

//main function
int main(){ 
    double n;
    int state;
    printf("Which sort of operation you would like to proceed?:\n1. Find the Derivative of Polynomial Function\n2. Find the Definite Integral of Polynomial Function\n3. Find the Cos(x) or Sin(x)\n");
    scanf("%d", &state);
    switch (state){
    case 1:
        double x;
        printf("Determine value of x_0: ");
        scanf("%lf", &x);
        printf("Determine power of polynomial dependence: \n");
        scanf("%lf", &n);
        printf("%lf", find_derivative_of_polynomial_function(x, n));
        break;
    case 2:
        double min__;
        double max__;
        printf("Determine power of polynomial dependence: ");
        scanf("%lf", &n);
        printf("\nDetermine mimum:  ");
        scanf("%lf", &min__);
        printf("\nDetermine maximum:  ");
        scanf("%lf", &max__);
        printf("%lf", find_integral_of_polynomial_function(n, min__, max__));
        break;
    case 3:
        int state_2;
        printf("\n1.Find the Cos(x)\n 2.Find the Sin(x)\n");
        scanf("%d", &state_2);
        switch (state_2){
            case 1:
                double x;
                printf("Determine value of x_0: ");
                scanf("%lf", &x);
                printf("Cos(x) approximately equals: %.3lf", cosine(x));
                break;

            case 2:
                printf("Determine value of x_0: ");
                scanf("%lf", &x);
                printf("Sin(x) approximately equals: %.3lf", sine(x));
                break;
    
        }
    }
}

double power(double x, double n){
    double value = 1.0 ;
    for (int i=1; i<=n; i++){
        value *= x;
    }
    for (int i=-1; i>=n; i--)
        value /= x;
    return value;
}

uintmax_t factorial(uintmax_t n){
    if (n==0){
        return 1;
    } 
    else if (n==1){
        return 1;
    }
    else{
        return n*factorial(n-1);
    }
}

//alternative version of factorial what provides better performance with X>2PI (but still only till 3PI)
long double one_n_factorial(int n){
    long double fact = 1.0;
    for (int i=1;i<=n;i++){
        fact /= i;
    }
    return fact;
}

//Taylor series is SUM(f(n)(x0)(x-xo)/n!)
//This implementation work awesome for |x|<=2PI
//Values greater than 2PI require strings-based-arithmetic of usage of CPU's inner blocks
//Or just knowledge, what sin(2pi+x)=sin(x) ;)

double sine(double x){
    //in following code we treat x as it was given in radianes
    double sin__ = 0;
    int i = 1;
    while (x>=2*PI){
        x-=2*PI;
    }
    while (x<=-2*PI){
        x+=2*PI;
    }
    //To deprive ourselfs from lack of understanding i got to note that i'll consider Maclaurin series as Taylor's one (!)
    for (int j = 0; j<=TAYLOR_SERIES; j++){
        sin__ += power(-1, j)*(power(x,2*j+1)*one_n_factorial(2*j+1));
        i += 1;
    }
    return sin__;
}

double cosine(double x){
    double cos__ = 0;
    int i = 1;
    while (x>=2*PI){
        x-=2*PI;
    }
    while (x<=-2*PI){
        x+=2*PI;
    }
    //To deprive ourselfs from lack of understanding i got to note that i'll consider Maclaurin series as Taylor's one (!)
    for (int j = 0; j<=TAYLOR_SERIES; j++){
        cos__ += power(-1, j)*(power(x,2*j)*one_n_factorial(2*j));
        i += 1;
    }
    return cos__;
}

//integral f(x)dx = SUM(f(x)delta(x), delta(x)--> 0) from min to max
double find_integral_of_polynomial_function(double n, double min__, double max__){
    double inte_g = 0;
    double value = min__;
    while (value<=max__){
        inte_g += (power(value,n)*DELTA_OF_DIFFERENTIATION );
        value += DELTA_OF_DIFFERENTIATION ;
    }
    return inte_g;
}

//derivative of f(x) is lim(delta(x) -->o) (f(x+delta(x))-f(x))/delta(x)
double find_derivative_of_polynomial_function(double x, double n){
    double der_v = (power(x + DELTA_OF_DIFFERENTIATION , n) - power(x,n)) / DELTA_OF_DIFFERENTIATION ;
    return der_v;
}