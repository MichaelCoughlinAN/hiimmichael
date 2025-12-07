#!/bin/sh
gzip -v "$1"
mv -v "$1".gz "$1"
