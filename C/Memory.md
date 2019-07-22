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

![https://wiki.osdev.org/images/thumb/7/77/Paging_Structure.gif/467px-Paging_Structure.gif](https://wiki.osdev.org/images/thumb/7/77/Paging_Structure.gif/467px-Paging_Structure.gif)

Basically there is a register (the one called $cr3) that the Linux kernel changes when it switches processes and this changes the whole base mapping, resulting in a sometimes dfferent mapping (as mentioned above you can make the virtual address `0` in **process a** map to the same physical address as the virtual address `0` in **process b**.

The reason the above is important to understand is just so you know that the addresses we are using in our programs are not the physical ones but only the virtual ones.

## What is memory management?

There are several meanings to it like managing the mappings of memory mentioned above but what this refers to in the context of the heap, `malloc` and `free` is the management of a region of memory called the heap.

Basically the heap is a data structure beginning at a certain address in memory that holds the address of allocated chunks of memory and their length of allocation, meaning from address `5` for 2 bytes (`5` to `6` (one byte) and `6` to `7` (another byte)). Allocating this chunk of memory is done by the function `malloc` which simply maniuplates this data structure that keeps track of allocated regions and remaining memory that can be used to allocate chunks from. Because it manages it all for us it decides what address the chunk to be allocated will be (not that we would care much for what we are doing here) but we definately get our number of bytes (size of our region) allocated to us, starting from that point and growing upwards.

````c
void* addy = malloc(4);
*((int*)addy) = 69;
````

The above code gets a, on x86_32, 32-bit number (the size of an address in 32-Bit protected mode) returned from `malloc` and assigned to the variable `addy`. `void*` is used instead of say now using a `int` because this makes our code protable, meaning it can be recompiled for x86_64 and it will be the size of `long`. Else, we have to write more code.

The `(int*)` type cast means treat this address as a pointer to an integer. All this means is that when we write to this address we will write 4 bytes, offset from the address (value of `addy`). It means the number on the right hand side will be widened to 32-bits, which makes sense as we then write 32-bits (4 bytes).
