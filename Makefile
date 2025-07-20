OUTPUT := wii-messenger
SOURCES := source/main.cpp
LIBS := -lgrrlib -lfreetype -lharfbuzz -lpngu -lz

# Toolchain includes and libs
INCLUDES := -I/opt/devkitpro/portlibs/wii/include -I/opt/devkitpro/portlibs/wii/include/freetype
LDFLAGS := -L/opt/devkitpro/portlibs/wii/lib

CFLAGS := -g -O2 $(INCLUDES)
CXXFLAGS := $(CFLAGS)

# DevKitPro Rules
include $(DEVKITPPC)/wii_rules