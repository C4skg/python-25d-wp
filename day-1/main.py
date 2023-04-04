from hashlib import md5
from uuid import uuid4
from random import choices
import json

money = {
    "50":"5",
    "100":"20",
    "200":"40",
    "300":"80",
    "500":"100",
    "1000":"300",
    "1500":"500"
}
keys = list(money.keys())
text = "恭喜您获得满{}减{}优惠券，复制兑换码 {} 进行兑换使用吧！"

def create():
    key = choices(keys)[0];
    value = money.get(key);
    return (key,value,md5((key + '+' + str(uuid4()) + '+' + value).encode()).hexdigest());

def insertLocal(obj:tuple):
    global text;
    m1,m2,encode=obj;
    data = None
    try:
        with open('v/data.json',encoding='utf-8') as f:
            data = json.load(f);
    except:
        pass;
    with open('v/data.json','w',encoding='utf-8') as nf:
        if data:
            data[str(len(data)+1)] = {
                'condition': m1,
                'discount': m2,
                'id': encode
            }
        else:
            data = {
                '1':{
                    'condition': m1,
                    'discount': m2,
                    'id': encode
                }
            }
        # data = json.dumps(data)
        json.dump(data,nf,ensure_ascii=False);

    # write info
    with open('v/info.txt','a+',encoding='utf-8') as fs:
        fs.write(text.format(m1,m2,encode) + '\n')

for _ in range(200):
    v = create();
    insertLocal(v);