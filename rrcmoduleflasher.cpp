#include "rrcmoduleflasher.h"

RRCModuleFlasher::RRCModuleFlasher()
{
    bool mode[] = {false};
    mmode = new Parameter<bool, 1>("Mode", "MODE", mode, sizeof (mode)/sizeof (mode[0]));
    float fpd[] = {float(1.2)};
    mflashingPeriod = new Parameter<float, 1>("Flashing period", "FPD", fpd, sizeof(fpd)/sizeof (fpd[0]));
    uint16_t tfd[] = {40};
    mtimeout = new Parameter<uint16_t, 1>("Time for deactivation", "TFD", tfd, sizeof (tfd)/sizeof (tfd[0]));
    mmasterTimeout = new Parameter<uint16_t, 1>("Maximum activation duration", "MTFD", tfd, sizeof (tfd)/sizeof (tfd[0]));
    uint8_t gdd[] = {0};
    mgateDelay = new Parameter<uint8_t, 1>("Gate drop delay", "GDD", gdd, sizeof(gdd)/sizeof (gdd[0]));
    mactiveInputs = new Parameter<uint8_t, 1>("Active inputs", "AIN", gdd, sizeof(gdd)/sizeof (gdd[0]));
    mactivationInputs = new Parameter<uint8_t, 1>("Activation inputs", "ACIN", gdd, sizeof(gdd)/sizeof (gdd[0]));
    mdeactivationInputs = new Parameter<uint8_t, 1>("Deactivation inputs", "DCIN", gdd, sizeof(gdd)/sizeof (gdd[0]));
    mmaintainInputs = new Parameter<uint8_t, 1>("Maintain inputs", "MIN", gdd, sizeof(gdd)/sizeof (gdd[0]));

    //advanced settings
    mactiveInputsState = new Parameter<uint8_t, 1>("Active inputs states", "AINS", gdd, sizeof(gdd)/sizeof (gdd[0]));
    uint8_t inad[6] = {};
    minputActivationDelay = new Parameter<uint8_t, 6>("Inputs activation delays", "INAD", inad, sizeof(inad)/sizeof (inad[0]));
    minputDeactivationDelay = new Parameter<uint8_t, 6>("Inputs deactivation delays", "INDD", inad, sizeof(inad)/sizeof (inad[0]));

    paramneterList.push_back(mmode);
    paramneterList.push_back(mflashingPeriod);
    paramneterList.push_back(mtimeout);
    paramneterList.push_back(mmasterTimeout);
    paramneterList.push_back(mgateDelay);
    paramneterList.push_back(mactiveInputs);
    paramneterList.push_back(mactivationInputs);
    paramneterList.push_back(mdeactivationInputs);
    paramneterList.push_back(mmaintainInputs);
    paramneterList.push_back(mactiveInputsState);
    paramneterList.push_back(minputActivationDelay);
    paramneterList.push_back(minputDeactivationDelay);
}

RRCModuleFlasher::~RRCModuleFlasher()
{
    delete mmode;
    delete mflashingPeriod;
    delete mtimeout;
    delete mmasterTimeout;
    delete mgateDelay;
    delete mactiveInputs;
    delete mactivationInputs;
    delete mdeactivationInputs;
    delete mmaintainInputs;
    delete mactiveInputsState;
    delete minputActivationDelay;
    delete minputDeactivationDelay;
}
