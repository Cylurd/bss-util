TARGET := test.exe
SRCDIR := test
BUILDDIR := bin
OBJDIR := bin/obj
C_SRCS := 
CXX_SRCS := main.cpp
INCLUDE_DIRS := include
LIBRARY_DIRS := 
LIBRARIES := bss_util

CPPFLAGS += -w -std=gnu++0x
LDFLAGS += -L./bin/

include base.mk