---
title: test article
date: 2021/2/7
---

[TOC]

### 标题
---
# 一级标题
## 二级标题
### 三级标题
#### 四级标题
##### 五级标题
###### 六级标题  <!--最多6级标题-->
----
### 代码块
~~~c
    int a = 4 ;
~~~
---
### 表格
|  表头   | 表头  |
|  ----  | ----  |
| 单元格  | 单元格 |
| 单元格  | 单元格 |
---
### 红色字体

---
### 注释
~~~javascript
<div style='display: none'>
哈哈我是注释，不会在浏览器中显示。
</div>
~~~
---
### 任务列表
- [ ] 任务一 未做任务 `- + 空格 + [ ]`
- [x] 任务二 已做任务 `- + 空格 + [x]`
---
### 换行 (后面空2格)
nihao  
faweafe

---
### 空行
在编辑的时候有多少个空行(只要这一行只有回车或者space没有其他的字符就算空行)，在渲染之后，只隔着一行。

--- 
### 对齐方式
<center>行中心对齐</center>
<p align="left">行左对齐</p>
<p align="right">行右对齐</p>

---
### 斜体、粗体、删除线、下划线、背景高亮
*斜体*或_斜体_
**粗体**
***加粗斜体***
~~删除线~~
++下划线++
==背景高亮==

--- 
### 超链接、页内链接、自动链接
* 方法一
[]里写链接文字，()里写链接地址, ()中的""中可以为链接指定title属性，title属性可加可不加。title属性的效果是鼠标悬停在链接上会出现指定的 title文字，链接地址与title前有一个空格。

作者：择势量投
链接：https://www.jianshu.com/p/ebe52d2d468f
来源：简书
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
欢迎阅读 [择势勤](https://www.jianshu.com/u/16d77399d3a7 "择势勤")
* 方法二
我经常去的几个网站[Google][1]、[Leanote][2]。

[1]:http://www.google.com 
[2]:http://www.leanote.com



--- 
### 注脚
使用 Markdown[^1]可以效率的书写文档, 直接转换成 HTML[^2]。

[^1]:Markdown是一种纯文本标记语言

[^2]:HyperText Markup Language 超文本标记语言


--- 
### 自动链接
Markdown 支持以比较简短的自动链接形式来处理网址和电子邮件信箱，只要是用<>包起来， Markdown 就会自动把它转成链接。一般网址的链接文字就和链接地址一样，例如：
&lt;http://example.com/&gt; &emsp;&emsp; 
&lt;address@example.com&gt;

---
### 插图片
<center>  <!--开始居中对齐-->

![GitHub set up](http://zh.mweb.im/asset/img/set-up-git.gif "图片Title")
格式: ![图片Alt](图片地址 "图片Title")
</center> <!--结束居中对齐-->


--- 
### 多级引用
>>> 请问 Markdwon 怎么用？ - 小白
>> 自己看教程！ - 愤青
> 教程在哪？ - 小白

---
### 字体、字号、颜色
<font face="黑体">我是黑体字</font>
<font face="微软雅黑">我是微软雅黑</font>
<font face="STCAIYUN">我是华文彩云</font>
<font color=#0099ff size=12 face="黑体">黑体</font>
<font color=gray size=5>gray</font>
<font color=#00ffff size=3>null</font>

--- 
### 目录结构
在段落中填写 [TOC] 以显示全文内容的目录结构。
    [TOC]

--- 
### 流程图
```
graph LR
A-->B
```
```
sequenceDiagram
A->>B: How are you?
B->>A: Great!
```

--- 
#### 分割线
* * *
***
*****
- - -
-----------


--- 
### HTML表单
<center>
<table>
<tr>
<th rowspan="2">值班人员</th>
<th>星期一</th>
<th>星期二</th>
<th>星期三</th>
</tr>
<tr>
<td>李强</td>
<td>张明</td>
<td>王平</td>
</tr>
</table>

</center>


---
### 特殊字符
|  表头   | 表头  |
|  ----  | ----  |
| 单元格  | 单元格 |
| 单元格  | 单元格 |

｜特殊字符 | 描述 | 字符的代|
 |  ----  | ----  | ----  |
｜   | 空格符 |	&nbsp;|
｜< | 小于号 |	&lt; |
｜ > | 大于号 | &gt; |
｜&	 | 和号	| &amp;|
｜￥	 | 人民币 | &yen;|
｜©	 | 版权	| &copy;|
｜®	 | 注册商标	| &reg;|
｜°C | 摄氏度 | &deg;|
｜±	 | 正负号 | &plusmn;|
｜×	| 乘号 | &times;|
｜÷	| 除号 | &divide;|
｜²	| 平方（上标²）| &sup2;|
｜³	| 立方（上标³）| &sup3;|


