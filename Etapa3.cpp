#include<iostream>
#include<math.h>
using namespace std;
#define F 1
#define O 0
#define A 0
#define B 1

double lamA = 0.2261;
double lamB = 0.2379;
double miuA = 4.1400;
double miuB = 3.0507;

double rapA = lamA / miuA, rapB = lamB / miuB;
double pA = 0;
double DS = 1000000 / (lamA + lamB);

double genExp(double lambda)
{
	double u = (double)rand() / (RAND_MAX + 1);
	return(-log(1 - u) / lambda);
}

double genTr(int mr) {
	double x;
	if (mr == A)
		x = genExp(miuA);
	else
		x = genExp(miuB);
	return x;
}
int minTf(double Tf[19], int st[19], int S) {
	double min = Tf[1];
	int s = 1;
	for (int i = 1; i <= S; i++) {
		if (min > Tf[i] && st[i] == F) {
			min = Tf[i];
			s = i;
		}
	}
	return s;
}
int modulDefect(int sd, int nmf[2][20])
{
	double u;

	u = (double)rand() / (RAND_MAX + 1);
	pA = lamA / (lamA + lamB);
	if (u < pA)
		return A;
	else
		return B;
}
int main()
{
	int S = 1;
	int st[20], nmf[2][20], nf, nmd;
	int sd, md;
	int sr, mr;
	double Tf[20];
	double STf, STr;
	double Tpd, Tr = 0;
	double Trm;
	double ceas;
	double D = 0, Oc = 0;
	do {
		STf = 0; STr = 0;
		ceas = 0;
		nf = S;
		nmd = 0;
		for (int i = 1; i <= S; ++i)
		{
			nmf[A][i] = 1;
			nmf[B][i] = 2;
			Tf[i] = genExp(lamA + lamB);
			st[i] = F;
		}
		do {
			if (nf > 0)
			{
				int j;
				for (j = 1; j <= S; j++)
				{
					if (st[j] == F)
					{
						break;
					}
				}
				Tpd = Tf[j];
				sd = j;
				for (int i = 1; i <= S; i++)
				{
					if (Tf[i] < Tpd && st[i] == F)
					{
						Tpd = Tf[i];
						sd = i;
					}
				}
			}
			md = modulDefect(sd, nmf);
			if (nmd == 0 || (nf > 0 && Tpd < Tr)) {
				ceas += Tpd;
				if (nmd > 0)
					Tr -= Tpd;
				for (int i = 1; i <= S; i++)
				{
					if (st[i] == F)
						Tf[i] -= Tpd;
				}
				STf += (nf*Tpd);
				nmf[md][sd]--;
				nmd++;
				if (nmf[md][sd] >= 1)
				{
					Tf[sd] = genExp(lamA + lamB);
				}
				else if (nmf[md][sd] == 0)
				{
					st[sd] = O;
					nf--;
				}
				if (nmd == 1 || (st[sr] == F && st[sd] == O) || (sd == sr && md == A))
				{
					sr = sd;
					mr = md;
					if (nmd > 1)
						STr -= Tr;
					Tr = genTr(mr);
					STr += Tr;
				}
			}
			else {
				ceas += Tr;
				for (int i = 1; i <= S; i++)
				{
					if (st[i] == F)
						Tf[i] -= Tr;
				}
				STf += (nf*Tr);
				nmf[mr][sr]++;
				nmd--;
				if (nmf[A][sr] >= 1 && nmf[B][sr] >= 1 && st[sr] == 0) {
					st[sr] = F;
					nf++;
					Tf[sr] = genExp(lamA + lamB);
				}

				if (nmd > 0)
				{
					int j = 1;
					for (int i = 1; i <= S; i++)
					{
						if (st[i] == O)

						{
							if (nmf[B][i] == 0)
							{
								sr = i;
								mr = B;
								break;
							}
							else if (nmf[A][i] == 0)
							{
								sr = i;
								mr = A;
								j = 0;
								break;
							}
						}
						else if (j && nmf[A][i] == 1 && nmf[B][i] == 1)
						{
							sr = i;
							mr = B;
							break;
						}
					}
					Tr = genTr(mr);
					STr += Tr;
				}
			}
		} while (ceas < DS);
		D = STf / (S*DS) * 100;
		Oc = STr / DS * 100;
		cout << "S = " << S << endl;
		cout << "\t D= " << D << "% \n\t O= " << Oc << "%" << endl;
		++S;
	} while (Oc < 90.0);
	return 0;
}

