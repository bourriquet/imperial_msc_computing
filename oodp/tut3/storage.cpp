#include <iostream>

#define MAX 12

using namespace std;

class Device {

protected:
  double capacity;                     // GB                                                              
  double bandwidth;                    // MB/s                                                            

public:
  virtual double latency() = 0;        // ms                                                              
  Device(double c, double b) {
    capacity = c;
    bandwidth = b;
  }
  double getCapacity() {
    return capacity;
  }
  double getBandwidth() {
    return bandwidth;
  }
};

class HD : public Device {

protected:
  double rotation;                     // ms                                                              
  double seek;                         // ms                                                              

public:

  HD(double c, double b, double r, double s) : Device(c, b) {
    rotation = r;
    seek = s;
  }
  virtual double latency() {
    return rotation + seek;
  }

};

class SSD : public Device {

protected:
  double access;                       // ms                                                              

public:
  SSD(double c, double b, double a) : Device(c, b) {
    access = a;
  }
  virtual double latency() {
    return access;
  }

};

class Array {

protected:
  int device_count;
  Device *devices[MAX];
  virtual double scale() const = 0;

  double capacity() {
    double sum = 0;
    for (int i = 0; i < device_count; i++) {
      sum += devices[i]->getCapacity();
    }
    return sum;
  }
  double bandwidth() {
    double sum = 0;
    for (int i = 0; i < device_count; i++) {
      sum += devices[i]->getBandwidth();
    }
    return sum;
  }

public:
  Array() {
    device_count = 0;
  }
  bool addDevice(Device *d) {
    if (device_count >= MAX)
      return false;
    devices[device_count] = d;
    device_count++;
    return true;
  }
  double getCapacity() {
    return capacity() * scale();
  }
  double getBandwidth() {
    return bandwidth() * scale();
  }
  double getLatency() {
    double latency = 0.0;
    for (int i = 0; i < device_count; i++) {
      if (devices[i]->latency() > latency)
        latency = devices[i]->latency();
    }
    return latency;
  }

};

class RAID1 : public Array {

protected:
  virtual double scale() const {
    return 0.5;
  }

public:
  RAID1() : Array() {
  }

};

class RAID5 : public Array {

protected:
  virtual double scale() const {
    return (device_count - 1.0)/device_count;
  }

public:
  RAID5() : Array() {
  }
};

int main() {

  RAID1 r1;
  RAID5 r5;

  HD device1(500.0, 100.0, 4.0, 8.0);
  SSD device2(30.0, 300.0, 0.01);

  for (int i = 0; i < 4; i++) {
    r1.addDevice(&device1);
    r5.addDevice(&device2);
  }

  cout << r1.getBandwidth() << endl;
  cout << r1.getLatency() << endl;
  cout << r5.getCapacity() << endl;

  return 0;

}
