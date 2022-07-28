CXX = clang++
CXXFLAGS = -g

azalea_sourcedir := src
azalea_objdir := obj
azalea_bindir := bin
azalea_includedir := include

azalea_source_cxx := $(wildcard $(azalea_sourcedir)/*.cpp)

azalea_obj := $(subst $(azalea_sourcedir)/,$(azalea_objdir)/,$(addsuffix .o,$(basename $(lupine_source_cxx))))

azalea: dirs bin/azalea

dirs:
	@mkdir -p $(azalea_sourcedir)
	@mkdir -p $(azalea_objdir)
	@mkdir -p $(azalea_bindir)
	@mkdir -p $(azalea_includedir)

bin/azalea: $(wildcard src/*.cpp)
	@echo "Compiling azalea."
	@echo "  CXX $^"
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) -I './include' -std=c++17 $^ -o $@
