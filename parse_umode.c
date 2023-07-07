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

int	parse_umode		(char *, char *);

//////////////////////////////////////////////////////////////////////////////
//

int
parse_umode (nick,modes)
char	*nick;
char	*modes;
{
	Nick	*n;
	int	p, addmode;

	n = findNick(nick);
	p = -1;
	addmode = 0;

	if (!n)
	{
		return 0;
	}
	while (modes[++p] != '\0')
	{
		if (modes[p] == '+')
		{
			addmode = 1;
			continue;
		}
		if (modes[p] == '-')
		{
			addmode = 0;
			continue;
		}
		if (modes[p] == 'w')
		{
			if (addmode)
			{
				SetWall(n);
			}
			else
			{
				DelWall(n);
			}
		}
		if (modes[p] == 'i')
		{
			if (addmode)
			{
				SetInv(n);
			}
			else
			{
				DelInv(n);
			}
		}
		if (modes[p] == 'g')
		{
			if (addmode)
			{
				SetGlob(n);
			}
			else
			{
				DelGlob(n);
			}
		}
		if (modes[p] == 'o')
		{
			if (addmode)
			{
				if (config->opergreet)
				{
					char	readf[512];
					FILE	*fp;

					fp = fopen("oper_greet", "r");
					if (fp)
					{
						while (fgets(readf, 256, fp) != NULL)
						{
							if (readf[0] == ';')
							{
								continue;
							}
							send_to_sock(s, 
								"NOTICE %s :[\2OPER NOTICE\2] %s\n",
								n->nickname, readf);
						}
					}
				}
				SetOper(n);
			}
			else
			{
				DelOper(n);
				if (config->opergreet)
				{
					send_to_sock(s, 
						"NOTICE %s :%s\n",
						n->nickname,
						"Have a nice day!");
				}
			}
		}
	}
		return 0;
}

//////////////////////////////////////////////////////////////////////////////
//


