#ifndef DEF_FILTERS
#define DEF_FILTERS

class mhFILTERS{
private:
	double LPF_a, LPF_aZi, LPF_output;
	double DLPF_fb, DLPF_Zi, DLPF_output;
public:
	mhFILTERS();
	double LPF(double LPF_input, double LPF_g, double LPF_Ts);//LPF
	double DLPF(double DLPF_input, double DLPF_g, double DLPF_Ts);//擬似微分
};

#endif
