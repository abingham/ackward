#include <ackward/core/Import.hpp>

#include <boost/tokenizer.hpp>

using namespace boost::python;

namespace ackward { namespace core
{

object
import(const std::string& name)
{
    typedef boost::tokenizer<boost::char_separator<char> > 
        tokenizer;
    boost::char_separator<char> sep(".");
    tokenizer tokens(name, sep);
    return ackward::core::import(tokens.begin(), tokens.end());
}

object
findObject(const std::string& module,
           const std::string& name)
{
    object mod = import(module);
    
    try {
        return mod.attr(name.c_str());
    } catch (const boost::python::error_already_set&) {
        translatePythonException();
        throw;
    }
}

object
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
        object mod = import(toks.begin(), enditr);
        return mod.attr(enditr->c_str());
    } TRANSLATE_PYTHON_EXCEPTION();
}

}}
