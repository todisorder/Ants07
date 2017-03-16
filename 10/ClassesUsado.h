


//static double const parametro = 13.4;
double  parametro = 13.4;




////////////////////////////////////////////////////////
// Class Numerics (data)
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
class Numerics {
    
public:
    int numiter ;
    double xx ;
    double yy ;
    string Comm;
    
    Numerics (){
        xx = numxx;
        yy = numyy;
        cout << "Comments:" << endl;
        getline(cin, Comm, '\n');               // Nice... de http://www.cprogramming.com/tutorial/string.html
//        cout << "// Number of x intervals:" << endl;
//        cin >> numxx ;
//        cout << "// Number of y intervals:" << endl;
//        cin >> numyy ;
        cout << "Number of time iterations:" << endl;
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


#include "Matrix.h"
class Ant;

/********************************************************************/
//					Classe Pheromone
/********************************************************************/
//class Pheromone
//{
//public:
//    //    friend class Ants ;     //Acho que não precisa, só se precisasse de coisas private do Ants;
//    
//    //    Pheromone (Dados);
//    
//    Matrix Density;
//    
//    double DiffPhero;
//    double EvaporationPhero ;                // Vai ser = 1 na dimensionalização; só por completude.
//    //    double * ProductionRatesPhero ;         // Um para cada população!
//    double ProductionRatesPhero ;           // Por agora só um pra todos...
//    
//    Pheromone () {}
//    Pheromone (Numerics par) : Density(par) {}
//    
//    void Update(Matrix& mat);      // This function will only add the values in mat to the
//                                            //      values of Density.
//    
//};
//void Pheromone::Update(Matrix& mat){
//    Pheromone::Density(1,1) = 53.6;
//}
/********************************************************************/
//					END Classe Pheromone
/********************************************************************/

//////////////////////////////////////////////////////////////////////
///////////HH////////////HHH/////////HH///HHHHHHHHHHHHH///////////////
//////////HH/HH//////////HH/HH///////HH////////HH/////////////////////
/////////HH///HH/////////HH//HH//////HH////////HH/////////////////////
////////HH//////HH///////HH///HH/////HH////////HH/////////////////////
////////HH///////HH//////HH////HH////HH////////HH/////////////////////
///////HHHHHHHHHHHH//////HH/////HH///HH////////HH/////////////////////
//////HH//////////HH/////HH//////HH//HH////////HH/////////////////////
/////HH////////////HH////HH///////HH/HH////////HH/////////////////////
/////HH/////////////HH///HH////////HHHH////////HH/////////////////////
////HH///////////////HH//HH//////////HH////////HH/////////////////////
//////////////////////////////////////////////////////////////////////
//     ___      .__   __  .___________.    _______.
//    /   \     |  \ |  | |           |   /       |
//   /  ^  \    |   \|  | `---|  |----`  |   (----`
//  /  /_\  \   |  . `  |     |  |        \   \
// /  _____  \  |  |\   |     |  |    .----)   |
///__/     \__\ |__| \__|     |__|    |_______/
//////////////////////////////////////////////////////////////////////


/********************************************************************/
//					Class Ant
/********************************************************************/
class Ant
{
public:
    
    static double CurrentTime;
    static Matrix Pheromone;
    static int DropletNumber;
    static int DropletNumberToAdd;
    static int InactiveDropletsCount();
    static Matrix DropletTimes;
    static Matrix DropletCentersX;
    static Matrix DropletCentersY;
//    static Matrix DropletAmounts;
                        //  ^^^cf. http://www.tutorialspoint.com/cplusplus/cpp_static_members.htm
                        //  This way (a static Matrix) I don't need the Pheromone class.
                        //  But dx, dy, etc must now be defined in the beggining of the main file.
    
    double AntPosX;
    double AntPosY;
    double AntVelX;
    double AntVelY;
    double AntHomeDirX;
    double AntHomeDirY;
    bool IsReturning;
    Matrix AntDepositedPhero;       // Deprecated! XXXXXXXXX
    string AntFilenamePos;
    string AntFilenameVel;
    ofstream AntFilePos;
    ofstream AntFileVel;
    
    void Walk();
    
    static void BuildPheromone();
    static void UpdatePhero(Matrix& mat);
//    double IndexXOf(double position);     // Compute matrix index i associated to position.
//    double IndexYOf(double position);     // Compute matrix index j associated to position.
    double PheromoneConcentration(double x, double y);        // Evaluate Pheromone at ant position.
    double PheromoneGradientX();
    double PheromoneGradientY();
    double ForceX();
    double ForceY();
    
    //  Constructors
    Ant () : AntDepositedPhero(numxx, numyy){
        AntPosX = 0.;
        AntPosY = 0.;
        AntVelX = -0.7;
        AntVelY = .7;
        IsReturning = false;
    }
    Ant (const double posX, const double posY) : AntDepositedPhero(numxx, numyy){
        AntPosX = posX;
        AntPosY = posY;
        AntVelX = 0.1;
        AntVelY = 0.1;
        IsReturning = false;
    }
    Ant (Numerics data) : AntDepositedPhero(numxx, numyy) {
        AntPosX = 0.;
        AntPosY = 0.;
        AntVelX = 0.;
        AntVelY = 0.;
        IsReturning = false;
        

    }
    //  End Constructors
    
};
double Ant::CurrentTime = 0.;
Matrix Ant::Pheromone = Zeros(numxx,numyy);
int Ant::DropletNumber = 0;
int Ant::DropletNumberToAdd = 0;
//int Ant::InactiveDropletsCount = 0;
Matrix Ant::DropletCentersX = Zeros(LARGE_NUMBER,1);
Matrix Ant::DropletCentersY = Zeros(LARGE_NUMBER,1);
Matrix Ant::DropletTimes = Zeros(LARGE_NUMBER,1);
//Matrix Ant::DropletAmounts = Zeros(LARGE_NUMBER,1);

/********************************************************************/
//					END Class Ant
/********************************************************************/
//					Class Ant Functions
/********************************************************************/
////////////////////////////////////////////////////////////////////////////////////////
//     ___      .__   __. .___________.   ____    __    ____  ___       __       __  ___
//    /   \     |  \ |  | |           |   \   \  /  \  /   / /   \     |  |     |  |/  /
//   /  ^  \    |   \|  | `---|  |----`    \   \/    \/   / /  ^  \    |  |     |  '  /
//  /  /_\  \   |  . `  |     |  |          \            / /  /_\  \   |  |     |    <
// /  _____  \  |  |\   |     |  |           \    /\    / /  _____  \  |  `----.|  .  \
///__/     \__\ |__| \__|     |__|            \__/  \__/ /__/     \__\ |_______||__|\__\
////////////////////////////////////////////////////////////////////////////////////////
//                  Ant::Walk
//              Here goes each iteration calculation.
//////////////////////////////////////////////////////////////////////
void Ant::Walk(){
    double ii = IndexXOf(AntPosX);
    double jj = IndexYOf(AntPosY);
    //  Reset deposited pheromone
//    AntDepositedPhero = 0.*AntDepositedPhero;     // This causes memory leak!!!
//    for (int i=1; i<=numxx; i++) {
//        for (int j=1; j<=numyy; j++) {
//            AntDepositedPhero(i,j) = 0.;
//        }
//    }
    double AntXposNew;
    double AntYposNew;
    double AntVelXNew;
    double AntVelYNew;
    double AntXposOld = AntPosX;
    double AntYposOld = AntPosY;
    double AntVelXOld = AntVelX;
    double AntVelYOld = AntVelY;
    double RandomWalkVelX = 0.;
    double RandomWalkVelY = 0.;
    double RandomWalkVelXnew = RandomWalkVelX;
    double RandomWalkVelYnew = RandomWalkVelY;
    
    double RandomAngle = Uniform(generator);
    double Rzero = SmallNormal(generator);

    ////////////////////////////////////////////////////////
    // Random Walk
    ////////////////////////////////////////////////////////
    
    RandomWalkVelXnew = Rzero * cos(RandomAngle);
    RandomWalkVelYnew = Rzero * sin(RandomAngle);

    ////////////////////////////////////////////////////////
    // End Random Walk
    ////////////////////////////////////////////////////////

    
    ////////////////////////////////////////////////////////
    // Evolution
    ////////////////////////////////////////////////////////

    AntVelXNew = AntVelXOld + delta_t * ( -(1./TAU)*( AntVelXOld - ForceX() - RandomWalkVelXnew * Turn_off_random) );
    
    
    AntVelYNew = AntVelYOld + delta_t * ( -(1./TAU)*( AntVelYOld - ForceY() - RandomWalkVelYnew* Turn_off_random) );

    AntXposNew = AntXposOld + delta_t * (AntVelXNew);
    
    AntYposNew = AntYposOld + delta_t * (AntVelYNew);

    ////////////////////////////////////////////////////////
    // End Evolution
    ////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////
    // PERIODIC Boundary
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
    // End PERIODIC Boundary
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    
    ////////////////////////////////////////////////////////
    // Updating:
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////

    AntPosX = AntXposNew;
    AntPosY = AntYposNew;
    AntVelX = AntVelXNew;
    AntVelY = AntVelYNew;
    
//    AntDepositedPhero(ii,jj) = 0.01;     //  TEMP!!!!!!

    DropletNumberToAdd ++    ;
    
    DropletCentersX(DropletNumber+DropletNumberToAdd,1) = AntPosX;
    DropletCentersY(DropletNumber+DropletNumberToAdd,1) = AntPosY;
    
//    cout <<"Acabo de marcar phero numero " << DropletNumber<< " no ponto (" << AntPosX<<","<<AntPosY<<")"<<endl;
    
    DropletTimes(DropletNumber+DropletNumberToAdd,1) = CurrentTime;

}
//////////////////////////////////////////////////////////////////////
//                  END Ant::Walk
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//                  Ant::PheromoneConcentration
//                  Pointwise evaluation of Pheromone.
//////////////////////////////////////////////////////////////////////

double Ant::PheromoneConcentration(double X, double Y){
    
    double current_time = CurrentTime;
    double elapsed_time = 0.;
    double aux = 0.;
    double aux1 = 0.;
    int Max = MaxActiveDroplets;
    
    for (int droplet=max(1,DropletNumber-Max); droplet < DropletNumber; droplet++) {
        elapsed_time = current_time - DropletTimes(droplet,1);
        aux += Heat(X-DropletCentersX(droplet,1),Y-DropletCentersY(droplet,1),elapsed_time,DropletAmount);
        //  CHANGE to make concentration periodic!! Easy - put this inside 2d loop
        //  ALL this will be computed for EACH point in the sector!
        
    }

    aux1 = 1.*PheroHigh*exp(-PheroNarrow*abs(X));   // To test with given trail!
    int test = TestWithGivenTrail;
//  cout << "Phero: " <<SensitivityFunction(aux) + test*SensitivityFunction(aux1) << endl;
    return SensitivityFunction(aux) + test*SensitivityFunction(aux1);
    
}
//////////////////////////////////////////////////////////////////////
//                  END Ant::PheromoneConcentration
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//                  Ant::PheromoneGradientX
//                  Pointwise evaluation of Pheromone Gradient.
//////////////////////////////////////////////////////////////////////
double Ant::PheromoneGradientX(){       //  NOT NEEDED
    
    double current_time = CurrentTime;
    double elapsed_time = 0.;
    double aux1 = 0.;
    double aux2 = 0.;
    double aux3 = 0.;
    double aux4 = 0.;
    int Max = MaxActiveDroplets;

    for (int droplet=max(1,DropletNumber-Max); droplet < DropletNumber; droplet++) {
        elapsed_time = current_time - DropletTimes(droplet,1);
        aux1 += Heat(AntPosX-DropletCentersX(droplet,1),AntPosY-DropletCentersY(droplet,1),elapsed_time,DropletAmount);
        
        aux3 += -2.*( (AntPosX-DropletCentersX(droplet,1))/(4.*Diffusion*elapsed_time)) * aux1;   //  real gradient
    }
    


    aux4 = - PheroNarrow*PheroHigh*Sinal(AntPosX)*exp(-PheroNarrow*abs(AntPosX));
    
    
//    return aux4;    // To test with given trail!

    int test = TestWithGivenTrail;

    //cout << "grad x: " <<  aux3 + test*aux4 << endl;
    return aux3 + test*aux4;

    
}
//////////////////////////////////////////////////////////////////////
//                  END Ant::PheromoneGradientX
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//                  Ant::PheromoneGradientY
//                  Pointwise evaluation of Pheromone Gradient.
//////////////////////////////////////////////////////////////////////
double Ant::PheromoneGradientY(){       //  NOT NEEDED
//    double aux=0.;
//    double iofXpos = IndexXOf(AntPosX);
//    double jofYpos = IndexYOf(AntPosY);
//    if (jofYpos < numyy) {
//        aux = Pheromone(iofXpos,jofYpos+1) - Pheromone(iofXpos,jofYpos);
//        aux = aux/delta_y;
//    } else {
//        aux = 0.;
//    }
//    return aux;
    double current_time = CurrentTime;
    double elapsed_time = 0.;
    double aux1 = 0.;
    double aux2 = 0.;
    double aux3 = 0.;
    int Max = MaxActiveDroplets;

    for (int droplet=max(1,DropletNumber-Max); droplet < DropletNumber; droplet++) {
        elapsed_time = current_time - DropletTimes(droplet,1);
        aux1 += Heat(AntPosX-DropletCentersX(droplet,1),AntPosY-DropletCentersY(droplet,1),elapsed_time,DropletAmount);
        
        aux3 += -2.*( (AntPosY-DropletCentersY(droplet,1))/(4.*Diffusion*elapsed_time)) * aux1;   //  real gradient

    }
    

    return aux3;
//    return 0.;    // To test with given trail!

    
    
}
//////////////////////////////////////////////////////////////////////
//                  END Ant::PheromoneGradientY
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//._______   ______   .______        ______  _______   ////////////////
//|   ____| /  __  \  |   _  \      /      ||   ____| ////////////////
//|  |__   |  |  |  | |  |_)  |    |  ,----'|  |__    ////////////////
//|   __|  |  |  |  | |      /     |  |     |   __|   ////////////////
//|  |     |  `--'  | |  |\  \----.|  `----.|  |____  ////////////////
//|__|      \______/  | _| `._____| \______||_______| ////////////////
//                                                    ////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//                  Ant::ForceX
//                  Pointwise evaluation of Force (desired velocity).
//////////////////////////////////////////////////////////////////////
double Ant::ForceX(){
    double aux  = 0.;
    double auxX = 0.;
    
    for (int kk=0; kk <= RNumber; kk++) {
        for (int jj=0; jj <= ThetaNumber; jj++) {
            double pointr = DRSector*kk;
            double pointtheta = Angle(AntVelX,AntVelY) - SensingAreaHalfAngle + DThetaSector*jj;
            aux = aux + DRSector * DThetaSector * pointr*cos(pointtheta) * PheromoneConcentration(AntPosX + pointr*cos(pointtheta), AntPosY + pointr*sin(pointtheta)) * pointr*pointr ;
            auxX = auxX + DRSector * DThetaSector * PheromoneConcentration(AntPosX + pointr*cos(pointtheta), AntPosY + pointr*sin(pointtheta)) * pointr*pointr ;
        }
    }
            // FALTA a correção para ser periodico!!!!!!!!!!!!!
    
    aux = aux/auxX;
    
//    cout << "Main X: " << aux << endl;
//    cout << "Angle: " << Angle(AntVelX,AntVelY) << endl;
    return aux;
}
//////////////////////////////////////////////////////////////////////
//                  END Ant::ForceX
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//                  Ant::ForceY
//                  Pointwise evaluation of Force (desired velocity).
//////////////////////////////////////////////////////////////////////
double Ant::ForceY(){
    double aux=0.;
    double auxY=0.;
    
    
    for (int kk=0; kk <= RNumber; kk++) {
        for (int jj=0; jj <= ThetaNumber; jj++) {
            double pointr = DRSector*kk;
            double pointtheta = Angle(AntVelX,AntVelY) - SensingAreaHalfAngle + DThetaSector*jj;
            aux = aux + DRSector * DThetaSector * pointr*sin(pointtheta) * PheromoneConcentration(AntPosX + pointr*cos(pointtheta), AntPosY + pointr*sin(pointtheta)) * pointr*pointr ;
            auxY = auxY + DRSector * DThetaSector * PheromoneConcentration(AntPosX + pointr*cos(pointtheta), AntPosY + pointr*sin(pointtheta)) * pointr*pointr ;
        }
    }
    // FALTA a correção para ser periodico!!!!!!!!!!!!!
    
    aux = aux/auxY;
    
//    cout << "Main Y: " << aux << endl;
    
    return aux;
}
//////////////////////////////////////////////////////////////////////
//                  END Ant::ForceY
//////////////////////////////////////////////////////////////////////



int Ant::InactiveDropletsCount(){
    
    double current_time = CurrentTime;
    double elapsed_time = 0.;
    int aux = 0.;

    for (int droplet=1; droplet < DropletNumber ; droplet++) {
        elapsed_time = current_time - DropletTimes(droplet,1);
   //         cout << "Hii!" << 4.*Pi*Diffusion*current_time*Threshold << endl;
//        cout << exp(-Evaporation*elapsed_time) <<"<=" << 4.*Pi*Diffusion*elapsed_time*Threshold <<"?" <<endl;
        if (exp(-Evaporation*elapsed_time) <= 4.*Pi*Diffusion*elapsed_time*Threshold) {
            aux++;
//            cout << "Hey!" << endl;

        }
        
    }

    return aux;
    
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// __    __  .______    _______       ___   .___________. _______
//|  |  |  | |   _  \  |       \     /   \  |           ||   ____|
//|  |  |  | |  |_)  | |  .--.  |   /  ^  \ `---|  |----`|  |__
//|  |  |  | |   ___/  |  |  |  |  /  /_\  \    |  |     |   __|
//|  `--'  | |  |      |  '--'  | /  _____  \   |  |     |  |____
// \______/  | _|      |_______/ /__/     \__\  |__|     |_______|
//
//.______    __    __   _______ .______        ______
//|   _  \  |  |  |  | |   ____||   _  \      /  __  \
//|  |_)  | |  |__|  | |  |__   |  |_)  |    |  |  |  |
//|   ___/  |   __   | |   __|  |      /     |  |  |  |
//|  |      |  |  |  | |  |____ |  |\  \----.|  `--'  |
//| _|      |__|  |__| |_______|| _| `._____| \______/
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void Ant::UpdatePhero(Matrix& mat){         //  I think this is no longer used...
    //  'mat' is the current ant's deposited pheromone.
    //  Adds the various AntDepositedPhero and then diffuses
    //  the pheromone.
    for (int i=1; i<=numxx; i++) {
        for (int j=1; j<=numyy; j++) {
//            Pheromone(i,j) = (1. - delta_t*0.001)*Pheromone(i,j) + 1.*0.1*mat(i,j);
        }
    }
    
    
}

void Ant::BuildPheromone(){
    double current_time = CurrentTime;
    double elapsed_time = 0.;
    double aux = 0.;

    for (int i=1; i<=numxx; i++) {
        for (int j=1; j<=numyy; j++) {
            aux = 0.;
            for (int droplet=1; droplet < DropletNumber-DropletNumberToAdd; droplet++) {    // Do not read the last droplets, they are deltas.
                elapsed_time = current_time - DropletTimes(droplet,1);
		// cout << "active droplet " << droplet << endl;
                aux += Heat(x_1+i*delta_x-DropletCentersX(droplet,1),y_1+j*delta_y-DropletCentersY(droplet,1),elapsed_time,DropletAmount);
                
            }

            
            Pheromone(i,j) = aux;
            Pheromone(i,j) += TestWithGivenTrail*PheroHigh*exp(-PheroNarrow*abs(x_1+i*delta_x));   // To test with given trail!
        }
    }

    
}




/********************************************************************/
//					END Class Ant Functions
/********************************************************************/




