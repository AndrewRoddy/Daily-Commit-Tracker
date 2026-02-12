CXX = C:/msys64/ucrt64/bin/g++.exe
CXXFLAGS = -std=c++17 -fdiagnostics-color=always -g -mwindows

# Directories
SRC_DIR = src
INC_DIR = include
CURL_BASE = lib/curl-8.10.1_1-win64-mingw
BIN_DIR = bin

# Include and library paths
INCLUDES = -I$(INC_DIR) -I$(CURL_BASE)/include
LDFLAGS = -L$(CURL_BASE)/lib
LIBS = -lcurl.dll -lshell32

# Source files
SOURCES = $(SRC_DIR)/main.cpp \
          $(SRC_DIR)/tokens.cpp \
          $(SRC_DIR)/tray.cpp \
          $(SRC_DIR)/tzone.cpp \
          $(SRC_DIR)/tracker.cpp

TARGET = $(BIN_DIR)/Daily-Commit-Tracker.exe

all: clean $(TARGET)

$(TARGET): $(SOURCES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SOURCES) $(LDFLAGS) $(LIBS) -o $(TARGET)

clean:
	-rm -f $(TARGET)

.PHONY: all clean
