#include "iostream"
#include "math.h"

using namespace std;

float tabel_gain[33] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

void hitung_tabel(float treshold, int ratio)
{
	int gain_point = -90;
	float sinyal_out, penurunan_sinyal, gain_linier;
	// ulangi dari -90 dB sampai +6 dB
	for(int step=0; step<33; step++)
	{	
		// jika dibawah treshold
		if(gain_point <= treshold)
		{
			tabel_gain[step] = 1.0;
		}
		// jika diatas treshold
		else
		{
			// hitung output sinyal setelah dikompres
			sinyal_out = treshold + ((gain_point - treshold) / (float) ratio ); 
			// hitung penurunan sinyal sebelum dan sesudah dikompres
			penurunan_sinyal = sinyal_out - gain_point; 
			// hitung gain linier untuk dimasukkan ke ram
			gain_linier = pow( 10, (penurunan_sinyal / 20));
			// masukkan ke tabel
			tabel_gain[step] = gain_linier;
		}
		// nilai titik gain selanjutnya
		gain_point += 3;
	}
}

float hitung_attack(float waktu)
{
	// ubah dari ms ke dbps
	float dbps = 8685 / waktu;
	// hitung nilai untuk dimasukkan ke ram
	float nilai = fabs(1.0 - pow( 10, (dbps / 480000)));
	return nilai;
}

float hitung_hold(float waktu)
{
	// hitung nilai untuk dimasukkan ke ram
	float nilai = (48000 * waktu / 1000 ) * pow(2, -23);
	return nilai;
}

float hitung_release(float waktu)
{
	// ubah dari ms ke dbps
	float dbps = 8685 / waktu;
	// hitung nilai untuk dimasukkan ke ram
	float nilai = dbps / (96 * 48000);
	return nilai;
}

int main()
{ 
	// tidak ada apa apa disini
}
