from ackward.translation_unit import TranslationUnit
from ackward.elements import Function, Module

class LoggingModule(TranslationUnit):
    def __init__(self):
        objs=[
            Module(name='logging'),
            
            Function(
                name="getLogger",
                return_type="Logger"),
            
            Function(
                name='getLogger',
                signature=[('std::wstring', 'name')],
                return_type='Logger'),
            
            Function(
                name='getLoggerClass',
                return_type='boost::python::object'), # TODO: Better return type than this?
            
            Function(
                name='log',
                signature=[('Level', 'l'),
                           ('std::wstring', 'msg')]),
            
            Function(
                name='disable',
                signature=[('Level', 'l')]),
            
            Function(
                name='addLevelName',
                signature=[('Level', 'l'),
                           ('std::wstring', 'name')]),
            
            Function(
                name='getLevelName',
                signature=[('Level', 'l')]),
            
            # TODO: makeLogRecord
            
            Function(name='basicConfig'),
            
            Function(
                name='basicConfig',
                signature=[('boost::python::dict', 'kwargs')]),
            
            Function(name='shutdown'),
            
            Function(
                name='setLoggerClass',
                signature=[('boost::python::object', 'klass')]),
            ]
        
        for lvl in ['debug', 'info', 'warning', 'error', 'critical', 'exception']:
            objs.append(
                Function(
                    name=lvl,
                    signature=[('std::wstring', 'msg')]))

        super(LoggingModule, self).__init__(
            preprocessor_guard='INCLUDE_ACKWARD_LOGGING_MODULE_HPP',
            header_includes=[
                ('ackward', 'logging', 'Types.hpp')
                ],
            impl_includes=[
                ('string',),
                ('boost', 'python', 'dict.hpp'),
                ('boost', 'python', 'import.hpp'),
                ('boost', 'python', 'module.hpp'),
                ('boost', 'python', 'object.hpp'),
                ('ackward', 'logging', 'Logger.hpp'),
                ('ackward', 'logging', 'Module.hpp'),
                ],
            forward_declarations=[
                ('ackward', 'logging', 'class Logger'),
                ('boost', 'python', 'class dict')
                ],
            using=['namespace boost::python'],
            objects={ ('ackward', 'logging') : objs })

def definition():
    return LoggingModule()
