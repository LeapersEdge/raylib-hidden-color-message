CXX = g++
CXXFLAGS = -std=c++20 -Wall

rwildcard = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

SRCDIR = src
INCDIR = incl
UTILDIR = util
BUILDDIR = build
STATICLIBDIR = libs/_staticlibs

# libs ------------------------

IMGUIDIR = libs/imgui
RLIMGUIDIR = libs/rlimgui
STBDIR = libs/stb
RAYLIBDIR = libs/raylib

# -----------------------------

SRCS = $(call rwildcard,$(SRCDIR)/,*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

UTIL_SRCS = $(wildcard $(UTILDIR)/*.cpp)
UTIL_OBJS = $(patsubst $(UTILDIR)/%.cpp,$(BUILDDIR)/%.o,$(UTIL_SRCS))

# libs ------------------------

IMGUI_SRCS = $(wildcard $(IMGUIDIR)/*.cpp)
IMGUI_OBJS = $(patsubst $(IMGUIDIR)/%.cpp,$(BUILDDIR)/%.o,$(IMGUI_SRCS))

RLIMGUI_SRCS = $(wildcard $(RLIMGUIDIR)/*.cpp)
RLIMGUI_OBJS = $(patsubst $(RLIMGUIDIR)/%.cpp,$(BUILDDIR)/%.o,$(RLIMGUI_SRCS))

# -----------------------------

# add libs for include
INCFLAGS = -I$(INCDIR) -I$(UTILDIR) -I$(IMGUIDIR) -I$(RLIMGUIDIR) -I$(STBDIR) -I$(RAYLIBDIR)
LIBS = -lraylib -lglfw -lGL -lm -lpthread

TARGET = pipipopo

# add libs for objects
$(TARGET): $(OBJS) $(IMGUI_OBJS) $(RLIMGUI_OBJS) $(STB_OBJS) $(BUILDDIR)/main.o
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)/$(TARGET) $^ -L$(STATICLIBDIR) $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)  # Create the directory if it doesn't exist
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c -o $@ $<

$(BUILDDIR)/%.o: $(UTILDIR)/%.cpp
	@mkdir -p $(@D)  # Create the directory if it doesn't exist
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c -o $@ $<

# libs ------------------------

$(BUILDDIR)/%.o: $(IMGUIDIR)/%.cpp
	@mkdir -p $(@D)  # Create the directory if it doesn't exist
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c -o $@ $<

$(BUILDDIR)/%.o: $(RLIMGUIDIR)/%.cpp
	@mkdir -p $(@D)  # Create the directory if it doesn't exist
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c -o $@ $<

$(BUILDDIR)/%.o: $(STBDIR)/%.c
	@mkdir -p $(@D)  # Create the directory if it doesn't exist
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c -o $@ $<

# -----------------------------

$(BUILDDIR)/main.o: main.cpp
	@mkdir -p $(@D)  # Create the directory if it doesn't exist
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f $(BUILDDIR)/*.o $(BUILDDIR)/$(TARGET)