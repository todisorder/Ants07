/*
 *  Territory01.h
 *  
 *
 *  Created by Paulo Amorim on Oct/2014.
 *
 *
 */

#ifndef TERRIT          //http://www.cplusplus.com/doc/tutorial/preprocessor/
#define TERRIT

#include <cmath>
#include <complex>
//#include "Dados.h"
#include "matriz.h"
using namespace std;

/********************************************************************/
//					Classe Pheromone
/********************************************************************/
class Pheromone
{
public:
    friend class Ants ;     //Acho que não precisa, só se precisasse de coisas private do Ants;
    
    //    Pheromone (Dados);
    
    my_matrix PheromoneDensity;
    
    double DiffPhero;
    double EvaporationPhero ;                // Vai ser = 1 na dimensionalização; só por completude.
    //    double * ProductionRatesPhero ;         // Um para cada população!
    double ProductionRatesPhero ;           // Por agora só um pra todos...
    
    Pheromone () {}
    Pheromone (Numerics par) : PheromoneDensity(par) {}
    
};




/********************************************************************/
//					Classe Ants
/********************************************************************/
class Ants
{
public:

//	Ants(Dados);		//Construtor;  estava Ants(Dados *); mas quero fazer sem * se não for necessário.
	
    my_matrix PeacefulDensity ;
    my_matrix AggressiveDensity ;
    my_matrix HomeFieldX ;
    my_matrix HomeFieldY ;
    my_matrix HomePotential ;

    
//    static int NumPops;
                                    // De pág.11 de M-3, out. 2014.
    double DiffPeaceful;            // D_u
    double DiffAggressive;          // D_mu
    double SensitPeaceful;          // chi_u
    double SensitAggressive;        // chi_mu
    double SpeedNestPeaceful;       // E_u
    double ProductionAggressive;     // Lambda_1
    double EvaporationAggressive;    // Lambda_2
    double DeathByConflict;          // Z_mu
    double TotalPop;
    double Nestxx;
    double Nestyy;
    
    Ants () {}
    Ants (Numerics par) : PeacefulDensity(par), AggressiveDensity(par), HomeFieldX(par), HomeFieldY(par), HomePotential(par) {}
    
    void TimeStep (Numerics, Pheromone, int, int) ;
    
    Ants &operator=(const Ants &) ;
    
};

//int Ants::NumPops = 0 ;             // Moral: posso usar Ants::NumPops onde quiser, inclusive nos calculos da fero.



//void Ants::TimeStep (Numerics pars) {
//    // cenas
//}


///********************************************************************/
////					Classe Numerics dos parâmetros numéricos
////                  Só deve ser chamada uma vez
///********************************************************************/
//class Numerics {
//    
//public:
//    double numiter ;
//    double numxx ;
//    double numyy ;
//    string Comm
//    
//    Numerics (){
//        cout << "//Introduzir Comentários" << endl;
//        getline(cin, Comm, '\n');               // Nice... de http://www.cprogramming.com/tutorial/string.html
//        cout << "// CLASSE! Introduzir o numero de subintervalos em x pretendidos" << endl;
//        cin >> numxx ;
//        cout << "//Introduzir o numero de subintervalos em y pretendidos" << endl;
//        cin >> numyy ;
//        cout << "//Introduzir o numero de iterações em tempo pretendidas" << endl;
//        cin >> numiter ;
//        cin.ignore() ;
//        // Because C++!! ver http://stackoverflow.com/questions/12691316/getline-does-not-work-if-used-after-some-inputs
//        // É pq o ultimo cin deixa lá um \n que se não fizer isto é lido pelo próximo getline.
//        // Sem isto, só lê Comm da 1a vez que é chamado durante a execução. Sigh...
//    }
//    
//};
//
///********************************************************************/
////				Class my_matrix
////              Atenção que tem um construtor com Numerics
///********************************************************************/
//class my_matrix {
//public:
//    int dim1,dim2;
//    double * elementos;
//    
//    my_matrix() {}
//    my_matrix(Numerics par) {
//        dim1 = par.numxx ;
//        dim2 = par.numyy ;
//        elementos=new double[dim1*dim2];
//    }
//    my_matrix (int m,int n)
//    {
//        dim1=m;
//        dim2=n;
//        elementos=new double[m*n];
//    }
//    //    ~my_matrix()
//    //    {
//    //        delete[] elementos;
//    //    }
//    double &operator() (int i,int j){
//        if(i>=dim1){
//            cout << "erro em matriz" << endl;
//            exit(1);}
//        if(j>=dim2){
//            cout << "erro em matriz" << endl;
//            exit(1);}
//        
//        return elementos[i*dim2+j];
//    }
//    void print (){
//        int i,j;
//        for(i=0;i<dim1;i++)
//            for(j=0;j<dim2;j++){
//                cout << operator()(i,j) << " ";
//                if(j==dim2-1)
//                    cout << endl;
//            }
//    }
//    void set (string s)
//    {
//        int i,j;
//        if(s=="id")
//        {
//            for(i=0;i<dim1;i++)
//                for(j=0;j<dim2;j++)
//                    operator()(i,j)=1.0;
//        }
//        if(s=="zero")
//        {
//            for(i=0;i<dim1;i++)
//                for(j=0;j<dim2;j++)
//                    operator()(i,j)=0.0;
//        }
//    }
//};
//




#endif  //TERRIT