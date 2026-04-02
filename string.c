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



