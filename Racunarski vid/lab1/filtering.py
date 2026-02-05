import numpy as np

def convolution(img, kernel):
    img = img.astype(np.float64)
    kernel = kernel.astype(np.float64)
    output = np.zeros_like(img)

    pad_h = kernel.shape[0] // 2
    pad_w = kernel.shape[1] // 2

    padded_img = np.pad(img, ((pad_h, pad_h), (pad_w, pad_w)), mode='constant')

    for i in range(img.shape[0]):
        for j in range(img.shape[1]):
            region = padded_img[i:i + kernel.shape[0], j:j + kernel.shape[1]]
            output[i, j] = np.sum(region * kernel)

    return output


def fft(img):
    return np.fft.fftshift(np.fft.fft2(img))


def ifft(F):
    return np.abs(np.fft.ifft2(np.fft.ifftshift(F)))


def low_pass(F, radius):
    H, W = F.shape
    cx, cy = H // 2, W // 2
    mask = np.zeros_like(F, dtype=np.float64)

    for x in range(H):
        for y in range(W):
            if (x - cx)**2 + (y - cy)**2 <= radius**2:
                mask[x, y] = 1

    return F * mask


def remove_frequency_peaks(F, peaks, kv=5):

    H, W = F.shape
    cx, cy = H // 2, W // 2

    for dx, dy in peaks:
        x = cx + dx
        y = cy + dy
        F[x-kv:x+kv+1, y-kv:y+kv+1] = 0

        x2 = cx - dx
        y2 = cy - dy
        F[x2-kv:x2+kv+1, y2-kv:y2+kv+1] = 0

    return F
