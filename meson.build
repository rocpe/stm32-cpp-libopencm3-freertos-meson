project(
    'stm32-cpp-libopencm3-freertos-meson', 'c', 'cpp',
    version : '1.0',
    default_options : [
      'c_std=c2x',
      'cpp_std=c++23'
      ],
    meson_version : '>=1.4.0'
)

cflags = [
    '-mcpu=cortex-m3',
    '-DSTM32F1'
]

cppflags = [
    '-mcpu=cortex-m3',
    '-DSTM32F1'
]

ldflags = [
    '-T../../stm32f103x8.ld',
    '--specs=nosys.specs',
    '-nostartfiles',
    '-Wl,--gc-sections'
]

sources = [
    'src/main.cxx',
]

incdir = [
  'inc'
]

cc = meson.get_compiler('c')
libopencm3_dep = cc.find_library('opencm3_stm32f1') #uses system library.
#subdir('libs/libopencm3')

# include doxygen generation if enabled
if get_option('enable_docs')
  subdir('docs')
endif

# enable FreeRTOS
subdir('libs/FreeRTOS')

exe = executable(
    meson.project_name() + '.elf',
    sources,
    include_directories : incdir,
    c_args: cflags,
    cpp_args: cppflags,
    link_args: ldflags,
    dependencies: [libopencm3_dep, freertos_dep]
)

bin = custom_target('bin',
    input: exe,
    output: exe.full_path().split('/')[-1].split('.elf')[0] + '.bin',
    command: [ find_program('objcopy'), '-O', 'binary', '@INPUT@', '@OUTPUT@' ],
    build_by_default: true,
    depends: exe
)

stm32flash = find_program('st-flash', required: false)
if stm32flash.found()
    run_target(
        'flash',
        command: [
            stm32flash,
            '--reset',
            'write', bin.full_path(),
            '0x08000000',
        ],
        depends: bin
    )
endif
