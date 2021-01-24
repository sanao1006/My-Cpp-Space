#include "mh_DOB.hh"

mhDOB::mhDOB(){

	for(int i(0); i<10; i++) b[i]=0.0, c[i]=0.0, bzi[i]=0.0;
	a=0.0;
	d=0.0;

}

double mhDOB::DOB(double Ia, double dXres, double Ktn, double Mn, double gdis, double Ts){

	a = (Ktn * Ia)+(gdis * Mn * dXres);

	b[0] = gdis * (a - c[0]);
	c[0] += (Ts / 2.0) * (b[0] + bzi[0]);

	bzi[0] = b[0];

	d = c[0] - (gdis * Mn * dXres);

	return d;

}


