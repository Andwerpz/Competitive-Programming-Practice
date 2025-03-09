import matplotlib.pyplot as plt
from matplotlib.patches import Polygon

# List of hulls containing coordinates
hulls = [
    [[1.72791, -3.45582], [3.97063, 1.49469], [2.26664, 2.26664], [0, 0], ],    
[[0, 0], [-2.26664, -2.26664], [1.49469, -3.97063], [1.72791, -3.45582], ], 
[[-1.72791, 3.45582], [-3.97063, -1.49469], [-2.26664, -2.26664], [0, 0], ],[[0, 0], [2.26664, 2.26664], [-1.49469, 3.97063], [-1.72791, 3.45582], ], 
]

# Create figure and axis
fig, ax = plt.subplots()
ax.set_aspect('equal')

# Create a color map with distinct colors
cmap = plt.get_cmap('tab10', len(hulls))

# Plot each hull with a different color
for i, hull in enumerate(hulls):
    # Convert scientific notation to actual floats
    points = [[float(x), float(y)] for [x, y] in hull]
    poly = Polygon(points,
                   facecolor=cmap(i),
                   edgecolor='k',
                   linewidth=1,
                   alpha=0.8)
    ax.add_patch(poly)

# Set plot limits
all_points = [point for hull in hulls for point in hull]
x_coords = [float(point[0]) for point in all_points]
y_coords = [float(point[1]) for point in all_points]
ax.set_xlim(min(x_coords)-1, max(x_coords)+1)
ax.set_ylim(min(y_coords)-1, max(y_coords)+1)

plt.title('Multi-colored Hulls Plot')
plt.xlabel('X-axis')
plt.ylabel('Y-axis')
plt.show()