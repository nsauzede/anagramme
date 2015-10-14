#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define LMAX 1024
char *lfirst[LMAX];
int nfirst = 0;

int main( int argc, char *argv[])
{
#define MAX 1024
	char buf[MAX], buf2[MAX] = "";
	char *first = 0;
	char *last = 0;
	int i;
	if (argc > 2)
	{
		first = argv[1];
		last = argv[2];
	}
	if (!first || !last)
		exit( 1);
	FILE *in = fopen( "first.txt", "rt");
	while (!feof( in))
	{
		fgets( buf, sizeof( buf), in);
		int len = strlen( buf);
		for (i = 0; i < len; i++)
		{
			if (isupper( buf[i]))
				buf[i] |= ' ';
		}
		if (!strcmp( buf, buf2))
			continue;
		sprintf( buf2, "invalid");
		if (sscanf( buf, "%s", buf2) == 1)
		{
			if (buf2[0] == '#')
				continue;
			if (!strcmp( buf2, "theend"))
				break;
			lfirst[nfirst++] = strdup( buf2);
		}
	}
	fclose( in);
	printf( "nfirst=%d\n", nfirst);
	snprintf( buf, sizeof( buf), "%s%s", first, last);
	printf( "finding anagrams for '%s %s'...\n", first, last);
//	printf( "buf=[%s]...\n", buf);
	for (i = 0; i < nfirst; i++)
	{
		if (!strcmp( first, lfirst[i]))
			continue;
		int len = strlen( lfirst[i]);
//		printf( "i=%d first=[%s] len=%d\n", i, lfirst[i], len);
		int j;
		strcpy( buf2, buf);
		for (j = 0; j < len; j++)
		{
			char *p = strchr( buf2, lfirst[i][j]);
			if (!p)
			{
//				printf( "can't find %c\n", lfirst[i][j]);
				break;
			}
			else
			{
				int len2 = strlen( p);
				int k;
				for (k = 0; k < len2; k++)
				{
					p[k] = p[k + 1];
				}
//				printf( "buf2=[%s]\n", buf2);
			}
		}
		if (j == len)
		{
			printf( "%s : [%s]\n", lfirst[i], buf2);
		}
	}
	
	return 0;
}
