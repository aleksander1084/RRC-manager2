#ifndef PARAMETERLIST_H
#define PARAMETERLIST_H
#include <QObject>


class ParameterList
{
public:
    virtual ~ParameterList() = 0;
    virtual void setParameter() = 0;
};

#endif // PARAMETERLIST_H
