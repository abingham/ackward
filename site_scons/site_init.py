import ackward as akw

def TOOL_ACKWARD(env):
    def akw_header(target, source, env): 
        return akw.translate_header_file(str(source[0]), str(target[0]))
    akw_header = Builder(action = akw_header,
                         suffix = '_akw.hpp',
                         src_suffix = '.akw')
    
    def akw_impl(target, source, env):
        return akw.translate_impl_file(str(source[0]), str(target[0]))
    akw_impl = Builder(action = akw_impl,
                       suffix = '_akw.ipp',
                       src_suffix = '.akw')

    env.Append(
        BUILDERS = {
            'AkwHeader' : akw_header,
            'AkwImpl' : akw_impl
            })
