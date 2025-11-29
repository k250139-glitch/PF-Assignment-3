#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StudentRec{
    int id;
    char nm[100];
    char bt[30];
    char mem[10];
    char regdt[15];
    char dob[15];
    char intst[10];
};

struct StudentRec *arr=NULL;
int arrsz=0;

void loadDatabase(const char *fn){
    FILE *fp=fopen(fn,"rb");
    if(!fp){
        printf("File not opend..maybe new?\n");
        return;
    }
    struct StudentRec tmp;
    while(fread(&tmp,sizeof(struct StudentRec),1,fp)==1){
        arrsz++;
        arr=realloc(arr,arrsz*sizeof(struct StudentRec));
        arr[arrsz-1]=tmp;
    }
    fclose(fp);
}

void saveDatabase(const char *fn){
    FILE *fp=fopen(fn,"wb");
    if(!fp){
        printf("Save err...\n");
        return;
    }
    fwrite(arr,sizeof(struct StudentRec),arrsz,fp);
    fclose(fp);
}

int checkDup(int sid){
    for(int i=0;i<arrsz;i++){
        if(arr[i].id==sid) return 1;
    }
    return 0;
}

void addStudentFile(struct StudentRec s,const char *fn){
    FILE *fp=fopen(fn,"ab");
    if(!fp){
        printf("Cant write file lol\n");
        return;
    }
    fwrite(&s,sizeof(struct StudentRec),1,fp);
    fclose(fp);
}

void addStudentMem(struct StudentRec s){
    arrsz++;
    arr=realloc(arr,arrsz*sizeof(struct StudentRec));
    arr[arrsz-1]=s;
}

void updStudent(int sid,const char *fn){
    int f=0,c;
    for(int i=0;i<arrsz;i++){
        if(arr[i].id==sid){
            f=1;
            printf("New batch: ");
            while((c=getchar()), c != '\n' && c != EOF);
            scanf("%s",arr[i].bt);
            printf("New Membership: ");
            scanf("%s",arr[i].mem);
            break;
        }
    }
    if(!f){
        printf("No Student with id %d.\n",arr->id);
        return;
    }
    saveDatabase(fn);
}

void delStudent(int sid,const char *fn){
    int idx=-1;
    for(int i=0;i<arrsz;i++){
        if(arr[i].id==sid){
            idx=i;
            break;
        }
    }
    if(idx==-1){
        printf("id no found bro\n");
        return;
    }
    for(int j=idx;j<arrsz-1;j++){
        arr[j]=arr[j+1];
    }
    arrsz--;
    arr=realloc(arr,arrsz*sizeof(struct StudentRec));
    saveDatabase(fn);
}

void showAll() {
    printf("ID\tName\t\tBatch\tMembership\tRegDate\t\tDOB\t\tInterest\n\n");
    for (int i = 0; i < arrsz; i++) {
        printf("%d\t%s\t%s\t%s\t\t%s\t%s\t%s\n",arr[i].id,arr[i].nm,arr[i].bt,arr[i].mem,arr[i].regdt,arr[i].dob,arr[i].intst);
    }
}


void repBatch(){
    char bx[30],mx[10];
    printf("Batch: ");
    scanf("%s",bx);
    printf("Interest: ");
    scanf("%s",mx);
    printf("Report: \n");
    for(int i=0;i<arrsz;i++){
        if(strcmp(arr[i].bt,bx)==0 && strcmp(arr[i].intst,mx)==0){
            printf("ID:%d Name:%s\n",arr[i].id,arr[i].nm);
        }
    }
}

int main(){
    loadDatabase("members.dat");

    int ch=0,c;
    while(ch!=6){
        printf("\n   Menu----\n1. Register a new student\n2. Update membership type or batch\n3. Delete a student registration\n4. View all registrations\n5. Generate batch-wise reports\n6. Exit\n>> ");
        scanf("%d",&ch);

        if(ch==1){
            struct StudentRec s;
            printf("Student ID: ");
            scanf("%d", &s.id);
            while((c=getchar()), c != '\n' && c != EOF);

            if(checkDup(s.id)) {
                printf("ID already exists!\n");
                continue;
            }

            printf("Full Name: ");
            fgets(s.nm, sizeof(s.nm), stdin);
            s.nm[strcspn(s.nm, "\n")] = 0;

            printf("Batch (CS SE AI CY): ");
            scanf("%s", s.bt);
            while((c=getchar()), c != '\n' && c != EOF);

            printf("Membership Type (IEEE/ACM): ");
            scanf("%s", s.mem);
            while((c=getchar()), c != '\n' && c != EOF);

            printf("Registration Date (YYYY-MM-DD): ");
            scanf("%s", s.regdt);
            while((c=getchar()), c != '\n' && c != EOF);

            printf("Date of Birth (YYYY-MM-DD): ");
            scanf("%s", s.dob);
            while((c=getchar()), c != '\n' && c != EOF);

            printf("Interest in (IEEE/ACM/Both): ");
            scanf("%s", s.intst);
            while((c=getchar()), c != '\n' && c != EOF);

            addStudentMem(s);
            addStudentFile(s, "members.dat");
            printf("Added successfully.\n");

        }

        else if(ch==2){
            int x;
            printf("ID: ");
            scanf("%d",&x);
            updStudent(x,"members.dat");
        }

        else if(ch==3){
            int x;
            printf("ID: ");
            scanf("%d",&x);
            delStudent(x,"members.dat");
        }

        else if(ch==4){
            showAll();
        }

        else if(ch==5){
            repBatch();
        }
    }

    saveDatabase("members.dat");
    if(arr) free(arr);
    return 0;
}
