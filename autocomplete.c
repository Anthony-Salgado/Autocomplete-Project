#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "autocomplete.h"


//Compare functions for terms' lexicophraphic orders and weights
int cmp_term(const void *a, const void *b) {
    //Compare two terms lexicographically by their term field
    const term *ta = (const term*) a;
    const term *tb = (const term*) b;
    return strcmp(ta -> term, tb -> term);
}

int cmp_weights(const void *a, const void *b) {
    //Compare the weights of two terms
    const term *ta = (const term*) a;
    const term *tb = (const term*) b;

    if (ta -> weight < tb -> weight){
        return 1;
    } else if (ta -> weight > tb -> weight) {
        return -1;
    } else {
        return 0;
    }
}


// Part 1
void read_in_terms(term **terms, int *pnterms, char *filename){
    char line[200];
    //Open the file for reading
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: could not open file '%s'\n", filename);
        exit(EXIT_FAILURE);
    }

    //Count the number of lines in the file
    fgets(line, sizeof(line), fp);
    *pnterms = atoi(line);

    //Allocate memory for the terms
    *terms = (term*)malloc(*pnterms*sizeof(term));
    if (*terms == NULL) {
        fprintf(stderr, "Error:could not allocate memory for %d terms\n", *pnterms);
        exit(EXIT_FAILURE);
    }


    //Read in the terms and weights from the file
    int i = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strlen(line) > 1) {
            int j = 0;
            while(isdigit(line[j]) == 0) {
                j++;
            }
            char *p = strtok(line+j, "\t");
            (*terms)[i].weight = atof(p);
            p = strtok(NULL, "\t");
            p[strlen(p)-1] = '\0';
            strcpy((*terms)[i].term, p);
            i++;


        // for (int k = strlen(p)-2; k < 200; k++) {
        //         p[k] = '\0';
        //     }
        }
    }

    //Sort the terms in ascending orders
    qsort(*terms, *pnterms , sizeof(term), cmp_term);


    //Store the pointer to the block and the number of terms
    // *terms = t;
    // *pnterms = n;

    //Close the file
    fclose(fp);
}


// Part 2

int lowest_match (term *terms, int nterms, char *substr){
    int low = 0;
    int high = nterms - 1;
    int mid, cmp;

    while (low <= high) {
        mid = low + (high - low) /2;
        cmp = strncmp(terms[mid].term, substr, strlen(substr));

        if (cmp >= 0) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    if (strncmp(terms[low].term, substr, strlen(substr)) == 0) {
        return low;
    } else {
        return -1;
    }

}

// Part 3
int highest_match(struct term *terms, int nterms, char *substr) {
    int low = 1;
    int high = nterms - 1;
    int mid, cmp;
    
    while (low <= high) {
        mid = low + (high - low) / 2;
        cmp = strncmp(terms[mid].term, substr, strlen(substr));
        
        if (cmp > 0) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    if (strncmp(terms[high].term, substr, strlen(substr)) == 0){
        return high;
    } else {
        return -1;
    }
    
}


// Part 4
void autocomplete (term **answer, int *n_answer, term *terms, int nterms, char *substr){
    //Find the index of the first and last terms that match substr
    int low = lowest_match(terms, nterms, substr);
    int high = highest_match(terms, nterms, substr);

    //return an empty list if there are no matches
    if (low == -1 || high == -1 || low > high) {
        *answer = NULL;
        *n_answer = 0;
        return;
    }

    //allocate memory for results
    int n_results = high - low + 1;
    term *results = malloc(n_results * sizeof(term));
    if (results == NULL) {
        fprintf(stderr, "Error: failed to allocate memory for results \n");
        exit(EXIT_FAILURE);
    }

    //Copy the matching terms into results
    for (int i = 0; i < n_results; i++) {
        results[i] = terms[low + i];
    }

    //Sort results by weight in non-increasing order
    qsort(results, n_results, sizeof(term), cmp_weights);

    //Set the output variables
    *answer = results;
    *n_answer = n_results;
}

// int main(void)
// {
//     struct term *terms;
//     int nterms;
//     read_in_terms(&terms, &nterms, "cities.txt");
//     int l = lowest_match(terms, nterms, "Tor");
//     printf("The value of lowest match %d", l);
//     int h = highest_match(terms, nterms, "Tor");
//     printf("The value of highest match %d", h);
//     struct term *answer;
//     int n_answer;
//     autocomplete(&answer, &n_answer, terms, nterms, "Tor");
//     //free allocated blocks here -- not required for the project, but good practice
//     return 0;
// }




