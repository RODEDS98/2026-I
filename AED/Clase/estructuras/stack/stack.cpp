#include<iostream>
using namespace std;

template<class T>
class stack{
	
	public:
		stack();
		~stack();
		bool push(T a);
		bool pop(T &a);
		bool empty();
		bool full();
		void print();
		T topp();
		int size();

	private:
		T A[12];
		T* top;
};

template<class T>
stack<T>::stack(){
	top=nullptr;

}

template<class T>
stack<T>::~stack(){

}

template<class T>
bool stack<T>::push(T a){
	if(full() ) return false;
	if(empty()) {
		*A = a;
		top = A;
		return true; 
	}
	top++;
	*top=a;
	return true;
}

template<class T>
bool stack<T>::pop(T &a){
	if(!empty()){
		if(top==A){
			a=*top;
			top=nullptr;
			return true;
		}
		a=*top;
		top--;
		return true;
	}

	return false;
}

template<class T>
bool stack<T>::empty(){
	return !top;
}

template<class T>
bool stack<T>::full(){

	return A+11 == top;
}

template<class T>
T stack<T>::topp(){
	if(!empty()){
	    return *top;	
	}
	return T();
}
//A 2 3 4 top

template<class T>
int stack<T>::size(){
    if(empty()) return 0;
	return top-A+1;
}

template<class T>
void stack<T>::print(){
	if(empty()) return;
	cout<<"pila: ";
	for(T* p = A ; p<=top ; p++){
		 cout<< *p <<" ";
	}
}


int main(){
	stack<int> pila;
	cout<<pila.empty()<<endl;
	cout<<pila.full()<<endl;
	cout<<pila.topp()<<endl;
	
	for (int i=1; i<=12 ; i++){
		pila.push(i);pila.print();cout<<" size "<<pila.size() <<endl;
		cout<<pila.topp()<<endl;
	}
    
    cout<<pila.full()<<endl;
	cout<<pila.topp()<<endl;
    
    int a;
	for (int i=1; i<=12 ; i++){
		pila.pop(a);
		
		pila.print();cout<<" size "<<pila.size() <<endl;
	}
	cout<<pila.empty();
	cout<<endl;

	return 0;
}