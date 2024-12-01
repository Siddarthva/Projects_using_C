#include<stdio.h>
#include<stdlib.h>

struct attendance {
    char day[10];
    char DSA;
    char DSALAB;
    char OOPS;
    char OOPSLAB;
    char DLDC;
    char DLDCLAB;
    char MATH;
    char MAD;
    char UHV;
    char EXCEL;
    char SKILL;
    char PLACEMENT;
};

struct attended {
    int DSA;
    int DSALAB;
    int OOPS;
    int OOPSLAB;
    int DLDC;
    int DLDCLAB;
    int MATH;
    int MAD;
    int UHV;
    int EXCEL;
    int SKILL;
    int PLACEMENT;

    int totalDSA;
    int totalDSALAB;
    int totalOOPS;
    int totalOOPSLAB;
    int totalDLDC;
    int totalDLDCLAB;
    int totalMATH;
    int totalMAD;
    int totalUHV;
    int totalEXCEL;
    int totalSKILL;
    int totalPLACEMENT;
};

int read_previous_month(struct attended *log, FILE *file) {
    if (fscanf(file, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", 
               &log->DSA, &log->totalDSA, &log->DSALAB, &log->totalDSALAB, 
               &log->OOPS, &log->totalOOPS, &log->OOPSLAB, &log->totalOOPSLAB, 
               &log->DLDC, &log->totalDLDC, &log->DLDCLAB, &log->totalDLDCLAB, 
               &log->MATH, &log->totalMATH, &log->MAD, &log->totalMAD, 
               &log->UHV, &log->totalUHV, &log->EXCEL, &log->totalEXCEL, 
               &log->SKILL, &log->totalSKILL, &log->PLACEMENT, &log->totalPLACEMENT) != 24) {
        return 0;
    }
    return 1;
}

void write_attendance_percentage(struct attended log, char day[]) {
    FILE *file = fopen("attendance_percentage.txt", "a");
    if (file == NULL) return;
    fprintf(file, "Day: %s\n", day);
    if (log.totalDSA > 0) fprintf(file, "DSA Attendance: %.2f%%\n", (float)log.DSA / log.totalDSA * 100);
    if (log.totalDSALAB > 0) fprintf(file, "DSALAB Attendance: %.2f%%\n", (float)log.DSALAB / log.totalDSALAB * 100);
    if (log.totalOOPS > 0) fprintf(file, "OOPS Attendance: %.2f%%\n", (float)log.OOPS / log.totalOOPS * 100);
    if (log.totalOOPSLAB > 0) fprintf(file, "OOPSLAB Attendance: %.2f%%\n", (float)log.OOPSLAB / log.totalOOPSLAB * 100);
    if (log.totalDLDC > 0) fprintf(file, "DLDC Attendance: %.2f%%\n", (float)log.DLDC / log.totalDLDC * 100);
    if (log.totalDLDCLAB > 0) fprintf(file, "DLDCLAB Attendance: %.2f%%\n", (float)log.DLDCLAB / log.totalDLDCLAB * 100);
    if (log.totalMATH > 0) fprintf(file, "MATH Attendance: %.2f%%\n", (float)log.MATH / log.totalMATH * 100);
    if (log.totalMAD > 0) fprintf(file, "MAD Attendance: %.2f%%\n", (float)log.MAD / log.totalMAD * 100);
    if (log.totalUHV > 0) fprintf(file, "UHV Attendance: %.2f%%\n", (float)log.UHV / log.totalUHV * 100);
    if (log.totalEXCEL > 0) fprintf(file, "EXCEL Attendance: %.2f%%\n", (float)log.EXCEL / log.totalEXCEL * 100);
    if (log.totalSKILL > 0) fprintf(file, "SKILL Attendance: %.2f%%\n", (float)log.SKILL / log.totalSKILL * 100);
    if (log.totalPLACEMENT > 0) fprintf(file, "PLACEMENT Attendance: %.2f%%\n", (float)log.PLACEMENT / log.totalPLACEMENT * 100);
    fprintf(file, "--------------------------------------\n");
    fclose(file);
}

int main() {
    struct attendance entry;
    struct attended log;
    FILE *file;

    file = fopen("attendance_log.txt", "r");
    if (file == NULL) {
        file = fopen("attendance_log.txt", "w");
        if (file == NULL) return 1;
        log = (struct attended){0};
    } else {
        if (!read_previous_month(&log, file)) {
            fclose(file);
            return 1;
        }
        fclose(file);
    }

    printf("Enter the day: ");
    scanf("%s", entry.day);

    printf("1. Data Structures and Applications (A/P/N): ");
    scanf(" %c", &entry.DSA);

    printf("2. Data Structures Lab with C (A/P/N): ");
    scanf(" %c", &entry.DSALAB);

    printf("3. Object Oriented Programming Concepts (A/P/N): ");
    scanf(" %c", &entry.OOPS);

    printf("4. OOP Lab (A/P/N): ");
    scanf(" %c", &entry.OOPSLAB);

    printf("5. Digital Logic Designs and Computer Organizations (A/P/N): ");
    scanf(" %c", &entry.DLDC);

    printf("6. DLDC Lab (A/P/N): ");
    scanf(" %c", &entry.DLDCLAB);

    printf("7. Linear Algebra and Statistics for Machine Learning (A/P/N): ");
    scanf(" %c", &entry.MATH);

    printf("8. Mobile Application Development (A/P/N): ");
    scanf(" %c", &entry.MAD);

    printf("9. UHV (A/P/N): ");
    scanf(" %c", &entry.UHV);

    printf("10. Data Analytics Using Excel (A/P/N): ");
    scanf(" %c", &entry.EXCEL);

    printf("11. Skill Lab (MERN) (A/P/N): ");
    scanf(" %c", &entry.SKILL);

    printf("12. Aptitude/Placement (A/P/N): ");
    scanf(" %c", &entry.PLACEMENT);

    if (entry.DSA == 'P') log.DSA++;
    if (entry.DSA != 'N') log.totalDSA++;
    if (entry.DSALAB == 'P') log.DSALAB++;
    if (entry.DSALAB != 'N') log.totalDSALAB++;
    if (entry.OOPS == 'P') log.OOPS++;
    if (entry.OOPS != 'N') log.totalOOPS++;
    if (entry.OOPSLAB == 'P') log.OOPSLAB++;
    if (entry.OOPSLAB != 'N') log.totalOOPSLAB++;
    if (entry.DLDC == 'P') log.DLDC++;
    if (entry.DLDC != 'N') log.totalDLDC++;
    if (entry.DLDCLAB == 'P') log.DLDCLAB++;
    if (entry.DLDCLAB != 'N') log.totalDLDCLAB++;
    if (entry.MATH == 'P') log.MATH++;
    if (entry.MATH != 'N') log.totalMATH++;
    if (entry.MAD == 'P') log.MAD++;
    if (entry.MAD != 'N') log.totalMAD++;
    if (entry.UHV == 'P') log.UHV++;
    if (entry.UHV != 'N') log.totalUHV++;
    if (entry.EXCEL == 'P') log.EXCEL++;
    if (entry.EXCEL != 'N') log.totalEXCEL++;
    if (entry.SKILL == 'P') log.SKILL++;
    if (entry.SKILL != 'N') log.totalSKILL++;
    if (entry.PLACEMENT == 'P') log.PLACEMENT++;
    if (entry.PLACEMENT != 'N') log.totalPLACEMENT++;

    write_attendance_percentage(log, entry.day);

    file = fopen("attendance_log.txt", "w");
    if (file == NULL) return 1;

    fprintf(file, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", 
            log.DSA, log.totalDSA, log.DSALAB, log.totalDSALAB, 
            log.OOPS, log.totalOOPS, log.OOPSLAB, log.totalOOPSLAB, 
            log.DLDC, log.totalDLDC, log.DLDCLAB, log.totalDLDCLAB, 
            log.MATH, log.totalMATH, log.MAD, log.totalMAD, 
            log.UHV, log.totalUHV, log.EXCEL, log.totalEXCEL, 
            log.SKILL, log.totalSKILL, log.PLACEMENT, log.totalPLACEMENT);

    fclose(file);

    printf("Attendance updated and saved successfully.\n");
    
    return 0;
}
