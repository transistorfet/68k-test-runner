
68k Test Runner
===============

###### *Started May 27, 2023*

With this software, and some kind of 68k-based hardware system, it should be possible to run the
ProcessorTests suite from Tom Harte against real hardware, and verify the results.  This is not only
to verify the test suite against real hardware, but also could be helpful in testing against other
variants of the 68k, such as the 68030, or to develop test suites for those other variants.

The hardware targeted by the only runner I currently have is the
[Computie](https://jabberwocky.ca/projects/computie/) single board computer.  Since the test suite
is far too big to store on the device at nearly 9GB, it uses a serial port to communicate with a
desktop that controls the test runner that's written for the hardware, which runs the test and
returns the results.  It takes about 5 minutes to run through about 8000 tests for a single
instruction variant.

Because computie is running the test from memory, it can't capture most of the interrupt result
tests, and could halt if an interrupt occurs during a test.  It would be possible to use Fidget
or the 68kSupervisor/Arduino, with the memory on computie removed and data fed directly to the
processor as it requests it.  That should allow most tests to be tested, but it would likely be
slower in the case of the supervisor, and require verilog which I'm not good at yet for
[Fidget](https://jabberwocky.ca/projects/fidget/).  I could also make custom hardware.

The Computie 68k test runner has a copy of the libc implementation from ComputieOS, in the Computie
repository.  It is loaded directly from the monitor and runs on the bare system.

The python script can also report on data stored the sqlite database of results.  The repository has
the ASL.b and ASR.b instructions as examples, but I haven't scrutinized the tests or the runner to
know if they are accurate.  The ASR.b instructions are showing that 1642 tests don't match what the
hardware is doing, and I think the hardware is correct.  In most of the tests, the flags are
incorrectly set, with the test thinking the extend and carry flags shouldn't be set, but the
hardware thinking they should.  Since it's an ASR.b instruction, and the cases seem to be shifting a
value with the msb set, I think the flags should be set instead of cleared.  I've included a list of
the numbers of each test that failed in ASR.b-failures.txt

I'll probably take a break from this for the time being but might revisit it when I get back to
validating [Moa](https://jabberwocky.ca/projects/moa/)

