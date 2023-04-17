import re

keywords = open('filtered_words.txt','r',encoding='utf-8').read().split('\n');
comp = re.compile(rf'({"|".join(keywords)})',re.I);

while(1):
    Text = input("请输入待检测文本:");
    if len(comp.findall(Text)) != 0:
        print("Freedom")
    else:
        print("Human Rights");