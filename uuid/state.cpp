#include "state.h"

State::State(){ //Leitura

    if(!inited){
        FILE * arq = open("gstate", "rb");
        if(!arq == NULL){
            fread(timestamp, clockseq, node, 1, arq);
            fclose(arq);
        }else{
           timestamp = 0;
           clockseq = 0;
           node = {0};
        }
        inited = true;
    }
};

State::~State(){

    FILE * arq = open("gstate", "wb");
    if(!arq == NULL){
        fwrite(timestamp, clockseq, node, 1, arq);
        fclose(arq);
    }
};
