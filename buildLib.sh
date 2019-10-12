#!/bin/bash

make clean
make DEBUG=0
cp .theos/obj/libSubstitrate.dylib libSubstitrate_arm.dylib
make clean
make DEBUG=0 SIMULATOR=1
cp .theos/obj/iphone_simulator/libSubstitrate.dylib libSubstitrate_pc.dylib
lipo -create libSubstitrate_arm.dylib libSubstitrate_pc.dylib -output libSubstitrate.dylib
mv libSubstitrate.dylib ${THEOS}/vendor/lib/
rm -f libSubstitrate_arm.dylib libSubstitrate_pc.dylib