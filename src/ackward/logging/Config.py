from ackward import *

class Config(TranslationUnit):
    def module(self):
        return 'logging'

    def preprocessor_guard(self):
        return 'INCLUDE_ACKWARD_LOGGING_CONFIG_HPP'

    def header_includes(self):
        return [
            ('string',)
            ]

    def impl_includes(self):
        return [
            ('boost', 'python', 'dict.hpp'),
            ('boost', 'python', 'import.hpp'),
            ('ackward', 'core', 'Exceptions.hpp')
            ]

    def forward_declarations(self):
        return [
            ('boost', 'python', 'class dict')
            ]

    def objects(self):
        return {
            ('ackward', 'logging') : [
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
            }

def definition():
    return Config()
