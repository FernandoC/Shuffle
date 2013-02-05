/*************************************************************************
*  Author: Fernando Carrillo (fcarril1)
*  Assignment: pa2
*  Filename: Shuffle.c
*  Class: CMPS 101 Patrick Tantalo
*
*  Description: The Shuffle program reads in permutations
*     from a file. It then makes a default list and applies 
*     the permutations to it. It repeats this process until it
*     reverts back to its default state and prints out how many
*     iterations it took to do so. 
***********************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 250

void Shuffle(ListRef L, ListRef P){
   int i, posTo, offset, moveData;
   moveTo(P, 0);
   moveTo(L, 0);
   offset = getLength(L);
   while (!offEnd(P)){
      posTo = getCurrent(P);
      moveData = getFront(L);
      moveTo(L, offset-1);
      for(i = 1; i < posTo; i++){
         moveNext(L);
      }
      insertAfterCurrent(L, moveData);
      deleteFront(L);
      offset--;
      moveNext(P);
   }
}

int main(int argc, char * argv[]){

   int n=0, order=0, count=0;
   FILE *in, *out;
   char line[MAX_LEN];
   char tokenlist[MAX_LEN];
   char* token;

   /* check command line for correct number of arguments */
   if( argc != 3 ){
      printf("Usage: %s infile outfile\n", argv[0]);
      exit(1);
   }

   /* open files for reading and writing */
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   ListRef P = newList();
   ListRef L = newList();
   ListRef Lkey = newList();

   /* Gets number of permutations in the file via the first line */
   fgets(line, MAX_LEN, in);
   token = strtok(line, " \n");
   n = atoi(&token[0]);

   for( n=n; n > 0; n--){
      fgets(line, MAX_LEN, in);
      strcat(line, " ");
      token = strtok(line, " \n");
      tokenlist[0] = '\0';

      /* Iterates though a single permutation and insert every token into List P
         While generating a new List depending on how long P is. */
      count = 0;
      while ( token!=NULL ){
         count++;
         insertBack(P, atoi(token));
         insertBack(L, count);
         insertBack(Lkey, count);
         token = strtok(NULL, " \n");
      }

      Shuffle(L, P);
      order = 1;

      /*Prints out List L after one Permutation */
      printList(out, L);

      /*Shuffles until list L is back to its original state and prints order*/ 
      while(equals(L, Lkey) == 0){
         order++;
         Shuffle(L, P);
      }
      fprintf(out, " order=%d", order);
      fprintf(out, "\n");

      /* Empties out permutation generated List and keyList*/
      makeEmpty(L);
      makeEmpty(P);
      makeEmpty(Lkey);
   }

   /* free memory */
   freeList(&L);
   freeList(&P);
   freeList(&Lkey);

   /* close files */
   fclose(in);
   fclose(out);

   return(0);
}
