void a_julia();
void a_cameras();
void a_solids();
void a_indexing();
void a_instancing();
void a_lighting();
void a_materials();
void a_textures();
void a_local();
void a_mappers();
void a_distributed();
void a_smooth();
void a_bumpmappers();

void a_rendering_competition();

#include <thread>
#include <iostream>
#include <chrono>
using namespace std::chrono;
int main(int /*argc*/, char** /*argv*/) {
    auto start = high_resolution_clock::now();
    a_rendering_competition();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "It took: " << duration.count() << std::endl;
    // a_distributed();
    return 0;
}