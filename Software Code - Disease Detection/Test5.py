import tkinter as tk
from tkinter import filedialog
from PIL import Image, ImageTk
import numpy as np
import tensorflow as tf
import cv2
import serial
import time

# Load the trained model
model = tf.keras.models.load_model('model.h5')

# Define image size
img_height, img_width = 224, 224

# Define class labels with serial mapping
class_labels = {
    'A': 'Bacterial Leaf Blight',
    'B': 'Brown Spot',
    'C': 'Healthy',
    'D': 'Leaf Blast',
    'E': 'Leaf Blight',
    'F': 'Leaf Scald',
    'G': 'Leaf Smut',
    'H': 'Narrow Brown Spot'
}

# Fertilizer suggestions for each disease
fertilizer_suggestions = {
    'A': 'Use Nitrogen-rich fertilizer like Urea (46% N). Apply during early stages.',
    'B': 'Apply Potassium-based fertilizers. Use MOP (Muriate of Potash).',
    'C': 'No fertilizer needed. Plant is healthy.',
    'D': 'Use balanced NPK (10-26-26) to boost resistance.',
    'E': 'Spray Zinc Sulfate and apply compost to improve soil health.',
    'F': 'Use Phosphorus fertilizers. DAP (18-46-0) is recommended.',
    'G': 'Apply fungicide and avoid excess nitrogen. Use organic compost.',
    'H': 'Use Potash and Phosphorous. Avoid excess water.'
}

# Initialize serial communication with Arduino (update COM port)
try:
    arduino = serial.Serial(port="COM4", baudrate=9600, timeout=1)
    time.sleep(2)  # Allow connection to establish
    print("Connected to Arduino")
except:
    arduino = None
    print("Arduino not found. Serial communication disabled.")

# Function to send detected class serial to Arduino
def send_to_arduino(serial_letter):
    if arduino:
        arduino.write(serial_letter.encode())  # Send as byte
        print(f"Sent to Arduino: {serial_letter}")

# Function to predict the class of an image
def predict_image(img):
    img = img.resize((img_width, img_height))
    img_array = np.array(img) / 255.0  # Normalize
    img_array = np.expand_dims(img_array, axis=0)

    predictions = model.predict(img_array)
    predicted_index = np.argmax(predictions)

    # Get serial and class name
    serial = list(class_labels.keys())[predicted_index]
    predicted_class_name = class_labels[serial]

    # Send to Arduino
    send_to_arduino(serial)

    # Get fertilizer suggestion
    suggestion = fertilizer_suggestions.get(serial, "No suggestion available.")

    return f"{serial}: {predicted_class_name}", suggestion

# Function to load image from file
def load_image():
    file_path = filedialog.askopenfilename()
    if not file_path:
        return

    img = Image.open(file_path)
    predicted_result, suggestion = predict_image(img)

    # Display image
    img = img.resize((400, 400))  # Resize for display
    img_tk = ImageTk.PhotoImage(img)
    panel.config(image=img_tk)
    panel.image = img_tk

    # Update label with prediction and suggestion
    result_label.config(text=f"Predicted Class: {predicted_result}\nFertilizer: {suggestion}")

# Function to capture image from webcam
def capture_image():
    cap = cv2.VideoCapture(0)  # Open webcam

    if not cap.isOpened():
        result_label.config(text="Error: Could not access webcam")
        return

    while True:
        ret, frame = cap.read()
        if not ret:
            result_label.config(text="Error: Could not capture image")
            break

        # Display camera preview
        cv2.imshow("Press SPACE to capture", frame)

        key = cv2.waitKey(1) & 0xFF
        if key == 32:  # Space key to capture
            break

    cap.release()
    cv2.destroyAllWindows()

    # Convert frame to PIL image
    frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    img = Image.fromarray(frame)
    predicted_result, suggestion = predict_image(img)

    # Display image in GUI
    img = img.resize((400, 400))
    img_tk = ImageTk.PhotoImage(img)
    panel.config(image=img_tk)
    panel.image = img_tk

    # Update label with prediction and suggestion
    result_label.config(text=f"Predicted Class: {predicted_result}\nFertilizer: {suggestion}")

# Create GUI window
root = tk.Tk()
root.title("Rice Leaf Disease Classifier")
root.geometry("600x700")  # Increased window size

# Heading label
heading_label = tk.Label(root, text="Rice Leaf Disease Detector", font=("Arial", 18, "bold"))
heading_label.pack(pady=10)

# Buttons for Upload and Camera
btn_frame = tk.Frame(root)
btn_frame.pack(pady=10)

upload_btn = tk.Button(btn_frame, text="Upload Image", command=load_image, font=("Arial", 12))
upload_btn.grid(row=0, column=0, padx=10)

camera_btn = tk.Button(btn_frame, text="Use Camera", command=capture_image, font=("Arial", 12))
camera_btn.grid(row=0, column=1, padx=10)

# Image display panel
panel = tk.Label(root)
panel.pack(pady=10)

# Prediction result label
result_label = tk.Label(root, text="Predicted Class: ", font=("Arial", 14), justify="left")
result_label.pack(pady=10)

# Run the GUI
root.mainloop()
