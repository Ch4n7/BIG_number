#include <stdio.h>
#include <string.h>

#define BASE 10
#define MAXLEN 200
#define GAP 1	// the length of security gap

int writeout(int n[], int len);
int factorial(int res[], int lt, int rt);
int substract(int res[], int n1[], int len1, int n2[], int len2);
int divide(int res[], int n1[], int len1, int n2[], int len2);

int
main()
{
	int	cn, cx,
		n1[MAXLEN + GAP], len1,
		n2[MAXLEN + GAP], len2,
		result[MAXLEN * 2 + GAP], len;

	memset(n1, 0, sizeof(n1));
	memset(n2, 0, sizeof(n2));
	memset(result, 0, sizeof(result));
	printf("C - n:");
	scanf("%d", &cn);
	printf("C - x:");
	scanf("%d", &cx);
	len1 = factorial(n1, cn, cn - cx + 1);
	len2 = factorial(n2, cx, 1);
	len = divide(result, n1, len1, n2, len2);
	printf(" (%d)\n", writeout(result, len));

	return 0;
}

int writeout(int num[], int len)
{
	int	l, i;

	for (i = len - 1; i > 0 && num[i] == 0; --i);
	l = i + 1;
	for (; i >= 0; --i)
		printf("%d", num[i]);

	return l;	// return the length of the number that is printed.
}

int
factorial(int res[], int left, int right)
{
	int	i, j, carry;

	if (left < right)
		return -1;

	res[0] = 1;
	for (i = right; i <= left; ++i) {
		carry = 0;
		for (j = 0; j < MAXLEN; ++j) {
			res[j] = res[j] * i + carry;
			carry = res[j] / BASE;
			res[j] = res[j] % BASE;
		}
	}

	for (i = MAXLEN - 1; i > 0 && res[i] == 0; --i);
	return (i + 1); // return the length of the result
}

int
substract(int res[], int n1[], int len1, int n2[], int len2)
{	
	int	i;

	if (len1 < len2)
		return -1;	// n1 < n2  case#1
	else if (len1 == len2) {
		for (i = len1; i > 0 && n1[i] == n2[i]; --i);
		if (n1[i] < n2[i])
			return -1; // n1 < n2  case#2
	}

	for (i = 0; i < len1; i++) {
		res[i] = n1[i] - n2[i];
		if (res[i] < 0) {
			res[i] += BASE;
			res[i + 1]--;
		}
	}

	for (i = len1 - 1; i > 0 && res[i] == 0; --i);
	return (i + 1); // return the length of result
}

int
divide(int res[], int n1[], int len1, int n2[], int len2)
{
	int	diff, i, tmp;

	diff = len1 - len2;
	if (diff < 0)
		return -1;

	for (i = len1 - 1; i >= diff; --i)
		n2[i] = n2[i - diff];
	for (; i >= 0; --i)
		n2[i] = 0;

	len2 = len1;
	for (i = 0; i <= diff; ++i) {
		while ((tmp = substract(n1, n1, len1, n2 + i, len2 - i)) >= 0) {
			res[diff - i]++;
			len1 = tmp;
		}
	}

	for (i = len2; i > 0 && res[i] == 0; --i);

	return (i + 1);
}
