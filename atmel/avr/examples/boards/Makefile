
CWD		:=	$(dir $(lastword $(MAKEFILE_LIST)))

#  Produce HTML documentation
#
.PHONY: doc
doc:
	@cd $(CWD)../../../../doxygen && $(MAKE) --no-print-directory

#  Store flash program memory and fuse bytes
#    Use this on a newly received board to backup its content
#
.PHONY: backup
backup:
ifeq (,$(DEVICE))
	@echo Usage: make DEVICE=XXX backup
else
	@avrdude -c usbasp -p $(DEVICE) -U flash:r:$(DEVICE).flash.bin:r
	@avrdude -c usbasp -p $(DEVICE)	\
		-U efuse:r:-:h		\
		-U hfuse:r:-:h		\
		-U lfuse:r:-:h		\
		-U lock:r:-:h		\
		-U calibration:r:-:h	\
		2>/dev/null >$(DEVICE).fuses.hex
	@(set -e ;\
	  read line ; echo HW_DEVICE_FUSE_EB=$$line	;\
	  read line ; echo HW_DEVICE_FUSE_HB=$$line	;\
	  read line ; echo HW_DEVICE_FUSE_LB=$$line	;\
	  read line ; echo HW_DEVICE_FUSE_LOCK=$$line	;\
	  read line ; echo HW_DEVICE_FUSE_CAL=$$line )	\
	  <$(DEVICE).fuses.hex >$(DEVICE).fuses		\
	  && rm $(DEVICE).fuses.hex
endif
