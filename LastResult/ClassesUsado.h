


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
//    string Method;
    int MethodNumber;
    
    Numerics (){
        xx = numxx;
        yy = numyy;
        bool valid = false;
    
        
        cout << "Comments:" << endl;
        getline(cin, Comm, '\n');               // Nice... de http://www.cprogramming.com/tutorial/string.html
        
        // This while is not needed but now it is a reference.
        while (!valid)
        {
            valid = true; //Assume the cin will be an integer.
            
            cout << "Method:" << endl;
            cout << "1:             nonlocal" << endl;
            cout << "2:             point antennae" << endl;
            cout << "3:             local (linearized)" << endl;
            cin >> MethodNumber;
            
            if(cin.fail()) //cin.fail() checks to see if the value in the cin
                //stream is the correct type, if not it returns true,
                //false otherwise.
            {
//                Put the following in case an integer input is needed.
//                from http://www.cplusplus.com/forum/beginner/26821/
                cin.clear(); //This corrects the stream.
                cin.ignore(); //This skips the left over stream data.
                cout << "Please enter one of the options." << endl;
                valid = false; //The cin was not an integer so try again.
            }
        }
        switch (MethodNumber) {
            case 1:
                Method = "NonlocalOnly";
                break;
            case 2:
                Method = "Deltas";
                break;
            case 3:
                Method = "LocalOnly";
                break;
//            default:
//                Method = "BothMethods";
//                break;
        }
        cout << "Method is: "<< Method << endl;
        
        
        
        
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
    static int CurrentAntNumber;
    static int NumberOfActiveAnts;
    static int DropletNumber;
    static int DropletNumberToAdd;
    static int InactiveDropletsCount();
    static Matrix DropletTimes;
    static Matrix DropletCentersX;
    static Matrix DropletCentersY;
    static Matrix DropletIsActive;    
//    static Matrix DropletAmounts;
                        //  ^^^cf. http://www.tutorialspoint.com/cplusplus/cpp_static_members.htm
                        //  This way (a static Matrix) I don't need the Pheromone class.
                        //  But dx, dy, etc must now be defined in the beggining of the main file.
    
    double AntPosX;
    double AntPosY;
    double AntVelX;
    double AntVelY;
    double AntTurningAngle;
    double AntAngle;
    double AntDistanceX;
    double AntDistanceY;
    double AntDistance;
    double AntPheroL;               // Only for deltas method.
    double AntPheroR;               // Only for deltas method.
    double AntHomeDirX;
    double AntHomeDirY;
    bool AntIsActive;
    bool IsReturning;               // Not yet
    Matrix AntDepositedPhero;       // Deprecated! XXXXXXXXX
    string AntFilenamePos;
    string AntFilenamePosLast;
    string AntFilenameVel;
    string AntFilenamePhase;

    ofstream AntFilePos;
    ofstream AntFilePosLast;
    ofstream AntFileVel;
    ofstream AntFilePhase;

    
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
        AntVelX = -0.1;
        AntVelY = .1;
        AntIsActive = false;
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
int Ant::CurrentAntNumber = 0;
int Ant::NumberOfActiveAnts = 0;
int Ant::DropletNumber = 1;
int Ant::DropletNumberToAdd = 0;
//int Ant::InactiveDropletsCount = 0;
//Matrix Ant::DropletCentersX = Zeros(LARGE_NUMBER,1);
//Matrix Ant::DropletCentersY = Zeros(LARGE_NUMBER,1);
//Matrix Ant::DropletTimes = Zeros(LARGE_NUMBER,1);

Matrix Ant::DropletCentersX = Zeros(MaxActiveDropletsPerAnt,NumberOfAnts);
Matrix Ant::DropletCentersY = Zeros(MaxActiveDropletsPerAnt,NumberOfAnts);
Matrix Ant::DropletTimes = Zeros(MaxActiveDropletsPerAnt,NumberOfAnts);
Matrix Ant::DropletIsActive = Zeros(MaxActiveDropletsPerAnt,NumberOfAnts);


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
    
    double temp = 0.;
    
    string haha = Method;

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

//cout << "current a.n.=" << CurrentAntNumber<< endl;
//cout << "ForceX =" << ForceX() << endl;

    ////////////////////////////////////////////////////////
    // End Evolution
    ////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////
    // Boundary
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    
    if (BorderBehavior == "periodic") {
        
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
    }

    if (BorderBehavior == "respawn") {
        
        if (AntXposNew <= x_1) {
            AntXposNew = 0.;
            AntYposNew = 0.;
            ChangedSide = 1;
        }
        if (AntXposNew >= x_2) {
            AntXposNew = 0.;
            AntYposNew = 0.;
            ChangedSide = 1;
        }
        if (AntYposNew <= y_1) {
            AntXposNew = 0.;
            AntYposNew = 0.;
            ChangedSide = 1;
        }
        if (AntYposNew >= y_2) {
            AntXposNew = 0.;
            AntYposNew = 0.;
            ChangedSide = 1;
        }
    }

    ////////////////////////////////////////////////////////
    // End Boundary
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    
    ////////////////////////////////////////////////////////
    // Updating:
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////

    AntAngle = Angle(AntVelXNew,AntVelYNew);
    AntTurningAngle =  AngleBetween(AntVelXNew,AntVelYNew,AntVelXOld,AntVelYOld);         //Angle(AntVelXNew-AntVelX,AntVelYNew-AntVelY);
    
    AntPosX = AntXposNew;
    AntPosY = AntYposNew;
    AntVelX = AntVelXNew;
    AntVelY = AntVelYNew;
    
    AntDistanceX = AntDistanceX + delta_t * AntVelX;
    AntDistanceY = AntDistanceY + delta_t * AntVelY;
    AntDistance = sqrt(AntDistanceX*AntDistanceX + AntDistanceY*AntDistanceY);
    

    DropletNumberToAdd ++    ;
    
    /*
    DropletCentersX(DropletNumber+DropletNumberToAdd,1) = AntPosX;
    DropletCentersY(DropletNumber+DropletNumberToAdd,1) = AntPosY;
    DropletTimes(DropletNumber+DropletNumberToAdd,1) = CurrentTime;
    */
       
    int index = min(DropletNumber,MaxActiveDropletsPerAnt);
    	//cout << "HERElka=" << index<< endl;
    if (DropletNumber <= MaxActiveDropletsPerAnt){
    	DropletCentersX(index,CurrentAntNumber) = AntPosX;
    	DropletCentersY(index,CurrentAntNumber) = AntPosY;
    	DropletTimes(index,CurrentAntNumber) = CurrentTime;
    
    }          	
    else {
    	for (int ii=1; ii < MaxActiveDropletsPerAnt; ii++){
	    	temp = DropletCentersX(ii+1,CurrentAntNumber);
    		DropletCentersX(ii,CurrentAntNumber) = temp;
    		temp = DropletCentersY(ii+1,CurrentAntNumber);
    		DropletCentersY(ii,CurrentAntNumber) = temp;
    		temp = DropletTimes(ii+1,CurrentAntNumber);
    		DropletTimes(ii,CurrentAntNumber) = temp;
    		//cout << "Fodeu222" << endl;
    	}
    	DropletCentersX(MaxActiveDropletsPerAnt,CurrentAntNumber) = AntPosX;
    	DropletCentersY(MaxActiveDropletsPerAnt,CurrentAntNumber) = AntPosY;
    	DropletTimes(MaxActiveDropletsPerAnt,CurrentAntNumber) = CurrentTime;
    	//cout << "Fodeu222" << endl;
    	
    }
    
    DropletIsActive(index,CurrentAntNumber) = 1.;
//    	DropletIsActive.Print();
//     	DropletTimes.Print();
       
    
   

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
    double distancetodroplet = 0.;
    int Max = MaxActiveDropletsPerAnt;
    int index = 0;
    
//    for (int droplet=max(1,DropletNumber-Max); droplet < DropletNumber; droplet++) {
//       elapsed_time = current_time - DropletTimes(droplet,1);
//     aux += Heat(X-DropletCentersX(droplet,1),Y-DropletCentersY(droplet,1),elapsed_time,DropletAmount);
//   }
        //  CHANGE to make concentration periodic!! Easy - put this inside 2d loop
        //  ALL this will be computed for EACH point in the sector!
       
    for (int antnumber = 1; antnumber <= NumberOfActiveAnts; antnumber++){
        for (int droplet=1; droplet < min(DropletNumber,MaxActiveDropletsPerAnt); droplet++) {
            
            distancetodroplet = sqrt((X - DropletCentersX(droplet,antnumber))*(X - DropletCentersX(droplet,antnumber)) + (Y - DropletCentersY(droplet,antnumber))*(Y - DropletCentersY(droplet,antnumber)));
            if (distancetodroplet <= IgnoreDropletsFartherThan) {
                elapsed_time = current_time - DropletTimes(droplet,antnumber);
                aux += DropletIsActive(droplet,antnumber) * Heat(X-DropletCentersX(droplet,antnumber),Y-DropletCentersY(droplet,antnumber),elapsed_time,DropletAmount);
            }
            // Do not read the last droplets, they are deltas.
        }
    }
    //      NEW!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//    for (int antnumber = 1; antnumber <= NumberOfActiveAnts; antnumber++){
//        for (int droplet=1; droplet < min(DropletNumber,MaxActiveDropletsPerAnt); droplet++) {
//            elapsed_time = current_time - DropletTimes(droplet,antnumber);
//            aux += DropletIsActive(droplet,antnumber) * Heat(X-DropletCentersX(droplet,antnumber),Y-DropletCentersY(droplet,antnumber),elapsed_time,DropletAmount);
//            // Do not read the last droplets, they are deltas.
//        }
//    }
    //      END NEW!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    
// cout << "current a.n.=" << CurrentAntNumber<< endl;
//cout << "pher =" << aux << endl; 

//    aux1 = 1.*PheroHigh*exp(-PheroNarrow*abs(X));   // To test with given trail!
//    if (X <= PheroNarrow) {
//        aux1 = PheroHigh;
//    }
    
    int test = TestWithGivenTrail;
//  cout << "Phero: " <<SensitivityFunction(aux) + test*SensitivityFunction(aux1) << endl;
//    return SensitivityFunction(aux)*(1. - test) + test*SensitivityFunction(aux1);
    return SensitivityFunction(aux)*(1. - test) + test*SensitivityFunction(GivenTrail(X));
   
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
    int Max = MaxActiveDropletsPerAnt;

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
    int Max = MaxActiveDropletsPerAnt;

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
    
    if (Method == "NonlocalOnly") {
        
        for (int kk=0; kk <= RNumber; kk++) {
            for (int jj=0; jj <= ThetaNumber; jj++) {
                double pointr = DRSector*kk;
                double pointtheta = Angle(AntVelX,AntVelY) - SensingAreaHalfAngle + DThetaSector*jj;
                aux = aux + DRSector * DThetaSector * pointr*cos(pointtheta) * PheromoneConcentration(AntPosX + pointr*cos(pointtheta), AntPosY + pointr*sin(pointtheta)) *pointr ;
                auxX = auxX + DRSector * DThetaSector * PheromoneConcentration(AntPosX + pointr*cos(pointtheta), AntPosY + pointr*sin(pointtheta)) * pointr ;
                
            }
        }
        // FALTA a correção para ser periodico!!!!!!!!!!!!!
        
        aux = aux/auxX;

        return LambdaNonlocal * aux;
    }
    
    if (Method == "Deltas") {
        
        double pointr = DRSector*RNumber;
        double pointthetaL = Angle(AntVelX,AntVelY) - SensingAreaHalfAngle;
        double pointthetaR = Angle(AntVelX,AntVelY) + SensingAreaHalfAngle;

        aux = pointr*cos(pointthetaL) * PheromoneConcentration(AntPosX + pointr*cos(pointthetaL), AntPosY + pointr*sin(pointthetaL)) + pointr*cos(pointthetaR) * PheromoneConcentration(AntPosX + pointr*cos(pointthetaR), AntPosY + pointr*sin(pointthetaR)) ;
        auxX = PheromoneConcentration(AntPosX + pointr*cos(pointthetaL), AntPosY + pointr*sin(pointthetaL)) +  PheromoneConcentration(AntPosX + pointr*cos(pointthetaR), AntPosY + pointr*sin(pointthetaR)) ;
        
        AntPheroL = PheromoneConcentration(AntPosX + pointr*cos(pointthetaL), AntPosY + pointr*sin(pointthetaL));
        AntPheroR = PheromoneConcentration(AntPosX + pointr*cos(pointthetaR), AntPosY + pointr*sin(pointthetaR));
        
        // FALTA a correção para ser periodico!!!!!!!!!!!!!
        
        aux = aux/auxX;
        return LambdaDeltas * aux;
    }
    
    
    
    
    
    if (Method == "LocalOnly") {
        
        double A11 = cos(2.*Angle(AntVelX,AntVelY));
        double A12 = sin(2.*Angle(AntVelX,AntVelY));
        
        double MAT11 = 1. + (sin(2.*SensingAreaHalfAngle)/(2.*SensingAreaHalfAngle))
        * A11;
        
        double MAT12 = (sin(2.*SensingAreaHalfAngle)/(2.*SensingAreaHalfAngle))
        * A12;
        
        
        aux = (2./3.) * SENSING_AREA_RADIUS * Lambda * cos(Angle(AntVelX,AntVelY))
        * sin(SensingAreaHalfAngle) / SensingAreaHalfAngle
        + (1./4.)*pow(SENSING_AREA_RADIUS,2.) * Lambda
        * (MAT11*PheromoneGradientX() + MAT12*PheromoneGradientY() ) / PheromoneConcentration(AntPosX,AntPosY);
        
        
        return aux;
    }
    else {
        return 0.;
    }

    
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
    
    
    if (Method == "NonlocalOnly") {
        
        for (int kk=0; kk <= RNumber; kk++) {
            for (int jj=0; jj <= ThetaNumber; jj++) {
                double pointr = DRSector*kk;
                double pointtheta = Angle(AntVelX,AntVelY) - SensingAreaHalfAngle + DThetaSector*jj;
                aux = aux + DRSector * DThetaSector * pointr*sin(pointtheta) * PheromoneConcentration(AntPosX + pointr*cos(pointtheta), AntPosY + pointr*sin(pointtheta)) * pointr ;
                auxY = auxY + DRSector * DThetaSector * PheromoneConcentration(AntPosX + pointr*cos(pointtheta), AntPosY + pointr*sin(pointtheta)) * pointr ;
            }
        }
        // FALTA a correção para ser periodico!!!!!!!!!!!!!
        
        aux = aux/auxY;
        
        return LambdaNonlocal * aux;
    }
    if (Method == "Deltas") {
        
        // FALTA a correção para ser periodico!!!!!!!!!!!!!
        
        double pointr = DRSector*RNumber;
        double pointthetaL = Angle(AntVelX,AntVelY) - SensingAreaHalfAngle;
        double pointthetaR = Angle(AntVelX,AntVelY) + SensingAreaHalfAngle;
        
        aux = pointr*sin(pointthetaL) * PheromoneConcentration(AntPosX + pointr*cos(pointthetaL), AntPosY + pointr*sin(pointthetaL)) + pointr*sin(pointthetaR) * PheromoneConcentration(AntPosX + pointr*cos(pointthetaR), AntPosY + pointr*sin(pointthetaR)) ;
        auxY = PheromoneConcentration(AntPosX + pointr*cos(pointthetaL), AntPosY + pointr*sin(pointthetaL)) +  PheromoneConcentration(AntPosX + pointr*cos(pointthetaR), AntPosY + pointr*sin(pointthetaR)) ;

        
        
        aux = aux/auxY;
        
        return LambdaDeltas * aux;
    }
    
    if (Method == "LocalOnly") {
        
        double A21 = sin(2.*Angle(AntVelX,AntVelY));
        double A22 = - cos(2.*Angle(AntVelX,AntVelY));
        
        double MAT21 = (sin(2.*SensingAreaHalfAngle)/(2.*SensingAreaHalfAngle))
        * A21;
        
        double MAT22 = 1. + (sin(2.*SensingAreaHalfAngle)/(2.*SensingAreaHalfAngle))
        * A22;
        
        aux = (2./3.) * SENSING_AREA_RADIUS * Lambda * sin(Angle(AntVelX,AntVelY))
        * sin(SensingAreaHalfAngle) / SensingAreaHalfAngle
        + (1./4.)*pow(SENSING_AREA_RADIUS,2.) * Lambda
        * (MAT21*PheromoneGradientX() + MAT22*PheromoneGradientY() ) / PheromoneConcentration(AntPosX,AntPosY);
        
        return aux;
    }
    else {
        return 0.;
    }

    
    
    
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

/*    for (int i=1; i<=numxx; i++) {
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
    */
    
        for (int i=1; i<=numxx; i++) {
        for (int j=1; j<=numyy; j++) {
            aux = 0.;
            
			for (int antnumber = 1; antnumber <= NumberOfActiveAnts; antnumber++){
        	for (int droplet=1; droplet < min(DropletNumber,MaxActiveDropletsPerAnt)-1; droplet++) {
        	elapsed_time = current_time - DropletTimes(droplet,antnumber);
        	//cout << "El time" << elapsed_time << endl;
        	aux += DropletIsActive(droplet,antnumber) * Heat(x_1+i*delta_x-DropletCentersX(droplet,antnumber),y_1+j*delta_y-DropletCentersY(droplet,antnumber),elapsed_time,DropletAmount);

     		}   
   		 }
            
            Pheromone(i,j) = aux*(1.-TestWithGivenTrail) + TestWithGivenTrail*GivenTrail(x_1+i*delta_x);
//            Pheromone(i,j) += TestWithGivenTrail*PheroHigh*exp(-PheroNarrow*abs(x_1+i*delta_x));   // To test with given trail!
        }
    }

    
 
}




/********************************************************************/
//					END Class Ant Functions
/********************************************************************/




