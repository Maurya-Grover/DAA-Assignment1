import matplotlib.pyplot as plt

with open("rect.txt", "r") as f:
    lines = f.readlines
    for line in lines:
        print(line.split())