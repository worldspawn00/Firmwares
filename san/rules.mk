# project specific files
SRC +=

## chip/board settings
# the next two should match the directories in
#  <chibios>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
MCU_FAMILY = STM32
MCU_SERIES = STM32F0xx
# linker script to use
# it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
#  or <this_dir>/ld/
MCU_LDSCRIPT = STM32F042x6
# startup code to use
# is should exist in <chibios>/os/common/ports/ARMCMx/compilers/GCC/mk/
MCU_STARTUP = stm32f0xx
# it should exist either in <chibios>/os/hal/boards/
#  or <this_dir>/boards
BOARD = GENERIC_STM32_F042
# Cortex version
# Teensy LC is cortex-m0; Teensy 3.x are cortex-m4
MCU  = cortex-m0
# ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
ARMV = 6
# If you want to be able to jump to bootloader from firmware on STM32 MCUs,
# set the correct BOOTLOADER_ADDRESS. Either set it here, or define it in
# ./bootloader_defs.h or in ./boards/<FOO>/bootloader_defs.h (if you have
# a custom board definition that you plan to reuse).
# If you're not setting it here, leave it commented out.
# It is chip dependent, the correct number can be looked up here (page 175):
# http://www.st.com/web/en/resource/technical/document/application_note/CD00167594.pdf
# This also requires a patch to chibios:
#   <tmk_dir>/tmk_core/tool/chibios/ch-bootloader-jump.patch
#STM32_BOOTLOADER_ADDRESS = 0x1FFFC800

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   atmega32a    bootloadHID
# BOOTLOADER = atmel-dfu


# If you don't know the bootloader type, then you can specify the
# Boot Section Size in *bytes* by uncommenting out the OPT_DEFS line
#   Teensy halfKay      512
#   Teensy++ halfKay    1024
#   Atmel DFU loader    4096
#   LUFA bootloader     4096
#   USBaspLoader        2048
# OPT_DEFS += -DBOOTLOADER_SIZE=4096

DFU_ARGS = -a 0 -s 0x08000000:leave


# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no      # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = yes       # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
CONSOLE_ENABLE = no        # Console for debug(+400)
COMMAND_ENABLE = no        # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes            # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality on B7 by default
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
MIDI_ENABLE = no            # MIDI support (+2400 to 4200, depending on config)
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE = no           # Audio output on port C6
FAUXCLICKY_ENABLE = no      # Use buzzer to emulate clicky switches
HD44780_ENABLE = no 		# Enable support for HD44780 based LCDs (+400)

