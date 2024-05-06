#include <iostream>
#include <vector>

using namespace std;
class CoinSlot {
private:
    int coinAmount;
    const vector<int> coinValues;

public:
    CoinSlot() : coinAmount(0), coinValues({200, 100, 50, 20, 10, 5, 1}) {}
    
    int updateCoinAmount() {
        int insertedCoin;
        cout << "Inserez une piece (et entrez -1 pour annuler) : ";
        cin >> insertedCoin;
        
        if (insertedCoin == -1) {
            return -1; 
        }
        bool validCoin = false;
        for (int i=0;i<coinValues.size();i++) {
            if (insertedCoin == coinValues[i]) {
                validCoin = true;
                break;
            }
        }
        if (!validCoin) {
            cout << "Cette piece est invalide!" << endl;
            updateCoinAmount();
        }
        coinAmount =coinAmount+ insertedCoin;
        return insertedCoin;
    }
    int getCoinAmount() const {
        return coinAmount;
    }
    
    void clear() {
        coinAmount = 0;
    }
    
    void returnCoins(int currentPrice) {
        cout << "Remboursement des pieces : ";
        int change = coinAmount - currentPrice;
        if (change < 0) {
            cout << "Fonds insuffisants !" << endl;
            return;
        }
        if(change==0){
            cout << "howa hadak" << endl;
        }
        for (int i=0;i<coinValues.size();i++) {
            int numCoins = change / coinValues[i];
            if (numCoins > 0) {
                cout << numCoins << " x " << coinValues[i] / 100.0 << " euro, ";
                change =change -(numCoins * coinValues[i]);
            }
        }
        cout << endl;
    }
};