#ifndef STUDENT_H
#define STUDENT_H

#define MAX_STUDENTS 100
#define FILE_NAME "students.dat"

struct Student
{
    int rollNo;
    char name[50];
    char branch[50];
    float marks;
};

/* Menu */
void showMenu(void);

/* Student operations */
void addStudent(struct Student students[], int *count);
void viewStudents(struct Student students[], int count);
void searchStudent(struct Student students[], int count);
void updateStudent(struct Student students[], int count);
void deleteStudent(struct Student students[], int *count);

/* Additional features */
void sortStudents(struct Student students[], int count);
void calculateStatistics(struct Student students[], int count);
char getGrade(float marks);

/* File handling */
void saveStudents(struct Student students[], int count);
void loadStudents(struct Student students[], int *count);

/* Validation */
int isRollNumberExists(struct Student students[], int count, int rollNo);
void clearInputBuffer(void);
int getInteger(const char *message);
float getFloat(const char *message);

#endif