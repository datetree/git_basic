// 参考linux man page： 
//		http://man7.org/linux/man-pages/man3/mktime.3.html
//		http://man7.org/linux/man-pages/man3/tzset.3.html


// 涉及到的结构体
/*
 struct timeval 
 {
     time_t      tv_sec;     // seconds 
     suseconds_t tv_usec;    // microseconds 
 };
 
 struct tm 
 {
   int tm_sec;         // seconds 
   int tm_min;         // minutes 
   int tm_hour;        // hours 
   int tm_mday;        // day of the month 
   int tm_mon;         // month 	8（9-1）代表9月
   int tm_year;        // year 		113(2013-1900)代表2013年
   int tm_wday;        // day of the week 
   int tm_yday;        // day in the year 
   int tm_isdst;       // daylight saving time 
 };
*/


// 获取时间
// time_t time(time_t *t);																					从the Epoch到当前经历的时间，以秒为单位
// int gettimeofday(struct timeval *tv, struct timezone *tz);				从the Epoch到当前经历的时间，精确到微秒

// 转换时间
// char *ctime(const time_t *timep);																time_t    ---> ascii码字符串
// char *asctime(const struct tm *tm);															struct tm ---> ascii码字符串

// struct tm *gmtime(const time_t *timep);													time_t    ---> struct tm （转换后以UTC时间输出）
// time_t mktime(struct tm *tm);																		struct tm ---> time_t (北京时间需转换成UTC时间后再转换)
// struct tm *localtime(const time_t *timep);												time_t    ---> struct tm  (转换后以local time 输出，跟据系统配置的时区)

// 时区相关
/*
	tzset可以设置系统时区，该函数一般由时区相关的c库函数调用，如localtime();
	tzset根据环境变量TZ或相关配置文件设置时区信息，若从TZ环境变量能获得有效的数据，则根据TZ环境变量设置时区，否则根据配置文件设置时区
			1)TZ环境变量
					a) std offset  // 不使用DST的时区
					b) std offset dst [offset],start[/time],end[/time]  // 例子： TZ="NZST-12:00:00NZDT-13:00:00,M10.1.0,M3.3.0"
					c) :[filespec] // 使用指定配置文件，例子：TZ=":Pacific/Auckland"
			2)配置文件 (以tzfile格式描述时区信息)
					一般使用符号链接"/etc/localtime"来指向实际的配置文件；
					根据glibc的版本，实际的时区配置文件可能位于下面其中一个目录
							a) /usr/lib/zoneinfo
							b) /usr/share/zoneinfo
							c) TZDIR环境变量指定
*/

/*
	calendar time : When interpreted as an absolute time value, it represents the number of seconds elapsed since the Epoch, 1970-01-01 00:00:00 +0000 (UTC).
*/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	time_t now;
	struct tm *p_now_tm, now_tm;
		
	now = time(NULL);
	printf("%s", ctime(&now));
	
	p_now_tm = gmtime(&now);
	printf("%d, %d, %d, %d, %d, %d,      %d, %d, %d\n", 
						p_now_tm->tm_year+1900, p_now_tm->tm_mon+1, p_now_tm->tm_mday,
						p_now_tm->tm_hour, p_now_tm->tm_min, p_now_tm->tm_sec,
						p_now_tm->tm_wday, p_now_tm->tm_yday, p_now_tm->tm_isdst);
	printf("%u\n", (unsigned int)mktime(p_now_tm));
	
	p_now_tm = localtime(&now);
	printf("%d, %d, %d, %d, %d, %d,      %d, %d, %d\n", 
						p_now_tm->tm_year+1900, p_now_tm->tm_mon+1, p_now_tm->tm_mday,
						p_now_tm->tm_hour, p_now_tm->tm_min, p_now_tm->tm_sec,
						p_now_tm->tm_wday, p_now_tm->tm_yday, p_now_tm->tm_isdst);
	printf("%u\n", (unsigned int)mktime(p_now_tm));
	
	return 0;
}
