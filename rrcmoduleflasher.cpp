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
    mmode = nullptr;
    delete mflashingPeriod;
    mflashingPeriod = nullptr;
    delete mtimeout;
    mtimeout = nullptr;
    delete mmasterTimeout;
    mmasterTimeout = nullptr;
    delete mgateDelay;
    mgateDelay = nullptr;
    delete mactiveInputs;
    mactiveInputs  = nullptr;
    delete mactivationInputs;
    mactivationInputs = nullptr;
    delete mdeactivationInputs;
    mdeactivationInputs = nullptr;
    delete mmaintainInputs;
    mmaintainInputs = nullptr;
    delete mactiveInputsState;
    mactiveInputsState = nullptr;
    delete minputActivationDelay;
    minputActivationDelay = nullptr;
    delete minputDeactivationDelay;
    minputDeactivationDelay = nullptr;
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
    uint8_t tempActiveInputs = mactiveInputs->values[0];
    uint8_t tempActivationInputs = mactivationInputs->values[0];
    uint8_t tempDeactivationInputs = mdeactivationInputs->values[0];
    uint8_t tempMaintainInputs = mmaintainInputs->values[0];
    switch (n_mode) {
        case 0: tempActiveInputs &= ~(1UL << input);
                tempActivationInputs &= ~(1UL << input);
                tempDeactivationInputs &= ~(1UL << input);
                tempMaintainInputs &= ~(1UL << input);
                break;
        case 1: tempActiveInputs |= 1UL << input;
                tempActivationInputs |= 1UL << input;
                tempDeactivationInputs &= ~(1UL << input);
                tempMaintainInputs &= ~(1UL << input);
                break;
        case 2: tempActiveInputs |= 1UL << input;
                tempActivationInputs &= ~(1UL << input);
                tempDeactivationInputs |= 1UL <<input;
                tempMaintainInputs &= ~(1UL << input);
                break;
        case 3: tempActiveInputs |= 1UL << input;
                tempActivationInputs &= ~(1UL << input);
                tempDeactivationInputs &= ~(1UL << input);
                tempMaintainInputs |= 1UL << input;
    }
    if(tempActiveInputs != mactiveInputs->values[0]
            || tempActivationInputs != mactivationInputs->values[0]
            || tempDeactivationInputs != mdeactivationInputs->values[0]
            || tempMaintainInputs != mmaintainInputs->values[0])
    {
        mactiveInputs->myChanged(true);
        mactivationInputs->myChanged(true);
        mdeactivationInputs->myChanged(true);
        mmaintainInputs->myChanged(true);
    }
}

bool RRCModuleFlasher::mode()
{
    return mmode->values[0];
}

void RRCModuleFlasher::mode(bool n_mode)
{
    if( mmode->values[0] != n_mode)
    {
        mmode->values[0] = n_mode;
        mmode->myChanged(true);
    }

}

float RRCModuleFlasher::flashingPeriod()
{
    return mflashingPeriod->values[0];
}

void RRCModuleFlasher::flashingPeriod(float n_value)
{
    if(mflashingPeriod->values[0] > float(int(n_value*10)/10.0)
            || mflashingPeriod->values[0] < float(int(n_value*10)/10.0))
    {
        mflashingPeriod->values[0] = float(int(n_value*10)/10.0);
        mflashingPeriod->myChanged(true);
    }

}

uint16_t RRCModuleFlasher::timeout()
{
    return mtimeout->values[0];
}

void RRCModuleFlasher::timeout(uint16_t n_value)
{
    if(mtimeout->values[0] != n_value)
    {
        mtimeout->values[0] = n_value;
        mtimeout->myChanged(true);
    }
}

uint16_t RRCModuleFlasher::masterTimeout()
{
    return mmasterTimeout->values[0];
}

void RRCModuleFlasher::masterTimeout(uint16_t n_value)
{
    if(mmasterTimeout->values[0] != n_value)
    {
        mmasterTimeout->values[0] = n_value;
        mmasterTimeout->myChanged(true);
    }

}

uint8_t RRCModuleFlasher::gateDelay()
{
    return mgateDelay->values[0];
}

void RRCModuleFlasher::gateDelay(uint8_t n_value)
{
    if(mgateDelay->values[0] != n_value)
    {
        mgateDelay->values[0] = n_value;
        mgateDelay->myChanged(true);
    }

}

bool RRCModuleFlasher::activeInputState(int input)
{
    return bool((mactiveInputsState->values[0] >> input) & 1UL);
}

void RRCModuleFlasher::activeInputState(int input, bool n_value)
{
    uint8_t tempActiveInputsState = mactiveInputsState->values[0];

    if(n_value)
    {
        tempActiveInputsState |= 1UL << input;
    }
    else
    {
        tempActiveInputsState &= ~(1UL << input);
    }

    if(tempActiveInputsState != mactiveInputsState->values[0])
    {
        mactiveInputsState->values[0] = tempActiveInputsState;
        mactiveInputsState->myChanged(true);
    }
}

uint8_t RRCModuleFlasher::inputActivationDelay(int input)
{
    return minputActivationDelay->values[unsigned(input)];
}

void RRCModuleFlasher::inputActivationDelay(int input, uint8_t n_value)
{
    if(minputActivationDelay->values[unsigned(input)] != n_value)
    {
        minputActivationDelay->values[unsigned(input)] = n_value;
        minputActivationDelay->myChanged(true);
    }

}

uint8_t RRCModuleFlasher::inputDeactivationDelay(int input)
{
    return minputDeactivationDelay->values[unsigned(input)];
}

void RRCModuleFlasher::inputDeactivationDelay(int input, uint8_t n_value)
{
    if(minputDeactivationDelay->values[unsigned(input)] != n_value)
    {
        minputDeactivationDelay->values[unsigned(input)] = n_value;
        minputDeactivationDelay->myChanged(true);
    }

}


