import datetime
import time
import random

x1 = datetime.datetime(2024,1,26,8,0,0)
#print(datetime.datetime.timestamp(x1))

#x3=x1
with open('line_sample.txt', 'w') as f:
    for i in range(20):
        x1=x1+datetime.timedelta(hours=1)
        #timestamp =int(time.mktime(x3.timetuple()))
        timestamp=int(datetime.datetime.timestamp(x1))
        t=random.randint(20,23)
        h=random.randint(50,55)
        str1=f"home,room=LivingRoom temp={t:.1f},hum={h:.1f} {timestamp}\n"
        f.write(str1)        

        t=random.randint(23,25)
        h=random.randint(55,60)
        str2=f"home,room=Kitchen temp={t:.1f},hum={h:.1f} {timestamp}\n"    
        f.write(str2)        

print(x1)



