#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <math.h>
#include <libcpuid/libcpuid.h>
#include <sys/sysinfo.h>
#include "colour.h"

int main(void) {
	// CPU
	struct cpu_raw_data_t CPU_rawdata;
	struct cpu_id_t       CPU_data;
	bool                  CPU          = true;
	size_t                CPU_SpeedMHz = 0;
	
	if (cpuid_get_raw_data(&CPU_rawdata) < 0) {
		CPU = false;
	}
	if (cpu_identify(&CPU_rawdata, &CPU_data) < 0) {
		CPU = false;
	}
	if (CPU) {
		CPU_SpeedMHz =  cpu_clock_measure(200, 0);
		printf(colour_green "CPU: " colour_reset "%s (%i cores, %i threads) @ %liMHz\n", CPU_data.brand_str, CPU_data.num_cores, CPU_data.total_logical_cpus , CPU_SpeedMHz);
		printf(colour_green "CPU Cache: " colour_reset "%iK L1 %iK L2\n", CPU_data.l1_data_cache, CPU_data.l2_cache);
	}

	// RAM
	struct sysinfo sys_info;
	size_t         RAM_GB;
	sysinfo(&sys_info);
	RAM_GB = (size_t) ceil((((sys_info.totalram + 512)/1024)/1024)/1024);
	printf(colour_green "RAM: " colour_reset "%liGB\n", RAM_GB);

	// Swap
	size_t Swap_MB = (size_t) round(((sys_info.totalswap + 512)/1024)/1024);
	printf(colour_green "Swap: " colour_reset "%liMB\n", Swap_MB);

	// end of program
	return 0;
}