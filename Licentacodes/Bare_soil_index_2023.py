# Bare soil index 2023

import numpy as np
from matplotlib import pyplot as plt
import cv2
import matplotlib.colors as mcolors

# Căile către fișierele de imagini
red_paths = [
    '/content/drive/MyDrive/img/Red_M_2023_3.tif',
    '/content/drive/MyDrive/img/Red_M_2023_4.tif',
    '/content/drive/MyDrive/img/Red_M_2023_5.tif',
    '/content/drive/MyDrive/img/Red_M_2023_6.tif',
    '/content/drive/MyDrive/img/Red_M_2023_7.tif',
    '/content/drive/MyDrive/img/Red_M_2023_8.tif',
    '/content/drive/MyDrive/img/Red_M_2023_9.tif',
    '/content/drive/MyDrive/img/Red_M_2023_10.tif',
    '/content/drive/MyDrive/img/Red_M_2023_11.tif'
]

blue_paths = [
    '/content/drive/MyDrive/img/Blue_M_2023_3.tif',
    '/content/drive/MyDrive/img/Blue_M_2023_4.tif',
    '/content/drive/MyDrive/img/Blue_M_2023_5.tif',
    '/content/drive/MyDrive/img/Blue_M_2023_6.tif',
    '/content/drive/MyDrive/img/Blue_M_2023_7.tif',
    '/content/drive/MyDrive/img/Blue_M_2023_8.tif',
    '/content/drive/MyDrive/img/Blue_M_2023_9.tif',
    '/content/drive/MyDrive/img/Blue_M_2023_10.tif',
    '/content/drive/MyDrive/img/Blue_M_2023_11.tif'
]

swir_paths = [
    '/content/drive/MyDrive/img/Swir_M_2023_3.tif',
    '/content/drive/MyDrive/img/Swir_M_2023_4.tif',
    '/content/drive/MyDrive/img/Swir_M_2023_5.tif',
    '/content/drive/MyDrive/img/Swir_M_2023_6.tif',
    '/content/drive/MyDrive/img/Swir_M_2023_7.tif',
    '/content/drive/MyDrive/img/Swir_M_2023_8.tif',
    '/content/drive/MyDrive/img/Swir_M_2023_9.tif',
    '/content/drive/MyDrive/img/Swir_M_2023_10.tif',
    '/content/drive/MyDrive/img/Swir_M_2023_11.tif'
]

nir_paths = [
    '/content/drive/MyDrive/img/Nir_M_2023_3.tif',
    '/content/drive/MyDrive/img/Nir_M_2023_4.tif',
    '/content/drive/MyDrive/img/Nir_M_2023_5.tif',
    '/content/drive/MyDrive/img/Nir_M_2023_6.tif',
    '/content/drive/MyDrive/img/Nir_M_2023_7.tif',
    '/content/drive/MyDrive/img/Nir_M_2023_8.tif',
    '/content/drive/MyDrive/img/Nir_M_2023_9.tif',
    '/content/drive/MyDrive/img/Nir_M_2023_10.tif',
    '/content/drive/MyDrive/img/Nir_M_2023_11.tif'
]

# Funcția de încărcare și redimensionare a imaginilor
def load_and_resize(path, dimensions):
    band = cv2.imread(path, cv2.IMREAD_UNCHANGED).astype(float)
    return cv2.resize(band, dimensions)

# Dimensiunile imaginii
dimensions = (cv2.imread(red_paths[0], cv2.IMREAD_UNCHANGED).shape[1],
              cv2.imread(red_paths[0], cv2.IMREAD_UNCHANGED).shape[0])

# Încărcăm benzile pentru toate lunile
red_bands = [load_and_resize(path, dimensions) for path in red_paths]
blue_bands = [load_and_resize(path, dimensions) for path in blue_paths]
swir_bands = [load_and_resize(path, dimensions) for path in swir_paths]
nir_bands = [load_and_resize(path, dimensions) for path in nir_paths]

# Funcția Bare Soil Index (BSI)
def compute_bsi(swir_band, red_band, nir_band, blue_band):
    numerator = (swir_band + red_band) - (nir_band + blue_band)
    denominator = (swir_band + red_band) + (nir_band + blue_band)
    return np.divide(numerator, denominator, out=np.zeros_like(numerator), where=denominator!=0)

# Aplicarea formulei BSI pentru toate lunile
bsi_values = [compute_bsi(swir_bands[i], red_bands[i], nir_bands[i], blue_bands[i]) for i in range(9)]

# Funcția de normalizare a imaginii
def normalize_image(image):
    return cv2.normalize(image, None, 0, 255, cv2.NORM_MINMAX).astype(np.uint8)

# Aplicarea normalizării
bsi_normalized = [normalize_image(bsi) for bsi in bsi_values]

# Media peste toate lunile
bsi_mean = np.mean(bsi_normalized, axis=0).astype(np.uint8)
bsi_mean_normalized = normalize_image(bsi_mean)

# Calcul mediane
median_vals = [np.median(bsi_n) for bsi_n in bsi_normalized]
median_mean = np.median(bsi_mean_normalized)

main = sum(median_vals) / len(median_vals)
print(f"MAIN MAIN: {main}")
print(f"Median1: {median_mean}")

final1 = median_mean - main
print(f"Final1: {final1}")

# Măști binare adaptive
binary_masks = [cv2.adaptiveThreshold(bsi_n, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 11, 2)
                for bsi_n in bsi_normalized]
binary_mask_mean = cv2.adaptiveThreshold(bsi_mean_normalized, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 11, 2)

m_values = [np.mean(mask) for mask in binary_masks]
m10 = np.mean(binary_mask_mean)
binary_mean = sum(m_values) / len(m_values)
print(f"Binary mean: {binary_mean}")
print(f"Mean: {m10}")

final2 = binary_mean - m10
print(f"Final2: {final2}")

final = final1 + final2
print(f"Final: {final}")

# Măști binare cu prag ajustat
binary_masks = [cv2.threshold(bsi_n, m, 255, cv2.THRESH_BINARY)[1] for bsi_n, m in zip(bsi_normalized, m_values)]
_, binary_mask_mean = cv2.threshold(bsi_mean_normalized, m10 - final, 255, cv2.THRESH_BINARY)

# Funcția de suprapunere
def create_overlay(base_image, binary_mask):
    return cv2.addWeighted(base_image, 0.5, binary_mask, 0.5, 0)

# Aplicăm funcția de suprapunere
overlays = [create_overlay(bsi_n, mask) for bsi_n, mask in zip(bsi_normalized, binary_masks)]
overlay_mean = create_overlay(bsi_mean_normalized, binary_mask_mean)

# Funcția de decupare a imaginii
def crop_image(image, x, y, width, height):
    return image[y:y+height, x:x+width]

# Setăm datele delimitative ale imaginii și o decupăm
x, y, width, height = 3800, 1500, 1100, 1100
cropped_overlays = [crop_image(overlay, x, y, width, height) for overlay in overlays]
cropped_overlay_mean = crop_image(overlay_mean, x, y, width, height)
cropped_binary_mask_mean = crop_image(binary_mask_mean, x, y, width, height)

# Calcul pixeli nisip
sand_pixels = np.sum(cropped_binary_mask_mean == 255)
total_pixels = width * height
sand_percentage = (sand_pixels / total_pixels) * 100
print(f"Sand pixels: {sand_pixels}")
print(f"Total pixels: {total_pixels}")
print(f"Procentajul de pixeli cu nisip: {sand_percentage:.2f}%")

# Vizualizare
plt.figure(figsize=(20, 8))

plt.subplot(1, 2, 1)
plt.imshow(cropped_overlay_mean, cmap='hot')
plt.title('Mean BSI')
plt.axis('off')

plt.subplot(1, 2, 2)
plt.imshow(cropped_binary_mask_mean, cmap='gray')
plt.title('Masca binară decupată (nisip)')
plt.axis('off')

plt.tight_layout()
plt.show()