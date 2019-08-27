#include "rrcmodule.h"

RRCModule::RRCModule()
{
    uint8_t sn[] = {0,0,0,0,0};
    mserialNumber =     new Parameter<uint8_t, 5>   ("Serial number", "SN", sn, sizeof (sn)/sizeof (sn[0]));
    msoftwareVersion =  new Parameter<uint8_t, 5>   ("Software version", "SV", sn, sizeof (sn)/sizeof (sn[0]));
    uint8_t lu[] = {0,0,0};
    mlastUpdate =       new Parameter<uint8_t, 3>   ("Last update", "LU", lu, sizeof (lu)/sizeof (lu[0]));
    bool auth[] = {false};
    mauthenticity =     new Parameter<bool, 1>      ("Authenticity", "AU", auth, sizeof (auth)/sizeof (auth[0]));
    uint8_t rsid[] = {1};
    mRS485ID =          new Parameter<uint8_t, 1>   ("RS485 identifier", "RS4", rsid, sizeof (rsid)/sizeof (rsid[0]));
    mchipIDSig =        new Parameter<uint8_t, 3>   ("Chip signature", "CHID", lu, sizeof (lu)/sizeof (lu[0]));
    uint8_t chipSN[] = {0,0,0,0,0,0,0,0,0};
    mchipIDSN =         new Parameter<uint8_t, 9>   ("Chip serial number", "CHSN", chipSN, sizeof (chipSN)/sizeof (chipSN[0]));

    paramneterList.push_back(mserialNumber);
    paramneterList.push_back(msoftwareVersion);
    paramneterList.push_back(mlastUpdate);
    paramneterList.push_back(mauthenticity);
    paramneterList.push_back(mRS485ID);
    paramneterList.push_back(mchipIDSig);
    paramneterList.push_back(mchipIDSN);
}

RRCModule::~RRCModule()
{
    delete mserialNumber;
    delete msoftwareVersion;
    delete mlastUpdate;
    delete mauthenticity;
    delete mRS485ID;
    delete mchipIDSig;
    delete mchipIDSN;
    std::for_each(paramneterList.begin(), paramneterList.end(), [](ParameterList* param){delete param;});

}

