

#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

include $(DEVKITARM)/base_rules

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
# DATA is a list of directories containing binary data
# GRAPHICS is a list of directories containing files to be processed by grit
#
# All directories are specified relative to the project directory where
# the makefile is found
#
#---------------------------------------------------------------------------------
TARGET		:= $(notdir $(CURDIR))
BUILD		:= build
SOURCES		:= source
INCLUDES	:= include
DATA		:=
MUSIC		:=

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
ARCH	:=	-mthumb -mthumb-interwork

CFLAGS	:=	-g -Wall -O3\
		-mcpu=arm7tdmi -mtune=arm7tdmi\
 		-fomit-frame-pointer\
		-ffast-math \
		$(ARCH)

CFLAGS	+=	$(INCLUDE)

CXXFLAGS	:=	$(CFLAGS) -fno-rtti -fno-exceptions

ASFLAGS	:=	-g $(ARCH)
LDFLAGS	=	-g $(ARCH) -Wl,-Map,$(notdir $*.map)

#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project
#---------------------------------------------------------------------------------
LIBS	:= -lgba
 
 
#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:=	$(DEVKITPRO)/libgba

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------


 
export OUTPUT	:=	game_mb
 
export VPATH	:=	$(foreach dir,$(SOURCES),./$(dir)) \
					$(foreach dir,$(DATA),./$(dir)) \
					$(foreach dir,$(GRAPHICS),./$(dir))

export DEPSDIR	:=	./$(BUILD)

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

C_SRCS 		:= 	$(call rwildcard,$(SOURCES),*.c)
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

ifneq ($(strip $(MUSIC)),)
	export AUDIOFILES	:=	$(foreach dir,$(notdir $(wildcard $(MUSIC)/*.*)),./$(MUSIC)/$(dir))
	BINFILES += soundbank.bin
endif

export LD	:=	$(CC)


OFILES_BIN := $(addsuffix .o,$(BINFILES))

#OFILES_SOURCES := $($(C_SCRS):%=$(BUILD)/%.o)
OFILES_SOURCES := $(foreach file,$(C_SRCS),$(BUILD)/$(file).o)
OFILES := $(OFILES_BIN) $(OFILES_SOURCES)

export HFILES := $(addsuffix .h,$(subst .,_,$(BINFILES)))

export INCLUDE	:=	$(foreach dir,$(INCLUDES),-iquote ./$(dir)) \
					$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
					-I./$(BUILD)
 
export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)

.PHONY: all clean

all: $(OUTPUT).gba

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(BUILD) $(TARGET).elf $(TARGET).gba 
 
$(OUTPUT).gba: $(OUTPUT).elf
	$(OBJCOPY) -O binary $< $@
	@echo built ... $(notdir $@)
	@gbafix $@


$(OUTPUT).elf: $(OFILES_SOURCES)
	echo $(OFILES_SOURCES) __ $(C_SRCS)
	@echo linking cartridge
	$(LD)  $(LDFLAGS) -specs=gba.specs $(OFILES) $(LIBPATHS) $(LIBS) -o $@

$(BUILD)/%.o: %
	@mkdir -p $(BUILD)/$(SOURCES)
	@echo $(notdir $<)
	$(CC) -MMD -MP -MF $(DEPSDIR)/$*.d $(CFLAGS) -c $< -o $@ $(ERROR_FILTER) $(INCLUDE)