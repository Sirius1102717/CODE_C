#include <iostream>
#include <string>
#include<vector>
using namespace std;
struct UFD  //用户文件目录
{
    string filename;
    bool fileprotect[3];  //在c++中，bool类型按非零为true，是零为false规则执行
    vector<bool> open_protect_code;
    vector<bool> file_protect_code;
    bool openprotect[3];  //仅在文件打开时有效
    size_t read;
    size_t write;  //定义为读写指针
    size_t filelength;
    UFD* next;
};
struct MFD  //主文件目录
{
    string userName;
    size_t maxfile;  //每个用户最多拥有文件数
    UFD* ufd;
    MFD* next;
};
struct AFD  //打开文件目录
{
    UFD *head, *tail;
    size_t maxopen;
    size_t currentopen;  //当前打开文件数
};
MFD *head, *tail;  //主文件目录指针

void initUser();                  //进行用户的初始化
void displayUser();               //进行系统用户的输出
MFD* queryUser(string userName);  //进行用户的查找，找到则返回用户映射指针
bool createFile(MFD* user, string filename, bool fileprotect[3],
                size_t filelength);  //进行文件的创建操作，成功则返回true，否则返回false
bool deleteFile(MFD* user, string filename, AFD* afd);                    //进行文件删除操作
bool openFile(MFD* user, string filename, AFD* afd, bool openprotect[]);  //进行文件打开操作
bool readFile(AFD* afd, string filename);                                 //进行读操作
bool writeFile(AFD* afd, string filename);                                //进行文件的写操作
bool closeFile(AFD* afd, string filename);                                //关闭文件
void displayUserFile(MFD* user);            //进行用户文件的显示
void displayOpenFile(AFD* afd, MFD* user);  //显示打开的文件

void setfile(string userName, MFD* user)  //对文件进行各种操作
{
    AFD* afd;  //为用户初始化打开文件目录
    afd = new AFD;
    afd->head = afd->tail = nullptr;
    afd->maxopen = 5;  //最多同时打开5个文件
    afd->currentopen = 0;

    size_t command;
    string filename;
    bool fileprotect[3];
    bool openprotect[3];
    size_t filelength;
    while(1) {
        cout << "*******************欢迎进入个人文件系统！*******************" << endl;
        cout << "**     1、创建文件\t3、打开文件\t5、执行文件       **" << endl;
        cout << "**     2、删除文件\t4、关闭文件\t6、写入文件       **" << endl;
        cout << "**     0、退出登陆                                        **" << endl;
        cout << "************************************************************" << endl;
        cout << userName << "$ ";
        cin >> command;  //输入命令进行操作
        switch(command) {
            case 1:
                cout << "请输入文件名，保护码(示例:1 0 1)，文件长度：";
                cin >> filename >> fileprotect[0] >> fileprotect[1] >> fileprotect[2] >> filelength;
                createFile(user, filename, fileprotect, filelength);
                displayUserFile(user);
                break;
            case 2:
                cout << "请输入要删除的文件名：";
                cin >> filename;
                deleteFile(user, filename, afd);
                displayUserFile(user);
                break;
            case 3:
                cout << "请输入要打开的文件名，保护码(示例:1 0 1)：";
                cin >> filename >> openprotect[0] >> openprotect[1] >> openprotect[2];
                openFile(user, filename, afd, openprotect);
                displayOpenFile(afd, user);
                break;
            case 4:
                cout << "请输入要关闭的文件名：";
                cin >> filename;
                closeFile(afd, filename);
                displayOpenFile(afd, user);
                break;
            case 5:
                cout << "请输入要执行的文件名：";
                cin >> filename;
                readFile(afd, filename);
                displayOpenFile(afd, user);
                break;
            case 6:
                cout << "请输入要写入的文件名：";
                cin >> filename;
                writeFile(afd, filename);
                displayOpenFile(afd, user);
                break;
            case 0:
                cout << "您已退出登陆！" << endl;
                return;
                break;
            default: cout << "没有这项操作！" << endl; break;
        }
    }
}

void initUser() {
    cout << "请输入十位用户的名字：" << endl;
    for(size_t i = 1; i <= 10; i++)  //初始化十个不同用户
    {
        MFD* m;
        m = (MFD*)malloc(sizeof(MFD));
        if(m == nullptr) { exit(0); }
        cin >> m->userName;
        m->ufd = nullptr;
        m->next = nullptr;
        m->maxfile = 0;  //每位用户最多拥有10个文件.当前拥有0个文件
        if(head == nullptr) {
            head = tail = m;
        } else {
            tail->next = m;
            tail = m;
        }
    }
}

void displayUser() {
    MFD* m = nullptr;
    m = head;
    cout << "用户列表：";
    while(m) {
        cout << m->userName << "  ";
        m = m->next;
    }
    cout << endl;
}

MFD* queryUser(string userName) {
    MFD* m = nullptr;
    m = head;
    while(m) {
        if(userName == m->userName) return m;
        m = m->next;
    }
    return nullptr;
}

bool createFile(MFD* user, string filename, bool fileprotect[3], size_t filelength) {
    if(user->maxfile == 10) {
        cout << "文件数量已达到上限！" << endl;
        return false;
    }
    UFD* ufd = new UFD;
    if(ufd == nullptr) { return false; }
    ufd->filename = filename;
    ufd->fileprotect[0] = fileprotect[0];
    ufd->fileprotect[1] = fileprotect[1];
    ufd->fileprotect[2] = fileprotect[2];
    ufd->filelength = filelength;
    ufd->read = ufd->write = 0;
    ufd->next = nullptr;

    if(user->ufd == nullptr) {
        user->ufd = ufd;
    } else {
        UFD *op, *preOp = nullptr;
        op = user->ufd;
        while(op)  //查找是否存在同名文件
        {
            if(op->filename == ufd->filename) {

                cout << "文件 " << ufd->filename << " 已存在！" << endl;
                return false;
            }
            preOp = op;
            op = op->next;
        }
        preOp->next = ufd;
        user->maxfile++;  //文件数加一
    }
    return true;
}

void displayUserFile(MFD* user) {
    cout << "用户 " << user->userName << " 的文件列表：" << endl;
    UFD* ufd = nullptr;
    ufd = user->ufd;
    while(ufd) {
        cout << ufd->filename << " " << ufd->fileprotect[0] << " " << ufd->fileprotect[1] << " "
             << ufd->fileprotect[2] << " " << ufd->filelength << endl;
        ufd = ufd->next;
    }
}

bool deleteFile(MFD* user, string filename, AFD* afd) {
    UFD *ufd = nullptr, *prefile = nullptr, *temp;
    ufd = afd->head;
    while(ufd)  //在打开文件中查找
    {
        if(filename == ufd->filename) {
            cout << "文件\"" << filename << "\" 处于打开状态，请先关闭！\n";
            return false;
        }
        ufd = ufd->next;
    }
    ufd = user->ufd;
    while(ufd)  //在文件中进行查找
    {
        if(filename == ufd->filename) {
            if(ufd == user->ufd) {
                temp = ufd;
                user->ufd = ufd->next;
            } else {
                temp = ufd;
                prefile->next = ufd->next;
            }
            delete temp;
            cout << "文件删除成功！" << endl;
            return true;
        }
        prefile = ufd;
        ufd = ufd->next;
    }
    if(prefile->next == nullptr) {
        cout << "用户 " << user->userName << " 没有此文件：\"" << filename << "\"！" << endl;
    }
    return false;
}

bool openFile(MFD* user, char filename[], AFD* afd, bool openprotect[]) {
    UFD* ufd = nullptr;
    ufd = user->ufd;
    while(ufd) {
        if(ufd->filename == filename) break;
        ufd = ufd->next;
    }
    if(ufd) {
        UFD* xfile;
        xfile = (UFD*)malloc(sizeof(UFD));
        if(xfile == nullptr) { return false; }
        *xfile = *ufd;  //根据文件的权限进行打开权限的赋值
        if(xfile->fileprotect[0] == 0
           || openprotect[0] == 0)  //当文件权限读为0或者打开权限读为0都视为没有打开权限
        {
            cout << "没有读取权限！" << endl;
            return false;
        } else
            xfile->openprotect[0] = 1;  //可读
        //此时不管写和执行的权限是什么都不影响打开，因为后面判断权限用的是打开权限，所以我们要赋值
        if(xfile->fileprotect[1] < openprotect[1]) cout << "没有写入权限！" << endl;
        if(xfile->fileprotect[2] < openprotect[2]) cout << "没有执行权限！" << endl;
        xfile->openprotect[1] = min(xfile->fileprotect[1], openprotect[1]);  //选择权限小的写入
        xfile->openprotect[2] = min(
            xfile->fileprotect[2], openprotect[2]);  //!这个文件的一级保护码和二级保护码合并保护操作

        xfile->next = nullptr;
        if(afd->head == nullptr) {
            afd->head = afd->tail = xfile;
            afd->currentopen += 1;
        } else if(afd->currentopen < afd->maxopen) {
            afd->tail->next = xfile;
            afd->tail = xfile;
            afd->currentopen += 1;
        } else {
            cout << "文件打开数已达到上限！" << endl;
            return false;
        }
    } else {
        cout << "文件 " << filename << " 不存在！" << endl;
        return false;
    }
    return true;
}

bool closeFile(AFD* afd, string filename) {
    UFD *ufd = nullptr, *preFile = nullptr, *temp = nullptr;
    ufd = afd->head;  //在打开文件链表中进行查找
    while(ufd) {
        if(ufd->filename == filename) {
            if(ufd == afd->head) {
                if(ufd == afd->tail) {
                    temp = ufd;
                    afd->head = afd->tail = nullptr;
                } else {
                    temp = ufd;
                    afd->head = ufd->next;
                }
            } else if(ufd == afd->tail) {
                temp = ufd;
                preFile->next = nullptr;
                afd->tail = preFile;
            } else {
                temp = ufd;
                preFile->next = ufd->next;
            }
            delete temp;
            cout << "文件已关闭！" << endl;
            return true;
        }
        preFile = ufd;
        ufd = ufd->next;
    }
    cout << "该文件不存在！" << endl;
    return false;
}

bool readFile(AFD* afd, string filename) {
    UFD* ufd = nullptr;
    ufd = afd->head;
    while(ufd) {
        if(ufd->filename == filename) {
            if(ufd->openprotect[1]) {
                ufd->read++;
                return true;
            } else {
                cout << "没有执行权限！" << endl;
                return false;
            }
        }
        ufd = ufd->next;
    }
    cout << "没有此文件！" << endl;
    return false;
}

bool writeFile(AFD* afd, string filename) {
    UFD* ufd = nullptr;
    ufd = afd->head;
    while(ufd) {
        if(ufd->filename == filename) {
            if(ufd->openprotect[2]) {
                ufd->write++;
                return true;
            } else {
                cout << "没有写入权限！" << endl;
                return false;
            }
        }
        ufd = ufd->next;
    }
    cout << "没有此文件！" << endl;
    return false;
}

void displayOpenFile(AFD* afd, MFD* user) {
    cout << "用户 " << user->userName << " 的文件打开列表：" << endl;
    UFD* ufd;
    ufd = afd->head;
    while(ufd) {
        cout << ufd->filename << " " << ufd->openprotect[0] << " " << ufd->openprotect[1] << " "
             << ufd->openprotect[2] << " " << ufd->filelength << " ";
        cout << " 执行次数：" << ufd->read << "   写入次数：" << ufd->write << endl;
        ufd = ufd->next;
    }
}

int main() {
    initUser();
    string userName;
    while(true) {
        displayUser();
        cout << "（退出程序输入0）请选择一位用户登陆：";
        cin >> userName;
        MFD* user;
        user = queryUser(userName);
        if(user == nullptr)
            cout << "没有此用户，请重新输入！" << endl;
        else {
            setfile(userName, user);  //这个函数要想退出，必然是用户输入0要求退出
            //head=tail=nullptr;
        }
    }
    return 0;
}