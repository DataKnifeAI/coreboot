/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2020 Johanna Schander <coreboot@mimoja.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 */

#ifndef __GPIO_H__
#define __GPIO_H__

#include <soc/gpe.h>
#include <soc/gpio.h>
#include <stdint.h>

// Bootblock configuration
static const struct pad_config early_gpio_table[] = {};

// Ramstage configuration
static const struct pad_config gpio_table[] = {};

#endif // __GPIO_H__
