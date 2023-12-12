#include <iostream>
#include <cstdio>
#include <cstdlib>

// majority credits for the idea YT: TheRainHarvester
std::string plotData(float x, float y, const char* title) {
    const char* filename = "data.txt";

    // Open data file for writing
    FILE* dataFile = fopen(filename, "w");
    if (dataFile == NULL) {
        std::cerr << "Error opening data file" << std::endl;
        return "";
    }

    // Write data to the file
    fprintf(dataFile, "%f %f\n", x, y);
    fclose(dataFile);

    // Get the full path of the data file
    char fullPath[_MAX_PATH];
    if (_fullpath(fullPath, filename, _MAX_PATH) == NULL) {
        std::cerr << "Error getting full path" << std::endl;
        return "";
    }

    // Open Gnuplot pipe for plotting in the console
    FILE* gnuplotPipe = _popen("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\" -persist", "w");

    if (gnuplotPipe == NULL) {
        std::cerr << "Error opening Gnuplot pipe" << std::endl;
        return "";
    }

    // Gnuplot to set title and plot data and send them to the conole
    fprintf(gnuplotPipe, "set term qt persist\n");
    fprintf(gnuplotPipe, "set title \"%s\" \n", title);
    fprintf(gnuplotPipe, "plot '%s'\n", fullPath);

    fflush(gnuplotPipe);
    fclose(gnuplotPipe);

    return fullPath;
}

int main() {
    // Sample data
    float i = 1;
    float j = 10;

    // Call the plotData function with data and title
    std::string filePath = plotData(i, j, "Title");


    return 0;
}
