
////////////////////////////////////////////////////////
//  Class matriz
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
class matriz {
public:
    int lines,cols;
    double * elementos;
    
    
    matriz (){}
    matriz (int m,int n)
    {
        lines=m;
        cols=n;
        elementos=new double[m*n];
        for (int i=0; i< lines ; i++) {
            for (int j=0; j<cols; j++) {
                elementos[i*cols+j] = 0.;
            }
        }
    }
    matriz (Numerics& data)
    {
        lines=data.numxx;
        cols=data.numyy;
        elementos=new double[lines*cols];
        for (int i=0; i< lines ; i++) {
            for (int j=0; j<cols; j++) {
                elementos[i*cols+j] = 3.;
            }
        }
    }
    //    ~matriz()
    //    {
    //        delete[] elementos;
    //    }
    
    
    double &operator() (int i,int j){
        if(i>=lines){
            cout << "erro x" << endl;
            exit(1);}
        if(j>=cols){
            cout << "erro y" << endl;
            exit(1);}
        
        return elementos[i*cols+j];
    }
    
    
    
    
    void print (){
        int i,j;
        for(i=0;i<lines;i++)
            for(j=0;j<cols;j++){
                cout << operator()(i,j) << " ";
                if(j==cols-1)
                    cout << endl;
            }
    }
    
    
    
    
    
};

// Ver http://condor.depaul.edu/ntomuro/courses/262/notes/lecture3.html
matriz operator+(const matriz &M1, const matriz &M2)
{
    matriz soma (M1.lines, M1.cols);
    for (int i=0; i< soma.lines ; i++) {
        for (int j=0; j<soma.cols; j++) {
            soma.elementos[i*M1.cols+j] = M1.elementos[i*M1.cols+j] + M2.elementos[i*M1.cols+j];
        }
    }
    return soma;
}
matriz operator-(const matriz &M1, const matriz &M2)
{
    matriz soma (M1.lines, M1.cols);
    for (int i=0; i< soma.lines ; i++) {
        for (int j=0; j<soma.cols; j++) {
            soma.elementos[i*M1.cols+j] = M1.elementos[i*M1.cols+j] - M2.elementos[i*M1.cols+j];
        }
    }
    return soma;
}
matriz operator*(const matriz &M1, const double C)
{
    matriz prod (M1.lines, M1.cols);
    prod = M1;
    
    for (int i=0; i< prod.lines ; i++) {
        for (int j=0; j<prod.cols; j++) {
            prod.elementos[i*M1.cols+j] *= C ;
        }
    }
    return prod;
}
matriz operator*(const matriz &M1, const matriz &M2)
{
    matriz prod (M1.lines, M1.cols);
    double aux = 0.;
    for (int i=0; i< prod.lines ; i++) {
        for (int j=0; j<prod.cols; j++) {
            for (int k=0; k<prod.cols; k++) {
                aux += M1.elementos[i*M1.cols+k] * M2.elementos[k*M1.cols+j];
            }
            prod.elementos[i*M1.cols+j] = aux;
            aux = 0.;
        }
    }
    return prod;
}
////////////////////////////////////////////////////////
// END Class matriz
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////



