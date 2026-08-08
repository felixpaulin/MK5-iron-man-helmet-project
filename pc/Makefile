# Tool macros

CC ?= gcc
CXX ?= g++

# Settings

NAME = TinyMLModelTest
BUILD_PATH = ./build

# Main application source

CXXSOURCES = TinyMLModelTest.cpp

# Header search paths

CFLAGS += -I../lib/iron-man-mk5-helmet-tinyml-impulse
# C compiler flags

CFLAGS += -Wall
CFLAGS += -g
CFLAGS += -Wno-strict-aliasing
CFLAGS += -Os
CFLAGS += -DNDEBUG

# C++ compiler flags

CXXFLAGS += -std=c++11

# Linker flags

LDFLAGS += -lm
LDFLAGS += -lstdc++

# ============================================================
# CMSIS-DSP
# ============================================================

CSOURCES += $(wildcard ../lib/iron-man-mk5-helmet-tinyml-impulse/edge-impulse-sdk/CMSIS/DSP/Source/TransformFunctions/*.c) $(wildcard ../lib/iron-man-mk5-helmet-tinyml-impulse/edge-impulse-sdk/CMSIS/DSP/Source/CommonTables/*.c) $(wildcard ../lib/iron-man-mk5-helmet-tinyml-impulse/edge-impulse-sdk/CMSIS/DSP/Source/BasicMathFunctions/*.c) $(wildcard ../lib/iron-man-mk5-helmet-tinyml-impulse/edge-impulse-sdk/CMSIS/DSP/Source/ComplexMathFunctions/*.c) $(wildcard ../lib/iron-man-mk5-helmet-tinyml-impulse/edge-impulse-sdk/CMSIS/DSP/Source/FastMathFunctions/*.c) $(wildcard ../lib/iron-man-mk5-helmet-tinyml-impulse/edge-impulse-sdk/CMSIS/DSP/Source/SupportFunctions/*.c) $(wildcard ../lib/iron-man-mk5-helmet-tinyml-impulse/edge-impulse-sdk/CMSIS/DSP/Source/MatrixFunctions/*.c) $(wildcard ../lib/iron-man-mk5-helmet-tinyml-impulse/edge-impulse-sdk/CMSIS/DSP/Source/StatisticsFunctions/*.c)

# ============================================================
# Edge Impulse DSP + model
# ============================================================

CXXSOURCES += $(wildcard ../lib/iron-man-mk5-helmet-tinyml-impulse/tflite-model/*.cpp) $(wildcard ../lib/iron-man-mk5-helmet-tinyml-impulse/edge-impulse-sdk/dsp/kissfft/*.cpp) $(wildcard ../lib/iron-man-mk5-helmet-tinyml-impulse/edge-impulse-sdk/dsp/dct/*.cpp) $(wildcard ../lib/iron-man-mk5-helmet-tinyml-impulse/edge-impulse-sdk/dsp/memory.cpp) $(wildcard ../lib/iron-man-mk5-helmet-tinyml-impulse/edge-impulse-sdk/porting/posix/*.c*) $(wildcard ../lib/iron-man-mk5-helmet-tinyml-impulse/edge-impulse-sdk/porting/mingw32/*.c*)

CCSOURCES +=

# ============================================================
# TensorFlow Lite Micro
# ============================================================

CFLAGS += -DTF_LITE_DISABLE_X86_NEON=1

CSOURCES += ../lib/iron-man-mk5-helmet-tinyml-impulse/edge-impulse-sdk/tensorflow/lite/c/common.c

CCSOURCES += $(wildcard ../lib/iron-man-mk5-helmet-tinyml-impulse/edge-impulse-sdk/tensorflow/lite/kernels/*.cc) $(wildcard ../lib/iron-man-mk5-helmet-tinyml-impulse/edge-impulse-sdk/tensorflow/lite/kernels/internal/*.cc) $(wildcard ../lib/iron-man-mk5-helmet-tinyml-impulse/edge-impulse-sdk/tensorflow/lite/micro/kernels/*.cc) $(wildcard ../lib/iron-man-mk5-helmet-tinyml-impulse/edge-impulse-sdk/tensorflow/lite/micro/*.cc) $(wildcard ../lib/iron-man-mk5-helmet-tinyml-impulse/edge-impulse-sdk/tensorflow/lite/micro/memory_planner/*.cc) $(wildcard ../lib/iron-man-mk5-helmet-tinyml-impulse/edge-impulse-sdk/tensorflow/lite/core/api/*.cc)

# ============================================================
# Object files
# ============================================================

COBJECTS := $(patsubst %.c,%.o,$(CSOURCES))
CXXOBJECTS := $(patsubst %.cpp,%.o,$(CXXSOURCES))
CCOBJECTS := $(patsubst %.cc,%.o,$(CCSOURCES))

# ============================================================
# Default target
# ============================================================

.PHONY: all
all: app

# ============================================================
# Compile C sources
# ============================================================

$(COBJECTS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ============================================================
# Compile C++ sources
# ============================================================

$(CXXOBJECTS): %.o: %.cpp
	$(CXX) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

# ============================================================
# Compile C++ (.cc) sources
# ============================================================

$(CCOBJECTS): %.o: %.cc
	$(CXX) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

# ============================================================
# Link application
# ============================================================

.PHONY: app
app: $(COBJECTS) $(CXXOBJECTS) $(CCOBJECTS)
	mkdir -p $(BUILD_PATH)
	$(file >objects.rsp,$(COBJECTS) $(CXXOBJECTS) $(CCOBJECTS))
	$(CXX) @objects.rsp -o $(BUILD_PATH)/$(NAME) $(LDFLAGS)

# ============================================================
# Clean
# ============================================================

.PHONY: clean
clean:
	rm -f $(COBJECTS)
	rm -f $(CXXOBJECTS)
	rm -f $(CCOBJECTS)