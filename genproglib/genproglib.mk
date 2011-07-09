STEM := genproglib
TGT_TYPE := lib
genproglib_SOURCES := literalexpr.cc

genproglib_CPPFLAGS := -DPROJ=genproglib

include rules.mk
