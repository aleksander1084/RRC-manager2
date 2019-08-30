#ifndef RRCMODULEFLASHER_H
#define RRCMODULEFLASHER_H

#include <QObject>
#include "rrcmodule.h"

class RRCModuleFlasher : public RRCModule
{
    Q_OBJECT
public:
    RRCModuleFlasher();
    ~RRCModuleFlasher();

    int inputMode(int input);
    void inputMode(int input, int n_mode);
    bool mode();
    void mode(bool n_mode);
    float flashingPeriod();
    void flashingPeriod(float n_value);
    uint16_t timeout();
    void timeout(uint16_t n_value);
    uint16_t masterTimeout();
    void masterTimeout(uint16_t n_value);




protected:
    Parameter<bool, 1>      *mmode;
    Parameter<float, 1>     *mflashingPeriod;
    Parameter<uint16_t, 1>  *mtimeout;
    Parameter<uint16_t, 1>  *mmasterTimeout;
    Parameter<uint8_t, 1>   *mactiveInputs;
    Parameter<uint8_t, 1>   *mactivationInputs;
    Parameter<uint8_t, 1>   *mdeactivationInputs;
    Parameter<uint8_t, 1>   *mmaintainInputs;

    //advenced settings
    Parameter<uint8_t, 1>   *mgateDelay;
    Parameter<uint8_t, 1>   *mactiveInputsState;
    Parameter<uint8_t, 6>   *minputActivationDelay;
    Parameter<uint8_t, 6>   *minputDeactivationDelay;

};

#endif // RRCMODULEFLASHER_H
