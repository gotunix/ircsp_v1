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


