import os.path

def include(incl):
    return '#include <{0}>'.format(os.path.join(*incl))

def generate(incls):
    return [include(incl) for incl in incls]
