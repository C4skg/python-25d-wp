from PIL import (
    Image,
    ImageDraw,
    ImageFont
)
import os;
from random import choices
def addSignal(image:str,value:str,randomFont:bool=False) -> Image:
    track = Image.open(image);
    draw = ImageDraw.Draw(track);
    width = track.size[0];
    #Font
    base = 'C:/windows/fonts/Arial.ttf';
    font = ImageFont.truetype(base,size=40);
    draw.text((width - len(value)*20,10),value,font=font);
    track.show()

if __name__ == '__main__':
    image = addSignal('v/logo.jpg','Signal');