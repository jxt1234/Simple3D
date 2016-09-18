#include "lowlevelAPI/IFunctionTable.h"
class DefaultFunctionTable: public IFunctionTable
{
public:
virtual void* vGetFunction(const std::string& name);
};
