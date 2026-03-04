#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    float marks;
};

void addStudent() {
    FILE *fp;
    struct Student s;

    fp = fopen("students.txt", "a");
    if(fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%d %s %.2f\n", s.roll, s.name, s.marks);
    fclose(fp);

    printf("Student Added Successfully!\n");
}

void displayStudents() {
    FILE *fp;
    struct Student s;

    fp = fopen("students.txt", "r");
    if(fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\nStudent Records:\n");

    while(fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) != EOF) {
        printf("Roll: %d  Name: %s  Marks: %.2f\n",
               s.roll, s.name, s.marks);
    }

    fclose(fp);
}

void searchStudent() {
    FILE *fp;
    struct Student s;
    int roll, found = 0;

    printf("Enter Roll Number to Search: ");
    scanf("%d", &roll);

    fp = fopen("students.txt", "r");
    if(fp == NULL) {
        printf("No records found!\n");
        return;
    }

    while(fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) != EOF) {
        if(s.roll == roll) {
            printf("Student Found!\n");
            printf("Roll: %d  Name: %s  Marks: %.2f\n",
                   s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }

    if(!found)
        printf("Student not found!\n");

    fclose(fp);
}

void findHighestAndAverage() {
    FILE *fp;
    struct Student s;
    float sum = 0, max = 0, avg;
    int count = 0;

    fp = fopen("students.txt", "r");
    if(fp == NULL) {
        printf("No records found!\n");
        return;
    }

    while(fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) != EOF) {
        sum += s.marks;
        if(count == 0 || s.marks > max)
            max = s.marks;
        count++;
    }

    if(count == 0) {
        printf("No students available!\n");
    } else {
        avg = sum / count;
        printf("Highest Marks: %.2f\n", max);
        printf("Average Marks: %.2f\n", avg);
    }

    fclose(fp);
}

int main() {
    int choice;

    while(1) {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Highest & Average\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: findHighestAndAverage(); break;
            case 5: exit(0);
            default: printf("Invalid Choice!\n");
        }
    }

    return 0;
}