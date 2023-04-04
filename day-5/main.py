from PIL import Image
import cv2

'''
def foo():
    res = yield 5;
    print(res);

res = foo();
print(next(res))
print(next(res));
# print(next(res))

'''

def xrange_100(n):
    while n<100:
        n+=1;
        yield n;


for i in xrange_100(1):
    print(i)

