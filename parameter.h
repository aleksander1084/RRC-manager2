#ifndef PARAMETER_H
#define PARAMETER_H
#include <QObject>
#include <iostream>
#include <cstddef>
#include "parameterlist.h"

template<typename valType = int, int numOfVal = 1>class Parameter : public ParameterList
{
public:
    Parameter()
    {

    }
    Parameter(QString n_name, QString n_symbol, valType n_values[], int valSize)
        : name(n_name), symbol(n_symbol)
    {
        for(int i = 0; i < valSize; i++)
        {
            values[i] = n_values[i];
        }
        for(int i = valSize; i < numOfVal; i++)
        {
            values[i] = defaultValues[i];
        }

    }

    void setParameter()
    {

    }
    void setParameter(QString n_name, QString n_symbol, valType n_values[])
    {

    }

    bool operator==( const Parameter &q )
    {
        if((sizeof(values)/sizeof(*values)))
        {
           return values == q.values;
        }
        else {
           return false;
        }
    }

    //valType &operator=()
    ~Parameter()
    {

    }
    QString name;
    QString symbol;
    std::array<valType, numOfVal> values;
    std::array<valType, numOfVal> defaultValues;
//    valType values[numOfVal];
//    valType defaultValues[numOfVal];
private:

};

#endif // PARAMETER_H
