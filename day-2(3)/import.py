import json
import sqlite3
import tqdm

J_data = json.load(
    open('v/data.json',encoding='utf-8')
)

conn = sqlite3.connect('v/data.db')
cursor = conn.cursor();

def createTable():
    try:
        cursor.execute(
            '''
            create table if not exists coupon(
                id integer primary key autoincrement,
                condition integer,
                discount integer,
                couponId varchar(32)
            )
            '''
        )
        conn.commit();
        return True;
    except:
        return False;

def query(Sql):
    cursor.execute(
        Sql
    );
    return cursor.fetchall();

def sqlExec(Sql):
    try:
        cursor.execute(
            Sql
        );
        conn.commit();
        return True
    except:
        return False;


if createTable():
    cleared = sqlExec('delete from coupon') and sqlExec('''
        update sqlite_sequence set seq=0 where name = 'coupon'
    ''')
    if not cleared:
        exit(0);
    bar = tqdm.tqdm(total=len(J_data));
    for e in J_data:
        pic = J_data[e];
        Sql = f'''
                insert into coupon(condition,discount,couponId) values(
                    {int(pic['condition'])},
                    {int(pic['discount'])},
                    '{pic['id']}'
                )
            '''
        i_res = sqlExec(
            Sql
        )
        if i_res:
            bar.update(1);