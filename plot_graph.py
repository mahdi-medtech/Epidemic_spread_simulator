import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("simulation_output.csv")

plt.plot(data["Day"], data["S"], label="Susceptible")
plt.plot(data["Day"], data["I"], label="Infected")
plt.plot(data["Day"], data["R"], label="Recovered")
plt.plot(data["Day"], data["V"], label="Vaccinated")

plt.xlabel("Day")
plt.ylabel("Population")
plt.title("Epidemic Spread Simulation")
plt.legend()

plt.show()