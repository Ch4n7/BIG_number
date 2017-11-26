#include <stdio.h>
#include <string.h>

#define BASE 10
#define LEN 100
#define GAP 1	// security gap length

int readin(int n[]);
int writeout(int n[]);
int substract(int n1[], int len1, int n2[], int len2);

int
main()
{
	int	n1[LEN + GAP], len1,
		n2[LEN + GAP], len2;

	len1 = readin(n1);
	len2 = readin(n2);
	if (!substract(n1, len1, n2, len2))
		writeout(n1);
	else
		printf("Illegal!\n");

	return 0;
}

int
readin(int num[])
{
	char	str[LEN + GAP];
	int	i, length;

	memset(num, 0, sizeof(int) * (LEN + GAP));
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

// Compute n1 - n2, and return the result into n1.
// If n1 < n2, report error.
int
substract(int n1[], int len1, int n2[], int len2)
{
	int	i;
	
	if (len1 < len2)	// n1 < n2 #1
		return 1;

	for (i = 0; i < len1; i++) {
		n1[i] -= n2[i];
		if (n1[i] < 0) {
			n1[i] += BASE;
			n1[i+1]--;
		}
	}

	if (n1[len1] != 0)		// n1 < n2 #2 when len1 = lenn2
		return 1;

	return 0;
}

