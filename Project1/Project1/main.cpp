#define     MAX_RGN_BUFF    256
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdint.h>

/*
 * [Description] : random (a0, ..., an) 까지의 constant를 결정한다.
 */
char* RGN_CONSTANT()
{
	static char RGN_Array[MAX_RGN_BUFF];
	int            i = 0;

	memset(RGN_Array, 0x00, sizeof(RGN_Array));
	srand(time(NULL));

	/* random constant 값이 0값이 되지 않도록 마지막에 1을 더한다. */
	for (i = 0; i < MAX_RGN_BUFF; i++)
		RGN_Array[i] = (rand() % (MAX_RGN_BUFF - 1) + 1);

	return RGN_Array;
}

/*
 * [Description] : universal hash 함수
 * @param1 : char* k 데이터 k 값(문자열)
 * @param2 : int m m modulo 값
 * @param3 : char* RGN random constant 값
 */
int hash_universal(const char* k, int m, char* RGN)
{
	int         hash_key;
	int         len = 0;
	int         i = 0;
	uint64_t    sum = 0;

	/* m 값은 k0, ... kn이 가질수 있는 최대값보다 큰 값을 결정한다. */
	if (m <= MAX_RGN_BUFF)
	{
		printf("hash_universal:m must be bigger than %d\n", MAX_RGN_BUFF);
		return -1;
	}

	/* m 값은 소수(prime number)가 되도록 결정한다. */
	for (i = 2; i < m; i++)
	{
		if (!(m% i))
		{
			printf("hash_universal:m is not prime number\n");
			return -1;
		}
	}

	len = strlen(k);
	for (i = 0; i < len; i++)
		sum += ((int)pow(k[i], (len - i - 1)) % m * RGN[i]);
	hash_key = sum % m;
	printf("%d\n", hash_key);
	return hash_key;
}

int main()
{
	char* rgn_const = NULL;
	
	for (int i = 0; i < 100; i++)
	{
		rgn_const = RGN_CONSTANT();

		hash_universal("g32ry5wtgwerg", 257, rgn_const);
		hash_universal("5sfdhygh34g33g", 257, rgn_const);
		hash_universal("xbyjerhregreg", 257, rgn_const);
		hash_universal("ey3f65uhys", 257, rgn_const);
		hash_universal("batuqwmuq04", 257, rgn_const);
		hash_universal("09q74tsadlkhg", 257, rgn_const);
		hash_universal("gj9q4sdfghj", 257, rgn_const);

		printf("\n");
	}
	return 1;
}
