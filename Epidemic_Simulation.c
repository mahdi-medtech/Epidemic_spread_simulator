#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_POP 500

#define SUSCEPTIBLE 0
#define INFECTED    1
#define RECOVERED   2
#define VACCINATED  3
#define DEAD        4
#define BASE_MORTALITY 0.5f
#define OVERLOAD_MORTALITY 10.0f


typedef struct {
    int state;
    int daysInfected;
} Person;

typedef struct {
    int peakInfected;
    int peakDay;
    int totalInfected;
    int totalDead;
    int duration;
} Result;



Result runSimulation(
    Person population[],
    float R0,
    int mode,
    int populationSize,
    int infectionProbability,
    int contactRate,
    int recoveryDays,
    int totalDays,
    int initialInfected,
    int vaccinationPercent,
    int hospitalCapacity,
    int showDaily
) {
    int peakInfected = 0;
    int peakDay = 0;
    int totalDead = 0;
    int duration = 0;
    int totalEverInfected = initialInfected;
    FILE *file = NULL;

    if (showDaily) {
        file = fopen("simulation_output.csv", "w");
        if (file == NULL) {
            printf("Error creating CSV file.\n");
            exit(1);
        }
        fprintf(file, "Day,S,I,R,V,D\n");
    }

    /* ---------------- Initialize Population ---------------- */
    for (int i = 0; i < populationSize; i++) {
        population[i].state = SUSCEPTIBLE;
        population[i].daysInfected = 0;
    }

    /* ---------------- Initial Infection ---------------- */
    int count = 0;
    while (count < initialInfected) {
        int index = rand() % populationSize;

        if (population[index].state == SUSCEPTIBLE) {
            population[index].state = INFECTED;
            count++;
        }
    }

    /* ---------------- Vaccination ---------------- */
    if (mode == 2) {
        int vaccinatedCount = (vaccinationPercent * populationSize) / 100;
        count = 0;

        while (count < vaccinatedCount) {
            int index = rand() % populationSize;

            if (population[index].state == SUSCEPTIBLE) {
                population[index].state = VACCINATED;
                count++;
            }
        }
    }

    /* ---------------- Daily Simulation ---------------- */
    for (int day = 1; day <= totalDays; day++) {

        int newInfections[MAX_POP] = {0};

        /* Spread */
        for (int i = 0; i < populationSize; i++) {

            if (population[i].state == INFECTED) {

                int effectiveContactRate = contactRate;

                if (mode == 3)
                    effectiveContactRate = contactRate / 2;

                for (int c = 0; c < effectiveContactRate; c++) {

                    int randomPerson = rand() % populationSize;

                    if (population[randomPerson].state == SUSCEPTIBLE) {
                        if (rand() % 100 < infectionProbability) {
                            newInfections[randomPerson] = 1;
                        }
                    }
                }
            }
        }

        /* Apply New Infections */
        for (int i = 0; i < populationSize; i++) {
            if (newInfections[i] == 1) {
                population[i].state = INFECTED;
                population[i].daysInfected = 0;
                totalEverInfected++;
            }
        }

        // Count current infected once (for hospital capacity check)
        int currentInfected = 0;
        for (int i = 0; i < populationSize; i++) {
            if (population[i].state == INFECTED)
                currentInfected++;
        }

        /* Recovery */
        for (int i = 0; i < populationSize; i++) {
            if (population[i].state == INFECTED) {
                population[i].daysInfected++;

                // During recovery check
                if (population[i].daysInfected >= recoveryDays) {

                    float effectiveMortality = BASE_MORTALITY;

                    if (currentInfected > hospitalCapacity) {
                        effectiveMortality = OVERLOAD_MORTALITY;
                    }

                    if (rand() % 100 < effectiveMortality) {
                        population[i].state = DEAD;
                        totalDead++;
                    } else {
                        population[i].state = RECOVERED;
                    }
                }
            }
        }

        /* Count SIR */
        int sCount = 0, iCount = 0, rCount = 0, vCount = 0, dCount = 0;

        for (int i = 0; i < populationSize; i++) {
            if (population[i].state == SUSCEPTIBLE)
                sCount++;
            else if (population[i].state == INFECTED)
                iCount++;
            else if (population[i].state == RECOVERED)
                rCount++;
            else if (population[i].state == VACCINATED)
                vCount++;
            else if (population[i].state == DEAD)
                dCount++;

            if (iCount > 0)
                duration = day;
        }

        float Rt = R0 * ((float)sCount / populationSize);

        if (showDaily) {
            printf("Day %-3d | S:%-4d I:%-4d R:%-4d V:%-4d D:%-4d | Rt: %.2f\n",
                   day, sCount, iCount, rCount, vCount, dCount, Rt);

            fprintf(file, "%d,%d,%d,%d,%d,%d\n",
                    day, sCount, iCount, rCount, vCount, dCount);

            if (iCount == 0) {
                break;
            }
        }

        if (iCount > peakInfected) {
            peakInfected = iCount;
            peakDay = day;
        }
    }

    Result r;
    r.peakInfected = peakInfected;
    r.peakDay = peakDay;
    r.totalInfected = totalEverInfected;
    r.totalDead = totalDead;
    r.duration = duration;

    if (showDaily) {
        fclose(file);
    }

    return r;
}


int main() {

    srand(time(0));

    int populationSize;
    int infectionProbability;
    int contactRate;
    int recoveryDays;
    int totalDays;
    int initialInfected;
    int mode;
    int vaccinationPercent = 0;
    int hospitalCapacity;

    printf("\n============================================================\n");
    printf("   EPIDEMIOLOGICAL SPREAD & CONTAINMENT SIMULATION SYSTEM\n");
    printf("============================================================\n\n");

    printf("--------------- INPUT PARAMETERS ---------------\n");

    printf("Enter Population Size: ");
    scanf("%d", &populationSize);

    if (populationSize <= 0 || populationSize > MAX_POP) {
        printf("Invalid population size.\n");
        return 0;
    }

    printf("Enter Infection Probability (0-100): ");
    scanf("%d", &infectionProbability);

    printf("Enter Contact Rate per Day: ");
    scanf("%d", &contactRate);

    printf("Enter Recovery Days: ");
    scanf("%d", &recoveryDays);

    printf("Enter Total Simulation Days: ");
    scanf("%d", &totalDays);

    printf("Enter Initial Infected Count: ");
    scanf("%d", &initialInfected);

    if (initialInfected > populationSize) {
        printf("Initial infected cannot exceed population.\n");
        return 0;
    }

    printf("Enter Hospital Capacity: ");
    scanf("%d", &hospitalCapacity);

    printf("\nSelect Containment Mode:\n");
    printf("1. No Containment\n");
    printf("2. Vaccination\n");
    printf("3. Lockdown\n\n");
    printf("Enter choice: ");
    scanf("%d", &mode);

    int effectiveContactRate = contactRate;

    if (mode == 3) {
        effectiveContactRate = contactRate / 2;
    }

    if (mode == 2) {
        printf("Enter Vaccination Percentage (0-100): ");
        scanf("%d", &vaccinationPercent);
    }

    float R0 = (infectionProbability / 100.0)
               * effectiveContactRate
               * recoveryDays;

    int trials;

    printf("Enter Number of Simulation Trials: ");
    scanf("%d", &trials);

    if (trials <= 0) {
        printf("Invalid number of trials.\n");
        return 0;
    }

    printf("------------------------------------------------\n\n");

    printf("\n================ EPIDEMIC METRICS ================\n");
    printf("Basic Reproduction Number (R0): %.2f\n", R0);

    if (R0 > 1)
        printf("Status: Epidemic Growth Expected (R0 > 1)\n");
    else if (R0 == 1)
        printf("Status: Stable Spread (R0 = 1)\n");
    else
        printf("Status: Infection Will Die Out (R0 < 1)\n");

    if (R0 > 1) {
        float herd = (1 - (1 / R0)) * 100;
        printf("Herd Immunity Threshold: %.2f%%\n", herd);
    }

    Person population[MAX_POP];
    float avgPeakBase = 0;
    float avgPeakContain = 0;
    float avgTotalBase = 0;
    float avgTotalContain = 0;
    float avgDeadBase = 0;
    float avgDeadContain = 0;
    float avgDurationBase = 0;
    float avgDurationContain = 0;
    float avgPeakDayBase = 0;
    float avgPeakDayContain = 0;

    for (int t = 0; t < trials; t++) {

        Result base = runSimulation(
            population,
            R0,
            1, populationSize,
            infectionProbability,
            contactRate,
            recoveryDays,
            totalDays,
            initialInfected,
            0,
            hospitalCapacity,
            0
        );

        Result containment = runSimulation(
            population,
            R0,
            mode,
            populationSize,
            infectionProbability,
            contactRate,
            recoveryDays,
            totalDays,
            initialInfected,
            vaccinationPercent,
            hospitalCapacity,
            0
        );

        avgPeakBase += base.peakInfected;
        avgPeakContain += containment.peakInfected;

        avgTotalBase += base.totalInfected;
        avgTotalContain += containment.totalInfected;

        avgDeadBase += base.totalDead;
        avgDeadContain += containment.totalDead;

        avgDurationBase += base.duration;
        avgDurationContain += containment.duration;

        avgPeakDayBase += base.peakDay;
        avgPeakDayContain += containment.peakDay;
    }

    avgPeakBase /= trials;
    avgPeakContain /= trials;

    avgTotalBase /= trials;
    avgTotalContain /= trials;

    avgDeadBase /= trials;
    avgDeadContain /= trials;

    avgDurationBase /= trials;
    avgDurationContain /= trials;

    avgPeakDayBase /= trials;
    avgPeakDayContain /= trials;

    float peakDayReduction =
        ((avgPeakDayBase - avgPeakDayContain)
         / avgPeakDayBase) * 100;

    float durationReduction =
        ((avgDurationBase - avgDurationContain)
         / avgDurationBase) * 100;

    float deathReduction = 0;
    if (avgDeadBase > 0)
        deathReduction =
            ((avgDeadBase - avgDeadContain)
             / avgDeadBase) * 100;

    printf("--------------------------------------------------\n");
    printf("\n------ Sample Simulation (Detailed Daily Output) ------\n\n");

    runSimulation(
        population,
        R0,
        mode, populationSize,
        infectionProbability,
        contactRate,
        recoveryDays,
        totalDays,
        initialInfected,
        vaccinationPercent,
        hospitalCapacity,
        1
    );

    printf("\n=================================================\n");
    printf("               SIMULATION SUMMARY\n");
    printf("=================================================\n");

    printf("\n----------- Averaged Over %d Trials -----------\n\n", trials);

    printf("Average Peak (Without Containment): %.2f\n", avgPeakBase);
    printf("Average Peak (With Containment): %.2f\n\n", avgPeakContain);

    printf("Average Total Infected (Without Containment): %.2f\n", avgTotalBase);
    printf("Average Total Infected (With Containment): %.2f\n\n", avgTotalContain);

    printf("Average Peak Day (Without Containment): %.2f\n", avgPeakDayBase);
    printf("Average Peak Day (With Containment): %.2f\n\n", avgPeakDayContain);

    printf("Average Duration (Without Containment): %.2f days\n", avgDurationBase);
    printf("Average Duration (With Containment): %.2f days\n\n", avgDurationContain);

    printf("Average Total Dead (Without Containment): %.2f\n", avgDeadBase);
    printf("Average Total Dead (With Containment): %.2f\n\n", avgDeadContain);

    float totalReduction =
        ((avgTotalBase - avgTotalContain)
         / avgTotalBase) * 100;

    float peakReduction =
        ((avgPeakBase - avgPeakContain)
         / avgPeakBase) * 100;

    printf("\n---------------- COMPARISON ----------------\n");

    printf("Average Peak Reduction: %.2f%%\n", peakReduction);
    printf("Average Total Infection Reduction: %.2f%%\n", totalReduction);
    printf("Average Peak Day Reduction: %.2f%%\n", peakDayReduction);
    printf("Average Duration Reduction: %.2f%%\n", durationReduction);
    printf("Average Death Reduction: %.2f%%\n", deathReduction);
    printf("---------------------------------------------\n");

    return 0;
}
