WS2812_DRIVER = vendor
POINTING_DEVICE_DRIVER = custom

SPI_DRIVER_REQUIRED = yes

SRC += lib/pmw3610/pmw3610.c
SRC += lib/pmw3610/custom_pointing_device.c
