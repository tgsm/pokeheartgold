# Use the assembler to build the scripts
# Framework for when we actually get around to script dumping
SCRIPT_DIR  := files/fielddata/script/scr_seq
SCRIPT_NARC := $(SCRIPT_DIR).narc
SCRIPT_SRCS := $(wildcard $(SCRIPT_DIR)/*.s)
SCRIPT_OBJS := $(SCRIPT_SRCS:%.s=%.o)
SCRIPT_BINS := $(SCRIPT_SRCS:%.s=%.bin)

# Delete intermediate object files
.INTERMEDIATE: $(SCRIPT_OBJS)

ifeq ($(NODEP),)
$(SCRIPT_DIR)/%.bin: dep = $(shell $(SCANINC) -I . -I ./include -I $(WORK_DIR)/files -I $(WORK_DIR)/lib/include $*.s)
else
$(SCRIPT_DIR)/%.bin: dep :=
endif

$(SCRIPT_BINS): %.bin: %.s $$(dep)
	$(WINE) $(MWAS) $(MWASFLAGS) -o $*.o $<
	$(OBJCOPY) -O binary --file-alignment 4 $*.o $@

$(SCRIPT_NARC): $(SCRIPT_BINS)

# Once this has been reversed, uncomment the below
# FS_CLEAN_TARGETS += $(SCRIPT_NARC) $(SCRIPT_BINS)
FS_CLEAN_TARGETS += $(SCRIPT_NARC) $(SCRIPT_OBJS) \
	$(SCRIPT_DIR)/scr_seq_00000000.bin \
	$(SCRIPT_DIR)/scr_seq_00000001.bin \
	$(SCRIPT_DIR)/scr_seq_00000006.bin \
	$(SCRIPT_DIR)/scr_seq_00000017.bin \
	$(SCRIPT_DIR)/scr_seq_00000020.bin \
	$(SCRIPT_DIR)/scr_seq_00000027.bin \
	$(SCRIPT_DIR)/scr_seq_00000028.bin \
	$(SCRIPT_DIR)/scr_seq_00000036.bin \
	$(SCRIPT_DIR)/scr_seq_00000056.bin \
	$(SCRIPT_DIR)/scr_seq_00000057.bin \
	$(SCRIPT_DIR)/scr_seq_00000062.bin \
	$(SCRIPT_DIR)/scr_seq_00000068.bin \
	$(SCRIPT_DIR)/scr_seq_00000072.bin \
	$(SCRIPT_DIR)/scr_seq_00000073.bin \
	$(SCRIPT_DIR)/scr_seq_00000074.bin \
	$(SCRIPT_DIR)/scr_seq_00000079.bin \
	$(SCRIPT_DIR)/scr_seq_00000083.bin \
	$(SCRIPT_DIR)/scr_seq_00000137.bin \
	$(SCRIPT_DIR)/scr_seq_00000138.bin \
	$(SCRIPT_DIR)/scr_seq_00000139.bin \
	$(SCRIPT_DIR)/scr_seq_00000208.bin \
	$(SCRIPT_DIR)/scr_seq_00000209.bin \
	$(SCRIPT_DIR)/scr_seq_00000964.bin \
