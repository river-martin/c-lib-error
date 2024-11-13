# c-lib-error

## Overview

`c-lib-error` is a C library that defines a struct for errors, and a macro that sets the error code and error message (such that it includes the file name, line number and function name of the code that set the error).

## Installation

To install `c-lib-error` to `/usr/local/`, clone the repository and run `sudo make install`.

```sh
git clone https://github.com/river-martin/c-lib-error.git
cd c-lib-error
sudo make install
```

## Usage

See `tests/test_error.c`.
