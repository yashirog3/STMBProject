#include <iostream>
#include <sys/time.h> //We need this C lib to work with more precision timestamp
#include <regex> //To find mac address of a output system ip command
#include "uuid.h" 
#include "state.h"

#define LOCK
#define UNLOCK

//Functions signatures
uint64 getTimeStamp();
static uint16 true_random();
static uint16 clockseq = 0;
unode getIeeeNode();

uuid::uuid(){

    node = {0};
    uint64 timestamp = getTimeStamp();
    state estado;
    static bool inited = false;
    if(clockseq == 0){
        clockseq = true_random();
        inited = true;
    };
    
        
    time_low =(uint32) timestamp & 0xFFFFFFFF;
    time_mid = (uint16) ((timestamp >> 32) & 0xFFFF);
    time_hi_and_version = ((uint16) ((timestamp >> 48) & 0x0FFF)) | (1 << 12);
    clock_seq_low = clockseq & 0xFF;
    clock_seq_hi_and_reserved = ((clockseq & 0x3F00) >> 8) | 0x80;
    node = getIeeeNode();
}

uuid::~uuid(){


};

uint64 getSystemTime(){

    struct timeval tempo;
    gettimeofday(&tempo, (struct timezone *) 0);    
    return(((uint64) tempo.tv_sec * 10000000) 
    + ((uint64)tempo.tv_usec * 10) 
    + I64(0x01B21DD213814000));

};



uint64 getTimeStamp(){

    uint64 timestamp;
    uint64 time_now;
    uint16 theticks;
    static uint64 time_last;
    static bool inited = false;

    if(!inited){
        
        time_now = getSystemTime();
        theticks = UUIDS_PER_TICK;
        inited = true;
    }      

    for(;;){

        time_now = getSystemTime();
        if(time_last != time_now){
            
            theticks = 0;
            time_last = time_now;
            break;
        }

        if(theticks < UUIDS_PER_TICK){            
            theticks++;
            break;
        }
    };

    return time_now + theticks;

}


static uint16 true_random(){

    static bool inited = false;
    uint64 time_now;
    if(!inited){        
     time_now = getSystemTime() / UUIDS_PER_TICK;   
     srand((unsigned int) (((time_now >> 32) ^time_now) &0xFFFFFFFF));
     inited = true;
    }

    return rand();
}

int charToHex(char ch){

    int aux = (int) ch;
    if(aux >= 48 && aux <= 57)
        return aux - 48;
    if(aux >= 65 && aux <= 70)
        return aux - 55;
    if(aux >= 97 && aux <= 102)
        return aux - 87;    
    return 16;

}

unode getIeeeNode(){
    FILE * arq = popen(COMMAND, "r");
    char buffer[100] = {0};        
    std::regex macaddress("((..:){5}..)");
    int j = 0;
    unode node;
    while(fscanf(arq, "%100s", buffer) != EOF){
        if(std::regex_match(buffer, macaddress)){
            for(int i = 0; i < 17; i+=3){                
                node.node[j++] = ((charToHex(buffer[i]) << 4) + charToHex(buffer[i+1]));
            };
            break;
        };
    };    
    return node;
}

std::ostream &operator<<(std::ostream &os, const uuid &id){ 
    os << std::hex << id.time_low << "-" << id.time_mid << "-" << id.time_hi_and_version \
    << "-" << (int) id.clock_seq_hi_and_reserved << (int) id.clock_seq_low \
    << "-" << (int) id.node.node[0] << (int) id.node.node[1] << (int) id.node.node[2] \
    << (int) id.node.node[3] << (int) id.node.node[4] << (int) id.node.node[5];
    return os; 
};

//Write_state and Read_State

void Write_State(uint64 timestamp, uint16 clockseq, unode node){

    FILE * arq = fopen("state", "wb");
    if(arq != NULL){

        fprintf(arq, "%x
    };
    

};
