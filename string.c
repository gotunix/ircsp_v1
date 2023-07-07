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

char *
token (tokenlist,index)
char	*tokenlist;
int	index;
{
	static		char	token[512];
	unsigned	int	curtok, curpos, tokenpos;

	curtok = 1;
	curpos = 0;
	tokenpos = 0;

	while (curtok < index)
	{
		if (tokenlist[curpos++] == ' ')
		{
			curtok++;
		}
		if (tokenlist[curpos] == '\n')
		{
			return NULL;
		}
	}
	while ((tokenlist[curpos] != ' ') &&
		(tokenlist[curpos] != '\r') &&
		(tokenlist[curpos] != '\n'))
	{
		token[tokenpos++] = tokenlist[curpos++];
	}
	token[tokenpos] = '\0';
	return (char *)token;
}

///////////////////////////////////////////////////////////////////////////////
//

char *
lrange (tokenlist,from)
char	*tokenlist;
int	from;
{
	static		char	token[1024];
	unsigned	int	curtok, tokenpos, curpos;

	curtok = 1;
	tokenpos = 0;
	curpos = 0;

	while (curtok < from)
	{
		if (tokenlist[curpos++] == ' ')
		{
			curtok++;
		}
		else if ((tokenlist[curpos] == '\n') || 
			(tokenlist[curpos] ==  '\0'))
		{
			return NULL;
		}
	}
	while ((tokenlist[curpos] != '\n') && 
		(tokenlist[curpos] != '\0') &&
		(tokenlist[curpos] != '\r'))
	{
		token[tokenpos++] = tokenlist[curpos++];
	}
	token[tokenpos] = '\0';
	return (char *)token;
}

///////////////////////////////////////////////////////////////////////////////
//

int
tokenize (inlist,sep)
char	*inlist;
char	sep;
{
	char	outlist[1024];
	int	pos, num;

	pos = 0;
	num = 1;

	while ((inlist[pos] != '\n') && (inlist[pos] != '\0'))
	{
		if (inlist[pos] == sep)
		{
			outlist[pos] = ' ';
			++num;
		}
		else
		{
			outlist[pos] = inlist[pos];
		}
		++pos;
	}
	strcpy(inlist, outlist);
	inlist[pos] = '\0';

	return num;
}

///////////////////////////////////////////////////////////////////////////////
//
 
char *
nocolon (line)
char	*line;
{
	int	pos;

	pos = -1;

	if (line[0] != ':') 
	{
		return 0;
	}
	while (line[++pos] != '\0')
	{
		line[pos] = line[pos+1];
	}
	return line;
}

///////////////////////////////////////////////////////////////////////////////
//

int 
numtokens (line)
char	*line;
{
	int	pos, num_tok;

	pos = 0;
	num_tok = 1;

	for (;pos<strlen(line); ++pos)
	{
		if (line[pos] == ' ')
		{
			num_tok += 1;
		}
	}
	return num_tok;
}

///////////////////////////////////////////////////////////////////////////////
//

char *
chop (chopme)
char	*chopme;
{
	int	x;

	x = strlen(chopme) - 1;

	if ((chopme[ x ] == '\n') || (chopme[ x ] == '\r'))
	{
		chopme[ x ] = '\0';
	}
	return chopme;
}

///////////////////////////////////////////////////////////////////////////////
//



