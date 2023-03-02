//“As a Hokie, I will conduct myself with honor and integrity at all times.
// I will not lie, cheat, or steal, nor will I accept the actions of those who do.”
// Zachary Blocher zblocher 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zipData.h"

int main(int argc, char *argv[])
{
    
    if ( argc != 3 )
	{
		fprintf(stderr, "Usage: vectors <input-file> <output-file>\n");
		exit(1);
	}
    // open the input file to read
    printf("Before files\n");
    FILE* in = fopen(argv[1], "r");
    // create 
    FILE* out = fopen(argv[2], "w");
    printf("after files\n");

    // create variables for the passed through filter
    char command[200];
    char FileName[101];
    char countyCheck[101];
    char placeCheck[181];
    char post1[20], post2[20];
    char postalCheck[20];
    printf("before while\n");
    
    
    // get the first command
    fscanf(in, "%s", command);
    //loop until the file is empty
    while ( !feof(in) )
    {
        //printf("start of while\n");
        fgetc(in);
        printf("New command is:%s\n", command);
        // check each new line for the new command 
        // check if command is filename
        if ( strcmp(command, "filename") == 0)
        {
            
            fscanf(in, "%[^\n]", FileName);
            fgetc(in);
            fprintf(out, "filename %s\n", FileName);
        }  
        // check if command is county
        else if ( strcmp(command, "county") == 0)
        {
            
            fscanf(in, "%[^\n]", countyCheck);
            fgetc(in);
            //printf("running county name\n");
            county(FileName, countyCheck, out);
        }
        // check if command is place
        else if ( strcmp(command, "place") == 0)
        {
            fscanf(in, "%[^\n]", placeCheck);
            fgetc(in);
            //printf("before calling place\n");
            place(FileName, placeCheck, out);

        }
        // check if command is distance
        else if ( strcmp(command, "distance") == 0)
        {
            fscanf(in, "%s", post1);
            fgetc(in);
            fscanf(in, "%[^\n]", post2);
            fgetc(in);
            printf("running distance |%s| |%s|\n", post1, post2);
            distance(FileName, post1,post2,out);
        }
        // check if command is postal
        else if( strcmp(command, "postal") == 0)
        {
            fscanf(in, "%[^\n]", postalCheck);
            fgetc(in);
            postal(FileName, postalCheck ,out);
        }
        fscanf(in,"%s", command);
    }
    // close the input and ouotput files
    fclose(in);
    fclose(out);
    return 0;
}