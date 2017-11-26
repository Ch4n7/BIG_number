#include <stdio.h>
#include <string.h>

#define BASE 10
#define LEN 100
#define GAP 1	// security gap length

int readin(int n[]);
int writeout(int n[]);
int multiply(int res[], int n1[], int len1, int n2[], int len2);

int
main()
{
	int	n1[LEN + GAP], len1,
		n2[LEN + GAP], len2,
		result[LEN * 2 + GAP];

	memset(n1, 0, sizeof(n1));
	memset(n2, 0, sizeof(n2));
	memset(result, 0, sizeof(result));
	len1 = readin(n1);
	len2 = readin(n2);
	if (!multiply(result, n1, len1, n2, len2))
		writeout(result);
	else
		printf("Illegal!\n");

	return 0;
}

int
readin(int num[])
{
	char	str[LEN + GAP];
	int	i, length;

	fgets(str, LEN + 1, stdin);
	length = strlen(str) - 1;	// not count the NEWLINE
	for (i = 0; i < length; i++)
		num[i] = str[length - 1 - i] - '0';	

	return length;
}

int
writeout(int num[])
{
	int	i;
	
	for (i = LEN - 1; i >= 0; i--)
		if (num[i] != 0) break;
	if (i < 0)	// num[] contains all 0
		printf("%d", 0);
	for (; i >= 0; i--)
		printf("%d", num[i]);
	putchar('\n');

	return 0;
}

// Compute n1 x n2, and return the result into n1.
// If overflows, report error.
int
multiply(int res[], int n1[], int len1, int n2[], int len2)
{
	int	i, j;
	
	for (i = 0; i < len1; i++) {
		for (j = 0; j < len2; j++) {
			res[i + j] += n1[i] * n2[j];
		}
	}
	for (i = 0; i < LEN * 2; i++) {
		res[i+1] += res[i] / BASE;
		res[i] %= BASE;
	}

	return 0;
}

