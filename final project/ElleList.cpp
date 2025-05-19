#include <stdio.h>
#include <string.h>

struct tracker {
    char movieT[100];
    char type[20];
};

//movie list tracker
void inputList(struct tracker *movie) {
    FILE *fp;
    int count = 0;
    int num = 1;
    int file = 0;
    
    fp = fopen("MovieList.txt", "r");
    if (fp) {
        file = 1;
        char line[200];
        while (fgets(line, sizeof(line), fp)) {
            if (line[0] >= '0' && line[0] <= '9') {
                int i = 0;
                while (line[i] >= '0' && line[i] <= '9') {
                    i++;
                }
                if (line[i] == '.') {
                    int number;
                    if (sscanf(line, "%d.", &number) == 0) {
                        if (num >= num) {
                            num = number + 1;
                        }
                    }
                }
            }
        }
        fclose(fp);
    }
    
    // Now open for appending
    fp = fopen("MovieList.txt", "a");
    if (!fp) {
        printf("Could not open file.\n");
        return;
    }
    
    // If file didn't exist before, write header
    if (!file) {
        fprintf(fp, "=== Elle's Movie List ===\n");
    }
    
    printf("=== LIST YOUR MOVIE === \n");
    printf("Press ENTER to EXIT!\n");
    printf("\nEnter Movie Title: \n");
    for(int i=0; i<100; i++){
        if(fgets(movie[i].movieT, sizeof(movie[i].movieT), stdin) == NULL){
            break;
        }
        movie[i].movieT[strcspn(movie[i].movieT, "\n")] = 0; 
        
        if(strlen(movie[i].movieT) == 0){
            break;
        }
        count++;
    }
    
    for(int i=0; i<count; i++){
        fprintf(fp, "%d. %s\n", num + i, movie[i].movieT);
    }
    fclose(fp);
        
    printf("Saved.\n");
}
//tv-show list tracker

//rating of the list

//deleting a list

//if the user enter keys that is not acceptable, it will error
int main() {
    struct tracker movie[100];
    inputList(movie);
    
    return 0;
}
