#include<iostream>
#include<ctime>
#include<string>
using namespace std;
int main(){
    srand(time(0));
    cout<<"CREATE DATABASE OOP;"<<endl<<"USE OOP;"<<endl;
    cout<<"CREATE TABLE poi(lkj DATE, mnb INT, bvc INT, dfj CHAR, PRIMARY KEY(lkj));"<<endl;
    for(int i=0;i<100;i++){
        cout<<"INSERT INTO poi(lkj, mnb, bvc, dfj) VALUES (";
        for(int j=0;j<4;j++){
            for(int k=0;k<3;k++){
                cout<<char('a'+(rand()%26));
            }
            if(j!=3){
                cout<<", ";
                }
            else
            {
                cout<<");"<<endl;
            }
            
        }
    }
    system("pause");
    return 0;
}


//SELECT * from poi;
//SELECT * from poi  WHERE dfj LIKE '%ser';