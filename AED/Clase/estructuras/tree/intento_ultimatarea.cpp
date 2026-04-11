#include <iostream>
using namespace std;

template<class T>
class Node{
    
    public:
        Node(T data);
        ~Node();
        Node& operator=(T d){
            data=d;
            return *this; 
        }
    private:
        T data;
        Node<T>* nodes[2];        
};

template<class T>
Node<T>::Node(T data){
    this->data=data;
    nodes[0]=0;
    nodes[1]=0;
}

template<class T>
Node<T>::~Node(){
    
}



template<class T>
struct Cola{
	T A[30];
	T* Tail=nullptr;
	T* Head=nullptr;

	bool vacio();
	bool lleno();
	bool push(T a);
	bool pop(T &a);
	void print();
	
};

template<class T>
bool Cola<T>::vacio(){
	return(  Tail == nullptr ); //Tail!= nullptr &&  Head!= nullptr &&
}




template<class T>
bool Cola<T>::lleno(){
    int dim= sizeof(A)/sizeof(*A);
	if(!vacio()){
		if (Head<Tail)
		{
		 	return( Tail-Head == dim-1 );
		}
		else{
			return( !(Head-Tail-1));
		}
	}
	
	return false;

}

template<class T>
bool Cola<T>::push(T a){
    cout<<"agregando "<<endl;
    int dim= sizeof(A)/sizeof(*A);
	if(vacio()){
	    
		if(Head== nullptr){ // cambiar
			Head=A;
			*Head=a;
			Tail=Head;
		//	 cout<<"pushI Head"<<Head;cout<<" pushI Tail"<<Tail<<endl;
			return true;
		}
		else{
	        Tail=Head;
	        *Tail=a;
	        return true;
		}

	}
	else if(!lleno()){
		if(Head<=Tail){
			if(Tail!=A+dim-1){
				Tail++;	 //cout<<"push Head"<<Head;cout<<" push Tail"<<Tail<<endl;
				*Tail=a;
				return true;
			}
			else{
				Tail=A;
				*Tail=a;
			//	cout<<"push Head"<<Head;cout<<" push Tail"<<Tail<<endl;
				return true;
			}		
		}
		else if(Tail<Head && Head-Tail != 1){	
		    Tail++;
		    *Tail=a;
					//		    cout<<"push Head"<<Head;cout<< "push Tail"<<Tail<<endl;
			return true;
					
		}
	}
	
	cout<<"lleno"<<endl;
	return false;
	
}

template<class T>
bool Cola<T>::pop(T &a){
    cout<<"borrando ";
    int dim= sizeof(A)/sizeof(*A);
	if(vacio()){
		cout<<"vacio"<<endl;
		return false;
	}
	else if(Head==Tail){
		a=*Head;
		Head++;	
		Tail=nullptr;
		//			    cout<<"POP Head"<<Head;cout<<" POP Tail"<<Tail<<endl;
        return true;
	}
	else if(Head<Tail){
		a=*Head;
		Head++;		
		//			    cout<<"POP Head"<<Head;cout<<" POP Tail"<<Tail<<endl;

		return true;
	}
	else if(Tail<Head){		
		if(Head!= A+dim-1){
		    a=*Head;
			Head++;	 return true;
		}
		else{
			a=*Head;
			Head=A;	return true;	
		}
	}
    return false;
}

template<class T>
void Cola<T>::print(){
    int dim= sizeof(A)/sizeof(*A);cout<<"print: "<<endl;
    //cout<<"Head"<<Head<<endl;cout<<"Tail"<<Tail<<endl;
    //cout<<sizeof(A)/sizeof(*A)<<endl;
    if(!vacio()){ //cout<<"Head"<<endl;
        T* i= Head;
        if(Head==Tail){
            cout<<*Head<<endl;
        }
        else if(Head<Tail){
            for(; i<=Tail ; i++)
                cout<<*i<<" ";
        }
        else{
            for(; i<A+dim ; i++)
                cout<<*i<<" ";
            i=A;
            for(; i<=Tail ; i++)
                cout<<*i<<" ";
        
        }
    }
    else{
        cout<<" vacio "<<endl;
    }        
}


int main(){
    Cola<int*> Pint;
    //cout<<Pint.vacio()<<endl;
    //cout<<Pint.lleno()<<endl;
    int val;
    int* valptr = &val;
    Pint.push(valptr);
    Pint.print();

	return 0;
}