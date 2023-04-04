import sqlite3
import re

conn = sqlite3.connect('v/data.db');
cursor = conn.cursor()

def findInfo(id) -> list:
    try:
        return cursor.execute(
            f'''
                select condition,discount from coupon where couponId = '{id}'
            '''
        ).fetchall();
    except:
        return [];

def matchId(info):
    compile = re.compile(r'.*([0-9|a-z]{32}).*',re.IGNORECASE);
    find = compile.findall(info);
    if len(find) != 0:
        return find[0][0]
    else:
        return False;

userIn = input('请输入激活码：');

id = matchId(userIn);
if id:
    res = findInfo(id);
    if res:
        print( "恭喜您获得满%s减%s优惠券" % (res))
    else:
        print("激活码不存在")
else:
    print("激活码无效");