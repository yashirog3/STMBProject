#ifndef UUID_H
#define UUID_H
#include <ostream>
#include "usertypes.h"

/*uuid class refers to RFC 4122 */

class uuid{
  
  private:
    uint32 time_low;
    uint16 time_mid;
    uint16 time_hi_and_version;
    uint8 clock_seq_hi_and_reserved;
    uint8 clock_seq_low;
    unode node;

  public:
    uuid();
    ~uuid();
    friend std::ostream &operator<<(std::ostream &os, const uuid &id);
};


#endif
