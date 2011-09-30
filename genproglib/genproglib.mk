STEM := genproglib
TGT_TYPE := lib
genproglib_SOURCES := expr.cc

genproglib_CPPFLAGS := -DPROJ=genproglib

include rules.mk
