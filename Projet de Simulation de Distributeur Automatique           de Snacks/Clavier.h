#include <iostream>

using namespace std;
class Clavier {
public:
    int getSelection() {
    int selection;
    cout << "Entrez le numero de l'emplacement (et -1 pour quitter) :";
    cin >> selection;
    selection=selection-1;
    if(selection==-1){
        return -1;
    }
    return selection;
};
};
