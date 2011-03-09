#ifndef CAL_H
#define CAL_H

#include <cmath>
#include "Input.h"
#include "Result.h"
#include <string>

using namespace std;

const double pi = 3.14159265;
const double g = 32.174; //gravity

Result calMain( Input _input );
double Clo( double , double); //function prototype
double lamda( double , double);
double ptrim( double , double);
double etrim(double[], double[]);
double eD(double[], double[], double);
double eLamda(double[], double[], double);
string* Check( double[] , double , double , double ); //Front-end qualifier sub-routine


//void error( double ); // check if it is <=0

#endif // CAL_H
