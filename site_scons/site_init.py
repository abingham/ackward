import ackward as akw

def TOOL_ACKWARD(env):
    def akw_header(target, source, env): 
        return akw.translate_header_file(str(source[0]), str(target[0]))
    akw_header = Builder(action = akw_header,
                         suffix = '.hpp',
                         src_suffix = '.py')
    
    def akw_impl(target, source, env):
        return akw.translate_impl_file(str(source[0]), str(target[0]))
    akw_impl = Builder(action = akw_impl,
                       suffix = '.cpp',
                       src_suffix = '.py')

    env.Append(
        BUILDERS = {
            'AkwHeader' : akw_header,
            'AkwImpl' : akw_impl
            })
