#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SUBJECTS 20
#define MAX_NAME_LENGTH 50

struct attended {
    int present;
    int total;
};

struct subject {
    char name[MAX_NAME_LENGTH];
    struct attended attendance;
};

struct day_attendance {
    char day[10];
    char status[MAX_SUBJECTS]; 
};

void initialize_subjects(struct subject *subjects, int count) {
    for (int i = 0; i < count; i++) {
        subjects[i].attendance.present = 0;
        subjects[i].attendance.total = 0;
    }
}

void save_subjects_to_file(struct subject *subjects, int count) {
    FILE *file = fopen("subjects.txt", "w");
    if (!file) {
        printf("Error: Could not open subjects file for writing.\n");
        return;
    }
    fprintf(file, "%d\n", count);
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d %d\n", subjects[i].name, 
                subjects[i].attendance.present, 
                subjects[i].attendance.total);
    }
    fclose(file);
}

int load_subjects_from_file(struct subject *subjects) {
    FILE *file = fopen("subjects.txt", "r");
    if (!file) {
        return 0; 
    }
    int count;
    fscanf(file, "%d\n", &count);
    for (int i = 0; i < count; i++) {
        fscanf(file, "%s %d %d\n", subjects[i].name, 
               &subjects[i].attendance.present, 
               &subjects[i].attendance.total);
    }
    fclose(file);
    return count;
}

void record_attendance(struct subject *subjects, int count, struct day_attendance *entry) {
    printf("Enter the day: ");
    scanf("%s", entry->day);

    printf("Select the subjects for today (Enter subject numbers separated by space, -1 to stop):\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s\n", i + 1, subjects[i].name);
    }

    int subject_index;
    while (1) {
        printf("Enter subject number (-1 to stop): ");
        scanf("%d", &subject_index);
        if (subject_index == -1) break;

        if (subject_index < 1 || subject_index > count) {
            printf("Invalid subject number. Try again.\n");
            continue;
        }

        subject_index--; 
        printf("%s (A/P): ", subjects[subject_index].name);
        scanf(" %c", &entry->status[subject_index]);

        if (entry->status[subject_index] == 'P') {
            subjects[subject_index].attendance.present++;
        }
        subjects[subject_index].attendance.total++;
    }
}

void write_attendance_log(struct subject *subjects, int count, char day[]) {
    FILE *file = fopen("attendance_percentage.txt", "a");
    if (!file) {
        printf("Error: Could not open attendance percentage file.\n");
        return;
    }
    fprintf(file, "Day: %s\n", day);
    for (int i = 0; i < count; i++) {
        if (subjects[i].attendance.total > 0) {
            fprintf(file, "%s Attendance: %.2f%%\n", subjects[i].name,
                    (float)subjects[i].attendance.present / subjects[i].attendance.total * 100);
        }
    }
    fprintf(file, "--------------------------------------\n");
    fclose(file);
}

int main() {
    struct subject subjects[MAX_SUBJECTS];
    struct day_attendance entry;

    int subject_count = load_subjects_from_file(subjects);
    if (subject_count == 0) {
        printf("Enter the number of subjects: ");
        scanf("%d", &subject_count);

        printf("Enter the names of the subjects:\n");
        for (int i = 0; i < subject_count; i++) {
            printf("Subject %d: ", i + 1);
            scanf("%s", subjects[i].name);
        }
        initialize_subjects(subjects, subject_count);
        save_subjects_to_file(subjects, subject_count);
    }

    record_attendance(subjects, subject_count, &entry);
    write_attendance_log(subjects, subject_count, entry.day);
    save_subjects_to_file(subjects, subject_count);

    printf("Attendance updated and saved successfully.\n");
    return 0;
}
