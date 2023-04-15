from lxml import etree
import os

htmlFile = r'index.html';

def Sniff(obj:etree._Element):
    cards = {
        'img': ['src'],
        'a'  : ['href'],
        'video' : ['poster','src'],
        'link': ['href'],
        'script': ['src'],
        'form': ['action']
    }
    for card in cards:
        values = obj.xpath(f'//{card}');
        if len(values) != 0:
            for child in values:
                for t in cards.get(card):
                    links = child.xpath(f'./@{t}');
                    for txt in links:
                        txt = txt.strip()
                        if txt != '':
                            print(txt)
    
if __name__ == '__main__':
    if not os.path.isfile(htmlFile):
        exit(0);

    with open(htmlFile,'r',encoding='utf-8') as f:
        html = f.read();

    H_obj = etree.HTML(html);
    Sniff(H_obj)