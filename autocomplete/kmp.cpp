#include <iostream>
#include <cstring>

// Fills lps[] for given pattern pat[0..M-1]
void computeLPSArray(char* pat, int M, int* lps)
{
	int i = 1, j = 0;
	lps[0] = -1;
	while(i<M){
		if(pat[i] != pat[j]){
			lps[i] = j;
			while(j>=0 && pat[j] != pat[i]){
				j = lps[j];
			}
		}
		else{
			lps[i] = lps[j];
		}
		i++; j++;
	}

	lps[M] = j;
}

// Prints occurrences of txt[] in pat[]
void KMPSearch(char* pat, char* txt)
{
	// printf("Found pattern at index %d \n", index_where_found);

	int pat_max = 0, txt_max = 0;
	for(int i=0; pat[i] != '\0'; i++){
		pat_max++;
	}
	for(int i=0; txt[i] != '\0'; i++){
		txt_max++;
	}
	int i=0, j=0;
	int* lps = new int[pat_max+1];
	computeLPSArray(pat, pat_max, lps);
	while(i<txt_max){
		if(pat[j] == txt[i]){
			i++;j++;
			if(j == pat_max){
				printf("Found pattern at index %d \n", i-j);
				j = lps[j];
			}
		}
		else{
			j = lps[j];
			if(j < 0){
				j++;i++;
			}
		}
	}
	delete[] lps;
}
