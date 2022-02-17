#include <iostream>
#include <math.h>


using namespace std;
double lamA = 0.2261;
double lamB = 0.2379;
double miuA = 4.1400;
double miuB = 3.0507;
double pA = lamA / (lamA + lamB);
double pB = lamB / (lamA + lamB);

double genExp(double lambda)
{
	double u, x;
	u = (double)rand() / (RAND_MAX + 1);
	x = -1 / lambda * log(1 - u);
	return x;
}

double genGauss(double medie, double sigma)
{
	double s = 0; int i;
	for (i = 1; i <= 12; i++)
		s += (double)rand() / RAND_MAX;
	return medie + sigma * (s - 6);
}

double genTr(void)
{
	double U, Tr;
	U = (double)rand() / RAND_MAX;
	if (U < pA)
	{
		Tr = genGauss(1 / miuA, 1 / (4 * miuA));
		//Tr = genExp(miuA);
	}
	else
	{
		Tr = genGauss(1 / miuB, 1 / (4 * miuB));
		//Tr = genExp(miuB);
	}
	return Tr;
}

int main()
{
	int S;
	cout << "S= ";
	cin >> S;
	double DS;
	double STf = 0;
	double STr = 0;
	double nf = S;
	double no = 0;
	double ceas = 0;
	double Tpo = genExp(S*(lamA + lamB));
	int NO = 1000000;
	int No = 0;
	int Nr = 0;
	double Tr;
	do
	{
		if (nf == S || nf > 0 && Tpo < Tr)
		{
			No++;
			ceas += Tpo;
			if (no > 0) Tr = Tr - Tpo;
			STf += nf * Tpo;
			nf--;
			no++;
			if (no == 1) {
				Tr = genTr();
				STr += Tr;
			}
		}

		else
		{
			Nr++;
			ceas += Tr;
			if (nf > 0) Tpo -= Tr;
			STf += nf * Tr;
			nf++;
			no--;
			if (no > 0)
			{
				Tr = genTr();
				STr += Tr;
			}
		}

		if (nf > 0) Tpo = genExp(nf * (lamA + lamB));

	} while (No < NO);
	DS = ceas;
	double D = STf / (DS * S) * 100;
	double O = STr / DS * 100;

	cout << "No = " << No << endl;
	cout << "Nr= " << Nr << endl;

	double Trm = (1 / (lamA + lamB)) * (lamA / miuA + lamB / miuB);
	cout << "Trm teoretic= " << Trm << endl;
	cout << "Trm calculat= " << STr / Nr << endl;

	cout << "D= " << D << endl;
	cout << "O= " << O << endl;

	double vf;

	vf = 1 / (1 + lamA / miuA + lamB / miuB) * 100;
	cout << "Verificare pentru S=";
	cout << S << endl;
	cout << "D=" << vf << endl;
	cout << "O=" << 100 - vf << endl;

	return 0;
}
