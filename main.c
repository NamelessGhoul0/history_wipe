/*
	Copyright (C) 2017, NamelessGhoul0

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <psp2kern/kernel/threadmgr.h>
#include <psp2kern/kernel/processmgr.h>
#include <psp2kern/kernel/modulemgr.h>
#include <psp2kern/io/fcntl.h>

int main_thread(SceSize args, void *argp) {

	while (1) {
		ksceIoRemove("vd0:history/data.bin");
		ksceIoRemove("vd0:history/data.bak");
		ksceIoRemove("ur0:user/00/shell/playlog/playlod.dat");
		ksceIoRemove("ur0:user/00/shell/playlog/playlog.dat");
		ksceKernelDelayThread(900*1000*1000); // Delay for 15 minutes
	}

	return 0;
}

void _start() __attribute__ ((weak, alias ("module_start")));

int module_start(SceSize argc, const void *args) {
	SceUID thid = ksceKernelCreateThread("history_wipe", main_thread, 0x40, 0x10000, 0, 0, NULL);

	if (thid >= 0) {
		ksceKernelStartThread(thid, 0, NULL);
	}

	return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args) {
	return SCE_KERNEL_STOP_SUCCESS;
}
