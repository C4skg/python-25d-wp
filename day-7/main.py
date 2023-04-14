from genericpath import isdir, isfile
import os
import re
from time import time
accept = {
    '.py':{
        'desc': r'[^\\+](\#.*)'
    },
    '.html':{
        'desc': r'(\<\!\-\-.*\-\-\>)'
    },
    '.js':{
        'desc': r'(\/\/.*)'
    },
    '.css':{
        'desc': r'(\/\*.*\/\*)'
    },
    '.cpp':{
        'desc': r'(\/\/.*)'
    },
    '.h':{
        'desc': r'(\/\/.*)'
    }
}

# 目标路径
T_dir = 'code';



class codeTime:
    def __init__(self) -> None:
        self.time = {

        }

    def getTotal(self):
        ALL_ = {
            'normal': 0,
            'desc': 0,
            'space': 0
        }
        for i in self.time.values():
            ALL_['normal'] += i['normal'];
            ALL_['desc'] += i['desc'];
            ALL_['space'] += i['space'];
        return ALL_;

total = codeTime();


def fileFuzz(file:str):
    keys = accept.keys();
    if not file.endswith(tuple(keys)):
        return False;
    fileType = '.' + file.split('.')[-1];
    if not total.time.get(fileType):
        total.time[fileType] = {
            'normal': 0,
            'desc' : 0,
            'space': 0
        };
    try:
        with open(file,'r') as f:
            data = f.readlines();
    except:
        return False;

    rules = accept.get(fileType).get('desc');
    for line in data:
        if line.strip() == '':
            total.time[fileType]['space'] += 1;
        elif len(re.findall(rules,line,re.I)) != 0:
            total.time[fileType]['desc'] += 1;
        
        total.time[fileType]['normal'] += 1;
    return True;


def dirFuzz(dirs:str):
    absPath = os.path.abspath(dirs)
    if os.path.isfile(absPath):
        fileFuzz(absPath);
    elif os.path.isdir(absPath):
        for e in os.listdir(absPath):
            e = os.path.join(absPath,e);
            if os.path.isfile(e):
                fileFuzz(e);
            elif os.path.isdir(e):
                dirFuzz(e);


if __name__ == '__main__':
    dirFuzz(T_dir);
    print(total.time)