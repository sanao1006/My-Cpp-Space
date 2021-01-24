
#include <iostream>
#include <fstream>
#include "mh_PDctrl.cc"
#include "mh_Filter.cc"
#include "mh_DOB.cc"

int main(){
	// シミュレーション時間 [s]
	const double tEND = 10;
	// サンプリング [s]
	const double Ts = 0.0001;
	// 基本周波数 [rad/s]
	const double omega = 1.0*M_PI;
	// 各変数
	double t(0.0), Thd(0.0), dThd(0.0);
	double fexo(0.0), nf(0.0), nv(0.0);
	double Iimp(0.0), Iref(0.0), Icmp(0.0);
	double Tout(0.0), Thout(0.0);
	double T1(0.0), Tl(0.0), f2(0.0);
	double dThout(0.0), ddThout(0.0);
	double ddThref(0.0), error(0.0);
	// カウント変数
	int DisplayCount(0);
		
	const double K = 50.0;
	// 比例ゲイン
	static double Kp=K*K;
	// 微分ゲイン
	static double Kd=2*2*K;
	
	const double Ktn =0.414;//トルク定数
	const double Jn = 0.00586+0.001;//モータの慣性モーメント
	const double gpd =200.0;//
	const double gdob = 100.0;//カットオフ周波数

	/*
	Output
	*/
	FILE *file;
	file = fopen("DATA.dat", "w");
	std::cout << "=====================================" << std::endl;
	std::cout << "  Acceleration Contorol SIMULATION          " << std::endl;
	std::cout << "=====================================" << std::endl;

	
	mhDOB D[10];
	mhFILTERS F[10];
	/**
	* Real-time signal processing simulation
	*/
	do{
		//////////////////////////////
		/**
		* Input signal
		*/
		// Periodic signal
		Thd = 0.3*sin(omega*t);      //角度指令:ご自由に設定可能
		dThd = 0.3*omega*cos(omega*t);
		
		ddThref = ctrl(Thd, dThd, Thout, dThout, Kp, Kd);/* PD制御*/
		
		/*ノイズや外力など*/
		nf = 0.0;
		nv = 0.0;
		fexo = 0.0;

		/*
		ACS
		*/

		Iref = Jn/Ktn*ddThref;
		Iimp = Iref + Icmp; 
		T1 = Ktn*Iimp - Tl;

		dThout = dThout + T1 *Ts/Jn - nv;
		Thout = Thout + dThout*Ts;
		Tl = 0;//負荷トルク: ご自由に設定可能

		Tout  = D[0].DOB(Iref, dThout, Ktn, Jn, gdob, Ts);//外乱オブザーバ
		Icmp = Tout/Ktn;
		ddThout = F[0].DLPF(dThout, gpd, Ts);
		error = Thd -Thout;
		
		// Display results
		if(DisplayCount == 0 || DisplayCount == (int)(1/Ts)) {
			std::cout << "---------------- " << t << " s" << " ----------------" << std::endl; //時刻
			std::cout << "Theta response      : " << Thout      << std::endl; //角度応答
			std::cout << "Distarbance : " << Tout << std::endl;//外乱オブザーバで推定したトルク
			DisplayCount = 0;
		}
		DisplayCount++;
		// Output results
		fprintf(file , "%f %f %f %f %f %f\n", t, Thd, Thout,Tl,Tout, error); //時刻、角度指令、角度応答、負荷トルク、推定トルク、角度誤差

		t += Ts;

	}while(t<=tEND);

	std::cout << "=============== Finish ==============" << std::endl;

	fclose(file);
     
	//FILE *gp;　　グラフ出力（オフにしてます）
     //gp = popen("gnuplot -persist","w");
     //fprintf(gp,"set term qt font \"Times New Roman,11\"\n");
     //fprintf(gp, "set key outside center top horizontal reverse left\n" );
     //fprintf(gp, "set yrange [-1.0:1.0]\n" )     ;
     //fprintf(gp, "set ylabel \'Angle [rad]\'\n" );
     //fprintf(gp,"set xlabel \'Time [s]\'\n");
     //fprintf(gp, "plot 'DATA.dat' u 1:2 with lines lc rgb \'#000000\' lt 0 title 'Command',\'DATA.dat' u 1:3 with lines lc rgb \'#000000\' title 'Th_{out}',\'DATA.dat' u 1:4 with lines lc rgb \'#009600\' title 'error'\n");
     //fflush(gp);
     //pclose(gp);
     //
	return 0;
}
