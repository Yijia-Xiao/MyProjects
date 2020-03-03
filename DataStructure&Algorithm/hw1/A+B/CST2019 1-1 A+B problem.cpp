// Author Xiao Yijia
#include<cstdio>
#include<cstring>
#define M 100000000

// Declaring these global variables here, the worst case in 50% test is 40ms, much faster than 'new'
// For this reason, it is feasible to use some global variables to accelerate the program
char p[5005], q[5005];
long long a[630] = { 0 }, b[630] = { 0 };
long long carry[1260] = { 0 }, res[1300] = { 0 };
long long d1[5010] = { 0 }, d2[5010] = { 0 };
int power[8] = { 1, 10,100,1000,10000,100000,1000000,10000000 };

//Packaging the memset instructions as a inline function can make the codes more understandable
inline void reset();

int main() {
	int n;
	scanf("%d", &n);
	while (n--)
	{
		// read in the 2 numbers
		scanf("%s", p);
		scanf("%s", q);
		int l1 = 0, l2 = 0;
		int ctr1 = 0, ctr2 = 0;
		int num1 = 0, num2 = 0;

		// Here we need to think more carefully: if input is 0, then in codes below, we have p[l1 - i - 1]
		// and it will access invalid memory
		if(p[0] == '0' || q[0] == '0'){
			printf("0\n");
			continue;
		}
		// finding the lenth of 2 numbers
		while (p[l1] != '\0')
			l1++;
		while (q[l2] != '\0')
			l2++;

		// calculating how many long long are needed
		num1 = (l1 % 8 == 0 ? l1 / 8 : l1 / 8 + 1);
		num2 = (l2 % 8 == 0 ? l2 / 8 : l2 / 8 + 1);

		// converting the char to int
		for (int i = 0; i < l1; i++)
			d1[i] = p[l1 - i - 1] - '0';
		for (int i = 0; i < l2; i++)
			d2[i] = q[l2 - i - 1] - '0';

		// converting 8 'int' to 1 'long long'
		// using 'power' array to reverse the longlong
		for (int i = 0; i < num1; i++) {
			for (int ctr = 0; ctr < 8; ctr++) {
				a[i] += power[ctr] * d1[8 * i + ctr];
			}
		}
		for (int i = 0; i < num2; i++) {
			for (int ctr = 0; ctr < 8; ctr++) {
				b[i] += power[ctr] * d2[8 * i + ctr];
			}
		}
		
		// M2 is close to long_long_max(2 ^ 63), we can use this as a upper bound
		// if the res[i] is larger than M2, we need to carry the values forward
		const long long M2 = (long long)1e18;
		for(int i = 0; i < num1; i++)
			for(int j = 0; j < num2; j++)
			{
				res[i + j] += a[i] * b[j];
				if (res[i + j] > M2)
				{
					res[i + j + 1] += res[i + j] / M;
					res[i + j] %= M;
				}
			}

		// the final 'carry' after calculation (have been explained in report)
		for(int i = 0; i < num1 + num2 + 1 + 1; i++)
		{
			res[i + 1] += res[i] / M;
			res[i] %= M;
		}

		// finding the lwnth of res
		int pos = sizeof(res) / sizeof(long long) - 1;
		while (res[pos] == 0)
		{
			pos--;
		}
		printf("%lld", res[pos]);

		// complement the longlong less than 8 digits (using '0')
		for (int i = pos - 1; i >= 0; i--)
			printf("%08lld", res[i]);
		printf("\n");
		reset();
	}
	return 0;
}
inline void reset() {
	//using memset is faster
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	memset(d1, 0, sizeof(d1));
	memset(d2, 0, sizeof(d2));
	memset(carry, 0, sizeof(carry));
	memset(res, 0, sizeof(res));
}