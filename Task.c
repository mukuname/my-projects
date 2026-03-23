/*
 ============================================================================
 Name        : Task.c
 Author      : Enock Mukuna
 Version     : 1.0
 Date        : February 20, 2026
 Description : Mission Planner - A command-line goal management system written in standard C.
               This program allows users to create, track, and manage goals with due dates,
               mark them as completed, and generate progress reports. It demonstrates the use
               of dynamic memory allocation, file input/output, and time/date manipulation
               using the C standard library.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INITIAL_CAPACITY 5
#define DATE_BUFFER 20

typedef struct {
    char title[100];
    char description[300];
    time_t due_date;
    int completed;
} Goal;

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

time_t parseDate(const char *dateStr) {
    struct tm tm_date = {0};
    int year, month, day;

    if (sscanf(dateStr, "%d-%d-%d", &year, &month, &day) != 3) {
        return (time_t)-1;
    }

    tm_date.tm_year = year - 1900;
    tm_date.tm_mon = month - 1;
    tm_date.tm_mday = day;
    tm_date.tm_hour = 0;
    tm_date.tm_min = 0;
    tm_date.tm_sec = 0;

    return mktime(&tm_date);
}

void formatDate(time_t date, char *buffer, size_t size) {
    struct tm *tm_info = localtime(&date);
    strftime(buffer, size, "%Y-%m-%d", tm_info);
}

void addGoal(Goal **goals, int *count, int *capacity) {
    if (*count >= *capacity) {
        *capacity *= 2;
        *goals = realloc(*goals, (*capacity) * sizeof(Goal));
        if (*goals == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }
    }

    Goal *g = &((*goals)[*count]);

    printf("Enter goal title: ");
    fgets(g->title, sizeof(g->title), stdin);
    g->title[strcspn(g->title, "\n")] = 0;

    printf("Enter description: ");
    fgets(g->description, sizeof(g->description), stdin);
    g->description[strcspn(g->description, "\n")] = 0;

    char dateStr[DATE_BUFFER];
    printf("Enter due date (YYYY-MM-DD): ");
    fgets(dateStr, DATE_BUFFER, stdin);
    dateStr[strcspn(dateStr, "\n")] = 0;

    g->due_date = parseDate(dateStr);
    if (g->due_date == (time_t)-1) {
        printf("Invalid date format. Goal not added.\n");
        return;
    }

    g->completed = 0;
    (*count)++;

    printf("Goal added successfully.\n");
}

void viewGoals(Goal *goals, int count) {
    if (count == 0) {
        printf("No goals available.\n");
        return;
    }

    time_t now = time(NULL);

    for (int i = 0; i < count; i++) {
        char dateBuffer[DATE_BUFFER];
        formatDate(goals[i].due_date, dateBuffer, DATE_BUFFER);

        double daysLeft = difftime(goals[i].due_date, now) / (60 * 60 * 24);

        printf("\nGoal #%d\n", i + 1);
        printf("Title: %s\n", goals[i].title);
        printf("Description: %s\n", goals[i].description);
        printf("Due Date: %s\n", dateBuffer);
        printf("Days Remaining: %.0f\n", daysLeft);
        printf("Status: %s\n", goals[i].completed ? "Completed" : "In Progress");
    }
}

void markCompleted(Goal *goals, int count) {
    if (count == 0) {
        printf("No goals to mark.\n");
        return;
    }

    int choice;
    printf("Enter goal number to mark completed: ");
    scanf("%d", &choice);
    clearInputBuffer();

    if (choice < 1 || choice > count) {
        printf("Invalid selection.\n");
        return;
    }

    goals[choice - 1].completed = 1;
    printf("Goal marked as completed.\n");
}

void saveGoals(Goal *goals, int count) {
    FILE *file = fopen("goals.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\n", goals[i].title);
        fprintf(file, "%s\n", goals[i].description);
        fprintf(file, "%ld\n", (long)goals[i].due_date);
        fprintf(file, "%d\n", goals[i].completed);
    }

    fclose(file);
    printf("Goals saved to file.\n");
}

void loadGoals(Goal **goals, int *count, int *capacity) {
    FILE *file = fopen("goals.txt", "r");
    if (file == NULL) {
        printf("No saved goals found.\n");
        return;
    }

    *count = 0;

    while (!feof(file)) {
        if (*count >= *capacity) {
            *capacity *= 2;
            *goals = realloc(*goals, (*capacity) * sizeof(Goal));
            if (*goals == NULL) {
                printf("Memory allocation failed.\n");
                exit(1);
            }
        }

        Goal *g = &((*goals)[*count]);

        if (!fgets(g->title, sizeof(g->title), file)) break;
        g->title[strcspn(g->title, "\n")] = 0;

        if (!fgets(g->description, sizeof(g->description), file)) break;
        g->description[strcspn(g->description, "\n")] = 0;

        long due;
        if (fscanf(file, "%ld\n", &due) != 1) break;
        g->due_date = (time_t)due;

        if (fscanf(file, "%d\n", &g->completed) != 1) break;

        (*count)++;
    }

    fclose(file);
    printf("Goals loaded successfully.\n");
}

void progressReport(Goal *goals, int count) {
    if (count == 0) {
        printf("No goals available.\n");
        return;
    }

    int completed = 0;
    for (int i = 0; i < count; i++) {
        if (goals[i].completed)
            completed++;
    }

    double percent = ((double)completed / count) * 100.0;

    printf("\nProgress Report\n");
    printf("Total Goals: %d\n", count);
    printf("Completed: %d\n", completed);
    printf("Completion Rate: %.2f%%\n", percent);
}

int main() {
    Goal *goals = malloc(INITIAL_CAPACITY * sizeof(Goal));
    int count = 0;
    int capacity = INITIAL_CAPACITY;
    int choice;

    if (goals == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    while (1) {
        printf("\nMission Planner Menu\n");
        printf("1. Add Goal\n");
        printf("2. View Goals\n");
        printf("3. Mark Goal as Completed\n");
        printf("4. Save Goals\n");
        printf("5. Load Goals\n");
        printf("6. Progress Report\n");
        printf("7. Exit\n");
        printf("Choose an option: ");

        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                addGoal(&goals, &count, &capacity);
                break;
            case 2:
                viewGoals(goals, count);
                break;
            case 3:
                markCompleted(goals, count);
                break;
            case 4:
                saveGoals(goals, count);
                break;
            case 5:
                loadGoals(&goals, &count, &capacity);
                break;
            case 6:
                progressReport(goals, count);
                break;
            case 7:
                free(goals);
                printf("Goodbye.\n");
                return 0;
            default:
                printf("Invalid option.\n");
        }
    }
}
