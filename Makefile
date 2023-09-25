WCC = wcc386
WCFLAGS = -bt=dos -za99 -d2 -3r -oaxt -q

objs := $(patsubst %.c,%.obj,$(wildcard src/*.c))

all: $(objs) dostest1 dos4gw
.PHONY: $(objs) dostest1 dos4gw clean

$(objs): %.obj: %.c
	@echo "Compiling $<"
	@$(WCC) $(WCFLAGS) -fo=$@ $<

dostest1: $(objs)
	@mkdir -p bin
	@echo "Linking $@.exe"
	@wlink OPTION QUIET NAME bin/$@ SYSTEM dos4g OPTION map=bin/$@.map $(foreach obj, $(objs), FILE $(obj))

dos4gw:
	@echo "Copying DOS4GW"
	@cp -n $(WATCOM)/binw/dos4gw.exe bin/dos4gw.exe

clean:
	@echo "Cleaning"
	@rm -f $(objs)
	@rm -rf bin
