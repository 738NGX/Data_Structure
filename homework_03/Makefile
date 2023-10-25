CC       := g++
CCFLAGS  := -g -std=c++14 -Wall -Werror

BuildDir := build
Target   := runme

Source = $(wildcard *.cpp)
Object = $(Source:%.cpp=$(BuildDir)/%.o)

all: $(BuildDir) | $(Target)

$(Target): $(Object)
	@$(CC) -o $(BuildDir)/$(Target) $(Object)
	@cmd /C echo run $(BuildDir)\\$(Target)

$(BuildDir)/%.o: %.cpp
	@$(CC) $(CCFLAGS) -c $< -o $@

clean:
	@cmd /C del /Q /F $(BuildDir)
	@cmd /C rmdir /Q /S $(BuildDir)
	@cmd /C echo clean up build

$(BuildDir):
	@cmd /C mkdir $(BuildDir)
