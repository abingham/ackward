import platform

try:
    from configparser import ConfigParser
except ImportError:
    from ConfigParser import ConfigParser

APPNAME='ackward'
VERSION=0.1

top = '.'
out = 'build'

def options(ctx):
    ctx.load('compiler_c++')

def read_config():
    '''Read the user configuration file.
    '''

    class Config:
        def __init__(self, cp):
            self.cp = cp
            if not self.cp.has_section('config'):
                self.cp.add_section('config')

        def __getitem__(self, key):
            return cp.get('config', key)

    cp = ConfigParser(
        defaults={
            'BOOST_INCLUDE_DIR' : [],
            'BOOST_LIB_DIR' : [],
            'BOOST_LIBS' : [],
            'PYTHON_INCLUDE_DIR' : [],
            'PYTHON_LIB_DIR' : [],
            'PYTHON_LIBS' : [],
            })

    cp.read('custom.ini')

    return Config(cp)

def configure(ctx):
    cfg = read_config()

    ctx.load('compiler_c++')

    # support inter-library includes
    ctx.env.append_value('INCLUDES', '#/src')

    # python stuff
    ctx.env.append_unique('INCLUDES', cfg['PYTHON_INCLUDE_DIR'])
    ctx.env.append_unique('LIBPATH', cfg['PYTHON_LIB_DIR'])
    ctx.env.append_unique('LIBS', cfg['PYTHON_LIB'])

    # boost stuff
    ctx.env.append_unique('INCLUDES', cfg['BOOST_INCLUDE_DIR'])
    ctx.env.append_unique('LIBPATH', cfg['BOOST_LIB_DIR'])
    ctx.env.append_unique('LIBS', cfg['BOOST_LIBS'].split())

    # Keep gcc happy
    if platform.system() == 'Linux':
        ctx.env.append_value('CXXFLAGS', ['-std=c++0x'])
    
    # Configuration checks
    ctx.check(header_name='Python.h')
    ctx.check_cc(lib=cfg['PYTHON_LIB'], uselib_store='python')
    ctx.check(header_name='boost/python.hpp', features='cxx')
    ctx.check(header_name='boost/filesystem.hpp', features='cxx')
    ctx.check_cxx(lib='boost_system', uselib_store='boost_system')
    ctx.check_cxx(lib='boost_filesystem', use='boost_system')
    ctx.check_cxx(lib='boost_python3', use='python')

def build(ctx):
    ctx.recurse(
        'src/ackward')

