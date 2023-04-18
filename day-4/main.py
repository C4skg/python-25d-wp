import re
import time

comp = re.compile(r'([a-z\']+)',re.I);

mode = int(input('请输入1或2来选择模式:').strip(''));

if mode == 1:
    userIn = input('请输入一段文本以统计单词数:');
    print(f'文中单词数:{len(comp.findall(userIn))}')
else:
    file = input('请输入待读取文件路径：'); 
    start = time.time();
    with open(f'{file}',"r",encoding='utf-8') as f:
        print(f'文中单词数:{len(comp.findall(f.read()))}')
    print('time:',time.time() - start)

