# stm32-cpp-libopencm3-freertos-meson
Template for creating new project on STM32 in C++ with libopencm3 and FreeRTOS. The build system is Meson.
# Setup
I assume you have git, meson. arm-none-eabi-g++(and others) and libopencm3 installed on your system.

Clone this repo with submodules:
```bash
git clone --recurse-submodules https://github.com/rocpe/stm32-cpp-libopencm3-freertos-meson.git
```
Go to the root directory of the project and configure:
```bash
meson setup build/release --cross-file=cross-file.txt --buildtype=release
```
Or use build/debug and debugging symbols
```bash
meson setup build/debug --cross-file=cross-file.txt --buildtype=debugoptimized
```
You have to have installed libopencm3 globally on your system. ([package for Arch Linux](https://archlinux.org/packages/community/any/libopencm3/), [for other distros see this PKGBUILD file](https://github.com/archlinux/svntogit-community/blob/packages/libopencm3/trunk/PKGBUILD)). TODO: Add libopencm3 as submodule.

Then compile :
```bash
meson compile -C build/release
```
It should throw some linker warnings. Don't worry. As long as it compiles it's just fine.

You can compile with docs
```bash
meson compile -C build/release docs
```

Upload via st-link:
```bash
meson compile -C build/release flash
```

# Porting to other stm32
Default stm32 is stm32f103cbt6 (popular bluepill board). Here is shown how to port this project to other stm32 by example.
## Example: porting to stm32f411
Other popular board is blackpill. It uses either stm32f401 or stm32f411. The latter will be shown. 
1. Go to file cross-file.txt and change cpu to cortex-m4:
```
...
cpu = 'cortex-m4'
```
Stm32f411 has Cortex M4 core.

2. Change cflags, cppflags and linker script in `meson.build`:
```
...

cflags = [
    '-mcpu=cortex-m4',
    '-DSTM32F4'
]

cppflags = [
    '-mcpu=cortex-m4',
    '-DSTM32F4'
]

ldflags = [
    '-T../../stm32f411xc.ld', # new linker file
    '--specs=nosys.specs',
    '-nostartfiles',
    '-Wl,--gc-sections'
]
...
```

3. Add new linker script (named stm32f411xc.ld) in the root directory of the project. Content of `stm32f411xc.ld`:
```ld
/* Define memory regions. */
MEMORY
{
	rom (rx) : ORIGIN = 0x08000000, LENGTH = 256K
	ram (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

/* Include the common ld script. */
INCLUDE cortex-m-generic.ld
```
For other stm32 you can find linker script in the [internet](github.com/alextrical/STM32-linker-scripts/tree/main/LD%20Files) (use just memory layout part of those scripts) or read documentation for memory layout for your MC.

4. Edit `meson_options.txt` file:
```
...
option('port',
  type : 'string',
  value : 'GCC/ARM_CM4F', # change to your MC arch. Look at libs/FreeRTOS/portable/
  description : 'Port folder')
```

5. Change `inc/FreeRTOSConfig.h` to match this MC. You can find a lot of examples across the internet.

6. Run setup as described above.

# TODO
1. Add libopencm3 as submodule and make it compile with meson.
