# To see a list of available make targets from bash, type:
# make <space> <tab> <tab>


include makefile-generic.mk


# Set default compiler toolchain (can still override from command line)
config := clang


SDLCONFIG := sdl2-config

CPPFLAGS := -I nas2d-core/include/
CXXFLAGS := -std=c++17 -O2 -g -Wall -Wextra -Wpedantic -Wno-unknown-pragmas
LDFLAGS := -static-libgcc -static-libstdc++ -L nas2d-core/lib/ $($(SDLCONFIG) --static-libs)
LDLIBS := -lnas2d -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lphysfs -lGLEW -lGL

# By default, compile and link both static library and dynamic link library
all: test1 test2 test3

test1: | nas2d
test2: | nas2d
test3: | nas2d

.PHONY: nas2d
nas2d:
	+make -C nas2d-core/

$(eval $(call DefineCppProject,test1,test1.exe,test_1/))
$(eval $(call DefineCppProject,test2,test2.exe,test_2/))
$(eval $(call DefineCppProject,test3,test3.exe,test_3/))
