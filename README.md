# BVH (Bounding Volume Hierarchy) Visualization

BVH Visualization written in OpenGL. Visualizes the bounding boxes (AABBs) of the BVH as wireframe interactively (first person camera).

## Compile / Run
Requirements: OpenGL 4.3

```bash 
git clone --recursive git@github.com:MircoWerner/BVHVisualization.git
cd BVHVisualization
./pre-build.sh
mkdir build
cd build
cmake ..
make
./BVHVisualization
```

If no command line arguments are provided, the example BVH will be visualized. To render your own BVH use:
```bash
./BVHVisualization <pathToYourBVHFile.csv>
```

## File Format / BVH CSV File
The BVH has to be provided in the following format:
```csv
left right primitiveIdx aabb_min_x aabb_min_y aabb_min_z aabb_max_x aabb_max_y aabb_max_z  # first line header
1 2 0 -5.6406 0.3184 -2.2571 -5.4849 0.4859 -2.1585 # then the data
...
```
- left/right: absolute child pointer
- primitiveIdx: some custom index, will be ignored
- aabb_*: AABB of the node/leaf

## Controls / UI
- W,A,S,D,Shift,Space: Move the camera forward,left,backward,right,down,up.
- Right mouse button (press and hold) and dragging the mouse: Rotate the camera.
- Mouse wheel: Zoom the camera.


- Checkbox "BVH Color Leaf": Enable/Disable that the leaf nodes are rendered in a different (green) color.
- "BVH Min Depth": Minimum level of the BVH that is rendered.
- "BVH Max Depth": Maximum level of the BVH that is rendered.
- Button "Screenshot": Take a screenshot (without UI), will be saved in the folder with the executable.

## Screenshots
A screenshot showing an entire BVH of the [Stanford Dragon](http://graphics.stanford.edu/data/3Dscanrep/) model:

![img bvh visualization](https://github.com/MircoWerner/BVHVisualization/blob/main/resources/bvhexample/lbvh_visualization.png?raw=true)

Leaf nodes can be visualized with a different color:

![img bvh visualization leafs](https://github.com/MircoWerner/BVHVisualization/blob/main/resources/bvhexample/lbvh_visualization_green.png?raw=true)