#ifndef PARAMETER_H
#define PARAMETER_H
#include <QObject>
#include <iostream>
#include <cstddef>
#include "parameterlist.h"
#include <QDebug>
#include <typeinfo>

template<typename valType = int, int numOfVal = 1>class Parameter : public ParameterList
{
public:
    Parameter()
    {

    }
    Parameter(QString n_name, QString n_symbol, std::vector<valType> n_values, std::vector<valType> n_defaultValues)
    {
        name = n_name;
        symbol = n_symbol;
        //qDebug() << name;
        int valSize = n_values.size();
        for(int i = 0; i < valSize; i++)
        {
            values.push_back(n_values[i]);
            defaultValues.push_back(n_defaultValues[i]);
            //qDebug() << values[i];
        }
        for(int i = valSize; i < numOfVal; i++)
        {
            values.push_back(defaultValues[i]);
            //qDebug() << values[i];
        }

    }
    Parameter(QString n_name, QString n_symbol, std::vector<valType> n_values)
    {
        name = n_name;
        symbol = n_symbol;
        //qDebug() << name;
        int valSize = n_values.size();
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

    virtual QStringList readParameter()
    {
        QStringList respond;
        respond.push_back(mySymbol());
        respond.push_back(QString::number(valueType()));
        qDebug() << "readed parameter type is " << respond.at(1);
        respond += valueToQStringList();
        return respond;
    }

    //void setParameter();

    virtual void setParameter(QStringList parameterSections)
    {
        myChanged(false);
        //QString test = parameterSections.at(0) + ": ";
        for (unsigned i = 0; i < values.size(); ++i) {
            values[i] = valType(parameterSections.at(i+2).toFloat());
            //test += values[i];
        }
        //qDebug() << test;
    }

//    void setParameter(QString n_name, QString n_symbol, valType n_values[], int valSize)
//    {
//        name = n_name;
//        symbol = n_symbol;
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

    ~Parameter()
    {

    }

    std::vector<valType> values;
    std::vector<valType> defaultValues;
//    valType values[numOfVal];
//    valType defaultValues[numOfVal];
private:

    bool isBool()
    {
        return std::is_same<valType, bool>::value;
    }

    bool isUint8_t()
    {
       return std::is_same<valType, uint8_t>::value;
    }

    bool isUint16_t()
    {
        return std::is_same<valType, uint16_t>::value;
    }

    bool isFloat()
    {
        return std::is_same<valType, float>::value;
    }

    int valueType()
    {
        if(isBool())
            return 0;
        else if(isUint8_t())
            return 1;
        else if(isUint16_t())
            return 1;
        else if(isFloat())
            return 2;
        else
            return -1;//TODO: error handler
    }

    QStringList valueToQStringList()
    {
        QStringList response;

        for (unsigned long long i = 0; i < values.size(); ++i)
        {
            response.push_back(QString::number(double(values.at(i)), 'f', 1));
        }

        return response;
    }

};







#endif // PARAMETER_H
