import cv2
import numpy as np
import matplotlib.pyplot as plt

# Load two grayscale images
img1 = cv2.imread("out.png", cv2.IMREAD_GRAYSCALE)
img2 = cv2.imread("org.png", cv2.IMREAD_GRAYSCALE)

# Check for errors
if img1 is None or img2 is None:
    raise FileNotFoundError("One or both input images were not found.")

# Resize to same dimensions if needed
img1 = cv2.resize(img1, (256, 256))
img2 = cv2.resize(img2, (256, 256))

# Compute absolute difference
diff = cv2.absdiff(img1, img2)

# Save difference image
cv2.imwrite("diff.png", diff)

# Show result
plt.figure(figsize=(12, 4))
plt.subplot(1, 3, 1)
plt.imshow(img1, cmap="gray")
plt.title("Image 1")
plt.axis("off")

plt.subplot(1, 3, 2)
plt.imshow(img2, cmap="gray")
plt.title("Image 2")
plt.axis("off")

plt.subplot(1, 3, 3)
plt.imshow(diff, cmap="gray")
plt.title("Absolute Difference")
plt.axis("off")

plt.tight_layout()
plt.show()

# Print diff pixel values
print("Difference Image Pixel Values:")
print(diff)
