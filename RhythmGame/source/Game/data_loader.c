#include "data_loader.h"
#include <stdio.h>
#include <nds.h>

bool loadBeatsFromFile(const char* filePath, int* beats, int maxBeats, int* numBeatsLoaded) {
    FILE* file = fopen(filePath, "rb");
    if (!file) {
        iprintf("Failed to open the file: %s\n\n Did you use the wrong version of the ROM? (NDS/Emulator)\n If not, on the root of your SD Card, create a 'app_data' folder and put your 'timestamps.txt' file inside of it.\n", filePath);
        return false;
    }

    int value;
    *numBeatsLoaded = 0;
    while (fscanf(file, "%d,", &value) > 0 && *numBeatsLoaded < maxBeats) {
        beats[(*numBeatsLoaded)++] = value;
    }

    fclose(file);
    if (*numBeatsLoaded == maxBeats && fscanf(file, "%d,", &value) > 0) {
        iprintf("Failed to load beats from file.\n Too many values within the 'timestamps.txt' file.\n");
        return false;
    }
    return true;
}