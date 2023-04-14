from lxml import etree
import os

htmlFile = r'index.html';

def Sniff(obj:etree._Element):
    children = obj.xpath("./*");
    if len(children) == 0:
        for t in obj.xpath('./text()'):
            t = t.strip('');
            if t != '':
                print(t)
    else:
        for e in children:
            Sniff(e);
    
if __name__ == '__main__':
    if not os.path.isfile(htmlFile):
        exit(0);

    with open(htmlFile,'r',encoding='utf-8') as f:
        html = f.read();

    H_obj = etree.HTML(html);
    Sniff(H_obj)