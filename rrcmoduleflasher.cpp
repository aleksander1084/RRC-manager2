#include "rrcmoduleflasher.h"
#include <math.h>

RRCModuleFlasher::RRCModuleFlasher()
{
    mmode = new Parameter<bool, 1>("Mode", "MODE", {false}, {true});
    mflashingPeriod = new Parameter<float, 1>("Flashing period", "FPD", {float(1.2)}, {float(1.2)});
    mtimeout = new Parameter<uint16_t, 1>("Time for deactivation", "TFD", {40}, {40});
    mmasterTimeout = new Parameter<uint16_t, 1>("Maximum activation duration", "MTFD", {1800}, {1800});
    mactiveInputs = new Parameter<uint8_t, 1>("Active inputs", "AIN", {0x7}, {0x0});
    mactivationInputs = new Parameter<uint8_t, 1>("Activation inputs", "ACIN", {0x1}, {0x0});
    mdeactivationInputs = new Parameter<uint8_t, 1>("Deactivation inputs", "DCIN", {0x02}, {0x00});
    mmaintainInputs = new Parameter<uint8_t, 1>("Maintain inputs", "MIN", {0x04}, {0x00});

    //advanced settings
    mgateDelay = new Parameter<uint8_t, 1>("Gate drop delay", "GDD", {0}, {0});
    mactiveInputsState = new Parameter<uint8_t, 1>("Active inputs states", "AINS", {0x00}, {0x00});
    minputActivationDelay = new Parameter<uint8_t, 6>("Inputs activation delays", "INAD", {0,0,0,0,0,0}, {0,0,0,0,0,0});
    minputDeactivationDelay = new Parameter<uint8_t, 6>("Inputs deactivation delays", "INDD", {0,0,0,0,0,0}, {0,0,0,0,0,0});

    paramneterList.push_back(mmode);
    paramneterList.push_back(mflashingPeriod);
    paramneterList.push_back(mtimeout);
    paramneterList.push_back(mmasterTimeout);
    paramneterList.push_back(mactiveInputs);
    paramneterList.push_back(mactivationInputs);
    paramneterList.push_back(mdeactivationInputs);
    paramneterList.push_back(mmaintainInputs);
    paramneterList.push_back(mgateDelay);
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

int RRCModuleFlasher::inputMode(int input)
{
//    qDebug() << "IN " << input;
//    qDebug() << "Un " << mactiveInputs->values[mactiveInputs->values.size() - 1] << " " << (mactiveInputs->values[mactiveInputs->values.size() - 1] & input );
//    qDebug() << "Act " << mdeactivationInputs->values[mactiveInputs->values.size() - 1] << " " << (mactiveInputs->values[mactiveInputs->values.size() - 1] & input );
//    qDebug() << "Dact " << mdeactivationInputs->values[mactiveInputs->values.size() - 1] << " " << (mdeactivationInputs->values[mactiveInputs->values.size() - 1] & input );
//    qDebug() << "Main " << mmaintainInputs->values[mactiveInputs->values.size() - 1] << " " << (mmaintainInputs->values[mactiveInputs->values.size() - 1] & input );
    if(((mactiveInputs->values[mactiveInputs->values.size() - 1] >> input) & 1U) == 0)
    {
        //(number >> n) & 1U;
        return 0;//unactive
    }
    else
    {
        if(((mactivationInputs->values[mactiveInputs->values.size() - 1] >> input) & 1U) == 1)
        {
            return 1; //activation
        }
        else if(((mdeactivationInputs->values[mactiveInputs->values.size() - 1] >> input) & 1U) == 1)
        {
            return 2; //deactivation
        }
        else if(((mmaintainInputs->values[mactiveInputs->values.size() - 1] >> input) & 1U) == 1)
        {
            return 3; //maintain
        }
        else
        {
            return -1; //error
        }
    }
}

void RRCModuleFlasher::inputMode(int input, int n_mode)// 0 = unactive, 1 = activation, 2 = deactivation, 3 = maintain
{
    switch (n_mode) {
        case 0: mactiveInputs->values[0] &= ~(1UL << input);
                mactivationInputs->values[0] &= ~(1UL << input);
                mdeactivationInputs->values[0] &= ~(1UL << input);
                mmaintainInputs->values[0] &= ~(1UL << input);
                break;
        case 1: mactiveInputs->values[0] |= 1UL << input;
                mactivationInputs->values[0] |= 1UL << input;
                mdeactivationInputs->values[0] &= ~(1UL << input);
                mmaintainInputs->values[0] &= ~(1UL << input);
                break;
        case 2: mactiveInputs->values[0] |= 1UL << input;
                mactivationInputs->values[0] &= ~(1UL << input);
                mdeactivationInputs->values[0] |= 1UL <<input;
                mmaintainInputs->values[0] &= ~(1UL << input);
                break;
        case 3: mactiveInputs->values[0] |= 1UL << input;
                mactivationInputs->values[0] &= ~(1UL << input);
                mdeactivationInputs->values[0] &= ~(1UL << input);
                mmaintainInputs->values[0] |= 1UL << input;
    }
}

bool RRCModuleFlasher::mode()
{
    return mmode->values[0];
}

void RRCModuleFlasher::mode(bool n_mode)
{
    mmode->values[0] = n_mode;
}

float RRCModuleFlasher::flashingPeriod()
{
    return mflashingPeriod->values[0];
}

void RRCModuleFlasher::flashingPeriod(float n_value)
{
    mflashingPeriod->values[0] = float(int(n_value*10)/10);
}

uint16_t RRCModuleFlasher::timeout()
{
    return mtimeout->values[0];
}

void RRCModuleFlasher::timeout(uint16_t n_value)
{
    mtimeout->values[0] = n_value;
}

uint16_t RRCModuleFlasher::masterTimeout()
{
    return mmasterTimeout->values[0];
}

void RRCModuleFlasher::masterTimeout(uint16_t n_value)
{
    mmasterTimeout->values[0] = n_value;
}


