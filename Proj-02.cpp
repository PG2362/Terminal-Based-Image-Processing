#include <iostream>
#include "ppmio.h"
#include <string>
#include <vector>

std::vector<std::vector<RGB>> grayscale(const std::vector<std::vector<RGB>> &image);
std::vector<std::vector<RGB>> invert(const std::vector<std::vector<RGB>> &image);
std::vector<std::vector<RGB>> blur(const std::vector<std::vector<RGB>> &image);
std::vector<std::vector<RGB>> contrast(const std::vector<std::vector<RGB>> &image);
std::vector<std::vector<RGB>> mirror(const std::vector<std::vector<RGB>> &image);
std::vector<std::vector<RGB>> compress(const std::vector<std::vector<RGB>> &image);

void debugger(const std::vector<std::vector<RGB>> &image);
int main(int argc,char *argv[]){
    if(argc <= 2){
        std::cout << "Error: missing arguments in command line. Check for any possible missing input/output files or add an option\n";
        return 1;

    }
    std::vector<std::string>files;
    std::vector<std::string>options;
    bool db = false;
    // checks the command line for input/output files and options and sorts them.
    for(int i=1;i<argc;i++){
        std::string arg{argv[i]};
        if(!arg.empty() && arg[0] == '-'){
            if(arg == "-debug" || arg == "-Debug"){
                db = true;
            }
            else{
                options.push_back(arg);
            }
        }
        else if(static_cast<int>(files.size())< 2){
            files.push_back(arg);
        }
        else{
            std::cout << "Note: extra arguments found and ignored\n";
        }
    }
    if(static_cast<int>(files.size())< 2){
        std::cout << "Error: Input/Output files missing!\n";
        return 1;
    }
    std::string Inputfile = files[0];
    std::string Outputfile = files[1];

    std::vector<std::vector<RGB>> image;

    // trying to catch errors while reading input
    try {
        image = readPPM(Inputfile);
    } catch (const std::exception &e) {
        std::cerr << "Error reading input file. try again \n" ;
        return 1;
    }

    if(static_cast<int>(options.size()) == 0){
        std::cout << "No options entered!. try again \n" ;
        return 1;
    }

    if (db){
        // debugger printing out original pixel rgb values
        std::cout << "Original Image:\n \n \n \n";
        debugger(image);
    }
    for(std::string option: options){
        if(option == "-i"){
            image = invert(image);
            if (db){
            std::cout << "After inverting colors of the image:\n";
            debugger(image); // debugger printing out altered pixel rgb values
            }
        }
        else if(option == "-g"){
            image = grayscale(image);
            if (db){
            std::cout << "After Grayscaling the image:\n";
            debugger(image); // debugger printing out altered pixel rgb values
            }
        }
        else if(option == "-x"){
            image = contrast(image);
            if (db){
            std::cout << "After changing the image contrast:\n";
            debugger(image); // debugger printing out altered pixel rgb values
            }
        }
        else if(option == "-b"){
            image = blur(image);
            if (db){
            std::cout << "After blurring the image:\n";
            debugger(image); // debugger printing out altered pixel rgb values
            }
        }
        else if(option == "-m"){
            image = mirror(image);
            if (db){
            std::cout << "After mirroring the image:\n";
            debugger(image); // debugger printing out altered pixel rgb values
            }
        }
        else if(option == "-c"){
            image = compress(image);
            if (db){
            std::cout << "After compressing the image:\n";
            debugger(image); // debugger printing out altered pixel rgb values
            }
        }
        else if(option == "-debug" || option == "-Debug"){
            //Already handled. this is to make sure the else statement runs properly.
        }
        else{
            std::cout << "Note: Unknown options were entered and ignored\n"; // handles any incorrect/unknown options
        }




    }
    // trying to catch errors while creating output
    try {
        writePPM(Outputfile, image);
    } catch (const std::exception &e) {
        std::cerr << "Error writing output file:\n";
        return 1;
    }
    return 0;
}


void debugger(const std::vector<std::vector<RGB>> &image) {
    for(auto pixelstrip: image){
        for(auto pixel: pixelstrip){
            std::cout << "(" << static_cast<int>(pixel.r)<< "," << static_cast<int>(pixel.g) << ","
            << static_cast<int>(pixel.b) << ") ";
        }
        std::cout << "\n";
    }
}

std::vector<std::vector<RGB>> grayscale(const std::vector<std::vector<RGB>> &image){
    std::vector<std::vector<RGB>> image2 = image;
    int sum = 0;
    for(auto &pixelstrip: image2){
        for(auto &pixel: pixelstrip){
            // casting r,g,b values to int to add them, since they are of unsigned char type
            sum = static_cast<int>(pixel.r)+static_cast<int>(pixel.g)+static_cast<int>(pixel.b);
            //casting them back to unsigned char
            auto value = static_cast<unsigned char>(sum/3);
            pixel.r = value;
            pixel.g = value;
            pixel.b = value;
}
}
return image2;
}

std::vector<std::vector<RGB>> invert(const std::vector<std::vector<RGB>> &image){
    std::vector<std::vector<RGB>> image2 = image;
    int max = 255;
    for(auto &pixelstrip: image2){
        for(auto &pixel: pixelstrip){
            int pr = static_cast<int>(pixel.r);
            int pg = static_cast<int>(pixel.g);
            int pb = static_cast<int>(pixel.b);
            pr = max-pr;
            pg = max-pg;
            pb = max-pb;
            pixel.r = static_cast<unsigned char>(pr);
            pixel.g = static_cast<unsigned char>(pg);
            pixel.b = static_cast<unsigned char>(pb);

}

}
return image2;
}

std::vector<std::vector<RGB>> mirror(const std::vector<std::vector<RGB>> &image) {
    auto image2 = image;
    for (auto &pixelstrip : image2) {
        // reverses all the "pixel strips" to mirror image
        std::reverse(pixelstrip.begin(), pixelstrip.end());
    }
    return image2;
}


std::vector<std::vector<RGB>> blur(const std::vector<std::vector<RGB>> &image){
 auto image2 = image;
 int length = static_cast<int>(image2.size());
 int width = static_cast<int>(image2[0].size());
 int sum1,sum2,sum3;
 //ignores first and last pixel in a vertical "pixelstrip"
 for(int i = 1; i<length-1; i++){
    //ignores first and last pixel in a horizontal "pixelstrip"
    for(int j = 1; j<width-1; j++){
        sum1 = 0;
        sum2 = 0;
        sum3 = 0;
        for(int k = -1;k<=1;k++){
            for(int l = -1;l<=1;l++){
                sum1 += static_cast<int>(image[i + k][j + l].r);
                sum2 += static_cast<int>(image[i + k][j + l].g);
                sum3 += static_cast<int>(image[i + k][j + l].b);
                // original image is used here so that the blurred pixels arent used for the averages
            }
        }
        image2[i][j].r = static_cast<unsigned char>(sum1/9);
        image2[i][j].g = static_cast<unsigned char>(sum2/9);
        image2[i][j].b = static_cast<unsigned char>(sum3/9);
    }
 }
 return image2;
}

std::vector<std::vector<RGB>> contrast(const std::vector<std::vector<RGB>> &image){
    std::vector<std::vector<RGB>> image2 = image;
    
    for(auto &pixelstrip: image2){
        for(auto &pixel: pixelstrip){
        int r2 = static_cast<int>((pixel.r - 128) * 1.2 + 128);
        int g2 = static_cast<int>((pixel.g - 128) * 1.2 + 128);
        int b2 = static_cast<int>((pixel.b - 128) * 1.2 + 128);
        // checks for out of range values and sets it to either the max or min bounds
        if(r2>255){
            r2= 255;
        }
        else if(r2<0){
            r2 = 0;
        }

        if(g2>255){
            g2= 255;
        }
        else if(g2<0){
            g2 = 0;
        }

        if(b2>255){
            b2= 255;
        }
        else if(b2<0){
            b2 = 0;
        }
        pixel.r = static_cast<unsigned char>(r2);
        pixel.g = static_cast<unsigned char>(g2);
        pixel.b = static_cast<unsigned char>(b2);

        }
    }
    return image2;
}

std::vector<std::vector<RGB>> compress(const std::vector<std::vector<RGB>> &image) {
    std::vector<std::vector<RGB>> image2;
    int length = static_cast<int>(image.size());
    int width = static_cast<int>(image[0].size());
    
    for (int i = 0; i < length;  i++) {
        if (i % 2 != 0) { 
            std::vector<RGB> rownew;
            for (int j = 0; j < width; j++) {
                if (j % 2 != 0) { 
                    rownew.push_back(image[i][j]); 
                    // Only adds it to the new image vector when (i%2 !=0) and (j%2 !=0)
                }
            }
            image2.push_back(rownew);
        }
    }
    return image2;
}


