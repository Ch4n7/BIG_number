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
		n2[LEN + GAP], len2,
		result[LEN + GAP], tmplen;
	int	i, j, diff;

	memset(n1, 0, sizeof(n1));
	memset(n2, 0, sizeof(n2));
	memset(result, 0, sizeof(result));
	len1 = readin(n1);
	len2 = readin(n2);
	diff = len1 - len2;
	if (diff < 0) {
		printf("Illegal!\n");
		return -1;
	} if (diff > 0) {
		// extend the n2 ab..c -> ab..c0..0, 
		// after this extension, len1 == len2
		for (i = len1 - 1; i >= diff; i--)
			n2[i] = n2[i - diff];
		for (; i >= 0; i--)
			n2[i] = 0;
	}

	len2 = len1;
	for (i = 0; i <= diff; i++) {
		while ((tmplen = substract(n1, len1, n2 + i, len2 - i)) >= 0) {
			result[diff - i]++;
			len1 = tmplen;
		}
	}

	writeout(result);

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

// Compute n1 - n2, and save the result into n1, return the length of result
// If n1 < n2, return non-zero.
int
substract(int n1[], int len1, int n2[], int len2)
{
	int	i;
	
	if (len1 < len2)	// n1 < n2 #1
		return -1;
	else if (len1 == len2) {	// n1 < n2 #2
		i = len1;
		while (i > 0 && n1[i] == n2[i]) i--;
		if (n1[i] < n2[i]) 
			return -1;
	}

	for (i = 0; i < len1; i++) {
		n1[i] -= n2[i];
		if (n1[i] < 0) {
			n1[i] += BASE;
			n1[i+1]--;
		}
	}

	for (i = len1 - 1; i >= 0; i--)
		if (n1[i] > 0) break;
	return (i + 1);	// return the length
}

