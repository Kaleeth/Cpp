#!/bin/bash
git clean -f -d -X
find . -name "Makefile" | xargs rm -f
rm -drf build
