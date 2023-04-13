import os;
import re;
import tqdm;

diaryPath = 'diary';

if not os.path.isdir(diaryPath):
    exit(0);

com = re.compile(r'([a-z\']+)',re.I);

result = {};
dirs = os.listdir(diaryPath);
bar = tqdm.tqdm(total=len(dirs));
for file in dirs:
    path = os.path.join(diaryPath,file);
    try:
        with open(path,'r',encoding='UTF-8') as f:
            txt = f.read()
    except:
        continue;
    total = com.findall(txt);
    tmp = {
        'len': len(total)
    }
    #*出现数量最多的即为核心词汇
    t_temp = {};
    max = {
        'num': 0,
        'danci': '?'
    };
    for i in total:
        if t_temp.get(i):
            t_temp[i] +=1;
        else:
            t_temp[i] = 1;
        if t_temp[i] > max['num']:
            max['num'] = t_temp[i];
            max['danci'] = i;
    tmp['res'] = max

    result[file.split('.')[0]] = tmp;


print(result)

