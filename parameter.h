#ifndef PARAMETER_H
#define PARAMETER_H
#include <QObject>
#include <iostream>
#include <cstddef>
#include "parameterlist.h"
#include <QDebug>

template<typename valType = int, int numOfVal = 1>class Parameter : public ParameterList
{
public:
    Parameter()
    {

    }
    Parameter(QString n_name, QString n_symbol, valType n_values[], int valSize)
    {
        name = n_name;
        symbol = n_symbol;
        qDebug() << name;
        for(int i = 0; i < valSize; i++)
        {
            values.push_back(n_values[i]);
            //qDebug() << values[i];
        }
        for(int i = valSize; i < numOfVal; i++)
        {
            values.push_back(defaultValues[i]);
            //qDebug() << values[i];
        }

    }

    void setParameter()
    {

    }
    void setParameter(QString n_name, QString n_symbol, valType n_values[], int valSize)
    {
        name = n_name;
        symbol = n_symbol;
        for(int i = 0; i < valSize; i++)
        {
            values[i] = n_values[i];
        }
        for(int i = valSize; i < numOfVal; i++)
        {
            values[i] = defaultValues[i];
        }
    }

//    void setParameterValue(valType n_values[], int valSize)
//    {
//        for(int i = 0; i < valSize; i++)
//        {
//            values[i] = n_values[i];
//        }
//        for(int i = valSize; i < numOfVal; i++)
//        {
//            values[i] = defaultValues[i];
//        }
//    }

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

    std::vector<valType> values;
    std::vector<valType> defaultValues;
//    valType values[numOfVal];
//    valType defaultValues[numOfVal];
private:

};

#endif // PARAMETER_H
