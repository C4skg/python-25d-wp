import re

keywords = open('filtered_words.txt','r',encoding='utf-8').read().split('\n');


while(1):
    Text = input("请输入待检测文本:");
    print(
        re.sub(rf'({"|".join(keywords)})',"**",Text)
    )