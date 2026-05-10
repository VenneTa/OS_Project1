#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
/*
The fuctionality of this is to take in text from a source and to reverse it. Then returning it to some target.
Input can come from command line or text file. Target can be or text file.
With 0 extra parameters the input is command line and target is command line.
With 1 extra parameter the input is the parameter (text file) and the target is command line.
With 2 extra parameters the input is the first parameter (text file) and the target is the second parameter (text file).
*/
int main(int argc, char *argv[]){
  // If more than 2 extra parameters given, prints error
  if(argc > 3){
    fprintf(stderr, "usage: reverse <input> <output>\n");
    exit(1);
  }

  // If input is the same as output, error
  if(argc == 3){
    if(strcmp(argv[1], argv[2]) == 0){
      fprintf(stderr,"Input and output files must differ");
      exit(1);
    }
  }

  // Input file or stdin
  FILE *fileIn;

  // If no additional parameters then reads lines from stdin.
  if(argc == 1){
    fileIn = stdin;
  }

  // If additional parameters opens input file
  if(argc > 1){
    fileIn = fopen(argv[1],"r");
    if(fileIn == NULL){
      fprintf(stderr, "error: cannot open file %s\n", argv[1]);
      exit(1);
    }
  }


  // Reading the file
  char *line = NULL;
  char **lines = NULL;
  ssize_t read;
  size_t len = 0;
  int lineCount = 0;
  
  // Going over all lines and collecting them to array
  while((read = getline(&line,&len,fileIn)) != -1){
    char *copyLine = malloc(read+1); // Memory reserve

    // malloc failure check
    if(!copyLine){
      fprintf(stderr, "malloc failed\n");
      exit(1);
    }
    strcpy(copyLine,line); // Copies the line

    // realloc to a temp, utilized to extend array
    char **temp = realloc(lines, (lineCount+1)*sizeof(char *));
    if(!temp){
      free(copyLine);
      for(int i = 0; i<lineCount; i++){
        free(lines[i]);
      }
      free(lines);
      fprintf(stderr, "realloc failed\n");
      exit(1);
    }
    lines = temp;
    lines[lineCount] = copyLine;
    lineCount++;
  }
  if(argc != 1){
    fclose(fileIn);
  }
  free(line);

  // If belove 3 arguments given, then results are printed to stdout
  if(argc == 1 || argc == 2){
    for(int i = lineCount-1; i>=0; i--){
      fprintf(stdout, "%s", lines[i]);
    }
  }

  // If 3 arguments givem, results printed to specified output file
  if(argc == 3){
    // Opening the output file
    FILE *fileOut = fopen(argv[2],"w");
    if(fileOut == NULL){
      fprintf(stderr, "error: cannot open file %s \n", argv[2]);
      // Freeing the lines from dynamic memory, in case problem:
      for(int i = 0; i<lineCount; i++){
        free(lines[i]);
      }
      free(lines);
      exit(1);
    }
    
    // Outputting text in reverse order
    for(int i = lineCount-1; i>=0; i--){
      fprintf(fileOut, "%s", lines[i]);
    }
    fclose(fileOut);
  }

  // Freeing the remaining malloc memory
  for(int i = 0; i<lineCount; i++){
    free(lines[i]);
  }
  free(lines);

  exit(0);
}

