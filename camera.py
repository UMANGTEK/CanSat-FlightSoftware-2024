import time
import picamera

def record_video(duration, output_filename):
    withpicamera.PiCamera() as camera:
        camera.resolution = (1920, 1080)
        camera.framerate = 30
        camera.start_recording(output_filename)
        camera.wait_recording(duration)
        camera.stop_recording()

if __name__ == "__main__":
    recording_duration = 60


    while True:
        current_time = time.strftime("%H%M%S")
        output_filename = f"/home/janus/Recordings/video_{current_time}.h264"
        record_video(recording_duration, output_filename)
        print(f"Video recorded and saved as {output_filename}")
