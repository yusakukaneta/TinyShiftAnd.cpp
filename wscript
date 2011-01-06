APPNAME = 'TinyShiftAnd.cpp'
VERSION = '0.0.2'

top = '.'
out = 'build'

def options(opt):
    opt.tool_options('compiler_cxx')

def configure(conf):
    conf.check_tool('compiler_cxx')

def build(bld):
    for name in ('ShiftAnd', 'ExtShiftAnd'):
        bld(features = ['cxx', 'cprogram'], 
            source   = name + '.cpp', 
            target   = name, 
            includes = '.', 
            cxxflags = ['-Wall', 
                        '-W', 
                        '-Wformat=2', 
                        '-Wcast-qual', 
                        '-Wcast-align', 
                        '-Wwrite-strings', 
                        '-Wconversion', 
                        '-Wfloat-equal', 
                        '-Wpointer-arith'])
