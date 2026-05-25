/* Abstract base class. Attributes: deviceID, name,
location, isOn, firmwareVersion. Methods: toggle(),
getStatus(), restart(), generateReport(). */

#ifndef SMART_DEVICE_H 
#define SMART_DEVICE_H
#include <string>
#include<iostream>
using namespace std;
class SmartDevice{
 protected:
  string deviceid;
  string name;
  string location;
  bool isOn;
  string firmWareVersion;
 public:
  SmartDevice():deviceid(""),name(""),location(""),isOn(false),firmWareVersion(""){}
  SmartDevice(string deviceid,string name,string location,bool isOn ,string firmWareVersion){
    this->deviceid=deviceid;
    this->name=name;
    this->location=location;
    this->isOn=isOn;
    this->firmWareVersion=firmWareVersion;
  }
  string getId(){return deviceid;}
  void setId(){
    cout<<"Enter Device Id : ";
    cin>>deviceid;
    cout<<endl;
  }
  string getName(){return name;}
  virtual ~SmartDevice(){}
  virtual void toggle()=0;
  virtual string getStatus()=0;
  virtual void restart()=0;
  virtual void getReport()=0;
  virtual void AddInfo(string a)=0;
};
#endif