add_executable(balance-board
        balance-board.c
        lib/fonts.c
        lib/st7735.c
        lib/DEV_Config.c
        lib/ICM20948.c
        )

# pull in common dependencies
target_link_libraries(
        balance-board
        hardware_pwm
        hardware_pio
        hardware_spi
        hardware_i2c
        pico_stdlib
)

# enable usb output, disable uart output
pico_enable_stdio_usb(balance-board 1)
pico_enable_stdio_uart(balance-board 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(balance-board)

# add url via pico_set_program_url
example_auto_set_url(balance-board)
