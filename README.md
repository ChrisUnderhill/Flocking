# Flocking
A simulation of emergent behaviour arising from autonomous intelligent agents. Created with SFML in C++.

Boids have a limited vision range, and will combine three behaviours. Alignment encourages Boids to point in the same direction as other Boids they can see. Cohension encourages Boids to minimise the distance to other Boids they can see. Seperation encourages Boids to maintain some distance between themselves and others they can see. 

These three simple behaviours are tunable in strength at runtime and can produce large scale behaviour reminiscent of flocking birds and swarms of fish, despite no top-down control of Boids.
