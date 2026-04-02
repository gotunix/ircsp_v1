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

int	parse_cmode		(char *, char *, char *);

///////////////////////////////////////////////////////////////////////////////
//

int
parse_cmode (who,chan,modes)
char	*who;
char	*chan;
char	*modes;
{
	ChanDB	*cs;
	int	p, addmode;
	char	*sptr[3];

	cs = chandb;
	p = -1;
	addmode = 0;

	sptr[0] = strtok(modes, " ");
	sptr[1] = strtok(NULL, " ");

	cs = findChan(chan);
	if (!cs)
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
		if (modes[p] == 'o')
		{
			if (addmode)
			{
				send_to_sock(s, 
					"MODE %s -o %s\n",
					chan, sptr[1]);

				send_to_sock(s, 
					"MODE %s -v %s\n",
					chan, sptr[1]);
			}
		}
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//


