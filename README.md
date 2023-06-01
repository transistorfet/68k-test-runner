
68k Test Runner
===============

###### *Started May 27, 2023*

With this software, and some kind of 68k-based hardware system, it should be possible to run the
ProcessorTests suite from Tom Harte against real hardware, and verify the results.  This is not only
to verify the test suite against real hardware, but also could be helpful in testing against other
variants of the 68k, such as the 68030, or to develop test suites for those other variants.

The hardware targeted by the runner itself is the
[Computie](https://jabberwocky.ca/projects/computie/) single board computer.  Since the test suite
is far too big to store on the device at nearly 9GB, it uses a serial port to communicate with a
desktop that controls the test runner that's written for the hardware, which runs the test and
returns the results

The Computie 68k test runner has a copy of the libc implementation from ComputieOS, in the Computie
repository.
