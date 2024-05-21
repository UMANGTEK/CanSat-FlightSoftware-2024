from picamera2.encoders import H264Encoder, Quality
from picamera2.outputs import FileOutput
fro picamera2 import Picamera2
import time
import TPi.GPIO as GPIO

picam2 = Picamera2()
picam2.configure(picam2.create_video_configuration())
encoder = H264Encoder()
CAMLED = 40
duration 60
GPIO.setmode(GPIO.BCM)
GPIO.setup(CAMLED, GPIO.OUT, initial=False)

while True:
    current_time = time.strftime("%H%M%S")
    output_filenme = f"/home/janus/Recordings/video_{current_time}.h264"
    GPIO.output(CAMLED, True)
    output = FileOutput(output_filename)
    picam2.start_recording(encoder, output, quality=Quality.HIGH)
    time.sleep(duration)
    picam2.stop_recording()
    GPIO.output(CAMLED, False)
