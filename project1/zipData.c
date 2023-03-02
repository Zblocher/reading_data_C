#include <stdio.h>
#include <string.h>
#include "zipData.h"
#include <math.h>
// create the function to read in the function
void read_record(FILE *in, double *latitude, double *longitude,char COUNTRY_CODE[], char POSTAL_CODE[],
char PLACE_NAME[],char ADMIN1[],char ADMIN_CODE1[],char ADMIN2[],char ADMIN_CODE2[], char ADMIN3[],char ADMIN_CODE3[],char accuracy[])
{
    // initialize all variables as null in case of missing variables
    COUNTRY_CODE[0] ='\0';
    POSTAL_CODE[0] = '\0';
    PLACE_NAME[0] = '\0';
    ADMIN1[0] = '\0';
    ADMIN_CODE1[0] = '\0';
    ADMIN2[0] = '\0';
    ADMIN_CODE2[0] = '\0';
    ADMIN3[0] = '\0';
    ADMIN_CODE3[0] = '\0';
    accuracy[0] = '\0';
    // read in all the data 
    fscanf(in, "%[^\t]", COUNTRY_CODE);
    // skip the space between
    fgetc(in);
    fscanf(in, "%[^\t]", POSTAL_CODE);
    fgetc(in);
    fscanf(in, "%[^\t]",PLACE_NAME);
    fgetc(in);
    fscanf(in, "%[^\t]", ADMIN1);
    fgetc(in);
    fscanf(in, "%[^\t]", ADMIN_CODE1);
    fgetc(in);
    fscanf(in, "%[^\t]", ADMIN2);
    fgetc(in);
    fscanf(in, "%[^\t]", ADMIN_CODE2);
    fgetc(in);
    fscanf(in, "%[^\t]", ADMIN3);
    fgetc(in);
    fscanf(in, "%[^\t]", ADMIN_CODE3);
    fgetc(in);
    fscanf(in, "%lf", latitude);
    fscanf(in, "%lf", longitude);
    fgetc(in);
    fscanf(in, "%[^\n]",accuracy); 
    fgetc(in);
}

void print_record(FILE *out, double latitude, double longitude,char COUNTRY_CODE[], char POSTAL_CODE[],
char PLACE_NAME[],char ADMIN1[],char ADMIN_CODE1[],char ADMIN2[],char ADMIN_CODE2[], char ADMIN3[],char ADMIN_CODE3[],char accuracy[])
{
    // print out all of the data and start a new line at the end 
    fprintf(out, "%s\t", COUNTRY_CODE);
    fprintf(out, "%s\t", POSTAL_CODE);
    fprintf(out, "%s\t", PLACE_NAME);
    fprintf(out, "%s\t", ADMIN1);
    fprintf(out, "%s\t", ADMIN_CODE1);
    fprintf(out, "%s\t", ADMIN2);
    fprintf(out, "%s\t", ADMIN_CODE2);
    fprintf(out, "%s\t", ADMIN3);
    fprintf(out, "%s\t", ADMIN_CODE3);
    fprintf(out, "%f\t", latitude);
    fprintf(out, "%f\t", longitude);
    fprintf(out, "%s\n", accuracy);
}

// create postal function
void postal(char FileName[], char postFilter[], FILE* out)
{
    // intiliaze all parameters as null incase of missing data
    char COUNTRY_CODE[3] = "";
    char POSTAL_CODE[21] = "";
    char PLACE_NAME[181] = "";
    char ADMIN1[101] = "";
    char ADMIN_CODE1[21] = "";
    char ADMIN2[101] = "";
    char ADMIN_CODE2[21] = "";
    char ADMIN3[101];
    char ADMIN_CODE3[21] = "";
    double latitude = 0;
    double longitude = 0;
    char accuracy[2] = "";
    int error_count = 0;
    
    FILE *in = fopen(FileName, "r");
    fprintf(out,"postal %s\n",postFilter);
    // loop through the file
    while ( !feof(in) )
    {
        //get the line of data 
        read_record(in,  &latitude,  &longitude, COUNTRY_CODE,  POSTAL_CODE,
                PLACE_NAME, ADMIN1, ADMIN_CODE1, ADMIN2, ADMIN_CODE2,  ADMIN3, ADMIN_CODE3, accuracy);
        // check if the postal code is the same 
        if ( strcmp(POSTAL_CODE, postFilter) == 0)
        {   
            // indent the line of data
            fprintf(out,"\t");
            // print the found postal codes data
            print_record(out, latitude, longitude, COUNTRY_CODE, POSTAL_CODE,PLACE_NAME, ADMIN1, ADMIN_CODE1, ADMIN2, ADMIN_CODE2, ADMIN3, ADMIN_CODE3, accuracy);
            error_count++;
        }
        
    }
    // if no postal code found write error message
    if(error_count < 1)
    {
        fprintf(out,"Sorry, postal code %s was not found.\n", postFilter);
    }
    
}
// create county function
void county(char FileName[], char countyFilter[], FILE* out)
{
    // intitialize parameters to null incase of missing information
    char COUNTRY_CODE[3] = "";
    char POSTAL_CODE[21] = "";
    char PLACE_NAME[181] = "";
    char ADMIN1[101] = "";
    char ADMIN_CODE1[21] = "";
    char ADMIN2[101] = "";
    char ADMIN_CODE2[21] = "";
    char ADMIN3[101];
    char ADMIN_CODE3[21] = "";
    double latitude = 0;
    double longitude = 0;
    char accuracy[2] = "";
    int error_count = 0;
    FILE *in = fopen(FileName, "r");
    //printf("running county\n");
    fprintf(out,"county %s\n",countyFilter);
    while ( !feof(in) )
    {
        //call the read_record function to get the line of information   
        read_record(in,  &latitude,  &longitude, COUNTRY_CODE,  POSTAL_CODE,
                PLACE_NAME, ADMIN1, ADMIN_CODE1, ADMIN2, ADMIN_CODE2,  ADMIN3, ADMIN_CODE3, accuracy);
        // check if the countys are similiar
        if ( strstr(ADMIN2, countyFilter) != 0)
        {
            // print the found countys data
            print_record(out, latitude, longitude, COUNTRY_CODE, POSTAL_CODE,PLACE_NAME, ADMIN1, ADMIN_CODE1, ADMIN2, ADMIN_CODE2, ADMIN3, ADMIN_CODE3, accuracy);
            error_count++;
        }
    }
    // if no county was found print error statement
    if(error_count < 1)
    {
        fprintf(out,"Sorry, county %s was not found.\n", countyFilter);
    }
}
//create place function
void place(char FileName[], char placeFilter[], FILE* out)
{
    // initialize varibles to be null incase information is missing
    char COUNTRY_CODE[3] = "";
    char POSTAL_CODE[21] = "";
    char PLACE_NAME[181] = "";
    char ADMIN1[101] = "";
    char ADMIN_CODE1[21] = "";
    char ADMIN2[101] = "";
    char ADMIN_CODE2[21] = "";
    char ADMIN3[101];
    char ADMIN_CODE3[21] = "";
    double latitude = 0;
    double longitude = 0;
    char accuracy[2] = "";
    int error_count = 0;
    FILE *in = fopen(FileName, "r");

    fprintf(out,"place %s\n",placeFilter);
    // loop throuh the file 
    while ( !feof(in) )
    {   
        // get the line of information
        read_record(in,  &latitude,  &longitude, COUNTRY_CODE,  POSTAL_CODE,
                PLACE_NAME, ADMIN1, ADMIN_CODE1, ADMIN2, ADMIN_CODE2,  ADMIN3, ADMIN_CODE3, accuracy);
        // check if the places are similiar 
        if (strstr(PLACE_NAME, placeFilter) != 0)
        {   fprintf(out,"\t");
            // write the found data to the output file
            print_record(out, latitude, longitude, COUNTRY_CODE, POSTAL_CODE,PLACE_NAME, ADMIN1, ADMIN_CODE1, ADMIN2, ADMIN_CODE2, ADMIN3, ADMIN_CODE3, accuracy);
            error_count++;
        }
        
    }
    // if no place found write error mesage
    if(error_count < 1)
    {
        fprintf(out,"Sorry, place name %s was not found.\n", placeFilter);
    }
    
}
// create the distance function
void distance(char FileName[], char post1[], char post2[], FILE* out)
{
    // initalize parameters as null in case of missing information
    char COUNTRY_CODE[3] = "";
    char POSTAL_CODE[21] = "";
    char PLACE_NAME[181] = "";
    char ADMIN1[101] = "";
    char ADMIN_CODE1[21] = "";
    char ADMIN2[101] = "";
    char ADMIN_CODE2[21] = "";
    char ADMIN3[101];
    char ADMIN_CODE3[21] = "";
    double latitude = 0;
    double longitude = 0;
    double latitude1 = 0;
    double latitude2 = 0;
    double longitude1 = 0;
    double longitude2 = 0;
    char accuracy[2] = "";
    int error_count1 = 0;
    int error_count2 = 0;
    
    FILE *in = fopen(FileName, "r");
    fprintf(out, "distance %s %s\n",post1,post2);
    // loop through the data
    while ( !feof(in) )
    {
        // get the line of data information   
        read_record(in,  &latitude,  &longitude, COUNTRY_CODE,  POSTAL_CODE,
                PLACE_NAME, ADMIN1, ADMIN_CODE1, ADMIN2, ADMIN_CODE2,  ADMIN3, ADMIN_CODE3, accuracy);
        // if the postal codes match and it hasnt been found before
        if ( strcmp(POSTAL_CODE, post1) == 0 && error_count1 == 0)
        {
            // print the first found postal codes data
            print_record(out, latitude, longitude, COUNTRY_CODE, POSTAL_CODE,PLACE_NAME, ADMIN1, ADMIN_CODE1, ADMIN2, ADMIN_CODE2, ADMIN3, ADMIN_CODE3, accuracy);
            error_count1++;
            latitude1 = latitude * M_PI/180;
            longitude1 = longitude * M_PI/180;
        }
        // check if the second postal code is there and hasnt been found before
        if ( strcmp(POSTAL_CODE, post2) == 0 && error_count2 == 0)
        {
            // print the first found data for the second postal code
            print_record(out, latitude, longitude, COUNTRY_CODE, POSTAL_CODE,PLACE_NAME, ADMIN1, ADMIN_CODE1, ADMIN2, ADMIN_CODE2, ADMIN3, ADMIN_CODE3, accuracy);
            error_count2++;
            latitude2 = latitude * M_PI/180;
            longitude2 = longitude * M_PI/180;
        }
        
    }
    // if both are found use the haversine formula to calculate the distance
    if((error_count1 > 0) && (error_count2 > 0))
    {
        double tempLat = (latitude2-latitude1);
        double tempLon = (longitude2- longitude1);
        double ans = sin(tempLat/2)*sin(tempLat/2) + cos(latitude1)*cos(latitude2)*sin(tempLon/2)*sin(tempLon/2);
        double c = 2*atan2(sqrt(ans),sqrt(1-ans));
        double d = 6371.0 * c;
        fprintf(out, "Distance: %lf km\n", d);
    }
    // if first wasnt found write error
    if(error_count1 < 1)
    {
        fprintf(out,"Sorry, postal code %s was not found.\n", post1);
    }
    // if second postal code write error message
    if(error_count2 < 1)
    {
        fprintf(out,"Sorry, postal code %s was not found.\n", post2);
    }

}



