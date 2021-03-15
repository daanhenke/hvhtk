include make/common.mk

EFI_HYPERVISOR_TARGET = $(BUILD_DIR)/hva.efi

EFI_HYPERVISOR_SOURCES = \
	arch/efi/main.cc \
	arch/efi/log.cc \
	arch/efi/platform.cc \
	visor/visor.cc \
	arch/efi/memory.cc \
	arch/efi/bitmap.cc \
	arch/efi/host.cc \
	cpu/memory.cc \
	visor/host.cc \
	arch/efi/idt.asm
EFI_HYPERVISOR_OBJECTS = $(addprefix $(OBJECT_DIR)/efi-hypervisor/,$(addsuffix .o,$(EFI_HYPERVISOR_SOURCES)))
$(EFI_HYPERVISOR_TARGET): $(EFI_HYPERVISOR_OBJECTS)

.PHONY: all
all: $(EFI_HYPERVISOR_TARGET)