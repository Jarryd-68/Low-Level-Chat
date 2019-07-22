Memory management
=================

So I am writing this on one take my dudes.

Before I explain what the hell the _"heap"_ is and what `malloc` and `free` do I need to explain some other things.

For the programs we will be writing there are a few things to take note of. Your CPU has different modes it can operate in and sub-modes within these. On x86,
for reasons of backwards compatibility with older software, the boot procedure had to stay the same. So x86 CPUs literally have years of history always implemented in them.

I was going to write about how the boot procedure works but I can leave that for ater.

Basically with the help of the chain of events `CPU hardwired to run code memory mapped to the BIOS firmware chip -> BIOS reads in boot sector from disk -> Grub (typical boot sector program) -> Linux kernel (multiple stages of loading) -> Starts systemd or whatever init process (first process to be spawned)`.
You end up, on x86_32, in 32-Bit Protected Mode. The word **protected** is important as this mode introduces a layer of address translation.

When you started up in 16-bit mode the address you generate in your software and then use to store a value at it for example is the address that the memory controller sees.

`Input address -> Address seen by memory controller` (the address `0` is `0` in your RAM chip).

When you are in 32-Bit protected mode the address you generate, say now `0`, goes through a translation formula, done by hardware,
and maps to a different physical address. What this allows you to do is have two processes, only one running at any given time on a single core, both use the same address (we call it a virtual address) like `0` but the physical address can differ (you could make them map to the same physical address).

I took this diagram from this site called osdev.org which makes it easy to understand.


Basically there is a register that the Linux kernel changes when it switches processes and this changes the whole base mapping, resulting in a sometimes dfferent mapping (as mentioned above you can make the virtual address `0` in **process a** map to the same physical address as the virtual address `0` in **process b**.
