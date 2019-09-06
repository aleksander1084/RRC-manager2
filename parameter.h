#ifndef PARAMETER_H
#define PARAMETER_H
#include <QObject>
#include <iostream>
#include <cstddef>
#include "parameterlist.h"
#include <QDebug>
#include <typeinfo>

template<typename valType = int, int numOfVal = 1>
/**
 * @brief The Parameter class represent single parameter of the module, depending on a template can hold different type and amount of values
 */
class Parameter : public ParameterList
{
public:
    /**
     * @brief Parameter default constructor used to define pointers of this type
     */
    Parameter()
    {

    }

    /**
     * @brief Parameter constructor used to define new parameters under pointers
     * @param n_name name of the new parameter
     * @param n_symbol symbol for the new parameter
     * @param n_values vector of values fo the new parameters
     * @param n_defaultValues vector of default values of parameter
     */
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

    /**
     * @brief Parameter oveloaded constructor when there is no need do define default values
     */
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

    /**
     * @brief readParameter implementation of the virtual method responsible for reading a parameter via based class pointer
     * @return
     */
    virtual QStringList readParameter()
    {
        QStringList respond;
        respond.push_back(mySymbol());
        respond.push_back(QString::number(valueType()));
        qDebug() << "readed parameter type is " << respond.at(1);
        respond += valueToQStringList();
        return respond;
    }

    /**
     * @brief setParameter implementation of the virtual method responsible for setting value of the parameter via based class pointer
     * @param parameterSections
     */
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

    /**
     * @brief operator == overload of operator
     */
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

    std::vector<valType> values; /**<vector of values*/
    std::vector<valType> defaultValues; /**<vector of default values*/

private:
    /**
     * @brief isBool test is this specific parameter containg bool type values
     */
    bool isBool()
    {
        return std::is_same<valType, bool>::value;
    }

    /**
     * @brief isUint8_t test is this specific parameter containing uint8_t type values
     */
    bool isUint8_t()
    {
       return std::is_same<valType, uint8_t>::value;
    }

    /**
     * @brief isUint16_t test is this specific parameter containing uint16_t type values
     */
    bool isUint16_t()
    {
        return std::is_same<valType, uint16_t>::value;
    }

    /**
     * @brief isFloat test is this specific parameter containing float type values
     */
    bool isFloat()
    {
        return std::is_same<valType, float>::value;
    }

    /**
     * @brief valueType test defining type of a holded value
     * @return 0 for bool, 1 for uint8_t and uint16_t, 2 for float (dropped extra value for uint16_t because later it uses the same coding, decoding and transmitions methods
     */
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

    /**
     * @brief valueToQStringList method converting vector of values into QStringList
     * @return
     */
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
