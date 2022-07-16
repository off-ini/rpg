//
// Created by infini on 16/07/22.
//

#ifndef RPG_DISTRIBUTION_H
#define RPG_DISTRIBUTION_H

#include <random>

class Gen{
public:
    static int distNumber(int nim, int max){
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> gen(0, 3);

        return gen(rng);
    }
};

#endif //RPG_DISTRIBUTION_H
