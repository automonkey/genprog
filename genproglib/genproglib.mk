STEM := genproglib
TGT_TYPE := lib
genproglib_SOURCES := genproglib.cc

genproglib_CPPFLAGS := -DPROJ=genproglib

include rules.mk
