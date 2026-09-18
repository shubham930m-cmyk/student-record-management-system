#include <stdio.h>
#include <string.h>
#include "student.h"

void clearInputBuffer(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        // Clear remaining input
    }
}
int getInteger(const char *message)
{
    int value;
    char extra;

    while (1)
    {
        printf("%s", message);

        if (scanf("%d%c", &value, &extra) == 2 && extra == '\n')
        {
            return value;
        }

        printf("Invalid input! Please enter a valid integer.\n");
        clearInputBuffer();
    }
}
float getFloat(const char *message)
{
    float value;
    char extra;

    while (1)
    {
        printf("%s", message);

        if (scanf("%f%c", &value, &extra) == 2 && extra == '\n')
        {
            return value;
        }

        printf("Invalid input! Please enter a valid number.\n");
        clearInputBuffer();
    }
}
void showMenu(void)
{
    printf("\n========================================\n");
    printf("       STUDENT RECORD MANAGEMENT\n");
    printf("========================================\n");
    printf("1. Add Student\n");
    printf("2. View All Students\n");
    printf("3. Search Student\n");
    printf("4. Update Student\n");
    printf("5. Delete Student\n");
    printf("6. Sort Students\n");
    printf("7. Calculate Statistics\n");
    printf("8. Exit\n");
    printf("========================================\n");
}

int isRollNumberExists(struct Student students[], int count, int rollNo)
{
    for (int i = 0; i < count; i++)
    {
        if (students[i].rollNo == rollNo)
        {
            return 1;
        }
    }

    return 0;
}

void saveStudents(struct Student students[], int count)
{
    FILE *file = fopen(FILE_NAME, "wb");

    if (file == NULL)
    {
        printf("\nError: Could not save student records!\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, file);
    fwrite(students, sizeof(struct Student), count, file);

    fclose(file);
}

void loadStudents(struct Student students[], int *count)
{
    FILE *file = fopen(FILE_NAME, "rb");

    if (file == NULL)
    {
        *count = 0;
        return;
    }

    fread(count, sizeof(int), 1, file);

    if (*count < 0 || *count > MAX_STUDENTS)
    {
        *count = 0;
        fclose(file);
        return;
    }

    fread(students, sizeof(struct Student), *count, file);

    fclose(file);
}

void addStudent(struct Student students[], int *count)
{
    int rollNo;

    if (*count >= MAX_STUDENTS)
    {
        printf("\nStudent limit reached!\n");
        return;
    }

    printf("\n========== ADD STUDENT ==========\n");

    rollNo = getInteger("Enter Roll Number: ");

    if (rollNo <= 0)
    {
        printf("\nInvalid Roll Number!\n");
        return;
    }

    if (isRollNumberExists(students, *count, rollNo))
    {
        printf("\nError: Roll Number %d already exists!\n", rollNo);
        return;
    }

    students[*count].rollNo = rollNo;

    printf("Enter Name: ");
    clearInputBuffer();
    fgets(students[*count].name, sizeof(students[*count].name), stdin);

    students[*count].name[strcspn(students[*count].name, "\n")] = '\0';

    printf("Enter Branch: ");
    fgets(students[*count].branch, sizeof(students[*count].branch), stdin);

    students[*count].branch[strcspn(students[*count].branch, "\n")] = '\0';

   do
{
    students[*count].marks = getFloat("Enter Marks (0-100): ");

    if (students[*count].marks < 0 ||
        students[*count].marks > 100)
    {
        printf("Invalid marks! Please enter a value between 0 and 100.\n");
    }

} while (students[*count].marks < 0 ||
         students[*count].marks > 100);

    (*count)++;

    saveStudents(students, *count);

    printf("\nStudent added successfully!\n");
}

void viewStudents(struct Student students[], int count)
{
    if (count == 0)
    {
        printf("\nNo student records found!\n");
        return;
    }

    printf("\n========== ALL STUDENTS ==========\n\n");

    printf("%-10s %-25s %-25s %-10s\n",
           "Roll No", "Name", "Branch", "Marks");

    printf("---------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++)
    {
        printf("%-10d %-25s %-25s %-10.2f\n",
               students[i].rollNo,
               students[i].name,
               students[i].branch,
               students[i].marks);
    }

    printf("---------------------------------------------------------------------\n");
    printf("Total Students: %d\n", count);
}

void searchStudent(struct Student students[], int count)
{
    int rollNo;
    int found = 0;

    if (count == 0)
    {
        printf("\nNo student records found!\n");
        return;
    }

    rollNo = getInteger("\nEnter Roll Number to search: ");

    for (int i = 0; i < count; i++)
    {
        if (students[i].rollNo == rollNo)
        {
            printf("\n========== STUDENT FOUND ==========\n");
            printf("Roll Number : %d\n", students[i].rollNo);
            printf("Name        : %s\n", students[i].name);
            printf("Branch      : %s\n", students[i].branch);
            printf("Marks       : %.2f\n", students[i].marks);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nStudent with Roll Number %d not found!\n", rollNo);
    }
}

void updateStudent(struct Student students[], int count)
{
    int rollNo;
    int found = 0;

    if (count == 0)
    {
        printf("\nNo student records found!\n");
        return;
    }

    rollNo = getInteger("\nEnter Roll Number to update: ");

    for (int i = 0; i < count; i++)
    {
        if (students[i].rollNo == rollNo)
        {
            printf("\n========== CURRENT DETAILS ==========\n");
            printf("Roll Number : %d\n", students[i].rollNo);
            printf("Name        : %s\n", students[i].name);
            printf("Branch      : %s\n", students[i].branch);
            printf("Marks       : %.2f\n", students[i].marks);

            printf("\n========== ENTER NEW DETAILS ==========\n");

            printf("Enter New Name: ");
            clearInputBuffer();
            fgets(students[i].name, sizeof(students[i].name), stdin);

            students[i].name[strcspn(students[i].name, "\n")] = '\0';

            printf("Enter New Branch: ");
            fgets(students[i].branch, sizeof(students[i].branch), stdin);

            students[i].branch[strcspn(students[i].branch, "\n")] = '\0';

           do
            {
                students[i].marks = getFloat("Enter New Marks (0-100): ");

                if (students[i].marks < 0 ||
                     students[i].marks > 100)
                {
                    printf("Invalid marks! Please enter a value between 0 and 100.\n");
                }

            } while (students[i].marks < 0 ||
                    students[i].marks > 100);

            saveStudents(students, count);

            printf("\nStudent record updated successfully!\n");

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nStudent with Roll Number %d not found!\n", rollNo);
    }
}

void deleteStudent(struct Student students[], int *count)
{
    int rollNo;
    int found = 0;
    char confirm;

    if (*count == 0)
    {
        printf("\nNo student records found!\n");
        return;
    }

    rollNo = getInteger("\nEnter Roll Number to delete: ");

    for (int i = 0; i < *count; i++)
    {
        if (students[i].rollNo == rollNo)
        {
            printf("\n========== STUDENT FOUND ==========\n");
            printf("Roll Number : %d\n", students[i].rollNo);
            printf("Name        : %s\n", students[i].name);
            printf("Branch      : %s\n", students[i].branch);
            printf("Marks       : %.2f\n", students[i].marks);

            printf("\nAre you sure you want to delete this record? (y/n): ");
            scanf(" %c", &confirm);

            if (confirm == 'y' || confirm == 'Y')
            {
                for (int j = i; j < *count - 1; j++)
                {
                    students[j] = students[j + 1];
                }

                (*count)--;

                saveStudents(students, *count);

                printf("\nStudent record deleted successfully!\n");
            }
            else
            {
                printf("\nDeletion cancelled.\n");
            }

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nStudent with Roll Number %d not found!\n", rollNo);
    }
}

void sortStudents(struct Student students[], int count)
{
    int choice;

    if (count == 0)
    {
        printf("\nNo student records found!\n");
        return;
    }

    printf("\n========== SORT STUDENTS ==========\n");
    printf("1. Sort by Marks (Highest to Lowest)\n");
    printf("2. Sort by Name (A-Z)\n");
    printf("3. Sort by Roll Number (Ascending)\n");
    choice = getInteger("Enter your choice: ");

    if (choice < 1 || choice > 3)
    {
        printf("\nInvalid sorting choice!\n");
        return;
    }

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            int shouldSwap = 0;

            if (choice == 1 &&
                students[j].marks < students[j + 1].marks)
            {
                shouldSwap = 1;
            }
            else if (choice == 2 &&
                     strcmp(students[j].name, students[j + 1].name) > 0)
            {
                shouldSwap = 1;
            }
            else if (choice == 3 &&
                     students[j].rollNo > students[j + 1].rollNo)
            {
                shouldSwap = 1;
            }

            if (shouldSwap)
            {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    saveStudents(students, count);

    printf("\nStudents sorted successfully!\n");
}

char getGrade(float marks)
{
    if (marks >= 90)
        return 'A';
    else if (marks >= 80)
        return 'B';
    else if (marks >= 70)
        return 'C';
    else if (marks >= 60)
        return 'D';
    else if (marks >= 40)
        return 'E';
    else
        return 'F';
}

void calculateStatistics(struct Student students[], int count)
{
    if (count == 0)
    {
        printf("\nNo student records found!\n");
        return;
    }

    float totalMarks = 0;
    float highest = students[0].marks;
    float lowest = students[0].marks;

    int passCount = 0;
    int failCount = 0;

    for (int i = 0; i < count; i++)
    {
        totalMarks += students[i].marks;

        if (students[i].marks > highest)
            highest = students[i].marks;

        if (students[i].marks < lowest)
            lowest = students[i].marks;

        if (students[i].marks >= 40)
            passCount++;
        else
            failCount++;
    }

    float average = totalMarks / count;

    printf("\n========== STUDENT STATISTICS ==========\n");
    printf("Total Students : %d\n", count);
    printf("Average Marks  : %.2f\n", average);
    printf("Highest Marks  : %.2f\n", highest);
    printf("Lowest Marks   : %.2f\n", lowest);
    printf("Passed         : %d\n", passCount);
    printf("Failed         : %d\n", failCount);

    printf("\n========== GRADES ==========\n");

    printf("%-10s %-25s %-10s %-10s\n",
           "Roll No", "Name", "Marks", "Grade");

    printf("------------------------------------------------------\n");

    for (int i = 0; i < count; i++)
    {
        printf("%-10d %-25s %-10.2f %-10c\n",
               students[i].rollNo,
               students[i].name,
               students[i].marks,
               getGrade(students[i].marks));
    }

    printf("------------------------------------------------------\n");
}