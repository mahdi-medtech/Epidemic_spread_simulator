# Epidemiological Spread Simulation & Containment Optimization System

## Overview

This project implements a stochastic, compartment-based SIRD (Susceptible–Infected–Recovered–Deceased) epidemiological model to simulate disease spread within a configurable population.

It is designed to analyze outbreak dynamics under uncertainty while incorporating real-world constraints such as healthcare capacity and intervention strategies.

---

## Core Features

- Stochastic disease spread modeling  
- SIRD compartmental framework  
- Configurable epidemiological parameters:
  - Contact rate  
  - Infection probability  
  - Recovery duration  
  - Mortality rate  

- Dynamic state transitions (S → I → R/D)  
- Healthcare capacity constraints  
- Multi-scenario simulation capability  

---

## Containment & Optimization

The system includes intervention strategies such as:

- Vaccination modeling  
- Lockdown simulation  
- Healthcare capacity limits  

Mortality rates dynamically increase when infection levels exceed system capacity, enabling realistic overload scenario analysis.

---

## Epidemiological Metrics

The model computes:

- Basic reproduction number (R₀)  
- Effective reproduction number (Rₜ)  
- Peak infection levels  
- Total affected population  
- Mortality outcomes  
- Multi-trial statistical analysis  

---

## System Design

The simulation is structured around:

- State-based modeling (SIRD transitions)  
- Probabilistic decision-making  
- Iterative time-step simulation  
- CSV-based data output for analysis  

---

## Technical Implementation

- Language: C  
- Model Type: Stochastic SIRD Framework  
- Data Output: CSV  
- Visualization: Python-based plotting  

---

## Functional Highlights

- Incorporates uncertainty through probabilistic transitions  
- Models real-world constraints like healthcare overload  
- Supports multiple simulation runs for comparative analysis  
- Generates structured data for external visualization  

---

## How to Run

1. Compile the program:
   gcc simulation.c -o simulation

2. Run:
   ./simulation

3. Analyze generated CSV output using Python or spreadsheet tools  

---

## Output

- Simulation results in CSV format  
- Metrics for infection spread and mortality  
- Compatible with analytical tools for visualization  

---

## Future Enhancements

- Real-time data integration  
- Advanced predictive modeling  
- Machine learning-based parameter tuning  
- Interactive visualization dashboards  

---

## Note

This project was developed as part of research-oriented exploration in epidemiological modeling, focusing on stochastic systems, computational simulation, and constraint-based analysis.

---

## Author

**Mahdiya Rifqua M**  
B.Tech Computer Science & Medical Engineering  
(Specialization: Artificial Intelligence and Data Analysis)
