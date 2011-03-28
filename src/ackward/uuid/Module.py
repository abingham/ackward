from ackward import (function,
                     Module,
                     ModuleProperty,
                     Namespace,
                     TranslationUnit)

def definition(env):
    with TranslationUnit(
        header_includes=[
            ('ackward', 'uuid', 'Types.hpp'),
            ('ackward', 'uuid', 'UUID.hpp'),
            ],
        impl_includes=[
            ('ackward', 'uuid', 'Module.hpp'),
            ]) as t:

        with Namespace('ackward', 'uuid'):
            # NOTE: This method fails mysteriously when not under the
            # debugger. Why?
            function('Node getnode()')

            # uuid.uuid1([node[, clock_seq]]) Generate a UUID from a
            # host ID, sequence number, and the current time. If node
            # is not given, getnode() is used to obtain the hardware
            # address. If clock_seq is given, it is used as the
            # sequence number; otherwise a random 14-bit sequence
            # number is chosen.
            function('UUID uuid1()')
    
            function('UUID uuid1(Node node)')
            function('UUID uuid1(Node node, unsigned int clock_seq)')
            
            # uuid.uuid3(namespace, name) Generate a UUID based on the
            # MD5 hash of a namespace identifier (which is a UUID) and
            # a name (which is a string).
            function('UUID uuid3(UUID name_space, std::string name)')
            
            # uuid.uuid4()
            # Generate a random UUID.
            function('UUID uuid4()')
            
            function('UUID uuid5(UUID name_space, std::string name)')
            
            # The uuid module defines the following namespace
            # identifiers for use with uuid3() or uuid5().
            
            # uuid.NAMESPACE_DNS
            # When this namespace is specified, the name string is a
            # fully-qualified domain name.

            with Module(name='uuid'):
                for ns in ['DNS', 'URL', 'OID', 'X500']:
                    ModuleProperty(
                        name='NAMESPACE_%s' % ns,
                        type='UUID')

    return t
