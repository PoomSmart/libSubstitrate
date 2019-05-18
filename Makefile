TARGET = iphone:clang:latest:5.0
ARCHS = armv7 armv7s arm64 arm64e
PACKAGE_VERSION = 0.0.1-4

include $(THEOS)/makefiles/common.mk

LIBRARY_NAME = libSubstitrate
libSubstitrate_FILES = libSubstitrate.mm
libSubstitrate_LIBRARIES = substrate

include $(THEOS_MAKE_PATH)/library.mk
