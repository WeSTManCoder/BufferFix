HL2SDK = /home/src_sdk/hl2sdk-episode1
HL2PUB = $(HL2SDK)/public
HL2LIB = $(HL2SDK)/linux_sdk
LIB_EXT = so
LIB_SUFFIX = _i486.$(LIB_EXT)

PROJECT = bufferfix
BIN_DIR = Original
OBJECTS = subhook/subhook.c serverplugin.cpp

CPP = gcc
CFLAGS = -DSOURCE_ENGINE=1 -DSE_EPISODEONE=1
CFLAGS += -DPOSIX -Dstricmp=strcasecmp -D_stricmp=strcasecmp -D_strnicmp=strncasecmp -Dstrnicmp=strncasecmp \
	-D_snprintf=snprintf -D_vsnprintf=vsnprintf -D_alloca=alloca -Dstrcmpi=strcasecmp -DCOMPILER_GCC -Wall -Werror \
	-Wno-overloaded-virtual -Wno-switch -Wno-unused -msse -DHAVE_STDINT_H -m32 -Wno-invalid-offsetof -D_LINUX -Wno-pointer-arith
CPPFLAGS += -Wno-non-virtual-dtor -fno-exceptions -fno-rtti

C_DEBUG_FLAGS = -D_DEBUG -DDEBUG -g -ggdb3

LINK += -m32 -lm -ldl -lstdc++ -shared -static-libgcc
LINK +=   $(HL2LIB)/tier1_i486.a vstdlib$(LIB_SUFFIX) tier0$(LIB_SUFFIX)

INCLUDE = -I. -I.. -I$(HL2PUB) -I$(HL2PUB)/tier1 -I$(HL2PUB)/dlls


BINARY = $(PROJECT).$(LIB_EXT)

OBJ_BIN := $(OBJECTS:%.cpp=$(BIN_DIR)/%.o)

MAKEFILE_NAME := $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))

$(BIN_DIR)/%.o: %.cpp
	$(CPP) $(INCLUDE) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	
all:
	mkdir -p $(BIN_DIR)
	ln -sf $(HL2LIB)/vstdlib$(LIB_SUFFIX);
	ln -sf $(HL2LIB)/tier0$(LIB_SUFFIX);
	$(MAKE) -f $(MAKEFILE_NAME) extension

check :

extension: check $(OBJ_BIN)
	$(CPP) $(INCLUDE) $(OBJ_BIN) $(LINK) -o $(BIN_DIR)/$(BINARY)

debug:
	CFLAGS +=  C_DEBUG_FLAGS
	$(MAKE) -f $(MAKEFILE_NAME) all DEBUG=true

default: all

clean:
	rm -rf $(BIN_DIR)


