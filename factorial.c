#include <stdio.h>
#include <string.h>

#define MAXN 3000

int
main()
{
	int	big_decimal[MAXN];
	int	n, carry, tempn;
	int	i, j;

	memset(big_decimal, 0, sizeof(big_decimal));
	big_decimal[0] = 1;
	scanf("%d", &n);
	// imitation of hand-computing
	for (i = 2; i <= n; i++) {
		carry = 0;
		for (j = 0; j < MAXN; j++) {
			tempn = big_decimal[j] * i + carry;
			carry = tempn / 10;
			big_decimal[j] = tempn % 10;
		}
	}

	for (j = MAXN - 1; j >= 0; j--) if (big_decimal[j]) break; // ignore the leading zeros
	printf("%d digits:\n", j);
	for (; j >=0; j--) printf("%d", big_decimal[j]);
	putchar('\n');

	return 0;
}
