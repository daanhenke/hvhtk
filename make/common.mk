SOURCE_DIR	= source
INCLUDE_DIR = include
BUILD_DIR	= build
OBJECT_DIR	= $(BUILD_DIR)/object

GENERATED_DIRS = $(BUILD_DIR) $(OBJECT_DIR)

CC 	= clang
CXX = clang++
LD 	= ld

EFI_CC 	= clang
EFI_CXX = clang++
EFI_LD 	= lld-link

CFLAGS 		=
CXXFLAGS 	= $(CFLAGS)
LDFLAGS 	=

EFI_CFLAGS 		= -target x86_64-pc-win32-coff -fno-stack-protector -fshort-wchar -mno-red-zone -I$(INCLUDE_DIR)
EFI_CXXFLAGS 	= $(EFI_CFLAGS)
EFI_LDFLAGS 	= -subsystem:efi_application -nodefaultlib -dll -entry:efi_main

$(BUILD_DIR)/%.efi:
	@echo [efi:ld] $@
	@mkdir -p $(dir $@)
	$(EFI_LD) $(EFI_LDFLAGS) -out:$@ $<

$(OBJECT_DIR)/efi-hypervisor/%.cc.o: $(SOURCE_DIR)/%.cc
	@echo [efi:cxx] $@
	@mkdir -p $(dir $@)
	$(EFI_CXX) $(EFI_CXXFLAGS) -o $@ -c $<