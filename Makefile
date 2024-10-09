# =============================================================================

.PHONY: all clean rebuild
.SUFFIXES: .c .exe .out

# =============================================================================

_COLOR_BEGIN = \033[1;38;5;101m
_COLOR_END = \033[m

# =============================================================================

PROJECT_NAME = gl-lab
PROJECT_FULL_NAME = team-iwd/gl-lab

LOG_PREFIX = ${_COLOR_BEGIN}${PROJECT_FULL_NAME}:${_COLOR_END}

# =============================================================================

INCLUDE_PATH = include
SOURCE_PATH = src

TARGET_SUFFIX ?= out

TARGETS = \
	${SOURCE_PATH}/00-setup.${TARGET_SUFFIX}

# =============================================================================

CC = cc
CFLAGS = -D_DEFAULT_SOURCE -g -I${INCLUDE_PATH} -O2 -std=gnu99
LDLIBS = -ldl -lGL -lglfw -lm -lpthread -lrt -lX11

# =============================================================================

all: pre-build build post-build

pre-build:
	@printf "${LOG_PREFIX} Using: '${CC}' to build all examples.\n"

build: ${TARGETS}

.c.exe .c.out:
	@printf "${LOG_PREFIX} Compiling: $@ (from $<)\n"
	@${CC} $< ${SOURCE_PATH}/external/glad.c -o $@ ${CFLAGS} ${LDFLAGS} ${LDLIBS}

post-build:
	@printf "${LOG_PREFIX} Build complete.\n"

# =============================================================================

rebuild: clean all

# =============================================================================

clean:
	@printf "${LOG_PREFIX} Cleaning up.\n"
	@rm -f ${SOURCE_PATH}/*.exe  ${SOURCE_PATH}/*.out

# =============================================================================
