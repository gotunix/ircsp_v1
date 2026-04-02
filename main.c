///////////////////////////////////////////////////////////////////////////////
//		  IRCSP - Internet Realy Chat Services Package
//                  Copyright (C) 2000 Lostworld Development
//          Written By: Justin Ovens [evilicey] [ice95@lostworld.net]
//
//   This program, documentation, and everything included in this
//   package are Copyright (C) 2000 Lostworld Development. You may
//   not use this program in any way sharp or form with out 
//   the Lostworld Developers expresss written consent.
//
//   This program is not gnu puclic license and is not freeware.
//   Possession with out permission, license, is strictly
//   prohibited.  You may purchace this program (Biniary), and
//   a license from our web page [www.lostworld.net].
//
//   The authors of this program are in no way liable for any
//   consequences or damages, suffered by you or anyone else,
//   arising out of the use or inablility to use this program.
//
//   Author Contact information: ice95@lostworld.net
///////////////////////////////////////////////////////////////////////////////



#include "services.h"

///////////////////////////////////////////////////////////////////////////////
//

int
main (argc, argv)
int   argc;
char  *argv[];
{
	int	start;
	char	buf[1024];

	printf(
		"IRCSP Version: %s\n", 
		VERSION);
	printf(
		"Copyright (C) 2000 Lostworld Development.\n");
	printf(
		"IRCSP was written by: Justin Ovens (ice95)\n");
	printf(
		"Compilied on: %s [%s]\n", 
		__DATE__, __TIME__);
	printf(
		"$Source code last update Date$: %s\n", 
		DATE);

	StartTime  = time(NULL);
	LastCycle  = time(NULL);
	LastGCheck = time(NULL);
	CheckNick  = time(NULL);
	ChanCycle  = time(NULL);

	start = Signal_Handler();

	while (--argc > 0 && (*++argv)[0] == '-')
	{
		char	*p;
		int	flag;

		p = argv[0] + 1;
		flag = *p++;

		if (flag == '\0' || *p == '\0')
		{
			if (argc > 1 && argv[1][0] != '-')
			{
				p = *++argv;
				argc -= 1;
			}
			else
			{
				p = "";
			}
			switch (flag)
			{
				case 'c':
				case 'C':
					boot_copyright();
					break;
				case 'h':
				case 'H':
					boot_help();
					break;
				default:
					printf("Unknown option. try -h for help\n");
					exit(1);
			}
		}
	}

	start = load_config ();
	if (start == -1)
	{
		printf("load_config() -- ERROR: missing config file\n");
		exit(1);
	}
	if (start ==  0)
	{
		printf("load_config() -- ERROR: missing feileds in config file\n");
		exit(1);
	}
	if (start ==  1)
	{
		printf("load_config() -- successful!\n");
	}

	start = load_admin();
	if (start == -1)
	{
		printf("load_admin() -- ERROR: missing admin.db file\n");
		exit(1);
	}
	if (start == 1)
	{
		printf("load_admin() -- successful!\n");
	}

	printf("Moving Services into background!\n");
	printf("Services PID: %d\n", getpid()+1);

	/*
	if (fork())
	{
		exit(1);
	} 
	*/

	start = conn();
	start = load_gline();
	start = load_suspchan();
	start = load_nick();
	start = load_channel();
	start = load_cadmin();
	start = load_bans();

	while (s)
	{
		if (sockread(s, buf))
		{
			parse(buf);
		}

		if ((time(NULL) - LastCycle) > config->savecycle)
		{
			LastCycle=time(NULL);

			save_admin();
			save_cadmin();
			save_gline();
			save_nsdb();
			save_channel();	
			save_bans();

			send_to_sock(s, 
				":%s PRIVMSG %s :SaveCycle -- Next Cycle:  %d\n",
				config->unick, config->statchan, 
				config->savecycle);
		}
		if ((time(NULL) - LastGCheck) > config->glinecycle)
		{
			LastGCheck = time(NULL);

			send_to_sock(s, 
				":%s PRIVMSG %s :GlineCycle -- Next Cycle: %d\n",
				config->unick, config->statchan, 
				config->glinecycle);

			checkgline();
		}
		if ((time(NULL) - CheckNick) > config->nickcycle)
		{
			CheckNick = time(NULL);

			send_to_sock(s, 
				":%s PRIVMSG %s :NickCycle -- Next Cycle: %d\n",
				config->unick, config->statchan, 
				config->nickcycle);

			checknick();
		}
		if ((time(NULL) - ChanCycle) > config->chancycle)
		{
			ChanCycle = time(NULL);

			send_to_sock(s, 
				":%s PRIVMSG %s :ChanCycle -- Next Cycle: %d\n",
				config->unick, config->statchan, 
				config->chancycle);

			checkchan();
		}
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//

