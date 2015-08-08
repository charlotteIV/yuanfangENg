#ifndef RANDOM_H
#define RANDOM_H

#include <time.h>
#include <stdlib.h>

class Random
{
public:
    //
    Random(unsigned int max = 100, bool timeVariable = false){
        this->max = max;

        // The random values are not same in each excute time
        if(timeVariable){
            srand((int)time(NULL));
        }
    }

    // range: 0-seed
    unsigned int NextInteger(){
        return rand() % max;
    }

    float NextFloat(){
        return (rand() % max) * 1.0f / max;
    }

private:
    unsigned int max;
};

#endif // RANDOM_H
