def convert_timestamps(input_file, output_file):
    try:
        with open(input_file, 'r') as file:
            lines = file.readlines()

        frame_counts = []
        for line in lines:
            # Split the line by any whitespace and select the first element
            first_timestamp = line.split()[0]  # Get only the first number
            frame_count = int(float(first_timestamp) * 60)
            frame_counts.append(frame_count)

        # Write the frame counts to the output file
        with open(output_file, 'w') as file:
            for frame in frame_counts:
                file.write(f"{frame}\n")

        print("Converting timestamps successful.")
    except FileNotFoundError:
        print("Error: File not found.")
    except Exception as e:
        print(f"Error: {e}")

    # Wait for user input before closing
    input("Press Enter to exit...")

input_file_name = 'timestamps.txt'
output_file_name = 'framestamps.txt'

convert_timestamps(input_file_name, output_file_name)
