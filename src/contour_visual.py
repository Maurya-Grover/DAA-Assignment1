import matplotlib.pyplot as plt
import matplotlib.patches as patches
import sys

fig, ax = plt.subplots()

xmin, xmax, ymin, ymax = 1e18, -1e18, 1e18, -1e18

with open(sys.argv[1], "r") as f:
    lines = f.readlines()[1:]
    for line in lines:
        x1, x2, y1, y2 = [float(x) for x in line.split()]
        xmin = min(x1, x2, xmin)
        xmax = max(x1, x2, xmax)
        ymin = min(y1, y2, ymin)
        ymax = max(y1, y2, ymax)
        rect = patches.Rectangle((x1, y1), x2-x1, y2-y1, linewidth=1, edgecolor='r', facecolor='none')
        ax.add_patch(rect)


fxmin, fxmax = xmin, xmax
fymin, fymax = ymin, ymax

with open("stripes.txt", "r") as f:
    lines = f.readlines()
    for line in lines:
        elems = line.split()
        x1, x2 = [fxmax if x == 'inf' else fxmin if x == '-inf' else float(x) for x in elems[0:2]]
        y1, y2 = [fymax if x == 'inf' else fymin if x == '-inf' else float(x) for x in elems[2:4]]
        m = float(elems[4])
        rect = patches.Rectangle((x1, y1), x2-x1, y2-y1, linewidth=1, edgecolor=(0,0,0,0.3), facecolor='none')
        ax.add_patch(rect)

with open("contour.txt", "r") as f:
    lines = f.readlines()
    for line in lines:
        x1, x2, y1, y2 = [float(x) for x in line.split()]
        plt.plot((x1,x2), (y1,y2), color="green", linewidth=3)

plt.xlim([xmin-3, xmax+3]) 
plt.ylim([ymin-3, ymax+3])
# ax.autoscale()

plt.show()