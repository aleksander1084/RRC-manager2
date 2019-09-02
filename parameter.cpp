#include "parameter.h"

//template<typename valType, int numOfVal>
//Parameter<valType, numOfVal>::Parameter(QString n_name, QString n_symbol, valType n_values[])
//    : name(n_name), symbol(n_symbol)
//{
//    int passedValues = sizeof(n_values)/sizeof (n_values[0]);
//    for(int i = 0; i < passedValues; i++)
//    {
//        values[i] = n_values[i];
//    }
//    for(int i = passedValues; i < numOfVal; i++)
//    {
//        values[i] = defaultValues[i];
//    }

//}

//template<typename valType, int numOfVal>
//bool Parameter<valType, numOfVal>::operator==(const Parameter &q)
//{
//    if((sizeof(values)/sizeof(*values)))
//    {
//       return values == q.values;
//    }
//    else {
//       return false;
//    }
//}

//template<typename valType, int numOfVal>
//Parameter<valType, numOfVal>::~Parameter()
//{
//    delete values;
//    delete defaultValues;
//}

//template<>
//bool Parameter<bool>::isBool()
//{
//    return true;
//}


