from ackward.translation_unit import TranslationUnit
from ackward.elements import Function, Module, ModuleProperty

class UUIDModule(TranslationUnit):
    def __init__(self):
        objs=[
            Module(name='uuid'),

            # NOTE: This method fails mysteriously when not under the
            # debugger. Why?
            Function(
                name='getnode',
                return_type='Node'),

            # uuid.uuid1([node[, clock_seq]])
            # Generate a UUID from a host ID, sequence number, and the current
            # time. If node is not given, getnode() is used to obtain the
            # hardware address. If clock_seq is given, it is used as the
            # sequence number; otherwise a random 14-bit sequence number is
            # chosen.
            Function(
                name='uuid1',
                return_type='UUID'),
            
            Function(
                name='uuid1',
                signature=[('Node', 'node')],
                return_type='UUID'),
            
            Function(
                name='uuid1',
                signature=[('Node', 'node'),
                           ('unsigned int', 'clock_seq')],
                return_type='UUID'),
            
            # uuid.uuid3(namespace, name)
            # Generate a UUID based on the MD5 hash of a namespace identifier
            # (which is a UUID) and a name (which is a string).
            Function(
                name='uuid3',
                signature=[('UUID', 'name_space'),
                           ('std::string', 'name')],
                return_type='UUID'),
            
            # uuid.uuid4()
            # Generate a random UUID.
            Function(
                name='uuid4',
                return_type='UUID'),
            
            Function(
                name='uuid5',
                signature=[('UUID', 'name_space'),
                           ('std::string', 'name')],
                return_type='UUID')
            ]
            
        # The uuid module defines the following namespace identifiers for
        # use with uuid3() or uuid5().
            
        # uuid.NAMESPACE_DNS
        # When this namespace is specified, the name string is a
        # fully-qualified domain name.
        for ns in ['DNS', 'URL', 'OID', 'X500']:
            objs.append(
                ModuleProperty(
                    name='NAMESPACE_%s' % ns,
                    type='UUID'))

        super(UUIDModule, self).__init__(
            forward_declarations=[
                ],
            header_includes=[
                ('ackward', 'uuid', 'Types.hpp'),
                ('ackward', 'uuid', 'UUID.hpp'),
                ],
            impl_includes=[
                ('ackward', 'uuid', 'Module.hpp'),
                ],
        objects={('ackward', 'uuid') : objs})
            
def definition():
    return UUIDModule()
