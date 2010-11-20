def generate(usings):
    return '\n'.join(['using {0};'.format(u) for u in usings])
        
