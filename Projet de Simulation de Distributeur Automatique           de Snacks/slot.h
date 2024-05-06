#include "motor.h"
#include <string>
#include <iostream>
using namespace std;
class Slot {
private:
    string productName;
    int id;
    int numProducts;
    int prix;
    Motor* motor1;
    Motor* motor2;

public: 
    Slot() : id(0),productName(""), numProducts(0), prix(0), motor1(nullptr), motor2(nullptr) {}
    Slot(string productName, int ID, int price, int motorID1, int motorID2 = 0)
        : productName(productName), id(ID), prix(price), numProducts(0) {
        motor1 = new Motor(motorID1);
        if (motorID2 != 0) {
            motor2 = new Motor(motorID2);
        } else {
            motor2 = nullptr;
        }
    };
    int getMotor1Id() {
        return motor1 != nullptr ? motor1->getId() : 0;
    }

    int getMotor2Id() {
        return motor2 != nullptr ? motor2->getId() : 0;
    }
    virtual ~Slot() {
        delete motor1;
        delete motor2;
    };
    virtual void drop() =0;
    int getNumProducts() {
        return numProducts;
    };
    void setNumProducts(int numProducts) {
        this->numProducts = numProducts;
    };
    string getProductName() {
        return productName;
    };
    void setProductName(string productName) {
        this->productName = productName;
    };
    int getPrice() {
        return prix;
    };
    void setPrice(int price) {
        this->prix = price;
    };
    int getId() {
        return id;
    };
};
class SmallSlot : public Slot {
private:
    Motor* motor1;

public:
    SmallSlot(string ProductName,int slotid,int price,int motorid1)
        : Slot(ProductName,slotid,price,motorid1){}

    ~SmallSlot() {}

    void drop() {
        if (getMotor1Id() != 0) {
            Motor* motor1 = new Motor(getMotor1Id());
            motor1->trigger();
            delete motor1;
        }
        cout << this->getProductName() << " Livre depuis la fente " << this->getId() << endl;
        this->setNumProducts(this->getNumProducts() - 1);
    };
};
class WideSlot : public Slot {
private:
    Motor* motor1;
    Motor* motor2;

public:
    WideSlot(string productName, int id, int price, int motorId1, int motorId2)
        : Slot(productName, id, price,motorId1,motorId2) {}

    ~WideSlot() {}

    void drop() {
        if (getMotor1Id() != 0) {
            Motor* motor1 = new Motor(getMotor1Id());
            motor1->trigger();
            delete motor1;
        }
        if (getMotor2Id() != 0) {
            Motor* motor2 = new Motor(getMotor2Id());
            motor2->trigger();
            delete motor2;
        }
        cout << this->getProductName() << " Livre depuis la fente " << this->getId() << endl;
        this->setNumProducts(this->getNumProducts() - 1);
    };
};
