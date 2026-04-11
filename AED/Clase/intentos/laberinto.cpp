#include <iostream>
using namespace std;

void print(int(* A)[10], int fil ){
    for(int(* i)[10]=A    ; i < A+fil  ; i++){
        for(  int* j = *i  ; j < *(i+1) ; j++){
            if(*j==-1){
               cout<<"X";
            }
            else if(*j==100){
               cout<<"A";
            }
            else if(*j==200){
               cout<<"B";
            }
            
            else{
               cout<<" ";
            }
           
        }
        cout<<endl;
    }
    cout<<endl;
} 

/*
void LAB(int(* A)[10], int fil, int* dir_A,int* dir_B ){
    //int(* i)[fil]= dir_A;
    
    if( *j != 10 ){
    if(  (i-1) >= A ){
        if( *( *(i-1) + (j-*i+0) ) == 0 )                      (*j)++;                       //      o  
        
        if( *( j-1 ) ==9   && ( j-1 ) >= *i )                      (*j)++;                                        
        if( *( j+1 ) ==9   && ( j+1 ) < *(i+1) )                   (*j)++;                                        // o         o
        if(  (i+1) < A+fil+1 ){
        if( *( *(i+1) + (j-*i+0) ) == 9)                       (*j)++;                                             //      o 
    }
}
*/

template<size_t fil,size_t col>
void encontrar(int (&ini)[fil][col], int* &p_A, int* &p_B, int (&fin)[fil][col]  ){
    int count=0;
    //cout<<sizeof(ini) /sizeof(**ini);
    const int dim = sizeof(ini) /sizeof(**ini);
    for(int* i = *ini ; i < *ini+dim  ; i++ ){
        if ( *i==100){
            count++;
            p_A = i;
            
        }
        else if ( *i==200){
            count++;
            p_B = i;
        }
        else if ( count==2){
            break;
        }
       
    }
}    

template<size_t fil,size_t col>
void solucion(int(& A)[fil][col], int* dir_A , int* dir_B ){             //   100 101 102 103
    if (dir_A < dir_B){
        int(* i)[col]=dir_A;
        
        for( ; i < A+fil ; i++){                           //   200 201 202 203
            for(  int* j = *i  ; j < *(i+1) ; j++){        //   300 301 302 303 //   400 401 402 403 *( *(i-1) + (j-*i-1) )
    
              if( *j != -1 ){
                if(  (i-1) >= A ){
                    if( *( *(i-1) + (j-*i+0) ) == 0 )                      (*j)++;                       //      o  
                }
                if( *( j-1 ) ==9   && ( j-1 ) >= *i )                      (*j)++;                                        
                if( *( j+1 ) ==9   && ( j+1 ) < *(i+1) )                   (*j)++;                                        // o         o
    
                if(  (i+1) < A+fil+1 ){
                    if( *( *(i+1) + (j-*i+0) ) == 9)                       (*j)++;                                             //      o 
                  
                }
    
               //cout<< *j <<" ";*
              }
            }
      
        }
    }
}


int main()
{
    cout<<"buscaminas\n";
    int fil,col;
    int** p;
    
    fil=10;
    col=10;
    
    int* dir_A = nullptr;
    int* dir_B = nullptr;
    
    
    int A[10][10]=  {{100,-1,0, 0, 0,0, 0, 0, 0,-1},  //1
                      {0,-1,0, 0, 0,0, -1,-1, 0,-1},  //2
                      {0,-1,0,-1,-1,0,-1, -1,-1,-1},  //3
                      {0,-1,0,-1, 0,0,-1,  0, 0, 0},  //4
                      {9, 0,0,-1,0,0,0,0,-1,-1},  //1
                      {9,-1,-1,-1,-1,-1,0,0,-1,0},  //2
                      {0,0,0,0,-1,0,0,0,0,0},  //3
                      {0,-1,-1,0,-1,0,0,-1,-1,-1},  //8
                      {-1,-1,0,0,-1,0,0,-1,0,0},  //9
                      {0,0,0,0,-1,0,0,0,0,200},  //10
                     };
    // Dibujar matriz
    print(A,fil); 

    
    // Dibujar matriz 

    
    //solucion(A, 10 );     
    encontrar(A ,dir_A ,dir_B , A  );
    //cout<<"direccion A:"<< dir_A<<endl<<"direccion B:"<< dir_B<<endl;
    cout<<"Solucion:"<<endl;
    
    return 0;
}