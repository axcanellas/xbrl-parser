#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>

//GLOBAL VARIABLES
char* in_filename;
char* out_filename;


int main(int argc, char* argv[]) {
/*
    int option;
    opterr = 0;
    while ( (option = getopt(argc, argv, ":o:r:g:b:t")) != -1 ) {
        switch(option) {
          case 'o':
              out_filename = optarg;
              break;
		    }
	  }

    for (int i = optind; i < argc; i++) {
        in_filename = argv[i];
    }
    */

    //open input file and check for errors
    FILE* in_file = fopen("ALB_10-K_2020.xml", "rb");
    if (in_file == NULL) {
        perror("ERROR: Could not open input file \n");
        return EXIT_FAILURE;
    }

    // create net income loss tag string for reference (including the space at the end)
    char netIncomeLossTag[24] = "<us-gaap:NetIncomeLoss ";
    // create compare string
    char compareTag[24];
    // create variable to store desired value
    char netIncomeLoss[9];
    // fread 23 bytes into compare string
    while (fgets(compareTag, sizeof(compareTag), in_file) != NULL) {
        while(strcmp(compareTag, netIncomeLossTag) != 0) {
            fgets(compareTag, sizeof compareTag, in_file);
        }

        printf("DEBUG: compareTag = %s\n", compareTag);

        // compare with reference string. if match, skip until after ">" is found, read in the next 9 bytes
        if(strcmp(compareTag, netIncomeLossTag) == 0) {
            char c = fgetc(in_file);
            while(c != '>') {
                c = fgetc(in_file);
            }
            fgets(netIncomeLoss, 9, in_file);
            printf("Net income loss: %s\n", netIncomeLoss);
        }
    }
    fclose(in_file);
}

