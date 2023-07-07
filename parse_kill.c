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

int	parse_kill		(char *, char *);

//////////////////////////////////////////////////////////////////////////////
//

int
parse_kill (nick,buf)
char	*nick;
char	*buf;
{
	char	*ptr[2];

	ptr[0] = strtok(buf, " ");
	strtok(NULL, "(");
	ptr[1] = strtok(NULL, ")");

	printf("ptr1 %s\n", ptr[0]);
	printf("ptr2 %s\n", ptr[1]);

	if (!strcasecmp(ptr[0], config->unick))
	{
		send_to_sock(s, 
			"WALLOPS :%s killed %s :%s\n",
			nick, ptr[0], ptr[1]);

		send_to_sock(s, 
			"NICK %s 1 0 %s %s %s :%s\n",
			config->unick, config->unick, 
			config->servname, config->servname, 
			config->udesc);

		send_to_sock(s, 
			":%s MODE %s +o\n",
			config->unick, config->unick);

		send_to_sock(s, 
			"NOTICE %s :%s\n",
			nick,"Don't KILL service bots.");
		return 0;
	}
	if (!strcasecmp(ptr[0], config->nnick))
	{
		send_to_sock(s, 
			"WALLOPS :%s killed %s :%s\n",
			nick, ptr[0], ptr[1]);

		send_to_sock(s, 
			"NICK %s 1 0 %s %s %s :%s\n",
			config->nnick, config->nnick, 
			config->servname, config->servname, 
			config->ndesc);

		send_to_sock(s, 
			":%s MODE %s +o\n",
			config->nnick, config->nnick);

		send_to_sock(s, 
			"NOTICE %s :%s\n",
			nick, "Don't KILL service bots.");
		return 0;
	}
	if (!strcasecmp(ptr[0], config->hnick))
	{
		send_to_sock(s, 
			"WALLOPS :%s killed %s :%s\n",
			nick, ptr[0], ptr[1]);

		send_to_sock(s, 
			"NICK %s 1 0 %s %s %s :%s\n",
			config->hnick, config->hnick, 
			config->servname, config->servname, 
			config->hdesc);

		send_to_sock(s, 
			"NOTICE %s :%s\n",
			nick, "Don't KILL service bots.");
		return 0;
	}
	if (!strcasecmp(ptr[0], config->scnick))
	{
		send_to_sock(s, 
			"WALLOPS :%s killed %s :%s\n",
			nick, ptr[0], ptr[1]);

		send_to_sock(s, 
			"NICK %s 1 0 %s %s %s :%s\n",
			config->scnick, config->scnick, 
			config->servname, config->servname, 
			config->scdesc);

		send_to_sock(s, 
			"NOTICE %s :%s\n",
			nick, "Don't KILL service bots.");
		return 0;
	}
	if (!strcasecmp(ptr[0], config->wnick))
	{
		send_to_sock(s, 
			"WALLOPS :%s killed %s :%s\n",
			nick, ptr[0], ptr[1]);

		send_to_sock(s, 
			"NICK %s 1 0 %s %s %s :%s\n",
			config->wnick, config->wnick, 
			config->servname, config->servname, 
			config->wdesc);

		send_to_sock(s, 
			"NOTICE %s :%s\n",
			nick, "Don't KILL service bots.");
		return 0;
	}
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//


