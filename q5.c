#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int lineSize=0,c;
char **lines;

char *readLine();
int insertLine(char index[],char  *text);
void printAllLines();
void deleteLine();
void freeAll();
void updateFile();
char* readLineDynamic(FILE *fp);


int main() {

    lines=(char **)malloc(lineSize * sizeof(char *));
    if(lines==NULL){
        printf("Dynamic memory allocation failed!");
        return 1;
    }

    FILE *fp = fopen("q5.txt", "r");
    if(fp==NULL){
        printf("Can't open file q5.txt");
        return 1;
    }
    char *line;
    while ((line = readLineDynamic(fp)) != NULL) {
        lineSize++;
        char *Allocating = malloc(strlen(line) + 1);
        if(Allocating==NULL){
            printf("Allocating memory to 2d failed ");
            return 0;
        }
        lines[lineSize - 1]=Allocating;
        strcpy(lines[lineSize-1],line);
        free(line);
    }
    fclose(fp);


    int chose;
    while(1){
        system("cls");
        printf("Chose from the above: \n1. Insert Line \n2. Delete Line\n3. Display All Lines\n4. Delete All Lines\n5. Exit\n\tChose :) ");
        scanf("%d",&chose);
        switch (chose)
        {
        case 1:
            char index[5];
            printf("Index :- ");
            scanf("%s",index);
            while((c=getchar()), c != '\n' && c != EOF);
            printf("%s Line :- ",index);
            char *text=readLine();
            insertLine(index,text);
            break;
        case 2:
            deleteLine();
            printf("\nDeleted a line\n");
            Sleep(5000);
            break;
        case 3:
            printAllLines();
            Sleep(5000);
            break;
        case 4:
            freeAll();
            printf("\nDeleted all lines!...\n");
            Sleep(5000);
            break;
        case 5:
            return 0;
            break;
        
        default:
            printf("\nInvalid Input :( \n");
            Sleep(3000);
            break;
        }   
    }

    return 0;
}

char *readLine(){
    char *buffer=NULL;
    int size=0;
    int ch;
    while((ch=getchar()), ch != '\n' && ch != EOF){
        buffer=realloc(buffer,size+1);
        if(buffer==NULL){
            printf("\nDMA failed!\n");
            return 0;
        }
        buffer[size]=ch;
        size++;
    }
    buffer = realloc(buffer, size + 1);
    if(buffer==NULL){
            printf("\nDMA failed!\n");
            return 0;
    }
    buffer[size] = '\0';
    return buffer;
}
int insertLine(char index[],char  *text){
    for(int i=0;i<lineSize;i++){
        if(strncmp(lines[i],index,strlen(index))==0){
            printf("\nLine already exist on index %s \n",index);
            Sleep(5000);
            return 0;
        }
    }
    char nextIndexOfLines[5];
    int indexNum,nextIndexNu;
    for(int i=0;i<lineSize-1;i++){
        indexNum=atoi(index);
        sscanf(lines[i+1],"%[^ ]",nextIndexOfLines);
        nextIndexNu=atoi(nextIndexOfLines);
        if(indexNum<nextIndexNu){

            lineSize++;
            lines=realloc(lines,sizeof(char *) * lineSize);

            int j;
            for(j=lineSize-1;j>i+1;j--){
                lines[j]=lines[j-1];
            }
            lines[i+1]=malloc(strlen(text) + strlen(index) + 5);
            sprintf(lines[i+1],"%s %s",index,text); 

            updateFile();
            printf("Added Line %s successfully ",index);
            Sleep(5000);
            return 0;
        }
    }
    lineSize++;
    lines=realloc(lines,sizeof(char *) * lineSize);
    if(lines==NULL){
            printf("\nDMA failed!\n");
            return 0;
        }
    lines[lineSize-1]=malloc(strlen(text) + strlen(index) + 5);

    sprintf(lines[lineSize-1],"%s %s",index,text);
    updateFile();
    return 0;
}

void printAllLines(){
    printf("\n\tThe Lines:\n\n");
    for(int i=0;i<lineSize;i++){
        printf("%s\n",lines[i]);
    }
}
void deleteLine(){
    char index[5];
    printf("Index :- ");
    scanf("%s",index);

    for(int i=0;i<lineSize;i++){
        if(strncmp(lines[i],index,strlen(index))==0){
            memmove(&lines[i],&lines[i+1],(lineSize-i-1)*sizeof(char*));
            lineSize--;
            lines=realloc(lines,lineSize*sizeof(char *));
            if(lines==NULL){
            printf("\nDMA failed! to shrink\n");
            return;
            }
            free(lines[i]);
            updateFile();
            return;
        }
    }
}
void freeAll(){
    for(int i=0;i<lineSize;i++){
        free(lines[i]);
    }
    free(lines);
    lines=NULL;
    lineSize=0;
    updateFile();
}
void updateFile(){
    FILE *pFile=fopen("q5.txt","w");
    if(pFile==NULL){
        printf("\nOpening file failed!\n");
        return;
    }
    for(int i=0;i<lineSize;i++){
        fprintf(pFile,"%s\n",lines[i]);
    }
    fclose(pFile);
}
char* readLineDynamic(FILE *fp) {
    char *buffer = NULL;
    int size = 0;
    int ch;

    while ((ch = fgetc(fp)) != '\n' && ch != EOF) {
        char *newBuffer = realloc(buffer, size + 2); 
        if(newBuffer==NULL){
            printf("\nDMA failed!\n");
            return 0;
        }
        if (!newBuffer) {
            free(buffer);
            return NULL;
        }
        buffer = newBuffer;
        buffer[size++] = ch;
    }

    if (size == 0 && ch == EOF)
        return NULL; 

    buffer[size] = '\0';
    return buffer;
}
