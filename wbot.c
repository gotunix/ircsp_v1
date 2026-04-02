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

int	do_wbot			(char *, char *, char *);
int	do_w_auth		(char *);
int	do_w_help		(char *);
int	do_w_register		(char *);

//////////////////////////////////////////////////////////////////////////////
//

int
do_wbot(nick,mynick,buf)
char	*nick;
char	*mynick;
char	*buf;
{
	char	*ptr[9];

	ptr[0] = strtok(buf, " ");
	ptr[0]++;

	if (!strcasecmp(token(buf,1), ":AUTH"))
	{
		char	*buff;

		buff = (char *)calloc(1, 1024);
		ptr[1] = strtok(NULL, "");

		if (ptr[1] == NULL)
		{
			send_to_sock(s, 
				":%s NOTICE %s :%s\n",
				mynick, nick,
				"Syntax: AUTH [channel] [nickname] [password]");

			return 0;
		}
		sprintf(buff, "%s PRIVMSG %s :%s %s",
			nick, mynick, ptr[0], ptr[1]);
		do_w_auth(buff);

		return 0;
	}
	if (!strcasecmp(token(buf,1), ":HELP"))
	{
		char	*buff;

		buff = (char *)calloc(1, 1024);
		ptr[1] = strtok(NULL, "");
		sprintf(buff, "%s PRIVMSG %s :%s %s",
			nick, mynick, ptr[0], ptr[1]);
		do_w_help(buff);

		return 0;
	}
	if (!strcasecmp(token(buf,1), ":REGISTER"))
	{
		char	*buff;

		buff = (char *)calloc(1, 1024);
		ptr[1] = strtok(NULL, "");

		if (ptr[1] == NULL)
		{
			send_to_sock(s, 
				":%s NOTICE %s :%s\n",
				mynick, nick,
				"Syntax: REGISTER [#channel] [password]");

			return 0;
		}
		sprintf(buff, "%s PRIVMSG %s :%s %s",
			nick, mynick, ptr[0], ptr[1]);
		do_w_register(buff);

		return 0;
	}
	else
	{
		send_to_sock(s, 
			":%s NOTICE %s :Unknown Command: %s\n",
			mynick, nick, nocolon(token(buf,1)));
		return 0;
	}
}

//////////////////////////////////////////////////////////////////////////////
//
//
// do_w_auth
//    Syntax: AUTH [#channel] [nickname] [password]
//
//    ptr[0]       = sender nickname
//    ptr[1]       = my nickname
//    ptr[2]       = NULL
//    ptr[3]       = channel
//    token(buf,1) = nickname
//    token(buf,2) = password
//
//  Description: Authorize your self with CS on your channel.
//
//

int
do_w_auth (buf)
char	*buf;
{
	ChanDB	*c; 
	Cadmin	*ca;
	char	*ptr[9];

	ptr[0] = strtok(buf, " ");
	strtok(NULL, " ");
	ptr[1] = strtok(NULL, " ");
	ptr[2] = strtok(NULL, " ");
	ptr[3] = strtok(NULL, " ");

	if ((ptr[1] == ' ') || (ptr[2] == ' ') || (ptr[3] == ' ') ||
		(token(buf,1) == ' ') || (token(buf,2) == ' '))
	{
		send_to_sock(s,"WALLOPS :do_w_auth() syntax error.\n");
		return 0;
	}
	ca = findCadmin(ptr[3], token(buf,1));
	c = findChan(ptr[3]);

	if (!c)
	{
		send_to_sock(s, 
			":%s NOTICE %s :Channel %s is not registered\n",
			ptr[1], ptr[0], ptr[3]);
		return 0;
	}
	if (!ca)
	{
		send_to_sock(s, 
			":%s NOTICE %s :%s\n",
			ptr[1], ptr[0],
			"Authentication failed!");
		return 0;
	}
	if (IsCAdmin(ca))
	{
		send_to_sock(s, 
			":%s NOTICE %s :%s\n",
			ptr[1], ptr[0], 
			"You're already authorized!");
		return 0;
	}
	if (!strcasecmp(ptr[1], c->bot))
	{
		if (!strcasecmp(ca->channel, ptr[3]))
		{
			if (!strcasecmp(ca->nickname, ptr[0]))
			{
				if (!strcasecmp(ca->nickname, token(buf,1)))
				{
					if (!strcasecmp(ca->password, token(buf,2)))
					{
						if (ca->level == 0)
						{
							send_to_sock(s, 
								":%s NOTICE %s :%s\n",
								ptr[1], ptr[0],
								"There is no need to auth a level 0 user.");
							return 0;
						}
						else
						{
							send_to_sock(s, 
								":%s NOTICE %s :Authencation Successful on %s\n", 
								ptr[1], ptr[0], ca->channel);
							SetCAdmin(ca);

							if ((IsChanOwner(ca)) || (IsChanAdmin(ca)) ||
								(IsChanOper(ca)))
							{
								send_to_sock(s, 
									":%s MODE %s +o %s\n", 
									ptr[1], ca->channel, ca->nickname);
								return 1;
							}
							if (IsChanVoice(ca))
							{
								send_to_sock(s, 
									":%s MODE %s +v %s\n",
									ptr[1], ca->channel, ca->nickname);
								return 1;
							}
						}
					}
					else
					{
						send_to_sock(s, 
							":%s NOTICE %s :%s\n",
							ptr[1], ptr[0],
							"Authentication failed!");
						DelCAdmin(ca);
					}
				}
				else
				{ 
					send_to_sock(s, 
						":%s NOTICE %s :%s\n",
						ptr[1], ptr[0],
						"Authentication failed!"); 
					DelCAdmin(ca); 
				} 
			} 
			else 
			{
				send_to_sock(s, 
					":%s NOTICE %s :%s\n",
					ptr[1],ptr[0],
					"Authentication failed!"); 
				DelCAdmin(ca); 
			} 
		} 
		else 
		{ 
			send_to_sock(s, 
				":%s NOTICE %s :%s\n",
				ptr[1], ptr[0],
				"Authentication failed!");
			DelCAdmin(ca); 
		} 
	} 
	else 
	{
		send_to_sock(s, 
			":%s NOTICE %s :%s\n",
			ptr[1], ptr[0],
			"Authentication failed!");
		DelCAdmin(ca); 
	} 
	return 0;  
}

//////////////////////////////////////////////////////////////////////////////
//
//
//
// do_w_help
//   Syntax: HELP, or HELP [topic]
//
//   ptr[0]       = sender nickname
//   ptr[1]       = my nickname
//   token(buf,2) = help topic, if there is one
//
//  Description: HELP
//
//

int
do_w_help (buf)
char	*buf;
{
	FILE	*fp, *fp2;
	char	*ptr[8], read[1024], file[512];

	ptr[0] = strtok(buf, " ");	/* sender nickname */
	strtok(NULL, " ");		/* information that is not needed */
	ptr[1] = strtok(NULL, " ");	/* service nickname */

	sprintf(file, "help/w/%s", token(buf,2));
	fp = fopen(file, "r");
	if (!fp)
	{
		fp2 = fopen("help/w/index", "r");

		if (!fp2)
		{
			send_to_sock(s, 
				":%s NOTICE %s :%s\n",
				ptr[1], ptr[0],
				"Help file is missing.");

			return 0;
		}
		else
		{
			while (fgets(read, 512, fp2) != NULL)
			{
				send_to_sock(s, 
					":%s NOTICE %s :%s\n",
					ptr[1], ptr[0], read);
			}
			return 0;
		}
	}
	else
	{
		while (fgets(read, 512, fp) != NULL)
		{
			send_to_sock(s, 
				":%s NOTICE %s :%s\n",
				ptr[1], ptr[0], read);
		}
		return 0;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//

int
do_w_register (buf)
char	*buf;
{
/*	ChanDB	*ctemp;		not needed till i re-write channel
				registration.. */
	char	*ptr[8];

	ptr[0] = strtok(buf, " ");	/* sender nickname */
	strtok(NULL, " ");		/* skip, not needed */
	ptr[1] = strtok(NULL, " ");	/* service nickname */
	strtok(NULL, " ");		/* skip, not needed */
	ptr[2] = strtok(NULL, " ");	/* channel name */
	ptr[3] = strtok(NULL, "\n");	/* email to send form to */

return 0;
}

//////////////////////////////////////////////////////////////////////////////
//


