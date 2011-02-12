#! /usr/bin/env python
# encoding: utf-8

APPNAME = 'TinyShiftAnd.cpp'
VERSION = '0.0.2'

top = '.'
out = 'build'
cxxflags = '-O9 -Wall -W -Wformat=2 -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion -Wfloat-equal -Wpointer-arith'

def options(opt):
    opt.tool_options('compiler_cxx')

def configure(conf):
    conf.check_tool('compiler_cxx')

def build(bld):
    bld(features='cxx cprogram',
        source='src/shiftand_main.cpp src/shiftand.cpp',
        includes='. src', 
        target='shiftand')

    bld(features='cxx cprogram',
        source='src/xshiftand_main.cpp src/xshiftand.cpp',
        includes='. src', 
        target='xshiftand')
