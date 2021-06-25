#include "mh_PDctrl.hh"
double ctrl(double x_cmd, double dx_cmd, double x, double dx, double Kp, double Kd){
double ddx_ref(0.0);
	ddx_ref = (x_cmd - x)*Kp + (dx_cmd - dx)*Kd;

	return ddx_ref;

}
