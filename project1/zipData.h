#include <stdio.h>

// declare the read record function
void read_record(FILE *in, double *latitude, double *longitude,char COUNTRY_CODE[], char POSTAL_CODE[],
char PLACE_NAME[],char ADMIN1[],char ADMIN_CODE1[],char ADMIN2[],char ADMIN_CODE2[], char ADMIN3[],char ADMIN_CODE3[],char accuracy[]);
// declare the print record function
void print_record(FILE *out, double latitude,double longitude,char COUNTRY_CODE[], char POSTAL_CODE[],
                char PLACE_NAME[],char ADMIN1[],char ADMIN_CODE1[],char ADMIN2[],char ADMIN_CODE2[],
                char ADMIN3[],char ADMIN_CODE3[],char accuracy[]);
// define postal function
void postal(char FileName[], char postFilter[], FILE* out);
//declare county function
void county(char FileName[], char countyFilter[], FILE* out);
//declare place function
void place(char FileName[],char placeFilter[], FILE* out);
// declare distance function
void distance(char FileName[], char post1[], char post2[], FILE* out);