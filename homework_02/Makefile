CC       := g++
CCFLAGS  := -g -std=c++14 -Wall -Werror

BuildDir := build
Target   := runme

Source = $(wildcard *.cpp)
Object = $(Source:%.cpp=$(BuildDir)/%.o)

all: $(BuildDir) | $(Target)

$(Target): $(Object)
	@$(CC) -o $(BuildDir)/$(Target) $(Object)
	@echo run $(BuildDir)\$(Target)

$(BuildDir)/%.o: %.cpp
	@$(CC) $(CCFLAGS) -c $< -o $@

clean:
	@rm -rf $(BuildDir)
	@echo clean up build

$(BuildDir):
	@mkdir $@
