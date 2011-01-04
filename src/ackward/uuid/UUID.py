from ackward.translation_unit import ClassTranslationUnit
from ackward.cls import Class, InlineMethod, Property

from_hex1='''
static UUID fromHex(const std::string& hex) {
    try {
        boost::python::object obj = UUID::cls()(hex);
        return UUID(obj);
    } TRANSLATE_PYTHON_EXCEPTION();
}
'''

from_hex2='''
static UUID fromHex(
  const std::string& hex,
  uint8_t version) {
    using namespace boost::python;

    try {
        boost::python::object obj = UUID::cls()(hex,
                                 object(),
                                 object(),
                                 object(),
                                 object(),
                                 version);
        return UUID(obj);
    } TRANSLATE_PYTHON_EXCEPTION();
}
'''

from_bytes1='''
static UUID fromBytes(const ackward::core::Bytes& bytes)
{
    try {
        boost::python::object obj = UUID::cls()(
            boost::python::object(), 
            bytes);
        return UUID(obj);
    } TRANSLATE_PYTHON_EXCEPTION();
}
'''

from_bytes2='''
static UUID fromBytes(
  const ackward::core::Bytes& bytes,
  uint8_t version)
{
    using namespace boost::python;

    try {
        boost::python::object obj = UUID::cls()(object(), 
                                 bytes,
                                 object(),
                                 object(),
                                 object(),
                                 version);
        return UUID(obj);
    } TRANSLATE_PYTHON_EXCEPTION();
}
'''

from_bytes_le1='''
static UUID fromBytes_LE(const ackward::core::Bytes& bytes_le)
{
    using namespace boost::python;

    try {
        object obj = UUID::cls()(
            object(), 
            object(),
            bytes_le);
        return UUID(obj);
    } TRANSLATE_PYTHON_EXCEPTION();
}
'''

from_bytes_le2='''
static UUID fromBytes_LE(
  const ackward::core::Bytes& bytes_le,
  uint8_t version)
{
    using namespace boost::python;

    try {
        boost::python::object obj = UUID::cls()(object(), 
                                 object(),
                                 bytes_le,
                                 object(),
                                 object(),
                                 version);
        return UUID(obj);
    } TRANSLATE_PYTHON_EXCEPTION();
}
'''

from_fields1='''
static UUID fromFields(const Fields& f)
{
    using namespace boost::python;

    try {
        object obj = UUID::cls()(object(), 
                                 object(),
                                 object(),
                                 core::convertTuple(f));
        return UUID(obj);
    } TRANSLATE_PYTHON_EXCEPTION();
}
'''

from_fields2='''
static UUID fromFields(
  const Fields& f,
  uint8_t version)
{
    using namespace boost::python;

    try {
        boost::python::object obj = UUID::cls()(object(), 
                                 object(),
                                 object(),
                                 core::convertTuple(f),
                                 object(),
                                 version);
        return UUID(obj);
    } TRANSLATE_PYTHON_EXCEPTION();
}
'''

version='''
uint8_t version() const
{
    using namespace boost::python;

    object v = _version();
    if (core::is_none(v))
        return 0;
    else
        return extract<uint8_t>(v);
}
'''

class UUID(ClassTranslationUnit):
    def __init__(self):
        c = Class(name='UUID',
                  wrapped_class='uuid.UUID')

        Property(
            cls=c,
            name='bytes',
            type='ackward::core::ByteArray',
            read_only=True)

        Property(
            cls=c,
            name='bytes_le',
            type='ackward::core::ByteArray',
            read_only=True)

        Property(
            cls=c,
            name='hex',
            type='std::string',
            read_only=True)

        Property(
            cls=c,
            name='fields',
            type='Fields',
            read_only=True)

        # We need to figure the proper type for a 128-bit value.
        # Don't forget a factory/constructor when we do.
        # Property(
        #     cls=c,
        #     python_name='int',
        #     name='integer',
        #     type='Integer',
        #     read_only=True)

        Property(
            cls=c,
            name='urn',
            type='std::string',
            read_only=True)

        Property(
            cls=c,
            name='variant',
            type='Variant',
            read_only=True)

        Property(
            cls=c,
            name='_version',
            python_name='version',
            type='boost::python::object',
            read_only=True)

        for code in [from_hex1, from_hex2, from_bytes1, from_bytes2, from_bytes_le1, from_bytes_le2, from_fields1, from_fields2, version]:
            InlineMethod(
                cls=c,
                code=code)

        super(UUID, self).__init__(
            forward_declarations=[
                ],
            header_includes=[
                ('ackward', 'core', 'ByteArray.hpp'),
                ('ackward', 'core', 'Bytes.hpp'),
                ('ackward', 'core', 'ExceptionTranslator.hpp'),
                ('ackward', 'core', 'Tuple.hpp'),
                ('ackward', 'core', 'Util.hpp'),
                ('ackward', 'uuid', 'Types.hpp'),
                ('ackward', 'uuid', 'Variant.hpp'),
                ],
            impl_includes=[
                ('ackward', 'uuid', 'UUID.hpp')
                ],
            objects={('ackward', 'uuid') : [c]})

def definition():
    return UUID()
