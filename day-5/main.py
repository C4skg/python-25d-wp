from PIL import Image
import cv2
import os

SIZE = {
    'iphone5': (1136,640)
}

for e in os.listdir('pic'):
    if e.endswith(('png','jpg')):
        path  = f'pic/{e}'
        image = Image.open(path)
        image = image.resize(SIZE['iphone5'])
        image.save(path)