#ifndef PARAMETERLIST_H
#define PARAMETERLIST_H
#include <QObject>

/**
 * @brief The ParameterList class base class for the parameter, defines some virtual methods, holds members the same for all kinds of parameters
 */
class ParameterList
{
public:
    virtual ~ParameterList();
    /**
     * @brief setParameter definition of the virtual method responsible for seting values of a parameter
     * @param parameterSections output of the message processing
     */
    virtual void setParameter(QStringList parameterSections) = 0;

    /**
     * @brief readParameter definition of the virtual method responsible for returning values of the parameters
     * @return
     */
    virtual QStringList readParameter() = 0;

    /**
     * @brief myChanged method returning value of the changed flag
     * @return value of the changed flag
     */
    bool myChanged();

    /**
     * @brief myChanged method setting value of the changed flag
     * @param n_changed new value
     */
    void myChanged(bool n_changed);

    /**
     * @brief mySymbol method returning symbol of the paramether
     * @return
     */
    QString mySymbol();




protected:
    QString name; /**< name of the parameter */
    QString symbol; /**< symbol of the parameter */
    bool changed = false; /**< flag describing was value of the parameter changed before last update of the module memory (eliminates need of transmition off all parameters every time) */
};

#endif // PARAMETERLIST_H
