CXX = clang++
CXXFLAGS = -g -lpthread

azalea_sourcedir := src
azalea_objdir := obj
azalea_bindir := bin
azalea_includedir := include
azalea_libdir := lib

azalea_source_cxx := $(shell find src/ -type f -name '*.cpp')

azalea_obj := $(subst $(azalea_sourcedir)/,$(azalea_objdir)/,$(addsuffix .o,$(basename $(lupine_source_cxx))))

azalea: dirs bin/azalea

dirs:
	@mkdir -p $(azalea_sourcedir)
	@mkdir -p $(azalea_objdir)
	@mkdir -p $(azalea_bindir)
	@mkdir -p $(azalea_includedir)
	@mkdir -p $(azalea_libdir)

bin/azalea: $(azalea_source_cxx)
	@echo "Compiling azalea."
	@echo "  CXX $^"
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) -I './include' -std=c++17 $^ lib/libz.a -o $@
