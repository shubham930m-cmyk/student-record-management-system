#include <stdio.h>
#include "student.h"

int main(void)
{
    struct Student students[MAX_STUDENTS];
    int count = 0;
    int choice;

    loadStudents(students, &count);

    do
    {
        showMenu();
        choice = getInteger("Enter your choice: ");

        switch (choice)
        {
            case 1:
                addStudent(students, &count);
                break;

            case 2:
                viewStudents(students, count);
                break;

            case 3:
                searchStudent(students, count);
                break;

            case 4:
                updateStudent(students, count);
                break;

            case 5:
                deleteStudent(students, &count);
                break;

            case 6:
                sortStudents(students, count);
                break;

            case 7:
                calculateStatistics(students, count);
                break;

            case 8:
                printf("\nThank you for using Student Record Management System!\n");
                break;

            default:
                printf("\nInvalid choice! Please enter 1-8.\n");
        }

    } while (choice != 8);

    return 0;
}