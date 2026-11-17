CXX = g++
CXXFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lX11 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

DEPS_DIR = deps
IMGUI_DIR = $(DEPS_DIR)/imgui
IMGUI_TAG = v1.93.0

# Select only the files you want (leading '/' anchors to the repository root)
IMGUI_FILES = /imconfig.h \
              /imgui.h \
              /imgui_internal.h \
              /imstb_rectpack.h \
              /imstb_textedit.h \
              /imstb_truetype.h \
              /imgui.cpp \
              /imgui_demo.cpp \
              /imgui_draw.cpp \
              /imgui_tables.cpp \
              /imgui_widgets.cpp \
              /backends/imgui_impl_glfw.h \
              /backends/imgui_impl_glfw.cpp \
              /backends/imgui_impl_opengl3.h \
              /backends/imgui_impl_opengl3.cpp \
              /backends/imgui_impl_opengl3_loader.h

# Automatically builds the .cpp list from IMGUI_FILES
IMGUI_SRC = $(addprefix $(IMGUI_DIR),$(filter %.cpp,$(IMGUI_FILES)))

INCLUDES = -I./include -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends
SRC = $(wildcard *.cpp) $(wildcard ./include/*.cpp) $(IMGUI_SRC)

.PHONY: compile run clean distclean

# Downloads metadata only, then fetches and checks out the selected files
$(IMGUI_DIR):
	mkdir -p $(DEPS_DIR)
	git clone --depth 1 --filter=blob:none --no-checkout --branch $(IMGUI_TAG) https://github.com/ocornut/imgui.git $(IMGUI_DIR)
	git -C $(IMGUI_DIR) sparse-checkout set --no-cone $(IMGUI_FILES)
	git -C $(IMGUI_DIR) checkout

compile: $(IMGUI_DIR)
	mkdir -p ./bin
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o ./bin/program $(SRC) include/glad/src/glad.c $(LDFLAGS) 

run: compile
	./bin/program

clean:
	rm -f ./bin/*
	rm -f imgui.ini

distclean: clean
	rm -rf $(DEPS_DIR)
