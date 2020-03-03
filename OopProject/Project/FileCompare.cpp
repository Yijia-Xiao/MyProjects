#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>
using namespace std;
int main(){
    string TestId;
    cout<<"Please enter the TestPoint Id :\t";
    cin>>TestId;
    cout<<endl;
    ifstream fin1("TestPoint"+TestId);
    ifstream fin2("StdPoint"+TestId);
    string my,std;
    int ctr=0;
    int succeed_times=0;
    int fail_times=0;
    int total_times=0;
    while(fin1){
        total_times++;
        getline(fin1,my);
        getline(fin2,std);
        if(my==std){
            succeed_times++;
            cout<<"TestPoint # "<<total_times<<" succeed!"<<endl;
            cout<<"MY Output:\t\t"<<my<<endl;
            cout<<"Standard Output:\t"<<std<<endl;
            cout<<endl;
        }
        else{
            fail_times++;
            cout<<"Difference found! TestPoint # "<<total_times<<" failed"<<endl;
            cout<<endl;
        }
        Sleep(100);
    }
    cout<<endl;
    cout<<"Test Report:"<<endl;
    cout<<"******************************************"<<endl;
    cout<<"**"<<"       Total Test TImes "<<total_times<<"             **"<<endl;
    cout<<"**"<<"       Succeed TImes    "<<succeed_times<<"             **"<<endl;
    cout<<"**"<<"       Total Test TImes "<<fail_times<<"             **"<<endl;
    cout<<"**"<<"       Correct Rate     "<<(succeed_times*100.0)/(total_times*1.0)<<"%           **"<<endl;
    cout<<"******************************************"<<endl;
    system("pause");

}