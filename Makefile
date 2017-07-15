##
## @file        Makefile
## @brief       Makefile for C/C++
## @author      Keitetsu
## @date        2017/03/20
## @copyright   Copyright (c) 2017 Keitetsu
## @par         License
##              This software is released under the MIT License.
##


CROSS_PREFIX =

CC           = $(CROSS_PREFIX)gcc
CXX          = $(CROSS_PREFIX)g++
LD           = $(CROSS_PREFIX)gcc
CFLAGS       = -Wall -Wextra -O3 -MMD -MP -D_GNU_SOURCE
CXXFLAGS     = -Wall -Wextra -O3 -MMD -MP
LDFLAGS      = -lm
LIBS         =
INCLUDE      = -I./include -I./LinkedList/include

DOXYGENDIR   = ./html ./latex
NOMAKEDIR    = $(DOXYGENDIR) .git%
OBJDIR       = ./obj
ifeq "$(strip $(OBJDIR))" ""
	OBJDIR   = .
endif
BINDIR       = ./bin
ifeq "$(strip $(BINDIR))" ""
	BINDIR = .
endif

CALLSRCS     = $(shell find * -name *.c)
CXXALLSRCS   = $(shell find * -name *.cpp)
CSRCS        = $(filter-out $(NOMAKEDIR), $(CALLSRCS))
CXXSRCS      = $(filter-out $(NOMAKEDIR), $(CALLXXSRCS))
SRCS         = $(CSRCS) $(CXXSRCS)
SRCDIRS      = $(dir $(SRCS))$
COBJS        = $(addprefix $(OBJDIR)/, $(patsubst %.c, %.o, $(CSRCS)))
CXXOBJS      = $(addprefix $(OBJDIR)/, $(patsubst %.cpp, %.o, $(CXXSRCS)))
OBJS         = $(COBJS) $(CXXOBJS)
OBJDIRS      = $(addprefix $(OBJDIR)/, $(SRCDIRS))
DEPS         = $(OBJS:.o=.d)
TARGET       = $(BINDIR)/$(shell basename `readlink -f .`)

$(TARGET): $(OBJS) $(LIBS)
	-mkdir -p $(BINDIR)
	$(LD) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.c
	-mkdir -p $(OBJDIR)
	-mkdir -p $(OBJDIRS)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(OBJDIR)/%.o: %.cpp
	-mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

.PHONY: clean all

clean:
	-rm -f $(OBJS) $(TARGET)
	-rm -rf $(OBJDIR)
	-rm -rf $(BINDIR)
	-rm -rf $(DOXYGENDIR)

all: clean $(TARGET)

-include $(DEPS)
