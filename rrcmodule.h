#ifndef RRCMODULE_H
#define RRCMODULE_H
#include <QObject>
#include <QDebug>
#include "parameter.h"
/**
 * @brief The RRCModule class class defines basic parameters for all modules
 */
class RRCModule : public QObject
{

    Q_OBJECT

public:
    RRCModule();
    ~RRCModule();
    QString serialNumber();
    void serialNumber(QString n_serialNumber);
    QString softwareVersion();
    void softwareVersion(QString n_softwareVersion);
    QString lastUpdate();
    void lastUpdate(int day, int month, int year);
    bool checkDeviceAuthenticity();

    template<typename typVal>
    std::vector<typVal> readParameter(QString n_symbol)
    {
        for (std::vector<ParameterList*>::iterator it = paramneterList.begin(); it != paramneterList.end(); ++it)
        {
            if((*it)->mySymbol() == n_symbol)
            {
                Parameter<typVal> *temp = ((Parameter<typVal>*)((*it)));
                qDebug()<< "temp size: " << temp->values.size();
                qDebug() << "values: ";

                for (unsigned int i = 0;i < temp->values.size();i++) {
                    qDebug() << temp->values[i];
                }
                return temp->values;
            }
        }
        std::vector<typVal> errorOcured;
        return errorOcured;
    }

    template<typename typVal>//TODO: add default values constructor
                             //TODO: change n_val from typVal arrayo to std::vector<typVal> that can be nitialized like {1,2,3}
    void setParameterValue(QString n_symbol, typVal n_val[], int n_valSize){
        for (std::vector<ParameterList*>::iterator it = paramneterList.begin(); it != paramneterList.end(); ++it)
        {
            if((*it)->mySymbol() == n_symbol)
            {
                for (int i = 0; i < n_valSize; ++i)
                {
                    ((Parameter<typVal>*)((*it)))->values[i] = n_val[i];
                }

                return;
            }
        }
    }

protected:
    Parameter<uint8_t, 5> *mserialNumber;
    Parameter<uint8_t, 5> *msoftwareVersion;
    Parameter<uint8_t, 3> *mlastUpdate;
    Parameter<bool, 1> *mauthenticity;
    Parameter<uint8_t, 1> *mRS485ID;
    Parameter<uint8_t, 3> *mchipIDSig;
    Parameter<uint8_t, 9> *mchipIDSN;
    std::vector<ParameterList *> paramneterList;
};

#endif // RRCMODULE_H
