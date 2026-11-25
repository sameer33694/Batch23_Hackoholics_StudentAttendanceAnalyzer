#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define FILE_NAME "attendance.dat"

/* Structure to store student information */
struct Student
{
    int rollNo;
    char name[50];
    char course[30];
    int semester;
    int totalClasses;
    int attendedClasses;
    float attendancePercentage;
};

/* Global array */
struct Student students[MAX_STUDENTS];
int studentCount = 0;

/* Function declarations */
void loadFromFile();
void saveToFile();
void addStudent();
void displayAllStudents();
void searchStudent();
void showBelow75();
void highestLowestAttendance();
void calculateClassAverage();
void calculateAttendance(struct Student *s);
void showStatus(float percentage);
int rollNumberExists(int rollNo);
void clearInputBuffer();

/* Main function */
int main()
{
    int choice;

    /* Load old records when program starts */
    loadFromFile();

    do
    {
        printf("\n");
        printf("=====================================================\n");
        printf("        COLLEGE STUDENT ATTENDANCE ANALYZER\n");
        printf("=====================================================\n");
        printf("1. Add Student Details\n");
        printf("2. Display Complete Attendance Report\n");
        printf("3. Search Student by Roll Number\n");
        printf("4. Show Students Below 75%% Attendance\n");
        printf("5. Find Highest and Lowest Attendance\n");
        printf("6. Calculate Average Attendance of Class\n");
        printf("7. Save Records to File\n");
        printf("8. Exit\n");
        printf("=====================================================\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayAllStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                showBelow75();
                break;

            case 5:
                highestLowestAttendance();
                break;

            case 6:
                calculateClassAverage();
                break;

            case 7:
                saveToFile();
                printf("\nRecords saved successfully!\n");
                break;

            case 8:
                saveToFile();
                printf("\nRecords saved successfully.\n");
                printf("Thank you for using Attendance Analyzer!\n");
                break;

            default:
                printf("\nInvalid choice! Please select from 1 to 8.\n");
        }

    } while (choice != 8);

    return 0;
}


/* ---------------------------------------------------
   Function to clear invalid input from keyboard buffer
   --------------------------------------------------- */
void clearInputBuffer()
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
        /* Clear buffer */
    }
}


/* ---------------------------------------------------
   Calculate attendance percentage
   --------------------------------------------------- */
void calculateAttendance(struct Student *s)
{
    if (s->totalClasses > 0)
    {
        s->attendancePercentage =
            ((float)s->attendedClasses / s->totalClasses) * 100.0f;
    }
    else
    {
        s->attendancePercentage = 0.0f;
    }
}


/* ---------------------------------------------------
   Display attendance status
   --------------------------------------------------- */
void showStatus(float percentage)
{
    if (percentage >= 75.0f)
    {
        printf("Eligible");
    }
    else if (percentage >= 65.0f)
    {
        printf("Warning");
    }
    else
    {
        printf("Critical Shortage");
    }
}


/* ---------------------------------------------------
   Check whether roll number already exists
   --------------------------------------------------- */
int rollNumberExists(int rollNo)
{
    int i;

    for (i = 0; i < studentCount; i++)
    {
        if (students[i].rollNo == rollNo)
        {
            return 1;
        }
    }

    return 0;
}


/* ---------------------------------------------------
   Add a new student
   --------------------------------------------------- */
void addStudent()
{
    struct Student s;

    if (studentCount >= MAX_STUDENTS)
    {
        printf("\nMaximum student limit reached!\n");
        return;
    }

    printf("\n=====================================================\n");
    printf("                 ADD NEW STUDENT\n");
    printf("=====================================================\n");

    printf("Enter Roll Number: ");
    scanf("%d", &s.rollNo);

    /* Prevent duplicate roll numbers */
    if (rollNumberExists(s.rollNo))
    {
        printf("\nA student with Roll Number %d already exists!\n",
               s.rollNo);
        return;
    }

    clearInputBuffer();

    printf("Enter Student Name: ");
    fgets(s.name, sizeof(s.name), stdin);

    /* Remove newline added by fgets */
    s.name[strcspn(s.name, "\n")] = '\0';

    printf("Enter Course (Example: B.Tech CSE): ");
    fgets(s.course, sizeof(s.course), stdin);

    s.course[strcspn(s.course, "\n")] = '\0';

    printf("Enter Semester: ");
    scanf("%d", &s.semester);

    printf("Enter Total Number of Classes: ");
    scanf("%d", &s.totalClasses);

    if (s.totalClasses <= 0)
    {
        printf("\nTotal classes must be greater than 0.\n");
        return;
    }

    printf("Enter Number of Classes Attended: ");
    scanf("%d", &s.attendedClasses);

    if (s.attendedClasses < 0 ||
        s.attendedClasses > s.totalClasses)
    {
        printf("\nInvalid attendance!\n");
        printf("Classes attended cannot be negative or greater "
               "than total classes.\n");
        return;
    }

    /* Calculate percentage */
    calculateAttendance(&s);

    /* Add student to array */
    students[studentCount] = s;
    studentCount++;

    /* Automatically save after adding student */
    saveToFile();

    printf("\nStudent added successfully!\n");

    printf("\nAttendance Percentage : %.2f%%\n",
           s.attendancePercentage);

    printf("Attendance Status     : ");
    showStatus(s.attendancePercentage);
    printf("\n");
}


/* ---------------------------------------------------
   Display all student records
   --------------------------------------------------- */
void displayAllStudents()
{
    int i;

    if (studentCount == 0)
    {
        printf("\nNo student records available.\n");
        return;
    }

    printf("\n");
    printf("===============================================================================================\n");
    printf("                              COMPLETE ATTENDANCE REPORT\n");
    printf("===============================================================================================\n");

    printf("%-8s %-20s %-15s %-5s %-8s %-10s %-12s %-18s\n",
           "Roll",
           "Name",
           "Course",
           "Sem",
           "Total",
           "Attended",
           "Attendance",
           "Status");

    printf("-----------------------------------------------------------------------------------------------\n");

    for (i = 0; i < studentCount; i++)
    {
        printf("%-8d %-20s %-15s %-5d %-8d %-10d %-11.2f%% ",
               students[i].rollNo,
               students[i].name,
               students[i].course,
               students[i].semester,
               students[i].totalClasses,
               students[i].attendedClasses,
               students[i].attendancePercentage);

        showStatus(students[i].attendancePercentage);

        printf("\n");
    }

    printf("===============================================================================================\n");

    printf("\nTotal Number of Students: %d\n", studentCount);
}


/* ---------------------------------------------------
   Search student using roll number
   --------------------------------------------------- */
void searchStudent()
{
    int rollNo;
    int i;
    int found = 0;

    if (studentCount == 0)
    {
        printf("\nNo student records available.\n");
        return;
    }

    printf("\nEnter Roll Number to Search: ");
    scanf("%d", &rollNo);

    for (i = 0; i < studentCount; i++)
    {
        if (students[i].rollNo == rollNo)
        {
            printf("\n=====================================================\n");
            printf("                  STUDENT FOUND\n");
            printf("=====================================================\n");

            printf("Roll Number          : %d\n",
                   students[i].rollNo);

            printf("Student Name         : %s\n",
                   students[i].name);

            printf("Course               : %s\n",
                   students[i].course);

            printf("Semester             : %d\n",
                   students[i].semester);

            printf("Total Classes        : %d\n",
                   students[i].totalClasses);

            printf("Classes Attended     : %d\n",
                   students[i].attendedClasses);

            printf("Attendance Percentage: %.2f%%\n",
                   students[i].attendancePercentage);

            printf("Attendance Status    : ");
            showStatus(students[i].attendancePercentage);
            printf("\n");

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nStudent with Roll Number %d not found.\n",
               rollNo);
    }
}


/* ---------------------------------------------------
   Display students having attendance below 75%
   --------------------------------------------------- */
void showBelow75()
{
    int i;
    int found = 0;

    if (studentCount == 0)
    {
        printf("\nNo student records available.\n");
        return;
    }

    printf("\n");
    printf("==========================================================================\n");
    printf("                    STUDENTS BELOW 75%% ATTENDANCE\n");
    printf("==========================================================================\n");

    printf("%-10s %-25s %-15s %-20s\n",
           "Roll No.",
           "Name",
           "Attendance",
           "Status");

    printf("--------------------------------------------------------------------------\n");

    for (i = 0; i < studentCount; i++)
    {
        if (students[i].attendancePercentage < 75.0f)
        {
            printf("%-10d %-25s %-14.2f%% ",
                   students[i].rollNo,
                   students[i].name,
                   students[i].attendancePercentage);

            showStatus(students[i].attendancePercentage);
            printf("\n");

            found = 1;
        }
    }

    if (!found)
    {
        printf("\nAll students have 75%% or more attendance.\n");
    }

    printf("==========================================================================\n");
}


/* ---------------------------------------------------
   Find highest and lowest attendance
   --------------------------------------------------- */
void highestLowestAttendance()
{
    int i;
    int highestIndex = 0;
    int lowestIndex = 0;

    if (studentCount == 0)
    {
        printf("\nNo student records available.\n");
        return;
    }

    for (i = 1; i < studentCount; i++)
    {
        if (students[i].attendancePercentage >
            students[highestIndex].attendancePercentage)
        {
            highestIndex = i;
        }

        if (students[i].attendancePercentage <
            students[lowestIndex].attendancePercentage)
        {
            lowestIndex = i;
        }
    }

    printf("\n=====================================================\n");
    printf("              ATTENDANCE ANALYSIS\n");
    printf("=====================================================\n");

    printf("\nHIGHEST ATTENDANCE\n");
    printf("------------------\n");

    printf("Roll Number : %d\n",
           students[highestIndex].rollNo);

    printf("Name        : %s\n",
           students[highestIndex].name);

    printf("Attendance  : %.2f%%\n",
           students[highestIndex].attendancePercentage);

    printf("\nLOWEST ATTENDANCE\n");
    printf("-----------------\n");

    printf("Roll Number : %d\n",
           students[lowestIndex].rollNo);

    printf("Name        : %s\n",
           students[lowestIndex].name);

    printf("Attendance  : %.2f%%\n",
           students[lowestIndex].attendancePercentage);

    printf("=====================================================\n");
}


/* ---------------------------------------------------
   Calculate class average attendance
   --------------------------------------------------- */
void calculateClassAverage()
{
    int i;
    float sum = 0.0f;
    float average;

    if (studentCount == 0)
    {
        printf("\nNo student records available.\n");
        return;
    }

    for (i = 0; i < studentCount; i++)
    {
        sum += students[i].attendancePercentage;
    }

    average = sum / studentCount;

    printf("\n=====================================================\n");
    printf("                 CLASS STATISTICS\n");
    printf("=====================================================\n");

    printf("Total Students          : %d\n", studentCount);
    printf("Average Class Attendance: %.2f%%\n", average);

    printf("Overall Class Status    : ");

    if (average >= 75.0f)
    {
        printf("Good\n");
    }
    else if (average >= 65.0f)
    {
        printf("Needs Improvement\n");
    }
    else
    {
        printf("Critical\n");
    }

    printf("=====================================================\n");
}


/* ---------------------------------------------------
   Save records to binary file
   --------------------------------------------------- */
void saveToFile()
{
    FILE *file;

    file = fopen(FILE_NAME, "wb");

    if (file == NULL)
    {
        printf("\nError: Unable to save records to file.\n");
        return;
    }

    /* Save number of students */
    fwrite(&studentCount, sizeof(int), 1, file);

    /* Save student structures */
    fwrite(students,
           sizeof(struct Student),
           studentCount,
           file);

    fclose(file);
}


/* ---------------------------------------------------
   Load records when program starts
   --------------------------------------------------- */
void loadFromFile()
{
    FILE *file;

    file = fopen(FILE_NAME, "rb");

    /* File may not exist during first execution */
    if (file == NULL)
    {
        studentCount = 0;
        return;
    }

    /* Read number of students */
    if (fread(&studentCount, sizeof(int), 1, file) != 1)
    {
        studentCount = 0;
        fclose(file);
        return;
    }

    /* Safety check */
    if (studentCount < 0 || studentCount > MAX_STUDENTS)
    {
        studentCount = 0;
        fclose(file);
        return;
    }

    /* Read student records */
    if (studentCount > 0)
    {
        fread(students,
              sizeof(struct Student),
              studentCount,
              file);
    }

    fclose(file);
}