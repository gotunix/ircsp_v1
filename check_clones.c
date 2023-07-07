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

void	checkclones	(void);

void
checkclones (void)
{
	Hosts	*h;
	Nick	*n;

	for (h = hosts; h; h = h->next)
	{
		if (h->clones == 2)		// user has 2 clones on. warn him not
		{				// load any more.
			for (n = nick; n; n = n->next)
			{
				if (!strcasecmp(n->userhost, h->hostname))
				{
					send_to_sock(s, 
						":%s NOTICE %s :Possible [%d] clones dectected from your host\n",
						config->unick, n->nickname, h->clones);
					send_to_sock(s,
						":%s NOTICE %s :One more clone and the IRC operators will be notified. If you continue to load clones, you will be auto-glined.\n",
						config->unick, n->nickname);
				}
			}
		}
		else if (h->clones >= 3)	// user has 3 clones, warn the opers.
		{
			send_to_sock(s,
				"WALLOPS :Possible [%d] clones from %s\n",
				h->clones, h->hostname);
			for (n = nick; n; n = n->next)
			{
				if (!strcasecmp(n->userhost, h->hostname))
				{
					send_to_sock(s,
						":%s NOTICE %s :Possible [%d] clones dectected from your host\n",
						config->unick, n->nickname, h->clones);
					send_to_sock(s,
						":%s NOTICE %s :One more clone and you will be glined.\n",
						config->unick, n->nickname);
				}
			}
		}
		else if (h->clones >= 4)	// BAD! a really stupid move for h->hostname 
		{				// cause he is now glined! :P
			for (n = nick; n; n = n->next)
			{
				if (!strcasecmp(n->userhost, h->hostname))
				{
					send_to_sock(s,
						":%s NOTICE %s :You have now been put on auto-gline, congraulations for not listing.\n",
						config->unick, n->nickname);
					addGline(h->hostname, time(NULL), 120+time(NULL),
						"Auto-Gline [Clones]");
				}
			}
		}
	}
}


