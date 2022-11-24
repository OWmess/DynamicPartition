//
// Created by owmess on 2022/11/23.
//
#include <iostream>
#include "OS.h"
#include <memory>

#define MAXSIZE 1000
using namespace std;

int main(){


    start:
    {
        OS os(MAXSIZE);

        if(!os.createPartition())
            goto start;


    }

    return 0;
}
