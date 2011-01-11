APPNAME = 'TinyShiftAnd.cpp'
VERSION = '0.0.2'

top = '.'
out = 'build'
targets = ('ShiftAnd', 'ExtShiftAnd')
tests   = {'ShiftAnd'   : ('ABABB',     'ABABABB'), 
           'ExtShiftAnd': ('AB?C*DE+F', 'ACCCDFABDEEEF')}

def options(opt):
    opt.tool_options('compiler_cxx')

def configure(conf):
    conf.check_tool('compiler_cxx')

def build(bld):
    for target in targets: 
        bld(features = ['cxx', 'cprogram'], 
            source   = target + '.cpp', 
            target   = target, 
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

def shutdown(ctx):
    pass
