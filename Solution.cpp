#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
#include<fstream>
#include<cstring>
using namespace std;
#define mx 501
#define nd 12
#define m(x,y) make_pair(x,y)
int getR(int RGB) { return (RGB >> 16) & 0xFF; }

int getG(int RGB) { return (RGB >> 8) & 0xFF; }

int getB(int RGB) { return RGB & 0xFF; }

int ar[mx][mx];
int dx[] = { 1,-1,0,0 };
int dy[] = { 0,0,1,-1 };

int component[mx][mx];
int sqr(int x) {
	return x*x;
}
double sqr(double x) {
	return x*x;
}
int dist(int x1, int y1, int x2, int y2) {
	int ret = sqr(getR(ar[x1][y1]) - getR(ar[x2][y2])) +
		sqr(getG(ar[x1][y1]) - getG(ar[x2][y2])) +
			sqr(getB(ar[x1][y1]) - getB(ar[x2][y2]));
	return ret;
}

void dfs(int x, int y, int &distFactor, int &n, int &m) {
	for (int i = 0;i < 4;++i) {
		int newX = x + dx[i], newY = y+dy[i];
		if (newX < 0 || newX >= n || newY < 0 || newY >= m)continue;
		if (component[newX][newY] == 0 && dist(x, y, newX, newY) <= distFactor)
		{
			component[newX][newY] = component[x][y];
			dfs(newX, newY,distFactor, n,m);
		}
	}
}

int floodfill(int n, int m, int distFactor) {
	for (int i = 0;i < n;++i)
		for (int j = 0;j < m;++j)
			component[i][j] = 0;
	int ret = 0;
	for (int i = 0;i < n;++i)
		for (int j = 0;j < m;++j)
			if (component[i][j] == 0) {
				ret++;
				component[i][j] = ret;
				dfs(i, j, distFactor,n,m);
			}
	return ret;
	}


int values[] = { 0,10,30,50,70,100,200, 300,500, 1000,3000,9000 };
int comps[] = { 0,10,30,50,70,100,200, 300,500, 1000,3000,9000 };

double prevectors[20][nd+5] = { 
{ 0.016357,0.290680,0.560619,0.827696,0.888334,0.879279,0.773867,0.860280,0.866196,0.830895,0.657610,0.492731 },
{ 0.000264,0.277900,0.286505,0.592293,0.822559,0.674847,0.414496,0.605809,0.569472,0.501718,0.434932,0.322835 },
{ 0.000047,0.504313,0.415760,0.675466,0.848903,0.745016,0.491315,0.630674,0.540152,0.302595,0.099652,0.104651 },
{ 0.000007,0.299564,0.399713,0.684369,0.820993,0.728511,0.480028,0.650044,0.559237,0.326299,0.089552,0.027778 },
{ 0.000252,0.774848,0.679276,0.793344,0.879353,0.810342,0.564383,0.688779,0.605368,0.416769,0.162525,0.053228 },
{ 0.000073,0.801958,0.664782,0.770173,0.841729,0.780023,0.513424,0.630882,0.530794,0.329756,0.104068,0.045603 },
{ 0.000137,0.896162,0.808319,0.863669,0.897584,0.856544,0.646277,0.726019,0.609007,0.391343,0.108817,0.023397 },
{ 0.000028,0.711009,0.597807,0.727529,0.822180,0.747548,0.468476,0.630398,0.546589,0.372415,0.117335,0.020576 },
{ 0.007478,0.984760,0.956999,0.961187,0.961672,0.947850,0.848193,0.871678,0.794697,0.639031,0.263778,0.091443 },
{ 0.010632,0.977827,0.951003,0.962100,0.965138,0.953769,0.864158,0.889128,0.824699,0.672813,0.308987,0.098003 },
{ 0.008023,0.960779,0.928833,0.949371,0.955651,0.943823,0.850152,0.879140,0.808907,0.649335,0.285557,0.093657 },
{ 0.019762,0.962352,0.934229,0.953713,0.964400,0.953679,0.873445,0.902469,0.850947,0.723003,0.395186,0.130755 },
{ 0.000006,0.445062,0.283166,0.435504,0.594727,0.487258,0.198895,0.331481,0.234637,0.166667,0.142857,1.000000 },
{ 0.000007,0.351858,0.273304,0.594471,0.668525,0.634960,0.324483,0.457364,0.333333,0.146893,0.038462,1.000000 },
{ 0.000006,0.387427,0.204141,0.532196,0.708724,0.619443,0.339394,0.519737,0.479204,0.245283,0.030769,0.500000 },
{ 0.000021,0.167026,0.315681,0.678317,0.757939,0.769368,0.553044,0.699954,0.631055,0.440589,0.140811,0.067797 } };

double V[100];
double cube(double x) {
	return x*x*x;
}
double dist(double A[], double B[]) {
	double ret = 0;
	for (int i = 0;i < nd ;++i)
		ret += sqr(A[i] - B[i]);
	//ret += sqr(A[0] - B[0] );
	return ret;
}
int classify(int n, int m) {
	double green = 0;
	double red = 0;
	double blue = 0;
	double all=0;
	double inv255 = 1.0 / double(255*255*255);
	for (int i = 0;i < n;++i)
		for (int j = 0;j < m;++j)
		{
			all+= ar[i][j]*inv255;

		}
	//cout << "Green = " << 100*green / double(n*m) <<"%\n"<< endl;

	//printf("\nComps:\n");
/*	int nd = 12;
	cout << "{";
	for (int i = 0;i < nd;++i) {
		comps[i] = floodfill(n, m, values[i]);
		V[i] = (i == 0 ? 1 : double(comps[i]) / double(comps[i - 1]));
	printf("%lf" ,(i==0?1: double(comps[i])/double(comps[i-1])));
	if (i !=nd -1) printf(",");
	}
	cout << "},";
	cout << endl;*/

	
	for (int i = 0;i < nd;++i) {
		comps[i] = floodfill(n, m, values[i]);
		V[i] = (i == 0 ? 1 : double(comps[i]) / double(comps[i - 1]));
	}
	//printf("%lf\n", double(comps[nd - 1]) / double(comps[0]));
	double dists[5] = { 0 };
	pair< double, int> P= m(1<<30,1);
	for (int i = 0;i < 16;++i) {
		//dists[i/4] += dist(V, prevectors[i]);
		P = min(P, m(dist(V, prevectors[i]), i / 4));
	}
	/*for (int i = 0;i < 4;++i)
		P = min(P, m(dists[i], i + 1));*/
	return P.second+1;
}

void debug_test() {
	char dummy[] = "style-6-8.in";
	for (int i = 1;i <= 4;++i) {
		dummy[6] = '0' + i;
		cout << "\nStyle "<<i<<":\n";
		for (int j = 0;j < 4;++j)
		{
			dummy[8] = j + '0';
			ifstream fin(dummy);
			int n, m;
			fin >> n >> m;
			for (int i = 0;i < n;++i)
				for (int j = 0;j < m;++j)
					fin >> ar[i][j];
			int C = classify(n, m);
			cout << j << " is classified as : " <<  C<< "\n\n";
			fin.close();
		}
	}
}

int main(){
	//debug_test();
	int t;
	scanf("%d", &t);
	while (t--) {
		int n, m;
		scanf("%d%d", &n, &m);
		for (int i = 0;i < n;++i)
			for (int j = 0;j < m;++j)
				scanf("%d", &ar[i][j]);
		printf("%d\n", classify(n, m));
	}
}
