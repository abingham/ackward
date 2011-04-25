from ackward import (function,
                     Module,
                     ModuleProperty,
                     Namespace,
                     TranslationUnit)

def doc(d):
    return '''
/**
\\rst
{0}
\endrst
*/'''.format(d)

get_node_doc = doc('''
Get the hardware address as a 48-bit positive integer. 

The first time this runs, it may launch a separate program, which
could be quite slow.''')

uuid1_doc = doc('Generate a UUID from a host ID, sequence number, and the current time.')

uuid3_doc = doc('Generate a UUID based on the MD5 hash of a namespace identifier (which is a UUID) and a name (which is a string).')

uuid4_doc = doc('Generate a random UUID.')

uuid5_doc = doc('Generate a UUID based on the SHA-1 hash of a namespace identifier (which is a UUID) and a name (which is a string).')

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
            function('Node getnode()').doc = get_node_doc

            # uuid.uuid1([node[, clock_seq]]) Generate a UUID from a
            # host ID, sequence number, and the current time. If node
            # is not given, getnode() is used to obtain the hardware
            # address. If clock_seq is given, it is used as the
            # sequence number; otherwise a random 14-bit sequence
            # number is chosen.
            function('UUID uuid1()').doc = uuid1_doc
    
            function('UUID uuid1(Node node)').doc = uuid1_doc
            function('UUID uuid1(Node node, unsigned int clock_seq)').doc = uuid1_doc
            
            # uuid.uuid3(namespace, name) Generate a UUID based on the
            # MD5 hash of a namespace identifier (which is a UUID) and
            # a name (which is a string).
            function('UUID uuid3(UUID name_space, std::string name)').doc = uuid3_doc
            
            # uuid.uuid4()
            # Generate a random UUID.
            function('UUID uuid4()').doc = uuid4_doc
            
            function('UUID uuid5(UUID name_space, std::string name)').doc = uuid5_doc
            
            # The uuid module defines the following namespace
            # identifiers for use with uuid3() or uuid5().
            
            # uuid.NAMESPACE_DNS
            # When this namespace is specified, the name string is a
            # fully-qualified domain name.

            with Module(name='uuid'):
                ModuleProperty(name='NAMESPACE_DNS', type='UUID').doc = doc(
                    'When this namespace is specified, the name string is a fully-qualified domain name.')
                ModuleProperty(name='NAMESPACE_URL', type='UUID').doc = doc(
                    'When this namespace is specified, the name string is a URL.')
                ModuleProperty(name='NAMESPACE_OID', type='UUID').doc = doc(
                    'When this namespace is specified, the name string is an ISO OID.')
                ModuleProperty(name='NAMESPACE_X500', type='UUID').doc = doc(
                    'When this namespace is specified, the name string is an X.500 DN in DER or a text output format.')

    return t
