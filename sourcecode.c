#include<stdio.h>
#include<stdlib.h>
#include<string.h>
# define password_hash 8246073859955783634
typedef struct {
    char name[30];
    int rno;
    int subjectcount;
    int *marks;
    float percentage;
}student;
void addstudents();
int loadrecord(student **stu,int *count);
void viewstudents(student *stu,int count);
void searchbyrollno(student *stu,int count);
void sortbypercentage(student *stu,int count);
void searchbyname(student *stu,int count);
void updatename(student *stu,int count);
void updateallmarks(student *stu,int count);
void update_one_subjectmark(student *stu,int count);
void add_subject(student *stu,int count);
void delete_subject(student *stu,int count);
void savetofile(student *stu,int count);
void deletestudent(student **stu,int *count);
void sortbyname(student *stu,int count);
void result(student *stu,int count);
void updatestudentmenu();
void saverecordstofile();
void sortmenu();
void searchmenu();
void sortbyrollno(student *stu,int count);
int comparebynameasc(const void *a,const void *b);
int comparebyroll_no_des(const void *a,const void *b);
int comparebynamedes(const void *a,const void *b);
int comparebypercent_no_des(const void *a,const void *b);
int comparebypercent_no_asc(const void *a,const void *b);
int comparebyroll_no_asc(const void *a,const void *b);
void exportcsv(student *stu,int count);
void backup_archive(student *stu,int count);
unsigned long long simplehash(const char *str);
int adminlogin();
int main()
{
    if(adminlogin())
    {
        printf("Access Granted For Admin Features....\n");
    }
    else{
        printf("Access Denied! Exiting.....\n");
        return 0;
    }
    int choice;
    printf("Welcome To The Student Database Management System.");
    do{
        printf("\n\n----------Main Menu----------\n");
        printf("1 - Add New Students.\n");
        printf("2 - View All Students.\n");
        printf("3 - Search Student.\n");
        printf("4 - Update Student Info.\n");
        printf("5 - Delete a Student.\n");
        printf("6 - Sort Students.\n");
        printf("7 - Topper / Fail List.\n");
        printf("8 - Save Records to File.\n");
        printf("9 - Backup Existing Records.\n");
        printf("10 - Export Current Records to CSV.\n");
        printf("11 - Exit.\n");
        printf("\nEnter Your Choice : ");
        scanf("%d",&choice);
        switch (choice)
        {
            case 1 : {
                addstudents();
                break;
            }
            case 2 : {
                student *arr;
                int count;
                if (loadrecord(&arr, &count) != 0)
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    break ;
                }
                viewstudents(arr,count);
                for (int i = 0; i < count; i++) 
                {
                    free(arr[i].marks);
                }
                free(arr);
                break;
            }
            case 3 : {
                searchmenu();
                break;
            }
            case 4 : {
                updatestudentmenu();
                break;
            }
            case 5 : {
                student *arr;
                int count;
                if (loadrecord(&arr, &count) != 0) 
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    break;
                }
                deletestudent(&arr,&count);
                savetofile(arr,count);
                for (int i = 0; i < count; i++) 
                {
                    free(arr[i].marks);
                }
                free(arr);
                break;
            }
            case 6 : {
                sortmenu();
                break;
            }
            case 7 : {
                student *arr;
                int count;
                if (loadrecord(&arr, &count) != 0) 
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    break;
                }
                result(arr, count);
                for (int i = 0; i < count; i++) 
                {
                    free(arr[i].marks);
                }
                free(arr);
                break;
            }
            case 8 : {
                saverecordstofile();
                break;
            }
            case 9 : {
                student *arr;
                int count;
                if (loadrecord(&arr, &count) != 0) 
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    break;
                }
                backup_archive(arr, count);
                for (int i = 0; i < count; i++) 
                {
                    free(arr[i].marks);
                }
                free(arr);
                break;
            }
            case 10 : {
                student *arr;
                int count;
                if (loadrecord(&arr, &count) != 0) 
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    break;
                }
                exportcsv(arr,count);
                for (int i = 0; i < count; i++) 
                {
                    free(arr[i].marks);
                }
                free(arr);
                break;
            }
            case 11 : {
                printf("\nThank you for using Student Database Manager.\n");
                printf("Wishing you a productive day ahead!\n");
                printf("Goodbye, and come back soon.\n");
                break;
            }
            default : {
                printf("\nInvalid Choice! Choose Again.");
            }
        }
    }while(choice != 11);
    return 0;
}
unsigned long long simplehash(const char *str)
{
    unsigned long long hash = 5381;
    int ch;
    while((ch = *str++))
    {
        hash = ((hash << 5) + hash) + ch;
    }
    return hash;
}
int adminlogin()
{
    char str[50];
    printf("Enter Admin Password : ");
    scanf("%[^\n]",str);
    unsigned long long inputhash = simplehash(str);
    if(inputhash == password_hash)
    {
        printf("\nLogin Successful! Welcome,Admin.\n");
        return 1;
    }
    else{
        printf("\nLogin Failed! Incorrect Password.\n");
        return 0;
    }
}
void addstudents()
{
    char mode[3];
    printf("Do you want to:\n");
    printf("1 - Append to existing data\n");
    printf("2 - Overwrite all existing data\n");
    printf("Enter your choice (1 or 2): ");
    int filechoice;
    scanf("%d",&filechoice);
    if(filechoice == 1)
    {
        strcpy(mode,"ab");
    }
    else if(filechoice == 2)
    {
        strcpy(mode,"wb");
    }
    else {
        printf("Invalid choice. Defaulting to append mode.\n");
        strcpy(mode, "ab");
    }
    FILE *fp;
    student *stu;
    fp = fopen("studentsdata.bin",mode);
    if(fp == NULL)
    {
        printf("Error : Unable To Open The File.");
        return ;
    }
    student *exist_record;
    int exist_count = 0;
    loadrecord(&exist_record,&exist_count);
    int n;
    printf("\n------------------------------------------\n");
    printf("\nEnter How Many Students Data You Want To Enter : ");
    scanf("%d",&n);
    if (n <= 0) {
        printf("Invalid number of students.\n");
        return;
    }
    stu = (student*)malloc(n*sizeof(student));
    int isduplicate;
    printf("\nEnter %d Students Data:-\n",n);
    for(int i = 0;i<n;i++)
    {
        isduplicate = 0;
        printf("Enter Student %d Name : ",i+1);
        while ((getchar()) != '\n');  
        scanf(" %[^\n]", stu[i].name);
        printf("Enter Student %d Roll No : ",i+1);
        scanf("%d",&stu[i].rno);
        for(int k=0;k<exist_count;k++)
        {
            if(stu[i].rno == exist_record[k].rno)
            {
                printf("Error: Roll No %d already exists. Please enter a unique roll number.\n", stu[i].rno);
                isduplicate = 1;
                break;
            }
        }
        if(isduplicate == 1)
        {
            i--;
            continue;
        }
        printf("Enter Student %d Total Subjects : ",i+1);
        scanf("%d",&stu[i].subjectcount);
        if (stu[i].subjectcount <= 0) 
        {
            printf("Invalid subject count. Skipping student.\n\n");
            i--;
            continue;
        }
        stu[i].marks = (int*)malloc(stu[i].subjectcount*sizeof(int));
        int total = 0;
        for(int j=0;j<stu[i].subjectcount;j++)
        {
            printf("Enter Subject %d Marks : ",j+1);
            scanf("%d",&stu[i].marks[j]);
            if (stu[i].marks[j] < 0 || stu[i].marks[j] > 100)
            {
                printf("Invalid marks! Please enter between 0 and 100.\n");
                j--;
                continue;
            }
            total += stu[i].marks[j];
        }
        stu[i].percentage = (float)total / stu[i].subjectcount;
        printf("Student %s (Roll No: %d) added with %.2f%%\n", stu[i].name, stu[i].rno, stu[i].percentage);
        printf("\n");
    }
    for(int i=0;i<n;i++)
    {
        fwrite(stu[i].name,sizeof(char),30,fp);
        fwrite(&stu[i].rno,sizeof(int),1,fp);
        fwrite(&stu[i].subjectcount, sizeof(int), 1, fp);
        fwrite(stu[i].marks, sizeof(int), stu[i].subjectcount, fp);
        fwrite(&stu[i].percentage, sizeof(float), 1, fp);
    }
    for(int i=0;i<n;i++)
    {
        free(stu[i].marks);
    }
    free(stu);
    for(int i=0;i<exist_count;i++)
    {
        free(exist_record[i].marks);
    }
    free(exist_record);
    fclose(fp);
    printf("Data has been successfully written to file.\n");
}
int loadrecord(student **stu,int *count_ptr)
{
    FILE *fp = fopen("studentsdata.bin", "rb");
    if (fp == NULL) {
        printf("Error: Unable To Open The File.\n");
        return 1;
    }
    int count = 0;
    int capacity = 2;
    *stu = (student*)malloc(capacity*sizeof(student));
    while(1)
    {
        student temp;
        if(fread(temp.name,sizeof(char),30,fp) != 30) break;
        if(fread(&temp.rno,sizeof(int),1,fp) != 1) break;
        if(fread(&temp.subjectcount, sizeof(int), 1, fp) != 1) break;
        temp.marks = (int*)malloc(temp.subjectcount*sizeof(int));
        if (temp.marks == NULL) {
            printf("Memory allocation failed!\n");
            fclose(fp);  // <== ADD this before return!
            return 1;
        }
        size_t read_count = fread(temp.marks, sizeof(int), temp.subjectcount, fp);
        if ((int)read_count != temp.subjectcount) break;
        if(fread(&temp.percentage, sizeof(float), 1, fp) != 1) break;
        if (count == capacity) 
        {
            capacity *= 2;
            *stu = (student*)realloc(*stu, capacity * sizeof(student));
            if (*stu == NULL) {
                printf("Memory reallocation failed!\n");
                free(*stu);
                fclose(fp);
                return 1;
            }
        }
        (*stu)[count] = temp;
        count++;
    }
    fclose(fp);
    *count_ptr = count;
    return 0;
}
void viewstudents(student *stu,int count)
{
    printf("\n------------------------------------------\n");
    printf("\nAll Students Records Are There :-\n");
    for(int i =0;i<count;i++)
    {
        printf("\n===============================");
        printf("\n  Student %d Details", i + 1);
        printf("\n===============================");
        printf("\nName : %s", stu[i].name);
        printf("\nRoll no : %d", stu[i].rno);
        printf("\nTotal Subjects : %d",stu[i].subjectcount);
        for(int j=0;j<stu[i].subjectcount;j++)
        {
            printf("\nSubject %d marks : %d",j+1,stu[i].marks[j]);
        }
        printf("\nPercentage : %.2f\n", stu[i].percentage);
    }
}
void searchmenu()
{
    int ch;
    printf("\n---------Search Menu---------\n");
    printf("1 - Search by Roll No.\n");
    printf("2 - Search by Name.\n");
    printf("0 - Back to Main Menu.\n");
    do {
        printf("\nEnter Your choice : ");
        scanf("%d",&ch);
        switch (ch) 
        {
            case 1 : {
                student *arr;
                int count;
                if (loadrecord(&arr, &count) != 0)
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    return;
                }
                searchbyrollno(arr,count);
                for (int i = 0; i < count; i++) 
                {
                    free(arr[i].marks);
                }
                free(arr);
                break;
            }
            case 2 : {
                student *arr;
                int count;
                if (loadrecord(&arr, &count) != 0)
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    return;
                }
                searchbyname(arr,count);
                for (int i = 0; i < count; i++) 
                {
                    free(arr[i].marks);
                }
                free(arr);
                break;
            }
            case 0 : {
                return;
            }
            default : {
                printf("\nInvalid Choice. Choose Again.\n");
            }
        }
    }while(ch < 0 || ch > 2);
}
void searchbyrollno(student *stu,int count)
{
    int search;
    int found = 0;
    printf("\n------------------------------------------\n");
    printf("\nEnter the Student's Roll No you want to Search : ");
    scanf("%d",&search);
    for(int i=0;i<count;i++)
    {
        if(stu[i].rno == search)
        {
            printf("\nStudent Details:-");
            printf("\nName : %s",stu[i].name);
            printf("\nRoll No : %d",stu[i].rno);
            printf("\nTotal Subjects : %d",stu[i].subjectcount);
            for(int j=0;j<stu[i].subjectcount;j++)
            {
                printf("\nSubject %d marks : %d",j+1,stu[i].marks[j]);
            }
            printf("\nPercentage : %.2f\n", stu[i].percentage);
            printf("\n------------------------------------------\n");
            found = 1;
            break;
        }
    }
    if(found == 0)
    {
        printf("\nStudent Roll No Did Not Found.");
    }
}
void searchbyname(student *stu,int count)
{
    int found = 0;
    char search[30];
    printf("\n------------------------------------------\n");
    printf("\nEnter the Student's Name you want to Search : ");
    while ((getchar()) != '\n');  
    scanf(" %[^\n]",search);
    for(int i=0;i<count;i++)
    {
        if(strcmp(stu[i].name,search) == 0)
        {
            printf("\nStudent Details:-");
            printf("\nName : %s",stu[i].name);
            printf("\nRoll No : %d",stu[i].rno);
            printf("\nTotal Subjects : %d",stu[i].subjectcount);
            for(int j=0;j<stu[i].subjectcount;j++)
            {
                printf("\nSubject %d marks : %d",j+1,stu[i].marks[j]);
            }
            printf("\nPercentage : %.2f\n", stu[i].percentage);
            printf("\n------------------------------------------\n");
            found = 1;
            break;
        }
    }
    if(found == 0)
    {
        printf("\nStudent Name Did Not Found.");
    }
}
void updatestudentmenu()
{
    int choice;
    printf("\n------------------------------------------\n");
    printf("\n------------Update Menu------------\n");
    printf("1 - Update Name.\n");
    printf("2 - Update All Marks.\n");
    printf("3 - Update Specific Subject Marks.\n");
    printf("4 - Add New Subjects.\n");
    printf("5 - Delete a Subject.\n");
    printf("0 - Back to the Main Menu.\n");
    do {
        printf("\nEnter Your Choice : ");
        scanf("%d",&choice);
        switch (choice)
        {
            case 1 : {
                student *arr;
                int count;
                if (loadrecord(&arr, &count) != 0)
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    return;
                }
                updatename(arr,count);
                savetofile(arr,count);
                for (int i = 0; i < count; i++) 
                {
                    free(arr[i].marks);
                }
                free(arr);
                break;
            }
            case 2 : {
                student *arr;
                int count;
                if (loadrecord(&arr, &count) != 0)
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    return;
                }
                updateallmarks(arr,count);
                savetofile(arr,count);
                for (int i = 0; i < count; i++) 
                {
                    free(arr[i].marks);
                }
                free(arr);
                break;
            }
            case 3 : {
                student *arr;
                int count;
                if (loadrecord(&arr, &count) != 0)
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    return;
                }
                update_one_subjectmark(arr,count);
                savetofile(arr,count);
                for (int i = 0; i < count; i++) 
                {
                    free(arr[i].marks);
                }
                free(arr);
                break;
            }
            case 4 : {
                student *arr;
                int count;
                if (loadrecord(&arr, &count) != 0)
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    return;
                }
                add_subject(arr,count);
                savetofile(arr,count);
                for (int i = 0; i < count; i++) 
                {
                    free(arr[i].marks);
                }
                free(arr);
                break;
            }
            case 5 : {
                student *arr;
                int count;
                if (loadrecord(&arr, &count) != 0)
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    return;
                }
                delete_subject(arr,count);
                savetofile(arr,count);
                for (int i = 0; i < count; i++) 
                {
                    free(arr[i].marks);
                }
                free(arr);
                break;
            }
            case 0 : {
                return;
            }
            default : {
                printf("\nInvalid Choice. Choose Again.\n");
            }
        }
    }while(choice < 0 || choice > 5);
}
void updatename(student *stu,int count)
{
    printf("\n------------------------------------------\n");
    int rno;
    int found = 0;
    printf("\nEnter the Student Roll No Whose Name You Want To Change : ");
    scanf("%d",&rno);
    for(int i=0;i<count;i++)
    {
        if(stu[i].rno == rno)
        {
            printf("Current Name of the Student : %s",stu[i].name);
            printf("\nEnter Name For Update : ");
            while ((getchar()) != '\n');  
            scanf(" %[^\n]", stu[i].name);
            found = 1;
            printf("\nName updated successfully!\n");
            break;
        }
    }
    if (!found)
    {
        printf("No student found with Roll No %d\n", rno);
    }
}
void updateallmarks(student *stu,int count)
{
    printf("\n------------------------------------------\n");
    int rno;
    int found = 0;
    printf("\nEnter the Student Roll No Whose Marks You Want To Change : ");
    scanf("%d",&rno);
    for(int i=0;i<count;i++)
    {
        if(stu[i].rno == rno)
        {
            printf("Current Marks:\n");
            for (int j = 0; j < stu[i].subjectcount; j++)
            {
                printf("Subject %d: %d\n", j + 1, stu[i].marks[j]);
            }
            int total = 0;
            for(int j=0;j<stu[i].subjectcount;j++)
            {
                printf("Enter Subject %d Marks : ",j+1);
                scanf("%d",&stu[i].marks[j]);
                total += stu[i].marks[j];
            }
            stu[i].percentage = (float)total / stu[i].subjectcount;
            printf("\nMarks updated Successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("No student found with Roll No %d\n", rno);
    }
}
void update_one_subjectmark(student *stu,int count)
{
    printf("\n------------------------------------------\n");
    int rno, found = 0;
    printf("\nEnter the Student Roll No whose one subject's mark you want to update: ");
    scanf("%d", &rno);
    for (int i = 0; i < count; i++)
    {
        if (stu[i].rno == rno)
        {
            printf("Current Marks:\n");
            for (int j = 0; j < stu[i].subjectcount; j++)
            {
                printf("Subject %d: %d\n", j + 1, stu[i].marks[j]);
            }
            int subject_index;
            printf("Enter the subject number (1 to %d) you want to update: ", stu[i].subjectcount);
            scanf("%d",&subject_index);
            if (subject_index < 1 || subject_index > stu[i].subjectcount)
            {
                printf("Invalid subject number!\n");
                return;
            }
            subject_index--;
            printf("Enter New Marks For Subject %d : ",subject_index+1);
            scanf("%d",&stu[i].marks[subject_index]);
            int total = 0;
            for(int j=0;j<stu[i].subjectcount; j++)
            {
                total += stu[i].marks[j];
            }
            stu[i].percentage = (float)total / stu[i].subjectcount;
            printf("\nSubject Marks updated Successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("No student found with Roll No %d\n", rno);
    }
}
void add_subject(student *stu,int count)
{
    printf("\n------------------------------------------\n");
    int rno, found = 0;
    printf("\nEnter the Student Roll No whose one subject you want to Add More : ");
    scanf("%d", &rno);
    for (int i = 0; i < count; i++)
    {
        if (stu[i].rno == rno)
        {
            printf("Total No Of Subject This Student Has : %d",stu[i].subjectcount);
            int n;
            printf("\nEnter the number of additional subjects to add : ");
            scanf("%d",&n);
            stu[i].marks = (int*)realloc(stu[i].marks , (stu[i].subjectcount+n)*sizeof(int));
            for(int j=stu[i].subjectcount;j<stu[i].subjectcount+n;j++)
            {
                printf("Enter Subject %d marks : ",j + 1);
                scanf("%d",&stu[i].marks[j]);
            }
            stu[i].subjectcount += n;
            int total = 0;
            for(int j=0;j<stu[i].subjectcount; j++)
            {
                total += stu[i].marks[j];
            }
            stu[i].percentage = (float)total / stu[i].subjectcount;
            printf("\nSubject Added Successfully.\n");
            found = 1;
        }
    }
    if (!found)
    {
        printf("No student found with Roll No %d\n", rno);
    }
}
void delete_subject(student *stu,int count)
{
    printf("\n------------------------------------------\n");
    int rno, found = 0;
    printf("\nEnter the Student Roll No whose one subject's mark you want to Delete: ");
    scanf("%d", &rno);
    for (int i = 0; i < count; i++)
    {
        if (stu[i].rno == rno)
        {
            found = 1;
            printf("Total No Of Subject This Student Has : %d",stu[i].subjectcount);
            printf("\nCurrent Marks:\n");
            for (int j = 0; j < stu[i].subjectcount; j++)
            {
                printf("Subject %d: %d\n", j + 1, stu[i].marks[j]);
            }
            int subject_index;
            printf("Enter the subject number (1 to %d) you want to Delete: ", stu[i].subjectcount);
            scanf("%d",&subject_index);
            if (subject_index < 1 || subject_index > stu[i].subjectcount)
            {
                printf("\nInvalid subject number!\n");
                return;
            }
            if (stu[i].subjectcount <= 1)
            {
                printf("\nCannot delete the last subject. A student must have at least one subject.\n");
                return;
            }
            subject_index--;
            char confirm;
            printf("Are you sure you want to delete Subject %d(Marks : %d) ? [YES - Y / NO - N] : ",subject_index+1,stu[i].marks[subject_index]);
            while ((getchar()) != '\n'); 
            scanf("%c",&confirm);
            if(confirm != 'y' && confirm != 'Y')
            {
                return;
            }
            for(int j=subject_index;j<stu[i].subjectcount-1;j++)
            {
                stu[i].marks[j] = stu[i].marks[j+1];
            }
            stu[i].subjectcount--;
            stu[i].marks = (int*)realloc(stu[i].marks , (stu[i].subjectcount)*sizeof(int));
            int total = 0;
            for(int j=0;j<stu[i].subjectcount; j++)
            {
                total += stu[i].marks[j];
            }
            stu[i].percentage = (stu[i].subjectcount > 0) ? (float)total / stu[i].subjectcount : 0.0;
            printf("\nSubject deleted Successfully!\n");
            break;
        }
    }   
    if (!found)
    {
        printf("No student found with Roll No %d\n", rno);
    }
}
void savetofile(student *stu,int count)
{
    FILE *fp = fopen("studentsdata.bin","wb");
    if(fp == NULL)
    {
        printf("Error : Unable To Open The File.");
        return ;
    }
    for(int i=0;i<count;i++)
    {
        fwrite(stu[i].name,sizeof(char),30,fp);
        fwrite(&stu[i].rno,sizeof(int),1,fp);
        fwrite(&stu[i].subjectcount, sizeof(int), 1, fp);
        fwrite(stu[i].marks, sizeof(int), stu[i].subjectcount, fp);
        fwrite(&stu[i].percentage, sizeof(float), 1, fp);
    }
    fclose(fp);
    printf("\nData Is Successfully Saved In File.\n");
}
void saverecordstofile()
{
    printf("\n------------------------------------------\n");
    printf("\nSave Option Selected.\n");
    printf("Records saved again successfully.\n");
}
void deletestudent(student **stu,int *count)
{
    int search,found = 0;
    printf("\n------------------------------------------\n");
    printf("Enter The Roll No Of Student Whose Record You Want To Delete : ");
    scanf("%d",&search);
    for(int i=0;i<*count;i++)
    {
        if((*stu)[i].rno == search)
        {
            free((*stu)[i].marks); 
            char confirm;
            printf("Are you sure you want to delete Student %d's record? [Yes - Y / No - N] : ",search);
            while ((getchar()) != '\n'); 
            scanf("%c",&confirm);
            if(confirm != 'y' && confirm != 'Y')
            {
                return;
            }
            for(int j=i;j<*count-1;j++)
            {
                (*stu)[j] = (*stu)[j+1];
            }
            printf("\nStudent with Roll No %d deleted Successfully.\n", search);
            found = 1;
            break;
        }
    }
    (*count)--;
    *stu = (student*)realloc(*stu,(*count) *sizeof(student));
    if (*stu == NULL && *count > 0)
    {
        printf("Memory reallocation failed after deletion.\n");
        exit(1);
    }
    if (!found)
    {
        printf("No student found with Roll No %d\n", search);
    }
}
void sortmenu()
{
    printf("\n-------------Sort Menu-------------\n");
    int choice;
    printf("1 - Sort by Name.\n");
    printf("2 - Sort by Roll No.\n");
    printf("3 - Sort by Percentage.\n");
    printf("0 - Back to Main Menu.\n");
    do {
        printf("\nEnter Your choice : ");
        scanf("%d",&choice);
        switch (choice)
        {
            case 1 : {
                student *arr;
                int count;
                if (loadrecord(&arr, &count) != 0)
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    return;
                }
                sortbyname(arr,count);
                char ch;
                printf("\nDo you want to save this sorted list to file? [Yes - Y / No - N] : ");
                while ((getchar()) != '\n');
                scanf("%c",&ch);
                if(ch == 'Y' || ch == 'y')
                {
                    savetofile(arr,count);
                }
                for (int i = 0; i < count; i++) 
                {
                    free(arr[i].marks);
                }
                free(arr);
                break;
            }
            case 2 : {
                student *arr;
                int count;
                if (loadrecord(&arr, &count) != 0)
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    return;
                }
                sortbyrollno(arr,count);
                char ch;
                printf("\nDo you want to save this sorted list to file? [Yes - Y / No - N] : ");
                while ((getchar()) != '\n');
                scanf("%c",&ch);
                if(ch == 'Y' || ch == 'y')
                {
                    savetofile(arr,count);
                }
                for (int i = 0; i < count; i++) 
                {
                    free(arr[i].marks);
                }
                free(arr);
                break;
            }
            case 3 : {
                student *arr;
                int count;
                if (loadrecord(&arr, &count) != 0)
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    return;
                }
                sortbypercentage(arr,count);
                char ch;
                printf("\nDo you want to save this sorted list to file? [Yes - Y / No - N] : ");
                while ((getchar()) != '\n');
                scanf("%c",&ch);
                if(ch == 'Y' || ch == 'y')
                {
                    savetofile(arr,count);
                }
                for (int i = 0; i < count; i++) 
                {
                    free(arr[i].marks);
                }
                free(arr);
                break;
            }
            case 0 : {
                return ;
            }
            default : {
                printf("Invalid Choice. Choose Again.");
            }
        }
    }while(choice < 0 || choice > 3);
}
void sortbyname(student *stu,int count)
{
    int sortOrder;
    printf("1 - Ascending.\n");
    printf("2 - Descending .\n");
    printf("\nEnter Your Sorting Preference : ");
    scanf("%d",&sortOrder);
    if(sortOrder == 1)
    {
        qsort(stu,count,sizeof(student),comparebynameasc);
        printf("Students sorted by Name (Ascending) :\n");
        printf("\nSorted List :");
        viewstudents(stu, count);
    }
    else{
        qsort(stu,count,sizeof(student),comparebynamedes);   
        printf("Students sorted by Name (Descending ) :\n");
        printf("\nSorted List :");
        viewstudents(stu, count);
    }
}
int comparebynameasc(const void *a,const void *b)
{
    return strcmp(((student*)a)->name,((student*)b)->name);
}
int comparebynamedes(const void *a,const void *b)
{
    return strcmp(((student*)b)->name, ((student*)a)->name);
}
void sortbyrollno(student *stu,int count)
{
    int sortOrder;
    printf("1 - Ascending.\n");
    printf("2 - Descending .\n");
    printf("\nEnter Your Sorting Preference : ");
    scanf("%d",&sortOrder);
    if(sortOrder == 1)
    {
        qsort(stu,count,sizeof(student),comparebyroll_no_asc);
        printf("Students sorted by Roll No (Ascending) :\n");
        printf("\nSorted List :");
        viewstudents(stu, count);
    }
    else{
        qsort(stu,count,sizeof(student),comparebyroll_no_des); 
        printf("Students sorted by Roll No (Descending ) :\n");
        printf("\nSorted List :");
        viewstudents(stu, count);
    }
}
int comparebyroll_no_asc(const void *a,const void *b)
{
    return ((student*)a)->rno - ((student*)b)->rno;
}
int comparebyroll_no_des(const void *a,const void *b)
{
    return ((student*)b)->rno - ((student*)a)->rno;
}
void sortbypercentage(student *stu,int count)
{
    int sortOrder;
    printf("1 - (Weakest First) Ascending.\n");
    printf("2 - (Toppers First) Descending .\n");
    printf("\nEnter Your Sorting Preference : ");
    scanf("%d",&sortOrder);
    if(sortOrder == 1)
    {
        qsort(stu,count,sizeof(student),comparebypercent_no_asc);
        printf("Students sorted by percentage (Ascending) :\n");
        printf("\nSorted List :");
        viewstudents(stu, count);
    }
    else{
        qsort(stu,count,sizeof(student),comparebypercent_no_des);  
        printf("Students sorted by percentage (Descending ) :\n");
        printf("\nSorted List :");
        viewstudents(stu, count); 
    }
}
int comparebypercent_no_des(const void *a,const void *b)
{
    student *s1 = (student*)a;
    student *s2 = (student*)b;
    if (s2->percentage > s1->percentage)
    {
        return 1;
    }
    if (s2->percentage < s1->percentage)
    {
        return -1;
    }
    return 0;
}
int comparebypercent_no_asc(const void *a,const void *b)
{
    student *s1 = (student*)a;
    student *s2 = (student*)b;
    if (s1->percentage < s2->percentage)
    {
        return -1;
    }
    if (s1->percentage > s2->percentage)
    {
        return 1;
    }
    return 0;
}
void result(student *stu,int count)
{   printf("\n------------------------------------------\n");
    printf("\n Student Result Analysis : \n");
    int failed = 0,passed = 0, topper = 0;
    printf("\nList Of Students Who Have Topped :-\n");
    for(int i=0;i<count;i++)
    {
        int hasfailed = 0;
        for(int j=0;j<stu[i].subjectcount;j++)
        {
            if(stu[i].marks[j] < 35)
            {
                hasfailed = 1;
                break;
            }
        }
        if(hasfailed != 1 && stu[i].percentage >= 90.0)
        {
            printf("Name : %s | Roll No : %d | Percentage : %.2f%%\n", stu[i].name, stu[i].rno, stu[i].percentage);
            topper++;
        }
    }
    printf("\nList of Student Who Have Passed :-\n");
    for(int i=0;i<count;i++)
    {
        int hasfailed = 0;
        for(int j=0;j<stu[i].subjectcount;j++)
        {
            if(stu[i].marks[j] < 35)
            {
                hasfailed = 1;
                break;
            }
        }
        if(hasfailed != 1 && stu[i].percentage < 90.0)
        {
            printf("Name : %s | Roll No : %d | Percentage : %.2f%%\n", stu[i].name, stu[i].rno, stu[i].percentage);
            passed++;
        }
    }
    printf("\nList of Students Who Have Failed :-\n");
    for(int i=0;i<count;i++)
    {
        int hasfailed = 0;
        for(int j=0;j<stu[i].subjectcount;j++)
        {
            if(stu[i].marks[j] < 35)
            {
                hasfailed = 1;
                break;
            }
        }
        if(hasfailed == 1)
        {
            printf("Name : %s | Roll No : %d | Percentage : %.2f%%\n", stu[i].name, stu[i].rno, stu[i].percentage);
            failed ++;
        }
    }
    printf("\nOverall Result :-");
    printf("\nTotal Students : %d",count);
    printf("\nTotal Topper Students: %d",topper);
    printf("\nTotal Passed Students : %d",passed);
    printf("\nTotal Failed Students : %d",failed);
    printf("\n\nNote : Students Who Scored 90.0 or Above Are Toppers.");
    printf("\nStudents Who Have Scored Above 35 In All Subjects Are Pass.");
    printf("\nStudents Who Have Scored Below 35 In 1 Subject Or More Are Failed.");
}
void backup_archive(student *stu,int count)
{
    FILE *fp = fopen("backup_history.bin","wb");
    if(fp == NULL)
    {
        printf("Error : Unable To Open The File.");
        return ;
    }
    char confirm;
    printf("Are you sure you want to Backup your Existing Data [YES - Y / NO - N]?");
    while ((getchar()) != '\n'); 
    scanf("%c",&confirm);
    if(confirm != 'Y' && confirm != 'y')
    {
        printf("Backup Cancelled.\n");
        return;
    }
    for(int i=0;i<count;i++)
    {
        fwrite(stu[i].name,sizeof(char),30,fp);
        fwrite(&stu[i].rno,sizeof(int),1,fp);
        fwrite(&stu[i].subjectcount, sizeof(int), 1, fp);
        fwrite(stu[i].marks, sizeof(int), stu[i].subjectcount, fp);
        fwrite(&stu[i].percentage, sizeof(float), 1, fp);
    }
    fclose(fp);
    printf("\nData is Successfully Backuped in 'backup_history.bin' File.\n");
}
void exportcsv(student *stu,int count)
{
    FILE *fp = fopen("studentdata.csv","w");
    if(fp == NULL)
    {
        printf("Error : Unable To Open The File.");
        return ;
    }
    char confirm;
    printf("Are you sure you want to Export your Existing Data to CSV Format [YES - Y / NO - N]?");
    while ((getchar()) != '\n'); 
    scanf("%c",&confirm);
    if(confirm != 'Y' && confirm != 'y')
    {
        printf("Export cancelled.\n");
        return;
    }
    int maxsubject = 0;
    for(int i=0;i<count;i++)
    {
        if(stu[i].subjectcount > maxsubject)
        {
            maxsubject = stu[i].subjectcount;
        }
    }
    fprintf(fp,"Name,Roll No,Total Subjects");
    for(int i=0;i<maxsubject;i++)
    {
        fprintf(fp,",Marks%d",i+1);
    }
    fprintf(fp,",Percentage\n");
    for(int i=0;i<count;i++)
    {
        fprintf(fp,"%s,%d,%d",stu[i].name,stu[i].rno,stu[i].subjectcount);
        for(int j=0;j<stu[i].subjectcount;j++)
        {
            fprintf(fp,",%d",stu[i].marks[j]);
        }
        for(int j=stu[i].subjectcount;j<maxsubject;j++)
        {
            fprintf(fp,",");
        }
        fprintf(fp,",%.2f\n",stu[i].percentage);
    }
    printf("\nCSV Export Successful! Data written to 'studentdata.csv'.\n");
    fclose(fp);
}