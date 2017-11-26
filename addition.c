#include <stdio.h>
#include <string.h>

#define BASE 10
#define LEN 100
#define GAP 1	// security gap length

int readin(int n[]);
int writeout(int n[]);
int add(int n1[], int n2[]);

int
main()
{
	int	n1[LEN + GAP],
		n2[LEN + GAP];

	readin(n1);
	readin(n2);
	if (!add(n1, n2))
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

	return 0;
}

int
writeout(int num[])
{
	int	i;
	
	for (i = LEN - 1; i >= 0; i--)
		if (num[i] != 0) break;
	for (; i >= 0; i--)
		printf("%d", num[i]);
	putchar('\n');

	return 0;
}

// Compute n1 + n2, and return the result into n1.
int
add(int n1[], int n2[])
{
	int	i, carry;

	carry = 0;
	for (i = 0; i < LEN; i++) {
		n1[i] += n2[i] + carry;
		carry = n1[i] / BASE;
		n1[i] %= BASE;
	}

	if (carry != 0)		// overflows
		return 1;

	return 0;
}

