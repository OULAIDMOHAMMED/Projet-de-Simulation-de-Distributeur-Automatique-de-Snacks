#include<iostream>
#include <cstdlib>
#include <conio.h>
#include "Automat.h"
using namespace std;
// La fonction client qui contient toutes les opérations qu'un client peut effectuer
void client(Automat automat1){
    int c;
    // Affichage du menu client
    cout << "              -----------------------------------------" << endl;
    cout << "              |             MENU client               |" << endl;
    cout << "              -----------------------------------------" << endl;
    cout << "              |  1. Acheter un produit                |" << endl;
    cout << "              |  2. Affichez les produits disponibles.|" << endl;
    cout << "              |  3. Quitter                           |" << endl;
    cout << "              -----------------------------------------" << endl;
    cout << "                   Choix : ";
    cin>>c;
    switch (c)
    {
        // partie pour acheter un produit
    case 1:{
        system("cls");
        int selectedSlot = automat1.Keypad.getSelection();
       if (selectedSlot == -1) {
        cout << "Annulation de l'achat." << endl;
        client(automat1);
       }
       if (!automat1.isAvailable(selectedSlot)) {
        cout << "Le produit n'est pas disponible dans cet emplacement." << endl;
        client(automat1);
       }
       int price = automat1.getPrice(selectedSlot);
        cout << "Prix du produit selectionne : " << price << " cents" << endl;

       int insertedCoins;
        insertedCoins = automat1.CoinSlot.updateCoinAmount();
        if (insertedCoins == -1) {
            cout << "Annulation de l'achat." << endl;
        }
        if (automat1.CoinSlot.getCoinAmount() < price)
        {
            automat1.CoinSlot.returnCoins(price);
        }
        if (automat1.CoinSlot.getCoinAmount() >= price)
        {
            automat1.dropSlot(selectedSlot);
            if (automat1.DropCheck.productReleased()) {
              cout << "Produit ejecte avec succes !" << endl;
            } else {
              cout << "Echec de l'ejection du produit." << endl;
            }

            automat1.CoinSlot.returnCoins(price);
        }
        automat1.CoinSlot.clear();
        cout << "Appuyez sur n'importe quelle touche pour returne au menu...";
        getch();
        system("cls");
        client(automat1);
          break;
    }
    // Code pour afficher les produits disponibles
    case 2:
        system("cls");
        automat1.print();
        client(automat1);
        break;
    case 3:
        return ;
        break;    
    default:
        break;
    }
}
void principale(Automat automat1);
// La fonction vendeur qui contient toutes les opérations qu'un vendeur peut effectuer
void vendeur(Automat automat1){
    int c;
    string productName;
    int id, price, motor1,motor2;
    cout << "                =================================================== " << endl;
    cout << "               |                  MENU vendeur                     |" << endl;
    cout << "                =================================================== " << endl;
    cout << "               |               1. Ajouter un produit               |" << endl;
    cout << "               |               2. Afficher les produits            |" << endl;
    cout << "               |               3. Pour modifier les informations   |" << endl;
    cout << "               |                        d'un produit               |" << endl;
    cout << "               |               4. pour reture au nemu principale   |" << endl;
    cout << "                =================================================== " << endl;
    cout << "                          Choix : ";
    cin>>c;
    switch (c)
    {
    case 1:{
        system("cls");
        int k;
        cout << "           ***************************************************" << endl;
        cout << "           *                   1. SmolSlot                   *" << endl;
        cout << "           *                   2. WideSlot                   *" << endl;
        cout << "           *                                                 *" << endl;
        cout << "           **************************************************" << endl;
        cout << "                                Choix :";
        cin>>k;
        switch (k)
        {
        case 1:{
            system("cls");
            cout<<endl;
            cout << "                         Entrez l'identifiant : ";
            cin >> id;
            if (!automat1.searchSlot(id)) {
               cout << "                         Entrez le nom du produit : ";
               cin >> productName;
               cout << "                         Entrez le prix : ";
               cin >> price;
               cout << "                         Entrez l'identifiant du moteur 1: ";
               cin >> motor1;
               automat1.addSlot(new SmallSlot(productName, id, price, motor1));
               //apres d ajoute un produit Remplissage du fichier avec les données finales de l'automate
               automat1.fillFile();
               automat1.fillAll();
               system("cls");
               cout << "                Produit ajoute avec succes." << endl;
               
            } 
            else{
               cout << "                Impossible, le slot est deja utilise!!!!!!" << endl;
            }
            vendeur(automat1);
            break;
            }
        case 2:{
            system("cls");
            cout << "                         Entrez l'identifiant : ";
            cin>>id;
            if (!automat1.searchSlot(id)){
                cout << "                         Entrez le nom du produit : ";
                cin>>productName;
                cout << "                         Entrez le prix : ";
                cin>>price;
                cout << "                         Entrez l'identifiant du moteur 1: ";
                cin>>motor1;
                cout << "                         Entrez l'identifiant du moteur 2: ";
                cin>>motor2;
                automat1.addSlot(new WideSlot(productName,id,price, motor1,motor2));
                //apres d ajoute un produit Remplissage du fichier avec les données finales de l'automate
                automat1.fillFile();
                automat1.fillAll();
                system("cls");
                cout << "                  Produit ajoute avec succes." << endl;
            }
            else{
               cout << "                Impossible, le slot est deja utilise!!!!!" << endl;
            }
            vendeur(automat1);
            break;
        }
        default:
            break;
        }
    }
        break;
    case 2:
        system("cls");
        automat1.print();
        cout << "Appuyez sur n'importe quelle touche pour returne au menu...";
        getch();
        system("cls");
        vendeur(automat1);
        break;
    case 3:
        int choix;
        automat1.print();
        cout << "                            1. Pour changer le nom du produit" << endl;
        cout << "                            2. Pour changer le prix" << endl;
        cout << "                            3. Pour changer le nom du produit et le prix" << endl;
        cout << "                                   Choix : ";
        cin >> choix;
        switch (choix)
        {
        case 1:
           cout << "                               Entrez l'ID de l'emplacement : ";
           cin >> id;
           cout << "                               Entrez le nouveau nom du produit : ";
           cin >> productName;
           automat1.changeSlot(id-1, productName);
           //apres de la modification Remplissage du fichier avec les données finales de l'automate
           automat1.fillFile();
           system("cls");
           vendeur(automat1);
           break;
        case 2:
           cout << "                               Entrez l'ID de l'emplacement : ";
           cin >> id;
           cout << "                               Entrez le nouveau prix : ";
           cin >> price;
           automat1.changeSlot(id-1, price);
           //apres de la modification Remplissage du fichier avec les données finales de l'automate
           automat1.fillFile();
           system("cls");
           vendeur(automat1);
           break;
        case 3:
           cout << "                               Entrez l'ID de l'emplacement : ";
           cin >> id;
           cout << "                               Entrez le nouveau nom du produit : ";
           cin >> productName;
           cout << "                               Entrez le nouveau prix : ";
           cin >> price;
           automat1.changeSlot(id-1, productName, price);
           //apres de la modification Remplissage du fichier avec les données finales de l'automate
           automat1.fillFile();
           system("cls");
           vendeur(automat1);
           break;
        default:
           break;
        }
        break;    
    case 4:
            system("cls");
            principale(automat1);
            break;    
    default:
        break;
    }
}
// La fonction principale qui appelle les fonctions selon le rôle de l'utilisateur
void principale(Automat automat1){
    int c;
    cout<<endl;
    cout << "                /___Bonjour, nous sommes ici pour vous.__/" <<endl;
    cout<<  "                ========================================="<<endl;
    cout<<  "                |            Menu principale            |"<<endl;
    cout<<  "                ========================================="<<endl;
    cout << "                |                                       |" <<endl;
    cout << "                |             1. Vous etes un           |" <<endl;
    cout << "                |                  vendeur?             |" <<endl;
    cout << "                |_______________________________________|" <<endl;
    cout << "                |                                       |" <<endl;
    cout << "                |             2. Vous etes un           |" <<endl;
    cout << "                |                  client?              |" <<endl;
    cout << "                |_______________________________________|" <<endl;
    cout << "                        Choose: ";
    cin>>c;
    switch (c)
    {
    case 1:
        system("cls");
        vendeur(automat1);
        break;
    case 2:
        system("cls");
        client(automat1);
        break;
    default:
        break;
    }
}
int main() {
    Automat automat1(10, 5);
    // Remplissage de l'automate à partir d'un fichier
    automat1.fillFromFile();
    automat1.fillAll();
    automat1.fillFile();
    // Lancement du menu principal
    principale(automat1);
    // Remplissage du fichier avec les données finales de l'automate
    automat1.fillFile();
    return 0;
}