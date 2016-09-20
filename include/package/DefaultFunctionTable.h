#ifndef PACKAGE_DEFAULTFUNCTIONTABLE_H
#define PACKAGE_DEFAULTFUNCTIONTABLE_H
#include "lowlevelAPI/IFunctionTable.h"
class DefaultFunctionTable: public IFunctionTable
{
public:
virtual void* vGetFunction(const std::string& name);
};
#endif
