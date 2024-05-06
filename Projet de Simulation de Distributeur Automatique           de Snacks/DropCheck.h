#include <cstdlib>
using namespace std;

class DropCheck {
public:
    bool productReleased() {
        int randNum = rand() % (100) + 1;
        if (randNum <= 90) {
            return true;
        } else {
            return false;
        }
    }
};