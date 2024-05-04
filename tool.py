from tkinter import ttk
import tkinter as tk
from tkinter import filedialog
import shutil
import sys
import os
import subprocess

def browse_file(entry):
    file_path = filedialog.askopenfilename()
    entry.delete(0, tk.END)
    entry.insert(0, file_path)

def export_game(platform, song_path, timestamp_path, game_dir):
    global new_game_dir
    new_game_dir = game_dir + song_path

    # If the path doesn't exist, make it.
    if not os.path.exists(new_game_dir):
        shutil.copytree(game_dir, new_game_dir)

    target_music_file = os.path.join(new_game_dir, "audio_data", "music.wav")

    if(platform == "Native NDS"):
        target_timestamp_file = os.path.join(new_game_dir, "app_data", "timestamps.txt")
    else:
        target_timestamp_file = os.path.join(new_game_dir, "nitrofiles", "timestamps.txt")

    # Overwrite the original music file
    shutil.copy(song_path, target_music_file)

    # Overwrite the original timestamp file
    shutil.copy(timestamp_path, target_timestamp_file)

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
    combo = ttk.Combobox( 
        main_window,
        state="readonly",
        values=["Native NDS", "Emulator"]
    )
    combo.set("Native NDS")
    combo.pack()

    tk.Label(main_window, text="Song File (.wav):").pack()
    song_entry = tk.Entry(main_window, width=50)
    song_entry.pack()
    tk.Button(main_window, text="Browse", command=lambda: browse_file(song_entry)).pack()

    tk.Label(main_window, text="Timestamp File (.txt):").pack()
    timestamp_entry = tk.Entry(main_window, width=50)
    timestamp_entry.pack()
    tk.Button(main_window, text="Browse", command=lambda: browse_file(timestamp_entry)).pack()

    tk.Button(main_window, text="Export", command=lambda: export_game(song_entry.get(), timestamp_entry.get(), copy_folder_path)).pack()

    tk.Button(main_window, text="Create NDS File", command=lambda: create_nds_game()).pack()

    main_window.mainloop()

if __name__ == "__main__":
    main()