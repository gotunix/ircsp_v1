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

int	load_cadmin		();

///////////////////////////////////////////////////////////////////////////////
//

int
load_cadmin ()
{
	FILE	*fp, *new;
	char	read[512], *ptr[6];

	fp = fopen("cadmin.db", "r");
	if (!fp)
	{
		new = fopen("cadmin.db", "a");
		fprintf(new, "; Channel Admin Database\n");
		fclose(new);
		return 0;
	}
	else
	{
		while (fgets(read, 256, fp) != NULL)
		{
			if (read[0] == ';')
			{
				continue;
			}

			ptr[0] = strtok(read, ":");
			ptr[1] = strtok(NULL, ":");
			ptr[2] = strtok(NULL, ":");
			ptr[3] = strtok(NULL, ":");
			ptr[4] = strtok(NULL, "\n");

			addCadmin(ptr[0], ptr[1], ptr[2], atoi(ptr[3]),
				atoi(ptr[4]));
		}
		fclose(fp);
		return 1;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//


