#include <iostream>
#include <map>

using namespace std;

int main ()
{
  map<char,int> m;
  
  //initializing
    m['a']=10;
    m['b']=20;
    m['c']=30;
    m.insert({'d',44});
    m.insert({'e',31});
    m.insert({'f',24});
    
    m.erase('b');
    m.erase('d');
  
    auto f1 = m.find('a');
    if ( f1 != m.end() )
        cout<<"'a' found! "<<f1->first<<" "<<f1->second;
    else
        cout<<"'a' no found! ";
    cout<<"\n";
    
    auto f2 = m.find('b');
    if ( f2 != m.end() )
        cout<<"'b' found!"<<f2->first<<" "<<f2->second;
    else
        cout<<"'b' no found!";

    cout<<"\n";

  return 0;
}
