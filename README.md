# CT6TARPS
Exploring NDS development by creating a rhythm game, which has a tool to create custom rhythm ROMS.

## Table of Contents
1. [Prerequisites](#prerequisites)
2. [How To Create Your Own NDS Rhythm Game](#how-to-create-your-own-nds-rhythm-game)
3. [Coding Standards](#coding-standards)
   * [C Style Guidelines](#c-style-guidelines)
   * [Assembly Style Guidelines](#assembly-style-guidelines)

## Prerequisites
These are prerequisites for if you would like to use this to create your own rhythm game for NDS.

Note: _I'm unsure of whether all of these need to be installed, as I haven't had time to test this out from a fresh PC._
- Install copy of repository project, [Python](https://www.python.org/), [Audacity](https://www.audacityteam.org/) and [devkitPro](https://github.com/devkitPro/installer/releases)![image](https://github.com/AmyE123/CT6TARPS/assets/55834601/00332b32-41d0-40a3-acf6-67a84f70583d)

## How To Create Your Own NDS Rhythm Game
1. Find a copy of the music you would like to use for your rhythm game. This music needs to be a **.wav**, and it also needs to be **very compressed**, to around **3mb** or so. I haven't tested any higher than this, but if it is too big you would get an error when building the ROM. [Here](https://www.xconvert.com/compress-wav) is an online tool I've used for compressing my .wav files.

2. Open Audacity and import the .wav file. Now we will be recording the timestamps. Whilst playing the music, you can use `ctrl + m` to make a label whilst the music is playing, make these labels to the beat of the song! If you spam the labels too fast, it may break the game though, so don't go too crazy. 

![image](https://github.com/AmyE123/CT6TARPS/assets/55834601/1e778201-16d2-407c-8f3f-708b607d93c5)

3. Once this is complete, go to `File > Export > Export Labels...` and locate the repository you just downloaded. Within the repository go to the `Tools` folder and find the `timestamps.txt` file. Overwrite this with your timestamps.

![image](https://github.com/AmyE123/CT6TARPS/assets/55834601/7fa4e787-ac9f-45d5-9790-1075bbdfb006)

![image](https://github.com/AmyE123/CT6TARPS/assets/55834601/b4a64ffe-16b7-417e-9c41-f8d3d9928605)


4. Once this has saved, open the file explorer and go to the same `Tools` folder within the repository again. Double check the `timestamps.txt` file has been overwritten with your new timestamps, and if it looks good, open the `ConvertTimestamps.exe` executable.
This will convert your timestamps into frames, and put this text within the `framestamps.txt` file within that same folder.

![image](https://github.com/AmyE123/CT6TARPS/assets/55834601/7b2df510-97cc-4a93-aa7c-9d1fb11a123f)

5. Now you want to go back to the root of the repository and open the `NDSRhythmMaker.exe` executable.
![image](https://github.com/AmyE123/CT6TARPS/assets/55834601/fd2fb9bb-6719-4fe9-969c-0aa735a3910f)

6. Add your compressed .wav file, and your new framestamps file.

![image](https://github.com/AmyE123/CT6TARPS/assets/55834601/b015911b-f948-44f3-a926-40351dc8b757)

7. Press the 'Export' button. You should see some text on the terminal, and you should see a new folder within the repository that has just been made. If you selected NDS, the folder would be `[songname]_NDS` and if you selected emulator, the folder would be `[songname]_Emulator`

![image](https://github.com/AmyE123/CT6TARPS/assets/55834601/dca0291e-afef-41ca-9b39-ec8eb0e752b5)

8. With this successfully made, press the 'Create NDS File` button, and check the terminal for text stating the file has been created successfully. If you get an error code, try compressing your wav file more, or reduce the amount of beats you're recording.
![image](https://github.com/AmyE123/CT6TARPS/assets/55834601/5e95d429-8628-495b-8a21-00b4dff74284)

### Flashcart Info
If you're using a flashcart to test your rhythm game, create a folder in the root of your SD card called `app_data`, and within this folder, copy the contents of the `app_data` folder within the new generated project files. This should just be the framestamps text file.
![image](https://github.com/AmyE123/CT6TARPS/assets/55834601/748df371-fb7a-42fc-9285-4305bd3f79b2)










## Coding Standards
### C Style Guidelines
The C code within this project mainly follows [Paul Krzyzanowski's C Programming Style guide](https://pk.org/rutgers/notes/pdf/Cstyle.pdf), which was summarised in the [University of Maryland Department of Computer Science's C Style Guidelines](https://www.cs.umd.edu/~nelson/classes/resources/cstyleguide/)

### Assembly Style Guidelines
The assembly-code within this project follows [Ken Lambert's Assembly Language Style Guide](https://simondlevy.academic.wlu.edu/files/courses/csci210w2018/LC3StyleGuide.pdf)
