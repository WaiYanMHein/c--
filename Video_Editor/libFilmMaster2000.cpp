#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include <cmath> 
#include <vector> 
#include <string>
#include <fstream>
#include "libFilmMaster2000.hpp"



using namespace std; 

string get_file_extension(const string& filename) {
    /* 
    get the extension of the file
    */
    //cout << filename.substr(filename.length() - 3, filename.length()) << endl; DEBUG1 
    return filename.substr(filename.length() - 3, filename.length());
}

void video_encode(){ 
    /*
    
    */
}

void video_decode(const string& filename) {
    /*
    decodes the video file into the struct Video

    Steps:
    1. Detect format of the Video, EG .mp4, .mov ... 
    2. Open and read metadata : frame rate, resolution, codec type
    3. Intialize decoder based on format
    4. Decode frames sequentially 
    5. Store in video struct
    */
    string extension = get_file_extension(filename); 

    try{
        ifstream file(filename, ios::binary); 
        if (file.is_open()) {
            FILE file = file.read(); 
            file.close();
        }
    }catch(exception e) {
        cout << "Error opening file" << e.what() << endl; 
    }
    
    if 
    
    

    if (extension == "mp4"){
        
    } 
    if else (extension == "mov"){
        
    }

}

void video_reverse(Video video){
    /*
    struct Video = frames, height, width, data; 
    Reverses the frames in the video 
    */
}

void video_swap_channel(Video video, unsigned char channel1, unsigned char channel2){

}

void video_clip_channel(Video video, unsigned char channel, unsigned char min_val, unsigned char max_val){

}

void scale_channel(Video video, unsigned char channel, double scale_factor){
    /*
    Scales the 'a' channel of the Video
    @params
    video : pass a struct with video info
    channel : the channel chosen to be scaled   
    scale_factor : factor by which channel will be scaled
    */
}