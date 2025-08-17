#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/resource.h>
#include "libFilmMaster2000.h"

void parse_comma_separated(const char *input,
unsigned char *val1, unsigned char *val2) {
    char *comma_pos = strchr(input, ',');
    if (!comma_pos) {
        fprintf(stderr, "Invalid input format: expected 'x,y'\n");
        exit(EXIT_FAILURE);
    }
    *val1 = (unsigned char)atoi(input);
    *val2 = (unsigned char)atoi(comma_pos + 1);
}

void parse_range(const char *input,
unsigned char *min_val, unsigned char *max_val) {
    if (input[0] != '[' || input[strlen(input) - 1] != ']') {
        fprintf(stderr, "Invalid input format: expected '[x,y]'\n");
        exit(EXIT_FAILURE);
    }
    char range[128];
    strncpy(range, input + 1, strlen(input) - 2);
    range[strlen(input) - 2] = '\0';

    char *comma_pos = strchr(range, ',');
    if (!comma_pos) {
        fprintf(stderr, "Invalid range format: expected '[x,y]'\n");
        exit(EXIT_FAILURE);
    }

    *min_val = (unsigned char)atoi(range);
    *max_val = (unsigned char)atoi(comma_pos + 1);
}

long get_memory_usage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}

void print_memory_usage(const char *flag, void *video) {
    if (!strcmp(flag, "-O")) {
        Video *v = (Video *)video;
        size_t memory_usage = sizeof(Video)
         + v->num_frames * v->channels * v->height * v->width;
        printf("Memory usage of Video struct: %zu KB\n", memory_usage / 1024);
    } else if (!strcmp(flag, "-M")) {
        MVideo *v = (MVideo *)video;
        size_t memory_usage = sizeof(MVideo) + v->num_frames * v->channels *
         v->height * v->width;
        printf("Memory usage of MVideo struct: %zu KB\n", memory_usage / 1024);
    } else {
        SVideo *v = (SVideo *)video;
        size_t total_size = v->num_frames * sizeof(Frame) +
        v->num_frames * v->channels * sizeof(Channel) +
        v->num_frames * v->channels * v->height * v->width;
        printf("Memory usage of SVideo struct: %zu KB\n",
         (sizeof(SVideo) + total_size) / 1024);
    }
}

void execute_function(const char *flag,
const char *function_name, void *video, char **argv, int argc) {
    clock_t start_time, end_time;
    long memory_before, memory_after;

    start_time = clock();
    memory_before = get_memory_usage();

    if (!strcmp(flag, "-S")) {
        if (!strcmp(function_name, "reverse")) {
            reverse_S((SVideo *)video);
        } else if (!strcmp(function_name, "swap_channel")) {
            if (argc < 6) {
                fprintf(stderr,
                "swap_channels_S:[in][out]-S swap_channels[ch1,ch2]\n");
                return;
            }
            unsigned char channel1, channel2;
            parse_comma_separated(argv[5], &channel1, &channel2);
            swap_channels_S((SVideo *)video, channel1, channel2);
        } else if (!strcmp(function_name, "clip_channel")) {
            if (argc < 7) {
                fprintf(stderr,
                "clip_channel_S:[in][out]-S clip_channel[ch][min,max]\n");
                return;
            }
            unsigned char channel = (unsigned char)atoi(argv[5]);
            unsigned char min_val, max_val;
            parse_range(argv[6], &min_val, &max_val);
            clip_channel_S((SVideo *)video, channel, min_val, max_val);
        } else if (!strcmp(function_name, "scale_channel")) {
            if (argc < 7) {
                fprintf(stderr,
                "scale_channel_S:[in][out]-S scale_channel[ch][scale]\n");
                return;
            }
            unsigned char channel = (unsigned char)atoi(argv[5]);
            float scale_factor = atof(argv[6]);
            scale_channel_S((SVideo *)video, channel, scale_factor);
        } else {
            fprintf(stderr,
            "Unknown function: %s for -S flag\n", function_name);
        }
    } else if (!strcmp(flag, "-M")) {
        if (!strcmp(function_name, "reverse")) {
            reverse_M((MVideo *)video);
        } else if (!strcmp(function_name, "swap_channel")) {
            if (argc < 6) {
                fprintf(stderr,
                "swap_channels_M:[in][out]-M swap_channels [ch1,ch2]\n");
                return;
            }
            unsigned char channel1, channel2;
            parse_comma_separated(argv[5], &channel1, &channel2);
            swap_channels_M((MVideo *)video, channel1, channel2);
        } else if (!strcmp(function_name, "clip_channel")) {
            if (argc < 7) {
                fprintf(stderr,
                "clip_channel_M:[in][out]-M clip_channel [ch] [min,max]\n");
                return;
            }
            unsigned char channel = (unsigned char)atoi(argv[5]);
            unsigned char min_val, max_val;
            parse_range(argv[6], &min_val, &max_val);
            clip_channel_M((MVideo *)video, channel, min_val, max_val);
        } else if (!strcmp(function_name, "scale_channel")) {
            if (argc < 7) {
                fprintf(stderr,
                "scale_channel_M:[in][out]-M scale_channel [ch] [scale]\n");
                return;
            }
            unsigned char channel = (unsigned char)atoi(argv[5]);
            float scale_factor = atof(argv[6]);
            scale_channel_M((MVideo *)video, channel, scale_factor);
        } else {
            fprintf(stderr,
            "Unknown function: %s for -M flag\n", function_name);
        }
    } else if (!strcmp(flag, "-O")) {
        if (!strcmp(function_name, "reverse")) {
            reverse((Video *)video);
        } else if (!strcmp(function_name, "swap_channel")) {
            if (argc < 6) {
                fprintf(stderr,
                "swap_channels:[in][out]-O swap_channels [ch1,ch2]\n");
                return;
            }
            unsigned char channel1, channel2;
            parse_comma_separated(argv[5], &channel1, &channel2);
            swap_channels((Video *)video, channel1, channel2);
        } else if (!strcmp(function_name, "clip_channel")) {
            if (argc < 7) {
                fprintf(stderr,
                "clip_channel:[in][out]-O clip_channel [ch] [min,max]\n");
                return;
            }
            unsigned char channel = (unsigned char)atoi(argv[5]);
            unsigned char min_val, max_val;
            parse_range(argv[6], &min_val, &max_val);
            clip_channel((Video *)video, channel, min_val, max_val);
        } else if (!strcmp(function_name, "scale_channel")) {
            if (argc < 7) {
                fprintf(stderr,
                "scale_channel:[in][out]-O scale_channel [ch] [scale]\n");
                return;
            }
            unsigned char channel = (unsigned char)atoi(argv[5]);
            float scale_factor = atof(argv[6]);
            scale_channel((Video *)video, channel, scale_factor);
        } else {
            fprintf(stderr,
            "Unknown function: %s for -O flag\n", function_name);
        }
    } else {
        fprintf(stderr, "Invalid flag: %s\n", flag);
    }

    end_time = clock();
    memory_after = get_memory_usage();

    double runtime = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Function '%s' completed in %.6f seconds.\n",
     function_name, runtime);
    printf("Memory usage: %ld KB\n", memory_after - memory_before);
}

int main(int argc, char *argv[]) {
    if (argc < 5) {
        fprintf(stderr,
        "Usage: %s [in][out][flag (-S/-M/-O)][function][options]\n",
        argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_file = argv[1];
    const char *output_file = argv[2];
    const char *flag = argv[3];
    const char *function_name = argv[4];

    clock_t start_time, end_time;
    long memory_before, memory_after;

    memory_before = get_memory_usage();
    start_time = clock();
    void *video = NULL;
    if (!strcmp(flag, "-O")) {
        video = decode(input_file);
    } else if (!strcmp(flag, "-M")) {
        video = decode_M(input_file);
    } else {
        video = decode_S(input_file);
    }
    end_time = clock();
    memory_after = get_memory_usage();
    if (!video) {
        fprintf(stderr, "Failed to decode input file: %s\n", input_file);
        return EXIT_FAILURE;
    }
    printf("Decode completed in %.6f seconds.\n",
     (double)(end_time - start_time)/ CLOCKS_PER_SEC);
    printf("Memory usage for decode: %ld KB\n", memory_after - memory_before);

    print_memory_usage(flag, video);

    execute_function(flag, function_name, video, argv, argc);

    memory_before = get_memory_usage();
    start_time = clock();
    if (!strcmp(flag, "-O")) {
        if (encode(output_file, (Video *)video) != 0) {
            fprintf(stderr, "Failed to encode output file: %s\n", output_file);
            free_video((Video *)video);
            return EXIT_FAILURE;
        }
        free_video((Video *)video);
    } else if (!strcmp(flag, "-M")) {
        if (encode_M(output_file, (MVideo *)video) != 0) {
            fprintf(stderr, "Failed to encode output file: %s\n", output_file);
            free_video_M((MVideo *)video);
            return EXIT_FAILURE;
        }
        free_video_M((MVideo *)video);
    } else {
        if (encode_S(output_file, (SVideo *)video) != 0) {
            fprintf(stderr, "Failed to encode output file: %s\n", output_file);
            free_video_S((SVideo *)video);
            return EXIT_FAILURE;
        }
        free_video_S((SVideo *)video);
    }
    end_time = clock();
    memory_after = get_memory_usage();
    printf("Encode completed in %.6f seconds.\n",
     (double)(end_time - start_time)/ CLOCKS_PER_SEC);
    printf("Memory usage for encode: %ld KB\n", memory_after - memory_before);

    printf("Operation '%s' completed successfully with flag '%s'.\n",
     function_name, flag);
    return EXIT_SUCCESS;
}
