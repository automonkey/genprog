STEM := libut
TGT_TYPE := cppexe
libut_SOURCES :=\
	LibUT-Main.cpp \
	LibUT-Operations.cpp \

libut_DEPENDSON := lib
libut_INCLUDES := external/catch

include rules.mk

TEST_FILES += $(TARGET)

