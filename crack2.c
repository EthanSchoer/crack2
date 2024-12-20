#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

const int PASS_LEN = 20;        // Maximum any password will be
const int HASH_LEN = 33;        // Length of MD5 hash strings

void trim(char string[])
{
    int i = 0;
    while (string[i] != '\n' && string[i] != '\0')
    {
        i++;
    }
    string[i] = '\0';
}

// Given a target plaintext word, use it to try to find
// a matching hash in the hashFile.
// Get this function working first!
char * tryWord(char * plaintext, char * hashFilename)
{
    // Hash the plaintext
    char *hash = md5(plaintext, strlen(plaintext));
    int found = 0;
    // Open the hash file
    FILE *hashFile = fopen(hashFilename, "r");
    // Loop through the hash file, one line at a time.
    while(!feof(hashFile))
    {
        char *line = malloc(1001);
        if (fgets(line, 1001, hashFile) != NULL)
{
    trim(line);
    if (strcmp(hash, line) == 0)
    {
        found = 1;
    }
}

        free(line);
    }
    fclose(hashFile);
    
    if (found == 1)
    {
        return hash;
    }
    free(hash);
    return NULL;
    // Attempt to match the hash from the file to the
    // hash of the plaintext.

    // If there is a match, you'll return the hash.
    // If not, return NULL.

    // Before returning, do any needed cleanup:
    //  Close files?
    //  Free memory?

    // Modify this line so it returns the hash
    // that was found, or NULL if not found.
}


int main(int argc, char *argv[])
{
    int cracked = 0;
    if (argc < 3) 
    {
        fprintf(stderr, "Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }

    // These two lines exist for testing. When you have
    // tryWord working, it should display the hash for "hello",
    // which is 5d41402abc4b2a76b9719d911017c592.
    // Then you can remove these two lines and complete the rest
    // of the main function below.
   char *found = malloc(1001);
    
    // Open the dictionary file for reading.
    FILE *dictFile = fopen(argv[2], "r");
    // For each dictionary word, pass it to tryWord, which
    // will attempt to match it against the hashes in the hash_file.
    while(!feof(dictFile))
    {
        char *line = malloc(1001);
        if (fgets(line, 1001, dictFile) != NULL)
        {
            trim(line);
            found = tryWord(line, argv[1]);
            if (found != NULL)
            {
                cracked++;
                printf("%s %s\n", found, line);
            }
        }
        free(found);
        //free(line);
    }
    // If we got a match, display the hash and the word. For example:
    //   5d41402abc4b2a76b9719d911017c592 hello
    
    // Close the dictionary file.
    fclose(dictFile);
    // Display the number of hashes that were cracked.
    printf("%d hashes were cracked", cracked);
    // Free up any malloc'd memory?
}
