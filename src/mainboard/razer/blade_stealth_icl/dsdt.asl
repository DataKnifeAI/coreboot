/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2018 Intel Corporation
 * Copyright (C) 2020 Johanna Schander <git@mimoja.de>
 *
 * Adapted for 4.19-era ACPI layout (acpi/acpi.h + dsdt_top.asl).
 */

#include <acpi/acpi.h>

DefinitionBlock(
	"dsdt.aml",
	"DSDT",
	ACPI_DSDT_REV_2,
	OEM_ID,
	ACPI_TABLE_CREATOR,
	0x20110725	// OEM revision
)
{
	#include <acpi/dsdt_top.asl>
	#include <soc/intel/common/block/acpi/acpi/platform.asl>
	#include <soc/intel/common/block/acpi/acpi/globalnvs.asl>

	#include <cpu/intel/common/acpi/cpu.asl>

	Device (\_SB.PCI0)
	{
		#include <soc/intel/common/block/acpi/acpi/northbridge.asl>
		#include <soc/intel/icelake/acpi/southbridge.asl>
	}

	#include <southbridge/intel/common/acpi/sleepstates.asl>

	#include "acpi/mainboard.asl"
}
