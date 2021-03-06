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

DOXYGENDIR   = spec_html
NOMAKEPATHS  = $(DOXYGENDIR)/% .git%
OBJDIR       = obj
ifeq "$(strip $(OBJDIR))" ""
	OBJDIR = .
endif
BINDIR       = bin
ifeq "$(strip $(BINDIR))" ""
	BINDIR = .
endif

CALLSRCS     = $(shell find * -name '*.c')
CXXALLSRCS   = $(shell find * -name '*.cpp')
CSRCS        = $(filter-out $(NOMAKEPATHS), $(CALLSRCS))
CXXSRCS      = $(filter-out $(NOMAKEPATHS), $(CXXALLSRCS))
SRCS         = $(CSRCS) $(CXXSRCS)
CSRCDIRS     = $(dir $(CSRCS))
CXXSRCDIRS   = $(dir $(CXXSRCS))
SRCDIRS      = $(CSRCDIRS) $(CXXSRCDIRS)
COBJS        = $(addprefix $(OBJDIR)/, $(patsubst %.c, %.o, $(CSRCS)))
CXXOBJS      = $(addprefix $(OBJDIR)/, $(patsubst %.cpp, %.o, $(CXXSRCS)))
OBJS         = $(COBJS) $(CXXOBJS)
COBJDIRS     = $(addprefix $(OBJDIR)/, $(CSRCDIRS))
CXXOBJDIRS   = $(addprefix $(OBJDIR)/, $(CXXSRCDIRS))
OBJDIRS      = $(COBJDIRS) $(CXXOBJDIRS)
DEPS         = $(OBJS:.o=.d)
TARGET       = $(BINDIR)/$(shell basename `readlink -f .`)

$(TARGET): $(OBJS) $(LIBS)
	-mkdir -p $(BINDIR)
	$(LD) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.c
	-mkdir -p $(OBJDIR)
	-mkdir -p $(COBJDIRS)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(OBJDIR)/%.o: %.cpp
	-mkdir -p $(OBJDIR)
	-mkdir -p $(CXXOBJDIRS)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

.PHONY: clean all

clean:
	-rm -f $(OBJS) $(TARGET)
	-rm -rf $(OBJDIR)
	-rm -rf $(BINDIR)
	-rm -rf $(DOXYGENDIR)

all: clean $(TARGET)

-include $(DEPS)

