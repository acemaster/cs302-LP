/*
let the input be a string S consisting of n characters: a1 ... an.
let the grammar contain r nonterminal symbols R1 ... Rr.
This grammar contains the subset Rs which is the set of start symbols.
let P[n,n,r] be an array of booleans. Initialize all elements of P to false.
for each i = 1 to n
  for each unit production Rj -> ai
    set P[1,i,j] = true
for each i = 2 to n -- Length of span
  for each j = 1 to n-i+1 -- Start of span
    for each k = 1 to i-1 -- Partition of span
      for each production RA -> RB RC
        if P[k,j,B] and P[i-k,j+k,C] then set P[i,j,A] = true
if any of P[n,1,x] is true (x is iterated over the set s, where s are all the indices for Rs) then
  S is member of language
else
  S is not member of language
*/



#include <iostream>

//productions will be of the Chomsky normal form r->a or r->r1r2 


int main(){
	char grammar[100];
	char nts[100];
	char unitproductions[100][100];
	char normalproductions[100][100];
	printf("Please enter the number of characters in grammar\n");
	int ngrammar;
	scanf("%d",&ngrammar);
	for (int i = 0; i < ngrammar; ++i)
	{
		scanf("%c",&grammar[i]);
	}
	printf("Please enter the number of non terminal symbols\n");
	int nnts;
	scanf("%d",&nnts);
	for (int i = 0; i < nnts; ++i)
	{
		scanf("%c",&nts[i]);
	}
	printf("Set the unit productions: \n");
	char a,b;
	printf("R->a form: \n");
	while(1){
		scanf("%c",a);
	}


}


