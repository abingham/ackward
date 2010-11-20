from ackward.translation_unit import TranslationUnit
from ackward.elements import Function

class Module(TranslationUnit):
    def preprocessor_guard(self):
        return 'INCLUDE_ACKWARD_LOGGING_MODULE_HPP'

    def header_includes(self):
        return [
            ('ackward', 'logging', 'Types.hpp')
            ]

    def impl_includes(self):
        return [
            ('string',),
            ('boost', 'python', 'dict.hpp'),
            ('boost', 'python', 'import.hpp'),
            ('boost', 'python', 'module.hpp'),
            ('boost', 'python', 'object.hpp'),
            ('ackward', 'logging', 'Logger.hpp'),
            ]

    def forward_declarations(self):
        return [
            ('ackward', 'logging', 'class Logger'),
            ('boost', 'python', 'class dict')
            ]

    def using(self):
        return ['namespace boost::python']

    def namespace(self):
        return ('ackward', 'logging')

    def objects(self):
        objs = [
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
            
        return { ('ackward', 'logging') : objs }

def definition():
    return Module()
