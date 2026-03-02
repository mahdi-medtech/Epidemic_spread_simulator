Epidemiological Spread Simulation & Containment Optimization System

Overview

The rapid emergence and global transmission of infectious diseases demand computational models capable of analyzing outbreak dynamics under realistic constraints.

This project implements a stochastic, compartment-based SIRD (Susceptible–Infected–Recovered–Deceased) epidemiological model developed in C to simulate disease propagation within a configurable population.

Model Framework

The system utilizes:

- Stochastic state-transition modeling
- Probabilistic transmission dynamics
- Configurable epidemiological parameters
- Resource-constrained healthcare modeling

Each individual dynamically transitions between S, I, R, and D states based on:

- Contact rate
- Infection probability
- Recovery duration
- Mortality rate
- Hospital capacity constraints

This enables realistic simulation of uncertainty in epidemic progression.

Containment & Optimization Features

The system incorporates intervention strategies including:

- Vaccination modeling
- Lockdown enforcement
- Healthcare capacity limits

Mortality rates dynamically increase when active infections exceed hospital capacity, allowing evaluation of system overload scenarios.

Epidemiological Metrics Computed

- Basic reproduction number (R0)
- Effective reproduction number (Rt)
- Peak infection levels
- Total affected population
- Mortality outcomes
- Multi-trial simulation analysis

Technical Implementation

Language: C  
Model Type: Stochastic SIRD Framework  
Data Output: CSV for analytical processing  
Visualization: Python-based plotting  

Research Significance

By integrating stochastic algorithms, compartment modeling, and healthcare resource constraints, this system provides a structured computational platform for:

- Epidemic behavior analysis
- Public health response evaluation
- Policy experimentation under constrained systems

Developed as part of B.Tech Computer Science & Medical Engineering research exploration.
