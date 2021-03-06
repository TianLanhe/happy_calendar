见面日历
========
专属日历，记录见面天数
--------

* `save.dat` ：上学期数据文件，保存新修改
* `recover.dat` ：上学期原始数据文件，保存默认数据
* `save_new.dat` ：新学期数据文件，保存新修改
* `recover_new.dat` ：新学期原始数据文件，保存默认数据

代码思路:
--------
#### 数据结构说明：

用一个自定义类型Node的连续数组存储，每个元素表示某坐标的颜色。

第一个元素的color成员表示数组的长度。如`node[0].color=5`表示node有效元素的范围为`[1,5]`。

元素的坐标信息也包括了日期信息，`void PrintDay(int x,int y)`会根据坐标解析出该坐标对应的日期，然后打印该日期

1. 打印学期选择界面，调用`int SelectTerm()`选择一个学期
2. 光标回到开头，调用`void PrintCalendar()`打印学期日历界面
3. 初始化，打开`save.dat`(新学期是`save_new.dat`)，若不存在，则打开`recover.dat`，若也不存在，那就什么都不干。若打开成功，成块读取文件中的内容，初始化node。然后按照node的信息调用`void ChangeColor(int x,int y)`改变对应坐标的颜色
4. 接着将控制权交给用户，点击`日期`则会调用`void ChangeColor(int x,int y)`，搜索node数组，若有对应坐标的元素，则修改color成员，否则新建一个记录，即node[0].color++，改变对应坐标的颜色。若点击`保存`，则调用`int Save()`将node数组写入文件，保存起来。若点击`恢复默认`，则调用`int Recovery()`读取`recover.day`，与初始化类似。若点击`退出`则退出循环，程序结束。

### 注意：

* __不能使用`system("cls")`来清屏__，因为调用后鼠标事件`ReadConsoleInput(hInput, &inRec, 1, &res)`读取会失效，我也不知道为什么。
* __正确应返回0，出错返回-1__，程序里正确返回1，出错返回0不是那么好。
* 基本上两个学期的所有操作又重新写了函数处理，最好能调用同一个函数处理不同的事情。

### 截图：
![](https://github.com/TianLanhe/happy_calendar/raw/master/screenshot.jpg)
