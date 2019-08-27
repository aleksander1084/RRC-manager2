#ifndef PARAMETERLIST_H
#define PARAMETERLIST_H
#include <QObject>


class ParameterList
{
public:
    virtual ~ParameterList();
    virtual void setParameter() = 0;
    QString myName();
    QString mySymbol();


protected:
    QString name;
    QString symbol;
};

#endif // PARAMETERLIST_H
