# c-lib-error

## Overview

`c-lib-error` is a C library that defines a struct for errors, and a macro that sets the error code and error message (such that it includes the file name, line number and function name of the code that set the error).

## Installation

To install `liberror.a` and its header files to `/usr/local`, run the commands below.

```sh
git clone https://github.com/river-martin/c-lib-error.git
cd c-lib-error
sudo INSTALL_PREFIX=/usr/local make install # sudo is required to write file to /usr/local
```

To install to a different directory, set `INSTALL_PREFIX` to something else. If your user has write permission for `$INSTALL_PREFIX`, you don't need to use `sudo`.

## Usage

See `tests/test_error.c`.
