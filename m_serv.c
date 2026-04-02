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

int	m_stats			(char *);

//////////////////////////////////////////////////////////////////////////////
//

int
m_stats (buf)
char	*buf;
{
	char	*ptr[5];

	ptr[0] = strtok(buf, " ");
	strtok(NULL, " ");
	ptr[2] = strtok(NULL, " ");

	if (!strcasecmp(ptr[2], "VERSION"))
	{
		send_to_sock(s, 
			"NOTICE %s :IRCSP [\2%s\2]\n",
			ptr[0], VERSION);

		send_to_sock(s, 
			"NOTICE %s :Copyright (C) 1999 Lostworld Development.\n", 
			ptr[0]);

		send_to_sock(s, 
			"NOTICE %s :Written By: Justin Ovens (evilicey)\n", 
			ptr[0]);

		send_to_sock(s, 
			"NOTICE %s :Compiled on: %s [%s] \n",
			ptr[0], __DATE__, __TIME__);

		send_to_sock(s, 
			"NOTICE %s :$Last Source Update$ %s\n",
			ptr[0], DATE);
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//


