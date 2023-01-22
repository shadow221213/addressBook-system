#include <bits/stdc++.h>
using namespace std;
// 简简单单的快读
template < typename T > inline T read( ) {
    int f = 1;
    T sum = 0;
    char ch = getchar( );
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar( );
    }
    while (isdigit(ch)) {
        sum = (sum << 1) + (sum << 3) + (ch ^ 48);
        ch = getchar( );
    }
    return f * sum;
}
// 通讯录容量
const int N = 1e5 + 5;
// 字符串长度
const int M = 1e2 + 2;
// 星期名称
char weekDay[10][7] = { "星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六" };
// 每月天数
int Day[2][13] = { { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 } };
// 即时改变字符串
char name[M], phone[M], address[M], workPhone[M];
// 生日信息
struct Birthday {
    int year;	// 年
    int month;	// 月
    int day;	// 日
};
// 个人信息
struct Person {
    int Sex;	                            // 性别
    int Age;	                            // 年龄
    int Number;	                            // 编号
    struct Birthday Birth;	                // 出生日期
    int Type;	                            // 类型
    char Name[M];	                        // 姓名
    char Phone[M];	                        // 手机号码
    char Address[M];	                    // 单位名称
    char WorkPhone[M];	                    // 办公电话
    bool operator < (const Person a)const {	// 重定义比较运算符
        return Number < a.Number;
    }
};
// 通讯录
struct Book {
    struct Person Array[N]; // 建设通讯录
    int Size;	            // 通讯录现存大小
}Abs;
// 编号
int NUMBER( ) {
    int number;
    printf("输入-1可退出该选项\n");
    printf("请输入编号：");
    number = read<int>( );
    return number;
}
// 姓名
inline void NAME( ) {
    printf("请输入姓名：");
    scanf("%s", name);
}
// 性别
inline int SEX( ) {
    int sex;
    printf("1.男 2.女\n");
    printf("请输入性别：");
    while (1) {
        sex = read<int>( );
        if (sex == 1 || sex == 2) break;
        printf("输入有误，请重新输入\n");
    }
    return sex;
}
// 年龄
inline int AGE( ) {
    printf("请输入年龄：");
    int age;
    while (1) {
        age = read<int>( );
        if (age >= 0) break;
        printf("输入有误，请重新输入\n");
    }
    return age;
}
// 出生日期
inline struct Birthday BIRTH( ) {
    printf("例：xxxx xx xx\n");
    printf("请输入生日：");
    struct Birthday birth;

    while (1) {
        birth.year = read<int>( );
        if (birth.year >= 0) break;
        printf("输入有误，请重新输入\n");
    }

    while (1) {
        birth.month = read<int>( );
        if (birth.month > 0 && birth.month <= 12) break;
        printf("输入有误，请重新输入\n");
    }

    while (1) {
        birth.day = read<int>( );
        if (birth.day > 0 && birth.day <= Day[(birth.year % 4 == 0 && birth.year % 100 != 0) ||
            birth.year % 400 == 0][birth.month]) break;
        printf("输入有误，请重新输入\n");
    }

    return birth;
}
// 生日
inline struct Birthday BIRTHDAY( ) {
    printf("例：xx xx\n");
    printf("请输入生日：");
    struct Birthday birth = { 0 };

    while (1) {
        birth.month = read<int>( );
        if (birth.month > 0 && birth.month <= 12) break;
        printf("输入有误，请重新输入\n");
    }

    while (1) {
        birth.day = read<int>( );
        if (birth.day > 0 && birth.day <= Day[(birth.year % 4 == 0 && birth.year % 100 != 0) ||
            birth.year % 400 == 0][birth.month]) break;
        printf("输入有误，请重新输入\n");
    }

    return birth;
}
// 类型
inline int TYPE( ) {
    printf("0.自己 1.家人 2.朋友 3.同学 4.同事\n");
    printf("请输入类型：");
    int type;
    while (1) {
        type = read<int>( );
        if (type >= 0 && type <= 4) break;
        printf("输入有误，请重新输入\n");
    }
    return type;
}
// 办公电话
inline void WORKPHONE( ) {
    printf("请输入办公电话：");
    scanf("%s", workPhone);
}
// 手机号码
inline void PHONE( ) {
    printf("请输入手机号码：");
    scanf("%s", phone);
}
// 单位名称
inline void ADDRESS( ) {
    printf("请输入单位名称：");
    scanf("%s", address);
}
// kmp算法
inline void getNext(int next[], char t[]) {
    int j = 0, k = -1;
    int n = strlen(t);
    next[0] = -1;

    while (j < n - 1)
        if (k == -1 || t[j] == t[k]) {
            j++; k++;
            if (t[j] == t[k]) next[j] = next[k];
            else next[j] = k;
        }
        else k = next[k];
}

inline int kmp(char s[], char t[]) {
    int next[N], i = 0, j = 0;
    int n = strlen(s);
    int m = strlen(t);
    getNext(next, t);

    while (i < n && j < m)
        if (j == -1 || s[i] == t[j]) {
            i++;
            j++;
        }
        else j = next[j];

    if (j >= m) return (i - m);
    else return (-1);
}
// 查找联系人
inline int findNumber(int x) {
    int l = 0;
    int r = Abs.Size;
    while (l < r) {
        int mid = l + r >> 1;
        if (Abs.Array[mid].Number == x) return mid;
        else if (Abs.Array[mid].Number < x) l = mid + 1;
        else r = mid;
    }
    return -1;
}
// 判断今日是否有人过生日
inline bool FindBirthDay( ) {
    time_t now = time(NULL);
    tm * time = localtime(&now);

    struct Birthday birth = { time->tm_year + 1900, time->tm_mon + 1, time->tm_mday };

    bool cnt = false;
    for (int i = 0; i < Abs.Size; i++)
        if (Abs.Array[i].Birth.month == birth.month &&
            Abs.Array[i].Birth.day == birth.day)
            cnt = true;

    return cnt;
}
// 清屏
inline void sys( ) {
    system("pause");
    system("cls");
}
// 更改联系人
inline bool ALL(int x) {
    int number = NUMBER( );
    if (number < 0) {
        sys( );
        return false;
    }

    if (x == Abs.Size && findNumber(number) != -1) {
        printf("该联系人已存在\n");

        sys( );
        return false;
    }
    Abs.Array[x].Number = number;

    NAME( );
    strcpy(Abs.Array[x].Name, name);

    Abs.Array[x].Sex = SEX( );

    Abs.Array[x].Age = AGE( );

    Abs.Array[x].Birth = BIRTH( );

    Abs.Array[x].Type = TYPE( );

    PHONE( );
    strcpy(Abs.Array[x].Phone, phone);

    ADDRESS( );
    strcpy(Abs.Array[x].Address, address);

    WORKPHONE( );
    strcpy(Abs.Array[x].WorkPhone, workPhone);

    return true;
}
// 查无此人
inline void notFound( ) {
    printf("查无此人\n");
    sys( );
}
// 读入历史数据
inline void start( ) {
    FILE * fp = fopen("in.txt", "r");

    if (fp == NULL) return;
    // 文件读入
    int number;
    while (fscanf(fp, "%d", &number) != EOF) {
        int x = Abs.Size;
        if (findNumber(number) != -1) x = findNumber(number);
        Abs.Array[x].Number = number;

        fscanf(fp, "%s", name);
        strcpy(Abs.Array[x].Name, name);

        int sex;
        fscanf(fp, "%d", &sex);
        Abs.Array[x].Sex = sex;

        int age;
        fscanf(fp, "%d", &age);
        Abs.Array[x].Age = age;

        struct Birthday birth;
        fscanf(fp, "%d %d %d", &birth.year, &birth.month, &birth.day);
        Abs.Array[x].Birth = birth;

        int type;
        fscanf(fp, "%d", &type);
        Abs.Array[x].Type = type;

        fscanf(fp, "%s", phone);
        strcpy(Abs.Array[x].Phone, phone);

        fscanf(fp, "%s", address);
        strcpy(Abs.Array[x].Address, address);

        fscanf(fp, "%s", workPhone);
        strcpy(Abs.Array[x].WorkPhone, workPhone);

        if (x == Abs.Size) Abs.Size++;
    }

    fclose(fp);
}
// 存入历史数据
inline void end( ) {
    FILE * fp = fopen("in.txt", "w");
    // 文件输出
    for (int i = 0; i < Abs.Size; i++) {
        fprintf(fp, "%d ", Abs.Array[i].Number);
        fprintf(fp, "%s ", Abs.Array[i].Name);
        fprintf(fp, "%d %d ", Abs.Array[i].Sex, Abs.Array[i].Age);
        fprintf(fp, "%d %d %d ",
            Abs.Array[i].Birth.year, Abs.Array[i].Birth.month, Abs.Array[i].Birth.day);
        fprintf(fp, "%d ", Abs.Array[i].Type);
        fprintf(fp, "%s %s %s\n",
            Abs.Array[i].Phone, Abs.Array[i].Address, Abs.Array[i].WorkPhone);
    }

    fclose(fp);
}
// 显示查找结果
inline void showResult(int i) {
    printf("#################################################\n");
    printf("编号：%d\n", Abs.Array[i].Number);
    printf("姓名：%s\n", Abs.Array[i].Name);
    printf("性别：");
    if (Abs.Array[i].Sex == 1) printf("男\n");
    else printf("女\n");
    printf("年龄：%d\n", Abs.Array[i].Age);
    printf("单位：%s\n", Abs.Array[i].Address);
    printf("类型：");
    switch (Abs.Array[i].Type) {
    case 0:
        printf("自己\n");
        break;
    case 1:
        printf("家人\n");
        break;
    case 2:
        printf("朋友\n");
        break;
    case 3:
        printf("同学\n");
        break;
    case 4:
        printf("同事\n");
        break;
    }
    printf("出生日期：%04d-%02d-%02d\n",
        Abs.Array[i].Birth.year, Abs.Array[i].Birth.month, Abs.Array[i].Birth.day);
    printf("办公电话：%s\n", Abs.Array[i].WorkPhone);
    printf("手机号码：%s\n", Abs.Array[i].Phone);
    printf("#################################################\n");
}
// 显示电子佛
inline void showBuddha( );
// 退出通讯录
inline void exitBook( ) {
    end( );
    sys( );
    showBuddha( );
    sys( );
    exit(0);
}
// 添加联系人
inline void addPerson( ) {
    if (Abs.Size == N) {
        printf("通讯录已满，已无法添加新联系人\n");

        sys( );
        return;
    }

    if (!ALL(Abs.Size)) return;
    Abs.Size++;
    sort(Abs.Array, Abs.Array + Abs.Size);

    printf("添加成功\n");
    sys( );
}
// 显示联系人
inline void showPerson( ) {
    if (!Abs.Size) {
        printf("暂时还没有联系人\n");

        sys( );
        return;
    }

    for (int i = 0; i < Abs.Size; i++)
        showResult(i);
    sys( );
}
// 删除联系人
inline void deletePerson( ) {
    int number = NUMBER( );
    if (number < 0) {
        sys( );
        return;
    }

    int cnt = findNumber(number);
    if (cnt == -1) {
        notFound( );
        return;
    }

    for (int i = cnt; i < Abs.Size; i++)
        Abs.Array[i] = Abs.Array[i + 1];
    Abs.Size--;
    printf("删除成功\n");
    sys( );
}
// 查找菜单
inline void showFind( ) {
    printf("#################################################\n");
    printf("##################### 1.编号 ####################\n");
    printf("##################### 2.姓名 ####################\n");
    printf("##################### 3.生日 ####################\n");
    printf("##################### 4.类型 ####################\n");
    printf("#################################################\n");
    printf("请选择要查询的内容：");
}
// 查找编号
inline void FindNumber( ) {
    int number = NUMBER( );
    if (number < 0) {
        sys( );
        return;
    }

    int cnt = findNumber(number);
    if (cnt == -1) {
        notFound( );
        return;
    }

    showResult(cnt);
    sys( );
}
// 查找生日
inline void FindBirth(struct Birthday birth) {
    bool cnt = false;
    for (int i = 0; i < Abs.Size; i++)
        if (Abs.Array[i].Birth.month == birth.month &&
            Abs.Array[i].Birth.day == birth.day) {
            showResult(i);
            cnt = true;
        }

    if (!cnt) {
        notFound( );
        return;
    }
    sys( );
}
// 查找姓名
inline void FindName( ) {
    NAME( );

    bool cnt = false;
    for (int i = 0; i < Abs.Size; i++)
        if (kmp(Abs.Array[i].Name, name) != -1) {
            showResult(i);
            cnt = true;
        }

    if (!cnt) {
        notFound( );
        return;
    }
    sys( );
}
// 查找类型
inline void FindType( ) {
    int type = TYPE( );

    bool cnt = false;
    for (int i = 0; i < Abs.Size; i++)
        if (Abs.Array[i].Type == type) {
            showResult(i);
            cnt = true;
        }

    if (!cnt) {
        notFound( );
        return;
    }
    sys( );
}
// 查询联系人
inline void findPerson( ) {
    showFind( );

    int Select = read<int>( );
    struct Birthday birth;
    switch (Select) {
    case 1:
        FindNumber( );
        break;
    case 2:
        FindName( );
        break;
    case 3:
        birth = BIRTHDAY( );
        FindBirth(birth);
        break;
    case 4:
        FindType( );
        break;
    default:
        printf("输入有误，请重新输入\n");
        sys( );
        break;
    }
}
// 修改联系人
inline void modifyPerson( ) {
    int number = NUMBER( );
    if (number < 0) {
        sys( );
        return;
    }

    int cnt = findNumber(number);
    if (cnt == -1) {
        notFound( );
        return;
    }
    if (!ALL(cnt)) return;

    sort(Abs.Array, Abs.Array + Abs.Size);
    sys( );
}
// 清空联系人
inline void clearPerson( ) {
    Abs.Size = 0;
    printf("该通讯录已清空\n");
    sys( );
}
// 批量添加联系人
inline void batchAddPerson( ) {
    FILE * fp = fopen("add.txt", "r");

    if (fp == NULL) return;
    // 文件读入
    int number;
    while (fscanf(fp, "%d", &number) != EOF) {
        int x = Abs.Size;
        int cnt = findNumber(number);
        if (cnt != -1) x = cnt;
        Abs.Array[x].Number = number;

        fscanf(fp, "%s", name);
        strcpy(Abs.Array[x].Name, name);

        int sex;
        fscanf(fp, "%d", &sex);
        Abs.Array[x].Sex = sex;

        int age;
        fscanf(fp, "%d", &age);
        Abs.Array[x].Age = age;

        struct Birthday birth;
        fscanf(fp, "%d %d %d", &birth.year, &birth.month, &birth.day);
        Abs.Array[x].Birth = birth;

        int type;
        fscanf(fp, "%d", &type);
        Abs.Array[x].Type = type;

        fscanf(fp, "%s", phone);
        strcpy(Abs.Array[x].Phone, phone);

        fscanf(fp, "%s", address);
        strcpy(Abs.Array[x].Address, address);

        fscanf(fp, "%s", workPhone);
        strcpy(Abs.Array[x].WorkPhone, workPhone);

        if (x == Abs.Size) Abs.Size++;
    }

    fclose(fp);

    sort(Abs.Array, Abs.Array + Abs.Size);
    printf("导入完成\n");
    sys( );
}
// 获取今日过生日的人
inline void getBirthday( ) {
    printf("今天过生日的有：\n");

    time_t now = time(NULL);
    tm * time = localtime(&now);

    struct Birthday birth = { time->tm_year + 1900, time->tm_mon + 1, time->tm_mday };
    FindBirth(birth);
}
// 获取当前时间
inline void getTime( ) {
    time_t now = time(NULL);
    tm * time = localtime(&now);

    printf("#################################################\n");
    printf("北京时间：%04d年%02d月%02d日 %s ",
        time->tm_year + 1900, time->tm_mon + 1, time->tm_mday, weekDay[time->tm_wday]);
    printf("%02d:%02d:%02d\n", time->tm_hour, time->tm_min, time->tm_sec);
    printf("#################################################\n");

    sys( );
}
// 主界面
inline void showMenu( ) {
    printf("#################################################\n");
    printf("################# 通讯录管理系统 ################\n");
    printf("#################################################\n");
    printf("################## 1.添加联系人 #################\n");
    printf("################## 2.显示联系人 #################\n");
    printf("################## 3.删除联系人 #################\n");
    printf("################## 4.查找联系人 #################\n");
    printf("################## 5.修改联系人 #################\n");
    printf("################## 6.清空联系人 #################\n");
    printf("################## 0.退出通讯录 #################\n");
    printf("#################################################\n");
    printf("################ 7.查看当前时间点 ###############\n");
    printf("################ 8.批量添加联系人 ###############\n");
    printf("# 请将批量添加信息文件命名为\"add.txt\", ANSI编码 #\n");
    printf("# 顺序:编号,姓名,性别,年龄,出生日期,类型,电话号 #\n");
    printf("########## 接上顺序: 单位名称,办公电话 ##########\n");
    printf("# 请检查以保证导入信息的正确性,本程序不对其勘误 #\n");
    if (FindBirthDay( )) {
        printf("#################################################\n");
        printf("###### 今天是某人的生日，输入9祝他生日快乐 ######\n");
    }
    printf("#################################################\n");
    printf("请输入选项：");
}
// 选择界面
inline void showSelect( ) {
    showMenu( );

    int Select = read<int>( );
    switch (Select) {
    case 0:
        exitBook( );
        break;
    case 1:
        addPerson( );
        break;
    case 2:
        showPerson( );
        break;
    case 3:
        deletePerson( );
        break;
    case 4:
        findPerson( );
        break;
    case 5:
        modifyPerson( );
        break;
    case 6:
        clearPerson( );
        break;
    case 7:
        getTime( );
        break;
    case 8:
        batchAddPerson( );
        break;
    case 9:
        getBirthday( );
        break;
    default:
        printf("输入有误，请重新输入\n");
        sys( );
        break;
    }
}

signed main( ) {
    Abs.Size = 0;
    start( );
    while (1)
        showSelect( );

    return 0;
}
// 显示电子佛
inline void showBuddha( ) {
    printf("#################################################\n");
    printf("############### 期待您的下次使用! ###############\n");
    printf("#################################################\n");
    printf("                    _oo0oo_ \n");
    printf("                   o8888888o \n");
    printf("                  888\" . \"888 \n");
    printf("                 (|  - _ -  |) \n");
    printf("                 0\\    =    /0 \n");
    printf("           ______ /\\_______/\\ ______ \n");
    printf("          /  |||          | //   \". \\ \n");
    printf("         /  \\\\/|      '   / ||    \"| \\ \n");
    printf("        /  __/||       -:-|||| / \\--- \\ \n");
    printf("        |     | \\ ||   - ///  |    |  | \n");
    printf("        \\  |__|  ''\\|__'_'  __/-.  /  / \n");
    printf("        / | .-\\_____        ______/-./ \n");
    printf("       _____\"'.\"    / --.--|   '.  .  ___ \n");
    printf("      /  '<   .___\\_<|>_/ ___.'  > ' = = \\ \n");
    printf("      |  | : - / ' ./' \ _ / ';. / - ' :| | \n");
    printf("      \\  \\ | '_-. ' /_ __ / '_. . /   _ ./ \n");
    printf("======= -.______ =.______/ ______/____.- ======== \n");
    printf("#################################################\n");
    printf("############### 电子佛驱散仿生bug ###############\n");
    printf("############### 求求老师,给给高分 ###############\n");
    printf("#################################################\n");
}