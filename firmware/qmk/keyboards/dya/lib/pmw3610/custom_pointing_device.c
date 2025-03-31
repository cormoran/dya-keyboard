// Copyright 2025 cormoran707
// SPDX-License-Identifier: GPL-2.0-or-later
#include "pmw3610.h"
#include "pointing_device.h"

void pointing_device_driver_init(void) {
    pmw3610_pointing_device_driver.init();
}

report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) {
    return pmw3610_pointing_device_driver.get_report(mouse_report);
}

uint16_t pointing_device_driver_get_cpi(void) {
    return pmw3610_pointing_device_driver.get_cpi();
}

void pointing_device_driver_set_cpi(uint16_t cpi) {
    pmw3610_pointing_device_driver.set_cpi(cpi);
}
