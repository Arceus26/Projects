# Crust Index 2024

import numpy as np
from matplotlib import pyplot as plt
import cv2

# Căile către fișierul de imagini
red_3_path = '/content/drive/MyDrive/img/Red_M_2024_3.tif'
blue_3_path = '/content/drive/MyDrive/img/Blue_M_2024_3.tif'
swir_3_path = '/content/drive/MyDrive/img/Swir_M_2024_3.tif'
nir_3_path = '/content/drive/MyDrive/img/Nir_M_2024_3.tif'

red_4_path = '/content/drive/MyDrive/img/Red_M_2024_4.tif'
blue_4_path = '/content/drive/MyDrive/img/Blue_M_2024_4.tif'
swir_4_path = '/content/drive/MyDrive/img/Swir_M_2024_4.tif'
nir_4_path = '/content/drive/MyDrive/img/Nir_M_2024_4.tif'

red_5_path = '/content/drive/MyDrive/img/Red_M_2024_5.tif'
blue_5_path = '/content/drive/MyDrive/img/Blue_M_2024_5.tif'
swir_5_path = '/content/drive/MyDrive/img/Swir_M_2024_5.tif'
nir_5_path = '/content/drive/MyDrive/img/Nir_M_2024_5.tif'

red_6_path = '/content/drive/MyDrive/img/Red_M_2024_6.tif'
blue_6_path = '/content/drive/MyDrive/img/Blue_M_2024_6.tif'
swir_6_path = '/content/drive/MyDrive/img/Swir_M_2024_6.tif'
nir_6_path = '/content/drive/MyDrive/img/Nir_M_2024_6.tif'

red_7_path = '/content/drive/MyDrive/img/Red_M_2024_7.tif'
blue_7_path = '/content/drive/MyDrive/img/Blue_M_2024_7.tif'
swir_7_path = '/content/drive/MyDrive/img/Swir_M_2024_7.tif'
nir_7_path = '/content/drive/MyDrive/img/Nir_M_2024_7.tif'

red_8_path = '/content/drive/MyDrive/img/Red_M_2024_8.tif'
blue_8_path = '/content/drive/MyDrive/img/Blue_M_2024_8.tif'
swir_8_path = '/content/drive/MyDrive/img/Swir_M_2024_8.tif'
nir_8_path = '/content/drive/MyDrive/img/Nir_M_2024_8.tif'

red_9_path = '/content/drive/MyDrive/img/Red_M_2024_9.tif'
blue_9_path = '/content/drive/MyDrive/img/Blue_M_2024_9.tif'
swir_9_path = '/content/drive/MyDrive/img/Swir_M_2024_9.tif'
nir_9_path = '/content/drive/MyDrive/img/Nir_M_2024_9.tif'

red_10_path = '/content/drive/MyDrive/img/Red_M_2024_10.tif'
blue_10_path = '/content/drive/MyDrive/img/Blue_M_2024_10.tif'
swir_10_path = '/content/drive/MyDrive/img/Swir_M_2024_10.tif'
nir_10_path = '/content/drive/MyDrive/img/Nir_M_2024_10.tif'

red_11_path = '/content/drive/MyDrive/img/Red_M_2024_11.tif'
blue_11_path = '/content/drive/MyDrive/img/Blue_M_2024_11.tif'
swir_11_path = '/content/drive/MyDrive/img/Swir_M_2024_11.tif'
nir_11_path = '/content/drive/MyDrive/img/Nir_M_2024_11.tif'

# Funcția de încărcare și rediminsionare a imaginilor
def load_and_resize(path, dimensions):
    band = cv2.imread(path, cv2.IMREAD_UNCHANGED).astype(float)
    return cv2.resize(band, dimensions)

dimensions = (cv2.imread(red_3_path, cv2.IMREAD_UNCHANGED).shape[1],
              cv2.imread(red_3_path, cv2.IMREAD_UNCHANGED).shape[0])

# Încărcăm benzile
red_bands = [load_and_resize(path, dimensions) for path in [red_3_path, red_4_path, red_5_path, red_6_path, red_7_path, red_8_path, red_9_path, red_10_path, red_11_path]]
blue_bands = [load_and_resize(path, dimensions) for path in [blue_3_path, blue_4_path, blue_5_path, blue_6_path, blue_7_path, blue_8_path, blue_9_path, blue_10_path, blue_11_path]]
swir_bands = [load_and_resize(path, dimensions) for path in [swir_3_path, swir_4_path, swir_5_path, swir_6_path, swir_7_path, swir_8_path, swir_9_path, swir_10_path, swir_11_path]]
nir_bands = [load_and_resize(path, dimensions) for path in [nir_3_path, nir_4_path, nir_5_path, nir_6_path, nir_7_path, nir_8_path, nir_9_path, nir_10_path, nir_11_path]]

# Funcția Crust index
def compute_ci(red_band, blue_band):
    numerator = red_band - blue_band
    denominator = red_band + blue_band
    return np.divide(numerator, denominator, out=np.zeros_like(numerator), where=denominator!=0)

# Aplicarea formulei Crust Index
index_values = [compute_ci(red_bands[i], blue_bands[i]) for i in range(9)]

# Funcția de normalizare a imaginii
def normalize_image(image):
    return cv2.normalize(image, None, 0, 255, cv2.NORM_MINMAX).astype(np.uint8)

# Aplicarea normalizării
index_normalized = [normalize_image(index) for index in index_values]

# Media peste toate lunile
index_mean = np.mean(index_normalized, axis=0).astype(np.uint8)
index_mean_normalized = normalize_image(index_mean)

# Măști binare adaptive
binary_masks = [cv2.adaptiveThreshold(index_n, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 11, 2)
                for index_n in index_normalized]
binary_mask_mean = cv2.adaptiveThreshold(index_mean_normalized, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 11, 2)

m_values = [np.mean(mask) for mask in binary_masks]
m10 = np.mean(binary_mask_mean)
print(f"Mean: {m10}")

# Folosim un prag specific de 0.2 * 255 = 51
avg = 0.2 * 255
print(f"AVG: {avg}")

# Din media măștilor binare adaptive scoatem pragul specific pentru a obține valoarea finală a pragului
threshold = m10 - avg
print(f"Final: {threshold}")

# Măști binare cu prag ajustat
binary_masks = [cv2.threshold(index_n, m, 255, cv2.THRESH_BINARY)[1] for index_n, m in zip(index_normalized, m_values)]
_, binary_mask_mean = cv2.threshold(index_mean_normalized, threshold, 255, cv2.THRESH_BINARY)

# Funția de suprapunere
def create_overlay(base_image, binary_mask):
    return cv2.addWeighted(base_image, 0.5, binary_mask, 0.5, 0)

# Aplicăm funcția de suprapunere
overlays = [create_overlay(index_n, mask) for index_n, mask in zip(index_normalized, binary_masks)]
overlay_mean = create_overlay(index_mean_normalized, binary_mask_mean)

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
print(f"Sand pixels:{sand_pixels}")
print(f"Total pixels:{total_pixels}")
print(f"Procentajul de pixeli cu nisip (CI): {sand_percentage:.2f}%")

# Vizualizare
plt.figure(figsize=(20, 8))

plt.subplot(1, 2, 1)
plt.imshow(cropped_overlay_mean, cmap='hot')
plt.title(f'Mean CI')
plt.axis('off')

plt.subplot(1, 2, 2)
plt.imshow(cropped_binary_mask_mean, cmap='gray')
plt.title(f'Masca binară decupată (nisip) - CI')
plt.axis('off')

plt.tight_layout()
plt.show()