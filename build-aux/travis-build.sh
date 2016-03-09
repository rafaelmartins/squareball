#!/bin/bash

set -ex

rm -rf build
mkdir -p build

pushd build > /dev/null

../configure \
    CFLAGS="-Wall -g" \
    --enable-tests \
    --enable-valgrind \
    --disable-silent-rules \
    ${CONFIGURE_ARGS}

popd > /dev/null

make -C build "${TARGET}"
