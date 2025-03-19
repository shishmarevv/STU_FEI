#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name_surname[100];
    int year;
    float gpa;
} student;

student *input_file(char *filename, int *student_count) {
    FILE *f = fopen(filename, "r");
    if(f == NULL){
        printf("Error opening file\n");
        return NULL;
    }
    fscanf(f, "%d", student_count);
    fgetc(f);
    student *students = (student *)malloc(*student_count * sizeof(student));
    for(int i = 0; i < *student_count; i++){
        char ch; int j = 0;
        while((ch = fgetc(f)) != '\n'){
            students[i].name_surname[j] = ch;
            j++;
        }
        students[i].name_surname[j] = '\0';
        fscanf(f, "%d %f", &students[i].year, &students[i].gpa);
        ch = fgetc(f);
    }
    return students;
    fclose(f);
}

void print_students(student *students, int student_count){
    for(int i = 0; i < student_count; i++){
        printf("%s; %d; %.2f\n", students[i].name_surname, students[i].year, students[i].gpa);
    }
}

student *best_student(student *students, int student_count, int year){
    student *best = NULL;
    for (int i = 0; i < student_count; i++){
        if (students[i].year == year){
            if (best == NULL || best->gpa < students[i].gpa){
                best = &students[i];
            }
        }
    }
    return best;
}

int main(){
    student *students, *best;
    int student_count;
    students = input_file("students.txt", &student_count);
    if(students == NULL){
        printf("Error reading file\n");
        return -1;
    }
    print_students(students, student_count);
    int year = 2;
    best = best_student(students, student_count, year);
    if (best == NULL){
        printf("No student found %d year\n", year);
        return -2;
    }
    printf("Best student %d year: %s\n", year,  best->name_surname);
    return 0;
}