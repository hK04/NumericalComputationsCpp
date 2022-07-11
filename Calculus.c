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
double sine(double x, double n);
double cosine(double x, double n);

//define natural logarithm
double logarithm(double x, double n);

//define numerical integral
double find_definite_integral(double n, double min__, double max__, double (*function)(double, double));

//define numerical derrivative 
double find_derivative(double x, double n, double(*function)(double, double));

//main function
int main(){ 
    double n = 0;;
    int state, state_2;
    printf("Which sort of operation you would like to proceed?:\n1. Find the Derivative of Function\n2. Find the Definite Integral of Function\n3. Find the Cos(x), Sin(x), Ln(x) or x^n\n");
    scanf("%d", &state);
    switch (state){
    case 1:
        double x;
        printf("For which sort of Function you would like to find Definite Integral?: \n1.Find for the x^n\n2.Find for the Cos(x)\n3.Find for the Sin(x)\n4.Find for the Ln(x)");
        scanf("%d", &state_2);

        switch (state_2){
            case 1:
                printf("Determine power of polynomial dependence:  ");
                scanf("%lf", &n);
                break;
        }
        printf("Determine value of x_0: ");
        scanf("%lf", &x);

        switch (state_2){
            case 1:
                printf("%lf", find_derivative(x, n, power));
                break; 

            case 2:
                printf("%lf", find_derivative(x, n, cosine));
                break;

            case 3:
                printf("%lf", find_derivative(x, n, sine));
                break;

            case 4:
                printf("%lf", find_derivative(x, n, logarithm));
                break;
        }
        break;

    case 2:
        double min__;
        double max__;
        printf("For which sort of Function you would like to find Definite Integral?: \n1.Find for the x^n\n2.Find for the Cos(x)\n3.Find for the Sin(x)\n4.Find for the Ln(x)");
        scanf("%d", &state_2);
        switch (state_2){
            case 1:
                printf("Determine power of polynomial dependence:  ");
                scanf("%lf", &n);
                break;
        }

        printf("\nDetermine mimum:  ");
        scanf("%lf", &min__);
        printf("Determine maximum:  ");
        scanf("%lf", &max__);

        switch (state_2){
            case 1:
                printf("%lf", find_definite_integral(n, min__, max__, power));
                break; 

            case 2:
                printf("%lf", find_definite_integral(n, min__, max__, cosine));
                break;

            case 3:
                printf("%lf", find_definite_integral(n, min__, max__, sine));
                break;

            case 4:
                printf("%lf", find_definite_integral(n, min__, max__, logarithm));
                break;
        }
        break;

    case 3:
        printf("\n1.Find the Cos(x)\n2.Find the Sin(x)\n3.Find the Ln(x)");
        scanf("%d", &state_2);
        switch (state_2){
            case 1:
                double x;
                printf("Determine value of x_0: ");
                scanf("%lf", &x);
                printf("Cos(x) approximately equals: %.3lf", cosine(x, n));
                break;

            case 2:
                printf("Determine value of x_0: ");
                scanf("%lf", &x);
                printf("Sin(x) approximately equals: %.3lf", sine(x, n));
                break;

            case 3:
                printf("Determine value of x_0: ");
                scanf("%lf", &x);
                printf("Ln(x) approximately equals: %.3lf", logarithm(x, n));
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


double sine(double x, double n){
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

double cosine(double x, double n){
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

double logarithm(double x, double n){
    double log__ = 0;
    if (x == 1.0){
        return log__;
    }
    for (int j = 1; j<=2*TAYLOR_SERIES; j++){
        log__ += power(-1, j+1)*power(x-1,j)/j;
    }
    return log__;

}

//integral f(x)dx = SUM(f(x)delta(x), delta(x)--> 0) from min to max
double find_definite_integral(double n, double min__, double max__, double (*function)(double, double)){
    double inte_g = 0;
    double value = min__;
    while (value<=max__){
        inte_g += (function(value,n)*DELTA_OF_DIFFERENTIATION );
        value += DELTA_OF_DIFFERENTIATION ;
    }
    return inte_g;
}

//derivative of f(x) is lim(delta(x) -->o) (f(x+delta(x))-f(x))/delta(x)
double find_derivative(double x, double n, double(*function)(double, double)){
    double der_v = (function(x + DELTA_OF_DIFFERENTIATION , n) - function(x,n)) / DELTA_OF_DIFFERENTIATION ;
    return der_v;
}