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
        rect = patches.Rectangle((x1, y1), x2-x1, y2-y1, linewidth=1, edgecolor='r', facecolor=(0,0,0,0.2))
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
xoff = (xmax-xmin)*0.05
yoff = (ymax-ymin)*0.05
plt.xlim([xmin - xoff, xmax + xoff]) 
plt.ylim([ymin - yoff, ymax + yoff])
# ax.set_aspect("equal")
plt.title("Area of the set of iso-rectangles: " + str(sys.argv[2]))
plt.show()