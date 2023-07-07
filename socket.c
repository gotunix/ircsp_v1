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
#include "socket.h"

int	conn			();
int	sockread		(int, char *);

//////////////////////////////////////////////////////////////////////////////
//

int
conn ()
{
	struct	hostent		*hp;
	struct	sockaddr_in	sin;
	int			port;

	if ((hp = gethostbyname (config->server) ) == NULL) 
	{
		printf(
			"conn()  --  ERROR: Unknown hostname (%s)\n",
			config->server);

		exit(1);
	}
	if (( s = socket (AF_INET, SOCK_STREAM, 0) ) < 0) 
	{
		printf(
			"conn()  --  ERROR: Client: Socket\n");

		exit (1);
	}

	sin.sin_family = AF_INET;
	port = atoi (config->port);
	sin.sin_port = htons(port);
	bcopy (hp->h_addr, &sin.sin_addr, hp->h_length);

	if (connect(s, (struct sockaddr *)&sin, sizeof (sin) ) < 0) 
	{
		printf(
			"conn()  --  ERROR: Client: Connect\n");

		exit(1);
	}

	serv = fdopen(s, "a+");

	send_to_sock(s, 
		"PASS :%s\n", 
		config->password);

	send_to_sock(s, 
		"SERVER %s 1 %lu %lu P09 :%s\n",
		config->servname, time(NULL), time(NULL),
		config->servdesc);

	send_to_sock(s, 
		"NICK %s 1 0 %s %s %s :%s\n",
		config->unick, config->unick, 
		config->servname, config->servname, 
		config->udesc);

	send_to_sock(s, 
		"NICK %s 1 0 %s %s %s :%s\n",
		config->nnick, config->nnick, 
		config->servname, config->servname,
		config->ndesc);

	send_to_sock(s, 
		"NICK %s 1 0 %s %s %s :%s\n",
		config->scnick, config->scnick, 
		config->servname, config->servname, 
		config->scdesc);

	send_to_sock(s, 
		"NICK %s 1 0 %s %s %s :%s\n",
		config->hnick, config->hnick, 
		config->servname, config->servname, 
		config->hdesc);

	send_to_sock(s, 
		"NICK %s 1 0 %s %s %s :%s\n",
		config->wnick, config->wnick, 
		config->servname, config->servname, 
		config->wdesc);

	send_to_sock(s, 
		":%s MODE %s +o\n",
		config->unick, config->unick);

	send_to_sock(s, 
		":%s MODE %s +o\n",
		config->nnick, config->nnick);

	send_to_sock(s, 
		":%s JOIN %s\n",
		config->unick, config->clonechan);

	send_to_sock(s, 
		":%s JOIN %s\n",
		config->unick, config->statchan);

	send_to_sock(s, 
		"MODE %s +oiws %s\n",
		config->statchan, config->unick);

	send_to_sock(s, 
		"MODE %s +oiws %s\n",
		config->clonechan, config->unick);

	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//

int 
send_to_sock (int socket, const char *fmt, ...) 
{
	char	*string;
	va_list	args;

	string = malloc(MAXBUFLENGTH);

	va_start(args, fmt);
	vsnprintf(string, MAXBUFLENGTH, fmt, args);
	va_end(args);

	send(socket, string, strlen(string), 0);
	return(strlen(string));
}

//////////////////////////////////////////////////////////////////////////////
//

int
sockread(s,buf)
int	s;
char	*buf;
{
	char	inc;
	int	bufnum, n;
	fd_set	fds;
	struct	timeval	wait;

	bufnum = 0;

	if (s == -1)
	{
		return (-1);
	}

	wait.tv_sec  = 0L;
	wait.tv_usec = 2500L;
	FD_ZERO(&fds);
	FD_SET(s, &fds);

	if (select(s+1, &fds, NULL, 0, &wait) > 0)
	{
		do
		{
			n = read(s, &inc, 1);
			if (n == 0)
			{
				return -1;
			}
			if (bufnum < BUFFER_SIZE - 1 )
			{
				buf[bufnum++] = inc;
			}
		}
		while (inc != '\n');
		{
			buf[bufnum] = '\0';
		}
		brx += bufnum;
		return bufnum;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//


