#!/bin/bash

make DEBUG=0
cp -v ".theos/obj/libSubstitrate.dylib" ${THEOS}/vendor/lib/
