#ifndef LIBFILMMASTER2000_HPP
#define LIBFILMMASTER2000_HPP

#include <string>
#include <vector>

using namespace std;

struct Photo{
    int height;
    int width;
    int pixels; 
}; 

struct Video{ 
    string filename;                // video file path
    long num_frames;                // number of frames in the video
    double duration;                // duration in seconds
    int frameRate;                  // frames per second
    unsigned char channels;         // color_channels    
    unsigned char height;           // height of the frame
    unsigned char width;            // width of the frame
    unsigned char *data;            // pixel data
}; 

// misc helper functions

string get_file_extension(const string& filename); 

// photo functions

void photo_adjust_brightness(Photo photo, double brightness); 

void photo_adjust_contrast(Photo photo, double contrast); 

void photo_denoise(Photo photo); 

void photo_inpaint(Photo photo); 

// video functions

// encodes the video
void video_encode(const string filename, Video video);  

// decodes the video
void video_decode(const string& filename); 

// reverses the video
void video_reverse(Video video);

// swaps the color channels of the video, RGB
void video_swap_channel(Video video, unsigned char channel1, unsigned char channel2); 

// clips the color channels of the video, RGB
void video_clip_channel(Video video, unsigned char channel, unsigned char min_val, unsigned char max_val); 

// scales the color channels of the video, RGB
void video_scale_channel(Video video, unsigned char channel, double scale_factor);

#endif





