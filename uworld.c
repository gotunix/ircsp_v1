///////////////////////////////////////////////////////////////////////////////
//		  IRCSP - Internet Realy Chat Services Package
//                  Copyright (C) 2000 Lostworld Development
//          Written By: Justin Ovens [evilicey] [ice95@lostworld.net]
//
//   This program, documentation, and everything included in this
//   package are Copyright (C) 2000 Lostworld Development. You may
//   Download this package from the lostworld site, or via CVS
//   from source forge.
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 1, or (at your option)
//   any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software
//   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
//   The authors of this program are in no way liable for any
//   consequences or damages, suffered by you or anyone else,
//   arising out of the use or inablility to use this program.
//
//   Author Contact information: ice95@lostworld.net
///////////////////////////////////////////////////////////////////////////////


#include "services.h"
#include <string.h>

int	do_uworld		(char *, char *, char *);
int	do_help			(char *);
int	do_auth			(char *);
int	do_gline		(char *);
int	do_mode			(char *);
int	do_op			(char *);
int	do_deop			(char *);
int	do_kick			(char *);
int	do_kill			(char *);
int	do_masskill		(char *);
int	do_clearmode		(char *);
int	do_uptime		(char *);
int	num_nuk			(char *);
int	do_join			(char *);
int	do_part			(char *);
int	do_verify		(char *);
int	do_operlist		(char *);
int	do_opermsg		(char *);
int	do_map			(char *);
int	do_invite		(char *);
int	do_whois		(char *);
int	do_access		(char *);
int	do_mkpasswd		(char *);
int	do_count		(char *);
int	do_njupe		(char *);
int	do_remnjupe		(char *);
int	do_jupe			(char *);
int	do_remjupe		(char *);
int	do_rehash		(char *);
int	do_collide		(char *);
int	do_save			(char *);
int	do_suspend		(char *);
int	do_remsuspend		(char *);
int	do_adduser		(char *);
int	do_moduser		(char *);
int	do_remuser		(char *);
int	do_say			(char *);
int	do_action		(char *);
int	do_raw			(char *);

//////////////////////////////////////////////////////////////////////////////
//

int
do_uworld (snick,mynick,buf)
char	*snick;
char	*mynick;
char	*buf;
{
	Nick	*n;
	char	*ptr[9];

	n = findNick(snick);

	if (!n)
	{
		send_to_sock(s, 
			"NOTICE %s :%s\n",
			snick, "do_uworld() -- malloc() memory leaks. scream!!!");

		send_to_sock(s,
			"WALLOPS :%s [%s] -- Memory Leak!!\n", 
			snick, buf);

		return 0;
	}

	if (IsOper(n))
	{
		ptr[0] = strtok(buf, " ");
		ptr[0]++;

		if (!strcasecmp(token(buf,1), ":GLINE"))
		{
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");
			if (ptr[1] == NULL)
			{
				send_to_sock(s, 
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: GLINE [user@host] [expire] [reason]");

				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_gline(buff);

			return 0;
		}
		if (!strcasecmp(token(buf,1), ":MODE"))
		{
			char  *buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");
			if (ptr[1] == NULL)
			{
				send_to_sock(s, 
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: MODE [#channel] [mode]");

				return 0;
			}
			sprintf(buff, "%s PTIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_mode(buff);

			return 0;
		}
		if (!strcasecmp(token(buf,1), ":OP"))
		{
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");
			if (ptr[1] == NULL)
			{
				 send_to_sock(s, 
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: OP [#channel] [nickname]");

				return 0;
			}
			sprintf(buff, "%s PTIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_op(buff);

			return 0;
		}
		if (!strcasecmp(token(buf,1), ":DEOP"))
		{
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");
			if (ptr[1] == NULL)
			{
				send_to_sock(s, 
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: DEOP [#channel] [nickname]");

				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_deop(buff);

			return 0;
		}
		if (!strcasecmp(token(buf,1), ":KICK"))
		{
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");
			if (ptr[1] == NULL)
			{
				send_to_sock(s, 
					":%s NOTICE %s :%s\n",
					mynick, snick,
				"Syntax: KICK [#channel] [nickname] [reason]");

				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_kick(buff);

			return 0;
		}
		if (!strcasecmp(token(buf,1), ":INV"))
		{
			send_to_sock(s, 
				"INVITE %s %s\n",
				nick, config->statchan);

			send_to_sock(s, 
				"INVITE %s %s\n",
				nick, config->clonechan);

			return 0;
		}
		if (!strcasecmp(token(buf,1), ":KILL"))
		{
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");
			if (ptr[1] == NULL)
			{
				send_to_sock(s, 
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: KILL [nickname] [reason]");

				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_kill(buff);

			return 0;
		}
		if (!strcasecmp(token(buf,1), ":MASSKILL"))
		{
			char	*buff;
                        
			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			if (ptr[1] == NULL)
			{
				send_to_sock(s,
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: MASSKILL [user@host] [reason]");
                                
				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_masskill(buff);
                                        
			return 0;
		}
		if (!strcasecmp(token(buf,1), ":AUTH"))
		{
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");
			if (ptr[1] == NULL)
			{ 
				send_to_sock(s, 
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: AUTH [nick] [password]");

				return 0; 
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_auth(buff);

			return 0;
		}
		if (!strcasecmp(token(buf,1), ":NUMNUK"))
		{
			Admin	*a;
			char	*buff;

			buff = (char *)calloc(1, 1024);
			a = findAdmin(snick);
			ptr[1] = strtok(NULL, "");

			if (ptr[1] == NULL)
			{
				return 0;
			}

			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			if (a)
			{
				if (IsAdmin(a))
				{
					num_nuk(buff);
				}
				else
				{
					return 0;
				}
			}
			else
			{
				return 0;
			}

			return 0;
		}
		if (!strcasecmp(token(buf,1), ":UPTIME"))
		{
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_uptime(buff);

			return 0;
		}
		if (!strcasecmp(token(buf,1), ":JOIN"))
		{
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			if (ptr[1] == NULL)
			{
				send_to_sock(s, 
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: JOIN [servicebot] [#channel]");

				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_join(buff);

			return 0;
		}
		if (!strcasecmp(token(buf,1), ":PART"))
		{ 
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			if (ptr[1] == NULL)
			{
				send_to_sock(s, 
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: PART [servicebot] [#channel]");

				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_part(buff);

			return 0;
		}
		if (!strcasecmp(token(buf,1), ":CLEARMODE"))
		{
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			if (ptr[1] == NULL)
			{
				send_to_sock(s, 
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: CLEARMODE [#channel]");

				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_clearmode(buff);

			return 0;
		}
		if ((!strcasecmp(token(buf,1), ":HELP")) ||
			(!strcasecmp(token(buf,1), ":SHOWCOMMANDS")))
		{
			Admin	*a;
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			send_to_sock(s,
				":%s NOTICE %s :\2IRCSP %s.\2\n", 
				mynick, snick, VERSION);

			send_to_sock(s,
				":%s NOTICE %s :\2COPYRIGHT (C) 2000 Lostworld Development.\2\n",
				mynick, snick);

			send_to_sock(s,
				":%s NOTICE %s :\2Written By: Justin Ovens [evilicey].\2\n",
				mynick, snick);

			send_to_sock(s, ":%s NOTICE %s : \n",
				mynick, snick);

			send_to_sock(s, ":%s NOTICE %s : \n",
				mynick, snick);

			a = findAdmin(snick);
			if (!a)
			{
				send_to_sock(s, 
					":%s NOTICE %s :\2Uworld %s				Level %d\2\n",
					mynick, snick, VERSION, OPER_LEVEL);
			}
			else
			{
				if (IsAdmin(a))
				{
					send_to_sock(s,
						":%s NOTICE %s :\2Uworld %s				Level %d\2\n",
						mynick, snick, 
						VERSION, a->level);
				}
				else
				{
					send_to_sock(s,
						":%s NOTICE %s :\2Uworld %s				Level %d\2\n",
						mynick, snick, VERSION, 
						OPER_LEVEL);
				}
			} 
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]); 
			do_help(buff); 

			return 0;
		}
		if (!strcasecmp(token(buf,1), ":VERIFY")) 
		{ 
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			if (ptr[1] == NULL)
			{
				send_to_sock(s, 
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: VERIFY [nickname]");

				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_verify(buff);

			return 0; 
		}
		if (!strcasecmp(token(buf,1), ":OPERLIST")) 
		{
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_operlist(buff);

			return 0; 
		}
		if (!strcasecmp(token(buf,1), ":OPERMSG")) 
		{
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			if (ptr[1] == NULL)
			{
				send_to_sock(s, 
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: OPERMSG [newmessage]");

				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_opermsg(buff);                

			return 0; 
		}
		if (!strcasecmp(token(buf,1), ":MAP")) 
		{
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_map(buff);

			return 0; 
		}
		if (!strcasecmp(token(buf,1), ":INVITE")) 
		{ 
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			if (ptr[1] == NULL)
			{
				send_to_sock(s, 
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: INVITE [nickname] [#channel]");

				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_invite(buff);

			return 0;
		}
		if (!strcasecmp(token(buf,1), ":WHOIS")) 
		{ 
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			if (ptr[1] == NULL)
			{
				send_to_sock(s, 
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: WHOIS [nickname]");

				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_whois(buff);

			return 0; 
		}
		if (!strcasecmp(token(buf,1), ":ACCESS")) 
		{ 
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			if (ptr[1] == NULL)
			{
				send_to_sock(s, 
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: ACCESS [service] [nickname]");

				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_access(buff);

			return 0; 
		}
		if (!strcasecmp(token(buf,1), ":MKPASSWD")) 
		{
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			if (ptr[1] == NULL)
			{
				send_to_sock(s, 
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: MKPASSWD [password]");

				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]); 
			do_mkpasswd(buff);

			return 0; 
		}
		if (!strcasecmp(token(buf,1), ":COUNT")) 
		{ 
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_count(buff);

			return 0; 
		}
		if (!strcasecmp(token(buf,1), ":NJUPE")) 
		{ 
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			if (ptr[1] == NULL)
			{
				send_to_sock(s,
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: NJUPE [nickname] [reason]");

				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_njupe(buff);

			return 0; 
		}
		if (!strcasecmp(token(buf,1), ":REMNJUPE")) 
		{ 
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			if (ptr[1] == NULL)
			{
				send_to_sock(s,
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: REMNJUPE [nickname]");

				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_remnjupe(buff);

			return 0;
		}
		if (!strcasecmp(token(buf,1), ":JUPE")) 
		{ 
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			if (ptr[1] == NULL)
			{
				send_to_sock(s,
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: JUPE [servername] [reason]");

				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_jupe(buff);

			return 0; 
		}
		if (!strcasecmp(token(buf,1), ":REMJUPE")) 
		{ 
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			if (ptr[1] == NULL)
			{
				send_to_sock(s,
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: REMJUPE [servername]");

				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_remjupe(buff);

			return 0;
		}
		if (!strcasecmp(token(buf,1), ":REHASH")) 
		{  
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			if (ptr[1] == NULL)
			{
				send_to_sock(s,
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: REHASH [database]");

				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_rehash(buff);

			return 0; 
		}
		if (!strcasecmp(token(buf,1), ":COLLIDE")) 
		{
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			if (ptr[1] == NULL)
			{
				send_to_sock(s, 
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: COLLIDE [nickname]");

				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_collide(buff);

			return 0; 
		}
		if (!strcasecmp(token(buf,1), ":SAVE")) 
		{ 
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_save(buff);

			return 0; 
		}
		if (!strcasecmp(token(buf,1), ":SUSPEND")) 
		{ 
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			if (ptr[1] == NULL)
			{
				send_to_sock(s,
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: SUSPEND [nickname] [service] [reason]");

				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_suspend(buff);

			return 0; 
		}
		if (!strcasecmp(token(buf,1), ":REMSUSPEND")) 
		{ 
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			if (ptr[1] == NULL)
			{
				send_to_sock(s,
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: REMSUSPEND [nickname] [service]");

				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_remsuspend(buff);

			return 0; 
		} 
		if (!strcasecmp(token(buf,1), ":ADDUSER")) 
		{ 
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			if (ptr[1] == NULL)
			{
				send_to_sock(s,
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: ADDUSER [nickname] [userhost] [level] [password]");

				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_adduser(buff);

			return 0; 
		}
		if (!strcasecmp(token(buf,1), ":MODUSER")) 
		{ 
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			if (ptr[1] == NULL)
			{
				send_to_sock(s,
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: MODUSER [nickname] [what] [new]");

				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_moduser(buff);

			return 0; 
		}
		if (!strcasecmp(token(buf,1), ":REMUSER")) 
		{ 
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			if (ptr[1] == NULL)
			{
				send_to_sock(s,
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: REMUSER [nickname]");	

				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_remuser(buff);

			return 0; 
		} 
		if (!strcasecmp(token(buf,1), ":SAY")) 
		{ 
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			if (ptr[1] == NULL)
			{
				send_to_sock(s,
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: SAY [bot] [#channel/nickname] [message]");

				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_say(buff);

			return 0; 
		}
		if (!strcasecmp(token(buf,1), ":ACTION")) 
		{ 
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			if (ptr[1] == NULL)
			{
				send_to_sock(s,
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: ACTION [bot] [#channel/nickname] [message]");

				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_action(buff);

			return 0; 
		} 
		if (!strcasecmp(token(buf,1), ":RAW")) 
		{
			char	*buff;

			buff = (char *)calloc(1, 1024);
			ptr[1] = strtok(NULL, "");

			if (ptr[1] == NULL)
			{
				send_to_sock(s,
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"Syntax: RAW [stuff]");

				return 0;
			}
			sprintf(buff, "%s PRIVMSG %s :%s %s",
				snick, mynick, ptr[0], ptr[1]);
			do_raw(buff);

			return 0; 
		} 
		if (!strcasecmp(token(buf,1), ":DIE"))
		{ 
			Admin	*a; 

			a = admin;
			a = findAdmin(snick);

			if (!a)
			{
				send_to_sock(s, 
					":%s NOTICE %s :\2%s\2",
					mynick, snick,
					"Permission denied.");
				return 0;
			}
			else 
			{
				if (!IsAdmin(a))
				{
					send_to_sock(s, 
						":%s NOTICE %s :\2%s\2\n",
						mynick, snick,
						"Permission denied.");
					return 0;
				}
				else
				{
					if (a->level != 1000) 
					{
						send_to_sock(s, 
							":%s NOTICE %s :%s\n",
							mynick, snick,
							"Permission denied.");
						return 0;
					}
					else
					{
						send_to_sock(s, 
							":%s NOTICE %s :%s\n",
							mynick, snick,
							"Shuting down services, saving databases.");

						send_to_sock(s, 
							"WALLOPS :Shuting down services by the request of %s\n",
							snick); 

						save_admin();
						save_cadmin();
						save_channel(); 
						save_gline();
						save_nsdb();
						save_bans();

						send_to_sock(s, 
							":%s QUIT :Shutdown by: %s\n",
							config->unick, snick);

						send_to_sock(s, 
							":%s QUIT :Shutdown by: %s\n",
							config->hnick, snick);

						send_to_sock(s, 
							":%s QUIT :Shutdown by: %s\n",
							config->nnick, snick);

						send_to_sock(s, 
							":%s QUIT :Shutdown by: %s\n",
							config->scnick, snick);

						send_to_sock(s, 
							":%s QUIT :Shutdown by: %s\n",
							config->wnick, snick);

						send_to_sock(s, 
							"SQUIT %s :Shutdown by: %s\n",
							config->servname, snick);

						exit(1);
					}
				}
			}
			return 0;
		}
		if (!strcasecmp(token(buf,1), ":LISTADMIN"))
		{
			Admin	*a;
			Nick	*n;

			for (a = admin; a; a = a->next)
			{
				n = findNick(a->nickname);
				if (!n)
				{
					send_to_sock(s, 
						":%s NOTICE %s :%s %s\n",
						mynick, snick,
						a->nickname,
						"is not logged on our network.");
				}
				else
				{
					if (IsAdmin(a))
					{
						send_to_sock(s, 
							":%s NOTICE %s :\2%s\2 (\2%s\2) is an authorized level [\2%d\2] admin.\n",
							mynick, snick, 
							a->nickname,
							n->userhost, 
							a->level);
					}
					else
					{
						send_to_sock(s,
							":%s NOTICE %s :\2%s\2 (\2%s\2) is an admin but is not authorized.\n",
							mynick, snick, 
							a->nickname, n->userhost);
					}	
				}
			}
			return 0;
		}
		if (!strcasecmp(token(buf,1), ":LISTUSERS"))
		{
			Nick   *n;

			send_to_sock(s,
				":%s NOTICE %s :Global user list.\n",
				mynick,snick);
			for (n = nick; n; n = n->next)
			{
				send_to_sock(s,
					":%s NOTICE %s :%s (\2%s\2) on %s\n",
					mynick, snick, n->nickname,
					n->userhost, n->server);
			}/*

				send_to_sock(s, 
					":%s NOTICE %s :Nickname: %s\n",
					mynick, snick, n->nickname);

				send_to_sock(s, 
					":%s NOTICE %s :Userhost: %s\n",
					mynick, snick, n->userhost);

				send_to_sock(s, 
					":%s NOTICE %s :Realname: %s\n",
					mynick, snick, n->realname);

				send_to_sock(s, 
					":%s NOTICE %s :Server: %s\n",
					mynick, snick, n->server);

				if (IsOper(n))
				{
					send_to_sock(s, 
						":%s NOTICE %s :%s %s\n",
						mynick, snick, n->nickname,
						"is an IRC Operator");
				}
				if (IsInvisible(n))
				{
					send_to_sock(s, 
						":%s NOTICE %s :%s %s\n",
						mynick, snick, n->nickname,
						"is invisible (+i)");
				}
				if (IsWallops(n))
				{
					send_to_sock(s, 
						":%s NOTICE %s :%s %s\n",
						mynick, snick, n->nickname,
						"is listening to wallops (+w)");
				}
				if (IsGlobops(n))
				{
					send_to_sock(s, 
						":%s NOTICE %s :%s %s\n",
						mynick, snick, n->nickname,
						"is listening to globops (+g)");
				}
				send_to_sock(s, 
					":%s NOTICE %s :%s\n",
					mynick, snick,
					"-------------------------------------------------------");
			} */
			return 0;
		}
		else
		{
			send_to_sock(s, 
				":%s NOTICE %s :Unknown Command: %s\n",
				mynick, snick, nocolon(token(buf,1)));
			return 0;
		}
		return 0;
	}
	if (!IsOper(n))
	{
		send_to_sock(s, 
			":%s NOTICE %s :\2%s\2\n",
			config->unick, n->nickname,
			"Permission denied.");
		return 0;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//

struct aGline *
checkforgline (hostname)
char	*hostname;
{
	struct	aGline	*g;

	g = gline;
	while (g)
	{
		if (!strcasecmp(g->userhost, hostname))
		{
			return g;
		}
		g = g->next;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//
//
// do_gline
//   Syntax: GLINE [user@host] [expire] [reason]
//
//     ptr[0] = Sender Nick
//     ptr[1] = OperServ Nick
//     ptr[2] = user@host
//     ptr[3] = expire
//     ptr[4] = reason
//
//   Description:
//       This is used to globaly ban users from the
//       network.
//
//

int
do_gline (buf)
char	*buf;
{
	Admin	*a;
	struct	aGline	*g;
	time_t	extime, chex;
	char	*ptr[9];
	int	gtime;

	ptr[0] = strtok(buf, " ");	/* sender nickname */
	strtok(NULL, " ");		/* information we don't need.. skip it */
	ptr[1] = strtok(NULL, " ");	/* operserv nickname */
	strtok(NULL, " ");		/* information we don't need.. skip it */
	ptr[2] = strtok(NULL, " ");	/* gline user@host */
	ptr[3] = strtok(NULL, " ");	/* gline expire time in seconds */
	ptr[4] = strtok(NULL, "\n");	/* reason for gline */
	extime = time(NULL) + atoi(ptr[3]);
	time(&extime);

	/*
	 * if someone forgot one of the arguments we would crash
	 * unless i did this. =) and its nice to have OS bitch
	 * a opers who don't know how to set a gline
	 */

	if ((ptr[2] == NULL) || (ptr[3] == NULL) || (ptr[4] == NULL))
	{
		send_to_sock(s, 
			":%s NOTICE %s :%s\n",
			ptr[1], ptr[0],
			"Syntax: GLINE [user@host] [Expire] [reason]");
		return 0;
	}

	/*
	 * this will stop opers/admins or anyone from adding *@* as a gline, 
	 * or from glining the entire network.
	 */

	if (!strcasecmp(ptr[2], "*@*"))
	{
		send_to_sock(s, 
			":%s NOTICE %s :Excessive GLINE [%s]\n", 
			ptr[1], ptr[0], ptr[2]);

		send_to_sock(s, 
			"WALLOPS :%s -- Excessive GLINE [%s]\n",
			ptr[0], ptr[2]);

		return 0;
	}
	gtime = atoi(ptr[3]);

	/*
	 * checks if the expire time is higher than 3600 seconds (1 hour) 
	 * and if your not an admin and try to gline for more than 3600 
	 * seconds this will reset the expire time back to 3600.
	 */

	if (gtime > 3600)   
	{
		a = findAdmin(ptr[0]);
		if (!a)
		{
			send_to_sock(s, 
				":%s NOTICE %s :%s\n",
				ptr[1], ptr[0],
				"Permission denied - Resetting gline to 3600 seconds.");
			strcpy(ptr[3], "3600");
		}
		if (!IsAdmin(a))
		{
			send_to_sock(s, 
				":%s NOTICE %s :%s\n",
				ptr[1], ptr[0],
				"Permission denied - Resetting gline to 3600 seconds.");
			strcpy(ptr[3], "3600");
		}
	}
	g = checkforgline(ptr[2]);

	/*
	 * if the gline already exist's reset the expire don't
	 * readd the gline to the database, or we could have
	 * problmes with checkgline.
	 */

	if (g)
	{
		chex = time(NULL) + atoi(ptr[3]);
		time(&chex);

		send_to_sock(s, 
			":%s NOTICE %s :Gline [%s] already in database\n",
			ptr[1], ptr[0], ptr[2]);

		send_to_sock(s, 
			":%s NOTICE %s :Resetting Gline\n",
			ptr[1], ptr[0], ptr[2]);

		send_to_sock(s, 
			"WALLOPS :%s Resetting gline for %s [Expires: %s]\n", 
			ptr[0], ptr[2], chop(ctime(&extime)));

		rem_gline(ptr[2]);
		addGline(ptr[2], time(NULL), atoi(ptr[3])+time(NULL), ptr[4]);

		return 0;
	}
#ifdef NO_OPER_GLINE
	a = findAdmin(ptr[0]);
	if (IsAdmin(a))
	{
#endif
		send_to_sock(s, 
			"WALLOPS :%s Adding gline for %s (%d Seconds) [Expires: %s] %s\n",
			ptr[0], ptr[2], atoi(ptr[3]), 
			chop(ctime(&extime)), ptr[4]);

		addGline(ptr[2], time(NULL), atoi(ptr[3])+time(NULL), ptr[4]);

		return 1;
#ifdef NO_OPER_GLINE
	}
	else
	{
		send_to_sock(s, ":%s NOTICE %s :\2%s\2\n",
			ptr[1], ptr[0],
			"Permission denied.");

		return 0;
	}
#endif
}

//////////////////////////////////////////////////////////////////////////////
//
//
//
// do_auth
//   Syntax: AUTH [nickname] [password]
//
//     ptr[0] = sender nickname
//     ptr[1] = my nickname
//
//   Description: Authorize your self as an admin on
//                OS.
//
//
//
//

int
do_auth (buf)
char   *buf;
{
	Admin	*a;
	Nick	*n;
	char	*ptr[4];
	char	salt[3];
	extern	char	*crypt();

	ptr[0] = strtok(buf, " ");	/* nickname */
	strtok(NULL, " ");		/* information that is not needed */
	ptr[1] = strtok(NULL, " ");	/* mynickname */
	a = findAdmin(token(buf,2));
	n = findNick(token(buf,2));

	if (!n)
	{
		send_to_sock(s,
			":%s NOTICE %s :%s\n",
			ptr[1], ptr[0],
			"You're not real, go away!");
		return 0;
	}
	if (!a)
	{
		send_to_sock(s, 
			":%s NOTICE %s :%s\n",
			ptr[1], ptr[0],
			"Authentication failed!");
		return 0;
	}
	if (IsAdmin(a))
	{
		send_to_sock(s, 
			":%s NOTICE %s :%s\n",
			ptr[1], ptr[0],
			"You're already authorized!");
		return 0;
	}
	if (!strcasecmp(ptr[0], a->nickname))
	{
		if (!strcasecmp(token(buf,2), a->nickname))
		{
			if (!match(a->hostname, n->userhost))
			{
				salt[0] = token(buf,3)[0];
				salt[1] = token(buf,3)[1];
				salt[2] = '\0';
				if (!strcasecmp(a->password, crypt(token(buf,3), salt)))
				{
					if (IsSusp(a))
					{
						send_to_sock(s, 
							":%s NOTICE %s :%s\n",
							ptr[1], ptr[0],
							"You're account has been suspended.");
						return 0;
					}
					else
					{
						send_to_sock(s, 
							":%s NOTICE %s :%s\n", 
							ptr[1], ptr[0],
							"Authorization successful!");
						SetAdmin(a);
						return 1;
					}
				}
				else
				{
					send_to_sock(s, 
						":%s NOTICE %s :%s\n",
						ptr[1], ptr[0],
						"Authentication failed!");
					DelAdmin(a);
					return 0;
				}
			}
			else
			{
				send_to_sock(s, 
					":%s NOTICE %s :%s\n",
					ptr[1], ptr[0],
					"Authentication failed!");
				DelAdmin(a);
				return 0;
			}
		}
		else
		{
			send_to_sock(s, 
				":%s NOTICE %s :%s\n",
				ptr[1], ptr[0],
				"Authentication failed!");
			DelAdmin(a);
			return 0;
		}
	}
	else
	{
		send_to_sock(s, 
			":%s NOTICE %s :%s\n",
			ptr[1], ptr[0],
			"Authentication failed!");
		DelAdmin(a);
		return 0;
	}
}

//////////////////////////////////////////////////////////////////////////////
//
//
// do_help
//   Syntax: HELP [help topic]
//
//     ptr[0] = sender nickname
//     ptr[1] = my nickname.
//
//   Description: help topic. allows opers to 
//                get a list of commands and
//                the commands arguments.
//
//

int
do_help (buf)
char	*buf;
{
	FILE	*fp;
	char	*ptr[8], file[1024], read[1024];

	ptr[0] = strtok(buf, " ");	/* sender nickname */
	strtok(NULL, " ");		/* information that is not needed */
	ptr[1] = strtok(NULL, " ");	/* my nickname */

	if (token(buf,2) == NULL)
	{
		fp = fopen("help/uworld/index", "r");
	}
	else
	{
		sprintf(file, "help/uworld/%s", token(buf,2));
		fp = fopen(file, "r");
	}
	if (!fp)
	{
		send_to_sock(s, 
			":%s NOTICE %s :%s\n",
			ptr[1], ptr[0],
			"Help file is missing.");
		return 0;
	}
	else
	{
		while (fgets(read, 256, fp) != NULL)
		{
			send_to_sock(s, 
				":%s NOTICE %s :%s\n",
				ptr[1], ptr[0], read);
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//
//
//
// num_nuk
//    Syntax: NUMNUK [nickname]
//
//      ptr[0] = sender nickname.
//      ptr[1] = my nickname.
//      ptr[2] = nickname to nuke.
//
//   Description: send a lot of numerics to a nickname
//                makes their client do some weird stuff.
//
//

int
num_nuk (buf)
char	*buf;
{ 
	char	*ptr[5];
	int	i;

	ptr[0] = strtok(buf, " ");	/* sender nickname */
	strtok(NULL, " ");		/* information that is not needed */
	ptr[1] = strtok(NULL, " ");	/* my nickname */
//	strtok(NULL, " ");		/* information that is not needed */

	send_to_sock(s, 
		":%s NOTICE %s :Nuking %s\n", 
		ptr[1], ptr[0], token(buf,2));

	for(i = 0; i < 500; i++)
	{
		send_to_sock(s, "381 %s :YEY!!!!:P\n",
			token(buf,2));
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//
//
//
//
// do_uptime
//    Syntax: UPTIME
//
//      ptr[0] = sender nickname.
//      ptr[2] = my nickname.
//
//   Description: tells how long services have been running.
//
//
//

int
do_uptime (buf)
char	*buf;
{
	char	*ptr[2];
	int	days, hours, mins, secs;
	time_t	curtime, uptime;

	ptr[0] = strtok(buf, " ");	/* sender nickname */
	strtok(NULL, " ");		/* information that is not needed */
	ptr[1] = strtok(NULL, " ");	/* my nickname */

	curtime = time(NULL);
	uptime = curtime - StartTime;

	days = uptime/86400;
	hours = (uptime/3600)%24;
	mins = (uptime/60)%60;
	secs = uptime%60;

	send_to_sock(s, 
		":%s NOTICE %s :Services up \2%d\2 day(s) \2%d\2 hour(s) \2%d\2 min(s) \2%d\2 sec(s)\n",
		ptr[1], ptr[0], days, hours, mins, secs);
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//
//
//
// do_mode
//     Syntax: MODE [#channel] [+/- mode(s)/nick]
//
//      ptr[0] = sender nickname.
//      ptr[1] = my nickname.
//      ptr[2] = channel.
//      ptr[3] = modes
//
//    Description: This command allows opers to 
//                 change channel modes without
//                 having to be oped in that 
//                 channel.
//
//
//

int
do_mode (buf)
char	*buf;
{
	char	*ptr[5];

	ptr[0] = strtok(buf, " ");	/* sender nickname */
	strtok(NULL, " ");		/* information that is not needed */
	ptr[1] = strtok(NULL, " ");	/* my nickname */
	strtok(NULL, " ");		/* information that is not needed */
	ptr[2] = strtok(NULL, " ");	/* channel */
	ptr[3] = strtok(NULL, "");	/* modes */
 
	if ((ptr[2] == NULL) || (ptr[3] == NULL))
	{
		send_to_sock(s, 
			":%s NOTICE %s :%s\n",
			ptr[1], ptr[0],
			"Syntax: MODE [#Channel] [modes]");

		return 0;
	}

	send_to_sock(s, 
		"MODE %s %s\n", 
		ptr[2], ptr[3]);

	send_to_sock(s, 
		"WALLOPS :%s CMD MODE %s %s\n", 
		ptr[0], ptr[2], ptr[3]);

	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//
//
// do_op
//     Syntax: OP [#channel] [nickname]
//
//      ptr[0] = sender nickname.
//      ptr[1] = my nickname.
//      ptr[2] = channel.
//      ptr[3] = nickname.
//
//    Description: This command allows opers to 
//                 op users in channels without
//                 having to be oped in that 
//                 channel.
//
//
//

int
do_op (buf)
char	*buf;
{
	char	*ptr[5];

	ptr[0] = strtok(buf, " ");	/* sender nickname */
	strtok(NULL, " ");		/* information that is not needed */
	ptr[1] = strtok(NULL, " ");	/* my nickname */
	strtok(NULL, " ");		/* information that is not needed */
	ptr[2] = strtok(NULL, " ");	/* channel */
	ptr[3] = strtok(NULL, "");	/* nickname */

	if ((ptr[2] == NULL) || (ptr[3] == NULL))
	{
		send_to_sock(s, 
			":%s NOTICE %s :%s\n",
			ptr[1], ptr[0],
			"Syntax: OP [#Channel] [nickname]");

		return 0;
	}
 
	send_to_sock(s, 
		"MODE %s +o %s\n", 
		ptr[2], ptr[3]);

	send_to_sock(s, 
		"WALLOPS :%s CMD OP %s %s\n", 
		ptr[0], ptr[2], ptr[3]);

	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//
//
// do_deop
//     Syntax: DEOP [#channel] [nickname]
//
//      ptr[0] = sender nickname.
//      ptr[1] = my nickname.
//      ptr[2] = channel.
//      ptr[3] = nickname
//
//    Description: This command allows opers to 
//                 deop users in a channel without
//                 having to be oped in that 
//                 channel.
//
//
//

int
do_deop (buf)
char	*buf;
{
	char	*ptr[5];

	ptr[0] = strtok(buf, " ");	/* sender nickname */
	strtok(NULL, " ");		/* information that is not needed */
	ptr[1] = strtok(NULL, " ");	/* my nickname */
	strtok(NULL, " ");		/* information that is not needed */
	ptr[2] = strtok(NULL, " ");	/* channel */
	ptr[3] = strtok(NULL, "");	/* nickname */

	if ((ptr[2] == NULL) || (ptr[3] == NULL))
	{
		send_to_sock(s, 
			":%s NOTICE %s :%s\n",
			ptr[1], ptr[0],
			"Syntax: DEOP [#Channel] [nickname]");

		return 0;
	}

	send_to_sock(s, 
		"MODE %s -o %s\n", 
		ptr[2], ptr[3]);

	send_to_sock(s, 
		"WALLOPS :%s CMD DEOP %s %s\n", 
		ptr[0], ptr[2], ptr[3]);

	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//
//
// do_kick
//    Syntax: KICK [#channel] [nickname] [reason]
//
//    ptr[0]   =   sender nickname
//    ptr[1]   =   service nickname
//
//  Description: Allows IRC Operators to remove users from 
//               a channel without having to be oped or
//               even in the channel.
//
//
//

int
do_kick (buf)
char	*buf;
{
	char	*ptr[6];

	ptr[0] = strtok(buf, " ");	/* sender nickname */
	strtok(NULL, " ");		/* not needed information */
	ptr[1] = strtok(NULL, " ");	/* my nickname */
	strtok(NULL, " ");		/* not needed information */
	ptr[2] = strtok(NULL, " ");	/* channel */
	ptr[3] = strtok(NULL, " ");	/* nick to kick */
	ptr[4] = strtok(NULL, "\n");	/* reason for kick */

	if ((ptr[2] == NULL) || (ptr[3] == NULL) || (ptr[4] == NULL))
	{
		send_to_sock(s, 
			":%s NOTICE %s :%s\n",
			ptr[1], ptr[0],
			"Syntax: KICK [#channel] [nick] [reason]");
		return 0;
	}

	send_to_sock(s, 
		"KICK %s %s :%s\n", 
		ptr[2], ptr[3], ptr[4]);

	send_to_sock(s, 
		"WALLOPS :%s CMD KICK %s %s :%s\n", 
		ptr[0], ptr[2], ptr[3], ptr[4]);

	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//
//
// do_clearmode
//     Syntax: CLEARMODE [#channel]
//
//     ptr[0]   =   sender nickname.
//     ptr[1]   =   service nickname.
//
//  Descriptioin: Allows IRC Operators to CLEAR all channel modes
//                from a channel (execpt (+p and +o) without
//                having to be oped or in the channel.
//
//
//

int
do_clearmode (buf)
char	*buf;
{
	char	*ptr[8];

	ptr[0] = strtok(buf, " ");	/* sender nickname */
	strtok(NULL, " ");		/* not needed information */
	ptr[1] = strtok(NULL, " ");	/* my nickname */

	if (token(buf,2) == NULL)
	{
		send_to_sock(s, 
			":%s NOTICE %s :%s\n",
			ptr[1], ptr[0],
			"Syntax: CLEARMODE [#channel]");
		return 0; 
	}

	send_to_sock(s, 
		"MODE %s -tmnspkl * *\n", 
		token(buf,2));

	send_to_sock(s, 
		"WALLOPS :%s CMD CLEARMODE %s\n", 
		ptr[0], token(buf,2));

	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//
//
// do_kill
//    Syntax: KILL [nickname] [reason]
//
//     ptr[0]   =   sender nickname.
//     ptr[1]   =   service nickname.
//     ptr[2]   =   nickname to kill.
//     ptr[3]   =   reason for kill.
//
//  Description: removes a user from the network (KILL)
//
//
//

int
do_kill (buf)
char	*buf;
{
	char	*ptr[6];

	ptr[0] = strtok(buf, " ");	/* sender nickname */
	strtok(NULL, " ");		/* not needed information */
	ptr[1] = strtok(NULL, " ");	/* my nickname */
	strtok(NULL, " ");		/* not needed information */
	ptr[2] = strtok(NULL, " ");	/* nickname to kill */
	ptr[3] = strtok(NULL, "\n");	/* reason for kill */

	if ((ptr[2] == NULL) || (ptr[3] == NULL))
	{
		send_to_sock(s, 
			":%s NOTICE %s :%s\n",
			ptr[1], ptr[0],
			"Syntax: KILL [nick] [reason]");

		return 0;
	}

	send_to_sock(s, 
		"KILL %s :%s\n", 
		ptr[2], ptr[3]);

	send_to_sock(s, 
		"WALLOPS :%s CMD KILL %s :%s\n", 
		ptr[0], ptr[2], ptr[3]);

	return 0;
}



//////////////////////////////////////////////////////////////////////////////
//
//
// do_masskill
//    Syntax: MASSKILL [user@host] [reason]
//
//     ptr[0]   =   sender nickname.
//     ptr[1]   =   service nickname.
//     ptr[2]   =   hostname to masskill.
//     ptr[3]   =   reason for masskill.
//
//  Description: removes every user matchin user@host from the network (KILL)
//
//
//

int
do_masskill (buf)
char	*buf;
{
	Admin	*a;
	Nick	*n;
	char	*ptr[6];

	ptr[0] = strtok(buf, " ");	/* sender nickname */
	strtok(NULL, " ");		/* not needed information */
	ptr[1] = strtok(NULL, " ");	/* my nickname */
	strtok(NULL, " ");		/* not needed information */
	ptr[2] = strtok(NULL, " ");	/* user@host to kill */
	ptr[3] = strtok(NULL, "\n");	/* reason for kill */

	if ((ptr[2] == NULL) || (ptr[3] == NULL))
	{
		send_to_sock(s, 
			":%s NOTICE %s :%s\n",
			ptr[1], ptr[0],
			"Syntax: MASSKILL [username@hostname] [reason]");

		return 0;
	}

	if ((!match(ptr[2], "*")) || (!match(ptr[2], "*@*")) ||
		(!match(ptr[2], "*@*.*")))
	{
		send_to_sock(s,
			":%s NOTICE %s :Excessive Masskill.\n",
			ptr[1], ptr[0]);

		return 0;
	}

	for (n = nick; n; n = n->next)
	{
		if (!match(ptr[2], n->userhost))
		{
			send_to_sock(s, 
				":%s KILL %s :Masskill on [%s] -- %s\n", 
				config->unick, n->nickname, ptr[2],
				ptr[3]);

			a = findAdmin(n->nickname);
			if (a)
			{
				if (IsAdmin(a))
				{
					DelAdmin(a);
				}
			}
			delNick(n->nickname);
		}
	}
	send_to_sock(s, 
		"WALLOPS :%s CMD MASSKILL %s :%s\n", 
		ptr[0], ptr[2], ptr[3]);

	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//
//
// do_join
//    Syntax: JOIN [servicebot] [#channel]
//
//    ptr[0]   =   sender nickname.
//    ptr[1]   =   service nickname.
//
//  Description: Make a service bot join a channel.
//
//
//

int
do_join (buf)
char	*buf;
{
	char   *ptr[8];

	ptr[0] = strtok(buf, " ");	/* sender nickname */
	strtok(NULL, " ");		/* not needed information */
	ptr[1] = strtok(NULL, " ");	/* my nickname */
	strtok(NULL, " ");		/* not needed information */

	if ((token(buf,1) == NULL) || (token(buf,2) == NULL))
	{
		send_to_sock(s, 
			":%s NOTICE %s :%s\n",
			ptr[1], ptr[0],
			"Syntax: JOIN [nick] [#channel]");

		return 0;
	}

	ptr[2] = strtok(NULL, " ");	/* service nickname */
	ptr[3] = strtok(NULL, "\n");	/* channel */

	send_to_sock(s, 
		"WALLOPS :%s %s JOIN %s\n",
		ptr[0], ptr[2], ptr[3]);

	send_to_sock(s, 
		":%s JOIN %s\n", 
		ptr[2], ptr[3]);

	send_to_sock(s, 
		"MODE %s +o %s\n",
		ptr[2], ptr[3]);

	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//
//
// do_part
//    Syntax: PART [servicebot] [#channel]
//
//    ptr[0]   =   sender nickname.
//    ptr[1]   =   service nickname.
//
//  Description: Make a service bot leave a channel.
//
//

int
do_part (buf)
char	*buf;
{
	char   *ptr[8];

	ptr[0] = strtok(buf, " ");	/* sender nickname */
	strtok(NULL, " ");		/* not needed information */
	ptr[1] = strtok(NULL, " ");	/* my nickname */
	strtok(NULL, " ");		/* not needed information */

	if ((token(buf,1) == NULL) || (token(buf,2) == NULL))
	{
		send_to_sock(s, 
			":%s NOTICE %s :%s\n",
			ptr[1], ptr[0],
			"Syntax: PART [nick] [#channel]");

		return 0;
	}

	ptr[2] = strtok(NULL, " ");	/* service bot nick */
	ptr[3] = strtok(NULL, "\n");	/* channel */

	send_to_sock(s, 
		"WALLOPS :%s %s PART %s\n",
		ptr[0], ptr[2], ptr[3]);

	send_to_sock(s, 
		":%s PART %s\n", 
		ptr[2], ptr[3]);

	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//

int
do_verify (buf)
char	*buf;
{
	Nick	*n;
	Admin	*a;
	char	*ptr[3];

	ptr[0] = strtok(buf, " ");
	strtok(NULL, " ");
	ptr[1] = strtok(NULL, " ");

	if (token(buf,2) == NULL)
	{
		send_to_sock(s,
			":%s NOTICE %s :%s\n",
			ptr[1], ptr[0], 
			"Syntax: VERIFY [nickname]");
		return 0;
	}

	n = findNick(token(buf,2));
	a = findAdmin(token(buf,2));

	if (!n)
	{
		send_to_sock(s,
			":%s NOTICE %s :%s not found.\n",
			ptr[1], ptr[0], 
			token(buf,2));
		return 0;
	}
	else
	{
		if (IsOper(n))
		{
			send_to_sock(s,
				":%s NOTICE %s :\2%s\2 is an IRC Operator\n",
				ptr[1], ptr[0],
				token(buf,2));
		}
		else
		{
			send_to_sock(s,
				":%s NOTICE %s :\2%s\2 is not an IRC operator\n",
				ptr[1], ptr[0],
				token(buf,2));
			return 0;
		}
		if (a)
		{
			if (IsAdmin(a))
			{
				send_to_sock(s,
					":%s NOTICE %s :\2%s\2 is an authorized level \2%d\2 admin.\n",
					ptr[1], ptr[0],
					token(buf,2), a->level);
			}
			else
			{
				send_to_sock(s,
					":%s NOTICE %s :\2%s\2 is a non-authorized level \2%d\2 admin.\n",
					ptr[1], ptr[0],
					token(buf,2), a->level);
			}
					
		}

	}	
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//
// do_operlist
//	Syntax: OPERLIST
//
//	Desc: Gives you a complete list of GLOBAL IRC Operators.
//
//

int
do_operlist (buf)
char	*buf;
{
	Nick	*n;
	char	*ptr[2];

	ptr[0] = strtok(buf, " ");
	strtok(NULL, " ");
	ptr[1] = strtok(NULL, " ");

	send_to_sock(s,
		":%s NOTICE %s :Global IRC Operator List!\n",
		ptr[1], ptr[0]);

	for (n = nick; n; n = n->next)
	{
		if (IsOper(n))
		{
			send_to_sock(s,
				":%s NOTICE %s :%s (\2%s\2)\n",
				ptr[1], ptr[0], 
				n->nickname, n->userhost);
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//

int
do_opermsg (buf)
char	*buf;
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//

int
do_map (buf)
char	*buf;
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//

int
do_invite (buf)
char	*buf;
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//

int
do_whois (buf)
char	*buf;
{
	Admin	*a;
	Cadmin	*ca;
	Nick	*n;

	char	*ptr[5];

	ptr[0] = strtok(buf, " ");
	strtok(NULL, " ");
	ptr[1] = strtok(NULL, " ");

	a = findAdmin(token(buf,2));
	n = findNick(token(buf,2));

	if (!n)
	{
		send_to_sock(s,
			":%s NOTICE %s :No such user [%s]\n",
			ptr[1], ptr[0], token(buf,2));
		return 0;
	}
	else
	{
		send_to_sock(s,
			":%s NOTICE %s :%s is %s %s\n",
			ptr[1], ptr[0], token(buf,2),
			n->userhost, n->realname);
		send_to_sock(s,
			":%s NOTICE %s :on server %s\n",
			ptr[1], ptr[0], n->server);
		if (IsOper(n))
		{
			send_to_sock(s,
				":%s NOTICE %s :%s is an IRC Operator\n",
				ptr[1], ptr[0], token(buf,2));
		}
		time(&n->ConnTime);
		send_to_sock(s,
			":%s NOTICE %s :%s signed on %s\n",
			ptr[1], ptr[0], token(buf,2),
			chop(ctime(&n->ConnTime)));
		if (a)
		{
			if (!IsAdmin(a))
			{
				send_to_sock(s,
					":%s NOTICE %s :%s is a Services Admin (not authed)\n",
					ptr[1], ptr[0], token(buf,2));
			}
			else
			{
				send_to_sock(s,
					":%s NOTICE %s :%s is a [%d] Services Admin \n",
					ptr[1], ptr[0], token(buf,2),
					a->level);
			}
		} 
		else 
		{ 
		}
		for (ca = cadmin; ca; ca = ca->next)
		{
			if (!strcasecmp(ca->nickname, token(buf,2)))
			{
				if (ca->level == 500)
				{
					send_to_sock(s,
						":%s NOTICE %s :%s owns the channel %s\n",
						ptr[1], ptr[0], token(buf,2),
						ca->channel);
				}
				if (ca->level == 400)
				{
					send_to_sock(s,
						":%s NOTICE %s :%s is a channel admin on %s\n",
						ptr[1], ptr[0], token(buf,2),
						ca->channel);
				}
				if (ca->level == 350)
				{
					send_to_sock(s,
						":%s NOTICE %s :%s is a channel oper on %s\n",
						ptr[1], ptr[0], token(buf,2),
						ca->channel);
				}
				if (ca->level == 1)
				{
					send_to_sock(s,
						":%s NOTICE %s :%s is a channel voice on %s\n",
						ptr[1], ptr[0], token(buf,2),
						ca->channel);
				}
			}
		}
	}	
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//

int
do_access (buf)
char	*buf;
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//

int
do_mkpasswd (buf)
char	*buf;
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//

int
do_count (buf)
char	*buf;
{
	Nick	*n;
	char	*ptr[3];
	int	numHosts = 0;

	ptr[0] = strtok(buf, " ");
	strtok(NULL, " ");
	ptr[1] = strtok(NULL, " ");

	if (!token(buf,2))
	{
		send_to_sock(s,
			":%s NOTICE %s :Syntax: COUNT [hostmask]\n",
			ptr[1], ptr[0]);
		return 0;
	}

	send_to_sock(s,
		":%s NOTICE %s :Couting hostnames matching %s\n",
		ptr[1], ptr[0], token(buf,2));

	for (n = nick; n; n = n->next)
	{
		ptr[2] = token(buf,2);
		if (!match(ptr[2], n->userhost))
		{
			numHosts++;
		}
	}
	send_to_sock(s,
		":%s NOTICE %s :%d hostnames found matching %s\n",
		ptr[1], ptr[0], numHosts, token(buf,2));

	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//

int
do_njupe (buf)
char	*buf;
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//

int
do_remnjupe (buf)
char	*buf;
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//

//////////////////////////////////////////////////////////////////////////////
//

int
do_jupe (buf)
char	*buf;
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//

int
do_remjupe (buf)
char	*buf;
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//

int
do_rehash (buf)
char	*buf;
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//

int
do_collide (buf)
char	*buf;
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//

int
do_save (buf)
char	*buf;
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//

int
do_suspend (buf)
char	*buf;
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//

int
do_remsuspend (buf)
char	*buf;
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//

int
do_adduser (buf)
char	*buf;
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//

int
do_moduser (buf)
char	*buf;
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//

int
do_remuser (buf)
char	*buf;
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//

int
do_say (buf)
char	*buf;
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//

int
do_action (buf)
char	*buf;
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//

int
do_raw (buf)
char	*buf;
{
	Admin	*a;
	char *ptr[3];

	ptr[0] = strtok(buf, " ");
	strtok(NULL, " ");
	ptr[1] = strtok(NULL, " ");
	strtok(NULL, " ");
	ptr[2] = strtok(NULL, "");

	a = findAdmin(ptr[0]);
	if (!a)
	{
		send_to_sock(s,
			":%s NOTICE %s :\2Permission Denied.\2\n",
			ptr[1], ptr[0]);
		return 0;
	}
	else
	{
		if (IsAdmin(a))
		{
			if (a->level >= 800)
			{
				send_to_sock(s, 
					"%s\n", ptr[2]);
				send_to_sock(s,
					"WALLOPS :%s CMD RAW %s\n",
					ptr[0], ptr[2]);
				return 1;
			}
			else
			{
				send_to_sock(s,
					":%s NOTICE %s :\2%s\2\n",
					ptr[1], ptr[0],
					"Not Enough Access.");
				return 0;
			}
		}
		else
		{
			send_to_sock(s,
				":%s NOTICE %s :\2Permission Denied.\2\n",
				ptr[1], ptr[0]);
			return 0;
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//


