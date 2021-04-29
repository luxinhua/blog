---
title: HEXO Hacker 主题中文说明
date: 2021/4/23
categories:
  - python
toc: true # 是否启用内容索引
---

---
### ref : https://blog.csdn.net/qq_44647926/article/details/89499842
---


---
### 进度条 demo 
---
~~~bash
    import time
    scale=50 #尽量不要超过50 超过屏幕宽度会自动执行换行
    print("执行开始".center(scale//2,"-"))
    start=time.perf_counter()
    for i in range(scale+1):
    	a="*"*i
    	b="."*(scale-i)
    	c=(i/scale)*100
    	dur=time.perf_counter()-start
    	print("\r{:<3.0f}%[{}->{}] time:{:.2f}".format(c,a,b,dur),end="")
    	#\r将光标移动到前面
    	#{:^3.0f} 左对齐 保留3位整数位 保留0位小数位
    	time.sleep(0.1)
    print("\n")
    print("执行结束".center(scale//2,"-"))
~~~

--- 

~~~bash
count_down = 10  # 设置倒计时时间，单位：秒
interval = 1  # 设置屏幕刷新的间隔时间，单位：秒
for i in range(0, int(count_down/interval)+1):
     print("\r"+"▇▇▇▇"*i+" "+str(i*10)+"%", end="")
     time.sleep(interval)
print("\n加载完毕")
~~~

---

~~~bash
import time
count_down = 10  # 设置倒计时时间，单位：秒
interval = 0.25  # 设置屏幕刷新的间隔时间，单位：秒
for i in range(0, int(count_down/interval)):
    ch_list = ["\\", "|", "/", "-"]
    index = i % 4
    msg = "\r程序运行中 " + ch_list[index]
    print(msg, end="")
    time.sleep(interval)
print(u"\r结束" + "  "*len(msg))
~~~


