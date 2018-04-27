cmake_minimum_required(VERSION 3.10)
project(parallel_dijkstra)

set(CMAKE_CXX_STANDARD 17)

find_package(PostgreSQL REQUIRED)

add_executable(parallel_dijkstra main.cpp ParallelDijkstra.cpp ParallelDijkstra.h DijkstraNode.cpp DijkstraNode.h PostgreSQLLoader.cpp PostgreSQLLoader.h DijkstraGraph.cpp DijkstraGraph.h)

# Add include directories to your target. PRIVATE is useful with multi-target projects - see documentation of target_include_directories for more info
target_include_directories(parallel_dijkstra PRIVATE ${PostgreSQL_INCLUDE_DIRS})

# Add libraries to link your target againts. Again, PRIVATE is important for multi-target projects
target_link_libraries(parallel_dijkstra PRIVATE ${PostgreSQL_LIBRARIES})

