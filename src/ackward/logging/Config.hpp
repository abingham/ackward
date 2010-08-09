#ifndef INCLUDE_ACKWARD_LOGGING_CONFIG_HPP
#define INCLUDE_ACKWARD_LOGGING_CONFIG_HPP

#include <string>

namespace boost { namespace python { class dict; } }

namespace ackward { namespace logging
{

void fileConfig(const std::wstring& filename);
void fileConfig(const std::wstring& filename,
                boost::python::dict defaults);

void listen();
void listen(unsigned int port);

void stopListening();

}}

#endif
