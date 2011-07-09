STEM := genproglibut
TGT_TYPE := cppexe
genproglibut_SOURCES := genproglibut.cc

genproglibut_DEPENDSON := genproglib
genproglibut_INCLUDES := testframework

include rules.mk

TEST_FILES += $(TARGET)
