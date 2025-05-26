#include <stdio.h>
#include <string.h>

struct tracker { 
    char movieT[100]; // array to store movie title
    char tvShow[100]; // array to store tv show title
};

//MOVIE LIST TRACKER
void inputMovieList(struct tracker *movie) {
    FILE *fp;
    int count = 0;
    int num = 1;
    int file = 0;
    
    //// Open movie list text file to find last number used
    fp = fopen("MovieList.txt", "r");
    if (fp) {
        file = 1;
        char line[200];
        
        // Read each line to get last movie number
        while (fgets(line, sizeof(line), fp)) {
            int number;
            if (sscanf(line, "%d.", &number) == 1) {
                if (number >= num) {
                    num = number + 1; // update the next number
                }
            }
        }
        fclose(fp);
    }
    
    // Open file in append mode to add new movies
    fp = fopen("MovieList.txt", "a");
    
    if (!fp) {
        printf("Could not open file.\n");
        return;
    }
    
    printf("\n==== LIST YOUR MOVIE ==== \n");
    printf("RULE:\n");
    printf("1. Press ENTER to EXIT!\n");
    printf("2. Type movie title to saved\n");
    
    printf("\nENTER MOVIE TITLE: \n");
    struct tracker *p = movie;
    
    // Loop to get up to 100 movie titles from user
    for (int i = 0; i < 100; i++, p++) {
        if (fgets(p->movieT, sizeof(p->movieT), stdin) == NULL) {
            break;
        }
        p->movieT[strcspn(p->movieT, "\n")] = 0;

        if (*(p->movieT) == '\0') {
            break;
        }
        count++;
    }
    
    // Write all entered movies to file with numbering
    for(int i=0; i<count; i++){
        fprintf(fp, "%d. %s\n", num + i, movie[i].movieT);
    }
    fclose(fp);
        
    printf("Saved.\n");
}

//TV SHOW LIST TRACKER
void inputTVList(struct tracker *tv) {
    FILE *fp;
    int count = 0;
    int num = 1;
    int file = 0;
    
    fp = fopen("TV Show List.txt", "r");
    if (fp) {
        file = 1;
        char line[200];
        while (fgets(line, sizeof(line), fp)) {
            int number;
            if (sscanf(line, "%d.", &number) == 1) {
                if (number >= num) {
                    num = number + 1;
                }
            }
        }
        fclose(fp);
    }
    
    //condition if the file is not found
    fp = fopen("TV Show List.txt", "a");
    if (!fp) {
        printf("Could not open file.\n");
        return;
    }
    
    printf("\n==== LIST YOUR TV SHOW ==== \n");
    printf("RULE:\n");
    printf("1. Press ENTER to SAVED!\n");
    printf("2. Type TV Show title to saved\n");
    
    printf("\nENTER TV SHOW TITLE: \n");
    struct tracker *p = tv;
    for (int i = 0; i < 100; i++, p++) {
        if (fgets(p->tvShow, sizeof(p->tvShow), stdin) == NULL) {
            break;
        }
        p->tvShow[strcspn(p->tvShow, "\n")] = 0;

        if (*(p->tvShow) == '\0') {
            break;
        }
        count++;
    }
    
    for(int i=0; i<count; i++){
        fprintf(fp, "%d. %s\n", num + i, tv[i].tvShow);
    }
    fclose(fp);
        
    printf("Saved.\n");
}

//DELETING A MOVIE TITLE
// Function to delete a movie title from the movie list fil
void deleteMovieTitle() {
    char movieTitle[100];
    
    printf("Enter the movie title to delete: ");
    fgets(movieTitle, sizeof(movieTitle), stdin);
    movieTitle[strcspn(movieTitle, "\n")] = 0;

    FILE *fp = fopen("MovieList.txt", "r");
    if (!fp) {
        printf("File not found.\n");
        return;
    }

    char lines[100][200];
    int count = 0;
    int deleted = 0;
    char line[200];

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, movieTitle) == NULL) {
            strcpy(lines[count++], line);
        } else {
            deleted = 1;
        }
    }
    fclose(fp);

    fp = fopen("MovieList.txt", "w"); 
    if (!fp) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fputs(lines[i], fp);
    }
    fclose(fp);

    if (deleted)
        printf("Movie \"%s\" deleted successfully.\n", movieTitle);
    else
        printf("Movie \"%s\" not found.\n", movieTitle);
}

//DELETING TV SHOW TITLE
void deleteTVShow(){
	char TVtitle[100];
    printf("Enter the TV Show title to delete: ");
    fgets(TVtitle, sizeof(TVtitle), stdin);
    TVtitle[strcspn(TVtitle, "\n")] = 0;

    FILE *fp = fopen("TV Show List.txt", "r");
    if (!fp) {
        printf("File not found.\n");
        return;
    }

    char lines[100][200];
    int count = 0;
    int deleted = 0;
    char line[200];

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, TVtitle) == NULL) {
            strcpy(lines[count++], line);
        } else {
            deleted = 1;
        }
    }
    fclose(fp);

    fp = fopen("TV Show List.txt", "w"); 
    if (!fp) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fputs(lines[i], fp);
    }
    fclose(fp);

    if (deleted)
        printf("TV Show \"%s\" deleted successfully.\n", TVtitle);
    else
        printf("TV Show \"%s\" not found.\n", TVtitle);
}

// Main function to display menu and call appropriate functions
int main() {
    struct tracker movie[100]; //array use to hold the # of lines
    struct tracker tv[100];
    int choice;
    char input[10];

    while(1){
        printf("\n==== ELLE LIST TRACKER ====\n");
        printf("1. Movie List\n");
        printf("2. TV Show List\n");
        printf("3. Delete Movie Title\n");
        printf("4. Delete TV Show Title\n");
        printf("5. Exit\n");

        while (1) {
            printf("Enter your choice (1-5): ");
            if (fgets(input, sizeof(input), stdin) == NULL) {
                printf("Input error. Try again.\n");
                continue;
            }
            // Check if input is 1-5 only
            if (input[0] >= '1' && input[0] <= '5' && (input[1] == '\n' || input[1] == '\0')) {
                choice = input[0] - '0';  
                break;
            } else {
                printf("\nINVALID CHOICE! Choose number 1, 2, 3, 4 or 5 only!!\n\n");
            }
        }

        if(choice == 1){
            inputMovieList(movie);
        } else if(choice == 2){
            inputTVList(tv);
        } else if(choice == 3){
            deleteMovieTitle();
        } else if(choice == 4){
            deleteTVShow();
        } else if(choice == 5){
            printf("\nExit!\n");
            break;
        }
    }

    return 0;
}
