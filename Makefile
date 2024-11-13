CC := clang

# Note: run `export LD_PRELOAD=$(clang -print-file-name=libclang_rt.asan-x86_64.so)` if you want to use Address Sanitizer

ifeq ($(ASAN), 1)
# Note: run `source set_asan_env_vars.sh` if you want to use Address Sanitizer
ASAN_DEBUG     := -fsanitize=address -shared-libasan -ferror-limit=1
endif

# compiler flags
DEBUG     := -ggdb -gdwarf-4 -ferror-limit=1
OPTIMISE  := -O0
WARNING   := -Wall -Wextra -Wno-variadic-macros \
             -Wno-overlength-strings -pedantic
EXTRA     := -std=c11 -fPIC
CFLAGS    := $(DEBUG) $(ASAN_DEBUG) $(OPTIMISE) $(WARNING) $(EXTRA)
DFLAGS    ?= # -DDEBUG

# linker flags

LDFLAGS := $(ASAN_DEBUG) -lerror

# commands

COMPILE:=$(CC) $(CFLAGS) $(DFLAGS)

# files

CODE_FILES := $(wildcard src/*.c src/*.h tests/*.c tests/*.h)
SRC_OBJ_FILES := $(patsubst src/%.c, build/src/%.o, $(wildcard src/*.c))
# targets

liberror.a: $(SRC_OBJ_FILES)
	ar rcs liberror.a $(SRC_OBJ_FILES)
	ar t liberror.a

build/src/%.o: src/%.c $(CODE_FILES) | build
	$(COMPILE) -c -o $@ $<

build/tests/%.o: tests/%.c $(CODE_FILES) | build
	$(COMPILE) -c -o $@ $<

test_error: liberror.a | build
	$(COMPILE) -o $@ tests/test_error.c $(LDFLAGS)

tests: test_error
	./test_error

# target directories

build:
	mkdir -p build/src
	mkdir -p build/tests

# phony targets

install: liberror.a src/error.h
	install -d /usr/local/lib /usr/local/include
	# Octal permissions: 6 = rw-, 4 = r--
	install -m 644 liberror.a /usr/local/lib
	install -m 644 src/error.h /usr/local/include

uninstall:
	rm -f /usr/local/lib/liberror.a /usr/local/include/error.h

clean:
	rm -f test_error
	rm -f liberror.a
	rm -rf build

.PHONY: install uninstall clean tests