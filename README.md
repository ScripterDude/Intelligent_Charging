# ⚡ EV Charging Scheduler

This project finds the cheapest hours to charge an EV using Danish electricity prices.

The scheduling logic is written in **C**, while **Python** is used to retrieve price data and create the visualization.

The program fetches hourly prices from the **Elprisen lige nu API**, sorts them, and selects the cheapest charging hours within the chosen time period.

I used Matplotlib to visualize the electricity prices and highlight the hours selected by the program:
<img width="1398" height="664" alt="image" src="https://github.com/user-attachments/assets/30020dc1-a2f8-475f-908d-399bcdcc64cc" />

**Technologies:** C, Python

