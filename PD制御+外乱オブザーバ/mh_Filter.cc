#include "mh_Filter.hh"
#include <vector>
#include <math.h>

mhFILTERS::mhFILTERS(){

	LPF_a = 0.0;
	LPF_aZi = 0.0;
	LPF_output = 0.0;
	DLPF_fb = 0.0;
	DLPF_Zi = 0.0;
	DLPF_output = 0.0;

}

double mhFILTERS::LPF(double LPF_input, double LPF_g, double LPF_Ts){

	LPF_a       = (LPF_input - LPF_output) * LPF_g;

	LPF_output += (LPF_a + LPF_aZi)*LPF_Ts*0.5;
	LPF_aZi     = LPF_a;

	return LPF_output;

}

double mhFILTERS::DLPF(double DLPF_input, double DLPF_g, double DLPF_Ts){

	DLPF_output = (DLPF_input - DLPF_fb)*DLPF_g;

	DLPF_fb    += (DLPF_output + DLPF_Zi)*DLPF_Ts*0.5;
	DLPF_Zi     = DLPF_output;

	return DLPF_output;

}
