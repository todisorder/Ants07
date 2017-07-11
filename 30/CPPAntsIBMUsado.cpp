# include <fstream>
# include "stdlib.h"
# include <iostream>
# include <cmath>
# include <string>
#include <sstream>
#include <iomanip>  
#include <random>
#include <chrono>

using namespace std;

// ASCII art from http://www.kammerl.de/ascii/AsciiSignature.php
/////////////////////////////////////////////////
/////////////////////////////////////////////////
// _______       ___   .___________.    ___
//|       \     /   \  |           |   /   \
//|  .--.  |   /  ^  \ `---|  |----`  /  ^  \
//|  |  |  |  /  /_\  \    |  |      /  /_\  \
//|  '--'  | /  _____  \   |  |     /  _____  \
//|_______/ /__/     \__\  |__|    /__/     \__\
/////////////////////////////////////////////////
/////////////////////////////////////////////////

static string Method;

static double const numxx = 100.;
static double const numyy = 100.;

static int const NumberOfAnts = 50;

static int const LARGE_NUMBER = 1000;    //10000000

static int const MaxActiveDropletsPerAnt = 1000;

static int const TestWithGivenTrail = 0;    // 1=true, 0=false

//static double const Pi = 3.14159;
static double const Pi =  3.1415926535;
static double const Ln2 = 0.6931471806;

// obtain a seed from the system clock:
unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();

default_random_engine generator(seed1);
//default_random_engine generator(3800807093);      // To use same seed as another simulation.
normal_distribution<double> Normal(0.,1.);          // Normal(0.,1.)
normal_distribution<double> SmallNormal(0.,.05);      // (0.,.05)
uniform_real_distribution<double> Uniform(0.,2.*Pi);      // Uniformly distributed angle
uniform_int_distribution<int> UniformInteger(0,20);      // Uniformly distributed integer
//http://www.cplusplus.com/reference/random/normal_distribution/
// Normal(mean,stddev)
// Usage:
// double number = Normal(generator);
static double const Turn_off_random = 0.1*1.;    //*0.02;
//  ^^^ 0. = No Random!

//	Parameter for Regularizing Function
static double const RegularizingEpsilon = 0.01;

//  This is pheromone detection threshold, but not exactly. It's complicated.
static double const Threshold = 0.0001; //   Explained in the Readme...  0.00001


//////////////////////////////////////////////////////
// Ant parameters
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//  Time scale t_hat em segundos
static double const t_hat_in_seconds = 1.;

//  Space scale X_hat em centimetros
static double const X_hat_in_cm = 1.;                  // 1.73;

//  Relaxation time tau em segundos:
static double const tau = .1;         //    0.5

//  Nondimensional relaxation TAU = (t_hat / tau)^(-1).
//  Deve ser o relaxation time nas unidades t_hat.
//  Na equação deve aparecer 1/TAU.
static double const TAU = tau / t_hat_in_seconds;         //

//  Sensing area radius em centimetros
static double const SensingAreaRadius = .8;         //  .4

//  Sensing area radius em X_hat
static double const SENSING_AREA_RADIUS = SensingAreaRadius / X_hat_in_cm;         //

//  Sensing Area Half Angle
static double const SensingAreaHalfAngle = Pi/4.;         //

//	With Weber's Law, Lambda may be ~ 1 ??
static double const Lambda = 1.;         //10./SENSING_AREA_RADIUS;????

//////////////////////////////////////////////////////
// End Ant parameters
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

// tempo final
//static double const TFINAL = 0.1;
static double const delta_t = 0.05;   //     0.05

//  Pheromone Diffusion:
static double const Diffusion = 0.002;      // .0002

//  Pheromone Evaporation:
static double const Evaporation = 0.01;        //0.005

//  How much pheromone each ant deposits... not sure if I want this,
//  or the member vector in the Ant class.
static double const DropletAmountPerUnitTime = 1.*.1*.01;        //0.00001
static double const DropletAmount = DropletAmountPerUnitTime * delta_t;        //0.00001

string SensitivityMethod;

////////////////////////////
//  Definição do  Domínio
////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
// _______   ______   .___  ___.      ___       __  .__   __.
//|       \ /  __  \  |   \/   |     /   \     |  | |  \ |  |
//|  .--.  |  |  |  | |  \  /  |    /  ^  \    |  | |   \|  |
//|  |  |  |  |  |  | |  |\/|  |   /  /_\  \   |  | |  . `  |
//|  '--'  |  `--'  | |  |  |  |  /  _____  \  |  | |  |\   |
//|_______/ \______/  |__|  |__| /__/     \__\ |__| |__| \__|
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
// extremo inferior do intervalo em x (cm)
static double const x_1_cm = -25.;      //-5

// extremo superior do intervalo em x (cm)
static double const x_2_cm = 25.;       //5

// extremo inferior do intervalo em y (cm)
static double const y_1_cm =  -25.;     //-5

// extremo superior do intervalo em y (cm)
static double const y_2_cm = 25.;       //5

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

static double const delta_x = (x_2-x_1)/numxx;;
static double const delta_y = (y_2-y_1)/numyy;;

////////////////////////////
// Parametro temporário para a pheromone
////////////////////////////
static double const PheroNarrow = 5.;
static double const PheroHigh = .02;
////////////////////////////
// End Parametro temporário para a pheromone
////////////////////////////

////////////////////////////
// Nonlocal Sector Discretization parameters
////////////////////////////
static int const RNumber = 5;
static int const ThetaNumber = 5;
static double const DRSector = SENSING_AREA_RADIUS / RNumber;
static double const DThetaSector = 2.* SensingAreaHalfAngle / ThetaNumber;
////////////////////////////
// End Nonlocal Sector Discretization parameters
////////////////////////////



////////////////////////////
//  Parametro Só para os plots não ficarem
//  com um risco do lado ao outro
//  quando muda de lado por periodicidade
////////////////////////////
static int ChangedSide = 0;

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// _______  __    __  .__   __.   ______ .___________. __    ______   .__   __.      _______.
//|   ____||  |  |  | |  \ |  |  /      ||           ||  |  /  __  \  |  \ |  |     /       |
//|  |__   |  |  |  | |   \|  | |  ,----'`---|  |----`|  | |  |  |  | |   \|  |    |   (----`
//|   __|  |  |  |  | |  . `  | |  |         |  |     |  | |  |  |  | |  . `  |     \   \
//|  |     |  `--'  | |  |\   | |  `----.    |  |     |  | |  `--'  | |  |\   | .----)   |
//|__|      \______/  |__| \__|  \______|    |__|     |__|  \______/  |__| \__| |_______/
/////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//                  Auxiliary Functions
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
double IndexXOf(double position){
    double iofXpos = (position - x_1)/delta_x;
    iofXpos = max(1.,iofXpos);
    iofXpos = min(numxx,iofXpos);
    return iofXpos;
}
double IndexYOf(double position){
    double jofYpos = (position - y_1)/delta_y;
    jofYpos = max(1.,jofYpos);
    jofYpos = min(numyy,jofYpos);
    return jofYpos;
}

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
//      Regularizing Function
/////////////////////////////////////////////////
/////////////////////////////////////////////////
double RegularizingFunction(double X)
{
//    double aux =  pow(RegularizingEpsilon*RegularizingEpsilon+X*X,0.5);
    double aux = X;
    return aux;
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//      End Regularizing Function
/////////////////////////////////////////////////
/////////////////////////////////////////////////

/////////////////////////////////////////////////
/////////////////////////////////////////////////
//      Sensitivity Function
/////////////////////////////////////////////////
/////////////////////////////////////////////////
double SensitivityFunction(double c){
    
    double aux;
    
//        aux = c;  SensitivityMethod = "Identity";
    aux = sqrt(c*c + Threshold*Threshold);  SensitivityMethod = "Sqrt(c^2 + c_*^2)";
    //   aux = max(Threshold,c);     SensitivityMethod = "max(c, c_*)";
    
    return aux;
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//      End Sensitivity Function
/////////////////////////////////////////////////
/////////////////////////////////////////////////

/////////////////////////////////////////////////
/////////////////////////////////////////////////
//      Heat Equation fundamental solution
/////////////////////////////////////////////////
/////////////////////////////////////////////////
double Heat(double XX, double YY, double elapsed_time, double amount){
    
    double aux = 0.;
//    cout <<"????? = " << elapsed_time << endl;
    
    aux = (1. / (4.*Pi* Diffusion * elapsed_time));
    aux *= exp(-(XX*XX + YY*YY) / (4.*Diffusion*elapsed_time));
    aux *= exp(-Evaporation*elapsed_time); // Evaporation .001
    aux *= amount;
    
    return aux;
}



/////////////////////////////////////////////////
/////////////////////////////////////////////////
//      END Heat Equation fundamental solution
/////////////////////////////////////////////////
/////////////////////////////////////////////////

/////////////////////////////////////////////////
/////////////////////////////////////////////////
//      Save time step
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
void SaveAnt(double posx, double posy, int icurrent, string ref)
{
    double Tcurrent = icurrent * delta_t;
    
    stringstream sstream_buffer;
    string string_buffer;
    
    // create the filename (using string/stringstream for manipulation of the data that will form the name);
    sstream_buffer.clear();
    //	sstream_buffer << "./" << method_name << "/U_" << fixed << setprecision(6) << t_n  << "___" << n;
    //  	sstream_buffer << ref << "T-" << fixed << setprecision(2) << icurrent  << ".txt";
//    sstream_buffer << ref << "T-" << setfill('0')  << setw(6) << icurrent  << ".txt";
    sstream_buffer << ref << "T-"  << icurrent  << ".txt";
    string_buffer.clear();
    sstream_buffer >> string_buffer;
    
    // create the output stream
    ofstream of_U_n(string_buffer.c_str());
    
//    write all the key->values present the U_n
    
    of_U_n << posx << "\t" << posy << endl;
    
    
//    for(int j=0;j<xx;j++){
//        for(int k=0;k<yy;k++){
//            of_U_n << u1(j,k) << "\t";
//            if(k==yy-1)
//                of_U_n << endl;
//        }
//    }
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//      End Save time step
/////////////////////////////////////////////////
/////////////////////////////////////////////////


//  cf. http://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
double Sinal(double aa){
    if (aa > 0.) return 1.;
    if (aa < 0.) return -1.;
    return 0.;
}



//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//                  END Auxiliary Functions
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


#include "Classes.h"
//#include "matriz.h"
//#include "Matrix.h"



////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
// Print Info
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
void PrintInfo(double delta_t, string COMM, Numerics data){
    
    ofstream tempfile;
    tempfile.open("DataUsed.txt");
    string tempinfo;
    
    double tt = data.numiter ;
    
    tempfile << "#############################################################"<<endl;
    tempfile << "#############################################################"<<endl;
    tempfile << "#############################################################"<<endl;
    tempfile << "# Method is: "<< Method << endl;
    tempfile << "# delta t = "<< delta_t<< endl;
    tempfile << "# relaxation time tau (s) = "<< tau << endl;
    tempfile << "# No. of Iterations = "<< data.numiter << endl;
    tempfile << "# Final Time = "<< data.numiter * delta_t << endl;
    tempfile << "# Comments:" << "\t" << COMM <<endl;
    tempfile << "# X points (for phero visualization only) = "<< data.xx << endl;
    tempfile << "# Y points (for phero visualization only) = "<< data.yy << endl;
    tempfile << "# Radial discretization of sensing area = "<< RNumber << endl;
    tempfile << "# Angle discretization of sensing area = "<< ThetaNumber << endl;
    tempfile << "# Domain Info:" << endl;
    tempfile << "# Domain (Nondimensional)  = [" << x_1 << "," << x_2 << "] x [" << y_1 << "," << y_2 << "]" << endl;
    tempfile << "# Domain (Cm)  = [" << x_1_cm << "," << x_2_cm << "] cm x [" << y_1_cm << "," << y_2_cm << "] cm" << endl;
    tempfile << "------------------------------------------------------" << endl;
    tempfile << "Random is " << Turn_off_random << " times normal strength." << endl;
    tempfile << "------------------------------------------------------" << endl;
    tempfile << "Sensing Area Radius (cm)       	" << SensingAreaRadius << endl;
    tempfile << "Sensing Area Radius (X_hat)    	" << SENSING_AREA_RADIUS << endl;
    tempfile << "Sensing Half Angle             	Pi/" << Pi/SensingAreaHalfAngle << endl;
    tempfile << "Lambda                         	" << Lambda << endl;
    tempfile << "Diffusion                      	" << Diffusion << endl;
    tempfile << "Evaporation                    	" << Evaporation << endl;
    tempfile << "Droplet Amount                 	" << DropletAmount << endl;
    tempfile << "Droplet Amount p/ unit time        " << DropletAmountPerUnitTime << endl;
    tempfile << "Threshold                      	" << Threshold << endl;
    tempfile << "Max Number of active droplets/ant  " << MaxActiveDropletsPerAnt << endl;
    tempfile << "Max Number of active droplets  	" << MaxActiveDropletsPerAnt*NumberOfAnts << endl;
    tempfile << "------------------------------------------------------" << endl;
    tempfile << "delta t (seconds) = " << delta_t * t_hat_in_seconds << endl;
    tempfile << "Tfinal (t hat)    = " << tt*delta_t<< endl;
    tempfile << "Tfinal (seconds)  = " << tt*delta_t * t_hat_in_seconds << endl;
    tempfile << "Tfinal (minutos)  = " << tt*delta_t * t_hat_in_seconds / 60.<< endl;
    tempfile << "Tfinal (horas)    = " << tt*delta_t * t_hat_in_seconds / 3600.<< endl;
    tempfile << "------------------------------------------------------" << endl;
    tempfile << "Seed:  " << seed1 << endl;
    
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



/////////////////////////////////////////
/////////////////////////////////////////
//.___  ___.      ___       __  .__   __.
//|   \/   |     /   \     |  | |  \ |  |
//|  \  /  |    /  ^  \    |  | |   \|  |
//|  |\/|  |   /  /_\  \   |  | |  . `  |
//|  |  |  |  /  _____  \  |  | |  |\   |
//|__|  |__| /__/     \__\ |__| |__| \__|
/////////////////////////////////////////
/////////////////////////////////////////

int main (void){
    
    static double const parametro2 = 532.4;
    
    
    Numerics data;
    int numiter = data.numiter;
    
    int randomnumber;
    
    //////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////

    int NN = NumberOfAnts;
    int totalantnumber = NN;
    
    int ActiveAnts = 1;
    Ant::NumberOfActiveAnts = ActiveAnts;
    
    Ant * Pop;
    Pop = new Ant[NN];
    

    for (int antnumber=0; antnumber < totalantnumber; antnumber++) {
        
        //  Random initial velocities
        Pop[antnumber].AntVelX = 0.1*cos(Normal(generator));
        Pop[antnumber].AntVelY = 0.1*sin(Normal(generator));
        
        Pop[antnumber].AntFilenamePos = "AntPos-"+to_string(antnumber+1)+".txt";
        Pop[antnumber].AntFilePos.open(Pop[antnumber].AntFilenamePos,ofstream::app);
//        cout << Pop[antnumber].AntFilenamePos << endl;
//    }
    
//    for (int antnumber=0; antnumber < totalantnumber; antnumber++) {

//        Pop[antnumber].AntFilenamePosLast = "AntPosLast-"+to_string(antnumber+1)+".txt";
//        Pop[antnumber].AntFilePosLast.open(Pop[antnumber].AntFilenamePosLast,fstream::app);
//        cout << Pop[antnumber].AntFilenamePosLast << endl;
//    }
    
//    for (int antnumber=0; antnumber < totalantnumber; antnumber++) {

        Pop[antnumber].AntFilenameVel = "AntVel-"+to_string(antnumber+1)+".txt";
        Pop[antnumber].AntFileVel.open(Pop[antnumber].AntFilenameVel,ofstream::app);
        
        Pop[antnumber].AntFilenamePhase = "AntPhase-"+to_string(antnumber+1)+".txt";
        Pop[antnumber].AntFilePhase.open(Pop[antnumber].AntFilenamePhase,ofstream::app);
        
        
//        cout << Pop[antnumber].AntFilenameVel << endl;
        
        
        Pop[antnumber].AntFilePos << "#1 AntPos X" << "\t" <<  "#2 AntPos Y" << "\t" <<  "#3 Distance form nest" << "\t" << endl;
        Pop[antnumber].AntFileVel << "#1 AntVel X" << "\t" <<  "#2 AntVel Y" << "\t" <<  "#3 Speed" << "\t" << "#4 Turning Angle Rad" << "\t" << "\t" << "#5 Turning Angle Deg" << "\t" << "#6 Detected Phero Left" << "\t"<< "#7 Detected Phero Right" << "\t" << endl;
        Pop[antnumber].AntFilePhase << "#1 AntPos X" << "\t" << "#2 AntVel X" << "\t" <<  "#3 AntPos Y" << "\t" << "#4 AntVel Y" << "\t" << endl;
        

        if (Pop[antnumber].AntFileVel.is_open())
        {
//            ofs << "lorem ipsum";
            std::cout << "Output operation " << antnumber << " successfully performed\n";
  //          ofs.close();
        }
        else
        {
            std::cout << "Error opening file "<< antnumber << "\n";
        }
    }
    /******
     This is the most stupid shit ever... if I have more than 2 file opening loops above, 
     then the third loop fails after a certain number of opened files, only on Mac!!!!!!
     Whyyy?
    ******/
    
    
    
    
    ofstream AntPos("AntPos.txt");
    AntPos << "###  Units are X_hat = " << X_hat_in_cm << "cm." << endl;
    AntPos << Pop[0].AntPosX << "\t" << Pop[0].AntPosY << endl;

    
    //////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////
    //      MAIN LOOP
    //////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////

    //  Activate one ant
    Pop[0].AntIsActive = true;
    
    //	Start of time cycle
    for (int iter=1; iter <= numiter; iter++) {

        Ant::DropletNumberToAdd = 0;
        Ant::CurrentTime = iter*delta_t;
        
 
        
        for (int antnumber=0; antnumber < totalantnumber; antnumber++) {
            
            Ant::CurrentAntNumber = antnumber+1;
                
            if (Pop[antnumber].AntIsActive) {
                Pop[antnumber].Walk(); //cout << "Fodeuiter"<< iter<< endl;  
            }

            if (ChangedSide == 1) {
                Pop[antnumber].AntFilePos << endl;
                ChangedSide = 0;
            }
            Pop[antnumber].AntFilePos << Pop[antnumber].AntPosX << "\t" << Pop[antnumber].AntPosY << "\t" << sqrt(Pop[antnumber].AntPosX*Pop[antnumber].AntPosX + Pop[antnumber].AntPosY*Pop[antnumber].AntPosY) << endl;
            Pop[antnumber].AntFileVel << Pop[antnumber].AntVelX << "\t" << Pop[antnumber].AntVelY << "\t" << sqrt(Pop[antnumber].AntVelX*Pop[antnumber].AntVelX + Pop[antnumber].AntVelY*Pop[antnumber].AntVelY) << "\t" << Pop[antnumber].AntTurningAngle << "\t" << Pop[antnumber].AntTurningAngle*(180./Pi) << "\t" << Pop[antnumber].AntPheroL << "\t" << Pop[antnumber].AntPheroR << endl;
            Pop[antnumber].AntFilePhase << Pop[antnumber].AntPosX << "\t" << Pop[antnumber].AntVelX << "\t" <<  Pop[antnumber].AntPosY << "\t" << Pop[antnumber].AntVelY << "\t" << endl;


//			SaveAnt(Pop[antnumber].AntPosX, Pop[antnumber].AntPosY, iter, to_string(antnumber));
			   
			
			
			           
        }
        
        //  Decide to activate another ant or not
        
        randomnumber = UniformInteger(generator);
        cout << "Rand: " <<randomnumber << endl;
        if (randomnumber == 1 && ActiveAnts < totalantnumber) {
            Pop[ActiveAnts].AntIsActive = true;
            ActiveAnts++;
            cout << "Activated ant number " << ActiveAnts << endl;
            Ant::NumberOfActiveAnts = ActiveAnts;
        }
        
        
        
        
        //Ant::DropletNumber += Ant::DropletNumberToAdd;
        Ant::DropletNumber++;
        

        AntPos << Pop[0].AntPosX << "\t" << Pop[0].AntPosY << endl;
        
        cout << "Iter: " <<iter << endl;
        cout << "DropletNumber: " << Ant::DropletNumber-1 << endl;
       // cout << "InactiveDropletsCount: " << Ant::InactiveDropletsCount() << endl;
        
    }// End of time cycle
    
    
    // Write last position to a file.
    for (int antnumber=0; antnumber < totalantnumber; antnumber++){
        Pop[antnumber].AntFilePosLast << Pop[antnumber].AntPosX << "\t" << Pop[antnumber].AntPosY << endl;
    }
    
    PrintInfo(delta_t,data.Comm, data);
    
    cout << "Total number of active ants: " << ActiveAnts << "/" << NN << endl;
    
    cout << "Building Pheromone... " << endl;
    Ant::BuildPheromone();

///************   Deprecated:
    ofstream Phero;
    Phero.open("Phero.txt");
    for(int j=1;j<=numxx;j++){
        for(int k=1;k<=numyy;k++){
            Phero << x_1 + j*delta_x << "\t"<< y_1 + k*delta_y << "\t" << Ant::Pheromone(j,k) << endl;
            if(k==numyy)
                Phero << endl;
        }
    }
    Phero.close();
//*/

    
    
    return 0;
}


//	cout << "msg" << endl;


    
    
    
    
    
    
    
    
    




