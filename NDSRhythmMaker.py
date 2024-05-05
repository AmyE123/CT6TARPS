from tkinter import ttk
import tkinter as tk
from tkinter import filedialog
import shutil
import sys
import os
import subprocess

def get_application_path():
    """Get the path of the application (whether it's an .exe or .py)"""
    if getattr(sys, 'frozen', False):
        # If the application is run as a bundle (i.e., it's an .exe)
        application_path = os.path.dirname(sys.executable)
    else:
        # If it's run as a .py script
        application_path = os.path.dirname(os.path.abspath(__file__))
    return application_path

application_dir = get_application_path()

def browse_file(entry):
    file_path = filedialog.askopenfilename()
    entry.delete(0, tk.END)
    entry.insert(0, file_path)

def export_game(platform, song_path, timestamp_path, game_dir):
    song_name = os.path.splitext(os.path.basename(song_path))[0]  # Extract song name from path
    if platform == "NDS":
        template_dir = os.path.join(game_dir, "RhythmGame_NDS")
        game_name = "RhythmGame_NDS"
    else:
        template_dir = os.path.join(game_dir, "RhythmGame_Emulator")
        game_name = "RhythmGame_Emulator"
    
    global new_game_dir
    new_game_dir = os.path.join(game_dir, song_name + "_" + platform)  # Name the new directory after the song

    # Copy the entire directory template
    if os.path.exists(new_game_dir):
        shutil.rmtree(new_game_dir)  # Remove existing directory if it exists
    shutil.copytree(template_dir, new_game_dir)  # Copy the base template

    # Cleanup build & vs directory and any builds
    build_dir = os.path.join(new_game_dir, 'build')
    if os.path.exists(build_dir):
        shutil.rmtree(build_dir)

    vs_dir = os.path.join(new_game_dir, '.vs')
    if os.path.exists(vs_dir):
        shutil.rmtree(vs_dir)

    nds_file = os.path.join(new_game_dir, game_name + '.nds')
    elf_file = os.path.join(new_game_dir, game_name + '.elf')
    for file_path in [nds_file, elf_file]:
        if os.path.exists(file_path):
            os.remove(file_path)

    # Define the target files within the new directory structure
    target_music_file = os.path.join(new_game_dir, "audio_data", "music.wav")
    if platform == "NDS":
        target_framestamp_file = os.path.join(new_game_dir, "app_data", "framestamps.txt")
    else:
        target_framestamp_file = os.path.join(new_game_dir, "nitrofiles", "framestamps.txt")

    # Overwrite the music and timestamp files with the selected files
    shutil.copy(song_path, target_music_file)
    shutil.copy(timestamp_path, target_framestamp_file)

    print(f"Files exported for {platform}. Music: {target_music_file}, Framestamps: {target_framestamp_file}")

def create_nds_game():
    if os.path.exists(new_game_dir) and os.path.isfile(os.path.join(new_game_dir, "Makefile")):
        os.chdir(new_game_dir)
        try:
            subprocess.run(['make'], check=True)
            print("NDS file created successfully.")
        except subprocess.CalledProcessError as e:
            print("Failed to create NDS file:", e)
    else:
        print("Makefile not found or directory is incorrect.")

def main():
    main_window = tk.Tk()
    main_window.config(width=300, height=200)
    main_window.title("NDS Rhythm Game Creator Tool")

    tk.Label(main_window, text="Targeted Platform:").pack()
    platform = ttk.Combobox( 
        main_window,
        state="readonly",
        values=["NDS", "Emulator"]
    )
    platform.set("NDS")
    platform.pack()

    tk.Label(main_window, text="Song File (.wav):").pack()
    song_entry = tk.Entry(main_window, width=50)
    song_entry.pack()
    tk.Button(main_window, text="Browse", command=lambda: browse_file(song_entry)).pack()

    tk.Label(main_window, text="Framestamp File (.txt):").pack()
    framestamp_entry = tk.Entry(main_window, width=50)
    framestamp_entry.pack()
    tk.Button(main_window, text="Browse", command=lambda: browse_file(framestamp_entry)).pack()

    tk.Button(main_window, text="Export", command=lambda: export_game(platform.get(), song_entry.get(), framestamp_entry.get(), application_dir)).pack()

    tk.Button(main_window, text="Create NDS File", command=lambda: create_nds_game()).pack()

    main_window.mainloop()

if __name__ == "__main__":
    main()