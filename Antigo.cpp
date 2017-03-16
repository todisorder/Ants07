# include <fstream> //oi oi oi
# include "stdlib.h"
# include <iostream>
# include <cmath>
# include <string>
#include <sstream>
#include <iomanip>  
#include <random>
#include <chrono>
//ha ha ha 
using namespace std;

#include "matriz.h"
//#include "vector.h"

////////////////////////////////////////////////////////
// Class Numerics (data)
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
class Numerics {
    
public:
    int numiter ;
    double numxx ;
    double numyy ;
    string Comm;
    
    Numerics (){
        cout << "// Comments:" << endl;
        getline(cin, Comm, '\n');               // Nice... de http://www.cprogramming.com/tutorial/string.html
        cout << "// Number of x intervals:" << endl;
        cin >> numxx ;
        cout << "// Number of y intervals:" << endl;
        cin >> numyy ;
        cout << "// Number of time iterations:" << endl;
        cin >> numiter ;
        cin.ignore() ;
        // Because C++!! ver http://stackoverflow.com/questions/12691316/getline-does-not-work-if-used-after-some-inputs
        // … pq o ultimo cin deixa l· um \n que se n„o fizer isto È lido pelo prÛximo getline.
        // Sem isto, sÛ lÍ Comm da 1a vez que È chamado durante a execuÁ„o. Sigh...
    }
    
};
////////////////////////////////////////////////////////
// END Class Numerics (data)
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////


static double const Pi =  3.1415926535;
static double const Ln2 = 0.6931471806;

// obtain a seed from the system clock:
  unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();


default_random_engine generator(seed1);
normal_distribution<double> Normal(0.,1.);      // Normal(0.,1.)
normal_distribution<double> SmallNormal(0.,.05);      // (0.,.05)
uniform_real_distribution<double> Uniform(0.,2.*Pi);      // Uniformly distributed angle
//http://www.cplusplus.com/reference/random/normal_distribution/
// Normal(mean,stddev)
// Usage:
// double number = Normal(generator);
static double const Turn_off_random = 1.*1.;    //*0.02;
//  ^^^ 0. = No Random!

//	Parameter for Regularizing Function
static double const RegularizingEpsilon = 0.01;

//  This is pheromone detection threshold, but not exactly. It's complicated.
static double const Threshold = 0.05; //   Explained in the Readme...   0.1


//////////////////////////////////////////////////////
// Ant parameters
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//  Time scale t_hat em segundos
static double const t_hat_in_seconds = 1.;

//  Space scale X_hat em centimetros
static double const X_hat_in_cm = 1.73;

//  Relaxation time tau em segundos:
static double const tau = .3;         //    0.25

//  Nondimensional relaxation TAU = (t_hat / tau)^(-1).
//  Deve ser o relaxation time nas unidades t_hat.
//  Na equação deve aparecer 1/TAU.
static double const TAU = tau / t_hat_in_seconds;         //

//  Sensing area radius em centimetros
static double const SensingAreaRadius = .6;         //  .5

//  Sensing area radius em X_hat
static double const SENSING_AREA_RADIUS = SensingAreaRadius / X_hat_in_cm;         //

//  Sensing Area Half Angle
static double const SensingAreaHalfAngle = Pi/3.;         //

//  Converter quantidade de feromona numa taxa (velocidade sem espaço). Lambda é 1/(feromona * tempo).
//  A quantidade padrão de feromona dá uma taxa de Lambda / t_hat.
//  Por exemplo, se quando deteta uma quantidade de feromona = 1 ela anda a 2 * X_hat por t_hat, então
//  Lambda seria 2 * (3/2) * (sen theta * ell(em X_hat)^3)^(-1),
//  para que a Velocidade Desejada seja 2. X_hat/t_hat.
//static double const Lambda = .5* (3./2.) *(1./(sin(SensingAreaHalfAngle) * pow(SENSING_AREA_RADIUS,3.)));        //

//  Lambda versao sem sin():
//static double const Lambda = .5* (3./2.) *(1./(1. * pow(SENSING_AREA_RADIUS,3.)));        //

//  Lambda versao só com a media do integral
//static double const Lambda = .5* (3./2.) *(1./(SensingAreaHalfAngle * pow(SENSING_AREA_RADIUS,3.)));        //

//	With Weber's Law, Lambda may be ~ 1 ??
static double const Lambda = 1.;         //10./SENSING_AREA_RADIUS;????

//////////////////////////////////////////////////////
// End Ant parameters
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

// tempo final
//static double const TFINAL = 0.1;
static double const delta_t = 0.05;   //     0.005


////////////////////////////
//  Definição do  Domínio
////////////////////////////
// extremo inferior do intervalo em x (cm)
static double const x_1_cm = -25.;

// extremo superior do intervalo em x (cm)
static double const x_2_cm = 25.;

// extremo inferior do intervalo em y (cm)
static double const y_1_cm =  -50.;

// extremo superior do intervalo em y (cm)
static double const y_2_cm = 50.;

// extremo inferior do intervalo em x
static double const x_1 = x_1_cm / X_hat_in_cm;

// extremo superior do intervalo em x
static double const x_2 = x_2_cm / X_hat_in_cm;

// extremo inferior do intervalo em y
static double const y_1 = y_1_cm / X_hat_in_cm;

// extremo superior do intervalo em y
static double const y_2 = y_2_cm / X_hat_in_cm;

////////////////////////////
// End Definição do  Domínio
////////////////////////////

////////////////////////////
// Parametro temporário para a pheromone
////////////////////////////
static double const PheroNarrow = 1.;
static double const PheroHigh = 1.;
////////////////////////////
// End Parametro temporário para a pheromone
////////////////////////////

////////////////////////////
// Parametro Só para os plots não ficarem
//  com um risco do lado ao outro
//  quando muda de lado por periodicidade
////////////////////////////
int ChangedSide = 0;

string SensitivityMethod;



/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//  Cond. Inicial Position
//  http://stackoverflow.com/questions/10959694/why-does-call-by-value-example-not-modify-input-parameter
//  Preciso do & senão não muda o valor!
/////////////////////////////////////////////////
/////////////////////////////////////////////////
void InitialPosition (double& Xini, double& Yini)
{
    Xini = -5.;     //-5.
    Yini = 0.;      //0.
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//      End Cond. Inicial Position
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//  Cond. Inicial Velocity
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////
void InitialVelocity (double& Vx, double& Vy)
{
    Vx = .1;
    Vy = .1;
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//      End Cond. Inicial Velocity
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////



////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//  Define pheromone trail
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
void define_trail (int xx,int yy, my_matrix trail)
{
    double delta_x;
    delta_x = (x_2-x_1)/xx;
    double delta_y;
    delta_y = (y_2-y_1)/yy;
    double aux = 0.;
    int aux_5 = 5;
    double value = 300.;
    my_matrix temptop(xx,yy); // temptop.matrix("zero");
    double Xpos;
    double Ypos;
    
    
    //    Random trail         // http://www.cplusplus.com/reference/cstdlib/rand/?kw=rand
    ////////////////////////////////////////////////////////
//        srand (time(NULL));
    srand (6);
    for(int i=0;i<xx;i++){
        for(int j=0;j<yy;j++){
            
            aux = rand() % 10 + 10; aux = 1./aux;
//            trail(i,j)=10.*aux - .75;
            trail(i,j)=10.*aux ;
            if (i<aux_5 || i>xx-aux_5 || j<aux_5 || j>yy-aux_5) {
//                trail(i,j)=-0.75;
            }
        }
    }
    for (int l=1; l<=10; l++) {      //l<= 20.   Regularização
        for(int i=1;i<xx-1;i++){
            for(int j=1;j<yy-1;j++){
                trail(i,j)= 0.25*(trail(i-1,j) + trail(i+1,j) + trail(i,j-1) + trail(i,j+1));
            }
        }
        for(int j=1;j<xx-1;j++){    // Na fronteira
//            trail(j,0) = (1./3.)*(trail(j+1,0) + trail(j-1,0) + trail(j,1));
                                    // Periodic
            trail(j,0) = 0.25*(trail(j-1,0) + trail(j+1,0) + trail(j,yy-1) + trail(j,1));
        }
        for(int k=1;k<yy-1;k++){
//            trail(0,k) = (1./3.)*(trail(0,k+1) + trail(0,k-1) + trail(1,k));
            // Periodic
            trail(0,k) = 0.25*(trail(0,k+1) + trail(0,k-1) + trail(xx-1,k) + trail(1,k));
        }
        for(int j=1;j<xx-1;j++){
//            trail(j,yy-1) = (1./3.)*(trail(j+1,yy-1) + trail(j-1,yy-1) + trail(j,yy-2));
            // Periodic
            trail(j,yy-1) = .25*(trail(j+1,yy-1) + trail(j-1,yy-1) + trail(j,0) + trail(j,yy-2));
        }
        for(int k=1;k<yy-1;k++){
//            trail(xx-1,k) = (1./3.)*(trail(xx-1,k+1) + trail(xx-1,k-1) + trail(xx-2,k));
            // Periodic
            trail(xx-1,k) = .25*(trail(xx-1,k+1) + trail(xx-1,k-1) + trail(0,k) + trail(xx-2,k));
        }   // Cantos
        trail(0,0) = 0.5*(trail(1,0) + trail(0,1));
        trail(xx-1,0) = 0.5*(trail(xx-2,0) + trail(xx-1,1));
        trail(0,yy-1) = 0.5*(trail(0,yy-2) + trail(1,yy-1));
        trail(xx-1,yy-1) = 0.5*(trail(xx-2,yy-1) + trail(xx-1,yy-2));
    }
    for(int j=0;j<xx;j++){
        for(int k=0;k<yy;k++){
            
//            trail(j,k) = max(trail(j,k),-0.07);  //-0.02  //-0.035
//            trail(j,k) += 0.07;
//            trail(j,k) *= 14.;
        }
    }
    //   END Random trail
    for(int j=0;j<xx;j++){
        for(int k=0;k<yy;k++){
//            trail(j,k) = 0.;        //Para testar com zero
            Xpos = x_1 + j*delta_x;
            Ypos = y_1 + k*delta_y;
//            trail(j,k) = 1.*exp(-PheroNarrow*abs(Xpos)) * trail(j,k);
            trail(j,k) = 1.*exp(-PheroNarrow*abs(Xpos - 1.*sin(Ypos*0.3))) * trail(j,k);
        }
    }
}

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//  End Define pheromone trail
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////



/////////////////////////////////////////////////
/////////////////////////////////////////////////
//      Fcs úteis
/////////////////////////////////////////////////
/////////////////////////////////////////////////


double PartePositiva(double aa){
    
    return max(aa,0.);
}

double ParteNegativa(double aa){
    
    return - min(aa,0.);
}

//  cf. http://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
double Sinal(double aa){
    if (aa > 0.) return 1.;
    if (aa < 0.) return -1.;
    return 0.;
}

double SensitivityFunction(double c){
    
    double aux;
    
//    aux = c;  SensitivityMethod = "Identity";
    aux = sqrt(c*c + Threshold*Threshold);  SensitivityMethod = "Sqrt(c^2 + c_*^2)";
 //   aux = max(Threshold,c);     SensitivityMethod = "max(c, c_*)";
    
    return aux;
}


/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//  Define Pheromone
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////
double PheromoneConcentration (double Xpos, double Ypos, Numerics data, my_matrix trail)
{
	double delta_x;
    delta_x = (x_2-x_1)/data.numxx;
    double delta_y;
    delta_y = (y_2-y_1)/data.numyy;
    double aux = 0.;

	double iofXpos = (Xpos - x_1)/delta_x;  
	double jofYpos = (Ypos - y_1)/delta_y;
    
	aux = trail(iofXpos,jofYpos);               ////    Ele arredonda por baixo o indice (parte inteira).

//    cout << "iofXpos = " << iofXpos << endl;
//    cout << "jofYpos = " << jofYpos << endl;
//    cout << "trail = " << aux << endl;


//    aux = 1.*exp(-PheroNarrow*abs(Xpos));
    
    aux = SensitivityFunction(aux);   //  See readme...
    
    return aux;

}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//      End Define Pheromone
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////

/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//  Define Pheromone Gradient X
//      Definida como função de (x,y), tenho de dar uma
//      fórmula explícita!
//      Mais tarde, será numérico e vou precisar de interpolações, etc.
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////
double PheromoneGradientX (double Xpos, double Ypos, Numerics data, my_matrix trail)
{
    double aux = 0.;
    double delta_x;
    delta_x = (x_2-x_1)/data.numxx;
    double delta_y;
    delta_y = (y_2-y_1)/data.numyy;
    double iofXpos = (Xpos - x_1)/delta_x;
    double jofYpos = (Ypos - y_1)/delta_y;
    
    if (iofXpos<data.numxx-1) {
        aux =  PheromoneConcentration(Xpos+delta_x,Ypos,data,trail) -  PheromoneConcentration(Xpos,Ypos,data,trail) ;
        aux = aux/delta_x;
    } else {
        aux = 0.;       // TEMP!!
    }

    
    
    
    
//    aux = - 1.*PheroNarrow*Sinal(Xpos)*exp(-PheroNarrow*abs(Xpos));
    
    return aux;
    
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//      End Define Pheromone Gradient X
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////

/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//  Define Pheromone Gradient Y
//      Definida como função de (x,y), tenho de dar uma
//      fórmula explícita!
//      Mais tarde, será numérico e vou precisar de interpolações, etc.
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////
double PheromoneGradientY (double Xpos, double Ypos, Numerics data, my_matrix trail)
{
    double aux = 0.;
    double delta_x;
    delta_x = (x_2-x_1)/data.numxx;
    double delta_y;
    delta_y = (y_2-y_1)/data.numyy;
    double iofXpos = (Xpos - x_1)/delta_x;
    double jofYpos = (Ypos - y_1)/delta_y;
    
    if (jofYpos<data.numyy-1) {
        aux =   PheromoneConcentration(Xpos,Ypos+delta_y,data,trail) - PheromoneConcentration(Xpos,Ypos,data,trail) ;
        aux = aux/delta_y;
    } else {
        aux = 0.;       // TEMP!!
    }


    return aux;
    
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//      End Define Pheromone Gradient Y
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////


/////////////////////////////////////////////////
/////////////////////////////////////////////////
//      Norma de vetor
/////////////////////////////////////////////////
/////////////////////////////////////////////////
double Norm(double X, double Y)
{
    double aux =  sqrt(X*X + Y*Y);
    if (aux <= .000001) {
        return .000001;
    } else {
        return aux;
    }
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//      End Norma de vetor
/////////////////////////////////////////////////
/////////////////////////////////////////////////

/////////////////////////////////////////////////
/////////////////////////////////////////////////
//      Theta de vetor  http://en.cppreference.com/w/cpp/numeric/math/atan2
//      Cuidado que atan2 está entre -Pi/2 e Pi/2,
//      mas acho que isso não tem influencia porque
//      eu só calculo senos e cosenos do angulo,
//      que dariam a mesma coisa se fosse em (0, 2Pi).
//      CUIDADO Usage: atan2(Y,X) = arctan(Y/X) !!!!
/////////////////////////////////////////////////
/////////////////////////////////////////////////
double Angle(double X, double Y)
{
    double aux =  atan2(Y,X);
    return aux;
    
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//      End Theta de vetor
/////////////////////////////////////////////////
/////////////////////////////////////////////////

/////////////////////////////////////////////////
/////////////////////////////////////////////////
//      Radius de vetor  http://en.cppreference.com/w/cpp/numeric/math/hypot
/////////////////////////////////////////////////
/////////////////////////////////////////////////
double Radius(double X, double Y)
{
    double aux =  hypot(X,Y);
    return aux;
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//      End Radius de vetor
/////////////////////////////////////////////////
/////////////////////////////////////////////////


/////////////////////////////////////////////////
/////////////////////////////////////////////////
//      Regularizing Function
/////////////////////////////////////////////////
/////////////////////////////////////////////////
double RegularizingFunction(double X)
{
    double aux =  pow(RegularizingEpsilon*RegularizingEpsilon
				+X*X,0.5);
    return aux;
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//      End Radius de vetor
/////////////////////////////////////////////////
/////////////////////////////////////////////////


/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//       Define Force X,Y coordinates
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////

double ForceX(double AntXpos,double  AntYpos,double  AntVelX, double  AntVelY, Numerics data, my_matrix trail)
{
    double aux;
	double auxX = 1.;
    double N = Norm(AntVelX,AntVelY);
    
    double A11 = sin(2.*SensingAreaHalfAngle)/2.
    * cos(2.*Angle(AntVelX,AntVelY));
    
    double A12 = sin(2.*SensingAreaHalfAngle)/2.
    * sin(2.*Angle(AntVelX,AntVelY));
    
    
    aux = (2./3.) * pow(SENSING_AREA_RADIUS,3.) * Lambda * cos(Angle(AntVelX,AntVelY))
    * PheromoneConcentration(AntXpos,AntYpos,data,trail) * sin(SensingAreaHalfAngle)
    + (1./4.)*pow(SENSING_AREA_RADIUS,4.) * Lambda
    * (SensingAreaHalfAngle * PheromoneGradientX(AntXpos,AntYpos,data,trail)
       + A11 * PheromoneGradientX(AntXpos,AntYpos,data,trail) + A12 * PheromoneGradientY(AntXpos,AntYpos,data,trail))
    ;
    
	auxX = PheromoneConcentration(AntXpos,AntYpos,data,trail)*SENSING_AREA_RADIUS*SENSING_AREA_RADIUS
		* SensingAreaHalfAngle 
        + PheromoneGradientX(AntXpos,AntYpos,data,trail) * (2./3.) * pow(SENSING_AREA_RADIUS,3.)
        * cos(Angle(AntVelX,AntVelY)) * sin(SensingAreaHalfAngle)
        + PheromoneGradientY(AntXpos,AntYpos,data,trail) * (2./3.) * pow(SENSING_AREA_RADIUS,3.)
        * sin(Angle(AntVelX,AntVelY)) * sin(SensingAreaHalfAngle);
	
//	auxX = RegularizingFunction(auxX);
	
	aux = aux/auxX;


//    cout << "PheromoneConcentration="<<PheromoneConcentration(AntXpos,AntYpos) << endl;
//    cout << "A11="<<A11 << endl;
//    cout << "A12="<<A12 << endl;
//    cout << "ForceX="<<aux << endl;
    
    return 1.*aux;
}

double ForceY(double AntXpos,double  AntYpos,double  AntVelX, double  AntVelY, Numerics data, my_matrix trail)
{
    double aux;
    double auxY =1.;
    double N = Norm(AntVelX,AntVelY);
    
    double A22 = - sin(2.*SensingAreaHalfAngle)/2.
    * cos(2.*Angle(AntVelX,AntVelY));
    
    double A21 = sin(2.*SensingAreaHalfAngle)/2.
    * sin(2.*Angle(AntVelX,AntVelY));

    
    aux = (2./3.) *  pow(SENSING_AREA_RADIUS,3.) * Lambda * sin(Angle(AntVelX,AntVelY))
    * PheromoneConcentration(AntXpos,AntYpos,data,trail) * sin(SensingAreaHalfAngle)
    + (1./4.)*pow(SENSING_AREA_RADIUS,4.) * Lambda
    * (SensingAreaHalfAngle * PheromoneGradientY(AntXpos,AntYpos,data,trail)
       + A21 * PheromoneGradientX(AntXpos,AntYpos,data,trail) + A22 * PheromoneGradientY(AntXpos,AntYpos,data,trail))
    ;
    
    auxY = PheromoneConcentration(AntXpos,AntYpos,data,trail)*SENSING_AREA_RADIUS*SENSING_AREA_RADIUS
    * SensingAreaHalfAngle
    + PheromoneGradientX(AntXpos,AntYpos,data,trail) * (2./3.) * pow(SENSING_AREA_RADIUS,3.)
    * cos(Angle(AntVelX,AntVelY)) * sin(SensingAreaHalfAngle)
    + PheromoneGradientY(AntXpos,AntYpos,data,trail) * (2./3.) * pow(SENSING_AREA_RADIUS,3.)
    * sin(Angle(AntVelX,AntVelY)) * sin(SensingAreaHalfAngle);
	
//	auxY = RegularizingFunction(auxY);
	
	aux = aux/auxY;


//    cout << "ForceY="<<aux << endl;
//    cout << "A22="<<A22 << endl;
//    cout << "A21="<<A21 << endl;
//    cout << "Grad X = "<<PheromoneGradientX(AntXpos,AntYpos) << endl;
//    cout << "Grad Y = "<<PheromoneGradientY(AntXpos,AntYpos) << endl;
    
    return 1.*aux;
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//       End Define Force X,Y coordinates
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////



////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//
// Fncs para calcular gradientes, divergencia, Laplaciano, método upwiwnd
//
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
double Dmais(double dx,double uj, double ujj){
    
    return (ujj - uj)/dx;
}


////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//
// End Fncs para calcular gradientes, divergencia, Laplaciano, método upwiwnd
//
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
// Print Info
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
void PrintInfo(double delta_t, string COMM, int tt){
    
    ofstream tempfile;
    tempfile.open("DataUsed.txt");
    string tempinfo;
    
    tempfile << "#############################################################"<<endl;
    tempfile << "#############################################################"<<endl;
    tempfile << "#############################################################"<<endl;
    tempfile <<"# dt = "<< delta_t<< endl;
    tempfile <<"#" << "\t" << COMM <<endl;
    tempfile <<"#" << "Iter: " << tt <<endl;
    tempfile << "------------------------------------------------------" << endl;
    tempfile << "Space scale X_hat_in_cm (cm)       " << X_hat_in_cm << endl;
    tempfile << "Time scale t_hat_in_seconds (sec)       " << t_hat_in_seconds << endl;
    tempfile << "Sensing Area Radius (cm)       " << SensingAreaRadius << endl;
    tempfile << "Sensing Area Radius (X_hat)    " << SENSING_AREA_RADIUS << endl;
    tempfile << "Sensing Half Angle             Pi/" << Pi/SensingAreaHalfAngle << endl;
    tempfile << "Lambda                         " << Lambda << endl;
    tempfile << "------------------------------------------------------" << endl;
    tempfile << "Domain in cm: = [" << x_1_cm <<" , "<< x_2_cm << "] x [" << y_1_cm <<" , "<< y_2_cm << "]" << endl;
    tempfile << "Domain in X_hat: = [" << x_1 <<" , "<< x_2 << "] x [" << y_1 <<" , "<< y_2 << "]" << endl;
    tempfile << "------------------------------------------------------" << endl;
    tempfile << "delta t (seconds) = " << delta_t * t_hat_in_seconds << endl;
    tempfile << "Tfinal (seconds) = " << tt*delta_t * t_hat_in_seconds << endl;
    tempfile << "Tfinal (minutes) = " << tt*delta_t * t_hat_in_seconds / 60.<< endl;
    tempfile << "Tfinal (hours) = " << tt*delta_t * t_hat_in_seconds / 3600.<< endl;
    tempfile << "------------------------------------------------------" << endl;
    tempfile << "Sensitivity Function: "<< SensitivityMethod <<"." << endl;
    tempfile << "------------------------------------------------------" << endl;
    tempfile << " " << endl;
    
    tempfile.close();
    
    system("cp DataUsed.txt temp1.txt");
//    system("cat LogsLast.txt >> LogsData.txt");
    
    ifstream tempfile1;
    tempfile1.open("temp1.txt");
    
    while (getline(tempfile1, tempinfo,'\n'))
    {
        cout << tempinfo << endl;
    }
    
    tempfile1.close();
    
    system("rm temp1.txt");
    
}
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
// End Print Info
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////





////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//                              ////////////////////////
// Método propriamente dito     ////////////////////////
//                              ////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//  http://stackoverflow.com/questions/10959694/why-does-call-by-value-example-not-modify-input-parameter
//  Preciso do & senão não muda o valor!
////////////////////////////////////////////////////////
void AntWalk (int tt, int icurrent, double& AntXposOld, double& AntYposOld, double& AntVelXOld, double& AntVelYOld, Numerics data, my_matrix trail)
{

    // amplitude dos subintervalos em tempo
    double tfinal;
    //    double delta_t;
    tfinal = delta_t * tt;
    //    delta_t = tfinal/tt;
    double Tcurrent = icurrent * delta_t;


    double AntXposNew;
    double AntYposNew;
    double AntVelXNew;
    double AntVelYNew;
    double ForceXvalue;
    double ForceYvalue;
    double RandomWalkVelX = 0.;
    double RandomWalkVelY = 0.;
    double RandomWalkVelXnew = RandomWalkVelX;
    double RandomWalkVelYnew = RandomWalkVelY;
    
    ////////////////////////////////////////////////////////
    // Cálculo das Forças
    ////////////////////////////////////////////////////////
    
    ForceXvalue = ForceX(AntXposOld, AntYposOld, AntVelXOld, AntVelYOld, data, trail);
    ForceYvalue = ForceY(AntXposOld, AntYposOld, AntVelXOld, AntVelYOld, data, trail);
    
    ////////////////////////////////////////////////////////
    // End Cálculo das Forças
    ////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////
    // Cálculo do Random Walk
    //  estou a tentar ver de http://www.caam.rice.edu/~cox/stoch/dhigham.pdf
    ////////////////////////////////////////////////////////
//    int substeps = 20;
//    for (int i=0; i<=substeps; i++) {
//        RandomWalkVelXnew = RandomWalkVelXnew + sqrt(delta_t/substeps)* Normal(generator);
//    }
//    for (int i=0; i<=substeps; i++) {
//        RandomWalkVelYnew = RandomWalkVelYnew + sqrt(delta_t/substeps)* Normal(generator);
//    }
////    RandomWalkVelXnew = RandomWalkVelX + sqrt(delta_t)* Normal(generator);
////            cout << RandomWalkVelXnew << endl;
////
////    RandomWalkVelYnew = RandomWalkVelY + sqrt(delta_t)*Normal(generator);
////            cout << RandomWalkVelYnew << endl;
    
    // Not random walk...
    // rather a random perturbation:
    // Also, it goes inside the 1/tau. It is a change to
    //  the desired velocity.
    double RandomAngle = Uniform(generator);
//    Uniform.reset();
    double Rzero = SmallNormal(generator);
  //  SmallNormal.reset();

    RandomWalkVelXnew = Rzero * cos(RandomAngle);
    RandomWalkVelYnew = Rzero * sin(RandomAngle);
    
    ////////////////////////////////////////////////////////
    // End Cálculo do Random Walk
    ////////////////////////////////////////////////////////
    
    

    ////////////////////////////////////////////////////////
    // Evolução
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////

    //
    AntVelXNew = AntVelXOld + delta_t * ( -(1./TAU)*( AntVelXOld - ForceXvalue - RandomWalkVelXnew * Turn_off_random) );

    
    AntVelYNew = AntVelYOld + delta_t * ( -(1./TAU)*( AntVelYOld - ForceYvalue - RandomWalkVelYnew* Turn_off_random) );

    
    
//  Com relaxação:::
    
//    AntVelXNew = AntVelXOld + delta_t * ( -(1./TAU)*( AntVelXOld - ForceXvalue) )
//    + delta_t * RandomWalkVelXnew * Turn_off_random;
//    
//    AntVelYNew = AntVelYOld + delta_t * ( -(1./TAU)*( AntVelYOld - ForceYvalue) )
//    + delta_t * RandomWalkVelYnew * Turn_off_random;

//  Sem relaxação:::
    
//    AntVelXNew = AntVelXOld + delta_t * ( ForceXvalue )
//    + RandomWalkVelXnew;
//    
//    AntVelYNew = AntVelYOld + delta_t * ( ForceYvalue )
//    + RandomWalkVelYnew;

    AntXposNew = AntXposOld + delta_t * (AntVelXNew);

    AntYposNew = AntYposOld + delta_t * (AntVelYNew);
    
//        cout << "AntVelXNew="<< AntVelXNew << endl;
//        cout << "AntVelYNew="<< AntVelYNew << endl;
    
    
    ////////////////////////////////////////////////////////
    // End Evolução
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////

    
    ////////////////////////////////////////////////////////
    // Fronteira PERIODIC!
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    
    if (AntXposNew <= x_1) {
        AntXposNew = AntXposNew + (x_2 - x_1);
        ChangedSide = 1;
    }
    if (AntXposNew >= x_2) {
        AntXposNew = AntXposNew - (x_2 - x_1);
        ChangedSide = 1;
    }
    if (AntYposNew <= y_1) {
        AntYposNew = AntYposNew + (y_2 - y_1);
        ChangedSide = 1;
    }
    if (AntYposNew >= y_2) {
        AntYposNew = AntYposNew - (y_2 - y_1);
        ChangedSide = 1;
    }

    ////////////////////////////////////////////////////////
    // End Fronteira PERIODIC!
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    

    
    ////////////////////////////////////////////////////////
    // Atualização
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    
    AntXposOld = AntXposNew;

    AntYposOld = AntYposNew;
    
    AntVelXOld = AntVelXNew;
    
    AntVelYOld = AntVelYNew;
    
//    RandomWalkVelX = RandomWalkVelXnew;
//
//    RandomWalkVelY = RandomWalkVelYnew;
//        cout << "dentro  " << AntXposOld << endl;

    ////////////////////////////////////////////////////////
    // Delete Acho que não preciso pq não tenho vetores
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
//        cout << "Hi Force!  " << Radius(ForceXvalue,ForceYvalue) <<endl;
}




////////////////////////////////////////////////////////
// END AntWalk
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////





////////////////////////////////////////////////////////
// Main
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

int main (void){
    
    int tt;
    
    string COMM;
    string DIR;
	double xx, yy;
    
    

    
    int isAbort = 0;
    
//    cout << "// Comments:" << endl;
//    getline(cin, COMM, '\n');               // Nice... de http://www.cprogramming.com/tutorial/string.html
    //    cout << "// Name of Results Folder:" << endl;
    //    getline(cin, DIR, '\n');               // Nice... de http://www.cprogramming.com/tutorial/string.html
    // Pus a escolha da pasta no ficheiro Shell para executar.
//    cout << "// Number of x intervals:" << endl;
//    cin >> xx;
//    cout << "// Number of y intervals:" << endl;
//    cin >> yy;
//    cout << "//  Number of time iterations:" << endl;
//    cin >> tt;
    
    string DIR2 = "./"+DIR+"/";			//	This does nothing! At this point, we have cd'd into the
										//	right folder, in the shell script

    
    double TotalDistanceInCm = 0.;

	Numerics Data;
	xx = Data.numxx;
	yy = Data.numyy;
	tt = Data.numiter;
    double delta_x;
    delta_x = (x_2-x_1)/Data.numxx;
    double delta_y;
    delta_y = (y_2-y_1)/Data.numyy;

    
    my_matrix trail(xx,yy); define_trail(xx,yy,trail);

    ////////////////////////////
    //  Conds Iniciais
    ////////////////////////////
    
    double AntXposOld;
    double AntYposOld;
    InitialPosition(AntXposOld, AntYposOld);

    double AntVelXOld;
    double AntVelYOld;
    InitialVelocity(AntVelXOld, AntVelYOld);
    
//    double RandomWalkVelX = 0.;
//    double RandomWalkVelY = 0.;
    
    ofstream AntPos(DIR2+"AntPos.txt");
    
    AntPos << "###  Units are X_hat = " << X_hat_in_cm << "cm." << endl;
    AntPos << AntXposOld << "\t" << AntYposOld << endl;
    
    ofstream AntVel(DIR2+"AntVel.txt");
    
    AntVel << "###  Units are X_hat = " << X_hat_in_cm << "cm." << endl;
    AntVel << AntVelXOld << "\t" << AntVelYOld << endl;
    
    ofstream AntVelAngle(DIR2+"AntVelAngle.txt");
    
    AntVelAngle << "###  Units are X_hat = " << X_hat_in_cm << "cm." << endl;
    AntVelAngle << Angle(AntVelXOld,AntVelYOld) << endl;
    
    ofstream AntVelRadius(DIR2+"AntVelRadius.txt");
    
    AntVelRadius << "###  Units are X_hat = " << X_hat_in_cm << "cm." << endl;
    AntVelRadius << Radius(AntVelXOld,AntVelYOld) << endl;

    ofstream AntDistance(DIR2+"AntDistance.txt");
    
    AntDistance << "###  Units are X_hat = " << X_hat_in_cm << "cm." << endl;
    AntDistance << 0. <<"\t" << 0. << endl;

    ofstream AntPosX(DIR2+"AntPosX.txt");
    
    AntPosX << "###  Units are X_hat = " << X_hat_in_cm << "cm." << endl;
    AntPosX << 0.<< "\t" << AntXposOld  << endl;

    ofstream AntPosY(DIR2+"AntPosY.txt");
    
    AntPosY << "###  Units are X_hat = " << X_hat_in_cm << "cm." << endl;
    AntPosY << 0.<< "\t" << AntYposOld  << endl;

    /////////////////////////////
    // Ciclo em tempo
    /////////////////////////////
    //Ref:: AntWalk (int tt, double icurrent, double AntXposOld, double AntYposOld, double AntVelXOld, double AntVelYOld)
    
    for (int i=1; i<=tt; i++) {
        
        AntWalk (tt, i, AntXposOld, AntYposOld, AntVelXOld, AntVelYOld, Data, trail);
        
        TotalDistanceInCm = TotalDistanceInCm + delta_t * Radius(AntVelXOld,AntVelYOld)*X_hat_in_cm;
        
        if (i%100 == 0) {   //1000
            cout << "Iter restantes: " << tt - i << endl;
            
            //            if (isnan(AntXposOld)) {
            //                cout <<  "NAN numa iter menor que "<< i << endl;
            //                system("osascript -e 'tell app \"System Events\" to display dialog \"Abort!!!\" with icon 0 with title \"Abort!\" '");
            //                system("sh plot-png.sh");
            //                isAbort = 1;
            //                //abort();
            //                break;
            //            }
            
        }
        if (ChangedSide == 1) {
            AntPos << endl;
            ChangedSide = 0;
        }
        AntPos << AntXposOld << "\t" << AntYposOld << endl;
        AntVel << AntVelXOld << "\t" << AntVelYOld << endl;
        AntVelAngle << Angle(AntVelXOld,AntVelYOld) << endl;
        AntVelRadius << Radius(AntVelXOld,AntVelYOld) << endl;
        AntDistance << i*delta_t << "\t" << TotalDistanceInCm << endl;
        AntPosX << i*delta_t << "\t" << AntXposOld << endl;
        AntPosY << i*delta_t << "\t" << AntYposOld << endl;
    }
    /////////////////////////////
    // End Ciclo em tempo
    /////////////////////////////
    
    

//    cout << "Tfinal  = " << tt*delta_t<< endl;
//    cout << "delta_t = " << delta_t<< endl;
//    cout << "Num Iter = " << tt << endl;

    PrintInfo(delta_t,COMM,tt);
    
    /////////////////////////////
    // Escrever resultados
    /////////////////////////////

//    ofstream outfile_solucao5;
//    outfile_solucao5.open(DIR2+"Trail.txt");
//    for(int j=0;j<xx;j++){
//        for(int k=0;k<yy;k++){
//            outfile_solucao5 << trail(j,k) << "\t";
//            if(k==yy-1)
//                outfile_solucao5 << endl;
//        }
//    }
//    outfile_solucao5.close();
    ofstream outfile_solucao5;
    outfile_solucao5.open(DIR2+"Trail.txt");
    for(int j=0;j<xx;j++){
        for(int k=0;k<yy;k++){
            outfile_solucao5 << x_1 + j*delta_x << "\t"<< y_1 + k*delta_y << "\t" << trail(j,k) << endl;
            if(k==yy-1)
                outfile_solucao5 << endl;
        }
    }
    outfile_solucao5.close();

    
    
    
    
    if (isAbort==1) {
        abort();
    }

    
    cout << COMM << endl;
    cout << "Hi!  " << SENSING_AREA_RADIUS*0.6666*sin(SensingAreaHalfAngle)/SensingAreaHalfAngle <<endl;


    
    return 0;
}





    
    
    
    
    
    
    
    
    




