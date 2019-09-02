#include "parameterlist.h"

ParameterList::~ParameterList(){}


QString ParameterList::myName()
{
    return name;
}

QString ParameterList::mySymbol()
{
    return symbol;
}

bool ParameterList::myChanged()
{
    return changed;
}

void ParameterList::myChanged(bool n_changed)
{
    changed = n_changed;
}
