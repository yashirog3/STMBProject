#ifndef STATE_H_
#define STATE_H_
#include "usertypes.h"

class State{

    uint64 timestamp;
    uint16 clockseq;
    unode node;

    public:
        State();
        ~State();
}


#endif //STATE_H_

