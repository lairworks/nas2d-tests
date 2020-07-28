# To see a list of available make targets from bash, type:
# make <space> <tab> <tab>


include makefile-generic.mk


# Set compiler toolchain (default, gcc, clang, mingw)
config := default


SDLCONFIG := sdl2-config

CPPFLAGS := -I nas2d-core/
CXXFLAGS := -std=c++17 -O2 -g -Wall -Wextra -Wpedantic -Wno-unknown-pragmas
LDFLAGS := -static-libgcc -static-libstdc++ -L nas2d-core/lib/ $($(SDLCONFIG) --static-libs)
LDLIBS := -lnas2d -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lphysfs -lGLEW -lGL

NAS2DLIB := nas2d-core/lib/libnas2d.a

all: zombieGame rendererFunctions blendingModes

zombieGame.exe: $(NAS2DLIB)
rendererFunctions.exe: $(NAS2DLIB)
blendingModes.exe: $(NAS2DLIB)

$(NAS2DLIB): | nas2d

.PHONY: nas2d
nas2d:
	+make -C nas2d-core/

.PHONY: clean-nas2d
clean-nas2d:
	+make -C nas2d-core/ clean
.PHONY: clean-all-nas2d
clean-all-nas2d:
	+make -C nas2d-core/ clean-all

$(eval $(call DefineCppProject,zombieGame,zombieGame.exe,SampleProjects/ZombieGame/))
$(eval $(call DefineCppProject,rendererFunctions,rendererFunctions.exe,SampleProjects/RendererFunctions/))
$(eval $(call DefineCppProject,blendingModes,blendingModes.exe,SampleProjects/BlendingModes/))
