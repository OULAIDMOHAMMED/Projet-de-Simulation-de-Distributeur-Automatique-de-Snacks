#include<iostream>
#include "slot.h"
#include "Dropcheck.h"
#include "CoinSlot.h"
#include "Clavier.h"
#include <vector>
using namespace std;
class Automat {
private:
    vector<Slot*> slots;
    int numSlots;
    int numProductsPerSlot;
    int cached;
public:
    CoinSlot CoinSlot;
    Clavier Keypad;
    DropCheck DropCheck;

public:
    Automat(int numSlot, int numProductsPerSlot){
    this->numSlots = numSlot;
    this->numProductsPerSlot = numProductsPerSlot;
    this->cached = -1;
};
    ~Automat(){
        for (int i = 0; i < slots.size(); i++) {
            delete slots[i];
        }
    slots.clear();
};
    void addSlot(Slot* slot){
    slots.push_back(slot);
    numSlots++;
};
    bool searchSlot(int slotID) {
    if (slotID == cached) {
        return true;
    }
    for (auto i = slots.begin(); i != slots.end(); ++i) {
        if ((*i)->getId() == slotID) {
            cached = slotID;
            return true;
        }
    }
    return false;
}


    void changeSlot(int slotID, string productName, int price){
    if (slotID >= 0 && slotID < numSlots) {
        slots[slotID]->setProductName(productName);
        slots[slotID]->setPrice(price);
    }
    
};
    void changeSlot(int slotID, int price){
    if (slotID >= 0 && slotID < numSlots) {
        slots[slotID]->setPrice(price);
    }
    
};
    void changeSlot(int slotID, string productName){
    if (slotID >= 0 && slotID < numSlots) {
        slots[slotID]->setProductName(productName);
    }
    
};
    int getPieces(int slotID){
    if (slotID >= 0 && slotID < numSlots) {
        return slots[slotID]->getNumProducts();
    }
    return -1;
};
    bool isAvailable(int slotID){
    if (slotID >= 0 && slotID < numSlots) {
        if(slots[slotID]->getNumProducts() > 0){
            return true;
        }
        else{
            return false;
        }
    }
    return -1;
};
    int getPrice(int slotID){
    if (slotID >= 0 && slotID < numSlots) {
        return slots[slotID]->getPrice();
    }
    return -1;
};
    void dropSlot(int slotID){
    if (slotID >= 0 && slotID < numSlots) {
        slots[slotID]->drop();
    }
};
    void fillAll(){
        for(int i=0;i<slots.size();i++){
            slots[i]->setNumProducts(numProductsPerSlot);
        }
};
    void remplir(int slotID, int numProducts){
    if (slotID >= 0 && slotID < numSlots) {
        slots[slotID]->setNumProducts(numProducts);
    }
};
// Méthode pour remplir les données de l'automate à partir d'un fichier
void fillFromFile() {
    FILE *fichier = fopen("slots.txt", "r");
    if (fichier != nullptr) {
        char line[256];
        while (fgets(line, sizeof(line), fichier) != nullptr) {
            char productName[100];
            int id,price, motor1, motor2;
            if (sscanf(line, "%s %d %d %d %d %d", productName,&id,&price, &motor1, &motor2) == 5) {
                if(motor2==0){
                    slots.push_back(new SmallSlot(productName,id,price, motor1));
                }else{
                    slots.push_back(new WideSlot(productName,id,price, motor1, motor2));
                }
            }
        }
        fclose(fichier);
    } else {
        FILE *newFile = fopen("slots.txt", "w");
        if (newFile != nullptr) {
            fclose(newFile);
        } else {
            cout << "Erreur de créer le fichier." << endl;
        }
    }
};
// Méthode pour remplir un fichier avec les données actuelles de l'automate
void fillFile() {
        FILE *fichier = fopen("slots.txt", "w");
        if (fichier != nullptr) {
            for (const auto& slot : slots) {
                fprintf(fichier, "%s %d %d %d %d\n", slot->getProductName().c_str(),slot->getId(), slot->getPrice(), slot->getMotor1Id(), slot->getMotor2Id());
            }
            fclose(fichier);
        } else {
            cout << "Erreur  d'ouvrir le fichier " << endl;
        }
};
// Méthode pour afficher les informations de l'automate
void print() const {
        cout << "          -------------------------------------" << endl;
        cout << "          |       Contenu de l'automate       |" << endl;
        cout << "          -------------------------------------" << endl;
        int k=0;
        for (const auto& slot : slots) {
            k++;
            cout<<  "          |                                             " <<endl;
            cout << "          |      les information de produit==>"<<k<<" : " <<endl;
            cout << "          |Produit : " << slot->getProductName()<<endl;
            cout << "          |Prix : " << slot->getPrice()<< endl;
            cout << "          |Nombre de produits : " << slot->getNumProducts()<< endl;
            cout << "          -------------------------------------" << endl;
        }
}
};