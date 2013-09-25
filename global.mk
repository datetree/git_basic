PATH_BIN           ?= .
PATH_SRC           ?= .
PATH_INC           ?= .
PATH_LIB           += # ./my_libs

FILE_BASE          ?= $(shell basename `pwd`)
FILE_EXE           ?= $(PATH_BIN)/$(FILE_BASE)
FILE_A             ?= $(PATH_BIN)/$(FILE_BASE).a
FILE_SO            ?= $(PATH_BIN)/$(FILE_BASE).so
FILE_AUTO          ?= # ./my_auto_config.h
FILE_SRC_C         ?= $(wildcard $(foreach i,$(PATH_SRC),$(i)/*.c))
FILE_SRC_CPP       ?= $(wildcard $(foreach i,$(PATH_SRC),$(i)/*.cpp))
FILE_OBJ           ?= $(patsubst %.c,%.o,$(FILE_SRC_C)) $(patsubst %.cpp,%.o,$(FILE_SRC_CPP))
FILE_DEP           ?= $(patsubst %.c,%.d,$(FILE_SRC_C)) $(patsubst %.cpp,%.d,$(FILE_SRC_CPP))
FILE_LIB           += # ./my_libs/libxyz.a -labc
FILE_LIB_DEP       += # ./my_libs/libxyz.a
FILE_CLEAN         += $(FILE_OBJ) $(FILE_DEP) $(FILE_EXE) $(FILE_A) $(FILE_SO)
FILE_DISTCLEAN     += $(FILE_CLEAN) $(FILE_AUTO)

TOOL_CROSS_COMPILE ?=
TOOL_CC            ?= $(TOOL_CROSS_COMPILE)gcc
TOOL_AR            ?= $(TOOL_CROSS_COMPILE)ar
TOOL_RANLIB        ?= $(TOOL_CROSS_COMPILE)ranlib
TOOL_STRIP         ?= $(TOOL_CROSS_COMPILE)strip

OPTION_FLAG        += -O2 -g3 -Wall -Werror
OPTION_MACRO       += # -DNDEBUG
OPTION_INC         += $(foreach i,$(PATH_INC),-I$(i))
OPTION_LIB         += $(foreach i,$(PATH_LIB),-L$(i))

%.o: %.c
	$(TOOL_CC) $(OPTION_FLAG) $(OPTION_MACRO) $(OPTION_INC) -c -o $@ $<
%.o: %.cpp
	$(TOOL_CC) $(OPTION_FLAG) $(OPTION_MACRO) $(OPTION_INC) -c -o $@ $<
%.d: %.c
	@set -e; $(TOOL_CC) $(OPTION_FLAG) $(OPTION_MACRO) $(OPTION_INC) -MM -MQ $*.o -MQ $*.d -MF $@ $<
%.d: %.cpp
	@set -e; $(TOOL_CC) $(OPTION_FLAG) $(OPTION_MACRO) $(OPTION_INC) -MM -MQ $*.o -MQ $*.d -MF $@ $<

.PHONY: all strip a strip_a so strip_so clean distclean

all: $(FILE_EXE)

strip: $(FILE_EXE)
	$(TOOL_STRIP) $(FILE_EXE)

a: $(FILE_A)

strip_a: $(FILE_A)
	$(TOOL_STRIP) $(FILE_A)

so: $(FILE_SO)

strip_so: $(FILE_SO)
	$(TOOL_STRIP) $(FILE_SO)

clean:
	rm -f $(FILE_CLEAN)

distclean:
	rm -f $(FILE_DISTCLEAN)

$(FILE_EXE): $(FILE_OBJ) $(FILE_LIB_DEP)
	$(TOOL_CC) ${OPTION_FLAG} $(OPTION_LIB) -o $(FILE_EXE) $(FILE_OBJ) $(FILE_LIB)

$(FILE_A): $(FILE_OBJ)
	$(TOOL_AR) cru $(FILE_A) $(FILE_OBJ)
	$(TOOL_RANLIB) $(FILE_A)

$(FILE_SO): $(FILE_OBJ)
	$(TOOL_CC) -shared -fPIC -o $(FILE_SO) $(FILE_OBJ)

-include $(FILE_DEP)
