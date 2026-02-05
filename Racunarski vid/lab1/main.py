import cv2
import numpy as np
import matplotlib.pyplot as plt

from filtering import fft, ifft, remove_frequency_peaks

img = cv2.imread("slika_1.png", cv2.IMREAD_GRAYSCALE)

F = fft(img)

plt.imshow(np.log(np.abs(F) + 1), cmap='gray')
plt.title("FFT")
plt.show()

peaks = [
    (9, 9),
    (-8,50)
]

F_clean = remove_frequency_peaks(F.copy(), peaks, kv=5)

plt.imshow(np.log(np.abs(F_clean) + 1), cmap='gray')
plt.title("FFT After")
plt.show()

cleaned = ifft(F_clean)

plt.imshow(cleaned, cmap='gray')
plt.title("Cleaned")
plt.show()

cleaned_uint8 = np.clip(cleaned, 0, 255).astype(np.uint8)
cv2.imwrite("cleaned.png", cleaned_uint8)
