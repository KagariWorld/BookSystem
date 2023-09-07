// 头文件
#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include "sqlite3.h"
#include<string.h>

// 全局变量
// 弹出提示框
GtkWidget *dialog_tuifang_queding;
// 登录or注册输入框
GtkWidget* entryPersonId;
GtkWidget* entryPersonName;
GtkWidget* entryPwd;
GtkWidget* entryPersonIdentify;
	GtkWidget* labelIdentifyCode;
		char yzm[5] = "";   //定义一个字符数组用于存储验证码字符串
		char color[][10]={"green","red","brown","yellow","pink","gray","purple","orange"};
GtkWidget* entryToken;

GtkWidget* entryBookId;
GtkWidget* entryBookName;
GtkWidget* entryBookCategory;
GtkWidget* entryBookNum;


char loginName[20] = ""; // 登录后保存的name
char loginId[20] = "";

sqlite3* db;
char* sqlCreate = NULL;
char sqlInsert[200] = ""; // char* sqlInsert = NULL;
char sqlSelect[200] = ""; // char* sqlSelect = NULL;
char sqlUpdate[200] = "";
char sqlDelete[200] = "";
char* errmsg = NULL;
char **tb = NULL; // 查询结果集表的地址
int r = 0, c = 0; // 有效数据行数和列数

GtkWidget* home;
	// admin窗口
	GtkWidget* admin;
		GtkWidget* adminRegister;
		GtkWidget* adminLogIn;
			GtkWidget* adminOperate;
				GtkWidget* bookIn; // 进书
				GtkWidget* bookOut; // 出库
				GtkWidget* block; // 拉黑
				GtkWidget* blacklist; // 黑名单
				GtkWidget* allHistory; // 所有历史记录
				GtkWidget* borrowHistory; // 借书历史记录
				GtkWidget* returnHistory; // 还书历史记录

				GtkWidget* borrowBooks; // 借书
				GtkWidget* myHistory; // 个人历史记录
				GtkWidget* returnBooks; // 还书
				GtkWidget* deleteAccount; // 注销
				GtkWidget* updatePassword; // 改密码
	// student窗口
	GtkWidget* student;
		GtkWidget* studentRegister;
		GtkWidget* studentLogIn;
			GtkWidget*	studentOperate;

// 初始化函数
void sqlite_init();

void home_init();
	void admin_init();
		void adminRegister_init();
		void adminLogIn_init();
			void adminOperate_init();
				void bookIn_init(); // 进书
				void bookOut_init(); // 出书
				void block_init(); // 拉黑
				void blacklist_init(); // 黑名单
				void allHistory_init(); // 所有历史记录
				void borrowHistory_init(); // 借书历史记录
				void returnHistory_init(); // 还书历史记录

				void borrowBooks_init(); // 借书
				void myHistory_init(); // 个人历史记录
				void returnBooks_init(); // 还书
				void deleteAccount_init(); // 注销
				void updatePassword_init(); // 改密码
	void student_init();
		void studentRegister_init();
		void studentLogIn_init();
			void studentOperate_init();
				void borrowBooks_student_init(); // 借书
				void myHistory_student_init(); // 个人历史记录
				void returnBooks_student_init(); // 还书
				void deleteAccount_student_init(); // 注销
				void updatePassword_student_init(); // 改密码

// 功能函数
void set_background(GtkWidget *widget, int w, int h, const gchar *path);
void load_image(GtkWidget *image, const char *file_path, const int w, const int h);
void refresh_adminRegisterOrLogIn(GtkButton *button, gpointer user_data); // 刷新admin注册或登录界面
void refresh_studentRegisterOrLogIn(GtkButton *button, gpointer user_data); // 刷新student注册或登录界面
void clist_block(GtkWidget *clist, gint row, gint column,GdkEventButton *event, gpointer data); // 拉黑
void book_join(GtkButton *button, gpointer user_data); // 进书
void clist_book_out(GtkWidget *clist, gint row, gint column,GdkEventButton *event, gpointer data); // 出书
void refresh_bookIn(GtkButton *button, gpointer user_data); // 刷新进书界面
void clist_borrow(GtkWidget *clist, gint row, gint column,GdkEventButton *event, gpointer data); // 借书
void clist_return(GtkWidget *clist, gint row, gint column,GdkEventButton *event, gpointer data); // 还书

// 跳转函数
void home_to_admin(GtkButton *button, gpointer user_data);
	void admin_to_home(GtkButton *button, gpointer user_data);
	void admin_to_adminRegister(GtkButton *button, gpointer user_data);
		void adminRegister_to_admin(GtkButton *button, gpointer user_data);
		void adminRegister_to_adminLogIn(GtkButton *button, gpointer user_data); // admin注册逻辑，注册后跳转登录界面
	void admin_to_adminLogIn(GtkButton *button, gpointer user_data);
		void adminLogIn_to_admin(GtkButton *button, gpointer user_data);
		void adminLogIn_to_adminOperate(GtkButton *button, gpointer user_data); // admin登录逻辑，登录后跳转操作界面
			void adminOperate_to_bookIn(GtkButton *button, gpointer user_data);
				void bookIn_to_adminOperate(GtkButton *button, gpointer user_data);
			void adminOperate_to_bookOut(GtkButton *button, gpointer user_data);
				void bookOut_to_adminOperate(GtkButton *button, gpointer user_data);
			void adminOperate_to_block(GtkButton *button, gpointer user_data);
				void block_to_adminOperate(GtkButton *button, gpointer user_data);
			void adminOperate_to_blacklist(GtkButton *button, gpointer user_data);
				void blacklist_to_adminOperate(GtkButton *button, gpointer user_data);
			void adminOperate_to_allHistory(GtkButton *button, gpointer user_data);
				void allHistory_to_adminOperate(GtkButton *button, gpointer user_data);
			void adminOperate_to_borrowHisotry(GtkButton *button, gpointer user_data);
				void borrowHistory_to_adminOperate(GtkButton *button, gpointer user_data);
			void adminOperate_to_returnHisotry(GtkButton *button, gpointer user_data);
				void returnHistory_to_adminOperate(GtkButton *button, gpointer user_data);

			void adminOperate_to_borrowBooks(GtkButton *button, gpointer user_data);
				void borrowBooks_to_adminOperate(GtkButton *button, gpointer user_data);
			void adminOperate_to_myHistory(GtkButton *button, gpointer user_data);
				void myHistory_to_adminOperate(GtkButton *button, gpointer user_data);
			void adminOperate_to_returnBooks(GtkButton *button, gpointer user_data);
				void returnBooks_to_adminOperate(GtkButton *button, gpointer user_data);
			void adminOperate_to_deleteAccount(GtkButton *button, gpointer user_data);
				void deleteAccount_to_home(GtkButton *button, gpointer user_data);
				void deleteAccount_to_adminOperate(GtkButton *button, gpointer user_data);
			void adminOperate_to_updatePassword(GtkButton *button, gpointer user_data);
				void updatePassword_to_home(GtkButton *button, gpointer user_data);

			void adminOperate_to_adminLogin(GtkButton *button, gpointer user_data);

void home_to_student(GtkButton *button, gpointer user_data);
	void student_to_home(GtkButton *button, gpointer user_data);
	void student_to_studentRegister(GtkButton *button, gpointer user_data);
		void studentRegister_to_studentLogIn(GtkButton *button, gpointer user_data);
		void studentRegister_to_student(GtkButton *button, gpointer user_data);
	void student_to_studentLogIn(GtkButton *button, gpointer user_data);
		void studentLogIn_to_student(GtkButton *button, gpointer user_data);
		void studentLogIn_to_studentOperate(GtkButton *button, gpointer user_data);
			void studentOperate_to_borrowBooks(GtkButton *button, gpointer user_data);
				void borrowBooks_to_studentOperate(GtkButton *button, gpointer user_data);
			void studentOperate_to_myHistory(GtkButton *button, gpointer user_data);
				void myHistory_to_studentOperate(GtkButton *button, gpointer user_data);
			void studentOperate_to_returnBooks(GtkButton *button, gpointer user_data);
				void returnBooks_to_studentOperate(GtkButton *button, gpointer user_data);
			void studentOperate_to_deleteAccount(GtkButton *button, gpointer user_data);
				void deleteAccount_to_home_student(GtkButton *button, gpointer user_data);
				void deleteAccount_to_studentOperate(GtkButton *button, gpointer user_data);
			void studentOperate_to_updatePassword(GtkButton *button, gpointer user_data);
				void updatePassword_to_home_student(GtkButton *button, gpointer user_data);

			void studentOperate_to_studentLogin(GtkButton *button, gpointer user_data);


// main函数
int main(int argc, char *argv[]) {
	sqlite_init();
	gtk_init(&argc, &argv);

	home_init();
		admin_init();
		student_init();

	gtk_widget_show_all(home);
	gtk_main();
	return 0;
}



// 初始化函数（实现）
void sqlite_init() {
	// 打开DB
	sqlite3_open("book.db", &db); // 一般不用判断打开成功或失败，除非没有权限

	// person表
	sqlCreate = "CREATE TABLE tb_person (psn_id TEXT PRIMARY KEY,psn_name TEXT,pwd TEXT,yzm TEXT,token TEXT,reputation TXET DEFAULT \'良好\');";
	errmsg = NULL;
	sqlite3_exec(db, sqlCreate, NULL, NULL, &errmsg); // 执行sqlCreate: create table
		if(errmsg != NULL) {
			if(0 == strcmp(errmsg,"table tb_person already exists") ){
				printf("table tb_person existed\n"); // 输出错误信息errmsg
			}
			else {
				printf("table tb_person create other errors!\n");
				sqlite3_close(db);
				return;
			}
		}else {
			printf("table tb_person create ok!\n");
		}
	// book表
	sqlCreate = "CREATE TABLE tb_book (book_id TEXT PRIMARY KEY,book_name TEXT,category TEXT,number INT);";
	errmsg = NULL;
	sqlite3_exec(db, sqlCreate, NULL, NULL, &errmsg); // 执行sqlCreate: create table
		if(errmsg != NULL) {
			if(0 == strcmp(errmsg,"table tb_book already exists") ){
				printf("table tb_book existed\n"); // 输出错误信息errmsg
			}
			else {
				printf("table tb_book create other errors!\n");
				sqlite3_close(db);
				return;
			}
		}else {
			printf("table tb_book create ok!\n");
		}

	// 学生-存书关系表
	sqlCreate = "CREATE TABLE tb_own (psn_id TEXT,book_id TEXT,number INT, PRIMARY KEY(psn_id,book_id));";
		errmsg = NULL;
	sqlite3_exec(db, sqlCreate, NULL, NULL, &errmsg); // 执行sqlCreate: create table
		if(errmsg != NULL) {
			if(0 == strcmp(errmsg,"table tb_own already exists") ){
				printf("table tb_own existed\n"); // 输出错误信息errmsg
			}
			else {
				printf("%s", errmsg);
				printf("table tb_own create other errors!\n");
				sqlite3_close(db);
				return;
			}
		}else {
			printf("table tb_own create ok!\n");
		}
	// history表
	sqlCreate = "CREATE TABLE tb_history (id INTEGER PRIMARY KEY AUTOINCREMENT,psn_id TEXT,data TEXT,flag SMALLINT);";
	errmsg = NULL;
	sqlite3_exec(db, sqlCreate, NULL, NULL, &errmsg); // 执行sqlCreate: create table
		if(errmsg != NULL) {
			if(0 == strcmp(errmsg,"table tb_history already exists") ){
				printf("table tb_history existed\n"); // 输出错误信息errmsg
			}
			else {
				printf("table tb_history create other errors!\n");
				sqlite3_close(db);
				return;
			}
		}else {
			printf("table tb_history create ok!\n");
		}
	  /*触发器: 对tb_book进行INSERT操作时添加history{data: XXX(人)于XXX(时间)还书XXX剩余X本, flag: 1}; 
	  					进行DELETE操作时添加{data: XXX(人)于XXX(时间)借书XXX剩余X本, flag: 0}*/
	
	// sqlCreate = "CREATE TRIGGER trigger_insert_tb_history AFTER INSERT ON tb_book BEGIN INSERT INTO tb_history(data,flag) VALUES (\'有人于\'||datetime(\'now\')||\'入书一本\',1); END;";
	// errmsg = NULL;
	// sqlite3_exec(db, sqlCreate, NULL, NULL, &errmsg);
	// 	if(errmsg != NULL) {
	// 		printf("%s", errmsg);
	// 	}else printf("trigger_insert_tb_history OK");
	// sqlCreate = "CREATE TRIGGER trigger_delete_tb_history BEFORE DELETE ON tb_book BEGIN INSERT INTO tb_history(data,flag) VALUES (\'有人于\'||datetime(\'now\')||\'出书一本\',0); END;";
	// errmsg = NULL;
	// sqlite3_exec(db, sqlCreate, NULL, NULL, &errmsg);
	// 	if(errmsg != NULL) {
	// 		printf("%s", errmsg);
	// 	}else printf("trigger_delete_tb_history OK");

	// 关闭DB
	sqlite3_close(db);
}

void home_init() {
	home = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 有顶部边栏
	gtk_widget_set_size_request(home, 1000, 600); // 最小宽1000高600
	gtk_window_set_title(GTK_WINDOW(home), "图书管理系统---主界面"); // 标题
    set_background(home, 1000, 600, "./home_background.png"); // 设置背景
    gtk_window_set_position((GtkWindow*)home,GTK_WIN_POS_CENTER);

    GtkWidget* table = gtk_table_new(4, 3, TRUE); //高4宽3
    gtk_container_add(GTK_CONTAINER(home), table);
    	
    	GtkWidget* labelTitle = gtk_label_new(NULL);
	    gtk_table_attach_defaults(GTK_TABLE(table),labelTitle,0,3,0,1); // 左右0-3，上下0-1
	    gtk_label_set_markup(GTK_LABEL(labelTitle),"<span foreground='pink' font_desc='28'>图书管理系统</span>");

	    GtkWidget* buttonAdmin = gtk_button_new();
	    gtk_button_set_relief(GTK_BUTTON(buttonAdmin), GTK_RELIEF_NONE); // 按钮背景色透明
	    gtk_table_attach_defaults(GTK_TABLE(table),buttonAdmin,1,2,2,3);
	    GtkWidget* labelButtonAdmin = gtk_label_new("");
	    gtk_label_set_markup(GTK_LABEL(labelButtonAdmin),"<span foreground='white' font_desc='16'>以管理员身份注册/登录</span>");
	    gtk_container_add(GTK_CONTAINER(buttonAdmin),labelButtonAdmin);

	    GtkWidget* buttonStudent = gtk_button_new();
	    gtk_button_set_relief(GTK_BUTTON(buttonStudent), GTK_RELIEF_NONE); // 按钮背景色透明
	    gtk_table_attach_defaults(GTK_TABLE(table),buttonStudent,1,2,3,4);
	    GtkWidget* labelButtonStudent = gtk_label_new("");
	    gtk_label_set_markup(GTK_LABEL(labelButtonStudent),"<span foreground='white' font_desc='16'>以学生身份注册/登录</span>");
	    gtk_container_add(GTK_CONTAINER(buttonStudent),labelButtonStudent);

	g_signal_connect(home,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	g_signal_connect(buttonAdmin,"pressed",G_CALLBACK(home_to_admin),NULL);
	g_signal_connect(buttonStudent,"pressed",G_CALLBACK(home_to_student),NULL);}
	void admin_init() {
		admin = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 有顶部边栏
		gtk_widget_set_size_request(admin, 1000, 600); // 最小宽1000高600
		gtk_window_set_title(GTK_WINDOW(admin), "图书管理系统---管理员界面"); // 标题
	    set_background(admin, 1000, 600, "./admin_background.png"); // 设置背景
	    gtk_window_set_position((GtkWindow*)admin,GTK_WIN_POS_CENTER);

	    GtkWidget* table = gtk_table_new(4, 3, TRUE); //高4宽3
	    gtk_container_add(GTK_CONTAINER(admin), table);
	    	GtkWidget* labelTitle = gtk_label_new(NULL);
		    gtk_table_attach_defaults(GTK_TABLE(table),labelTitle,0,3,0,1); // 左右0-3，上下0-1
		    gtk_label_set_markup(GTK_LABEL(labelTitle),"<span foreground='black' font_desc='28'>管理员界面</span>");

	    	GtkWidget* buttonAdminRegister = gtk_button_new();
		    gtk_button_set_relief(GTK_BUTTON(buttonAdminRegister), GTK_RELIEF_NONE); // 按钮背景色透明
		    gtk_table_attach_defaults(GTK_TABLE(table),buttonAdminRegister,1,3,2,3);
		    GtkWidget* labelButtonAdminRegister = gtk_label_new("");
		    gtk_label_set_markup(GTK_LABEL(labelButtonAdminRegister),"<span foreground='black' font_desc='16'>注册</span>");
		    gtk_container_add(GTK_CONTAINER(buttonAdminRegister),labelButtonAdminRegister);

		    GtkWidget* buttonAdminLogIn = gtk_button_new();
		    gtk_button_set_relief(GTK_BUTTON(buttonAdminLogIn), GTK_RELIEF_NONE); // 按钮背景色透明
		    gtk_table_attach_defaults(GTK_TABLE(table),buttonAdminLogIn,1,3,3,4);
		    GtkWidget* labelButtonAdminLogIn = gtk_label_new("");
		    gtk_label_set_markup(GTK_LABEL(labelButtonAdminLogIn),"<span foreground='black' font_desc='16'>登录</span>");
		    gtk_container_add(GTK_CONTAINER(buttonAdminLogIn),labelButtonAdminLogIn);

		    GtkWidget* buttonAdminReturnToHome = gtk_button_new();
		    gtk_button_set_relief(GTK_BUTTON(buttonAdminReturnToHome), GTK_RELIEF_NONE); // 按钮背景色透明
		    gtk_table_attach_defaults(GTK_TABLE(table),buttonAdminReturnToHome,2,3,1,2);
		    GtkWidget* labelButtonAdminReturnToHome = gtk_label_new("");
		    gtk_label_set_markup(GTK_LABEL(labelButtonAdminReturnToHome),"<span foreground='black' font_desc='16'>返回</span>");
		    gtk_container_add(GTK_CONTAINER(buttonAdminReturnToHome),labelButtonAdminReturnToHome);

		g_signal_connect(admin,"destroy",G_CALLBACK(gtk_main_quit),NULL);
		g_signal_connect(buttonAdminReturnToHome,"pressed",G_CALLBACK(admin_to_home),NULL);
		g_signal_connect(buttonAdminRegister,"pressed",G_CALLBACK(admin_to_adminRegister),NULL);
		g_signal_connect(buttonAdminLogIn,"pressed",G_CALLBACK(admin_to_adminLogIn),NULL);
	}
		void adminRegister_init() {
			adminRegister = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 有顶部边栏
			gtk_widget_set_size_request(adminRegister, 1000, 600); // 最小宽1000高600
			gtk_window_set_title(GTK_WINDOW(adminRegister), "图书管理系统---管理员注册界面"); // 标题
		    set_background(adminRegister, 1000, 600, "./adminRegister_adminLogIn_background.png"); // 设置背景
		    gtk_window_set_position((GtkWindow*)adminRegister,GTK_WIN_POS_CENTER);

		    GtkWidget* table = gtk_table_new(7, 6, TRUE); //高7宽6
		    gtk_container_add(GTK_CONTAINER(adminRegister), table);

		    	GtkWidget* labelTitle = gtk_label_new(NULL);
			    gtk_table_attach_defaults(GTK_TABLE(table),labelTitle,0,6,0,2); // 左右0-3，上下0-1
			    gtk_label_set_markup(GTK_LABEL(labelTitle),"<span foreground='pink' font_desc='28'>管理员注册界面</span>");

			    GtkWidget* buttonAdminRegisterReturnToAdmin = gtk_button_new();
				gtk_button_set_relief(GTK_BUTTON(buttonAdminRegisterReturnToAdmin), GTK_RELIEF_NONE); // 按钮背景色透明
				gtk_table_attach_defaults(GTK_TABLE(table),buttonAdminRegisterReturnToAdmin,0,1,0,1);
				GtkWidget* labelButtonAdminRegisterReturnToAdmin = gtk_label_new("");
				gtk_label_set_markup(GTK_LABEL(labelButtonAdminRegisterReturnToAdmin),"<span foreground='pink' font_desc='16'>返回</span>");
				gtk_container_add(GTK_CONTAINER(buttonAdminRegisterReturnToAdmin),labelButtonAdminRegisterReturnToAdmin);

				GtkWidget* buttonAdminRegisterRefresh = gtk_button_new();
				gtk_button_set_relief(GTK_BUTTON(buttonAdminRegisterRefresh), GTK_RELIEF_NONE); // 按钮背景色透明
				gtk_table_attach_defaults(GTK_TABLE(table),buttonAdminRegisterRefresh,0,1,1,2);
				GtkWidget* labelButtonAdminRegisterRefresh = gtk_label_new("");
				gtk_label_set_markup(GTK_LABEL(labelButtonAdminRegisterRefresh),"<span foreground='pink' font_desc='16'>刷新</span>");
				gtk_container_add(GTK_CONTAINER(buttonAdminRegisterRefresh),labelButtonAdminRegisterRefresh);

			    GtkWidget* labelId = gtk_label_new("");
			    gtk_label_set_markup(GTK_LABEL(labelId),"<span foreground='black' font_desc='20'>工号：</span>");
			    gtk_table_attach_defaults(GTK_TABLE(table),labelId,2,3,2,3);
			    entryPersonId = gtk_entry_new();
			    gtk_table_attach_defaults(GTK_TABLE(table),entryPersonId,3,5,2,3);

			    GtkWidget* labelName = gtk_label_new("");
			    gtk_label_set_markup(GTK_LABEL(labelName),"<span foreground='black' font_desc='20'>姓名：</span>");
			    gtk_table_attach_defaults(GTK_TABLE(table),labelName,2,3,3,4);
			    entryPersonName = gtk_entry_new();
			    gtk_table_attach_defaults(GTK_TABLE(table),entryPersonName,3,5,3,4);
			    
			    GtkWidget* labelPwd = gtk_label_new("");
			    gtk_label_set_markup(GTK_LABEL(labelPwd),"<span foreground='black' font_desc='20'>密码：</span>");
			    gtk_table_attach_defaults(GTK_TABLE(table),labelPwd,2,3,4,5);
			    entryPwd = gtk_entry_new();
			    gtk_table_attach_defaults(GTK_TABLE(table),entryPwd,3,5,4,5);

			    GtkWidget* labelIdentify = gtk_label_new("");
			    gtk_label_set_markup(GTK_LABEL(labelIdentify),"<span foreground='black' font_desc='20'>验证码：</span>");
			    gtk_table_attach_defaults(GTK_TABLE(table),labelIdentify,2,3,5,6);
			    entryPersonIdentify = gtk_entry_new();
			    gtk_table_attach_defaults(GTK_TABLE(table),entryPersonIdentify,3,5,5,6);
				labelIdentifyCode = gtk_label_new("");
			    gtk_table_attach_defaults(GTK_TABLE(table),labelIdentifyCode,5,6,5,6);
				    srand(time(NULL)); //设置一个随机的种子，后面生成的就全是随机数
				    //定义一个字符数组用于存储验证码字符串
				    int i = 0;
				    for (i = 0; i < 4; ++i) {
				        int a = rand()%3;//因为有三种a-z、0-9、A-Z
				        if (a==0) {
				            yzm[i] = rand()%26+'a';//在‘a’的ascii码上加上0-25就是a-z
				        }
				        else if (a==1) {
				            yzm[i] = rand()%26+'A';//在‘A’的ascii码上加上0-25就是A-Z
				        }
				        else {
				            yzm[i] = rand()%10+'0';//在‘0’的ascii码上加上0-9就是0-9
				        }
				    }//通过for循环的形式我们就生成了四位的大小写+0-9混合的验证码
				    char cmd[100] = "";
				    sprintf(cmd,"<span foreground='%s' font_desc='16'>%s</span>",color[rand()%8],yzm);
			    	gtk_label_set_markup(GTK_LABEL(labelIdentifyCode),cmd);

			    GtkWidget* labelToken = gtk_label_new("");
			    gtk_label_set_markup(GTK_LABEL(labelToken),"<span foreground='black' font_desc='20'>令牌：</span>");
			    gtk_table_attach_defaults(GTK_TABLE(table),labelToken,2,3,6,7);
			    entryToken = gtk_entry_new();
			    gtk_table_attach_defaults(GTK_TABLE(table),entryToken,3,5,6,7);

			    GtkWidget* buttonSubmit = gtk_button_new();
				gtk_button_set_relief(GTK_BUTTON(buttonSubmit), GTK_RELIEF_NONE); // 按钮背景色透明
				gtk_table_attach_defaults(GTK_TABLE(table),buttonSubmit,5,6,6,7);
				GtkWidget* labelButtonSubmit = gtk_label_new("");
				gtk_label_set_markup(GTK_LABEL(labelButtonSubmit),"<span foreground='pink' font_desc='16'>注册</span>");
				gtk_container_add(GTK_CONTAINER(buttonSubmit),labelButtonSubmit);
				
				g_signal_connect(adminRegister,"destroy",G_CALLBACK(gtk_main_quit),NULL);
			    g_signal_connect(buttonAdminRegisterRefresh,"pressed",G_CALLBACK(refresh_adminRegisterOrLogIn),NULL);
			    g_signal_connect(buttonSubmit,"pressed",G_CALLBACK(adminRegister_to_adminLogIn),NULL);
			    g_signal_connect(buttonAdminRegisterReturnToAdmin,"pressed",G_CALLBACK(adminRegister_to_admin),NULL);
		}
		void adminLogIn_init() {
			adminLogIn = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 有顶部边栏
			gtk_widget_set_size_request(adminLogIn, 1000, 600); // 最小宽1000高600
			gtk_window_set_title(GTK_WINDOW(adminLogIn), "图书管理系统---管理员登录界面"); // 标题
		    set_background(adminLogIn, 1000, 600, "./adminRegister_adminLogIn_background.png"); // 设置背景
		    gtk_window_set_position((GtkWindow*)adminLogIn,GTK_WIN_POS_CENTER);

		    GtkWidget* table = gtk_table_new(7, 6, TRUE); //高7宽6
		    gtk_container_add(GTK_CONTAINER(adminLogIn), table);

		    	GtkWidget* labelTitle = gtk_label_new(NULL);
			    gtk_table_attach_defaults(GTK_TABLE(table),labelTitle,0,6,0,2); // 左右0-3，上下0-1
			    gtk_label_set_markup(GTK_LABEL(labelTitle),"<span foreground='pink' font_desc='28'>管理员登录界面</span>");

			    GtkWidget* buttonAdminLogInReturnToAdmin = gtk_button_new();
				gtk_button_set_relief(GTK_BUTTON(buttonAdminLogInReturnToAdmin), GTK_RELIEF_NONE); // 按钮背景色透明
				gtk_table_attach_defaults(GTK_TABLE(table),buttonAdminLogInReturnToAdmin,0,1,0,1);
				GtkWidget* labelButtonAdminLogInReturnToAdmin = gtk_label_new("");
				gtk_label_set_markup(GTK_LABEL(labelButtonAdminLogInReturnToAdmin),"<span foreground='pink' font_desc='16'>返回</span>");
				gtk_container_add(GTK_CONTAINER(buttonAdminLogInReturnToAdmin),labelButtonAdminLogInReturnToAdmin);

				GtkWidget* buttonAdminLogInRefresh = gtk_button_new();
				gtk_button_set_relief(GTK_BUTTON(buttonAdminLogInRefresh), GTK_RELIEF_NONE); // 按钮背景色透明
				gtk_table_attach_defaults(GTK_TABLE(table),buttonAdminLogInRefresh,0,1,1,2);
				GtkWidget* labelButtonAdminLogInRefresh = gtk_label_new("");
				gtk_label_set_markup(GTK_LABEL(labelButtonAdminLogInRefresh),"<span foreground='pink' font_desc='16'>刷新</span>");
				gtk_container_add(GTK_CONTAINER(buttonAdminLogInRefresh),labelButtonAdminLogInRefresh);

				GtkWidget* labelId = gtk_label_new("");
			    gtk_label_set_markup(GTK_LABEL(labelId),"<span foreground='black' font_desc='20'>工号：</span>");
			    gtk_table_attach_defaults(GTK_TABLE(table),labelId,2,3,2,3);
			    entryPersonId = gtk_entry_new();
			    gtk_table_attach_defaults(GTK_TABLE(table),entryPersonId,3,5,2,3);

			    GtkWidget* labelName = gtk_label_new("");
			    gtk_label_set_markup(GTK_LABEL(labelName),"<span foreground='black' font_desc='20'>姓名：</span>");
			    gtk_table_attach_defaults(GTK_TABLE(table),labelName,2,3,3,4);
			    entryPersonName = gtk_entry_new();
			    gtk_table_attach_defaults(GTK_TABLE(table),entryPersonName,3,5,3,4);
			    
			    GtkWidget* labelPwd = gtk_label_new("");
			    gtk_label_set_markup(GTK_LABEL(labelPwd),"<span foreground='black' font_desc='20'>密码：</span>");
			    gtk_table_attach_defaults(GTK_TABLE(table),labelPwd,2,3,4,5);
			    entryPwd = gtk_entry_new();
			    gtk_table_attach_defaults(GTK_TABLE(table),entryPwd,3,5,4,5);

			    GtkWidget* labelIdentify = gtk_label_new("");
			    gtk_label_set_markup(GTK_LABEL(labelIdentify),"<span foreground='black' font_desc='20'>验证码：</span>");
			    gtk_table_attach_defaults(GTK_TABLE(table),labelIdentify,2,3,5,6);
			    entryPersonIdentify = gtk_entry_new();
			    gtk_table_attach_defaults(GTK_TABLE(table),entryPersonIdentify,3,5,5,6);
				labelIdentifyCode = gtk_label_new("");
			    gtk_table_attach_defaults(GTK_TABLE(table),labelIdentifyCode,5,6,5,6);
				    srand(time(NULL)); //设置一个随机的种子，后面生成的就全是随机数
				    //定义一个字符数组用于存储验证码字符串
				    int i = 0;
				    for (i = 0; i < 4; ++i) {
				        int a = rand()%3;//因为有三种a-z、0-9、A-Z
				        if (a==0) {
				            yzm[i] = rand()%26+'a';//在‘a’的ascii码上加上0-25就是a-z
				        }
				        else if (a==1) {
				            yzm[i] = rand()%26+'A';//在‘A’的ascii码上加上0-25就是A-Z
				        }
				        else {
				            yzm[i] = rand()%10+'0';//在‘0’的ascii码上加上0-9就是0-9
				        }
				    }//通过for循环的形式我们就生成了四位的大小写+0-9混合的验证码
				    char cmd[100] = "";
				    sprintf(cmd,"<span foreground='%s' font_desc='16'>%s</span>",color[rand()%8],yzm);
			    	gtk_label_set_markup(GTK_LABEL(labelIdentifyCode),cmd);
			    GtkWidget* labelToken = gtk_label_new("");
			    gtk_label_set_markup(GTK_LABEL(labelToken),"<span foreground='black' font_desc='20'>令牌：</span>");
			    gtk_table_attach_defaults(GTK_TABLE(table),labelToken,2,3,6,7);
			    entryToken = gtk_entry_new();
			    gtk_table_attach_defaults(GTK_TABLE(table),entryToken,3,5,6,7);

			    GtkWidget* buttonSubmit = gtk_button_new();
				gtk_button_set_relief(GTK_BUTTON(buttonSubmit), GTK_RELIEF_NONE); // 按钮背景色透明
				gtk_table_attach_defaults(GTK_TABLE(table),buttonSubmit,5,6,6,7);
				GtkWidget* labelButtonSubmit = gtk_label_new("");
				gtk_label_set_markup(GTK_LABEL(labelButtonSubmit),"<span foreground='pink' font_desc='16'>登录</span>");
				gtk_container_add(GTK_CONTAINER(buttonSubmit),labelButtonSubmit);
			
			g_signal_connect(adminLogIn,"destroy",G_CALLBACK(gtk_main_quit),NULL);
			g_signal_connect(buttonAdminLogInRefresh,"pressed",G_CALLBACK(refresh_adminRegisterOrLogIn),NULL);
			g_signal_connect(buttonSubmit,"pressed",G_CALLBACK(adminLogIn_to_adminOperate),NULL);
			g_signal_connect(buttonAdminLogInReturnToAdmin,"pressed",G_CALLBACK(adminLogIn_to_admin),NULL);
		}
			void adminOperate_init() {
				adminOperate = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 有顶部边栏
				gtk_widget_set_size_request(adminOperate, 1000, 600); // 最小宽1000高600
				gtk_window_set_title(GTK_WINDOW(adminOperate), "图书管理系统---操作界面"); // 标题
			    set_background(adminOperate, 1000, 600, "./adminOperate_background.png"); // 设置背景
			    gtk_window_set_position((GtkWindow*)adminOperate,GTK_WIN_POS_CENTER);

			    GtkWidget* table = gtk_table_new(5, 6, TRUE); //高5宽6
			    gtk_container_add(GTK_CONTAINER(adminOperate), table);


			    	GtkWidget* labelTitle = gtk_label_new(NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table),labelTitle,0,6,0,2); // 左右0-6，上下0-2
				    char cmd[100] = "";
				    sprintf(cmd,"<span foreground='red' font_desc='40'>欢迎您，管理员%s</span>",loginName);
				    gtk_label_set_markup(GTK_LABEL(labelTitle),cmd);

				    // 进书（管）
				    GtkWidget* buttonAdminOperateBookIn = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonAdminOperateBookIn), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonAdminOperateBookIn,0,1,2,3);
					GtkWidget* labelButtonAdminOperateBookIn = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonAdminOperateBookIn),"<span foreground='gray' font_desc='16'>进书</span>");
					gtk_container_add(GTK_CONTAINER(buttonAdminOperateBookIn),labelButtonAdminOperateBookIn);

					// 拉黑（管）
				    GtkWidget* buttonAdminOperateBookOut = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonAdminOperateBookOut), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonAdminOperateBookOut,1,2,2,3);
					GtkWidget* labelButtonAdminOperateBookOut = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonAdminOperateBookOut),"<span foreground='gray' font_desc='16'>出库</span>");
					gtk_container_add(GTK_CONTAINER(buttonAdminOperateBookOut),labelButtonAdminOperateBookOut);

					// 查询黑名单（管）
					GtkWidget* buttonAdminOperateLookupBlacklist = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonAdminOperateLookupBlacklist), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonAdminOperateLookupBlacklist,2,3,2,3);
					GtkWidget* labelButtonAdminOperateLookupBlacklist = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonAdminOperateLookupBlacklist),"<span foreground='gray' font_desc='16'>查询黑名单</span>");
					gtk_container_add(GTK_CONTAINER(buttonAdminOperateLookupBlacklist),labelButtonAdminOperateLookupBlacklist);

				    // 出书（管）
				    GtkWidget* buttonAdminOperateBlock = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonAdminOperateBlock), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonAdminOperateBlock,3,4,2,3);
					GtkWidget* labelButtonAdminOperateBlock = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonAdminOperateBlock),"<span foreground='gray' font_desc='16'>拉黑</span>");
					gtk_container_add(GTK_CONTAINER(buttonAdminOperateBlock),labelButtonAdminOperateBlock);

					// 查询所有借阅记录（管）
					GtkWidget* buttonAdminOperateLookupAllHistory = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonAdminOperateLookupAllHistory), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonAdminOperateLookupAllHistory,4,6,2,3);
					GtkWidget* labelButtonAdminOperateLookupAllHistory = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonAdminOperateLookupAllHistory),"<span foreground='gray' font_desc='16'>查询所有借阅记录</span>");
					gtk_container_add(GTK_CONTAINER(buttonAdminOperateLookupAllHistory),labelButtonAdminOperateLookupAllHistory);

					// 查询所有借书记录（管）
					GtkWidget* buttonAdminOperateLookupBorrowHistory = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonAdminOperateLookupBorrowHistory), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonAdminOperateLookupBorrowHistory,4,5,3,4);
					GtkWidget* labelButtonAdminOperateLookupBorrowHistory = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonAdminOperateLookupBorrowHistory),"<span foreground='gray' font_desc='16'>借书历史</span>");
					gtk_container_add(GTK_CONTAINER(buttonAdminOperateLookupBorrowHistory),labelButtonAdminOperateLookupBorrowHistory);

					// 查询所有还书记录（管）
					GtkWidget* buttonAdminOperateLookupReturnHistory = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonAdminOperateLookupReturnHistory), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonAdminOperateLookupReturnHistory,5,6,3,4);
					GtkWidget* labelButtonAdminOperateLookupReturnHistory = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonAdminOperateLookupReturnHistory),"<span foreground='gray' font_desc='16'>还书历史</span>");
					gtk_container_add(GTK_CONTAINER(buttonAdminOperateLookupReturnHistory),labelButtonAdminOperateLookupReturnHistory);

					// 借书
					GtkWidget* buttonAdminOperateBorrowBook = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonAdminOperateBorrowBook), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonAdminOperateBorrowBook,0,1,3,4);
					GtkWidget* labelButtonAdminOperateBorrowBook = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonAdminOperateBorrowBook),"<span foreground='gray' font_desc='16'>借书</span>");
					gtk_container_add(GTK_CONTAINER(buttonAdminOperateBorrowBook),labelButtonAdminOperateBorrowBook);

					// 查询个人借阅记录
					GtkWidget* buttonAdminOperateLookupMyHistory = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonAdminOperateLookupMyHistory), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonAdminOperateLookupMyHistory,1,3,3,4);
					GtkWidget* labelButtonAdminOperateLookupMyHistory = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonAdminOperateLookupMyHistory),"<span foreground='gray' font_desc='16'>查询个人借阅记录</span>");
					gtk_container_add(GTK_CONTAINER(buttonAdminOperateLookupMyHistory),labelButtonAdminOperateLookupMyHistory);

					// 还书
					GtkWidget* buttonAdminOperateReturnBook = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonAdminOperateReturnBook), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonAdminOperateReturnBook,3,4,3,4);
					GtkWidget* labelButtonAdminOperateReturnBook = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonAdminOperateReturnBook),"<span foreground='gray' font_desc='16'>还书</span>");
					gtk_container_add(GTK_CONTAINER(buttonAdminOperateReturnBook),labelButtonAdminOperateReturnBook);

					// 注销账户
					GtkWidget* buttonAdminOperateDeleteAccount = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonAdminOperateDeleteAccount), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonAdminOperateDeleteAccount,2,4,4,5);
					GtkWidget* labelButtonAdminOperateDeleteAccount = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonAdminOperateDeleteAccount),"<span foreground='gray' font_desc='16'>注销账户</span>");
					gtk_container_add(GTK_CONTAINER(buttonAdminOperateDeleteAccount),labelButtonAdminOperateDeleteAccount);

					// 修改密码
					GtkWidget* buttonAdminOperateUpdatePassword = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonAdminOperateUpdatePassword), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonAdminOperateUpdatePassword,0,2,4,5);
					GtkWidget* labelButtonAdminOperateUpdatePassword = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonAdminOperateUpdatePassword),"<span foreground='gray' font_desc='16'>修改密码</span>");
					gtk_container_add(GTK_CONTAINER(buttonAdminOperateUpdatePassword),labelButtonAdminOperateUpdatePassword);


					// 登出账户
					GtkWidget* buttonAdminOperateLogOff = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonAdminOperateLogOff), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonAdminOperateLogOff,4,6,4,5);
					GtkWidget* labelButtonAdminOperateLogOff = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonAdminOperateLogOff),"<span foreground='gray' font_desc='16'>登出账户</span>");
					gtk_container_add(GTK_CONTAINER(buttonAdminOperateLogOff),labelButtonAdminOperateLogOff);

				g_signal_connect(adminOperate,"destroy",G_CALLBACK(gtk_main_quit),NULL);
				g_signal_connect(buttonAdminOperateBookIn,"pressed",G_CALLBACK(adminOperate_to_bookIn),NULL);
				g_signal_connect(buttonAdminOperateBookOut,"pressed",G_CALLBACK(adminOperate_to_bookOut),NULL);
				g_signal_connect(buttonAdminOperateBlock,"pressed",G_CALLBACK(adminOperate_to_block),NULL);
				g_signal_connect(buttonAdminOperateLookupBlacklist,"pressed",G_CALLBACK(adminOperate_to_blacklist),NULL);
				g_signal_connect(buttonAdminOperateLookupAllHistory,"pressed",G_CALLBACK(adminOperate_to_allHistory),NULL);
				g_signal_connect(buttonAdminOperateLookupBorrowHistory,"pressed",G_CALLBACK(adminOperate_to_borrowHisotry),NULL);
				g_signal_connect(buttonAdminOperateLookupReturnHistory,"pressed",G_CALLBACK(adminOperate_to_returnHisotry),NULL);
				g_signal_connect(buttonAdminOperateBorrowBook,"pressed",G_CALLBACK(adminOperate_to_borrowBooks),NULL);
				g_signal_connect(buttonAdminOperateLookupMyHistory,"pressed",G_CALLBACK(adminOperate_to_myHistory),NULL);
				g_signal_connect(buttonAdminOperateReturnBook,"pressed",G_CALLBACK(adminOperate_to_returnBooks),NULL);
				g_signal_connect(buttonAdminOperateDeleteAccount,"pressed",G_CALLBACK(adminOperate_to_deleteAccount),NULL);
				g_signal_connect(buttonAdminOperateUpdatePassword,"pressed",G_CALLBACK(adminOperate_to_updatePassword),NULL);
				g_signal_connect(buttonAdminOperateLogOff,"pressed",G_CALLBACK(adminOperate_to_adminLogin),NULL);
			}
				void bookIn_init() {
					bookIn = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 有顶部边栏
					gtk_widget_set_size_request(bookIn, 1000, 600); // 最小宽1000高600
					gtk_window_set_title(GTK_WINDOW(bookIn), "图书管理系统---进书界面"); // 标题
				    set_background(bookIn, 1000, 600, "./adminOperate_background.png"); // 设置背景
				    gtk_window_set_position((GtkWindow*)bookIn,GTK_WIN_POS_CENTER);

				    GtkWidget* table = gtk_table_new(7, 6, TRUE); //高7宽6
				    gtk_container_add(GTK_CONTAINER(bookIn), table);

				    GtkWidget* labelTitle = gtk_label_new(NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table),labelTitle,1,6,0,2); // 左右1-6，上下0-2
				    char cmd[100] = "";
				    sprintf(cmd,"<span foreground='green' font_desc='40'>购买图书</span>");
				    gtk_label_set_markup(GTK_LABEL(labelTitle),cmd);

					GtkWidget* buttonBookInToOperate = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonBookInToOperate), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonBookInToOperate,0,1,0,1);
					GtkWidget* labelButtonBookInToOperate = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonBookInToOperate),"<span foreground='black' font_desc='16'>返回</span>");
					gtk_container_add(GTK_CONTAINER(buttonBookInToOperate),labelButtonBookInToOperate);

					GtkWidget* buttonRefresh = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonRefresh), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonRefresh,0,1,1,2);
					GtkWidget* labelButtonRefresh = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonRefresh),"<span foreground='black' font_desc='16'>刷新</span>");
					gtk_container_add(GTK_CONTAINER(buttonRefresh),labelButtonRefresh);

					GtkWidget* labelId = gtk_label_new("");
				    gtk_label_set_markup(GTK_LABEL(labelId),"<span foreground='black' font_desc='20'>图书id：</span>");
				    gtk_table_attach_defaults(GTK_TABLE(table),labelId,2,3,2,3);
				    entryBookId = gtk_entry_new();
				    gtk_table_attach_defaults(GTK_TABLE(table),entryBookId,3,6,2,3);

				    GtkWidget* labelName = gtk_label_new("");
				    gtk_label_set_markup(GTK_LABEL(labelName),"<span foreground='gray' font_desc='20'>书名：</span>");
				    gtk_table_attach_defaults(GTK_TABLE(table),labelName,2,3,3,4);
				    entryBookName = gtk_entry_new();
				    gtk_table_attach_defaults(GTK_TABLE(table),entryBookName,3,6,3,4);

				    GtkWidget* labelCategory = gtk_label_new("");
				    gtk_label_set_markup(GTK_LABEL(labelCategory),"<span foreground='black' font_desc='20'>种别：</span>");
				    gtk_table_attach_defaults(GTK_TABLE(table),labelCategory,2,3,4,5);
				    entryBookCategory = gtk_entry_new();
				    gtk_table_attach_defaults(GTK_TABLE(table),entryBookCategory,3,6,4,5);

				    GtkWidget* labelNumber = gtk_label_new("");
				    gtk_label_set_markup(GTK_LABEL(labelNumber),"<span foreground='gray' font_desc='20'>数量：</span>");
				    gtk_table_attach_defaults(GTK_TABLE(table),labelNumber,2,3,5,6);
				    entryBookNum = gtk_entry_new();
				    gtk_table_attach_defaults(GTK_TABLE(table),entryBookNum,3,6,5,6);

				    GtkWidget* buttonSubmit = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonSubmit), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonSubmit,5,6,6,7);
					GtkWidget* labelButtonSubmit = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonSubmit),"<span foreground='black' font_desc='16'>进书</span>");
					gtk_container_add(GTK_CONTAINER(buttonSubmit),labelButtonSubmit);

					g_signal_connect(bookIn,"destroy",G_CALLBACK(gtk_main_quit),NULL);
					g_signal_connect(buttonSubmit,"pressed",G_CALLBACK(book_join),NULL);
					g_signal_connect(buttonBookInToOperate,"pressed",G_CALLBACK(bookIn_to_adminOperate),NULL);
					g_signal_connect(buttonRefresh,"pressed",G_CALLBACK(refresh_bookIn),NULL);
				}
				void bookOut_init() {
					bookOut = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 有顶部边栏
					gtk_widget_set_size_request(bookOut, 1000, 600); // 最小宽1000高600
					gtk_window_set_title(GTK_WINDOW(bookOut), "图书管理系统---出书界面"); // 标题
				    set_background(bookOut, 1000, 600, "./adminOperate_background.png"); // 设置背景
				    gtk_window_set_position((GtkWindow*)bookOut,GTK_WIN_POS_CENTER);

				    GtkWidget* table = gtk_table_new(5, 6, TRUE); //高5宽6
				    gtk_container_add(GTK_CONTAINER(bookOut), table);

				    GtkWidget* labelTitle = gtk_label_new(NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table),labelTitle,1,6,0,1); // 左右1-6，上下0-1
				    char cmd[100] = "";
				    sprintf(cmd,"<span foreground='green' font_desc='40'>图书出库</span>");
				    gtk_label_set_markup(GTK_LABEL(labelTitle),cmd);

					GtkWidget* buttonBookOutToOperate = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonBookOutToOperate), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonBookOutToOperate,0,1,0,1);
					GtkWidget* labelButtonBookOutToOperate = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonBookOutToOperate),"<span foreground='black' font_desc='16'>返回</span>");
					gtk_container_add(GTK_CONTAINER(buttonBookOutToOperate),labelButtonBookOutToOperate);

					GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table), scrolled_window, 0, 6, 1, 5);// 把按钮加入布局

				    // GTK_POLICY_AUTOMATIC：滚动条根据需要自动出现时
				    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

				    //创建一个带titles（分栏列表）的clist控件
				    gchar * listTitle[4] = {"id","书名","种别","剩余数量"};
				    GtkWidget* clist = gtk_clist_new_with_titles(4,listTitle);
					gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), clist); // 将clist放入滚动条中

				    gtk_clist_set_column_width(GTK_CLIST(clist),0,250); //设置第0列宽300
				    gtk_clist_set_column_justification(GTK_CLIST(clist),0,GTK_JUSTIFY_CENTER); //给clist 的第0列设置居中
				    gtk_clist_set_column_width(GTK_CLIST(clist),1,250);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),1,GTK_JUSTIFY_CENTER);
				    gtk_clist_set_column_width(GTK_CLIST(clist),2,250);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),2,GTK_JUSTIFY_CENTER);
				    gtk_clist_set_column_width(GTK_CLIST(clist),3,250);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),3,GTK_JUSTIFY_CENTER);

				    sqlite3_open("book.db", &db);
					memset(sqlSelect,'\0',sizeof(sqlSelect));
					sprintf(sqlSelect,"SELECT book_id,book_name,category,number FROM tb_book;");

					tb = NULL;
					r = 0;
					c = 0;
					errmsg = NULL;
					sqlite3_get_table(db, sqlSelect, &tb, &r, &c, &errmsg); // 执行db: select from tb
					if(errmsg != NULL) {
						printf("select error： %s\n",errmsg); // 输出错误信息errmsg
						sqlite3_close(db);
						return;
					}
					int i = 0, k = 0;
					char* list_text[4];
					for(i = 1; i < r+1; i++) { // r+1行
						for(k = 0; k < c; k++) { // c列
							printf(" [%s] ",tb[i*c+k]);
							list_text[k] = tb[i*c+k];
						}
						gtk_clist_append(GTK_CLIST(clist),list_text); // 添加list_text数组到clist中
					    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), clist); // 将clist放入滚动条中
						printf("\n");
					}
				    g_signal_connect(clist, "select-row", G_CALLBACK(clist_book_out), NULL);

					g_signal_connect(bookOut,"destroy",G_CALLBACK(gtk_main_quit),NULL);
					g_signal_connect(buttonBookOutToOperate,"pressed",G_CALLBACK(bookOut_to_adminOperate),NULL);
				}
				void block_init() {
					block = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 有顶部边栏
					gtk_widget_set_size_request(block, 1000, 600); // 最小宽1000高600
					gtk_window_set_title(GTK_WINDOW(block), "图书管理系统---拉黑界面"); // 标题
				    set_background(block, 1000, 600, "./adminOperate_background.png"); // 设置背景
				    gtk_window_set_position((GtkWindow*)block,GTK_WIN_POS_CENTER);

				    GtkWidget* table = gtk_table_new(5, 6, TRUE); //高5宽6
				    gtk_container_add(GTK_CONTAINER(block), table);


				    GtkWidget* labelTitle = gtk_label_new(NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table),labelTitle,1,6,0,1); // 左右1-6，上下0-1
				    char cmd[100] = "";
				    sprintf(cmd,"<span foreground='green' font_desc='40'>拉黑系统</span>");
				    gtk_label_set_markup(GTK_LABEL(labelTitle),cmd);


				    GtkWidget* buttonBlockToOperate = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonBlockToOperate), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonBlockToOperate,0,1,0,1);
					GtkWidget* labelButtonBlockToOperate = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonBlockToOperate),"<span foreground='black' font_desc='16'>返回</span>");
					gtk_container_add(GTK_CONTAINER(buttonBlockToOperate),labelButtonBlockToOperate);

				     /* 创建一个滚动窗口构件，将GtkCList组装到里面。
				     * 这样使得内容超出列表时，可以用滚动条浏览
				     * 第一个参数是水平方向的调整对象，
				     * 第二个参数是垂直方向的调整对象。
				     * 它们总是设置为NULL。
				     */
				    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table), scrolled_window, 0, 6, 1, 5);// 把按钮加入布局

				    // GTK_POLICY_AUTOMATIC：滚动条根据需要自动出现时
				    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

				    //创建一个带titles（分栏列表）的clist控件
				    gchar * listTitle[3] = {"id","名字","信用度"};
				    GtkWidget* clist = gtk_clist_new_with_titles(3,listTitle);
					gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), clist); // 将clist放入滚动条中

				    gtk_clist_set_column_width(GTK_CLIST(clist),0,333); //设置第0列宽300
				    gtk_clist_set_column_justification(GTK_CLIST(clist),0,GTK_JUSTIFY_CENTER); //给clist 的第0列设置居中
				    gtk_clist_set_column_width(GTK_CLIST(clist),1,333);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),1,GTK_JUSTIFY_CENTER);
				    gtk_clist_set_column_width(GTK_CLIST(clist),2,333);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),2,GTK_JUSTIFY_CENTER);

				    sqlite3_open("book.db", &db);
					memset(sqlSelect,'\0',sizeof(sqlSelect));
					sprintf(sqlSelect,"SELECT psn_id,psn_name,reputation FROM tb_person;");

					tb = NULL;
					r = 0;
					c = 0;
					errmsg = NULL;
					sqlite3_get_table(db, sqlSelect, &tb, &r, &c, &errmsg); // 执行db: select from tb
					if(errmsg != NULL) {
						printf("select error： %s\n",errmsg); // 输出错误信息errmsg
						sqlite3_close(db);
						return;
					}
					int i = 0, k = 0;
					char* list_text[3];
					for(i = 1; i < r+1; i++) { // r+1行
						for(k = 0; k < c; k++) { // c列
							printf(" [%s] ",tb[i*c+k]);
							list_text[k] = tb[i*c+k];
						}
						gtk_clist_append(GTK_CLIST(clist),list_text); // 添加list_text数组到clist中
					    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), clist); // 将clist放入滚动条中
						printf("\n");
					}


					sqlite3_close(db);
				    g_signal_connect(block,"destroy",G_CALLBACK(gtk_main_quit),NULL);
				    g_signal_connect(clist, "select-row", G_CALLBACK(clist_block), NULL);
				    g_signal_connect(buttonBlockToOperate,"pressed",G_CALLBACK(block_to_adminOperate),NULL);
				}
				void blacklist_init() {
					blacklist = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 有顶部边栏
					gtk_widget_set_size_request(blacklist, 1000, 600); // 最小宽1000高600
					gtk_window_set_title(GTK_WINDOW(blacklist), "图书管理系统---黑名单界面"); // 标题
				    set_background(blacklist, 1000, 600, "./adminOperate_background.png"); // 设置背景
				    gtk_window_set_position((GtkWindow*)blacklist,GTK_WIN_POS_CENTER);

				    GtkWidget* table = gtk_table_new(5, 6, TRUE); //高5宽6
				    gtk_container_add(GTK_CONTAINER(blacklist), table);



				    GtkWidget* buttonBlacklistToOperate = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonBlacklistToOperate), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonBlacklistToOperate,0,1,0,1);
					GtkWidget* labelButtonBlacklistToOperate = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonBlacklistToOperate),"<span foreground='black' font_desc='16'>返回</span>");
					gtk_container_add(GTK_CONTAINER(buttonBlacklistToOperate),labelButtonBlacklistToOperate);


				    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table), scrolled_window, 0, 6, 1, 5);// 把按钮加入布局

				    GtkWidget* labelTitle = gtk_label_new(NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table),labelTitle,1,6,0,1); // 左右1-6，上下0-1
				    char cmd[100] = "";
				    sprintf(cmd,"<span foreground='green' font_desc='40'>黑名单用户统计</span>");
				    gtk_label_set_markup(GTK_LABEL(labelTitle),cmd);

				    // GTK_POLICY_AUTOMATIC：滚动条根据需要自动出现时
				    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

				    //创建一个带titles（分栏列表）的clist控件
				    gchar * listTitle[4] = {"id","名字","令牌","信用度"};
				    GtkWidget* clist = gtk_clist_new_with_titles(4,listTitle);
					gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), clist); // 将clist放入滚动条中

				    gtk_clist_set_column_width(GTK_CLIST(clist),0,250); //设置第0列宽300
				    gtk_clist_set_column_justification(GTK_CLIST(clist),0,GTK_JUSTIFY_CENTER); //给clist 的第0列设置居中
				    gtk_clist_set_column_width(GTK_CLIST(clist),1,250);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),1,GTK_JUSTIFY_CENTER);
				    gtk_clist_set_column_width(GTK_CLIST(clist),2,250);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),2,GTK_JUSTIFY_CENTER);
				    gtk_clist_set_column_width(GTK_CLIST(clist),3,250);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),3,GTK_JUSTIFY_CENTER);

				    sqlite3_open("book.db", &db);
					memset(sqlSelect,'\0',sizeof(sqlSelect));
					sprintf(sqlSelect,"SELECT psn_id,psn_name,token,reputation FROM tb_person WHERE reputation=\'差\';");

					tb = NULL;
					r = 0;
					c = 0;
					errmsg = NULL;
					sqlite3_get_table(db, sqlSelect, &tb, &r, &c, &errmsg); // 执行db: select from tb
					if(errmsg != NULL) {
						printf("select error： %s\n",errmsg); // 输出错误信息errmsg
						sqlite3_close(db);
						return;
					}
					int i = 0, k = 0;
					char* list_text[4];
					for(i = 1; i < r+1; i++) { // r+1行
						for(k = 0; k < c; k++) { // c列
							printf(" [%s] ",tb[i*c+k]);
							list_text[k] = tb[i*c+k];
						}
						gtk_clist_append(GTK_CLIST(clist),list_text); // 添加list_text数组到clist中
					    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), clist); // 将clist放入滚动条中
						printf("\n");
					}

					sqlite3_close(db);
				    g_signal_connect(blacklist,"destroy",G_CALLBACK(gtk_main_quit),NULL);
				    g_signal_connect(buttonBlacklistToOperate,"pressed",G_CALLBACK(blacklist_to_adminOperate),NULL);
				}
				void allHistory_init() {
					allHistory = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 有顶部边栏
					gtk_widget_set_size_request(allHistory, 1000, 600); // 最小宽1000高600
					gtk_window_set_title(GTK_WINDOW(allHistory), "图书管理系统---所有历史记录界面"); // 标题
				    set_background(allHistory, 1000, 600, "./adminOperate_background.png"); // 设置背景
				    gtk_window_set_position((GtkWindow*)allHistory,GTK_WIN_POS_CENTER);

				    GtkWidget* table = gtk_table_new(5, 6, TRUE); //高5宽6
				    gtk_container_add(GTK_CONTAINER(allHistory), table);

				    GtkWidget* labelTitle = gtk_label_new(NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table),labelTitle,1,6,0,1); // 左右1-6，上下0-1
				    char cmd[100] = "";
				    sprintf(cmd,"<span foreground='green' font_desc='40'>系统内历史记录</span>");
				    gtk_label_set_markup(GTK_LABEL(labelTitle),cmd);

				    GtkWidget* buttonAllHistoryToOperate = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonAllHistoryToOperate), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonAllHistoryToOperate,0,1,0,1);
					GtkWidget* labelButtonAllHistoryToOperate = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonAllHistoryToOperate),"<span foreground='black' font_desc='16'>返回</span>");
					gtk_container_add(GTK_CONTAINER(buttonAllHistoryToOperate),labelButtonAllHistoryToOperate);

					GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table), scrolled_window, 0, 6, 1, 5);// 把按钮加入布局

				    // GTK_POLICY_AUTOMATIC：滚动条根据需要自动出现时
				    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

				    //创建一个带titles（分栏列表）的clist控件
				    gchar * listTitle[4] = {"id","学/工号","历史记录","flag（0为借书，1为还书）"};
				    GtkWidget* clist = gtk_clist_new_with_titles(4,listTitle);
					gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), clist); // 将clist放入滚动条中

				    gtk_clist_set_column_width(GTK_CLIST(clist),0,100); //设置第0列宽300
				    gtk_clist_set_column_justification(GTK_CLIST(clist),0,GTK_JUSTIFY_CENTER); //给clist 的第0列设置居中
				    gtk_clist_set_column_width(GTK_CLIST(clist),1,250);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),1,GTK_JUSTIFY_CENTER);
				    gtk_clist_set_column_width(GTK_CLIST(clist),2,400);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),2,GTK_JUSTIFY_CENTER);
				    gtk_clist_set_column_width(GTK_CLIST(clist),3,250);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),3,GTK_JUSTIFY_CENTER);

				    sqlite3_open("book.db", &db);
					memset(sqlSelect,'\0',sizeof(sqlSelect));
					sprintf(sqlSelect,"SELECT id,psn_id,data,flag FROM tb_history;");

					tb = NULL;
					r = 0;
					c = 0;
					errmsg = NULL;
					sqlite3_get_table(db, sqlSelect, &tb, &r, &c, &errmsg); // 执行db: select from tb
					if(errmsg != NULL) {
						printf("select error： %s\n",errmsg); // 输出错误信息errmsg
						sqlite3_close(db);
						return;
					}
					int i = 0, k = 0;
					char* list_text[4];
					for(i = 1; i < r+1; i++) { // r+1行
						for(k = 0; k < c; k++) { // c列
							list_text[k] = tb[i*c+k];
						}
						gtk_clist_append(GTK_CLIST(clist),list_text); // 添加list_text数组到clist中
					    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), clist); // 将clist放入滚动条中
						printf("\n");
					}

				    g_signal_connect(allHistory,"destroy",G_CALLBACK(gtk_main_quit),NULL);
				    g_signal_connect(buttonAllHistoryToOperate,"pressed",G_CALLBACK(allHistory_to_adminOperate),NULL);
				}
				void borrowHistory_init() {
					borrowHistory = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 有顶部边栏
					gtk_widget_set_size_request(borrowHistory, 1000, 600); // 最小宽1000高600
					gtk_window_set_title(GTK_WINDOW(borrowHistory), "图书管理系统---所有借书历史记录界面"); // 标题
				    set_background(borrowHistory, 1000, 600, "./adminOperate_background.png"); // 设置背景
				    gtk_window_set_position((GtkWindow*)borrowHistory,GTK_WIN_POS_CENTER);

				    GtkWidget* table = gtk_table_new(5, 6, TRUE); //高5宽6
				    gtk_container_add(GTK_CONTAINER(borrowHistory), table);

				    GtkWidget* labelTitle = gtk_label_new(NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table),labelTitle,1,6,0,1); // 左右1-6，上下0-1
				    char cmd[100] = "";
				    sprintf(cmd,"<span foreground='green' font_desc='40'>所有借书历史记录</span>");
				    gtk_label_set_markup(GTK_LABEL(labelTitle),cmd);

				    GtkWidget* buttonBorrowHistoryToOperate = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonBorrowHistoryToOperate), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonBorrowHistoryToOperate,0,1,0,1);
					GtkWidget* labelButtonBorrowHistoryToOperate = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonBorrowHistoryToOperate),"<span foreground='black' font_desc='16'>返回</span>");
					gtk_container_add(GTK_CONTAINER(buttonBorrowHistoryToOperate),labelButtonBorrowHistoryToOperate);

					GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table), scrolled_window, 0, 6, 1, 5);// 把按钮加入布局

				    // GTK_POLICY_AUTOMATIC：滚动条根据需要自动出现时
				    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

				    //创建一个带titles（分栏列表）的clist控件
				    gchar * listTitle[3] = {"id","学/工号","借书记录"};
				    GtkWidget* clist = gtk_clist_new_with_titles(3,listTitle);
					gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), clist); // 将clist放入滚动条中

				    gtk_clist_set_column_width(GTK_CLIST(clist),0,333); //设置第0列宽300
				    gtk_clist_set_column_justification(GTK_CLIST(clist),0,GTK_JUSTIFY_CENTER); //给clist 的第0列设置居中
				    gtk_clist_set_column_width(GTK_CLIST(clist),1,333);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),1,GTK_JUSTIFY_CENTER);
				    gtk_clist_set_column_width(GTK_CLIST(clist),2,333);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),2,GTK_JUSTIFY_CENTER);
				    

				    sqlite3_open("book.db", &db);
					memset(sqlSelect,'\0',sizeof(sqlSelect));
					sprintf(sqlSelect,"SELECT id,psn_id,data FROM tb_history WHERE flag=0;");

					tb = NULL;
					r = 0;
					c = 0;
					errmsg = NULL;
					sqlite3_get_table(db, sqlSelect, &tb, &r, &c, &errmsg); // 执行db: select from tb
					if(errmsg != NULL) {
						printf("select error： %s\n",errmsg); // 输出错误信息errmsg
						sqlite3_close(db);
						return;
					}
					int i = 0, k = 0;
					char* list_text[3];
					for(i = 1; i < r+1; i++) { // r+1行
						for(k = 0; k < c; k++) { // c列
							list_text[k] = tb[i*c+k];
						}
						gtk_clist_append(GTK_CLIST(clist),list_text); // 添加list_text数组到clist中
					    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), clist); // 将clist放入滚动条中
						printf("\n");
					}

				    g_signal_connect(borrowHistory,"destroy",G_CALLBACK(gtk_main_quit),NULL);
				    g_signal_connect(buttonBorrowHistoryToOperate,"pressed",G_CALLBACK(borrowHistory_to_adminOperate),NULL);
				}
				void returnHistory_init() {
					returnHistory = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 有顶部边栏
					gtk_widget_set_size_request(returnHistory, 1000, 600); // 最小宽1000高600
					gtk_window_set_title(GTK_WINDOW(returnHistory), "图书管理系统---所有还书历史记录界面"); // 标题
				    set_background(returnHistory, 1000, 600, "./adminOperate_background.png"); // 设置背景
				    gtk_window_set_position((GtkWindow*)returnHistory,GTK_WIN_POS_CENTER);

				    GtkWidget* table = gtk_table_new(5, 6, TRUE); //高5宽6
				    gtk_container_add(GTK_CONTAINER(returnHistory), table);

				    GtkWidget* labelTitle = gtk_label_new(NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table),labelTitle,1,6,0,1); // 左右1-6，上下0-1
				    char cmd[100] = "";
				    sprintf(cmd,"<span foreground='green' font_desc='40'>所有还书历史记录</span>");
				    gtk_label_set_markup(GTK_LABEL(labelTitle),cmd);

				    GtkWidget* buttonReturnHistoryToOperate = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonReturnHistoryToOperate), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonReturnHistoryToOperate,0,1,0,1);
					GtkWidget* labelButtonReturnHistoryToOperate = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonReturnHistoryToOperate),"<span foreground='black' font_desc='16'>返回</span>");
					gtk_container_add(GTK_CONTAINER(buttonReturnHistoryToOperate),labelButtonReturnHistoryToOperate);

					GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table), scrolled_window, 0, 6, 1, 5);// 把按钮加入布局

				    // GTK_POLICY_AUTOMATIC：滚动条根据需要自动出现时
				    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

				    //创建一个带titles（分栏列表）的clist控件
				    gchar * listTitle[3] = {"id","学/工号","还书记录"};
				    GtkWidget* clist = gtk_clist_new_with_titles(3,listTitle);
					gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), clist); // 将clist放入滚动条中

				    gtk_clist_set_column_width(GTK_CLIST(clist),0,333); //设置第0列宽300
				    gtk_clist_set_column_justification(GTK_CLIST(clist),0,GTK_JUSTIFY_CENTER); //给clist 的第0列设置居中
				    gtk_clist_set_column_width(GTK_CLIST(clist),1,333);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),1,GTK_JUSTIFY_CENTER);
				    gtk_clist_set_column_width(GTK_CLIST(clist),2,333);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),2,GTK_JUSTIFY_CENTER);
				    

				    sqlite3_open("book.db", &db);
					memset(sqlSelect,'\0',sizeof(sqlSelect));
					sprintf(sqlSelect,"SELECT id,psn_id,data FROM tb_history WHERE flag=1;");

					tb = NULL;
					r = 0;
					c = 0;
					errmsg = NULL;
					sqlite3_get_table(db, sqlSelect, &tb, &r, &c, &errmsg); // 执行db: select from tb
					if(errmsg != NULL) {
						printf("select error： %s\n",errmsg); // 输出错误信息errmsg
						sqlite3_close(db);
						return;
					}
					int i = 0, k = 0;
					char* list_text[3];
					for(i = 1; i < r+1; i++) { // r+1行
						for(k = 0; k < c; k++) { // c列
							list_text[k] = tb[i*c+k];
						}
						gtk_clist_append(GTK_CLIST(clist),list_text); // 添加list_text数组到clist中
					    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), clist); // 将clist放入滚动条中
						printf("\n");
					}

				    g_signal_connect(returnHistory,"destroy",G_CALLBACK(gtk_main_quit),NULL);
				    g_signal_connect(buttonReturnHistoryToOperate,"pressed",G_CALLBACK(returnHistory_to_adminOperate),NULL);
				}

				void borrowBooks_init() {
					borrowBooks = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 有顶部边栏
					gtk_widget_set_size_request(borrowBooks, 1000, 600); // 最小宽1000高600
					gtk_window_set_title(GTK_WINDOW(borrowBooks), "图书管理系统---借书界面"); // 标题
				    set_background(borrowBooks, 1000, 600, "./adminOperate_background.png"); // 设置背景
				    gtk_window_set_position((GtkWindow*)borrowBooks,GTK_WIN_POS_CENTER);

				    GtkWidget* table = gtk_table_new(5, 6, TRUE); //高5宽6
				    gtk_container_add(GTK_CONTAINER(borrowBooks), table);

				    GtkWidget* labelTitle = gtk_label_new(NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table),labelTitle,1,6,0,1); // 左右1-6，上下0-1
				    char cmd[100] = "";
				    sprintf(cmd,"<span foreground='green' font_desc='40'>借书系统</span>");
				    gtk_label_set_markup(GTK_LABEL(labelTitle),cmd);

				    GtkWidget* buttonBorrowBooksToOperate = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonBorrowBooksToOperate), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonBorrowBooksToOperate,0,1,0,1);
					GtkWidget* labelButtonBorrowBooksToOperate = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonBorrowBooksToOperate),"<span foreground='black' font_desc='16'>返回</span>");
					gtk_container_add(GTK_CONTAINER(buttonBorrowBooksToOperate),labelButtonBorrowBooksToOperate);

					GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table), scrolled_window, 0, 6, 1, 5);// 把按钮加入布局

				    // GTK_POLICY_AUTOMATIC：滚动条根据需要自动出现时
				    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

				    //创建一个带titles（分栏列表）的clist控件
				    gchar * listTitle[4] = {"id","书名","种别","剩余数量"};
				    GtkWidget* clist = gtk_clist_new_with_titles(4,listTitle);
					gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), clist); // 将clist放入滚动条中

				    gtk_clist_set_column_width(GTK_CLIST(clist),0,250); //设置第0列宽300
				    gtk_clist_set_column_justification(GTK_CLIST(clist),0,GTK_JUSTIFY_CENTER); //给clist 的第0列设置居中
				    gtk_clist_set_column_width(GTK_CLIST(clist),1,250);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),1,GTK_JUSTIFY_CENTER);
				    gtk_clist_set_column_width(GTK_CLIST(clist),2,250);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),2,GTK_JUSTIFY_CENTER);
				    gtk_clist_set_column_width(GTK_CLIST(clist),3,250);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),3,GTK_JUSTIFY_CENTER);

				    sqlite3_open("book.db", &db);
					memset(sqlSelect,'\0',sizeof(sqlSelect));
					sprintf(sqlSelect,"SELECT book_id,book_name,category,number FROM tb_book;");

					tb = NULL;
					r = 0;
					c = 0;
					errmsg = NULL;
					sqlite3_get_table(db, sqlSelect, &tb, &r, &c, &errmsg); // 执行db: select from tb
					if(errmsg != NULL) {
						printf("select error： %s\n",errmsg); // 输出错误信息errmsg
						sqlite3_close(db);
						return;
					}
					int i = 0, k = 0;
					char* list_text[4];
					for(i = 1; i < r+1; i++) { // r+1行
						for(k = 0; k < c; k++) { // c列
							list_text[k] = tb[i*c+k];
						}
						gtk_clist_append(GTK_CLIST(clist),list_text); // 添加list_text数组到clist中
					    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), clist); // 将clist放入滚动条中
					}
				    g_signal_connect(clist, "select-row", G_CALLBACK(clist_borrow), NULL);					

				    g_signal_connect(borrowBooks,"destroy",G_CALLBACK(gtk_main_quit),NULL);
				    g_signal_connect(buttonBorrowBooksToOperate,"pressed",G_CALLBACK(borrowBooks_to_adminOperate),NULL);
				}
				void myHistory_init() {
					myHistory = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 有顶部边栏
					gtk_widget_set_size_request(myHistory, 1000, 600); // 最小宽1000高600
					gtk_window_set_title(GTK_WINDOW(myHistory), "图书管理系统---我的历史记录界面"); // 标题
				    set_background(myHistory, 1000, 600, "./adminOperate_background.png"); // 设置背景
				    gtk_window_set_position((GtkWindow*)myHistory,GTK_WIN_POS_CENTER);

				    GtkWidget* table = gtk_table_new(5, 6, TRUE); //高5宽6
				    gtk_container_add(GTK_CONTAINER(myHistory), table);

				    GtkWidget* labelTitle = gtk_label_new(NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table),labelTitle,1,6,0,1); // 左右1-6，上下0-1
				    char cmd[100] = "";
				    sprintf(cmd,"<span foreground='green' font_desc='40'>个人历史记录</span>");
				    gtk_label_set_markup(GTK_LABEL(labelTitle),cmd);

				    GtkWidget* buttonMyHistoryToOperate = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonMyHistoryToOperate), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonMyHistoryToOperate,0,1,0,1);
					GtkWidget* labelButtonMyHistoryToOperate = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonMyHistoryToOperate),"<span foreground='black' font_desc='16'>返回</span>");
					gtk_container_add(GTK_CONTAINER(buttonMyHistoryToOperate),labelButtonMyHistoryToOperate);

				    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table), scrolled_window, 0, 6, 1, 5);// 把按钮加入布局

				    // GTK_POLICY_AUTOMATIC：滚动条根据需要自动出现时
				    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

				    //创建一个带titles（分栏列表）的clist控件
				    gchar * listTitle[2] = {"历史记录","flag（0为借书，1为还书）"};
				    GtkWidget* clist = gtk_clist_new_with_titles(2,listTitle);
					gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), clist); // 将clist放入滚动条中

				    gtk_clist_set_column_width(GTK_CLIST(clist),0,500); //设置第0列宽300
				    gtk_clist_set_column_justification(GTK_CLIST(clist),0,GTK_JUSTIFY_CENTER); //给clist 的第0列设置居中
				    gtk_clist_set_column_width(GTK_CLIST(clist),1,500);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),1,GTK_JUSTIFY_CENTER);
				    

				    sqlite3_open("book.db", &db);
					memset(sqlSelect,'\0',sizeof(sqlSelect));
					sprintf(sqlSelect,"SELECT data,flag FROM tb_history WHERE psn_id=\'%s\';",loginId);

					tb = NULL;
					r = 0;
					c = 0;
					errmsg = NULL;
					sqlite3_get_table(db, sqlSelect, &tb, &r, &c, &errmsg); // 执行db: select from tb
					if(errmsg != NULL) {
						printf("select error： %s\n",errmsg); // 输出错误信息errmsg
						sqlite3_close(db);
						return;
					}
					int i = 0, k = 0;
					char* list_text[2];
					for(i = 1; i < r+1; i++) { // r+1行
						for(k = 0; k < c; k++) { // c列
							list_text[k] = tb[i*c+k];
						}
						gtk_clist_append(GTK_CLIST(clist),list_text); // 添加list_text数组到clist中
					    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), clist); // 将clist放入滚动条中
						printf("\n");
					}

				    g_signal_connect(myHistory,"destroy",G_CALLBACK(gtk_main_quit),NULL);
				    g_signal_connect(buttonMyHistoryToOperate,"pressed",G_CALLBACK(myHistory_to_adminOperate),NULL);
				}
				void returnBooks_init() {
					returnBooks = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 有顶部边栏
					gtk_widget_set_size_request(returnBooks, 1000, 600); // 最小宽1000高600
					gtk_window_set_title(GTK_WINDOW(returnBooks), "图书管理系统---还书界面"); // 标题
				    set_background(returnBooks, 1000, 600, "./adminOperate_background.png"); // 设置背景
				    gtk_window_set_position((GtkWindow*)returnBooks,GTK_WIN_POS_CENTER);

				    GtkWidget* table = gtk_table_new(5, 6, TRUE); //高5宽6
				    gtk_container_add(GTK_CONTAINER(returnBooks), table);

				    GtkWidget* labelTitle = gtk_label_new(NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table),labelTitle,1,6,0,1); // 左右1-6，上下0-1
				    char cmd[100] = "";
				    sprintf(cmd,"<span foreground='green' font_desc='40'>还书系统</span>");
				    gtk_label_set_markup(GTK_LABEL(labelTitle),cmd);

				    GtkWidget* buttonReturnBooksToOperate = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonReturnBooksToOperate), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonReturnBooksToOperate,0,1,0,1);
					GtkWidget* labelButtonReturnBooksToOperate = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonReturnBooksToOperate),"<span foreground='black' font_desc='16'>返回</span>");
					gtk_container_add(GTK_CONTAINER(buttonReturnBooksToOperate),labelButtonReturnBooksToOperate);


					GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table), scrolled_window, 0, 6, 1, 5);// 把按钮加入布局

				    // GTK_POLICY_AUTOMATIC：滚动条根据需要自动出现时
				    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

				    //创建一个带titles（分栏列表）的clist控件
				    gchar * listTitle[4] = {"id","书名","种别","剩余数量"};
				    GtkWidget* clist = gtk_clist_new_with_titles(4,listTitle);
					gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), clist); // 将clist放入滚动条中

				    gtk_clist_set_column_width(GTK_CLIST(clist),0,250); //设置第0列宽300
				    gtk_clist_set_column_justification(GTK_CLIST(clist),0,GTK_JUSTIFY_CENTER); //给clist 的第0列设置居中
				    gtk_clist_set_column_width(GTK_CLIST(clist),1,250);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),1,GTK_JUSTIFY_CENTER);
				    gtk_clist_set_column_width(GTK_CLIST(clist),2,250);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),2,GTK_JUSTIFY_CENTER);
				    gtk_clist_set_column_width(GTK_CLIST(clist),3,250);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),3,GTK_JUSTIFY_CENTER);

				    sqlite3_open("book.db", &db);
					memset(sqlSelect,'\0',sizeof(sqlSelect));
					sprintf(sqlSelect,"SELECT tb_own.book_id,book_name,category,tb_own.number FROM tb_own,tb_book WHERE tb_book.book_id=tb_own.book_id AND psn_id=\'%s\';",loginId);

					tb = NULL;
					r = 0;
					c = 0;
					errmsg = NULL;
					sqlite3_get_table(db, sqlSelect, &tb, &r, &c, &errmsg); // 执行db: select from tb
					if(errmsg != NULL) {
						printf("select error： %s\n",errmsg); // 输出错误信息errmsg
						sqlite3_close(db);
						return;
					}
					int i = 0, k = 0;
					char* list_text[4];
					for(i = 1; i < r+1; i++) { // r+1行
						for(k = 0; k < c; k++) { // c列
							list_text[k] = tb[i*c+k];
						}
						gtk_clist_append(GTK_CLIST(clist),list_text); // 添加list_text数组到clist中
					    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), clist); // 将clist放入滚动条中
					}
				    g_signal_connect(clist, "select-row", G_CALLBACK(clist_return), NULL);



				    g_signal_connect(returnBooks,"destroy",G_CALLBACK(gtk_main_quit),NULL);
				    g_signal_connect(buttonReturnBooksToOperate,"pressed",G_CALLBACK(returnBooks_to_adminOperate),NULL);
				}
				void deleteAccount_init() {
					deleteAccount = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 有顶部边栏
					// GdkScreen *screen = gdk_screen_get_default();
					// gint screen_w = gdk_screen_get_width(screen);
					// gint screen_h = gdk_screen_get_height(screen);
					// gtk_window_move(GTK_WINDOW(deleteAccount), (screen_w *0.2), (screen_h *0.3));
					gtk_widget_set_size_request(deleteAccount, 500, 300); // 最小宽500高300
					gtk_window_set_title(GTK_WINDOW(deleteAccount), "图书管理系统---注销界面"); // 标题
				    set_background(deleteAccount, 500, 300, "./adminOperate_background.png"); // 设置背景
				    gtk_window_set_position((GtkWindow*)deleteAccount,GTK_WIN_POS_CENTER);
				    GtkWidget* table = gtk_table_new(4, 4, TRUE); //高4宽4
				    gtk_container_add(GTK_CONTAINER(deleteAccount), table);


				    GtkWidget* labelTitle0 = gtk_label_new(NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table),labelTitle0,0,4,0,1.5); // 左右1-6，上下0-1
				    char cmd0[100] = "";
				    sprintf(cmd0,"<span foreground='red' font_desc='40'>是否确定注销</span>");
				    gtk_label_set_markup(GTK_LABEL(labelTitle0),cmd0);


				    GtkWidget* labelTitle = gtk_label_new(NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table),labelTitle,0,4,1.5,3); // 左右1-6，上下0-1
				    char cmd[100] = "";
				    sprintf(cmd,"<span foreground='red' font_desc='40'>(此操作不可逆转)</span>");
				    gtk_label_set_markup(GTK_LABEL(labelTitle),cmd);


				    GtkWidget* buttonDeleteAccountYes = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonDeleteAccountYes), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonDeleteAccountYes,0,2,3,4);
					GtkWidget* labelButtonDeleteAccountYes = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonDeleteAccountYes),"<span foreground='red' font_desc='16'>是</span>");
					gtk_container_add(GTK_CONTAINER(buttonDeleteAccountYes),labelButtonDeleteAccountYes);

					GtkWidget* buttonDeleteAccountNo = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonDeleteAccountNo), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonDeleteAccountNo,2,4,3,4);
					GtkWidget* labelButtonDeleteAccountNo = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonDeleteAccountNo),"<span foreground='black' font_desc='16'>否</span>");
					gtk_container_add(GTK_CONTAINER(buttonDeleteAccountNo),labelButtonDeleteAccountNo);

				    g_signal_connect(buttonDeleteAccountYes,"pressed",G_CALLBACK(deleteAccount_to_home),NULL);
				    g_signal_connect(buttonDeleteAccountNo,"pressed",G_CALLBACK(deleteAccount_to_adminOperate),NULL);
				}
				void updatePassword_init() {
					updatePassword = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 有顶部边栏
					// GdkScreen *screen = gdk_screen_get_default();
					// gint screen_w = gdk_screen_get_width(screen);
					// gint screen_h = gdk_screen_get_height(screen);
					// gtk_window_move(GTK_WINDOW(updatePassword), (screen_w *0.2), (screen_h *0.3));
					gtk_widget_set_size_request(updatePassword, 500, 150); // 最小宽1000高600
					gtk_window_set_position((GtkWindow*)updatePassword,GTK_WIN_POS_CENTER);
					gtk_window_set_title(GTK_WINDOW(updatePassword), "图书管理系统---更改密码界面"); // 标题

				    GtkWidget* table = gtk_table_new(2, 4, TRUE); //高宽
				    gtk_container_add(GTK_CONTAINER(updatePassword), table);

					GtkWidget* labelPwd = gtk_label_new("");
				    gtk_label_set_markup(GTK_LABEL(labelPwd),"<span foreground='black' font_desc='20'>新密码：</span>");
				    gtk_table_attach_defaults(GTK_TABLE(table),labelPwd,0,1,0,1);
				    entryPwd = gtk_entry_new();
				    gtk_table_attach_defaults(GTK_TABLE(table),entryPwd,1,4,0,1);
					GtkWidget* buttonUpdatePasswordAccountYes = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonUpdatePasswordAccountYes), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonUpdatePasswordAccountYes,1,3,1,2);
					GtkWidget* labelButtonUpdatePasswordAccountYes = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonUpdatePasswordAccountYes),"<span foreground='black' font_desc='16'>更改</span>");
					gtk_container_add(GTK_CONTAINER(buttonUpdatePasswordAccountYes),labelButtonUpdatePasswordAccountYes);

					g_signal_connect(buttonUpdatePasswordAccountYes,"pressed",G_CALLBACK(updatePassword_to_home),NULL);
				}
				
	void student_init() {
		student = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 有顶部边栏
		gtk_widget_set_size_request(student, 1000, 600); // 最小宽1000高600
		gtk_window_set_title(GTK_WINDOW(student), "图书管理系统---学生界面"); // 标题
	    set_background(student, 1000, 600, "./student_background.png"); // 设置背景
	    gtk_window_set_position((GtkWindow*)student,GTK_WIN_POS_CENTER);
	    GtkWidget* table = gtk_table_new(4, 3, TRUE); //高4宽3
	    gtk_container_add(GTK_CONTAINER(student), table);
	    	GtkWidget* labelTitle = gtk_label_new(NULL);
		    gtk_table_attach_defaults(GTK_TABLE(table),labelTitle,0,3,0,1); // 左右0-3，上下0-1
		    gtk_label_set_markup(GTK_LABEL(labelTitle),"<span foreground='pink' font_desc='28'>学生界面</span>");

	    	GtkWidget* buttonStudentRegister = gtk_button_new();
		    gtk_button_set_relief(GTK_BUTTON(buttonStudentRegister), GTK_RELIEF_NONE); // 按钮背景色透明
		    gtk_table_attach_defaults(GTK_TABLE(table),buttonStudentRegister,1,3,2,3);
		    GtkWidget* labelButtonStudentRegister = gtk_label_new("");
		    gtk_label_set_markup(GTK_LABEL(labelButtonStudentRegister),"<span foreground='gray' font_desc='16'>注册</span>");
		    gtk_container_add(GTK_CONTAINER(buttonStudentRegister),labelButtonStudentRegister);

		    GtkWidget* buttonStudentLogIn = gtk_button_new();
		    gtk_button_set_relief(GTK_BUTTON(buttonStudentLogIn), GTK_RELIEF_NONE); // 按钮背景色透明
		    gtk_table_attach_defaults(GTK_TABLE(table),buttonStudentLogIn,1,3,3,4);
		    GtkWidget* labelButtonStudentLogIn = gtk_label_new("");
		    gtk_label_set_markup(GTK_LABEL(labelButtonStudentLogIn),"<span foreground='gray' font_desc='16'>登录</span>");
		    gtk_container_add(GTK_CONTAINER(buttonStudentLogIn),labelButtonStudentLogIn);

		    GtkWidget* buttonStudentReturnToHome = gtk_button_new();
		    gtk_button_set_relief(GTK_BUTTON(buttonStudentReturnToHome), GTK_RELIEF_NONE); // 按钮背景色透明
		    gtk_table_attach_defaults(GTK_TABLE(table),buttonStudentReturnToHome,2,3,1,2);
		    GtkWidget* labelButtonStudentReturnToHome = gtk_label_new("");
		    gtk_label_set_markup(GTK_LABEL(labelButtonStudentReturnToHome),"<span foreground='gray' font_desc='16'>返回</span>");
		    gtk_container_add(GTK_CONTAINER(buttonStudentReturnToHome),labelButtonStudentReturnToHome);

		g_signal_connect(student,"destroy",G_CALLBACK(gtk_main_quit),NULL);
		g_signal_connect(buttonStudentReturnToHome,"pressed",G_CALLBACK(student_to_home),NULL);
		g_signal_connect(buttonStudentRegister,"pressed",G_CALLBACK(student_to_studentRegister),NULL);
		g_signal_connect(buttonStudentLogIn,"pressed",G_CALLBACK(student_to_studentLogIn),NULL);
	}
		void studentRegister_init() {
			studentRegister = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 有顶部边栏
			gtk_widget_set_size_request(studentRegister, 1000, 600); // 最小宽1000高600
			gtk_window_set_title(GTK_WINDOW(studentRegister), "图书管理系统---学生注册界面"); // 标题
		    set_background(studentRegister, 1000, 600, "./studentRegister_studentLogIn_background.png"); // 设置背景
		    gtk_window_set_position((GtkWindow*)studentRegister,GTK_WIN_POS_CENTER);

		    GtkWidget* table = gtk_table_new(6, 3, TRUE); //高6宽3
		    gtk_container_add(GTK_CONTAINER(studentRegister), table);

		    	GtkWidget* labelTitle = gtk_label_new(NULL);
			    gtk_table_attach_defaults(GTK_TABLE(table),labelTitle,0,6,0,2); // 左右0-3，上下0-1
			    gtk_label_set_markup(GTK_LABEL(labelTitle),"<span foreground='pink' font_desc='28'>学生注册界面</span>");

			    GtkWidget* buttonStudentRegisterReturnToStudent = gtk_button_new();
				gtk_button_set_relief(GTK_BUTTON(buttonStudentRegisterReturnToStudent), GTK_RELIEF_NONE); // 按钮背景色透明
				gtk_table_attach_defaults(GTK_TABLE(table),buttonStudentRegisterReturnToStudent,0,1,0,1);
				GtkWidget* labelButtonStudentRegisterReturnToStudent = gtk_label_new("");
				gtk_label_set_markup(GTK_LABEL(labelButtonStudentRegisterReturnToStudent),"<span foreground='pink' font_desc='16'>返回</span>");
				gtk_container_add(GTK_CONTAINER(buttonStudentRegisterReturnToStudent),labelButtonStudentRegisterReturnToStudent);

				GtkWidget* buttonStudentRegisterRefresh = gtk_button_new();
				gtk_button_set_relief(GTK_BUTTON(buttonStudentRegisterRefresh), GTK_RELIEF_NONE); // 按钮背景色透明
				gtk_table_attach_defaults(GTK_TABLE(table),buttonStudentRegisterRefresh,0,1,1,2);
				GtkWidget* labelButtonStudentRegisterRefresh = gtk_label_new("");
				gtk_label_set_markup(GTK_LABEL(labelButtonStudentRegisterRefresh),"<span foreground='pink' font_desc='16'>刷新</span>");
				gtk_container_add(GTK_CONTAINER(buttonStudentRegisterRefresh),labelButtonStudentRegisterRefresh);

			    GtkWidget* labelId = gtk_label_new("");
			    gtk_label_set_markup(GTK_LABEL(labelId),"<span foreground='black' font_desc='20'>学号：</span>");
			    gtk_table_attach_defaults(GTK_TABLE(table),labelId,2,3,2,3);
			    entryPersonId = gtk_entry_new();
			    gtk_table_attach_defaults(GTK_TABLE(table),entryPersonId,3,5,2,3);

			    GtkWidget* labelName = gtk_label_new("");
			    gtk_label_set_markup(GTK_LABEL(labelName),"<span foreground='black' font_desc='20'>姓名：</span>");
			    gtk_table_attach_defaults(GTK_TABLE(table),labelName,2,3,3,4);
			    entryPersonName = gtk_entry_new();
			    gtk_table_attach_defaults(GTK_TABLE(table),entryPersonName,3,5,3,4);
			    
			    GtkWidget* labelPwd = gtk_label_new("");
			    gtk_label_set_markup(GTK_LABEL(labelPwd),"<span foreground='black' font_desc='20'>密码：</span>");
			    gtk_table_attach_defaults(GTK_TABLE(table),labelPwd,2,3,4,5);
			    entryPwd = gtk_entry_new();
			    gtk_table_attach_defaults(GTK_TABLE(table),entryPwd,3,5,4,5);

			    GtkWidget* labelIdentify = gtk_label_new("");
			    gtk_label_set_markup(GTK_LABEL(labelIdentify),"<span foreground='black' font_desc='20'>验证码：</span>");
			    gtk_table_attach_defaults(GTK_TABLE(table),labelIdentify,2,3,5,6);
			    entryPersonIdentify = gtk_entry_new();
			    gtk_table_attach_defaults(GTK_TABLE(table),entryPersonIdentify,3,5,5,6);
				labelIdentifyCode = gtk_label_new("");
			    gtk_table_attach_defaults(GTK_TABLE(table),labelIdentifyCode,5,6,5,6);
				    srand(time(NULL)); //设置一个随机的种子，后面生成的就全是随机数
				    //定义一个字符数组用于存储验证码字符串
				    int i = 0;
				    for (i = 0; i < 4; ++i) {
				        int a = rand()%3;//因为有三种a-z、0-9、A-Z
				        if (a==0) {
				            yzm[i] = rand()%26+'a';//在‘a’的ascii码上加上0-25就是a-z
				        }
				        else if (a==1) {
				            yzm[i] = rand()%26+'A';//在‘A’的ascii码上加上0-25就是A-Z
				        }
				        else {
				            yzm[i] = rand()%10+'0';//在‘0’的ascii码上加上0-9就是0-9
				        }
				    }//通过for循环的形式我们就生成了四位的大小写+0-9混合的验证码
				    char cmd[100] = "";
				    sprintf(cmd,"<span foreground='%s' font_desc='16'>%s</span>",color[rand()%8],yzm);
			    	gtk_label_set_markup(GTK_LABEL(labelIdentifyCode),cmd);

			    GtkWidget* buttonSubmit = gtk_button_new();
				gtk_button_set_relief(GTK_BUTTON(buttonSubmit), GTK_RELIEF_NONE); // 按钮背景色透明
				gtk_table_attach_defaults(GTK_TABLE(table),buttonSubmit,5,6,6,7);
				GtkWidget* labelButtonSubmit = gtk_label_new("");
				gtk_label_set_markup(GTK_LABEL(labelButtonSubmit),"<span foreground='pink' font_desc='16'>注册</span>");
				gtk_container_add(GTK_CONTAINER(buttonSubmit),labelButtonSubmit);
				
				g_signal_connect(studentRegister,"destroy",G_CALLBACK(gtk_main_quit),NULL);
			    g_signal_connect(buttonStudentRegisterRefresh,"pressed",G_CALLBACK(refresh_studentRegisterOrLogIn),NULL);
			    g_signal_connect(buttonSubmit,"pressed",G_CALLBACK(studentRegister_to_studentLogIn),NULL);
			    g_signal_connect(buttonStudentRegisterReturnToStudent,"pressed",G_CALLBACK(studentRegister_to_student),NULL);
		}
		void studentLogIn_init() {
			studentLogIn = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 有顶部边栏
			gtk_widget_set_size_request(studentLogIn, 1000, 600); // 最小宽1000高600
			gtk_window_set_title(GTK_WINDOW(studentLogIn), "图书管理系统---学生登录界面"); // 标题
		    set_background(studentLogIn, 1000, 600, "./studentRegister_studentLogIn_background.png"); // 设置背景
		    gtk_window_set_position((GtkWindow*)studentLogIn,GTK_WIN_POS_CENTER);

		    GtkWidget* table = gtk_table_new(6, 3, TRUE); //高6宽3
		    gtk_container_add(GTK_CONTAINER(studentLogIn), table);

		    	GtkWidget* labelTitle = gtk_label_new(NULL);
			    gtk_table_attach_defaults(GTK_TABLE(table),labelTitle,0,6,0,2); // 左右0-3，上下0-1
			    gtk_label_set_markup(GTK_LABEL(labelTitle),"<span foreground='pink' font_desc='28'>学生登录界面</span>");

			    GtkWidget* buttonStudentLogInReturnToStudent = gtk_button_new();
				gtk_button_set_relief(GTK_BUTTON(buttonStudentLogInReturnToStudent), GTK_RELIEF_NONE); // 按钮背景色透明
				gtk_table_attach_defaults(GTK_TABLE(table),buttonStudentLogInReturnToStudent,0,1,0,1);
				GtkWidget* labelButtonStudentLogInReturnToStudent = gtk_label_new("");
				gtk_label_set_markup(GTK_LABEL(labelButtonStudentLogInReturnToStudent),"<span foreground='pink' font_desc='16'>返回</span>");
				gtk_container_add(GTK_CONTAINER(buttonStudentLogInReturnToStudent),labelButtonStudentLogInReturnToStudent);

				GtkWidget* buttonStudentLogInRefresh = gtk_button_new();
				gtk_button_set_relief(GTK_BUTTON(buttonStudentLogInRefresh), GTK_RELIEF_NONE); // 按钮背景色透明
				gtk_table_attach_defaults(GTK_TABLE(table),buttonStudentLogInRefresh,0,1,1,2);
				GtkWidget* labelButtonStudentLogInRefresh = gtk_label_new("");
				gtk_label_set_markup(GTK_LABEL(labelButtonStudentLogInRefresh),"<span foreground='pink' font_desc='16'>刷新</span>");
				gtk_container_add(GTK_CONTAINER(buttonStudentLogInRefresh),labelButtonStudentLogInRefresh);

				GtkWidget* labelId = gtk_label_new("");
			    gtk_label_set_markup(GTK_LABEL(labelId),"<span foreground='black' font_desc='20'>学号：</span>");
			    gtk_table_attach_defaults(GTK_TABLE(table),labelId,2,3,2,3);
			    entryPersonId = gtk_entry_new();
			    gtk_table_attach_defaults(GTK_TABLE(table),entryPersonId,3,5,2,3);

			    GtkWidget* labelName = gtk_label_new("");
			    gtk_label_set_markup(GTK_LABEL(labelName),"<span foreground='black' font_desc='20'>姓名：</span>");
			    gtk_table_attach_defaults(GTK_TABLE(table),labelName,2,3,3,4);
			    entryPersonName = gtk_entry_new();
			    gtk_table_attach_defaults(GTK_TABLE(table),entryPersonName,3,5,3,4);
			    
			    GtkWidget* labelPwd = gtk_label_new("");
			    gtk_label_set_markup(GTK_LABEL(labelPwd),"<span foreground='black' font_desc='20'>密码：</span>");
			    gtk_table_attach_defaults(GTK_TABLE(table),labelPwd,2,3,4,5);
			    entryPwd = gtk_entry_new();
			    gtk_table_attach_defaults(GTK_TABLE(table),entryPwd,3,5,4,5);

			    GtkWidget* labelIdentify = gtk_label_new("");
			    gtk_label_set_markup(GTK_LABEL(labelIdentify),"<span foreground='black' font_desc='20'>验证码：</span>");
			    gtk_table_attach_defaults(GTK_TABLE(table),labelIdentify,2,3,5,6);
			    entryPersonIdentify = gtk_entry_new();
			    gtk_table_attach_defaults(GTK_TABLE(table),entryPersonIdentify,3,5,5,6);
				labelIdentifyCode = gtk_label_new("");
			    gtk_table_attach_defaults(GTK_TABLE(table),labelIdentifyCode,5,6,5,6);
				    srand(time(NULL)); //设置一个随机的种子，后面生成的就全是随机数
				    //定义一个字符数组用于存储验证码字符串
				    int i = 0;
				    for (i = 0; i < 4; ++i) {
				        int a = rand()%3;//因为有三种a-z、0-9、A-Z
				        if (a==0) {
				            yzm[i] = rand()%26+'a';//在‘a’的ascii码上加上0-25就是a-z
				        }
				        else if (a==1) {
				            yzm[i] = rand()%26+'A';//在‘A’的ascii码上加上0-25就是A-Z
				        }
				        else {
				            yzm[i] = rand()%10+'0';//在‘0’的ascii码上加上0-9就是0-9
				        }
				    }//通过for循环的形式我们就生成了四位的大小写+0-9混合的验证码
				    char cmd[100] = "";
				    sprintf(cmd,"<span foreground='%s' font_desc='16'>%s</span>",color[rand()%8],yzm);
			    	gtk_label_set_markup(GTK_LABEL(labelIdentifyCode),cmd);

			    GtkWidget* buttonSubmit = gtk_button_new();
				gtk_button_set_relief(GTK_BUTTON(buttonSubmit), GTK_RELIEF_NONE); // 按钮背景色透明
				gtk_table_attach_defaults(GTK_TABLE(table),buttonSubmit,5,6,6,7);
				GtkWidget* labelButtonSubmit = gtk_label_new("");
				gtk_label_set_markup(GTK_LABEL(labelButtonSubmit),"<span foreground='pink' font_desc='16'>登录</span>");
				gtk_container_add(GTK_CONTAINER(buttonSubmit),labelButtonSubmit);
			
			g_signal_connect(studentLogIn,"destroy",G_CALLBACK(gtk_main_quit),NULL);
			g_signal_connect(buttonStudentLogInRefresh,"pressed",G_CALLBACK(refresh_studentRegisterOrLogIn),NULL);
			g_signal_connect(buttonSubmit,"pressed",G_CALLBACK(studentLogIn_to_studentOperate),NULL);
			g_signal_connect(buttonStudentLogInReturnToStudent,"pressed",G_CALLBACK(studentLogIn_to_student),NULL);
		}
			void studentOperate_init() {
				studentOperate = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 有顶部边栏
				gtk_widget_set_size_request(studentOperate, 1000, 600); // 最小宽1000高600
				gtk_window_set_title(GTK_WINDOW(studentOperate), "图书管理系统---操作界面"); // 标题
			    set_background(studentOperate, 1000, 600, "./studentOperate_background.png"); // 设置背景
			    gtk_window_set_position((GtkWindow*)studentOperate,GTK_WIN_POS_CENTER);

			    GtkWidget* table = gtk_table_new(5, 6, TRUE); //高5宽6
			    gtk_container_add(GTK_CONTAINER(studentOperate), table);


			    	GtkWidget* labelTitle = gtk_label_new(NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table),labelTitle,0,6,0,2); // 左右0-6，上下0-2
				    char cmd[100] = "";
				    sprintf(cmd,"<span foreground='red' font_desc='40'>欢迎您，%s同学</span>",loginName);
				    gtk_label_set_markup(GTK_LABEL(labelTitle),cmd);


					// 借书
					GtkWidget* buttonStudentOperateBorrowBook = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonStudentOperateBorrowBook), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonStudentOperateBorrowBook,0,2,2,3);
					GtkWidget* labelButtonStudentOperateBorrowBook = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonStudentOperateBorrowBook),"<span foreground='black' font_desc='16'>借书</span>");
					gtk_container_add(GTK_CONTAINER(buttonStudentOperateBorrowBook),labelButtonStudentOperateBorrowBook);

					// 查询个人借阅记录
					GtkWidget* buttonStudentOperateLookupMyHistory = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonStudentOperateLookupMyHistory), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonStudentOperateLookupMyHistory,2,4,2,3);
					GtkWidget* labelButtonStudentOperateLookupMyHistory = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonStudentOperateLookupMyHistory),"<span foreground='yellow' font_desc='16'>查询个人借阅记录</span>");
					gtk_container_add(GTK_CONTAINER(buttonStudentOperateLookupMyHistory),labelButtonStudentOperateLookupMyHistory);

					// 还书
					GtkWidget* buttonStudentOperateReturnBook = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonStudentOperateReturnBook), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonStudentOperateReturnBook,4,6,2,3);
					GtkWidget* labelButtonStudentOperateReturnBook = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonStudentOperateReturnBook),"<span foreground='black' font_desc='16'>还书</span>");
					gtk_container_add(GTK_CONTAINER(buttonStudentOperateReturnBook),labelButtonStudentOperateReturnBook);

					// 注销账户
					GtkWidget* buttonStudentOperateDeleteAccount = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonStudentOperateDeleteAccount), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonStudentOperateDeleteAccount,0,2,3,4);
					GtkWidget* labelButtonStudentOperateDeleteAccount = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonStudentOperateDeleteAccount),"<span foreground='gray' font_desc='16'>注销账户</span>");
					gtk_container_add(GTK_CONTAINER(buttonStudentOperateDeleteAccount),labelButtonStudentOperateDeleteAccount);

					// 修改密码
					GtkWidget* buttonStudentOperateUpdatePassword = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonStudentOperateUpdatePassword), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonStudentOperateUpdatePassword,2,4,3,4);
					GtkWidget* labelButtonStudentOperateUpdatePassword = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonStudentOperateUpdatePassword),"<span foreground='gray' font_desc='16'>修改密码</span>");
					gtk_container_add(GTK_CONTAINER(buttonStudentOperateUpdatePassword),labelButtonStudentOperateUpdatePassword);


					// 登出账户
					GtkWidget* buttonStudentOperateLogOff = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonStudentOperateLogOff), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonStudentOperateLogOff,4,6,4,5);
					GtkWidget* labelButtonAdminOperateLogOff = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonAdminOperateLogOff),"<span foreground='gray' font_desc='16'>登出账户</span>");
					gtk_container_add(GTK_CONTAINER(buttonStudentOperateLogOff),labelButtonAdminOperateLogOff);

				g_signal_connect(studentOperate,"destroy",G_CALLBACK(gtk_main_quit),NULL);
				
				g_signal_connect(buttonStudentOperateBorrowBook,"pressed",G_CALLBACK(studentOperate_to_borrowBooks),NULL);
				g_signal_connect(buttonStudentOperateLookupMyHistory,"pressed",G_CALLBACK(studentOperate_to_myHistory),NULL);
				g_signal_connect(buttonStudentOperateReturnBook,"pressed",G_CALLBACK(studentOperate_to_returnBooks),NULL);
				g_signal_connect(buttonStudentOperateDeleteAccount,"pressed",G_CALLBACK(studentOperate_to_deleteAccount),NULL);
				g_signal_connect(buttonStudentOperateUpdatePassword,"pressed",G_CALLBACK(studentOperate_to_updatePassword),NULL);
				g_signal_connect(buttonStudentOperateLogOff,"pressed",G_CALLBACK(studentOperate_to_studentLogin),NULL);
			}
				void borrowBooks_student_init() {
					borrowBooks = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 有顶部边栏
					gtk_widget_set_size_request(borrowBooks, 1000, 600); // 最小宽1000高600
					gtk_window_set_title(GTK_WINDOW(borrowBooks), "图书管理系统---借书界面"); // 标题
				    set_background(borrowBooks, 1000, 600, "./studentOperate_background.png"); // 设置背景
				    gtk_window_set_position((GtkWindow*)borrowBooks,GTK_WIN_POS_CENTER);

				    GtkWidget* table = gtk_table_new(5, 6, TRUE); //高5宽6
				    gtk_container_add(GTK_CONTAINER(borrowBooks), table);
				    
				    GtkWidget* labelTitle = gtk_label_new(NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table),labelTitle,0,6,0,1); // 左右1-6，上下0-1
				    char cmd[100] = "";
				    sprintf(cmd,"<span foreground='red' font_desc='40'>借书系统</span>");
				    gtk_label_set_markup(GTK_LABEL(labelTitle),cmd);

				    GtkWidget* buttonBorrowBooksToOperate = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonBorrowBooksToOperate), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonBorrowBooksToOperate,0,1,0,1);
					GtkWidget* labelButtonBorrowBooksToOperate = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonBorrowBooksToOperate),"<span foreground='black' font_desc='16'>返回</span>");
					gtk_container_add(GTK_CONTAINER(buttonBorrowBooksToOperate),labelButtonBorrowBooksToOperate);

					GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table), scrolled_window, 0, 6, 1, 5);// 把按钮加入布局

				    // GTK_POLICY_AUTOMATIC：滚动条根据需要自动出现时
				    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

				    //创建一个带titles（分栏列表）的clist控件
				    gchar * listTitle[4] = {"id","书名","种别","剩余数量"};
				    GtkWidget* clist = gtk_clist_new_with_titles(4,listTitle);
					gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), clist); // 将clist放入滚动条中

				    gtk_clist_set_column_width(GTK_CLIST(clist),0,250); //设置第0列宽300
				    gtk_clist_set_column_justification(GTK_CLIST(clist),0,GTK_JUSTIFY_CENTER); //给clist 的第0列设置居中
				    gtk_clist_set_column_width(GTK_CLIST(clist),1,250);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),1,GTK_JUSTIFY_CENTER);
				    gtk_clist_set_column_width(GTK_CLIST(clist),2,250);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),2,GTK_JUSTIFY_CENTER);
				    gtk_clist_set_column_width(GTK_CLIST(clist),3,250);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),3,GTK_JUSTIFY_CENTER);

				    sqlite3_open("book.db", &db);
					memset(sqlSelect,'\0',sizeof(sqlSelect));
					sprintf(sqlSelect,"SELECT book_id,book_name,category,number FROM tb_book;");

					tb = NULL;
					r = 0;
					c = 0;
					errmsg = NULL;
					sqlite3_get_table(db, sqlSelect, &tb, &r, &c, &errmsg); // 执行db: select from tb
					if(errmsg != NULL) {
						printf("select error： %s\n",errmsg); // 输出错误信息errmsg
						sqlite3_close(db);
						return;
					}
					int i = 0, k = 0;
					char* list_text[4];
					for(i = 1; i < r+1; i++) { // r+1行
						for(k = 0; k < c; k++) { // c列
							list_text[k] = tb[i*c+k];
						}
						gtk_clist_append(GTK_CLIST(clist),list_text); // 添加list_text数组到clist中
					    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), clist); // 将clist放入滚动条中
					}
				    g_signal_connect(clist, "select-row", G_CALLBACK(clist_borrow), NULL);					

				    g_signal_connect(borrowBooks,"destroy",G_CALLBACK(gtk_main_quit),NULL);
				    g_signal_connect(buttonBorrowBooksToOperate,"pressed",G_CALLBACK(borrowBooks_to_studentOperate),NULL);
				}
				void myHistory_student_init() {
					myHistory = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 有顶部边栏
					gtk_widget_set_size_request(myHistory, 1000, 600); // 最小宽1000高600
					gtk_window_set_title(GTK_WINDOW(myHistory), "图书管理系统---我的历史记录界面"); // 标题
				    set_background(myHistory, 1000, 600, "./studentOperate_background.png"); // 设置背景
				    gtk_window_set_position((GtkWindow*)myHistory,GTK_WIN_POS_CENTER);

				    GtkWidget* table = gtk_table_new(5, 6, TRUE); //高5宽6
				    gtk_container_add(GTK_CONTAINER(myHistory), table);

				    GtkWidget* labelTitle = gtk_label_new(NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table),labelTitle,0,6,0,1); // 左右1-6，上下0-1
				    char cmd[100] = "";
				    sprintf(cmd,"<span foreground='red' font_desc='40'>历史记录</span>");
				    gtk_label_set_markup(GTK_LABEL(labelTitle),cmd);

				    GtkWidget* buttonMyHistoryToOperate = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonMyHistoryToOperate), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonMyHistoryToOperate,0,1,0,1);
					GtkWidget* labelButtonMyHistoryToOperate = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonMyHistoryToOperate),"<span foreground='black' font_desc='16'>返回</span>");
					gtk_container_add(GTK_CONTAINER(buttonMyHistoryToOperate),labelButtonMyHistoryToOperate);

				    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table), scrolled_window, 0, 6, 1, 5);// 把按钮加入布局

				    // GTK_POLICY_AUTOMATIC：滚动条根据需要自动出现时
				    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

				    //创建一个带titles（分栏列表）的clist控件
				    gchar * listTitle[2] = {"历史记录","flag（0为借书，1为还书）"};
				    GtkWidget* clist = gtk_clist_new_with_titles(2,listTitle);
					gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), clist); // 将clist放入滚动条中

				    gtk_clist_set_column_width(GTK_CLIST(clist),0,500); //设置第0列宽300
				    gtk_clist_set_column_justification(GTK_CLIST(clist),0,GTK_JUSTIFY_CENTER); //给clist 的第0列设置居中
				    gtk_clist_set_column_width(GTK_CLIST(clist),1,500);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),1,GTK_JUSTIFY_CENTER);
				    

				    sqlite3_open("book.db", &db);
					memset(sqlSelect,'\0',sizeof(sqlSelect));
					sprintf(sqlSelect,"SELECT data,flag FROM tb_history WHERE psn_id=\'%s\';",loginId);

					tb = NULL;
					r = 0;
					c = 0;
					errmsg = NULL;
					sqlite3_get_table(db, sqlSelect, &tb, &r, &c, &errmsg); // 执行db: select from tb
					if(errmsg != NULL) {
						printf("select error： %s\n",errmsg); // 输出错误信息errmsg
						sqlite3_close(db);
						return;
					}
					int i = 0, k = 0;
					char* list_text[2];
					for(i = 1; i < r+1; i++) { // r+1行
						for(k = 0; k < c; k++) { // c列
							list_text[k] = tb[i*c+k];
						}
						gtk_clist_append(GTK_CLIST(clist),list_text); // 添加list_text数组到clist中
					    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), clist); // 将clist放入滚动条中
						printf("\n");
					}

				    g_signal_connect(myHistory,"destroy",G_CALLBACK(gtk_main_quit),NULL);
				    g_signal_connect(buttonMyHistoryToOperate,"pressed",G_CALLBACK(myHistory_to_studentOperate),NULL);
				
				}
				void returnBooks_student_init() {
					returnBooks = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 有顶部边栏
					gtk_widget_set_size_request(returnBooks, 1000, 600); // 最小宽1000高600
					gtk_window_set_title(GTK_WINDOW(returnBooks), "图书管理系统---还书界面"); // 标题
				    set_background(returnBooks, 1000, 600, "./studentOperate_background.png"); // 设置背景
				    gtk_window_set_position((GtkWindow*)returnBooks,GTK_WIN_POS_CENTER);

				    GtkWidget* table = gtk_table_new(5, 6, TRUE); //高5宽6
				    gtk_container_add(GTK_CONTAINER(returnBooks), table);

				    GtkWidget* labelTitle = gtk_label_new(NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table),labelTitle,0,6,0,1); // 左右1-6，上下0-1
				    char cmd[100] = "";
				    sprintf(cmd,"<span foreground='red' font_desc='40'>还书系统</span>");
				    gtk_label_set_markup(GTK_LABEL(labelTitle),cmd);

				    GtkWidget* buttonReturnBooksToOperate = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonReturnBooksToOperate), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonReturnBooksToOperate,0,1,0,1);
					GtkWidget* labelButtonReturnBooksToOperate = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonReturnBooksToOperate),"<span foreground='black' font_desc='16'>返回</span>");
					gtk_container_add(GTK_CONTAINER(buttonReturnBooksToOperate),labelButtonReturnBooksToOperate);


					GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table), scrolled_window, 0, 6, 1, 5);// 把按钮加入布局

				    // GTK_POLICY_AUTOMATIC：滚动条根据需要自动出现时
				    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

				    //创建一个带titles（分栏列表）的clist控件
				    gchar * listTitle[4] = {"id","书名","种别","剩余数量"};
				    GtkWidget* clist = gtk_clist_new_with_titles(4,listTitle);
					gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), clist); // 将clist放入滚动条中

				    gtk_clist_set_column_width(GTK_CLIST(clist),0,250); //设置第0列宽300
				    gtk_clist_set_column_justification(GTK_CLIST(clist),0,GTK_JUSTIFY_CENTER); //给clist 的第0列设置居中
				    gtk_clist_set_column_width(GTK_CLIST(clist),1,250);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),1,GTK_JUSTIFY_CENTER);
				    gtk_clist_set_column_width(GTK_CLIST(clist),2,250);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),2,GTK_JUSTIFY_CENTER);
				    gtk_clist_set_column_width(GTK_CLIST(clist),3,250);
				    gtk_clist_set_column_justification(GTK_CLIST(clist),3,GTK_JUSTIFY_CENTER);

				    sqlite3_open("book.db", &db);
					memset(sqlSelect,'\0',sizeof(sqlSelect));
					sprintf(sqlSelect,"SELECT tb_own.book_id,book_name,category,tb_own.number FROM tb_own,tb_book WHERE tb_book.book_id=tb_own.book_id AND psn_id=\'%s\';",loginId);

					tb = NULL;
					r = 0;
					c = 0;
					errmsg = NULL;
					sqlite3_get_table(db, sqlSelect, &tb, &r, &c, &errmsg); // 执行db: select from tb
					if(errmsg != NULL) {
						printf("select error： %s\n",errmsg); // 输出错误信息errmsg
						sqlite3_close(db);
						return;
					}
					int i = 0, k = 0;
					char* list_text[4];
					for(i = 1; i < r+1; i++) { // r+1行
						for(k = 0; k < c; k++) { // c列
							list_text[k] = tb[i*c+k];
						}
						gtk_clist_append(GTK_CLIST(clist),list_text); // 添加list_text数组到clist中
					    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), clist); // 将clist放入滚动条中
					}
				    g_signal_connect(clist, "select-row", G_CALLBACK(clist_return), NULL);



				    g_signal_connect(returnBooks,"destroy",G_CALLBACK(gtk_main_quit),NULL);
				    g_signal_connect(buttonReturnBooksToOperate,"pressed",G_CALLBACK(returnBooks_to_studentOperate),NULL);
				}
				void deleteAccount_student_init() {
					deleteAccount = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 有顶部边栏
					// GdkScreen *screen = gdk_screen_get_default();
					// gint screen_w = gdk_screen_get_width(screen);
					// gint screen_h = gdk_screen_get_height(screen);
					// gtk_window_move(GTK_WINDOW(deleteAccount), (screen_w *0.2), (screen_h *0.3));
					gtk_widget_set_size_request(deleteAccount, 500, 300); // 最小宽500高300
					gtk_window_set_title(GTK_WINDOW(deleteAccount), "图书管理系统---注销界面"); // 标题
				    set_background(deleteAccount, 500, 300, "./studentOperate_background.png"); // 设置背景
				    gtk_window_set_position((GtkWindow*)deleteAccount,GTK_WIN_POS_CENTER);
				    GtkWidget* table = gtk_table_new(4, 4, TRUE); //高4宽4
				    gtk_container_add(GTK_CONTAINER(deleteAccount), table);


				    GtkWidget* labelTitle0 = gtk_label_new(NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table),labelTitle0,0,4,0,1.5); // 左右1-6，上下0-1
				    char cmd0[100] = "";
				    sprintf(cmd0,"<span foreground='red' font_desc='40'>是否确定注销</span>");
				    gtk_label_set_markup(GTK_LABEL(labelTitle0),cmd0);


				    GtkWidget* labelTitle = gtk_label_new(NULL);
				    gtk_table_attach_defaults(GTK_TABLE(table),labelTitle,0,4,1.5,3); // 左右1-6，上下0-1
				    char cmd[100] = "";
				    sprintf(cmd,"<span foreground='red' font_desc='40'>(此操作不可逆转)</span>");
				    gtk_label_set_markup(GTK_LABEL(labelTitle),cmd);


				    GtkWidget* buttonDeleteAccountYes = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonDeleteAccountYes), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonDeleteAccountYes,0,2,3,4);
					GtkWidget* labelButtonDeleteAccountYes = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonDeleteAccountYes),"<span foreground='green' font_desc='16'>是</span>");
					gtk_container_add(GTK_CONTAINER(buttonDeleteAccountYes),labelButtonDeleteAccountYes);

					GtkWidget* buttonDeleteAccountNo = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonDeleteAccountNo), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonDeleteAccountNo,2,4,3,4);
					GtkWidget* labelButtonDeleteAccountNo = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonDeleteAccountNo),"<span foreground='gray' font_desc='16'>否</span>");
					gtk_container_add(GTK_CONTAINER(buttonDeleteAccountNo),labelButtonDeleteAccountNo);

				    g_signal_connect(buttonDeleteAccountYes,"pressed",G_CALLBACK(deleteAccount_to_home),NULL);
				    g_signal_connect(buttonDeleteAccountNo,"pressed",G_CALLBACK(deleteAccount_to_studentOperate),NULL);
				}
				void updatePassword_student_init() {
					updatePassword = gtk_window_new(GTK_WINDOW_TOPLEVEL); // 有顶部边栏
					// GdkScreen *screen = gdk_screen_get_default();
					// gint screen_w = gdk_screen_get_width(screen);
					// gint screen_h = gdk_screen_get_height(screen);
					// gtk_window_move(GTK_WINDOW(updatePassword), (screen_w *0.2), (screen_h *0.3));
					gtk_widget_set_size_request(updatePassword, 500, 150); // 最小宽1000高600
					gtk_window_set_position((GtkWindow*)updatePassword,GTK_WIN_POS_CENTER);

					gtk_window_set_title(GTK_WINDOW(updatePassword), "图书管理系统---更改密码界面"); // 标题

				    GtkWidget* table = gtk_table_new(2, 4, TRUE); //高宽
				    gtk_container_add(GTK_CONTAINER(updatePassword), table);

					GtkWidget* labelPwd = gtk_label_new("");
				    gtk_label_set_markup(GTK_LABEL(labelPwd),"<span foreground='black' font_desc='20'>新密码：</span>");
				    gtk_table_attach_defaults(GTK_TABLE(table),labelPwd,0,1,0,1);
				    entryPwd = gtk_entry_new();
				    gtk_table_attach_defaults(GTK_TABLE(table),entryPwd,1,4,0,1);
					GtkWidget* buttonUpdatePasswordAccountYes = gtk_button_new();
					gtk_button_set_relief(GTK_BUTTON(buttonUpdatePasswordAccountYes), GTK_RELIEF_NONE); // 按钮背景色透明
					gtk_table_attach_defaults(GTK_TABLE(table),buttonUpdatePasswordAccountYes,1,3,1,2);
					GtkWidget* labelButtonUpdatePasswordAccountYes = gtk_label_new("");
					gtk_label_set_markup(GTK_LABEL(labelButtonUpdatePasswordAccountYes),"<span foreground='black' font_desc='16'>更改</span>");
					gtk_container_add(GTK_CONTAINER(buttonUpdatePasswordAccountYes),labelButtonUpdatePasswordAccountYes);

					g_signal_connect(buttonUpdatePasswordAccountYes,"pressed",G_CALLBACK(updatePassword_to_home_student),NULL);
				}

// 功能函数（实现）
void set_background(GtkWidget *widget, int w, int h, const gchar *path) {
	gtk_widget_set_app_paintable(widget, TRUE);  //允许窗口可以绘图
	gtk_widget_realize(widget); 
	
	/* 更改背景图时，图片会重叠
	 * 这时要手动调用下面的函数，让窗口绘图区域失效，产生窗口重绘制事件（即 expose 事件）。
	 */
	gtk_widget_queue_draw(widget);
	
	GdkPixbuf *src_pixbuf = gdk_pixbuf_new_from_file(path, NULL); // 创建图片资源对象
	// w, h是指定图片的宽度和高度
	GdkPixbuf *dst_pixbuf = gdk_pixbuf_scale_simple(src_pixbuf, w, h, GDK_INTERP_BILINEAR);

	GdkPixmap *pixmap = NULL;
	
	/* 创建pixmap图像; 
	 * NULL：不需要蒙版; 
	 * 123： 0~255，透明到不透明
	 */
	gdk_pixbuf_render_pixmap_and_mask(dst_pixbuf, &pixmap, NULL, 128);
	// 通过pixmap给widget设置一张背景图，最后一个参数必须为: FASLE
	gdk_window_set_back_pixmap(widget->window, pixmap, FALSE);
	
	// 释放资源
	g_object_unref(src_pixbuf);
	g_object_unref(dst_pixbuf);
	g_object_unref(pixmap);
}
void load_image(GtkWidget *image, const char *file_path, const int w, const int h) {
    gtk_image_clear( GTK_IMAGE(image) ); // 清除图像
    GdkPixbuf *src_pixbuf = gdk_pixbuf_new_from_file(file_path, NULL);  // 创建图片资源
    GdkPixbuf *dest_pixbuf = gdk_pixbuf_scale_simple(src_pixbuf, w, h, GDK_INTERP_BILINEAR); // 指定大小
    gtk_image_set_from_pixbuf(GTK_IMAGE(image), dest_pixbuf); // 图片控件重新设置一张图片(pixbuf)
    g_object_unref(src_pixbuf); // 释放资源
  	g_object_unref(dest_pixbuf); // 释放资源
}
void refresh_adminRegisterOrLogIn(GtkButton *button, gpointer user_data) {
	gtk_entry_set_text(GTK_ENTRY(entryPersonId),"");
    gtk_entry_set_text(GTK_ENTRY(entryPersonName),"");
    gtk_entry_set_text(GTK_ENTRY(entryPwd),"");
    gtk_entry_set_text(GTK_ENTRY(entryPersonIdentify),"");
    gtk_entry_set_text(GTK_ENTRY(entryToken),"");

    //设置一个新的验证码
    srand(time(NULL)); //设置一个随机的种子，后面生成的就全是随机数
    int i = 0;
    for (i = 0; i < 4; ++i) {
        int a = rand()%3;//因为有三种a-z、0-9、A-Z
        if (a==0) {
            yzm[i] = rand()%26+'a';//在‘a’的ascii码上加上0-25就是a-z
        }
        else if (a==1) {
            yzm[i] = rand()%26+'A';//在‘A’的ascii码上加上0-25就是A-Z
        }
        else {
            yzm[i] = rand()%10+'0';//在‘0’的ascii码上加上0-9就是0-9
        }
    }//通过for循环的形式我们就生成了四位的大小写+0-9混合的验证码
    char cmd[100] = "";
    sprintf(cmd,"<span foreground='%s' font_desc='16'>%s</span>",color[rand()%8],yzm);
    gtk_label_set_markup(GTK_LABEL(labelIdentifyCode),cmd);
} // 刷新admin注册or登录页面
void refresh_studentRegisterOrLogIn(GtkButton *button, gpointer user_data){
	gtk_entry_set_text(GTK_ENTRY(entryPersonId),"");
    gtk_entry_set_text(GTK_ENTRY(entryPersonName),"");
    gtk_entry_set_text(GTK_ENTRY(entryPwd),"");
    gtk_entry_set_text(GTK_ENTRY(entryPersonIdentify),"");

    //设置一个新的验证码
    srand(time(NULL)); //设置一个随机的种子，后面生成的就全是随机数
    int i = 0;
    for (i = 0; i < 4; ++i) {
        int a = rand()%3;//因为有三种a-z、0-9、A-Z
        if (a==0) {
            yzm[i] = rand()%26+'a';//在‘a’的ascii码上加上0-25就是a-z
        }
        else if (a==1) {
            yzm[i] = rand()%26+'A';//在‘A’的ascii码上加上0-25就是A-Z
        }
        else {
            yzm[i] = rand()%10+'0';//在‘0’的ascii码上加上0-9就是0-9
        }
    }//通过for循环的形式我们就生成了四位的大小写+0-9混合的验证码
    char cmd[100] = "";
    sprintf(cmd,"<span foreground='%s' font_desc='16'>%s</span>",color[rand()%8],yzm);
    gtk_label_set_markup(GTK_LABEL(labelIdentifyCode),cmd);
} // 刷新student注册或登录界面
void clist_block(GtkWidget *clist, gint row, gint column,GdkEventButton *event, gpointer data) {
	gchar *text; // 定义一个指针，存储我们的选项内容
  
  	/* 取得存储在被选中的行和列的单元格上的文本
   	* 当鼠标点击时，我们用text参数接收一个指针
   	*/
  	gtk_clist_get_text(GTK_CLIST(clist), row, column, &text);
  	sqlite3_open("book.db",&db);
  	memset(sqlUpdate,'\0',sizeof(sqlUpdate));
  	int s1 = sqlite3_total_changes(db);
  	printf("1-s1:%d", s1);
	sprintf(sqlUpdate,"UPDATE tb_person SET reputation=\'差\' WHERE psn_id=\'%s\' AND reputation=\'良好\';",text);
	errmsg = NULL;
	sqlite3_exec(db,sqlUpdate,NULL,NULL,&errmsg);
	if (errmsg != NULL) {
		printf("update error: %s\n", errmsg); // 输出错误信息errmsg
		sqlite3_close(db);
		return;
	}
	int s2 = sqlite3_total_changes(db);
  	printf("1-s2:%d", s2);
	if(s1!=s2) {
		gtk_clist_set_text(GTK_CLIST(clist),row, column+2,"差");
		sqlite3_close(db);
		// 注意！此处要返回！
		return;
	}

	memset(sqlUpdate,'\0',sizeof(sqlUpdate));
  	s1 = sqlite3_total_changes(db);
  	printf("2-s1:%d", s1);
	sprintf(sqlUpdate,"UPDATE tb_person SET reputation=\'良好\' WHERE psn_id=\'%s\' AND reputation=\'差\';",text);
	errmsg = NULL;
	sqlite3_exec(db,sqlUpdate,NULL,NULL,&errmsg);
	if (errmsg != NULL) {
		printf("update error: %s\n", errmsg); // 输出错误信息errmsg
		sqlite3_close(db);
		return;
	}
	s2 = sqlite3_total_changes(db);
  	printf("2-s2:%d", s2);
	printf("update ok!\n");
  	// 打印一些关于选中了哪一行的信息
  	g_print("第%d行，第%d列的内容为%s\n", row, column, text);
  	if(s1!=s2) {
		gtk_clist_set_text(GTK_CLIST(clist),row, column+2,"良好");
		sqlite3_close(db);
		return;
	}
} // 拉黑
void book_join(GtkButton *button, gpointer user_data) {
	const char* _id = gtk_entry_get_text(GTK_ENTRY(entryBookId));
	const char* _name = gtk_entry_get_text(GTK_ENTRY(entryBookName));
	const char* _category = gtk_entry_get_text(GTK_ENTRY(entryBookCategory));
	const char* _number_s= gtk_entry_get_text(GTK_ENTRY(entryBookNum));
	int _number = atoi(_number_s);

	sqlite3_open("book.db", &db);
	
	if(strcmp(_id,"")==0||strcmp(_name,"")==0||strcmp(_category,"")==0||_number==0) {
		dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"请输入完整！", "title");
	    gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
	    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
	    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
	    gtk_widget_destroy(dialog_tuifang_queding);
	    sqlite3_close(db);
	    return;
	}
 	// 插入该条记录，提示插入成功
   	memset(sqlInsert,'\0',sizeof(sqlInsert));
   	sprintf(sqlInsert,"INSERT INTO tb_book VALUES (\'%s\',\'%s\',\'%s\',%d);", _id, _name, _category, _number);
   	errmsg = NULL;
		sqlite3_exec(db,sqlInsert,NULL,NULL,&errmsg); // 执行sqlInsert: insert into table
 	if (errmsg != NULL) {
  		printf("insert error: %s\n", errmsg); // 输出错误信息errmsg
 	}
	printf("insert ok!\n");
	dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"添加成功！", "title");
    gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
    gtk_widget_destroy(dialog_tuifang_queding);
    // 刷新页面
    gtk_entry_set_text(GTK_ENTRY(entryBookId),"");
    gtk_entry_set_text(GTK_ENTRY(entryBookName),"");
    gtk_entry_set_text(GTK_ENTRY(entryBookCategory),"");
    gtk_entry_set_text(GTK_ENTRY(entryBookNum),"");

	sqlite3_close(db);
} // 进书
void clist_book_out(GtkWidget *clist, gint row, gint column,GdkEventButton *event, gpointer data) { 
	gchar *text; // 定义一个指针，存储我们的选项内容
  
  	/* 取得存储在被选中的行和列的单元格上的文本
   	* 当鼠标点击时，我们用text参数接收一个指针
   	*/
  	gtk_clist_get_text(GTK_CLIST(clist), row, column, &text);
  	sqlite3_open("book.db",&db);


  	memset(sqlSelect,'\0',sizeof(sqlSelect));
	sprintf(sqlSelect,"SELECT * FROM tb_book WHERE book_id=\'%s\';",text);

	tb = NULL;
	r = 0;
	c = 0;
	errmsg = NULL;
	sqlite3_get_table(db, sqlSelect, &tb, &r, &c, &errmsg); // 执行db: select from tb
	if(errmsg != NULL) {
		printf("select error： %s\n",errmsg); // 输出错误信息errmsg
		sqlite3_close(db);
		return;
	}
	char* num_ = tb[1*4+3];
	sqlite3_free_table(tb);
	printf("num_的值：%s", num_);
	int num = atoi(num_);
	printf("num的值：%d", num);
	char num_s[10]={"\0"};
	sprintf(num_s,"%d",num-1);
	if(num > 0) {
	  	memset(sqlUpdate,'\0',sizeof(sqlUpdate));
		sprintf(sqlUpdate,"UPDATE tb_book SET number=number-1 WHERE book_id=\'%s\';",text);
		errmsg = NULL;
		sqlite3_exec(db,sqlUpdate,NULL,NULL,&errmsg);
		if (errmsg != NULL) {
			printf("update error: %s\n", errmsg); // 输出错误信息errmsg
			sqlite3_close(db);
		}else {
			gtk_clist_set_text(GTK_CLIST(clist),row, column+3,num_s);
			sqlite3_close(db);
		}
	}else {
		dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"该书已无存货", "title");
		gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
	    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
	    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
	    gtk_widget_destroy(dialog_tuifang_queding);
	}
} // 出书 
void refresh_bookIn(GtkButton *button, gpointer user_data) {
	gtk_entry_set_text(GTK_ENTRY(entryBookId),"");
    gtk_entry_set_text(GTK_ENTRY(entryBookName),"");
    gtk_entry_set_text(GTK_ENTRY(entryBookCategory),"");
    gtk_entry_set_text(GTK_ENTRY(entryBookNum),"");
} // 刷新进书页面
void clist_borrow(GtkWidget *clist, gint row, gint column,GdkEventButton *event, gpointer data) {
	gchar *text; // 定义一个指针，存储我们的选项内容
  	/* 取得存储在被选中的行和列的单元格上的文本
   	* 当鼠标点击时，我们用text参数接收一个指针
   	*/
  	gtk_clist_get_text(GTK_CLIST(clist), row, column, &text);
  	sqlite3_open("book.db",&db);
  	// 先把book表里面的数据--，再把学生-存书表里面的数据++

  	// 查找book_id=text的数据将其number-1
  	memset(sqlSelect,'\0',sizeof(sqlSelect));
	sprintf(sqlSelect,"SELECT * FROM tb_book WHERE book_id=\'%s\';",text);
	tb = NULL;
	r = 0;
	c = 0;
	errmsg = NULL;
	sqlite3_get_table(db, sqlSelect, &tb, &r, &c, &errmsg); // 执行db: select from tb
	if(errmsg != NULL) {
		printf("select error： %s\n",errmsg); // 输出错误信息errmsg
		sqlite3_close(db);
		return;
	}
	char bookName[10] = {'\0'};
	strcpy(bookName, tb[5]);

	char* num_ = tb[1*4+3]; // 获得book表中number
	int num = atoi(num_); // number 字符串类型->整型
	char num_s[10]={"\0"};
	sprintf(num_s,"%d",num-1); // 计算number-1放到->字符串

	sqlite3_free_table(tb);
	if(num > 0) {
		// 1和2只能借1进的书，1和2都不能借2进的书，1和2同步了
	  	memset(sqlUpdate,'\0',sizeof(sqlUpdate));
		sprintf(sqlUpdate,"UPDATE tb_book SET number=number-1 WHERE book_id=\'%s\';",text);
		errmsg = NULL;
		sqlite3_exec(db,sqlUpdate,NULL,NULL,&errmsg);
		if (errmsg != NULL) {
			printf("update error: %s\n", errmsg); // 输出错误信息errmsg
			sqlite3_close(db);
		}else {
			// 先更新界面中表格的数据
			gtk_clist_set_text(GTK_CLIST(clist),row, column+3,num_s);


			// 查找tb_own表中book_id=text的数据
			memset(sqlSelect,'\0',sizeof(sqlSelect));
			sprintf(sqlSelect,"SELECT * FROM tb_own WHERE book_id=\'%s\' AND psn_id=\'%s\';",text,loginId);
			tb = NULL;
			r = 0;
			c = 0;
			sqlite3_free_table(tb);
			errmsg = NULL;
			sqlite3_get_table(db, sqlSelect, &tb, &r, &c, &errmsg); // 执行db: select from tb
			if(errmsg != NULL) {
				printf("select error： %s\n",errmsg); // 输出错误信息errmsg
				sqlite3_close(db);
				return;
			}

			int i = 0, k = 0;
			for(;i<5;i++)
			for( k=0;k<3;k++) {
				printf("tb[%d]%p ",i*3+k, tb[i*3+k]);
			}
			printf("tb%p\n", tb);
			printf("tb[0]%p\n", tb[0]);
			printf("loginName[%s]",loginName);

			// 查出来东西，tb[0]!=null；查不出来东西，tb[0]==null
			
			for(   ; i < r+1; i++) { // r+1行
				for(k = 0; k < c; k++) { // c列s
					printf("[%s] ",tb[i*c+k]);
				}
				printf("\n");
			}
			sqlite3_free_table(tb);

			// 如果没找到，就插入学生-存书关系表：添加一条记录insert(psn_id,book_id,1)
			
			if(r==0) {
				
				memset(sqlInsert,'\0',sizeof(sqlInsert));
			   	sprintf(sqlInsert,"INSERT INTO tb_own VALUES (\'%s\',\'%s\',%d);", loginId, text, 1);

			   	errmsg = NULL;
					sqlite3_exec(db,sqlInsert,NULL,NULL,&errmsg); // 执行sqlInsert: insert into table
			 	if (errmsg != NULL) {
			  		printf("insert error: %s\n", errmsg); // 输出错误信息errmsg
			 	}
				
			 	memset(sqlInsert,'\0',sizeof(sqlInsert));
			   	sprintf(sqlInsert,"INSERT INTO tb_history(psn_id,data,flag) VALUES (\'%s\',\'%s于\'||datetime('now')||'借书%s一本',%d);", loginId, loginName, bookName, 0);

			   	errmsg = NULL;
					sqlite3_exec(db,sqlInsert,NULL,NULL,&errmsg); // 执行sqlInsert: insert into table
			 	if (errmsg != NULL) {
			  		printf("insert error: %s\n", errmsg); // 输出错误信息errmsg
			  		sqlite3_close(db);
					return;
			 	}else {
					gtk_clist_set_text(GTK_CLIST(clist),row, column+3,num_s);  // 更新界面中表中数据 -1
					sqlite3_close(db);
				}
				
				sqlite3_close(db);
			}else {// 如果找到了，就更新学生-存书关系表：update借的书number++

				memset(sqlUpdate,'\0',sizeof(sqlUpdate));
				sprintf(sqlUpdate,"UPDATE tb_own SET number=number+1 WHERE book_id=\'%s\' AND psn_id=\'%s\';",text,loginId);
				errmsg = NULL;
				sqlite3_exec(db,sqlUpdate,NULL,NULL,&errmsg);
				if (errmsg != NULL) {
					printf("update error: %s\n", errmsg); // 输出错误信息errmsg
					sqlite3_close(db);
					return;
				}

				memset(sqlInsert,'\0',sizeof(sqlInsert));
			   	sprintf(sqlInsert,"INSERT INTO tb_history(psn_id,data,flag) VALUES (\'%s\',\'%s于\'||datetime('now')||'借书%s一本',%d);", loginId, loginName, bookName, 0);

			   	errmsg = NULL;
					sqlite3_exec(db,sqlInsert,NULL,NULL,&errmsg); // 执行sqlInsert: insert into table
			 	if (errmsg != NULL) {
			  		printf("insert error: %s\n", errmsg); // 输出错误信息errmsg
			  		sqlite3_close(db);
					return;
			 	}else {
					gtk_clist_set_text(GTK_CLIST(clist),row, column+3,num_s);  // 更新界面中表中数据 -1
					sqlite3_close(db);
				}

			}
		}
	}else {
		dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"该书已无存货", "title");
		gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
	    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
	    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
	    gtk_widget_destroy(dialog_tuifang_queding);
	}
} // 借书
void clist_return(GtkWidget *clist, gint row, gint column,GdkEventButton *event, gpointer data) {
	gchar *text; // 定义一个指针，存储我们的选项内容
  	/* 取得存储在被选中的行和列的单元格上的文本
   	* 当鼠标点击时，我们用text参数接收一个指针
   	*/
  	gtk_clist_get_text(GTK_CLIST(clist), row, column, &text);
  	sqlite3_open("book.db",&db);
  	// 先把学生-存书表里面的数据--，再把book表里面的数据++

  	// 查找book_id=text的数据将其number-1
  	memset(sqlSelect,'\0',sizeof(sqlSelect));
	sprintf(sqlSelect,"SELECT * FROM tb_own WHERE book_id=\'%s\' AND psn_id=\'%s\';",text,loginId);
	tb = NULL;
	r = 0;
	c = 0;
	errmsg = NULL;
	sqlite3_get_table(db, sqlSelect, &tb, &r, &c, &errmsg); // 执行db: select from tb
	if(errmsg != NULL) {
		printf("select error： %s\n",errmsg); // 输出错误信息errmsg
		sqlite3_close(db);
		return;
	}

	char* num_ = tb[1*3+2]; // 获得tb_own表中number
	int num = atoi(num_); // number 字符串类型->整型
	char num_s[10]={"\0"};
	sprintf(num_s,"%d",num-1); // 计算number-1放到->字符串

	sqlite3_free_table(tb);

	memset(sqlSelect,'\0',sizeof(sqlSelect));
	sprintf(sqlSelect,"SELECT book_name FROM tb_book WHERE book_id=\'%s\';",text);
	tb = NULL;
	r = 0;
	c = 0;
	errmsg = NULL;
	sqlite3_get_table(db, sqlSelect, &tb, &r, &c, &errmsg); // 执行db: select from tb
		if(errmsg != NULL) {
			printf("select error： %s\n",errmsg); // 输出错误信息errmsg
			sqlite3_close(db);
			return;
		}
	char bookName[20] = {'\0'};
	strcpy(bookName,tb[1]);
	if(num > 0) {
	  	memset(sqlUpdate,'\0',sizeof(sqlUpdate));
		sprintf(sqlUpdate,"UPDATE tb_own SET number=number-1 WHERE book_id=\'%s\' AND psn_id=\'%s\';",text,loginId);
		errmsg = NULL;
		sqlite3_exec(db,sqlUpdate,NULL,NULL,&errmsg);
		if (errmsg != NULL) {
			printf("update error: %s\n", errmsg); // 输出错误信息errmsg
			sqlite3_close(db);
		}else {
			// 先更新界面中表格的数据
			gtk_clist_set_text(GTK_CLIST(clist),row, column+3,num_s);


			
			memset(sqlUpdate,'\0',sizeof(sqlUpdate));
			sprintf(sqlUpdate,"UPDATE tb_book SET number=number+1 WHERE book_id=\'%s\';",text);
			errmsg = NULL;
			sqlite3_exec(db,sqlUpdate,NULL,NULL,&errmsg);
			if (errmsg != NULL) {
				printf("update error: %s\n", errmsg); // 输出错误信息errmsg
				sqlite3_close(db);
				return;
			}

			memset(sqlInsert,'\0',sizeof(sqlInsert));
		   	sprintf(sqlInsert,"INSERT INTO tb_history(psn_id,data,flag) VALUES (\'%s\',\'%s于\'||datetime('now')||'还书%s一本',%d);", loginId, loginName, bookName, 1);

		   	errmsg = NULL;
				sqlite3_exec(db,sqlInsert,NULL,NULL,&errmsg); // 执行sqlInsert: insert into table
		 	if (errmsg != NULL) {
		  		printf("insert error: %s\n", errmsg); // 输出错误信息errmsg
		  		sqlite3_close(db);
				return;
		 	}else {
				gtk_clist_set_text(GTK_CLIST(clist),row, column+3,num_s);  // 更新界面中表中数据 -1
				sqlite3_close(db);
			}		
		}
	}else {
		dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"您已无此书", "title");
		gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
	    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
	    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
	    gtk_widget_destroy(dialog_tuifang_queding);
	}
} // 还书


// 跳转函数（实现）
void home_to_admin(GtkButton *button, gpointer user_data) {
	gtk_widget_show_all(admin);
	gtk_widget_hide_all(home);
}
	void admin_to_home(GtkButton *button, gpointer user_data) {
		gtk_widget_show_all(home);
		gtk_widget_hide_all(admin);
	}
	void admin_to_adminRegister(GtkButton *button, gpointer user_data) {
		adminRegister_init();
		gtk_widget_show_all(adminRegister);
		gtk_widget_hide_all(admin);
	}
		void adminRegister_to_admin(GtkButton *button, gpointer user_data) {
			gtk_widget_show_all(admin);
			gtk_widget_hide_all(adminRegister);
		}
		void adminRegister_to_adminLogIn(GtkButton *button, gpointer user_data) {
			const char* _yzm = gtk_entry_get_text(GTK_ENTRY(entryPersonIdentify));
			const char* _id = gtk_entry_get_text(GTK_ENTRY(entryPersonId));
			const char* _name = gtk_entry_get_text(GTK_ENTRY(entryPersonName));
			const char* _pwd = gtk_entry_get_text(GTK_ENTRY(entryPwd));
			const char* _token = gtk_entry_get_text(GTK_ENTRY(entryToken));
			sqlite3_open("book.db", &db);
			memset(sqlSelect,'\0',sizeof(sqlSelect));
			sprintf(sqlSelect,"SELECT * FROM tb_person WHERE psn_id = \'%s\';", _id);
			char **tb = NULL; // 查询结果集表的地址
			int r = 0, c = 0; // 有效数据行数和列数
			errmsg = NULL;
			sqlite3_get_table(db, sqlSelect, &tb, &r, &c, &errmsg); // 执行db: select from tb
			if(errmsg != NULL) {
				printf("select error： %s\n",errmsg); // 输出错误信息errmsg
				sqlite3_close(db);
				return;
			}
			
			if(strcmp(yzm,_yzm)!=0) {// 验证码错误
			    dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"验证码错误", "title");
			    gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
			    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
			    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
			    gtk_widget_destroy(dialog_tuifang_queding);
			    sqlite3_close(db);
			    return;
			}
			else{
				if(strcmp(_token,"98")==0) {
					if(strcmp(_id,"")==0||strcmp(_name,"")==0||strcmp(_pwd,"")==0) {
						dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"请输入完整！", "title");
					    gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
					    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
					    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
					    gtk_widget_destroy(dialog_tuifang_queding);
					    sqlite3_close(db);
					    return;
					}
					if(r!=0) {// 已注册，请勿注册
				    	dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"已注册，请勿注册", "title");
					    gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
					    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
					    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
					    gtk_widget_destroy(dialog_tuifang_queding);
					    sqlite3_close(db);
				    }else { // 插入该条记录，提示注册成功
				    	memset(sqlInsert,'\0',sizeof(sqlInsert));
				    	sprintf(sqlInsert,"INSERT INTO tb_person(psn_id,psn_name,pwd,token) VALUES (\'%s\',\'%s\',\'%s\',\'%s\');", _id, _name, _pwd, _token);
				    	errmsg = NULL;
				 		sqlite3_exec(db,sqlInsert,NULL,NULL,&errmsg); // 执行sqlInsert: insert into table
					 	if (errmsg != NULL) {
					  		printf("insert error: %s\n", errmsg); // 输出错误信息errmsg
					 	}
						printf("insert ok!\n");
						dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"注册成功，点击确定跳转到登录界面", "title");
					    gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
					    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
					    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
					    gtk_widget_destroy(dialog_tuifang_queding);
						
						adminLogIn_init();
						sqlite3_close(db);
					    gtk_widget_show_all(adminLogIn);
						gtk_widget_hide_all(adminRegister);
				    }
				}else {
					dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"令牌错误", "title");
					gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
					gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
					gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
					gtk_widget_destroy(dialog_tuifang_queding);
					sqlite3_close(db);
				}
			}
			
		}
	void admin_to_adminLogIn(GtkButton *button, gpointer user_data) {
		adminLogIn_init();
		gtk_widget_show_all(adminLogIn);
		gtk_widget_hide_all(admin);
	}
		void adminLogIn_to_admin(GtkButton *button, gpointer user_data) {
			gtk_widget_show_all(admin);
			gtk_widget_hide_all(adminLogIn);
		}
		// admin登录 判定 跳转操作页面
		void adminLogIn_to_adminOperate(GtkButton *button, gpointer user_data) {
			const char* _yzm = gtk_entry_get_text(GTK_ENTRY(entryPersonIdentify));
			const char* _id = gtk_entry_get_text(GTK_ENTRY(entryPersonId));
			const char* _name = gtk_entry_get_text(GTK_ENTRY(entryPersonName));
			const char* _pwd = gtk_entry_get_text(GTK_ENTRY(entryPwd));
			const char* _token = gtk_entry_get_text(GTK_ENTRY(entryToken));


			sqlite3_open("book.db", &db);
			memset(sqlSelect,'\0',sizeof(sqlSelect));
			sprintf(sqlSelect,"SELECT psn_name,pwd,reputation FROM tb_person WHERE psn_id = \'%s\';", _id);
			char **tb = NULL; // 查询结果集表的地址
			int r = 0, c = 0; // 有效数据行数和列数
			errmsg = NULL;
			sqlite3_get_table(db, sqlSelect, &tb, &r, &c, &errmsg); // 执行db: select from tb
			if(errmsg != NULL) {
				printf("select error： %s\n",errmsg); // 输出错误信息errmsg
			}
			
			if(strcmp(yzm,_yzm)!=0) {// 验证码错误
			    dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"验证码错误", "title");
			    gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
			    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
			    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
			    gtk_widget_destroy(dialog_tuifang_queding);
			    sqlite3_close(db);
			}
			else{
				if(strcmp(_token,"98")==0) {
					if(strcmp(_id,"")==0||strcmp(_name,"")==0||strcmp(_pwd,"")==0) {
						dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"请输入完整！", "title");
					    gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
					    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
					    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
					    gtk_widget_destroy(dialog_tuifang_queding);
			    		sqlite3_close(db);
					    return;
					}
					if(r==0) { // 未注册要先注册
				    	dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"此工号未注册，请先注册", "title");
					    gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
					    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
					    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
					    gtk_widget_destroy(dialog_tuifang_queding);
			    		sqlite3_close(db);
			    		return;
				    }else { // 已注册 r!=0
				    	
				    	// 判断密码
				    	if(strcmp(tb[3],_name)!=0 || strcmp(tb[4],_pwd)!=0) {
				    		dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"姓名或密码错误！", "title");
						    gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
						    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
						    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
						    gtk_widget_destroy(dialog_tuifang_queding);
			    			sqlite3_close(db);
						    return;
				    	}

				    	if(strcmp(tb[5],"良好")==0) {
							dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"登录成功，点击确定跳转到操作界面", "title");
						    gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
						    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
						    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
						    gtk_widget_destroy(dialog_tuifang_queding);
							strcpy(loginName,_name);
							strcpy(loginId,_id);
							adminOperate_init();

						    gtk_widget_show_all(adminOperate);
							gtk_widget_hide_all(adminLogIn);
							sqlite3_close(db);
							return;
						}else {
							dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"您的信誉太差，已无法登录系统", "title");
						    gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
						    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
						    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
						    gtk_widget_destroy(dialog_tuifang_queding);
						    sqlite3_close(db);
						    return;
						}
				    }
				}else {
					dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"令牌错误", "title");
					gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
					gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
					gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
					gtk_widget_destroy(dialog_tuifang_queding);
					sqlite3_close(db);
					return;
				}
			}
		}
			void adminOperate_to_bookIn(GtkButton *button, gpointer user_data) {
				bookIn_init();
				gtk_widget_show_all(bookIn);
				gtk_widget_hide_all(adminOperate);
			}
				void bookIn_to_adminOperate(GtkButton *button, gpointer user_data) {
					gtk_widget_show_all(adminOperate);
					gtk_widget_hide_all(bookIn);
				}
			void adminOperate_to_bookOut(GtkButton *button, gpointer user_data) {
				bookOut_init();
				gtk_widget_show_all(bookOut);
				gtk_widget_hide_all(adminOperate);
			}
				void bookOut_to_adminOperate(GtkButton *button, gpointer user_data) {
					gtk_widget_show_all(adminOperate);
					gtk_widget_hide_all(bookOut);
				}
			void adminOperate_to_block(GtkButton *button, gpointer user_data) {
				block_init(); // 拉黑

				gtk_widget_show_all(block);
				gtk_widget_hide_all(adminOperate);
			}
				void block_to_adminOperate(GtkButton *button, gpointer user_data) {
					gtk_widget_show_all(adminOperate);
					gtk_widget_hide_all(block);
				}
			void adminOperate_to_blacklist(GtkButton *button, gpointer user_data) {
				blacklist_init(); // 黑名单

				gtk_widget_show_all(blacklist);
				gtk_widget_hide_all(adminOperate);
			}
				void blacklist_to_adminOperate(GtkButton *button, gpointer user_data) {
					gtk_widget_show_all(adminOperate);
					gtk_widget_hide_all(blacklist);
				}
			void adminOperate_to_allHistory(GtkButton *button, gpointer user_data) {
				allHistory_init(); // 所有历史记录

				gtk_widget_show_all(allHistory);
				gtk_widget_hide_all(adminOperate);
			}
				void allHistory_to_adminOperate(GtkButton *button, gpointer user_data) {
					gtk_widget_show_all(adminOperate);
					gtk_widget_hide_all(allHistory);
				}
			void adminOperate_to_borrowHisotry(GtkButton *button, gpointer user_data) {
				borrowHistory_init();

				gtk_widget_show_all(borrowHistory);
				gtk_widget_hide_all(adminOperate);
			}
				void borrowHistory_to_adminOperate(GtkButton *button, gpointer user_data) {
					gtk_widget_show_all(adminOperate);
					gtk_widget_hide_all(borrowHistory);
				}
			void adminOperate_to_returnHisotry(GtkButton *button, gpointer user_data) {
				returnHistory_init();

				gtk_widget_show_all(returnHistory);
				gtk_widget_hide_all(adminOperate);
			}
				void returnHistory_to_adminOperate(GtkButton *button, gpointer user_data) {
					gtk_widget_show_all(adminOperate);
					gtk_widget_hide_all(returnHistory);
				}

			void adminOperate_to_borrowBooks(GtkButton *button, gpointer user_data) {
				borrowBooks_init(); // 借书
				gtk_widget_show_all(borrowBooks);
				gtk_widget_hide_all(adminOperate);
			}
				void borrowBooks_to_adminOperate(GtkButton *button, gpointer user_data) {
					gtk_widget_show_all(adminOperate);
					gtk_widget_hide_all(borrowBooks);
				}
			void adminOperate_to_myHistory(GtkButton *button, gpointer user_data) {
				myHistory_init(); // 个人历史记录

				gtk_widget_show_all(myHistory);
				gtk_widget_hide_all(adminOperate);
			}
				void myHistory_to_adminOperate(GtkButton *button, gpointer user_data) {
					gtk_widget_show_all(adminOperate);
					gtk_widget_hide_all(myHistory);
				}
			void adminOperate_to_returnBooks(GtkButton *button, gpointer user_data) {
				returnBooks_init(); // 还书

				gtk_widget_show_all(returnBooks);
				gtk_widget_hide_all(adminOperate);
			}
				void returnBooks_to_adminOperate(GtkButton *button, gpointer user_data) {
					gtk_widget_show_all(adminOperate);
					gtk_widget_hide_all(returnBooks);
				}
			void adminOperate_to_deleteAccount(GtkButton *button, gpointer user_data) {
				deleteAccount_init(); // 注销

				gtk_widget_show_all(deleteAccount);
			}
				void deleteAccount_to_home(GtkButton *button, gpointer user_data) {
					sqlite3_open("book.db", &db);

					memset(sqlDelete,'\0',sizeof(sqlDelete));
				   	sprintf(sqlDelete,"DELETE FROM tb_person WHERE psn_id=\'%s\';",loginId);
				   	errmsg = NULL;
						sqlite3_exec(db,sqlDelete,NULL,NULL,&errmsg);
				 	if (errmsg != NULL) {
				  		printf("delete error: %s\n", errmsg); // 输出错误信息errmsg
				 	}else{
				 		printf("delete ok!\n");
						dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"注销成功！", "title");
					    gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
					    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
					    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
					    gtk_widget_destroy(dialog_tuifang_queding);

						gtk_widget_show_all(home);
						gtk_widget_hide_all(deleteAccount);
						gtk_widget_hide_all(adminOperate);
				 	}
					sqlite3_close(db);
				}
				void deleteAccount_to_adminOperate(GtkButton *button, gpointer user_data) {
					gtk_widget_hide_all(deleteAccount);
				}
			void adminOperate_to_updatePassword(GtkButton *button, gpointer user_data) {
				updatePassword_init(); // 改密码

				gtk_widget_show_all(updatePassword);
			}
				void updatePassword_to_home(GtkButton *button, gpointer user_data) {
					const char* _pwd = gtk_entry_get_text(GTK_ENTRY(entryPwd));

					sqlite3_open("book.db", &db);

					memset(sqlUpdate,'\0',sizeof(sqlUpdate));
				   	sprintf(sqlUpdate,"UPDATE tb_person SET pwd=\'%s\' WHERE psn_id=\'%s\';",_pwd, loginId);
				   	errmsg = NULL;
						sqlite3_exec(db,sqlUpdate,NULL,NULL,&errmsg); 
				 	if (errmsg != NULL) {
				  		printf("update error: %s\n", errmsg); // 输出错误信息errmsg
				 	}else{
				 		printf("update ok!\n");
						dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"更改成功，请重新登录！", "title");
					    gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
					    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
					    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
					    gtk_widget_destroy(dialog_tuifang_queding);

						gtk_widget_show_all(home);
						gtk_widget_hide_all(updatePassword);
						gtk_widget_hide_all(adminOperate);
				 	}
					sqlite3_close(db);

				}


			void adminOperate_to_adminLogin(GtkButton *button, gpointer user_data) {
				adminLogIn_init();
				gtk_widget_show_all(adminLogIn);
				gtk_widget_hide_all(adminOperate);
			}


void home_to_student(GtkButton *button, gpointer user_data) {
	gtk_widget_show_all(student);
	gtk_widget_hide_all(home);
}
	void student_to_home(GtkButton *button, gpointer user_data) {
		gtk_widget_show_all(home);
		gtk_widget_hide_all(student);
	}
	void student_to_studentRegister(GtkButton *button, gpointer user_data) {
		studentRegister_init();

		gtk_widget_show_all(studentRegister);
		gtk_widget_hide_all(student);
	}
		void studentRegister_to_studentLogIn(GtkButton *button, gpointer user_data) {
			const char* _yzm = gtk_entry_get_text(GTK_ENTRY(entryPersonIdentify));
			const char* _id = gtk_entry_get_text(GTK_ENTRY(entryPersonId));
			const char* _name = gtk_entry_get_text(GTK_ENTRY(entryPersonName));
			const char* _pwd = gtk_entry_get_text(GTK_ENTRY(entryPwd));

			sqlite3_open("book.db", &db);
			memset(sqlSelect,'\0',sizeof(sqlSelect));
			sprintf(sqlSelect,"SELECT * FROM tb_person WHERE psn_id=\'%s\';", _id);
			char **tb = NULL; // 查询结果集表的地址
			int r = 0, c = 0; // 有效数据行数和列数
			errmsg = NULL;
			sqlite3_get_table(db, sqlSelect, &tb, &r, &c, &errmsg); // 执行db: select from tb
			if(errmsg != NULL) {
				printf("select error： %s\n",errmsg); // 输出错误信息errmsg
				sqlite3_close(db);
				return;
			}
			
			if(strcmp(yzm,_yzm)!=0) {// 验证码错误
			    dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"验证码错误", "title");
			    gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
			    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
			    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
			    gtk_widget_destroy(dialog_tuifang_queding);
			    sqlite3_close(db);
			    return;
			}
			else{
				if(strcmp(_id,"")==0||strcmp(_name,"")==0||strcmp(_pwd,"")==0) {
					dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"请输入完整！", "title");
				    gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
				    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
				    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
				    gtk_widget_destroy(dialog_tuifang_queding);
				    sqlite3_close(db);
				    return;
				}
				if(r!=0) {// 已注册，请勿注册
			    	dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"已注册，请勿注册", "title");
				    gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
				    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
				    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
				    gtk_widget_destroy(dialog_tuifang_queding);
				    sqlite3_close(db);
			    }else { // 插入该条记录，提示注册成功
				    	memset(sqlInsert,'\0',sizeof(sqlInsert));
				    	sprintf(sqlInsert,"INSERT INTO tb_person(psn_id,psn_name,pwd) VALUES (\'%s\',\'%s\',\'%s\');", _id, _name, _pwd);
				    	errmsg = NULL;
				 		sqlite3_exec(db,sqlInsert,NULL,NULL,&errmsg); // 执行sqlInsert: insert into table
					 	if (errmsg != NULL) {
					  		printf("insert error: %s\n", errmsg); // 输出错误信息errmsg
					 	}
						printf("insert ok!\n");
						dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"注册成功，点击确定跳转到登录界面", "title");
					    gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
					    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
					    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
					    gtk_widget_destroy(dialog_tuifang_queding);
						
						studentLogIn_init();
						sqlite3_close(db);
					    gtk_widget_show_all(studentLogIn);
						gtk_widget_hide_all(studentRegister);
				    }
				}


			
		}
		void studentRegister_to_student(GtkButton *button, gpointer user_data) {
			gtk_widget_show_all(student);
			gtk_widget_hide_all(studentRegister);
		}
	void student_to_studentLogIn(GtkButton *button, gpointer user_data) {
		studentLogIn_init();

		gtk_widget_show_all(studentLogIn);
		gtk_widget_hide_all(student);
	}
		void studentLogIn_to_student(GtkButton *button, gpointer user_data) {
			gtk_widget_show_all(student);
			gtk_widget_hide_all(studentLogIn);
		}
		void studentLogIn_to_studentOperate(GtkButton *button, gpointer user_data) {
			const char* _yzm = gtk_entry_get_text(GTK_ENTRY(entryPersonIdentify));
			const char* _id = gtk_entry_get_text(GTK_ENTRY(entryPersonId));
			const char* _name = gtk_entry_get_text(GTK_ENTRY(entryPersonName));
			const char* _pwd = gtk_entry_get_text(GTK_ENTRY(entryPwd));


			sqlite3_open("book.db", &db);
			memset(sqlSelect,'\0',sizeof(sqlSelect));
			sprintf(sqlSelect,"SELECT psn_name,pwd,reputation FROM tb_person WHERE psn_id = \'%s\';", _id);
			char **tb = NULL; // 查询结果集表的地址
			int r = 0, c = 0; // 有效数据行数和列数
			errmsg = NULL;
			sqlite3_get_table(db, sqlSelect, &tb, &r, &c, &errmsg); // 执行db: select from tb
			if(errmsg != NULL) {
				printf("select error： %s\n",errmsg); // 输出错误信息errmsg
			}
			
			if(strcmp(yzm,_yzm)!=0) {// 验证码错误
			    dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"验证码错误", "title");
			    gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
			    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
			    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
			    gtk_widget_destroy(dialog_tuifang_queding);
			    sqlite3_close(db);
			}
			else{
				if(strcmp(_id,"")==0||strcmp(_name,"")==0||strcmp(_pwd,"")==0) {
					dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"请输入完整！", "title");
				    gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
				    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
				    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
				    gtk_widget_destroy(dialog_tuifang_queding);
		    		sqlite3_close(db);
				    return;
				}
				if(r==0) { // 未注册要先注册
			    	dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"此学号未注册，请先注册", "title");
				    gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
				    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
				    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
				    gtk_widget_destroy(dialog_tuifang_queding);
		    		sqlite3_close(db);
		    		return;
			    }else { // 已注册 r!=0
			    	// 判断密码
			    	if(strcmp(tb[3],_name)!=0 || strcmp(tb[4],_pwd)!=0) {
			    		dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"姓名或密码错误！", "title");
					    gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
					    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
					    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
					    gtk_widget_destroy(dialog_tuifang_queding);
		    			sqlite3_close(db);
					    return;
			    	}
			    	if(strcmp(tb[5],"良好")==0) {
			    		dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"登录成功，点击确定跳转到操作界面", "title");
					    gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
					    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
					    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
					    gtk_widget_destroy(dialog_tuifang_queding);
						strcpy(loginName,_name);
						strcpy(loginId,_id);
						studentOperate_init();
					    gtk_widget_show_all(studentOperate);
						gtk_widget_hide_all(studentLogIn);
						sqlite3_close(db);
						return;
				    }else {
				    	dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"您的信誉太差，已无法登录系统", "title");
					    gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
					    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
					    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
					    gtk_widget_destroy(dialog_tuifang_queding);
				    }

			    }
			}
			
		}
			void studentOperate_to_borrowBooks(GtkButton *button, gpointer user_data) {
				borrowBooks_student_init(); // 借书
				gtk_widget_show_all(borrowBooks);
				gtk_widget_hide_all(studentOperate);
			}
				void borrowBooks_to_studentOperate(GtkButton *button, gpointer user_data) {
					gtk_widget_show_all(studentOperate);
					gtk_widget_hide_all(borrowBooks);
				}
			void studentOperate_to_myHistory(GtkButton *button, gpointer user_data) {
				myHistory_student_init(); // 个人历史记录

				gtk_widget_show_all(myHistory);
				gtk_widget_hide_all(studentOperate);
			}
				void myHistory_to_studentOperate(GtkButton *button, gpointer user_data) {
					gtk_widget_show_all(studentOperate);
					gtk_widget_hide_all(myHistory);
				}
			void studentOperate_to_returnBooks(GtkButton *button, gpointer user_data) {
				returnBooks_student_init(); // 还书

				gtk_widget_show_all(returnBooks);
				gtk_widget_hide_all(studentOperate);
			}
				void returnBooks_to_studentOperate(GtkButton *button, gpointer user_data) {
					gtk_widget_show_all(studentOperate);
					gtk_widget_hide_all(returnBooks);
				}
			void studentOperate_to_deleteAccount(GtkButton *button, gpointer user_data) {
				deleteAccount_student_init(); // 注销

				gtk_widget_show_all(deleteAccount);
			}
				void deleteAccount_to_home_student(GtkButton *button, gpointer user_data) {
					sqlite3_open("book.db", &db);

					memset(sqlDelete,'\0',sizeof(sqlDelete));
				   	sprintf(sqlDelete,"DELETE FROM tb_person WHERE psn_id=\'%s\';",loginId);
				   	errmsg = NULL;
						sqlite3_exec(db,sqlDelete,NULL,NULL,&errmsg);
				 	if (errmsg != NULL) {
				  		printf("delete error: %s\n", errmsg); // 输出错误信息errmsg
				 	}else{
				 		printf("delete ok!\n");
						dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"注销成功！", "title");
					    gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
					    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
					    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
					    gtk_widget_destroy(dialog_tuifang_queding);

						gtk_widget_show_all(home);
						gtk_widget_hide_all(deleteAccount);
						gtk_widget_hide_all(studentOperate);
				 	}
					sqlite3_close(db);
				}
				void deleteAccount_to_studentOperate(GtkButton *button, gpointer user_data) {
					gtk_widget_hide_all(deleteAccount);
				}
			void studentOperate_to_updatePassword(GtkButton *button, gpointer user_data) {
				updatePassword_init(); // 改密码

				gtk_widget_show_all(updatePassword);
			}
				void updatePassword_to_home_student(GtkButton *button, gpointer user_data) {
					const char* _pwd = gtk_entry_get_text(GTK_ENTRY(entryPwd));

					sqlite3_open("book.db", &db);

					memset(sqlUpdate,'\0',sizeof(sqlUpdate));
				   	sprintf(sqlUpdate,"UPDATE tb_person SET pwd=\'%s\' WHERE psn_id=\'%s\';",_pwd, loginId);
				   	errmsg = NULL;
						sqlite3_exec(db,sqlUpdate,NULL,NULL,&errmsg); 
				 	if (errmsg != NULL) {
				  		printf("update error: %s\n", errmsg); // 输出错误信息errmsg
				 	}else{
				 		printf("update ok!\n");
						dialog_tuifang_queding = gtk_message_dialog_new( (gpointer)home,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,"更改成功，请重新登录！", "title");
					    gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
					    gtk_widget_set_size_request(dialog_tuifang_queding,450,100);
					    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
					    gtk_widget_destroy(dialog_tuifang_queding);

						gtk_widget_show_all(home);
						gtk_widget_hide_all(updatePassword);
						gtk_widget_hide_all(studentOperate);
				 	}
					sqlite3_close(db);
				}
			void studentOperate_to_studentLogin(GtkButton *button, gpointer user_data) {
				studentLogIn_init();
				gtk_widget_show_all(studentLogIn);
				gtk_widget_hide_all(studentOperate);
			}
