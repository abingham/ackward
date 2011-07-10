from ackward import (Class,
                     InlineFunction,
                     Namespace,
                     Property,
                     TranslationUnit)

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

    object v = _version;
    if (core::is_none(v))
        return 0;
    else
        return extract<uint8_t>(v);
}
'''

uuid_doc = '''
Immutable UUID objects as specified in RFC 4122.

\\rst
See `<http://docs.python.org/library/uuid.html#uuid.UUID>`_.
\\endrst
'''

fields_doc = '''
A tuple of the six integer fields of the UUID, which are also
available as six individual attributes and two derived attributes:

\\rst
==================== =============================
Field                Meaning
==================== =============================
time_low             the first 32 bits of the UUID
time_mid             the next 16 bits of the UUID
time_hi_version      the next 16 bits of the UUID
clock_seq_hi_variant the next 8 bits of the UUID
clock_seq_low        the next 8 bits of the UUID
node                 the last 48 bits of the UUID
time                 the 60-bit timestamp
clock_seq            the 14-bit sequence number'
==================== =============================
\\endrst
'''

def definition(env):
    global doc

    with TranslationUnit(
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
            ]) as t:

        with Namespace('ackward', 'uuid'):

            with Class(name='UUID',
                       wrapped_class='uuid.UUID',
                       doc=uuid_doc):
                Property(
                    name='bytes',
                    type='ackward::core::ByteArray',
                    read_only=True,
                    doc = 'The UUID as a 16-byte string (containing the six integer fields in big-endian byte order).')

                Property(
                    name='bytes_le',
                    type='ackward::core::ByteArray',
                    read_only=True,
                    doc = 'The UUID as a 16-byte string (with time_low, time_mid, and time_hi_version in little-endian byte order).')

                Property(
                    name='hex',
                    type='std::string',
                    read_only=True,
                    doc = 'The UUID as a 32-character hexadecimal string.')

                Property(
                    name='fields',
                    type='Fields',
                    read_only=True,
                    doc = fields_doc)

                # We need to figure the proper type for a 128-bit value.
                # Don't forget a factory/constructor when we do.
                # Property(
                #     cls=c,
                #     python_name='int',
                #     name='integer',
                #     type='Integer',
                #     read_only=True)

                Property(
                    name='urn',
                    type='std::string',
                    read_only=True,
                    doc = 'The UUID as a URN as specified in RFC 4122.')

                Property(
                    name='variant',
                    type='Variant',
                    read_only=True,
                    doc = 'The UUID variant, which determines the internal layout of the UUID. This will be one of the integer constants RESERVED_NCS, RFC_4122, RESERVED_MICROSOFT, or RESERVED_FUTURE.')

                Property(
                    name='_version',
                    python_name='version',
                    type='boost::python::object',
                    read_only=True)

                for code,doc in [
                    (from_hex1, 'Create a UUID from a string of 32 hexadecimal digits'),
                    (from_hex2, 'Create a UUID from a string of 32 hexadecimal digits and a version'),
                    (from_bytes1, 'Create a UUID from a string of 16 bytes.'),
                    (from_bytes2, 'Create a UUID from a string of 16 bytes and a version.'),
                    (from_bytes_le1, 'Create a UUID from a string of 16 bytes in little-endian order.'),
                    (from_bytes_le2, 'Create a UUID from a string of 16 bytes in little-endian order and a version.'),
                    (from_fields1, 'a tuple of six integers (32-bit time_low, 16-bit time_mid, 16-bit time_hi_version, 8-bit clock_seq_hi_variant, 8-bit clock_seq_low, 48-bit node)'),
                    (from_fields2, 'a tuple of six integers (32-bit time_low, 16-bit time_mid, 16-bit time_hi_version, 8-bit clock_seq_hi_variant, 8-bit clock_seq_low, 48-bit node) and a version.'),
                    (version, 'The UUID version number (1 through 5, meaningful only when the variant is RFC_4122).'),
                    ]:
                    InlineFunction(
                        code=code,
                        doc=doc)
    return t
