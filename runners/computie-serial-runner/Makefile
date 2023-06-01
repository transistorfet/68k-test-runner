
ROOT = .

include $(ROOT)/config.mk

RUNNER_OBJS = \
	src/tty_68681.o \
	src/runner.o \
	src/loader.o \
	src/main.o \
	libc-68k-none.a


all: runner.bin runner.load

libc-68k-none.a:
	make -C $(LIBC)/src

term:
	pyserial-miniterm /dev/ttyUSB0 38400

monitor.bin: $(MONITOR_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) --entry=_start -Tmonitor.ld -o $@.elf $^
	$(CC) $(CFLAGS) $(LDFLAGS) --entry=_start -Tmonitor.ld -Wl,--oformat=binary -o $@ $^
	hexdump -v -e '/1 "0x%02X, "' $@ > output.txt


runner.bin: $(RUNNER_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) --entry=main -Ttext=0x100000 -o $@.elf $^
	$(CC) $(CFLAGS) $(LDFLAGS) --entry=main -Ttext=0x100000 -Wl,--oformat=binary -o $@ $^


#runner.load: LOAD_ARGS = 180000


%.load: %.bin
	$(MAKE_LOAD_FILE) $^ $@ $(LOAD_ARGS)

%.send: %.bin
	$(MAKE_LOAD_FILE) $^ $@

%.a: $^
	$(AR) rc $@ $^
	$(RANLIB) $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.s
	$(AS) $(ASFLAGS) -c -o $@ $<

clean:
	find . \( -name "*.o" -or -name "*.a" -or -name "*.bin" -or -name "*.elf" -or -name "*.load" \) -delete -print

