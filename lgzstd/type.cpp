#include <typeinfo>
#include <cxxabi.h>
#include <string>

namespace util{

std::string GetTypeName(const char* name)
{
    int status = -1;
    char* clearName = abi::__cxa_demangle(name, NULL, NULL, &status);
    const char* const demangledName = (status==0) ? clearName : name;
    std::string ret_val(demangledName);
    free(clearName);
    return std::move(ret_val);
}

}
