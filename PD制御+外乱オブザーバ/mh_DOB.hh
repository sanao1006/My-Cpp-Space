#ifndef DEF_DOB
#define DEF_DOB

class mhDOB{
private:
	double b[10], bzi[10], c[10];
	double a, d;
public:
	mhDOB();
	double DOB(double Ia, double dXres, double Ktn, double Mn, double gdis, double Ts);
};

#endif
