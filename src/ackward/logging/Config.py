from ackward.translation_unit import TranslationUnit
from ackward.elements import Function

class Config(TranslationUnit):

    functions = [
        Function(
            name='fileConfig',
            signature=[
                ('std::wstring', 'filename')]),
        
        Function(
            name='fileConfig',
            signature=[
                ('std::wstring', 'filename'),
                ('boost::python::dict', 'defaults')]),
        
        Function(name='listen'),
        
        Function(
            name='listen',
            signature=[
                ('unsigned int', 'port')]),
        
        Function(name='stopListening'),
        ]

    def __init__(self):
        super(Config, self).__init__(
            preprocessor_guard='INCLUDE_ACKWARD_LOGGING_CONFIG_HPP',
            forward_declarations=[('boost', 'python', 'class dict')],
            header_includes=[('string',)],
            impl_includes=[
                ('boost', 'python', 'dict.hpp'),
                ('boost', 'python', 'import.hpp'),
                ('ackward', 'core', 'Exceptions.hpp'),
                ('ackward', 'logging', 'Module.hpp'),
                ],
            objects={ ('ackward', 'logging') : Config.functions })

def definition():
    return Config()
