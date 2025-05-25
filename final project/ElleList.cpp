#include <stdio.h>
#include <string.h>

struct tracker {
    char movieT[100];
    char tvShow[100];
};

//MOVIE LIST TRACKER
void inputMovieList(struct tracker *movie) {
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
                    if (sscanf(line, "%d.", &number) == 1) {
                        if (num >= num) {
                            num = number + 1;
                        }
                    }
                }
            }
        }
        fclose(fp);
    }
    
    //condition if the file is not found
    fp = fopen("MovieList.txt", "a");
    if (!fp) {
        printf("Could not open file.\n");
        return;
    }
    
    if (!file) {
        fprintf(fp, "\n=== Elle's Movie List ===\n");
    }
    
    printf("\n==== LIST YOUR MOVIE ==== \n");
    printf("RULE:\n");
    printf("1. Press ENTER to EXIT!\n");
    printf("2. Type movie title to saved\n");
    
    printf("\nENTER MOVIE TITLE: \n");
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
            if (line[0] >= '0' && line[0] <= '9') {
                int i = 0;
                while (line[i] >= '0' && line[i] <= '9') {
                    i++;
                }
                if (line[i] == '.') {
                    int number;
                    if (sscanf(line, "%d.", &number) == 1) {
                        if (num >= num) {
                            num = number + 1;
                        }
                    }
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
    
    if (!file) {
        fprintf(fp, "\n=== Elle's TV Show List ===\n");
    }
    
    printf("\n==== LIST YOUR TV SHOW ==== \n");
    printf("RULE:\n");
    printf("1. Press ENTER to SAVED!\n");
    printf("2. Type TV Show title to saved\n");
    
    printf("\nENTER TV SHOW TITLE: \n");
    for(int i=0; i<100; i++){
        if(fgets(tv[i].tvShow, sizeof(tv[i].tvShow), stdin) == NULL){
            break;
        }
        tv[i].tvShow[strcspn(tv[i].tvShow, "\n")] = 0; 
        
        if(strlen(tv[i].tvShow) == 0){
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

//rating of the list

//deleting a list

//if the user enter keys that is not acceptable, it will error
int main() {
    struct tracker movie[100];
    struct tracker tv[100];
    int choice;
    
    while(1){
    	printf("\n==== ELLE LIST TRACKER ====\n");
    	printf("1. Movie List\n");
    	printf("2. TV Show List\n");
    	printf("3. Exit\n");
    	printf("Enter your choice (1-3): ");
    	
    	if(scanf("%d", &choice) != 1){
    		while(getchar() != '\n');
    			printf("\nINVALID CHOICE! Choose number 1, 2, and 3 only!!\n");
    			continue;
		}
    	getchar();
    	
    	if(choice == 1){
    		inputMovieList(movie);
		}else if(choice == 2){
			inputTVList(tv);
		}else if(choice == 3){
			printf("Exit!");
			break;
		}else{
			printf("\nINVALID CHOICE! Choose number 1, 2, and 3 only!!\n");
		}
	}
    
    return 0;
}
