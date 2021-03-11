import matplotlib.pyplot as plt
import matplotlib.patches as patches

fig, ax = plt.subplots()

cmin = 1e18
cmax = -1e8

with open("rect.txt", "r") as f:
    lines = f.readlines()[1:]
    for line in lines:
        x1, x2, y1, y2 = [int(x) for x in line.split()]
        cmin = min(x1, x2, y1, y2, cmin)
        cmax = max(x1, x2, y1, y2, cmax)
        rect = patches.Rectangle((x1, y1), x2-x1, y2-y1, linewidth=1, edgecolor='r', facecolor=(0,0,0,0.2))
        ax.add_patch(rect)


fmin, fmax = cmin, cmax

with open("stripes.txt", "r") as f:
    lines = f.readlines()
    for line in lines:
        x1, x2, y1, y2, m = [fmax if x == 'inf' else fmin if x == '-inf' else int(x) for x in line.split()]
        rect = patches.Rectangle((x1, y1), x2-x1, y2-y1, linewidth=5, edgecolor=(0,0,0,0.3), facecolor='none')
        ax.add_patch(rect)

plt.xlim([cmin-2, cmax+2]) 
plt.ylim([cmin-2, cmax+2])
ax.set_aspect("equal")

plt.show()