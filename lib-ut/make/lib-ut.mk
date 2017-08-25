STEM := libut
TGT_TYPE := cppexe
libut_SOURCES :=\
	LibUT-Main.cpp \
	LibUT-ExpressionGenerator.cpp \
	LibUT-Operations.cpp \

libut_DEPENDSON := lib
libut_INCLUDES := external/catch lib/impl

include rules.mk

TEST_FILES += $(TARGET)

