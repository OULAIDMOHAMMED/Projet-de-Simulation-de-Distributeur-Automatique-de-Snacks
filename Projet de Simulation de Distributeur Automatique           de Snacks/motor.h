#include <iostream>
using namespace std;
class Motor {
private:
    int id;
public:
    Motor(int ID){
    this->id = ID;
    };
    void trigger(){
    cout << " Moteur " << id << "  est active " << endl;
    };
    int getId(){
        return id;
    }
};
