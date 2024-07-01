
import numpy as np
from shapely.geometry import LineString

trajectory_data = [(1, 2), (3, 4), (5, 6)]
trajectory_np_arr = np.array(trajectory_data)
print(trajectory_data)             # [(1, 2), (3, 4), (5, 6)]
print(trajectory_np_arr.tolist())  # [(1, 2), (3, 4), (5, 6)]
line = LineString(trajectory_np_arr.tolist())
print(line.wkt) # LINESTRING (1 2, 3 4, 5 6)
# print(line.wkb)
print(line)     # LINESTRING (1 2, 3 4, 5 6)
print(line.length)


