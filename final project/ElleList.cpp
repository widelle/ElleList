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
    
    // Open movie list text file to find last number used
    fp = fopen("MovieList.txt", "r");
    if (fp) {
        file = 1;
        char line[200];
        
        // Read each line to get last movie number
        while (fgets(line, sizeof(line), fp)) {
            int number;
            if (sscanf(line, "%d.", &number) == 1) { //outputs an integer from the string stored in line
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
        printf("Could not open file.\n"); // if file is not found
        return;
    }
    
    printf("\n==== LIST YOUR MOVIE ==== \n");
    printf("RULE:\n");
    printf("1. Press ENTER to EXIT!\n");
    printf("2. Type movie title to saved\n");
    
    printf("\nENTER MOVIE TITLE: \n");
    struct tracker *p = movie;
    
    // Loop to list title
    for (int i = 0; i < 100; i++, p++) {
        if (fgets(p->movieT, sizeof(p->movieT), stdin) == NULL) { // read a line of text
            break;
        }
        p->movieT[strcspn(p->movieT, "\n")] = 0; // remove the newline from the string

		/* - check if the string input is empty 
			- remove new line and will exit
		*/
        if (*(p->movieT) == '\0') { 
            break;
        }
        count++;
    }
    
    //saved movie
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
// Function to delete a movie title from the movie list file
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

    while (fgets(line, sizeof(line), fp)) { // searches the input to the line string where it stores the title
        if (strstr(line, movieTitle) == NULL) {
            strcpy(lines[count++], line);
        } else {
            deleted = 1; // if the line is found in the file, it will delete the string or the title
        }
    }
    fclose(fp);

    if (!deleted) {
        printf("Movie \"%s\" not found.\n", movieTitle);
        return;
    }

    // Rewrite file with updated numbering
    fp = fopen("MovieList.txt", "w");
    if (!fp) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        // Remove numbering 
        char *numbering = strchr(lines[i], '.');
        if (numbering != NULL) {
            numbering++; 
            while (*numbering == ' ') numbering++; // skip spaces
        } else {
            numbering = lines[i]; 
        }
        // Remove newline character
        numbering[strcspn(numbering, "\n")] = 0;
        
        fprintf(fp, "%d. %s\n", i + 1, numbering);
    }
    fclose(fp);

    printf("Movie \"%s\" deleted successfully.\n", movieTitle);
}

// DELETING SERIES LIST INPUT
void deleteTVShow() {
    char SeriesTitle[100];
    
    printf("Enter the movie title to delete: ");
    fgets(SeriesTitle, sizeof(SeriesTitle), stdin);
    SeriesTitle[strcspn(SeriesTitle, "\n")] = 0;

    FILE *fp = fopen("TV Show List.txt", "r");
    if (!fp) {
        printf("File not found.\n");
        return;
    }

    char lines[100][200];
    int count = 0;
    int deleted = 0;
    char line[200];

    while (fgets(line, sizeof(line), fp)) { // searches the input to the line string where it stores the title
        if (strstr(line, SeriesTitle) == NULL) {
            strcpy(lines[count++], line);
        } else {
            deleted = 1; // if the line is found in the file, it will delete the string or the title
        }
    }
    fclose(fp);

    if (!deleted) {
        printf("Movie \"%s\" not found.\n", SeriesTitle);
        return;
    }

    // Rewrite file with updated numbering
    fp = fopen("TV Show List.txt", "w");
    if (!fp) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        // Remove numbering 
        char *numbering = strchr(lines[i], '.');
        if (numbering != NULL) {
            numbering++; 
            while (*numbering == ' ') numbering++; 
        } else {
            numbering = lines[i]; 
        }
        // Remove newline character
        numbering[strcspn(numbering, "\n")] = 0;
        
        fprintf(fp, "%d. %s\n", i + 1, numbering);
    }
    fclose(fp);

    printf("Movie \"%s\" deleted successfully.\n", SeriesTitle);
}


// DISPLAY MOVIE LIST
void displayMovieList() {
    FILE *fp = fopen("MovieList.txt", "r");
    if (!fp) {
        printf("No movies found.\n");
        return;
    }

    printf("\n==== MOVIE LIST ====\n");
    char line[200];
    
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    fclose(fp);
}

// DISPLAY SERIES LIST
void displayTVList() {
    FILE *fp = fopen("TV Show List.txt", "r");
    if (!fp) {
        printf("No TV shows found.\n");
        return;
    }

    printf("\n==== TV SHOW LIST ====\n");
    char line[200];
    
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    fclose(fp);
}

//edit the input
void editInput() {
    char oldTitle[100], newTitle[100];
    char lines[100][200];
    int count = 0, found = 0;
    int listChoice;
    char input[10];
    char filename[50];
    char itemType[20];

    // Prompt user which list to edit
    printf("Which list do you want to edit?\n");
    printf("1. Movie List\n2. TV Show List\n");
    while (1) {
        printf("Enter your choice (1 or 2): ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Input error. Try again.\n");
            continue;
        }
        if ((input[0] == '1' || input[0] == '2') && (input[1] == '\n' || input[1] == '\0')) {
            listChoice = input[0] - '0';
            break;
        } else {
            printf("Invalid choice! Please enter 1 or 2.\n");
        }
    }

    // Set filename and itemType based on choice using strcpy
    if (listChoice == 1) {
        strcpy(filename, "MovieList.txt");
        strcpy(itemType, "movie");
    } else {
        strcpy(filename, "TV Show List.txt");
        strcpy(itemType, "TV show");
    }

    printf("Enter the %s title to edit: ", itemType);
    fgets(oldTitle, sizeof(oldTitle), stdin);
    oldTitle[strcspn(oldTitle, "\n")] = 0;  // remove newline

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("File not found.\n");
        return;
    }

    // Read all lines into array
    while (fgets(lines[count], sizeof(lines[0]), fp) != NULL) {
        count++;
        if (count >= 100) break;
    }
    fclose(fp);

    // Search for the old title in each line
    for (int i = 0; i < count; i++) {
        char *titleStart = strchr(lines[i], '.');
        if (titleStart != NULL) {
            titleStart += 2;
        } else {
            titleStart = lines[i];
        }
        // Remove trailing newline for comparison
        char temp[200];
        strcpy(temp, titleStart);
        temp[strcspn(temp, "\n")] = 0;

        if (strcmp(temp, oldTitle) == 0) {
            found = 1;
            printf("Enter the new %s title: ", itemType);
            fgets(newTitle, sizeof(newTitle), stdin);
            newTitle[strcspn(newTitle, "\n")] = 0;

            if (titleStart != lines[i]) {
                int numLen = (int)(titleStart - lines[i]);
                char newLine[200];
                int j;
                for (j = 0; j < numLen; j++) {
                    newLine[j] = lines[i][j];
                }
                newLine[j] = '\0';

                strcat(newLine, newTitle);
                strcat(newLine, "\n");

                strcpy(lines[i], newLine);
            } else {
                int len = 0;
                while (newTitle[len] != '\0') {
                    lines[i][len] = newTitle[len];
                    len++;
                }
                lines[i][len] = '\n';
                lines[i][len + 1] = '\0';
            }
            break;
        }
    }

    if (!found) {
        if (listChoice == 1) {
            printf("Movie \"%s\" not found.\n", oldTitle);
        } else {
            printf("TV show \"%s\" not found.\n", oldTitle);
        }
        return;
    }

    // Write all lines back to file
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fputs(lines[i], fp);
    }
    fclose(fp);

    if (listChoice == 1) {
        printf("Movie title updated successfully.\n");
    } else {
        printf("TV show title updated successfully.\n");
    }
}

// Main function to display menu and call appropriate functions
int main() {
    struct tracker movie[100]; //array use to hold the # of lines
    struct tracker tv[100];
    int choice;
    char input[10];

    while(1){
        printf("\n==== ELLE LIST TRACKER ====\n");
        printf("1. Movie List\n2. TV Show List\n");
        printf("3. Delete Movie Title\n4. Delete TV Show Title\n");
        printf("5. Display Movie List\n6. Display TV Show List\n");
        printf("7. Edit List\n8. Exit\n");

        while (1) {
            printf("Enter your choice (1-5): ");
            if (fgets(input, sizeof(input), stdin) == NULL) {
                printf("Input error. Try again.\n");
                continue;
            }
            // Check if input is 1-7 only
            if (input[0] >= '1' && input[0] <= '7' && (input[1] == '\n' || input[1] == '\0')) {
                choice = input[0] - '0';  
                break;
            } else {
                printf("\nINVALID CHOICE!\n\n");
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
        	displayMovieList();
		} else if(choice == 6){
			displayTVList();
		} else if(choice == 7){
			editInput();
        } else if(choice == 8){
        	printf("\nExit!\n");
            break;
		}
    }

    return 0;
}
