COMPILER = gcc
LANGUAGE = -x c
DEBUG_MODE = -g 
BINARY = -o ./BINARIES/EXECUTIVE
CODEFILES = ./CODEFILES/main.c ./CODEFILES/ANIM/anim.c ./CODEFILES/ANIM/UNITS/unit.c ./CODEFILES/RENDER/render.c ./CODEFILES/ANIM/IMAGES/images.c ./CODEFILES/ANIM/TEXTURES/textures.c ./CODEFILES/ANIM/UNITS/QUAD_ROTATING/quad.c ./CODEFILES/ANIM/UNITS/OS/os.c
LIBS = -lm -l X11 -l GL -l GLU

all:
	@$(COMPILER) $(LANGUAGE) $(DEBUG_MODE) $(BINARY) $(CODEFILES) $(LIBS) 
