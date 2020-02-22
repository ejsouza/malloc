#!/bin/sh
export DYLD_LIBRARY_PATH="/Users/esouza/42/malloc/"
export DYLD_INSERT_LIBRARIES="libft_malloc.so"
export DYLD_FORCE_FLAT_NAMESPACE=1
$@
