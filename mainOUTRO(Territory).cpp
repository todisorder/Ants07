
#include <iostream>
#include <fstream>
#include <cmath>
#include <complex>
#include <string>
#include <sstream>
#include <iomanip>

#define BUGG cout<<"Passou aqui!"<<endl;


//#include "Dados.h"
#include "Territory03.h"


using namespace std;

const double pi = 3.14159265358979323846;

int isAbort = 0;

double Dmais(double dx,double uj, double ujj){
    
    return (ujj - uj)/dx ;
}

void Regularizar(int xx, int yy, my_matrix& nest){
    
    my_matrix tempnest(xx,yy); tempnest.set("zero");
    
    for (int l=1; l<=10; l++) {
        for(int i=1;i<xx-1;i++){
            for(int j=1;j<yy-1;j++){
                tempnest(i,j)= 0.2*(nest(i,j) + nest(i-1,j) + nest(i+1,j) + nest(i,j-1) + nest(i,j+1));
            }
        }
        for(int i=1;i<xx-1;i++){
            for(int j=1;j<yy-1;j++){
                nest(i,j)= tempnest(i,j);
            }
        }
    }
}



double Divergencia(double dx, double dy, my_matrix& Matx, my_matrix& Maty, int j, int k, int xx, int yy ){
    double aux = 0. ;
    int jmaisum = j+1 ;
    int jmenosum = j-1 ;
    int kmaisum = k+1 ;
    int kmenosum = k-1 ;
    
    if (j==0) {
        jmenosum = xx - 1 ;
        if (k==0) {
            kmenosum = yy - 1 ;
        }
        if (k==yy-1) {
            kmaisum = 0 ;
        }
    }
    if (j==xx-1) {
        jmaisum = 0 ;
        if (k==0) {
            kmenosum = yy - 1 ;
        }
        if (k==yy-1) {
            kmaisum = 0 ;
        }
    }
    if (k==0) {
        kmenosum = yy - 1 ;
        if (j==0) {
            jmenosum = xx - 1 ;
        }
        if (j==xx-1) {
            jmaisum = 0 ;
        }
    }
    if (k==yy-1) {
        kmaisum = 0 ;
        if (j==0) {
            jmenosum = xx - 1 ;
        }
        if (j==xx-1) {
            jmaisum = 0 ;
        }
    }
    jmaisum = j+1 ;
    jmenosum = j-1 ;
    kmaisum = k+1 ;
    kmenosum = k-1 ;
    
    
    
    
    aux = 0.5 * (((Matx(jmaisum,k) - Matx(jmenosum,k) ) / dx ) + ( Maty(j,kmaisum) - Maty(j,kmenosum) ) / dy) ;
    
    return aux ;
}
double DivergenciaMais(double dx, double dy, my_matrix& Matx, my_matrix& Maty, int j, int k, int xx, int yy ){
    double aux = 0. ;
    int jmaisum = j+1 ;
    int jmenosum = j-1 ;
    int kmaisum = k+1 ;
    int kmenosum = k-1 ;
    
    if (j==0) {
        jmenosum = xx - 1 ;
        if (k==0) {
            kmenosum = yy - 1 ;
        }
        if (k==yy-1) {
            kmaisum = 0 ;
        }
    }
    if (j==xx-1) {
        jmaisum = 0 ;
        if (k==0) {
            kmenosum = yy - 1 ;
        }
        if (k==yy-1) {
            kmaisum = 0 ;
        }
    }
    if (k==0) {
        kmenosum = yy - 1 ;
        if (j==0) {
            jmenosum = xx - 1 ;
        }
        if (j==xx-1) {
            jmaisum = 0 ;
        }
    }
    if (k==yy-1) {
        kmaisum = 0 ;
        if (j==0) {
            jmenosum = xx - 1 ;
        }
        if (j==xx-1) {
            jmaisum = 0 ;
        }
    }
    jmaisum = j+1 ;
    jmenosum = j-1 ;
    kmaisum = k+1 ;
    kmenosum = k-1 ;
    
    
    
    
    aux =  ((Matx(jmaisum,k) - Matx(j,k) ) / dx ) + ( Maty(j,kmaisum) - Maty(j,k) ) / dy ;
    
    return aux ;
}




double Laplaciano(double dx, double dy, my_matrix& Mat, int j, int k, int xx, int yy ){
    double aux = 0. ;
    int jmaisum = j+1 ;
    int jmenosum = j-1 ;
    int kmaisum = k+1 ;
    int kmenosum = k-1 ;
    
    if (j==0) {
        jmenosum = xx - 1 ;
        if (k==0) {
            kmenosum = yy - 1 ;
        }
        if (k==yy-1) {
            kmaisum = 0 ;
        }
    }
    if (j==xx-1) {
        jmaisum = 0 ;
        if (k==0) {
            kmenosum = yy - 1 ;
        }
        if (k==yy-1) {
            kmaisum = 0 ;
        }
    }
    if (k==0) {
        kmenosum = yy - 1 ;
        if (j==0) {
            jmenosum = xx - 1 ;
        }
        if (j==xx-1) {
            jmaisum = 0 ;
        }
    }
    if (k==yy-1) {
        kmaisum = 0 ;
        if (j==0) {
            jmenosum = xx - 1 ;
        }
        if (j==xx-1) {
            jmaisum = 0 ;
        }
    }
    jmaisum = j+1 ;
    jmenosum = j-1 ;
    kmaisum = k+1 ;
    kmenosum = k-1 ;

    
    aux = (Mat(jmaisum,k) - 2.*Mat(j,k) + Mat(jmenosum,k))/(dx*dx) + (Mat(j,kmaisum) - 2.*Mat(j,k) + Mat(j,kmenosum))/(dy*dy) ;
    
    return aux ;
    
}

double Func(double in)
{
//    return 10. * tanh( in ) ;
    return 10. ;
}

void save_time_step(int xx, int yy, double dt, my_matrix u1, int icurrent, string ref)
{
    double Tcurrent = icurrent * dt;
    
    stringstream sstream_buffer;
    string string_buffer;
    
    // create the filename (using string/stringstream for manipulation of the data that will form the name);
    sstream_buffer.clear();
    //	sstream_buffer << "./" << method_name << "/U_" << fixed << setprecision(6) << t_n  << "___" << n;
    //  	sstream_buffer << ref << "T-" << fixed << setprecision(2) << icurrent  << ".txt";
    sstream_buffer << ref << "T-" << setfill('0')  << setw(6) << icurrent  << ".txt";
    string_buffer.clear();
    sstream_buffer >> string_buffer;
    
    // create the output stream
    ofstream of_U_n(string_buffer.c_str());
    
    // write all the key->values present the U_n
//    for(int j=0;j<xx;j++){
//        for(int k=0;k<yy;k++){
//            of_U_n << u1(j,k) << "\t";
//            if(k==yy-1)
//            of_U_n << endl;
//        }
//    }
    // CHEATCHEATCHEATCHEATCHEATCHEATCHEAT!!!
    for(int j=2;j<xx-2;j++){
        for(int k=2;k<yy-2;k++){
            of_U_n << u1(j,k) << "\t";
            if(k==yy-3)
            of_U_n << endl;
        }
    }
    // END CHEATCHEATCHEATCHEATCHEATCHEATCHEAT!!!
}




/********************************************************************/
//					MAIN
/********************************************************************/
int main () {
    
    BUGG

//    OLD:::::
//	/********************************************************************/
//	//			Definir os dados do problema.
//	/********************************************************************/
//	Dados *data = new Dados;
//	data->set ();
//	data->write ();
//	int numpt = data->get_int("numpt");
//	int numiter = data->get_int("numiter");
//	double xmin = data->get_double("xmin");
//	double dx = data->get_double("dx");
//	double dt = data->get_double("dt");
//	double tfinal = data->get_double("tfinal");		
//	double kapa = data->get_double("kapa");
//	double visc = data->get_double("visc");	
	
	
	
//	OLD::::
//	/********************************************************************/
//	//			Nomes de Folders e files
//	//			ATENÇÃO: se as pastas não existirem ele não as cria!!
//	/********************************************************************/
//	string FolderSols = "Miura10000";
//	string FolderErrors = "Miura10000";
//	//	string FolderErrors = "Sols";	
//	string stringSolUU = FolderSols + "/SolUU.txt";
//	string stringSolUUExact = FolderSols + "/SolUUExact.txt";
//	string stringErrUUL2 =  "LOGKDV-Miura10000.txt";
//	string stringErrUULinfty = FolderErrors + "/ErrUULinfty.txt";
//	string stringSolUUMIURA = FolderSols + "/SolUUMIURA.txt";
//	string stringNL2evol = FolderSols + "/NL2evol.txt";	
//	
//	char* FilenameSolUU = new char[stringSolUU.size()+1];
//	strcpy (FilenameSolUU,stringSolUU.c_str());
//	
//	char* FilenameSolUUExact = new char[stringSolUUExact.size()+1];
//	strcpy (FilenameSolUUExact,stringSolUUExact.c_str());
//	
//	char* FilenameErrUUL2 = new char[stringErrUUL2.size()+1];
//	strcpy (FilenameErrUUL2,stringErrUUL2.c_str());
//	
//	char* FilenameErrUULinfty = new char[stringErrUULinfty.size()+1];
//	strcpy (FilenameErrUULinfty,stringErrUULinfty.c_str());
//	
//	char* FilenameSolUUMIURA = new char[stringSolUUMIURA.size()+1];
//	strcpy (FilenameSolUUMIURA,stringSolUUMIURA.c_str());
//
//	char* FilenameNL2evol = new char[stringNL2evol.size()+1];
//	strcpy (FilenameNL2evol,stringNL2evol.c_str());

    
    /********************************************************************/
    //		Ler os dados Numéricos
    /********************************************************************/
    
    
    Numerics Parameters ;           // Basta isto. No construtor em TerritoryXX.h pergunta xx, yy, iter, e comentários.
    cout << "Parameters.numxx = "<< Parameters.numxx <<endl;
    cout << "Parameters.numyy = "<< Parameters.numyy <<endl;
    cout << "Parameters.numiter = "<< Parameters.numiter <<endl;
	/********************************************************************/
	//			Definir uma instancia Pop da classe Ants
	//			Ver TerritoryXX.cpp
	/********************************************************************/
    string line;
    string line2;
    stringstream buffer;
    int NN;
    int counter = 0;
    
    ifstream myfile ("AntData.txt");
    while ( getline(myfile,line) )      //saber numero de pops
    {
        if (line == "Next------>") {
            counter++;
        }
    }
    cout << "Numero de Populações:" << counter << endl ;
//    Ants::NumPops = counter ;
    NN = counter ;
    Ants * Pop ;
    Pop = new Ants [counter]  ;
    
    for (int j=0; j<counter; j++) {
        Pop[j].PeacefulDensity.dim1 = Parameters.numxx ;
        Pop[j].PeacefulDensity.dim2 = Parameters.numyy ;
        Pop[j].AggressiveDensity.dim1 = Parameters.numxx ;
        Pop[j].AggressiveDensity.dim2 = Parameters.numyy ;
        Pop[j].PeacefulDensity.elementos = new double[Parameters.numxx*Parameters.numyy] ;
        Pop[j].AggressiveDensity.elementos = new double[Parameters.numxx*Parameters.numyy] ;
        Pop[j].HomeFieldX.dim1 = Parameters.numxx ;
        Pop[j].HomeFieldX.dim2 = Parameters.numyy ;
        Pop[j].HomeFieldX.elementos = new double[Parameters.numxx*Parameters.numyy] ;
        Pop[j].HomeFieldY.dim1 = Parameters.numxx ;
        Pop[j].HomeFieldY.dim2 = Parameters.numyy ;
        Pop[j].HomeFieldY.elementos = new double[Parameters.numxx*Parameters.numyy] ;
        Pop[j].HomePotential.dim1 = Parameters.numxx ;
        Pop[j].HomePotential.dim2 = Parameters.numyy ;
        Pop[j].HomePotential.elementos = new double[Parameters.numxx*Parameters.numyy] ;
    }       // Porquê esta porcaria? ^^^ Ora, porque como é um apontador não pode ter inicializador
            // e por isso ele não sabe que memória por nos membros do tipo my_matrix.
            // Senão, dá Bus errors e Seg faults arbitrários.
            // Só sei fazer assim. É a vida.
            // Ou seja, gostava que isto estivesse num construtor mas não sei como.

    
    myfile.close();
    myfile.open("AntData.txt");
    int j = 0 ;
    double DiffPhero ;
    double EvaporationPhero ;
    double ProductionRatesPhero ;
    
    printf("População %d ********************************\n", j) ;
    
    while ( getline (myfile,line) )
    {

        if (line == "DiffPhero:") {
            getline(myfile,line2) ;     // Ler proxima linha
            stringstream(line2) >> DiffPhero;
            printf("DiffPhero [%d]------------>%10.5f \n",  j , DiffPhero)  ;
        }
        if (line == "EvaporationPhero:") {
            getline(myfile,line2) ;     // Ler proxima linha
            stringstream(line2) >> EvaporationPhero;
            printf("EvaporationPhero [%d]------------>%10.5f \n",  j , EvaporationPhero)  ;
        }
        if (line == "ProductionRatesPhero:") {
            getline(myfile,line2) ;     // Ler proxima linha
            stringstream(line2) >> ProductionRatesPhero;
            printf("ProductionRatesPhero [%d]------------>%10.5f \n",  j , ProductionRatesPhero)  ;
        }

        if (line == "DiffPeaceful:") {
            getline(myfile,line2) ;     // Ler proxima linha
            stringstream(line2) >> Pop[j].DiffPeaceful;
//            cout << "DiffPeaceful %20d" << j << ":" << Pop[j].DiffPeaceful  << endl ;
            printf("DiffPeaceful [%d]------------>%10.5f \n",  j , Pop[j].DiffPeaceful)  ;
        }
        if (line == "DiffAggressive:") {
            getline(myfile,line2) ;     // Ler proxima linha
            stringstream(line2) >> Pop[j].DiffAggressive;
//            cout << "DiffAggressive " << j << ":" << Pop[j].DiffAggressive  << endl ;
            printf("DiffAggressive [%d]---------->%10.1f \n",  j , Pop[j].DiffAggressive)  ;
        }
        if (line == "SensitPeaceful:") {
            getline(myfile,line2) ;     // Ler proxima linha
            stringstream(line2) >> Pop[j].SensitPeaceful;
//            cout << "SensitPeaceful " << j << ":" << Pop[j].SensitPeaceful  << endl ;
            printf("SensitPeaceful [%d]---------->%10.1f \n",  j , Pop[j].SensitPeaceful)  ;
            
        }
        if (line == "SensitAggressive:") {
            getline(myfile,line2) ;     // Ler proxima linha
            stringstream(line2) >> Pop[j].SensitAggressive;
//            cout << "SensitAggressive " << j << ":" << Pop[j].SensitAggressive  << endl ;
            printf("SensitAggressive[%d]--------->%10.1f \n",  j , Pop[j].SensitAggressive)  ;
        }
        if (line == "SpeedNestPeaceful:") {
            getline(myfile,line2) ;     // Ler proxima linha
            stringstream(line2) >> Pop[j].SpeedNestPeaceful;
//            cout << "SpeedNestPeaceful " << j << ":" << Pop[j].SpeedNestPeaceful  << endl ;
            printf("SpeedNestPeaceful [%d]------->%10.1f \n",  j , Pop[j].SpeedNestPeaceful)  ;
        }
        if (line == "ProductionAggressive:") {
            getline(myfile,line2) ;     // Ler proxima linha
            stringstream(line2) >> Pop[j].ProductionAggressive;
//            cout << "ProductionAggressive " << j << ":" << Pop[j].ProductionAggressive  << endl ;
            printf("ProductionAggressive [%d]---->%10.1f \n",  j , Pop[j].ProductionAggressive)  ;
        }
        if (line == "EvaporationAggressive:") {
            getline(myfile,line2) ;     // Ler proxima linha
            stringstream(line2) >> Pop[j].EvaporationAggressive;
//            cout << "EvaporationAggressive " << j << ":" << Pop[j].EvaporationAggressive  << endl ;
            printf("EvaporationAggressive [%d]--->%10.1f \n",  j , Pop[j].EvaporationAggressive)  ;
        }
        if (line == "DeathByConflict:") {
            getline(myfile,line2) ;     // Ler proxima linha
            stringstream(line2) >> Pop[j].DeathByConflict;
//            cout << "DeathByConflict " << j << ":" << Pop[j].DeathByConflict  << endl ;
            printf("DeathByConflict [%d]--------->%10.1f \n",  j , Pop[j].DeathByConflict)  ;
        }
        if (line == "Nestxx:") {
            getline(myfile,line2) ;     // Ler proxima linha
            stringstream(line2) >> Pop[j].Nestxx;
//            cout << "Nestxx " << j << ":" << Pop[j].Nestxx << endl ;
            printf("Nestxx [%d]------------------>%10.1f \n",  j , Pop[j].Nestxx)  ;
        }
        if (line == "Nestyy:") {
            getline(myfile,line2) ;     // Ler proxima linha
            stringstream(line2) >> Pop[j].Nestyy;
//            cout << "Nestyy" << j << ":" << Pop[j].Nestyy << endl ;
            printf("Nestyy [%d]------------------>%10.1f \n",  j , Pop[j].Nestyy)  ;
        }
        if (line == "TotalPop:") {
            getline(myfile,line2) ;     // Ler proxima linha
            stringstream(line2) >> Pop[j].TotalPop;
//            cout << "TotalPop" << j << ":" << Pop[j].TotalPop << endl ;
            printf("TotalPop [%d]---------------->%10.1f \n",  j , Pop[j].TotalPop)  ;
        }

        if (line == "Next------>") {
            j++ ;
            getline(myfile,line2) ;     // Avança uma linha que posso deixar vazia.
            cout << "\n" ;
            printf("População %d :\n", j) ;
            printf("_______________________________________________\n") ;
        }
        if (line == "Comment:") {
            getline(myfile,line2) ;     // Avança uma linha onde posso comentar com o numero da pop.
        }
        
    }
    
    myfile.close();
    
    /********************************************************************/
    //		Ok, aqui ele já leu os parametros fisicos das pops todas
    //      do ficheiro AntData.txt
    /********************************************************************/

    double xx = Parameters.numxx ;
    double yy = Parameters.numyy ;
    double dt = Parameters.dt ;
    double dx = Parameters.dx ;
    double dy = Parameters.dy ;


    
    /********************************************************************/
    //		Criar a feromona
    /********************************************************************/
    
    cout << "Isto: 11 " << Pop[1].PeacefulDensity.dim1 << endl ;
    Pheromone Phero (Parameters);

//    BUGG
//    Phero.PheromoneDensity.dim1 = Parameters.numxx ;
//    Phero.PheromoneDensity.dim2 = Parameters.numyy ;
//    Phero.PheromoneDensity.elementos = new double[Parameters.numxx*Parameters.numyy] ;
    
    
    
    /********************************************************************/
    //		Definir dados iniciais
    /********************************************************************/

    
    for (int j=0; j<NN; j++) {                      // Ciclo que percorre as pops
        Pop[j].PeacefulDensity.set("zero") ;
        Pop[j].AggressiveDensity.set("zero") ;
        Pop[j].HomeFieldX.set("zero") ;
        Pop[j].HomeFieldY.set("zero") ;
        
        for (int i=0; i<Parameters.numxx; i++) {
            for (int k=0; k<Parameters.numyy; k++) {
                
                Pop[j].HomeFieldX(i,k) = - (i*Parameters.dx - Pop[j].Nestxx) ;
                Pop[j].HomeFieldY(i,k) = - (k*Parameters.dy - Pop[j].Nestyy) ;
                double Norm = sqrt((Pop[j].HomeFieldX(i,k))*(Pop[j].HomeFieldX(i,k))+(Pop[j].HomeFieldY(i,k))*(Pop[j].HomeFieldY(i,k))+0.01*0.01) ;
                Pop[j].HomeFieldX(i,k) /= Norm ;
                Pop[j].HomeFieldY(i,k) /= Norm ;
                
                Pop[j].HomePotential(i,k) = - sqrt( (i*Parameters.dx - Pop[j].Nestxx)*(i*Parameters.dx - Pop[j].Nestxx) + (k*Parameters.dy - Pop[j].Nestyy)*(k*Parameters.dy - Pop[j].Nestyy) + 0.01*0.01 ) ;
                
            }
        }
    }
    for (int j=0; j<NN; j++) {                      // Ciclo que percorre as pops
        
        int nestindexx = 0 ;
        int nestindexy = 0 ;
        nestindexx = Pop[j].Nestxx / Parameters.dx ;
        nestindexy = Pop[j].Nestyy / Parameters.dy ;
        
        printf("nestindexx: %d, %d  \n", nestindexx, nestindexy) ;

        
        Pop[j].PeacefulDensity(nestindexx,nestindexy) = Pop[j].TotalPop / (Parameters.dx * Parameters.dy) ;
//        Pop[j].PeacefulDensity(nestindexx,nestindexy) = 2. ;
        
//        Pop[j].PeacefulDensity = Regularizar(xx, yy, Pop[j].PeacefulDensity) ;
        Regularizar(xx, yy, Pop[j].PeacefulDensity) ;
        
//        my_matrix tempnest(xx,yy); tempnest.set("zero");
//        
//        for (int l=1; l<=20; l++) {
//            for(int i=1;i<xx-1;i++){
//                for(int k=1;k<yy-1;k++){
//                    tempnest(i,k)= 0.25*(Pop[j].PeacefulDensity(i-1,k) + Pop[j].PeacefulDensity(i+1,k) + Pop[j].PeacefulDensity(i,k-1) + Pop[j].PeacefulDensity(i,k+1));
//                }
//            }
//            for(int i=1;i<xx-1;i++){
//                for(int k=1;k<yy-1;k++){
//                    Pop[j].PeacefulDensity(i,k)= tempnest(i,k);
//                }
//            }
//        }


        
        for (int i=0; i<Parameters.numxx; i++) {        // Ou dado inicial á mão
            for (int k=0; k<Parameters.numyy; k++) {
//                Pop[j].PeacefulDensity(i,k) = 0. ;
            }
        }

    }
    
    
    Phero.PheromoneDensity.set("zero") ;        // Definir tb os outros membros de Phero!
    Phero.DiffPhero = DiffPhero ;
    Phero.ProductionRatesPhero = ProductionRatesPhero ;
    Phero.EvaporationPhero = EvaporationPhero ;
    
    
//    cout << "Isto: 11 " << Pop[1].PeacefulDensity.dim1 << endl ;
//    cout << "Isto: 1AAAAAFHH! " << Phero.PheromoneDensity.dim1 << endl ;
//    BUGG
    
    
	/********************************************************************/
	//			Main loop
	/********************************************************************/
    int numiter = 0;
    numiter = Parameters.numiter ;
    
//    cout << " phero.PheromoneDensity(1,1) = ????   " <<    Phero.PheromoneDensity(1,1)  << endl ;
//    BUGG
//    cout << "Isto: ha " << Parameters.numiter << endl ;
    
    Ants * PopAux ;
    Ants PopAux2 ;
    PopAux = new Ants[NN];
    for (int j=0; j<NN; j++) {
        PopAux[j].PeacefulDensity.dim1 = Parameters.numxx ;
        PopAux[j].PeacefulDensity.dim2 = Parameters.numyy ;
        PopAux[j].AggressiveDensity.dim1 = Parameters.numxx ;
        PopAux[j].AggressiveDensity.dim2 = Parameters.numyy ;
        PopAux[j].PeacefulDensity.elementos = new double[Parameters.numxx*Parameters.numyy] ;
        PopAux[j].AggressiveDensity.elementos = new double[Parameters.numxx*Parameters.numyy] ;
        PopAux[j].HomeFieldX.dim1 = Parameters.numxx ;
        PopAux[j].HomeFieldX.dim2 = Parameters.numyy ;
        PopAux[j].HomeFieldX.elementos = new double[Parameters.numxx*Parameters.numyy] ;
        PopAux[j].HomeFieldY.dim1 = Parameters.numxx ;
        PopAux[j].HomeFieldY.dim2 = Parameters.numyy ;
        PopAux[j].HomeFieldY.elementos = new double[Parameters.numxx*Parameters.numyy] ;
        PopAux[j].HomePotential.dim1 = Parameters.numxx ;
        PopAux[j].HomePotential.dim2 = Parameters.numyy ;
        PopAux[j].HomePotential.elementos = new double[Parameters.numxx*Parameters.numyy] ;

    }       // Porquê esta porcaria? ^^^ Ora, porque como é um apontador não pode ter inicializador
    // e por isso ele não sabe que memória por nos membros do tipo my_matrix.
    // Senão, dá Bus errors e Seg faults arbitrários.
    // Só sei fazer assim. É a vida.
    // Ou seja, gostava que isto estivesse num construtor mas não sei como.

    //      Inicializar PopAux com as várias populações.
    for (int j=0; j<NN; j++) {
        PopAux[j] = Pop[j];
    }           // Demorei HORAS a fazer isto, que queria que fosse simplesmente criar uma cópia de Pop!!!!!!!!
                // Não posso usar o overload (i,j) do matriz.h no assignment constructor em TerritoryXX.cpp; Não sei porquê.
                // Tenho de repetir aqui acima esta inicialização à mão de PopAux, não sei porquê.
                // Enfim, quem inventou esta linguagem...........!
    
//    printf("PARA VERRRRRR 0: %f,  \n", Pop[1].ProductionAggressive) ;
//    printf("PARA VERRRRRR 1: %f,  \n", PopAux[1].ProductionAggressive) ;
//    printf("PARA VERRRRRR 2: %f,  \n", Pop[1].PeacefulDensity(1,1)) ;
//    printf("PARA VERRRRRR 3: %f,  \n", PopAux[1].PeacefulDensity(1,1)) ;
//    printf("PARA VERRRRRR 0: %f,  \n", Pop[1].HomeFieldX(1,1)) ;
//    printf("PARA VERRRRRR AUX HF: %f,  \n", PopAux[1].HomeFieldX(1,1)) ;
//    PopAux[1].HomeFieldX(2,1) = 35. ;
//        printf("PARA VERRRRRR 2: %f,  \n", Laplaciano(0.1, PopAux[1].HomeFieldX, 1, 1)) ;
    
//    cout << "OLHA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " << PopAux[2].PeacefulDensity.dim1 << endl ;
//    cout << "OLHA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " << PopAux[2].PeacefulDensity(2,2) << endl ;
//    PopAux[2].PeacefulDensity(2,2) = 34. ;
//    cout << "OLHA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " << PopAux[2].PeacefulDensity(2,2) << endl ;
//    cout << "OLHA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " << Pop[2].PeacefulDensity(2,2) << endl ;
////    Pop[2].PeacefulDensity(2,2) = PopAux[2].PeacefulDensity(2,2) ;
//    cout << "OLHA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " << Pop[2].PeacefulDensity(2,2) << endl ;
    
    
    printf("Parametros: dt: %e, dx: %f, dy: %f \n", dt,dx,dy) ;


    
    for (int i=1; i<=numiter ; i++) {           // Cada iteração
        
        my_matrix auxmatPhero(xx,yy) ; auxmatPhero.set("zero") ;
        my_matrix auxmatPheroProd(xx,yy) ; auxmatPheroProd.set("zero") ;
        for (int j=0; j<Parameters.numxx; j++) {      // Copiar feromona
            for (int k=0; k<Parameters.numyy; k++) {
                auxmatPhero(j,k) = Phero.PheromoneDensity(j,k) ;
            }
        }

        
        
        for (int popcurr=0; popcurr<NN; popcurr++) {              // Cada população
//            Pop[popcurr].TimeStep(Parameters, Phero, NN);						//  Evolução
//            PopAux->TimeStep(Parameters, Phero, popcurr, NN);						//  Evolução - Para poder usar as outras pops!

            /********************************************************************/
            //				OLHA Só!!!
            //              Vou antes fazer tudo neste ficheiro. Tipo
            //              Pop[popcurr].PeacefulDensity(k,l) =  ...fórmula com RHS PopAux[j,k,i,...].PeacefulDensity(k,l)
            //              (Ou vice versa!)
            //              no final, PopAux[popcurr]=Pop[popcurr] como acima... Mais simples...
            /********************************************************************/
            my_matrix auxmatX(xx,yy) ; auxmatX.set("zero") ;
            my_matrix auxmatY(xx,yy) ; auxmatY.set("zero") ;
            my_matrix auxLapX(xx,yy) ; auxLapX.set("zero") ;
            my_matrix auxLapY(xx,yy) ; auxLapY.set("zero") ;

            my_matrix auxmatFight(xx,yy) ; auxmatFight.set("zero") ;
            my_matrix auxmatDeath(xx,yy) ; auxmatDeath.set("zero") ;

            
//            for (int j=1; j<Parameters.numxx-1; j++) {      // Velocidades
//                for (int k=1; k<Parameters.numyy-1; k++) {
//                    
//                    auxmatX(j,k) = - PopAux[popcurr].PeacefulDensity(j,k) * PopAux[popcurr].SensitPeaceful * 0.5 * ( Phero.PheromoneDensity(j+1,k) - Phero.PheromoneDensity(j-1,k) ) ;
//                    auxmatX(j,k) += - PopAux[popcurr].PeacefulDensity(j,k) * PopAux[popcurr].HomeFieldX(j,k) ;
//                    auxmatX(j,k) /= dx ;
//                    
//                    auxmatY(j,k) = - PopAux[popcurr].PeacefulDensity(j,k) * PopAux[popcurr].SensitPeaceful * 0.5 * ( Phero.PheromoneDensity(j,k+1) - Phero.PheromoneDensity(j,k-1) ) ;
//                    auxmatY(j,k) += - PopAux[popcurr].PeacefulDensity(j,k) * PopAux[popcurr].HomeFieldY(j,k) ;
//                    auxmatY(j,k) /= dy ;
//                }
//            }
            for (int j=1; j<Parameters.numxx-1; j++) {      // Velocidades
                for (int k=1; k<Parameters.numyy-1; k++) {
                    int jmaisum = j+1 ;
                    int jmenosum = j-1 ;
                    int kmaisum = k+1 ;
                    int kmenosum = k-1 ;
                    
                    // Velocidades
//                    auxmatX(j,k) = - PopAux[popcurr].PeacefulDensity(j,k) * PopAux[popcurr].SensitPeaceful * ( Phero.PheromoneDensity(jmaisum,k) - Phero.PheromoneDensity(j,k) ) ;
//                    auxmatX(j,k) += - PopAux[popcurr].PeacefulDensity(j,k) * PopAux[popcurr].SpeedNestPeaceful * PopAux[popcurr].HomeFieldX(j,k) ;
                    auxmatX(j,k) += - PopAux[popcurr].PeacefulDensity(j,k) * PopAux[popcurr].SpeedNestPeaceful *0.5* ( PopAux[popcurr].HomePotential(j+1,k) - PopAux[popcurr].HomePotential(j-1,k) );

//                    auxmatX(j,k) += - PopAux[popcurr].PeacefulDensity(j,k) * PopAux[popcurr].SpeedNestPeaceful * PopAux[popcurr].HomeFieldX(j,k) * ( Func( Phero.PheromoneDensity(j,k)) ) ;
                    auxmatX(j,k) /= dx ;
                    
//                    auxmatY(j,k) = - PopAux[popcurr].PeacefulDensity(j,k) * PopAux[popcurr].SensitPeaceful * ( Phero.PheromoneDensity(j,kmaisum) - Phero.PheromoneDensity(j,k) ) ;
//                    auxmatY(j,k) += - PopAux[popcurr].PeacefulDensity(j,k) * PopAux[popcurr].SpeedNestPeaceful * PopAux[popcurr].HomeFieldY(j,k) ;
                    auxmatY(j,k) += - PopAux[popcurr].PeacefulDensity(j,k) * PopAux[popcurr].SpeedNestPeaceful *0.5* ( PopAux[popcurr].HomePotential(j,k+1) - PopAux[popcurr].HomePotential(j,k-1) ) ;
                    
//                    printf("Passo aqui!!!!: %e   \n", auxmatY(j,k)) ;

                    //                    auxmatY(j,k) += - PopAux[popcurr].PeacefulDensity(j,k) * PopAux[popcurr].SpeedNestPeaceful * PopAux[popcurr].HomeFieldY(j,k) * ( Func( Phero.PheromoneDensity(j,k)) ) ;
                    auxmatY(j,k) /= dy ;
                    
                    
                    double aa1 = 0. ;
                    aa1 = 0.2*( PopAux[popcurr].PeacefulDensity(j,k) +PopAux[popcurr].PeacefulDensity(j+1,k)+PopAux[popcurr].PeacefulDensity(j,k+1)+PopAux[popcurr].PeacefulDensity(j-1,k)+PopAux[popcurr].PeacefulDensity(j,k-1) ) ;
//                    aa1 = PopAux[popcurr].PeacefulDensity(j,k) ;
//                    aa1 = 1.;       // Difusão Linear
                    
                    auxLapX(j,k) = aa1 *0.5* ( PopAux[popcurr].PeacefulDensity(j+1,k) - PopAux[popcurr].PeacefulDensity(j-1,k) ) / dx ;
                    auxLapY(j,k) = aa1 *0.5* ( PopAux[popcurr].PeacefulDensity(j,k+1) - PopAux[popcurr].PeacefulDensity(j,k-1) ) / dy ;
                    
//                    auxLapX(j,k) =   ( PopAux[popcurr].PeacefulDensity(j,k) - PopAux[popcurr].PeacefulDensity(j-1,k) ) / dx ;
//                    auxLapY(j,k) =   ( PopAux[popcurr].PeacefulDensity(j,k) - PopAux[popcurr].PeacefulDensity(j,k-1) ) / dy ;
                    
                
                }
            }

            for (int j=1; j<Parameters.numxx-1; j++) {      // Termos conflito
                for (int k=1; k<Parameters.numyy-1; k++) {
                    for (int pp=0; pp<NN; pp++) {
                        if (pp != popcurr) {
                            auxmatFight(j,k) += PopAux[popcurr].ProductionAggressive * PopAux[popcurr].PeacefulDensity(j,k) * PopAux[pp].PeacefulDensity(j,k) ;
                            // ATENÇÃO que vou mudar tudo!!!!!
                            auxmatDeath(j,k) += PopAux[popcurr].DeathByConflict * PopAux[popcurr].PeacefulDensity(j,k) * PopAux[pp].PeacefulDensity(j,k) ;
//                            printf("PARA VERRRRRR: %f,  \n", auxmatDeath(j,k)) ;
                            
                        }
                    }

                }
            }
//            printf("POP: %d,  \n", popcurr) ;
//            printf("PARA VERRRRRR 1: %f,  \n", Pop[0].PeacefulDensity(1,1)) ;
//            printf("PARA VERRRRRR 2: %f,  \n", PopAux[0].PeacefulDensity(1,1)) ;
//            Pop[0].PeacefulDensity(1,1)=56.;
//            printf("PARA VERRRRRR 3: %f,  \n", Pop[0].PeacefulDensity(1,1)) ;
//            printf("PARA VERRRRRR 4: %f,  \n", PopAux[0].PeacefulDensity(1,1)) ;
            
            for (int j=1; j<Parameters.numxx-1; j++) {      // Evolução propriamente dita
                for (int k=1; k<Parameters.numyy-1; k++) {
//                    printf("LAPLAP LAPLAP: %f   \n", auxLapY(j,k) ) ;
//                    Pop[popcurr].PeacefulDensity(j,k) = PopAux[popcurr].PeacefulDensity(j,k) + Parameters.dt * (  PopAux[popcurr].DiffPeaceful * DivergenciaMais(dx, dy, auxLapX, auxLapY, j, k, xx, yy) + DivergenciaMais(dx, dy, auxmatX, auxmatY, j, k, xx, yy) - auxmatDeath(j,k)  ) ;

                    Pop[popcurr].PeacefulDensity(j,k) = PopAux[popcurr].PeacefulDensity(j,k) + Parameters.dt * (  PopAux[popcurr].DiffPeaceful * 0.5*( (auxLapX(j+1,k) - auxLapX(j-1,k))/dx +  (auxLapY(j,k+1) - auxLapY(j,k-1))/dy )  +  0.5*( (auxmatX(j+1,k) - auxmatX(j-1,k))/dx + (auxmatY(j,k+1) - auxmatY(j,k-1))/dy ) - auxmatDeath(j,k)  ) ;
                    
//                    if (Pop[popcurr].PeacefulDensity(j,k) < 0.) {
//                        printf("j: %e,  \n", Pop[popcurr].PeacefulDensity(j,k)) ;
//                        printf("j+1: %e,  \n", Pop[popcurr].PeacefulDensity(j+1,k)) ;
//                        printf("j-1: %e,  \n", Pop[popcurr].PeacefulDensity(j-1,k)) ;
//                        printf("k+1: %e,  \n", Pop[popcurr].PeacefulDensity(j,k+1)) ;
//                        printf("k-1: %e,  \n", Pop[popcurr].PeacefulDensity(j,k-1)) ;
//                        printf("Cena: %e,  \n", Parameters.dt * (  PopAux[popcurr].DiffPeaceful * ( (auxLapX(j+1,k) - auxLapX(j,k))/dx +  (auxLapY(j,k+1) - auxLapY(j,k))/dy )*1.  +  ( (auxmatX(j+1,k) - auxmatX(j,k))/dx + (auxmatY(j,k+1) - auxmatY(j,k))/dy )*1. - auxmatDeath(j,k)  )) ;
//                    }

//                    Pop[popcurr].PeacefulDensity(j,k) = PopAux[popcurr].PeacefulDensity(j,k) + dt * ( PopAux[popcurr].DiffPeaceful * Laplaciano(dx, PopAux[popcurr].PeacefulDensity, j, k, xx, yy) + Divergencia(dx, auxmatX, auxmatY, j, k, xx, yy) - auxmatDeath(j,k) ) ;
                    
//                    PopAux[popcurr].PeacefulDensity(j,k) + dt * ( PopAux[popcurr].DiffPeaceful * Laplaciano(dx, PopAux[popcurr].PeacefulDensity, j, k, xx, yy) + Divergencia(dx, auxmatX, auxmatY, j, k, xx, yy) - auxmatFight(j,k) + PopAux[popcurr].EvaporationAggressive * PopAux[popcurr].AggressiveDensity(j,k) ) ;
                    
                    Pop[popcurr].AggressiveDensity(j,k) = 0. ;
//                    PopAux[popcurr].AggressiveDensity(j,k) + dt * ( PopAux[popcurr].DiffAggressive * Laplaciano(dx, PopAux[popcurr].AggressiveDensity, j, k, xx, yy) + auxmatFight(j,k) - auxmatDeath(j,k) - PopAux[popcurr].EvaporationAggressive * PopAux[popcurr].AggressiveDensity(j,k) ) ;
                    
//                    printf("POP : %20.10f   \n", Pop[0].AggressiveDensity(50,50)) ;
//                    printf("POP AUX: %20.10f   \n", PopAux[0].AggressiveDensity(50,50)) ;
                    
                    
                }
            }

            
            delete auxmatX.elementos ;
            delete auxmatY.elementos ;
            delete auxLapX.elementos ;
            delete auxLapY.elementos ;
            delete auxmatFight.elementos ;
            delete auxmatDeath.elementos ;

            

        }       // Fim do ciclo em cada população

////        for (int j=1; j<Parameters.numxx-1; j++) {      // TESTE
////            for (int k=1; k<Parameters.numyy-1; k++) {
//                for (int pp=0; pp<NN; pp++) {
//                    if (Pop[pp].AggressiveDensity(50,50) > 0.) {
////                        printf("COEF FORA: %f   \n", Pop[pp].AggressiveDensity(j,k)) ;
//                        printf("COEF FORA11: %f   \n", Pop[pp].AggressiveDensity(50,50)) ;
//                    }
//                }
////            }
////        }

        
        for (int j=1; j<Parameters.numxx-1; j++) {      // Evolução da feromona
            for (int k=1; k<Parameters.numyy-1; k++) {
                
                for (int pp=0; pp<NN; pp++) {
                    for (int qq=0; qq<NN ; qq++) {
                        if (qq>pp) {
                            auxmatPheroProd(j,k) += Phero.ProductionRatesPhero * PopAux[pp].PeacefulDensity(j,k) * PopAux[qq].PeacefulDensity(j,k) ;
                        }
                    }
//                    if (PopAux[pp].AggressiveDensity(j,k) > 0.) {
//                        printf("COEF PROD FERO: %f   \n", PopAux[pp].AggressiveDensity(j,k)) ;
//                    }

                }
//                printf("COEF PROD FERO: %f   \n", Phero.ProductionRatesPhero) ;

                
                Phero.PheromoneDensity(j,k) = auxmatPhero(j,k) + dt * ( Phero.DiffPhero * Laplaciano(dx, dy, auxmatPhero, j, k, xx, yy) - Phero.EvaporationPhero * auxmatPhero(j,k) + auxmatPheroProd(j,k)  ) ;
//                printf("COEF PROD FERO: %f   \n", auxmatPheroProd(j,k)) ;
            }
        }

        //  Fronteira
        double HFX, HFY, norm_x, norm_y;
        
        for (int j=1; j<xx-1; j++) {        // Phero
            norm_x = 0.;
            norm_y = -1.;
            Phero.PheromoneDensity(j,0) = Phero.PheromoneDensity(j,1) ;
            
            norm_x = 0.;
            norm_y = 1.;
            Phero.PheromoneDensity(j,yy-1) = Phero.PheromoneDensity(j,yy-2) ;
            
        }
        for (int k=1; k<yy-1; k++) {
            norm_x = -1.;
            norm_y = 0.;
            Phero.PheromoneDensity(0,k) = Phero.PheromoneDensity(0,k) ;
            
            norm_x = 1.;
            norm_y = 0.;
            Phero.PheromoneDensity(xx-1,k) = Phero.PheromoneDensity(xx-2,k) ;
            
        }


        for (int popcurr=0; popcurr<NN; popcurr++) {      // Cada população
            for (int j=1; j<xx-1; j++) {
                norm_x = 0.;
                norm_y = -1.;
                HFX = Func(Phero.PheromoneDensity(j,1)) * Pop[popcurr].HomeFieldX(j,1) ;
                HFY = Func(Phero.PheromoneDensity(j,1)) * Pop[popcurr].HomeFieldY(j,1) ;
                
                Pop[popcurr].AggressiveDensity(j,0) = Pop[popcurr].AggressiveDensity(j,1) ;
                
//                Pop[popcurr].PeacefulDensity(j,0) = Pop[popcurr].PeacefulDensity(j,1) * ( 1. +  ( HFX * norm_x +  HFY * norm_y ) * ( dy / Pop[popcurr].DiffPeaceful ) ) ;

                //Nao
                Pop[popcurr].PeacefulDensity(j,0) = Pop[popcurr].PeacefulDensity(j,1) ;
                //Nao
                
                norm_x = 0.;
                norm_y = 1.;
                HFX = Func(Phero.PheromoneDensity(j,yy-2)) * Pop[popcurr].HomeFieldX(j,yy-2) ;
                HFY = Func(Phero.PheromoneDensity(j,yy-2)) * Pop[popcurr].HomeFieldY(j,yy-2) ;
                
                Pop[popcurr].AggressiveDensity(j,yy-1) = Pop[popcurr].AggressiveDensity(j,yy-2) ;
                
//                Pop[popcurr].PeacefulDensity(j,yy-1) = Pop[popcurr].PeacefulDensity(j,yy-2) * ( 1. +  ( HFX * norm_x +  HFY * norm_y ) * ( dy / Pop[popcurr].DiffPeaceful ) ) ;
                
                //Nao
                Pop[popcurr].PeacefulDensity(j,yy-1) = Pop[popcurr].PeacefulDensity(j,yy-2) ;
                //Nao

            }
            for (int k=1; k<yy-1; k++) {
                norm_x = -1.;
                norm_y = 0.;
                HFX = Func(Phero.PheromoneDensity(1,k)) * Pop[popcurr].HomeFieldX(1,k) ;
                HFY = Func(Phero.PheromoneDensity(1,k)) * Pop[popcurr].HomeFieldY(1,k) ;
                
                Pop[popcurr].AggressiveDensity(0,k) = Pop[popcurr].AggressiveDensity(1,k) ;
                
//                Pop[popcurr].PeacefulDensity(0,k) = Pop[popcurr].PeacefulDensity(1,k) * ( 1. +  ( HFX * norm_x +  HFY * norm_y ) * ( dy / Pop[popcurr].DiffPeaceful ) ) ;
                
                //Nao
                Pop[popcurr].PeacefulDensity(0,k) = Pop[popcurr].PeacefulDensity(1,k) ;
                //Nao

                norm_x = 1.;
                norm_y = 0.;
                HFX = Func(Phero.PheromoneDensity(xx-2,k)) * Pop[popcurr].HomeFieldX(xx-2,k) ;
                HFY = Func(Phero.PheromoneDensity(xx-2,k)) * Pop[popcurr].HomeFieldY(xx-2,k) ;
                
                Pop[popcurr].AggressiveDensity(xx-1,k) = Pop[popcurr].AggressiveDensity(xx-2,k) ;
                
//                Pop[popcurr].PeacefulDensity(xx-1,k) = Pop[popcurr].PeacefulDensity(xx-2,k) * ( 1. +  ( HFX * norm_x +  HFY * norm_y ) * ( dy / Pop[popcurr].DiffPeaceful ) ) ;
                
                //Nao
                Pop[popcurr].PeacefulDensity(xx-1,k) = Pop[popcurr].PeacefulDensity(xx-2,k) ;
                //Nao

            }
        }
        

        
        for (int popcurr=0; popcurr<NN; popcurr++) {      // Cada população
            for (int j=0; j<Parameters.numxx; j++) {      // Guardar PopAux para próxima iter
                for (int k=0; k<Parameters.numyy; k++) {
                    
                    // CHEAT!!!CHEAT!!!CHEAT!!!CHEAT!!!CHEAT!!!CHEAT!!!CHEAT!!!CHEAT!!!
                    
                    Pop[popcurr].PeacefulDensity(j,k) = max(0., Pop[popcurr].PeacefulDensity(j,k)) ;
                    Pop[popcurr].AggressiveDensity(j,k) = max(0., Pop[popcurr].AggressiveDensity(j,k)) ;
                    // END CHEAT!!!CHEAT!!!CHEAT!!!CHEAT!!!CHEAT!!!CHEAT!!!CHEAT!!!CHEAT!!!

                    
                    PopAux[popcurr].PeacefulDensity(j,k) = Pop[popcurr].PeacefulDensity(j,k) ;
                    PopAux[popcurr].AggressiveDensity(j,k) = Pop[popcurr].AggressiveDensity(j,k) ;
                }
            }
        }


        
        delete auxmatPhero.elementos ;
        delete auxmatPheroProd.elementos ;
        
        if (i%20 == 0) {
            cout << "Iter restantes = "<<numiter - i<<endl;
        }

//        cout << " phero.PheromoneDensity(1,1) = 23?   " <<    Phero.PheromoneDensity(1,1)  << endl ;
//        cout << " Pop[2].PeacefulDensity(1,1) = ?   " <<   Pop[2].PeacefulDensity(1,1)  << endl ;
        //  Aqui, cenas a fazer a cada iteração! .....
        
        if (isnan(Pop[1].PeacefulDensity(xx/2,yy/2))) {
            cout <<  "NAN numa iter menor que "<< i << endl;
            //                system("open sticky-notifications://note?message=NAN-ABORT");
//            system("osascript -e 'tell app \"System Events\" to display dialog \"Abort!!!\" with icon 0 with title \"Formigas 6\" '");
//            system("sh plot-png.sh");
            isAbort = 1;
            //abort();
            break;
        }
        
        my_matrix todas(xx,yy); todas.set("zero") ;
        for(int j=0;j<xx;j++){
            for(int k=0;k<yy;k++){
                for (int pp=0; pp<NN; pp++) {
                    todas(j,k) += Pop[pp].PeacefulDensity(j,k) ;
                }
            }
        }

        
        
        string ref ;
        for (j=0; j<NN; j++) {
            ref = to_string(j) ;
            if (i%20 == 0) {            //  1000
                save_time_step(xx, yy, dt, Pop[j].PeacefulDensity, i, "Pop-"+ref+"-Peace");
                save_time_step(xx, yy, dt, Pop[j].AggressiveDensity, i, "Pop-"+ref+"-Aggre");
            }
        }
        if (i%20 == 0) {            //  1000
            save_time_step(xx, yy, dt, todas, i, "Pop-"+ref+"-Total");
        }

        
        delete todas.elementos ;
        
	}		//	Fim de iter em tempo
    
    
    //******************************************************************
    //      Talvez aproveite estes: ----
	/********************************************************************/
	//			Escrever resultados em ficheiros
	/********************************************************************/
    ofstream outfile_solucao3;
    outfile_solucao3.open("PARAVER.txt");
    for(int j=0;j<xx;j++){
        for(int k=0;k<yy;k++){
//            outfile_solucao3 << sqrt((Pop[1].HomeFieldX(j,k))*(Pop[1].HomeFieldX(j,k))+(Pop[1].HomeFieldY(j,k))*(Pop[1].HomeFieldY(j,k)))  << "\t";
            outfile_solucao3 << Pop[0].PeacefulDensity(j,k)  << "\t";

            if(k==yy-1)
                outfile_solucao3 << endl;
        }
    }
    
    ofstream outfile_solucao4;
    outfile_solucao4.open("PARAVER2.txt");
//    double xx = Parameters.numxx ;
//    double yy = Parameters.numyy ;
    for(int j=0;j<xx;j++){
        for(int k=0;k<yy;k++){
//            outfile_solucao4 << sqrt((Pop[2].HomeFieldX(j,k))*(Pop[2].HomeFieldX(j,k))+(Pop[2].HomeFieldY(j,k))*(Pop[2].HomeFieldY(j,k)))  << "\t";
            outfile_solucao4 << Pop[1].PeacefulDensity(j,k) << "\t";
            if(k==yy-1)
                outfile_solucao4 << endl;
        }
    }
    
    ofstream outfile_solucao5;
    outfile_solucao5.open("PARAVER3.txt");
    //    double xx = Parameters.numxx ;
    //    double yy = Parameters.numyy ;
    for(int j=0;j<xx;j++){
        for(int k=0;k<yy;k++){
            //            outfile_solucao4 << sqrt((Pop[2].HomeFieldX(j,k))*(Pop[2].HomeFieldX(j,k))+(Pop[2].HomeFieldY(j,k))*(Pop[2].HomeFieldY(j,k)))  << "\t";
            outfile_solucao5 << Pop[2].PeacefulDensity(j,k) << "\t";
            if(k==yy-1)
                outfile_solucao5 << endl;
        }
    }
    ofstream outfile_solucao6;
    outfile_solucao6.open("PARAVER4.txt");
    //    double xx = Parameters.numxx ;
    //    double yy = Parameters.numyy ;
    for(int j=0;j<xx;j++){
        for(int k=0;k<yy;k++){
            //            outfile_solucao4 << sqrt((Pop[2].HomeFieldX(j,k))*(Pop[2].HomeFieldX(j,k))+(Pop[2].HomeFieldY(j,k))*(Pop[2].HomeFieldY(j,k)))  << "\t";
            outfile_solucao6 << Phero.PheromoneDensity(j,k) << "\t";
            if(k==yy-1)
                outfile_solucao6 << endl;
        }
    }
    ofstream outfile_solucao7;
    outfile_solucao7.open("AG0.txt");
    //    double xx = Parameters.numxx ;
    //    double yy = Parameters.numyy ;
    for(int j=0;j<xx;j++){
        for(int k=0;k<yy;k++){
            //            outfile_solucao4 << sqrt((Pop[2].HomeFieldX(j,k))*(Pop[2].HomeFieldX(j,k))+(Pop[2].HomeFieldY(j,k))*(Pop[2].HomeFieldY(j,k)))  << "\t";
            outfile_solucao7 << Pop[0].AggressiveDensity(j,k) << "\t";
            if(k==yy-1)
                outfile_solucao7 << endl;
        }
    }
    ofstream outfile_solucao8;
    outfile_solucao8.open("HFX.txt");
    //    double xx = Parameters.numxx ;
    //    double yy = Parameters.numyy ;
    for(int j=0;j<xx;j++){
        for(int k=0;k<yy;k++){
            //            outfile_solucao4 << sqrt((Pop[2].HomeFieldX(j,k))*(Pop[2].HomeFieldX(j,k))+(Pop[2].HomeFieldY(j,k))*(Pop[2].HomeFieldY(j,k)))  << "\t";
            outfile_solucao8 << Pop[0].HomeFieldX(j,k) << "\t";
            if(k==yy-1)
                outfile_solucao8 << endl;
        }
    }
    ofstream outfile_solucao9;
    outfile_solucao9.open("TUTTI.txt");
    //    double xx = Parameters.numxx ;
    //    double yy = Parameters.numyy ;
    double tudo = 0;
    for(int j=0;j<xx;j++){
        for(int k=0;k<yy;k++){
            tudo = 0. ;
            for (int pp=0; pp<NN; pp++) {
                tudo += Pop[pp].PeacefulDensity(j,k) ;
            }
            outfile_solucao9 << tudo << "\t";
            if(k==yy-1)
            outfile_solucao9 << endl;
        }
    }

    
    /********************************************************************/
	//			Escrever algo em cada execução
	/********************************************************************/
//	int history = 1; //
//	if (history == 1) {
//		ofstream ErroL2UU (FilenameErrUUL2, ios::app);
//		ErroL2UU << "#############################################################"<<endl;
//		ErroL2UU <<"# dt = "<< dt<< "\t dx = "<<dx<< "\t Tfinal = "<<dt*numiter<<endl
//		<<"# numpts = "<< numpt <<"\t visc = "<< visc << "\t Kapa = " << kapa  << endl;
//		ErroL2UU <<"#dt,\t dx,\t visc,\t Erro L2^2,\t Erro L2^2(T)/(Norma L2^2(T) exact), \t Norma L2-L2, \t Erro L2L2, \t Erro L2L2 relativo" <<endl;
//		ErroL2UU << dt << "\t" << dx<< "\t"<< visc <<"\t" << NormaL2(Prob.UU - Prob.SOL_EXACTAUU, dx) <<"\t"<< NormaL2(Prob.UU - Prob.SOL_EXACTAUU, dx)/NormaL2(Prob.SOL_EXACTAUU,dx)<< "\t" << NormaL2L2 << "\t" << ErroL2L2 <<"\t" << ErroL2L2Relativo <<endl <<"#"<<endl;
//		}
    
    delete[] Pop;

    delete[] PopAux;
    
    if (isAbort==1) {
        abort();
    }

    
    return 0;
}
/********************************************************************/
//			Fim de Main
/********************************************************************/
//Cenas a guardar
///********************************************************************/
////				Escrever a evolução
///********************************************************************/
//int tresD = 0;		//0 --> no 3D; 1 --> 3D yes.
//if (tresD == 1) {
//    int samplt = 20;
//    int samplx = 40;
//    if (i%samplt == 0) {	//Escrever no fich3d só de x em x iterações
//        for (int j = 0; j <= numpt - 1; j=j+samplx)	//e só de y em y pontos espaciais
//        {
//            fout3D1 << -i/samplt  <<"\t"<< real(Prob.XX.comps[j])<<"\t"<< abs(Prob.UU.comps[j]) <<endl;
//            }
//            fout3D1 <<endl;
//            }
//            }
