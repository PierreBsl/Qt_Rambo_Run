#ifndef UTILS_H
#define UTILS_H

#include <QtGlobal>     // for qrand()

class Utils {

public:

    static int randInt(int low, int high) {
        // Random number between low and high
        return qrand() % ((high + 1) - low) + low;
    }


};

#endif // UTILS_H
