#include "cal.h"

Result calMain( Input _input )
{
      //inputs element
      double delta;  // Total Weight , pounds
      double LCG; //Longitudinal Center of Gravity, ft forward of transom
      double VCG; //Vertical Center of Gravity, feet above Baseline
      double b;  // Chine beam length , feet
      double beta;  // Deadrise angle
      double V;  // Speed , foot / sec
      double trim[3];// trim angle2 , 2<=trim<=24

      delta = _input.get_Delta();
      LCG = _input.get_LCG();
      VCG = _input.get_VCG();
      b = _input.get_b();
      beta = _input.get_beta();
      V = _input.get_V();
      trim[0] = _input.get_trim0();
      trim[1] = _input.get_trim1();
      trim[2] = _input.get_trim2();
      //
/*
      //inputs
      cout <<"Please enter the Total Weight(pound) of the boat(delta) : ";
      cin >> delta;
      error(delta);
      cout <<"Please enter the Longitudinal Center of Gravity(ft forward of transom) of the boat(LCG) : ";
      cin >> LCG;
      cout <<"Please enter the Vertical Center of Gravity(feet above baseline) of the boat(VCG) : ";
      cin >> VCG;
      cout <<"Please enter the Chine beam length(feet) of the boat(b) : ";
      cin >> b;
      error(b);
      cout <<"Please enter the Deadrise Angle(Degree) of the boat(beta) : ";
      cin >> beta;
      cout <<"Please enter the Speed(ft/s) of the boat(V) : ";
      cin >> V;
      for(int i=0; i<3; i++){
              cout <<"Please enter trim angle[" << i << "] : " ;
              cin >> trim[i];
              }
      //
*/
      //calculated/other inputs
       double f = 0.5; //Perpendicular Distance off Shaft Line to CG
       double e = 4; //Shaft Angle, from Baseline, degrees
       double a = VCG - ((b/4)*(tan(beta*(pi/180)))); //a = VCG-(b/4)Tan(beta) ,Vertical distance between Df line of action & CG
       double MD = 1.937;  // Mass Density , ((lbf)*(sec^2))/(ft^4)
       double v = 0.000011133;     // kinematic viscosity of water , ft^2 / sec
      // double gamma = MD*g ; // weight density of water , pound / cubic foot
       double deltaCf = 0.0004 ; //ATTC Standard Roughness
            //


            //other calculated inputs
       double Cv = V/(sqrt(g*b)); //Speed Coefficient,  Cv = V / (gb)^1/2 , 0.60<=Cv<=25
       double CLbeta  =  delta / (0.5*(MD)*pow(V,2)*pow(b,2));  //Deadrise Planing Coefficient
       double CLo = Clo(CLbeta, beta);//Planing Coefficient Flat Plate
            //


       //define calculation elements
             double LTR[3] = {0};//Lift Trim Ratio
             double Lamda[3] = {0};//Mean Wetted Length Beam Ratio
             double VmOverV[3] = {0};// Vm/V
             double Vm[3] = {0};//  Average velocity on hull bottom planing surface
             double Re[3] = {0};// Reynold's number
             double Cf[3] = {0};// friction coefficient
             double Df[3] = {0};// Frictional Drag Force
             double D[3] = {0};//Total Horizontal Drag Force
             double Cp[3] = {0};//Center of Pressure Coefficient, Fraction of Mean Wetted Length
             double c[3] = {0};//At equilibrium trim
             double M[3] = {0};//to determining equilibrium trim angle

             //calculation elements
                   for ( int i=0 ; i<3 ; i++){

                       LTR[i] = CLo/(pow(trim[i],1.1));
                       Lamda[i] = lamda( Cv, LTR[i]);
                       VmOverV[i] =  pow((1-((0.012*pow(trim[i],1.1))/(pow(Lamda[i],0.5)*cos(trim[i]*(pi/180)))-(0.000457*beta)*pow(trim[i],0.66)/(pow(Lamda[i],0.34)*cos(trim[i]*(pi/180))))),0.5) ;
                       Vm[i] =  (VmOverV[i])*V;
                       Re[i] =  Vm[i]*Lamda[i]*(b/v);
                       Cf[i] =  0.075/pow((log10(Re[i])-2),2);
                       Df[i] =  ((MD*pow(Vm[i],2)*Lamda[i]*pow(b,2)*(Cf[i]+deltaCf))) / (2*cos(beta*(pi/180))) ;
                       D[i]  =  delta*tan(trim[i]*(pi/180)) + Df[i]/cos(trim[i]*(pi/180));
                       Cp[i] = 0.75 - (1 /(5.21*(pow(Cv,2) )/( pow(Lamda[i],2) ) +2.39 )) ;//Center of Pressure Coefficient, Fraction of Mean Wetted Length
                       c[i] =  LCG - Cp[i]*Lamda[i]*b;
                       M[i] = delta*((1-(sin(trim[i]*(pi/180)))*(sin((trim[i]+e)*(pi/180))))*(c[i]/(cos(trim[i]*(pi/180)))-f*sin(trim[i]*(pi/180))))+Df[i]*(a-f);
                   }
                   //

                   //equilibrium calculation elements

                         double Etrim = etrim( M, trim);
                         double ED = eD(D, trim, Etrim);
                         double EHP = ED*V/550 ;
                         double ELamda = eLamda(Lamda, trim, Etrim) ; //eLamda <= 4
                         //


                         //Length calculation
                               //double Lk = ELamda*b+(b*tan(beta*(pi/180))/(2*pi*tan(Etrim*(pi/180)))) ;// Wetted Keel Length, feet
                               //double Lc = ELamda*b-(b*tan(beta*(pi/180))/(2*pi*tan(Etrim*(pi/180)))) ;// Wetted Chine Length, feet
                               //double d  = Lk*sin(Etrim*(pi/180)) ;//Draft of Keel at Transom, feet


      //Front-end qualifier sub-routine
      Check(trim, ELamda, CLo, Cv);
      //

      //porpoising calculation + check
      double SP = pow(CLbeta/2,0.5); //  Stability Check Parameter
      double Ptrim = ptrim( SP, beta); // trim limit

     return Result( ( Ptrim / Etrim > 1 ) , EHP , Check(trim, ELamda, CLo, Cv) );

/*
      if (Ptrim/etrim >1)
         cout << "\nThe planing boat is stable\n\n";
      else cout << "The planing boat is not stable\n\n";
      //


      //Print power required Output
      cout << "The required power = " << EHP <<"hp"<<endl <<endl;
*/
}




double Clo( double CLbeta, double beta)     //Planing Coefficient Flat Plate
{
      //First Iteration----------------------------------------------------
      double bandwidth = 0.04;
      double CLoi = CLbeta; //Initial Guess for CLo

      // CLbeta = CLo - 0.0065*beta*(CLo)^0.6
      //Parabolic Interpolation
      double y1 = CLoi ;
      double y2 = CLoi+(bandwidth/2) ;
      double y3 = CLoi+bandwidth ;
      double x1 = y1 - 0.0065*beta*pow(y1,0.6) ;
      double x2 = y2 - 0.0065*beta*pow(y2,0.6) ;
      double x3 = y3 - 0.0065*beta*pow(y3,0.6) ;
      double k1 = (x1-x2)/(pow(x2,2)-pow(x1,2)) ;
      double k2 = (y2-y1)/(pow(x2,2)-pow(x1,2)) ;
      double b  = (k2*(pow(x2,2) - pow(x3,2))+y3-y2)/((x3-x2)-(k1)*(pow(x2,2)-pow(x3,2)));
      double a  = b*k1+k2;
      double c  = -b*x2 - a*pow(x2,2)+y2 ;
      double CLo1 = a*pow(CLbeta,2)+b*(CLbeta)+c ;

      //Second Iteration----------------------------------------------------
      bandwidth = 0.001;
      CLoi = CLo1; //Initial Guess for CLo

      // CLbeta = CLo - 0.0065*beta*(CLo)^0.6
      //Parabolic Interpolation
      y1 = CLoi - bandwidth ;
      y2 = CLoi ;
      y3 = CLoi + bandwidth ;
      x1 = y1 - 0.0065*beta*pow(y1,0.6) ;
      x2 = y2 - 0.0065*beta*pow(y2,0.6) ;
      x3 = y3 - 0.0065*beta*pow(y3,0.6) ;
      k1 = (x1-x2)/(pow(x2,2)-pow(x1,2)) ;
      k2 = (y2-y1)/(pow(x2,2)-pow(x1,2)) ;
      b  = (k2*(pow(x2,2) - pow(x3,2))+y3-y2)/((x3-x2)-(k1)*(pow(x2,2)-pow(x3,2)));
      a  = b*k1+k2;
      c  = -b*x2 - a*pow(x2,2)+y2 ;
      double CLo2 = a*pow(CLbeta,2)+b*(CLbeta)+c ;

      //check interpolation-------------------------------------------------
      double e = 0.0001;//Allowable difference
      double CLbeta2 = CLo2 - 0.0065*beta*(pow(CLo2,0.6));

      if ( (CLbeta2 - CLbeta) > e )
         CLo2 = 0;

      return CLo2;
}





double lamda( double Cv, double LTR)  //Mean Wetted Length Beam Ratio
{
       //First Iteration----------------------------------------------------
      double bandwidth = 1.7;
      double lamdai = 2.3; //Initial Guess for lamda

      // LTR = 0.012*lamda^1/2 + 0.0055*lamda^5/2 / Cv^2
      //Parabolic Interpolation
      double y1 = lamdai - bandwidth ;
      double y2 = lamdai ;
      double y3 = lamdai + bandwidth ;
      double x1 = 0.012*(pow(y1,0.5)) + 0.0055*(pow(y1,2.5)) / pow(Cv,2) ;
      double x2 = 0.012*(pow(y2,0.5)) + 0.0055*(pow(y2,2.5)) / pow(Cv,2) ;
      double x3 = 0.012*(pow(y3,0.5)) + 0.0055*(pow(y3,2.5)) / pow(Cv,2) ;
      double k1 = (x1-x2)/(pow(x2,2)-pow(x1,2)) ;
      double k2 = (y2-y1)/(pow(x2,2)-pow(x1,2)) ;
      double b  = (k2*(pow(x2,2) - pow(x3,2))+y3-y2)/((x3-x2)-(k1)*(pow(x2,2)-pow(x3,2)));
      double a  = b*k1+k2;
      double c  = -b*x2 - a*pow(x2,2)+y2 ;
      double lamda1 = a*pow(LTR,2)+b*(LTR)+c ;

      //Second Iteration----------------------------------------------------
      bandwidth = 0.25;
      lamdai = lamda1; //Initial Guess for CLo

      // LTR = 0.012*lamda^1/2 + 0.0055*lamda^5/2 / Cv^2
      //Parabolic Interpolation
      y1 = lamdai - bandwidth ;
      y2 = lamdai ;
      y3 = lamdai + bandwidth ;
      x1 = 0.012*(pow(y1,0.5)) + 0.0055*(pow(y1,2.5)) / pow(Cv,2) ;
      x2 = 0.012*(pow(y2,0.5)) + 0.0055*(pow(y2,2.5)) / pow(Cv,2) ;
      x3 = 0.012*(pow(y3,0.5)) + 0.0055*(pow(y3,2.5)) / pow(Cv,2) ;
      k1 = (x1-x2)/(pow(x2,2)-pow(x1,2)) ;
      k2 = (y2-y1)/(pow(x2,2)-pow(x1,2)) ;
      b  = (k2*(pow(x2,2) - pow(x3,2))+y3-y2)/((x3-x2)-(k1)*(pow(x2,2)-pow(x3,2)));
      a  = b*k1+k2;
      c  = -b*x2 - a*pow(x2,2)+y2 ;
      double lamda2 = a*pow(LTR,2)+b*(LTR)+c ;

      //check interpolation-------------------------------------------------
      double e = 0.0001;//Allowable difference
      double LTR2 = 0.012*(pow(lamda2,1/2)) + 0.0055*(pow(lamda2,5/2)) / pow(Cv,2);

      if ( (LTR2 - LTR) > e )
         lamda2 = 0;

      return lamda2;

}

double etrim(double M[], double trim[] ) //etrim calculation
{
double input = 0;
//Parabolic Interpolation
double y1 = trim[0];
double y2 = trim[1];
double y3 = trim[2];
double x1 = M[0] ;
double x2 = M[1] ;
double x3 = M[2] ;
double k1 = (x1-x2)/(pow(x2,2)-pow(x1,2)) ;
double k2 = (y2-y1)/(pow(x2,2)-pow(x1,2)) ;
double b = (k2*(pow(x2,2) - pow(x3,2))+y3-y2)/((x3-x2)-(k1)*(pow(x2,2)-pow(x3,2)));
double a = b*k1+k2;
double c = -b*x2 - a*pow(x2,2)+y2 ;
double etrim = a*pow(input,2)+b*(input)+c ;
return etrim;
}

double eD(double D[] , double trim[], double etrim) //trim limit calculation
{
      //Parabolic Interpolation
      double y1 = D[0] ;
      double y2 = D[1] ;
      double y3 = D[2] ;
      double x1 = trim[0] ;
      double x2 = trim[1] ;
      double x3 = trim[2] ;
      double k1 = (x1-x2)/(pow(x2,2)-pow(x1,2)) ;
      double k2 = (y2-y1)/(pow(x2,2)-pow(x1,2)) ;
      double b  = (k2*(pow(x2,2) - pow(x3,2))+y3-y2)/((x3-x2)-(k1)*(pow(x2,2)-pow(x3,2)));
      double a  = b*k1+k2;
      double c  = -b*x2 - a*pow(x2,2)+y2 ;
      double eD = a*pow(etrim,2)+b*(etrim)+c ;

      return eD;
}




 double eLamda(double Lamda[] , double trim[], double etrim) //trim limit calculation
{
      //Parabolic Interpolation
      double y1 = Lamda[0] ;
      double y2 = Lamda[1] ;
      double y3 = Lamda[2] ;
      double x1 = trim[0] ;
      double x2 = trim[1] ;
      double x3 = trim[2] ;
      double k1 = (x1-x2)/(pow(x2,2)-pow(x1,2)) ;
      double k2 = (y2-y1)/(pow(x2,2)-pow(x1,2)) ;
      double b  = (k2*(pow(x2,2) - pow(x3,2))+y3-y2)/((x3-x2)-(k1)*(pow(x2,2)-pow(x3,2)));
      double a  = b*k1+k2;
      double c  = -b*x2 - a*pow(x2,2)+y2 ;
      double eLamda = a*pow(etrim,2)+b*(etrim)+c ;

      return eLamda;
}

double ptrim(double SP, double beta) //trim limit calculation
{
      //Parabolic Interpolation
      double y1 = 81.406*pow(SP,2)+ 13.48 *SP -2.1165 ;
      double y2 = 82.399*pow(SP,2)+ 6.1735*SP +0.4566 ;
      double y3 = 72.326*pow(SP,2)+ 10.521*SP +0.7762 ;
      double x1 = 0 ;
      double x2 = 10 ;
      double x3 = 20 ;
      double k1 = (x1-x2)/(pow(x2,2)-pow(x1,2)) ;
      double k2 = (y2-y1)/(pow(x2,2)-pow(x1,2)) ;
      double b  = (k2*(pow(x2,2) - pow(x3,2))+y3-y2)/((x3-x2)-(k1)*(pow(x2,2)-pow(x3,2)));
      double a  = b*k1+k2;
      double c  = -b*x2 - a*pow(x2,2)+y2 ;
      double ptrim = a*pow(beta,2)+b*(beta)+c ;

      return ptrim;
}

string* Check(double trim[], double eLamda, double CLo, double Cv)//Front-end qualifier sub-routine
{
    string* s = new string[6];
    int stringCount = 0;
    int counter = 0;

    for ( int i = 0 ; i < 3 ; i++ )
    {
        if( trim[i] < 2 || trim[i] > 24 )
            counter++;
    }

    if ( counter > 0 )
        s[stringCount++] = "trim angle must be between 2 and 24, please enter again";

    if( eLamda < 0 || eLamda > 4 || eLamda != eLamda )
        s[stringCount++] =  "It is suggested that narrow the range of three trim angle";

    if( CLo == 0 )
        s[stringCount++] =  "Make sure the deadrise angle is between 0 to 30 degrees or try decreasing the input speed";

    if( Cv < 0.6 )
        s[stringCount++] =  "It is suggested to increase the input speed";

    if( Cv > 25 )
        s[stringCount++] =  "It is suggested to decrease the input speed";

    if ( counter > 0 || eLamda < 0 || eLamda > 4 || CLo == 0 || Cv < 0.6 || Cv > 25 || eLamda != eLamda)
        s[stringCount++] =  "There are some invalid inputs, please input again.";

    return s;
/*
     int counter =0 ;


       for(int i=0; i<3; i++){
               if( trim[i] < 2 || trim[i] > 24)
                   counter++;}

                   if ( counter > 0 ){
                   cout << "trim angle must me between 2 and 24, please enter again\n\n";
                   }

               if( eLamda < 0 || eLamda > 4 || eLamda != eLamda )
                   cout << "It is suggested that narrow the range of three trim angle\n\n";

               if( CLo == 0 )
                   cout << "Make sure the deadrise angle is between 0 to 30 degrees or try decreasing the input speed\n\n";

               if( Cv < 0.6 )
                   cout << "It is suggested to increase the input speed\n\n";

               if( Cv > 25 )
                   cout << "It is suggested to decrease the input speed\n\n";

      if ( counter > 0 || eLamda < 0 || eLamda > 4 || CLo == 0 || Cv < 0.6 || Cv > 25 || eLamda != eLamda){
           cout << "There are some invalid inputs, please input again.\n\n\n";
           main();}
*/
}

/*
void error(double x){
               if( x <= 0 ){
          cout <<"wrong input, please input again\n\n\n";
          main();}}
*/
