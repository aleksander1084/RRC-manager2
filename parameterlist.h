#ifndef PARAMETERLIST_H
#define PARAMETERLIST_H
#include <QObject>


class ParameterList
{
public:
    virtual ~ParameterList();
    virtual void setParameter(QStringList parameterSections) = 0;
    virtual QStringList readParameter() = 0;//read from RRC module and get ready to send
    QString myName();
    QString mySymbol();
    bool myChanged();
    void myChanged(bool n_changed);


protected:
    QString name;
    QString symbol;
    bool changed = false;
};

#endif // PARAMETERLIST_H
