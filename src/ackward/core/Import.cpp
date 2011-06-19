#include <ackward/core/Import.hpp>

#include <boost/tokenizer.hpp>

#include <ackward/core/ExceptionTranslator.hpp>

namespace bp=boost::python;

namespace ackward { namespace core
{

bp::object
import(const std::string& name)
{
    try {
        if (name.empty())
            return builtins();
        
        return bp::import(name.c_str());
    } TRANSLATE_PYTHON_EXCEPTION();
}

bp::object
findObject(const std::string& module,
           const std::string& name)
{
    bp::object mod = import(module);
    
    try {
        return mod.attr(name.c_str());
    } catch (const bp::error_already_set&) {
        translatePythonException();
        throw;
    }
}

bp::object
findObject(const std::string& fullName)
{
    typedef boost::tokenizer<boost::char_separator<char> > 
        tokenizer;
    boost::char_separator<char> sep(".");
    tokenizer tokens(fullName, sep);
    std::vector<std::string> toks(tokens.begin(),
                                  tokens.end());
    std::vector<std::string>::iterator enditr =
        toks.end();
    --enditr;

    try {
        bp::object mod = import(toks.begin(), enditr);
        return mod.attr(enditr->c_str());
    } TRANSLATE_PYTHON_EXCEPTION();
}

}}
