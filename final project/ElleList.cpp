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
		//check if the string input is empty & remove new line and will exit
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
        char *numbering = strchr(lines[i], '.'); // find the string and the period of numbering
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
    FILE *fp = fopen("MovieList.txt", "r"); // try to open 
    if (!fp) {
        printf("No movies found.\n");
        return;
    }

    printf("\n==== MOVIE LIST ====\n");
    char line[200];
    
    while (fgets(line, sizeof(line), fp)) { // reads line from the file
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
void editList() {
    char oldTitle[100], newTitle[100]; // stores title
    char lines[100][200]; // stores the lines
    int count = 0, found = 0; // track the numbering
    int listChoice; // movie or tv show
    char input[10];
    char filename[50]; // movie.txt or tvshow.txt
    char itemType[20];
    // Ask user which list to edit
    printf("\nWhich list do you want to edit?\n");
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

    if (listChoice == 1) {
        strcpy(filename, "MovieList.txt");
        strcpy(itemType, "movie");
    } else {
        strcpy(filename, "TV Show List.txt");
        strcpy(itemType, "TV show");
    }
    // Open the file for reading
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Could not open %s.\n", filename);
        return;
    }
    // Read all lines from the file 
    count = 0;
    while (fgets(lines[count], sizeof(lines[count]), fp) && count < 100) {
        count++;
    }
    fclose(fp);

    while (1) {
        printf("Enter the %s title to edit: ", itemType);
        if (fgets(oldTitle, sizeof(oldTitle), stdin) == NULL) {
            printf("Input error. Try again.\n");
            continue;
        }
        oldTitle[strcspn(oldTitle, "\n")] = 0;  // Remove newline character
        found = 0;  // Reset found 
        // Search for the title in the list
        for (int i = 0; i < count; i++) { 
            char *titleStart = strchr(lines[i], '.');
            if (titleStart != NULL) {
                titleStart++;  
                while (*titleStart == ' ') titleStart++; 
            } else {
                titleStart = lines[i]; 
            }

            char theTitle[200];
            strcpy(theTitle, titleStart);
            theTitle[strcspn(theTitle, "\n")] = 0;  // Remove newline

            if (strcmp(theTitle, oldTitle) == 0) {
                found = 1;
                // Ask for the new title
                printf("Enter the new %s title: ", itemType);
                if (fgets(newTitle, sizeof(newTitle), stdin) == NULL) {
                    printf("Input error. Try again.\n");
                    found = 0;  
                    break;
                }
                newTitle[strcspn(newTitle, "\n")] = 0;  // Remove newline
                // Replace the old title with the new title in the line
                if (titleStart != lines[i]) {
                    int titleLe = titleStart - lines[i];
                    char newLine[200];
	                    strncpy(newLine, lines[i], titleLe);
	                    newLine[titleLe] = '\0';
	                    strcat(newLine, newTitle);
	                    strcat(newLine, "\n");
	                    strcpy(lines[i], newLine);
                } else {
                    strcpy(lines[i], newTitle);
                    strcat(lines[i], "\n");
                }
                printf("%s title updated successfully!\n", itemType);
                break;
            }
        }

        if (found) {
            break;  // Exit the loop if title was found and updated
        } else {
            printf("%s \"%s\" not found. Please try again.\n", itemType, oldTitle); // Loop continues to ask again
        }
    }
    fp = fopen(filename, "w"); // Save the updated list back to the file
    if (!fp) {
        printf("Could not open %s for writing.\n", filename);
        return;
    }
    for (int i = 0; i < count; i++) {
        fputs(lines[i], fp);
    }
    fclose(fp);
    printf("The updated %s list has been saved.\n", itemType);
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
	            printf("Enter your choice (1-8): ");
	            if (fgets(input, sizeof(input), stdin) == NULL) {
	                printf("Input error. Try again.\n");
	                continue;
	            }
	            if (input[0] >= '1' && input[0] <= '8' && (input[1] == '\n' || input[1] == '\0')) {
	                choice = input[0] - '0';  
	                break; // Check if input is 1-7 only
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
			editList();
        } else if(choice == 8){
        	printf("\nExit!\n");
            break;
		}
    }
    return 0;
}
