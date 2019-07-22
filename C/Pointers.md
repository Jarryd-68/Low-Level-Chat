Pointers
========

Apparently the hardest part of C but that is just a lie told by the government. This is a simpification as different addressing modes exist but that isn't important to understand this all and also relocation.

## An introduction to how stuff actually works

First of all before pointers will make sense I want to explain what a "variable" actually is. Upon compile time "variables" like `x`, `y` and `godPleaseHelpMe` and translated to numbers representing addresses in memory.

It might be mapped like so for example:

1. `x` becomes the address `77`
2. `y` becomes the address `88`
3. `godPleaseHelpMe` becomes the address `99`

The way memory works is that you can give it an address, like `77` and then tell it to save a value at that address like `69` for example. Or maybe at address `88` we decide to store the value `255` and so on.

The way you visualise this at the C-level is `x = 69` but what is really happening is that the value of `69` is being set at address `77`.

### One little side note

Depending on the architetcure, what CPU you are using, they might use addresses in different ways. x86, which is probably what your desktop machine uses, is byte-addressed which means that each address addresses a byte.

## Now what are ~~🅱️ointers~~ Pointers

Now that we understand what a variable really is (address and value-at-that-address pair) the idea of a pointer is simple.

Take our variable `x` with a value of `69`. Now what that really is is some address, say now `25`, with a value stored at it being `69`.

Now we make another variable and call it `xAddr`, which is just an address and value pair, so let's say we have the address be `77`. Now the value we set is arbitrary but in this case we will interpret the value we assign here as yet another address. By interpret I mean we will pass it to the instructions that the CPU has that interpret such values as addresses.

So we then set the value at the address `77` (which is our variable `xAddr`) to the value (or address with respect to the way it will be used/interpreted) `25`.
