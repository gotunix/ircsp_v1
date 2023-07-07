/* ---------------------------------------------------------------------------
 * Copyright (c) GOTUNIX Networks
 * Copyright (c) GOTUNIXCODE
 * Copyright (c) Justin Ovens
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ---------------------------------------------------------------------------
 */


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

