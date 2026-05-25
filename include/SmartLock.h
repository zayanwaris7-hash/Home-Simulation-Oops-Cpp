/*6. SmartLock Inherits from SmartAppliance Attributes: isLocked, accessCode, accessLog.
Methods: lock(), unlock(), verifyCode(),
getAccessHistory().
*/
#ifndef  SMARTLOCK_H
#define  SMARTLOCK_H
#include<iostream>
#include<windows.h>
#include"SmartAppliance.h"
using namespace std;
class SmartLock:public SmartAppliance {
    protected:
     bool isLocked;
     string accessCode;
     string accessLog;
    public:
    SmartLock():isLocked(false),accessCode(""),accessLog(""){}
    SmartLock(string a, string b, string c, int d, string e, float f, string g ,bool h,string i,string j)
    :SmartAppliance(a,b,c,d,e,f,g),isLocked(h),accessCode(i),accessLog(j){}
    void lock(){
       cout<<"Smart Lock Name : "<<name<<"is Locking..."<<endl;
       Sleep(3000);
       isLocked=true;
       cout<<"[STATUS] LOCKED"<<endl;
    }
    bool verifyCode(string a){ return accessCode==a?true:false;}
    void unlock(){
        string s;
        do{
        cout<<"Enter your password to Unlock : "<<endl;
        cin>>s;
         if(!verifyCode(s)){cout<<"Invalid Password ! Try Again Nigga!"<<endl;}
        }while(!verifyCode(s));
        if(verifyCode(s)){
            cout<<"Unlocking ...."<<endl;
            accessLog+="Unlocking Smart Lock Name: "+name+".\n";
            Sleep(3000);
            cout<<"[Status] Unclocked Succesfully ."<<endl;
        }
    }
    void getAccessHistory(){
        string s;
        do{
        cout<<"Enter your password to get : "<<endl;
        cin>>s;
         if(!verifyCode(s)){cout<<"Invalid Password ! Try Again Nigga!"<<endl;}
        }while(!verifyCode(s));
        cout<<accessLog;
    }
    void setPassword(){
       
        string a;
        do{
        cout<<"Enter new Password :";
        cin>>a;
        if(!(a.length()==4)) cout<<"Length of Password Must be  4 "<<endl;
        }while(!(a.length()==4));
    }
    ~SmartLock()override{}

};
#endif