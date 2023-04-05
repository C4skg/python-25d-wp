from PIL import Image
import tqdm
import os

SIZE = {
    'iphone5': (1136,640)
}

if not os.access('resize',os.F_OK):
    os.mkdir('resize')

dirList = os.listdir('pic');

bar = tqdm.tqdm(total=len(dirList))

for e in dirList:
    if e.endswith(('png','jpg')):
        image = Image.open(f'pic/{e}')
        image = image.resize(SIZE['iphone5'])
        image.save(f'resize/{e}')
        bar.update(1);