#ifndef EASYPROCESS_H_INCLUDED
#define EASYPROCESS_H_INCLUDED

#include <easytype.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

#define PRO_ERROR -1
#define PRO_CHILD 0


typedef pid_t PID;
typedef enum {P_RUN, P_EXITED, P_ONSIGNAL, P_STOP, P_CONTINUE} PROSTATE;
typedef struct sigaction SIG;

typedef struct _PIPE
{
	INT32 inp;
	INT32 out;
	FILE* f;
}PIPE;

#define IPS_SLEEP    'S'
#define IPS_RUN      'R'
#define IPS_NOTBLOCK 'D'
#define IPS_ZOMBIE   'Z'
#define IPS_STOP     'T'
#define IPS_PAGING   'W'
#define IPS_KILLED   'X'

typedef struct _PIIO
{
	UINT32 allrd;
	UINT32 allwr;
	UINT32 syscallrd;
	UINT32 syscallwr;
	UINT32 hdrd;
	UINT32 hdwr;
}PIIO;

typedef struct _PISTAT
{
	PID pid;
	CHAR name[512];
	CHAR state;
	PID parent;
	INT32 pgrp;
	INT32 session;
	INT32 ttynr;
	INT32 tpgid;
	UINT32 flags;
	UINT32 minfaults;
	UINT32 wminfaults;
	UINT32 majfaults;
	UINT32 wmajfaults;
	UINT32 utime;
	UINT32 stime;
	UINT32 wutime;
	UINT32 wstime;
	INT32 rawprio;
	INT32 prio;
	INT32 nthreads;
	INT32 itrealvalue;
	unsigned long long int sttime;
	UINT32 vmemsize;
	INT32 rss;
	UINT32 rsslim;
	UINT32 stcode;
	UINT32 encode;
	UINT32 ststack;
	UINT32 esp;
	UINT32 eip;
	UINT32 signal;
	UINT32 blocked;
	UINT32 sigignore;
	UINT32 sigcatch;
	UINT32 wchan;
	UINT32 pagswap;
	UINT32 cumpagswap;
	INT32 exitsignal;
	INT32 processor;
	UINT32 rtprio;
	UINT32 policy;
	unsigned long long int delayio;
	UINT32 guesttime;
	INT32 cguesttime; 
}PISTAT;

typedef struct _PIMEM
{
	UINT32 size;
	UINT32 resident;
	UINT32 share;
	UINT32 text;
	UINT32 lib;
	UINT32 data;
	UINT32 dt;
}PIMEM;

typedef struct _PICORE
{
	INT32 n;
	CHAR model[128];
	FLOAT64 mips;
	CHAR features[128];
	INT32 implementer;
	INT32 architecture;
	INT32 variant;
	INT32 part;
	INT32 revision;
}PICORE;

typedef struct _PICPU
{
	UINT32 ncore;
	PICORE core[128];
	CHAR hardware[128];
	CHAR revision[64];
	CHAR serial[64];
}PICPU;
	

typedef VOID(*SIGCALL)(INT32);

BOOL pro_info_io(PIIO* pi, PID pid);
BOOL pro_info_stat(PISTAT* pi, PID pid);
BOOL pro_info_mem(PIMEM* pi, PID pid);
PID pro_pid_lst(BOOL reset);
BOOL pro_info_cpu(PICPU* pi);

#define sig_wait() pause()
BOOL sig_set(SIG* old, INT32 sig, SIGCALL fnc, BOOL restart, BOOL restore);

#define pro_fork() fork()
#define pro_mypid() getpid()
#define pro_parent_pid() getppid()

INT32 pro_pipe(PIPE* p);
VOID pro_initpiperead(PIPE* p, INT32 fi);
VOID pro_initpipewrite(PIPE* p, INT32 fo, INT32 efo);
PID pro_sh(CHAR* cmd, PIPE* pi, PIPE* po);
PROSTATE pro_pidstate(INT32* ex, PID p, BOOL async);
FLOAT64 pro_cpu_usage(INT32 idcpu, FLOAT64 tscan);

#endif // EASYSTRING_H_INCLUDED
