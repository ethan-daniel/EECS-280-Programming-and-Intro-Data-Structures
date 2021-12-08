#include <iostream>
#include <string>
#include <fstream>
#include "Matrix.h"
#include "Image.h"
#include "processing.h"

using namespace std;

int main(int argc, char *argv[]){

    if (argc != 5){
        cout << "Usage: resize INFILE OUTFILE WIDTH HEIGHT" << endl;
        return 1;
    }

    string inName = argv[1];
    string outName = argv[2];
    int new_width = atoi(argv[3]);
    int new_height = atoi(argv[4]);
    ifstream fin(inName);
    ofstream fout(outName);

    if (!fin.is_open() ){
        cout << "Unable to open " << inName << endl;
        return 1;
    }

    if (!fin.is_open() ){
        cout << "Unable to open " << outName << endl;
        return 1;
    }

    cout << "Processing... " << inName <<endl;

    Image* img = new Image;
    Image_init(img, fin);
    Image* carved_img = new Image(*img);
    seam_carve(carved_img, new_width, new_height);
    Image_print(carved_img, fout);

    delete img;
    delete carved_img;

    cout << "Resize of "<< inName <<" to " << outName << " completed!"<< endl;

    return 0;
}