from PIL import (
    Image,
    ImageFont,
    ImageDraw
)
from string import ascii_letters
from random import choices,randint

def createVerify() -> dict:
    vCode = choices(list(ascii_letters),k=4)
    
    background = Image.new('RGB',(120,25));
    for y in range(background.size[1]):
        for x in range(background.size[0]):
            background.putpixel(
                (x,y),
                (randint(0,255),randint(0,255),randint(0,255))
            )
    draw = ImageDraw.Draw(background);
    font = ImageFont.truetype(r'C:/windows/fonts/Arial.ttf',size=21)
    
    for i,v in enumerate(vCode):
        draw.text(
            (25*i + 10,0),
            v,
            font=font
        )

    return {
        'image': background,
        'code': ''.join(vCode)
    }


if __name__ == '__main__':
    verify = createVerify();
    print(verify)