#ifndef pfodUnhide_h
#define pfodUnhide_h
/*
 * (c)2014-2017 Forward Computing and Control Pty. Ltd.
 * NSW Australia, www.forward.com.au
 * This code is not warranted to be fit for any purpose. You may only use it at your own risk.
 * This code may be freely used for both private and commercial use
 * Provide this copyright is maintained.
 */
#include <stdint.h>
#include <Arduino.h>
#include "pfodDwgsBase.h"

class pfodUnhide : public pfodDwgsBase {
  public:
    pfodUnhide();
    pfodUnhide &idx(uint16_t _idx); // default 0 i.e. not set
    pfodUnhide &cmd(const char cmd); // default ' ' i.e. not set
    void init(Print *out, struct VALUES* _values);
    void send(char _startChar = '|');
};
#endif // pfodUnhide_h
