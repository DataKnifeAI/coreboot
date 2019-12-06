/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2018 Intel Corporation.
 * Copyright (C) 2020 Johanna Schander <coreboot@mimoja.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <console/console.h>
#include <fsp/api.h>
#include <soc/romstage.h>
#include <spd_bin.h>
#include <string.h>
#include <arch/cpu.h>
#include <intelblocks/mp_init.h>

#define RCOMP_TARGET_PARAMS 0x5


static const u8 dqs_map[2][8] = { {0, 2, 1, 3, 6, 7, 4, 5},
								  {1, 0, 3, 2, 5, 4, 7, 6} };

static const u16 rcomp_resistor[3] = {100, 100, 100};

static const u16 rcomp_target[RCOMP_TARGET_PARAMS] = {60, 20, 20, 20, 20};

static const u8 dq_map[12] = {0x0F, 0xF0, 0x0F, 0xF0, 0xFF, 0x00,
			      0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void mainboard_memory_init_params(FSPM_UPD *mupd)
{
	struct region_device spd_rdev;
	uint32_t spd_len = 0;
	FSP_M_CONFIG *mem_cfg = &mupd->FspmConfig;

	if (get_spd_cbfs_rdev(&spd_rdev, 0) < 0)
		die("MBOARD spd.bin not found\n");

	spd_len = region_device_sz(&spd_rdev);

	mem_cfg->MemorySpdDataLen = spd_len;

	/* Memory leak is ok since we have memory mapped boot media */
	mem_cfg->MemorySpdPtr00 = (uintptr_t)rdev_mmap_full(&spd_rdev);
	mem_cfg->MemorySpdPtr10 = mem_cfg->MemorySpdPtr00;

	mem_cfg->SpdAddressTable[0] = 0x0;
	mem_cfg->SpdAddressTable[1] = 0x0;
	mem_cfg->SpdAddressTable[2] = 0x0;
	mem_cfg->SpdAddressTable[3] = 0x0;


	mem_cfg->DqPinsInterleaved = 0;
	mem_cfg->CaVrefConfig = 0x2; /* VREF_CA->CHA/CHB */
	mem_cfg->ECT = 1;	     /* Early Command Training Enabled */
	mem_cfg->RefClk = 0;	     /* Auto Select CLK freq */

	memcpy(&mem_cfg->DqByteMapCh0, dq_map, sizeof(dq_map));
	memcpy(&mem_cfg->DqByteMapCh1, dq_map, sizeof(dq_map));

	memcpy(&mem_cfg->DqsMapCpu2DramCh0, dqs_map[0], sizeof(dqs_map[0]));
	memcpy(&mem_cfg->DqsMapCpu2DramCh1, dqs_map[1], sizeof(dqs_map[1]));

	memcpy(&mem_cfg->RcompResistor, rcomp_resistor, sizeof(rcomp_resistor));
	memcpy(&mem_cfg->RcompTarget, rcomp_target, sizeof(rcomp_target));
}
