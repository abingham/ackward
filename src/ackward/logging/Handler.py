from ackward.cls import Class, Method
from ackward.translation_unit import ClassTranslationUnit

class Handler(ClassTranslationUnit):

    def preprocessor_guard(self):
        return 'INCLUDE_ACKWARD_LOGGING_HANDLER_HPP'

    def forward_declarations(self):
        return [
            ('ackward', 'logging', 'class Formatter'),
            ('ackward', 'logging', 'class Filter'),
            ('ackward', 'logging', 'class LogRecord'),
            ]

    def header_includes(self):
        return [
            ('ackward', 'core', 'Object.hpp'),
            ('ackward', 'logging', 'Types.hpp'),
            ]

    def impl_includes(self):
        return super(Handler, self).impl_includes() + [
            ('ackward', 'logging', 'Formatter.hpp'),
            ('ackward', 'logging', 'Filter.hpp'),
            ('ackward', 'logging', 'Handler.hpp'),
            ('ackward', 'logging', 'LogRecord.hpp'),
            ]

    def handler_class(self):
        c = Class(
            name='Handler',
            wrapped_class='logging.Handler')
        
        Method(
            cls=c,
            name='setLevel',
            signature=[('Level', 'level')])

        Method(
            cls=c,
            name='setFormatter',
            signature=[('Formatter', 'f')])

        Method(
            cls=c,
            name='addFilter',
            signature=[('Filter', 'f')])

        Method(
            cls=c,
            name='removeFilter',
            signature=[('Filter', 'f')])

        Method(
            cls=c,
            name='flush',
            const=True)

        Method(
            cls=c,
            name='close')

        Method(
            cls=c,
            name='emit',
            signature=[('LogRecord', 'r')],
            const=True,
            virtual=Method.VIRTUAL)

        return c

    def objects(self):

# class FileHandler : public Handler
# {
# public:
#     FileHandler(const std::wstring& filename,
#                 const std::string& mode="a", 
#                 const std::string& encoding="", 
#                 bool delay=false);
# };

# class WatchedFileHandler : public Handler
# {
# public:
#     WatchedFileHandler(const std::wstring& filename,
#                        const std::string& mode="a", 
#                        const std::string& encoding="",
#                        bool delay=false);
# };

# class SocketHandler : public Handler
# {
# public:
#     SocketHandler(const std::wstring& host,
#                   unsigned int port);
# };

# template <typename Impl>
# class Handler_ : public Handler
# {
# public:
#     Handler_() :
#         Handler ( module().attr("Handler")() )
#         {
#             boost::python::object func = 
#                 boost::python::make_function(
#                     Handler_<Impl>::emit_impl);
#             obj().attr("emit") = func;
#         }

# private:
#     static void emit_impl(boost::python::object o)
#         {
#             LogRecord lr(o);
#             Impl::emit_(lr);
#         }
# };

# class NullHandler : public Handler_<NullHandler>
# {
# public:
#     static void emit_(const LogRecord&) {}
# };

        return {
            ('ackward', 'logging') : [
                self.handler_class(),
                ]
            }

def definition():
    return Handler()
    
        
