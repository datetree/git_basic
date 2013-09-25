// �ο�linux man page�� 
//		http://man7.org/linux/man-pages/man3/mktime.3.html
//		http://man7.org/linux/man-pages/man3/tzset.3.html


// �漰���Ľṹ��
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
   int tm_mon;         // month 	8��9-1������9��
   int tm_year;        // year 		113(2013-1900)����2013��
   int tm_wday;        // day of the week 
   int tm_yday;        // day in the year 
   int tm_isdst;       // daylight saving time 
 };
*/


// ��ȡʱ��
// time_t time(time_t *t);																					��the Epoch����ǰ������ʱ�䣬����Ϊ��λ
// int gettimeofday(struct timeval *tv, struct timezone *tz);				��the Epoch����ǰ������ʱ�䣬��ȷ��΢��

// ת��ʱ��
// char *ctime(const time_t *timep);																time_t    ---> ascii���ַ���
// char *asctime(const struct tm *tm);															struct tm ---> ascii���ַ���

// struct tm *gmtime(const time_t *timep);													time_t    ---> struct tm ��ת������UTCʱ�������
// time_t mktime(struct tm *tm);																		struct tm ---> time_t (����ʱ����ת����UTCʱ�����ת��)
// struct tm *localtime(const time_t *timep);												time_t    ---> struct tm  (ת������local time ���������ϵͳ���õ�ʱ��)

// ʱ�����
/*
	tzset��������ϵͳʱ�����ú���һ����ʱ����ص�c�⺯�����ã���localtime();
	tzset���ݻ�������TZ����������ļ�����ʱ����Ϣ������TZ���������ܻ����Ч�����ݣ������TZ������������ʱ����������������ļ�����ʱ��
			1)TZ��������
					a) std offset  // ��ʹ��DST��ʱ��
					b) std offset dst [offset],start[/time],end[/time]  // ���ӣ� TZ="NZST-12:00:00NZDT-13:00:00,M10.1.0,M3.3.0"
					c) :[filespec] // ʹ��ָ�������ļ������ӣ�TZ=":Pacific/Auckland"
			2)�����ļ� (��tzfile��ʽ����ʱ����Ϣ)
					һ��ʹ�÷�������"/etc/localtime"��ָ��ʵ�ʵ������ļ���
					����glibc�İ汾��ʵ�ʵ�ʱ�������ļ�����λ����������һ��Ŀ¼
							a) /usr/lib/zoneinfo
							b) /usr/share/zoneinfo
							c) TZDIR��������ָ��
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
