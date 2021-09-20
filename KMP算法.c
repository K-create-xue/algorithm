#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void prefix_table(char pattern[], int prefix[], int n){
	prefix[0] = 0;
	int i = 1;
	int len = 0;
	while (i < n){
		if (pattern[i] == pattern[len]){
			prefix[i] = ++len;
			++i;
		}
		else{
			if (len>0){
				len = prefix[len - 1];
			}
			else{
				prefix[i] = len;
				++i;
			}
		}
	}
}

void move_prefix(int prefix[], int n){
	int i = n - 1;
	while (i-->1){
		prefix[i] = prefix[i - 1];
	}
	prefix[0] = -1;
}

void kmp_search(char test[], char pattern[]){
	int n = strlen(test);
	int m = strlen(pattern);
	int *prefix = (int*)malloc(sizeof(int)*n);
	prefix_table(pattern, prefix, m);
	move_prefix(prefix, n);
	int i = 0, j = 0;
	while (i < n){
		if (j == m - 1 && pattern[j] == test[i]){
			printf("Found pattern at %d\n", i - j);
			j = prefix[j];
		}
		if (test[i] == pattern[j]){
			++i;++j;	
		}
		else{
			j = prefix[j];
			if (j == -1)
				++j; ++i;
		}
	}
}
int main(){
	char test[] = "ABBACBDABDADFSADA";
	char pattern[] = "BDABDA";

	kmp_search(test, pattern);

	/*char pattern[] = "ABABCABAA";
	int prefix[9];
	int n = 9;

	prefix_table(pattern, prefix, n);
	for (int i = 0; i < n; ++i){
		printf("%d  ", prefix[i]);
	}*/
	return 0;
}
