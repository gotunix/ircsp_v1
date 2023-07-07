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

Hosts	*addHost		(char *);
Hosts	*findHost		(char *);
void	delHost			(char *);

///////////////////////////////////////////////////////////////////////////////
//

Hosts *
addHost (hostname)
char	*hostname;
{
	Hosts	*h;
	int	mFail = 0, mPass = 0;

	h = (Hosts *)calloc(1, sizeof(Hosts));
	{
		if (!h)
		{
			if (config->debug)
			{
				printf(
					"addHost(): calloc() of h failed\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addHost(): calloc() of h [%p] passed.\n",
					h);
			}
			mPass++;
		}
	}
	h->hostname = (char *)calloc(1, 1024);
	{
		if (!h->hostname)
		{
			if (config->debug)
			{
				printf(
					"addHost(): calloc() of h->hostname failed\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addHost(): calloc() of h->hostname [%p] passed.\n",
					h->hostname);
			}
			mPass++;
		}
	}


	strcpy(h->hostname, hostname);
	h->numHosts++;

	if (config->debug)
	{
		printf(
			"addHost(): HST: %s\n",
			h->hostname);
	}

	if (!hosts)
	{
		hosts = h;
		h->next = NULL;
	}
	else
	{
		h->next = hosts;
		hosts = h;
	}
	return h;
}

///////////////////////////////////////////////////////////////////////////////
//

Hosts *
findHost (hostname)
char	*hostname;
{
	Hosts	*h;
	h = hosts;

	while (h)
	{
		if (!strcasecmp(h->hostname, hostname))
		{
			if (config->debug)
			{
				printf(
					"findHost(): %s [%p] found.\n",
					h->hostname, h->hostname);
			}
			return h;
		}
		h = h->next;
	}
	if (config->debug)
	{
		printf(
			"findHost(): %s not found\n",
			hostname);
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
//

void
delHost (hostname)
char	*hostname;
{
	Hosts	*h, *next, *delete;

	for (h = hosts; h; h = next)
	{
		next = h->next;
		if (!strcasecmp(h->hostname, hostname))
		{
			if (config->debug)
			{
				printf(
					"delHost(): %s [%p] found, removing.\n",
					h->hostname, h->hostname);
			}
			if (hosts == h)
			{
				hosts = h->next;
			}
			else
			{
				for (delete = hosts; (delete->next != h) && delete; delete = delete->next);
				delete->next = h->next;
			}
			free (h->hostname);
			free (h);
			return ;
		}
		if (config->debug)
		{
			printf(
				"delHost(): %s not found\n",
				hostname);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//

